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
    : ds::BaseState(factory, application),
      _mode_button_semaphore(xSemaphoreCreateBinary()),
      _beer_list_index(1)
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

                // Display to console
                state->_factory->get_output_handler()->println(data.get_message());

                // Add to log buffer
                if (log_buffer_size > 0)
                    log_buffer.push_back(data.get_message());
            }
        }
        state->_factory->get_os()->sleep_miliseconds(CONFIG_BS_NORMAL_LOGGING_TIMEOUT);
    }
}

void NormalState::input_service(void *args)
{
    NormalState *state = (NormalState *)args;
    log(INFO, "Input service is started");

    // Resume the suspended task
    vTaskResume(state->_display_time_service_task);

    while (true) {
        if (xSemaphoreTake(state->_mode_button_semaphore, portMAX_DELAY) == pdTRUE)
        {
            // Debounce delay
            vTaskDelay(50 / portTICK_PERIOD_MS);

            if (gpio_get_level(GPIO_NUM_23) == 0)
            {
                vTaskSuspend(state->_display_time_service_task);
                xTimerChangePeriod(
                    state->_display_beer_list_timer,
                    state->get_display_beer_list_timer_period(),
                    portMAX_DELAY);
                NormalState::display_beer_list(state->_display_beer_list_timer);
            }
            else if (gpio_get_level(GPIO_NUM_23) == 1)
            {
                state->_beer_list_index = 1;

                state->_factory->get_display()->show_time();
                vTaskResume(state->_display_time_service_task);

                if (state->_display_beer_list_timer != nullptr)
                {
                    xTimerStop(state->_display_beer_list_timer, 0);
                }
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void NormalState::display_time_service(void *args)
{
    NormalState *state = (NormalState *)args;
    while (true)
    {
        state->_factory->get_display()->show_time();
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void NormalState::display_beer_list(TimerHandle_t xTimer)
{
    NormalState *state = (NormalState *)pvTimerGetTimerID(xTimer);
    if (state == nullptr)
    {
        log(ERROR, "Failed to get the state from the timer");
        return;
    }

    uint16_t beer = state->_beer_list_index;

    state->_factory->get_display()->set_beer(
        beer,
        BeerList().get_beer_for_day(beer));

    // TODO: Method in NormalState for this
    state->_beer_list_index++;
    if (state->_beer_list_index > 31)
        state->_beer_list_index = 1;
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
        1536,
        this,
        1,
        NULL,
        1);
}

void NormalState::start_cli_service() {
    xTaskCreatePinnedToCore(
        NormalState::normal_cli,
        "console_cli",
        8192,
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

void NormalState::start_display_time_service()
{
    xTaskCreatePinnedToCore(
        NormalState::display_time_service,
        "display_time",
        1024,
        this,
        1,
        &_display_time_service_task,
        1);
}

void NormalState::create_display_beer_list_timer()
{
    // Create a timer to display the beers periodically
    _display_beer_list_timer = xTimerCreate(
        "display_beer_list_timer",
        get_display_beer_list_timer_period(),
        pdTRUE,
        (void *)this,
        NormalState::display_beer_list);
}

uint32_t NormalState::get_display_beer_list_timer_period() const
{
    return (std::stoi(_factory->get_configuration_manager()->get("dp.t_beer")) * 1000) / portTICK_PERIOD_MS;
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

    // Set timezone
    setenv("TZ", "CET-1CEST,M3.5.0/2,M10.5.0/3", 1); // TODO: Make this configurable
    tzset();

    // Start the "always running" services
    start_logging_service();
    start_input_service();
    start_display_time_service();

    // Start the timer for the beer display
    create_display_beer_list_timer();

    // Give the logger some time to start up
    _factory->get_os()->sleep_miliseconds(CONFIG_BS_NORMAL_START_TIMEOUT);

    // Set max size for the logging buffer
    uint16_t max_log_buffer_size = std::stoi(_factory->get_configuration_manager()->get("log.buf.len"));
    log_buffer.set_max_size(max_log_buffer_size);
    log_buffer_size = max_log_buffer_size;

    // Start the Serial License Retriever service, if enabled
    if (_factory->get_configuration_manager()->get("svc.uart_lic") == "1")
        _factory->get_serial_license_retriever()->start();
    
    // Start the Wifi Manager service
    _factory->get_wifi_manager()->start();

    // Start the login service
    start_login_service();

    // End the current task
    vTaskDelete(NULL);
}
