#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include "normal_state.h"
#include "logging_data.h"

#include "cli/model/normal/cli_parser_user_exec.h"
#include "../cli/cli/cli_runner.h"

#include "globals.h"
#include "logging.h"

#include "beer_list/beer_list.h"

#include <driver/gpio.h>

NormalState::NormalState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                           ds::BaseApplication &application)
    : ds::BaseState(factory, application), _mode_button_semaphore(xSemaphoreCreateBinary())
{
}

void NormalState::login_prompt(void *args) {
    NormalState *normal_state = (NormalState *)args;
    uint32_t incorrect_counter = 0;    
    while (true)
    {
        normal_state->_factory->get_output_handler()->println("\r\n\r\nLOGIN TO CONTINUE\r\n\r\n");
        std::string username = normal_state->_factory->get_input_handler()->get_string("Username: ", "");
        if (username.length() == 0)
            continue;

        normal_state->_factory->get_output_handler()->print("\r\n");
        std::string password = normal_state->_factory->get_input_handler()->get_password("Password: ", "");

        // Compare the username and password. If correct, proceed. Otherwise, freeze
        auto configuration_manager = normal_state->_factory->get_configuration_manager();
        const std::string expected_username = configuration_manager->get("auth.user");
        const std::string expected_password = configuration_manager->get("auth.pass");

        if (username == expected_username && password == expected_password)
        {
            normal_state->_factory->get_output_handler()->println("");
            break;
        }
        else
        {
            normal_state->_factory->get_output_handler()->println("\r\n\r\nCredentials are incorrect!");
            incorrect_counter++;
            log(WARNING, "Incorrect login attempt on console! Username: \"" + username + "\"");
            if (incorrect_counter >= CONFIG_BS_LOGIN_INCORRECT_TRIES_BEFORE_LOCK)
            {
                log(WARNING, "Too many incorrect login attempts on console. Blocking console");
                normal_state->_factory->get_output_handler()->println("\r\nBlocking login for " + std::to_string(CONFIG_BS_LOGIN_BLOCKING_TIME) + " seconds");
                normal_state->_factory->get_os()->sleep_miliseconds(CONFIG_BS_LOGIN_BLOCKING_TIME * 1000);
                incorrect_counter = 0;
                log(INFO, "Unblocking console");
            }
        }
    }

    normal_state->start_cli_service();

    vTaskDelete(NULL);
}

void NormalState::normal_cli(void *args)
{
    NormalState *normal_state = (NormalState *)args;
  
    log(INFO, "Console is started");

    next_parser = CLIParserUserExec().get_parser();
    prompt = "> ";

    while (next_parser != nullptr) {
        CLIRunner runner(next_parser, prompt);
        while (runner.run(true))
            ;
    }
    
    log(INFO, "Console ended");
    normal_state->start_login_service();
    vTaskDelete(NULL);
}

void NormalState::logging_service(void *args)
{
    NormalState *state = (NormalState *)args;
    log(INFO, "Logging service is started");

    while (true)
    {
        {
            // Put the lock in a scope so it gets released after the logging.
            // This way the logging doesn't block the queue. Without this, the
            // console would block if it sends something to the logger.
            std::lock_guard<std::mutex> lock(queue_mutex);
            while (!logging_queue.empty())
            {
                LoggingData data = logging_queue.front();
                logging_queue.pop();
                state->_factory->get_output_handler()->println(data.get_message());
            }
        }
        state->_factory->get_os()->sleep_miliseconds(CONFIG_BS_NORMAL_LOGGING_TIMEOUT);
    }
}

void NormalState::input_service(void *args)
{
    NormalState *state = (NormalState *)args;
    log(INFO, "Input service is started");

    while (true) {
        if (xSemaphoreTake(state->_mode_button_semaphore, portMAX_DELAY) == pdTRUE)
        {
            // Debounce delay
            vTaskDelay(50 / portTICK_PERIOD_MS);

            if (gpio_get_level(GPIO_NUM_23) == 0)
            {
                state->_display_beer_list_timer = xTimerCreate(
                    "display_beer_list_timer",
                    1000 / portTICK_PERIOD_MS,
                    pdTRUE,
                    (void *)0,
                    [](TimerHandle_t xTimer) {
                        // TODO: Display correct beer
                    });

                if (xTimerStart(state->_display_beer_list_timer, 0) != pdPASS)
                {
                    log(ERROR, "Failed to start the timer for the beer-list");
                    continue;
                }

                xTimerStart(state->_display_beer_list_timer, portMAX_DELAY);
            }

            if (gpio_get_level(GPIO_NUM_23) == 1)
            {
                if (state->_display_beer_list_timer != nullptr)
                {
                    xTimerDelete(state->_display_beer_list_timer, 0);
                    state->_display_beer_list_timer = nullptr;
                } else {
                    log(ERROR, "Timer is not running");
                }
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void NormalState::_isr_mode_button_state_change(void * args)
{
    NormalState* state = static_cast<NormalState*>(args);
    xSemaphoreGiveFromISR(state->_mode_button_semaphore, 0);
}

void NormalState::start_logging_service() {
    xTaskCreatePinnedToCore(
        NormalState::logging_service,
        "logger",
        1024,
        this,
        1,
        NULL,
        1);
}

void NormalState::start_cli_service() {
    xTaskCreatePinnedToCore(
        NormalState::normal_cli,
        "console_cli",
        4096,
        this,
        1,
        NULL,
        1);
}

void NormalState::start_login_service() {
    xTaskCreatePinnedToCore(
        NormalState::login_prompt,
        "login_prompt",
        4096,
        this,
        1,
        NULL,
        1);
}

void NormalState::start_input_service() {
    xTaskCreatePinnedToCore(
        NormalState::input_service,
        "input",
        1024,
        this,
        1,
        NULL,
        0);
}

void NormalState::run() {
    log(INFO, "Bootloader is finished");

    // Configure the GPIO for the 'mode' button
    gpio_config_t button_gpio_config = {
        .pin_bit_mask = 1ULL << GPIO_NUM_23,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_ANYEDGE,
    };
    gpio_config(&button_gpio_config);

    // Install the ISR service
    gpio_install_isr_service(0);

    // Add the ISR handler
    gpio_isr_handler_add(GPIO_NUM_23, NormalState::_isr_mode_button_state_change, this);

    // Start the "always running" services
    start_logging_service();
    start_input_service();

    // Give the logger some time to start up
    _factory->get_os()->sleep_miliseconds(CONFIG_BS_NORMAL_START_TIMEOUT);

    // Start the login service
    start_login_service();

    // End the current task
    vTaskDelete(NULL);
}