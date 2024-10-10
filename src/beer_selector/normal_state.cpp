#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include "normal_state.h"
#include "logging_data.h"

NormalState::NormalState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                           ds::BaseApplication &application)
    : ds::BaseState(factory, application)
{
}


void NormalState::log(Severity severity, const std::string message)
{
    _logging_queue.push(LoggingData(severity, message));
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
            normal_state->log(WARNING, "Incorrect login attempt on console! Username: \"" + username + "\"");
            if (incorrect_counter >= CONFIG_BS_LOGIN_INCORRECT_TRIES_BEFORE_LOCK)
            {
                normal_state->log(WARNING, "Too many incorrect login attempts on console. Blocking console");
                normal_state->_factory->get_output_handler()->println("\r\nBlocking login for " + std::to_string(CONFIG_BS_LOGIN_BLOCKING_TIME) + " seconds");
                normal_state->_factory->get_os()->sleep_miliseconds(CONFIG_BS_LOGIN_BLOCKING_TIME * 1000);
                incorrect_counter = 0;
                normal_state->log(INFO, "Unblocking console");
            }
        }
    }

    xTaskCreatePinnedToCore(
        NormalState::normal_cli,
        "console_cli",
        4096,
        args,
        2,
        NULL,
        1);
    vTaskDelete(NULL);
}

void NormalState::normal_cli(void *args)
{
    NormalState *normal_state = (NormalState *)args;
    vTaskSuspend(NULL);
}

void NormalState::logging_service(void *args)
{
    NormalState *state = (NormalState *)args;
    state->log(INFO, "Logging service is started");

    while (true)
    {
        while (!state->_logging_queue.empty())
        {
            LoggingData data = state->_logging_queue.front();
            state->_logging_queue.pop();
            state->_factory->get_output_handler()->println(data.get_message());
        }
        state->_factory->get_os()->sleep_miliseconds(CONFIG_BS_NORMAL_LOGGING_TIMEOUT);
    }
}

void NormalState::run() {
    log(INFO, "Bootloader is finished");

    xTaskCreatePinnedToCore(
        NormalState::logging_service,
        "logger",
        10224,
        this,
        1,
        NULL,
        1);

    // Give the logger some time to start up
    _factory->get_os()->sleep_miliseconds(CONFIG_BS_NORMAL_START_TIMEOUT);

    xTaskCreatePinnedToCore(
        NormalState::login_prompt,
        "login_prompt",
        4096,
        this,
        1,
        NULL,
        1);
    vTaskDelete(NULL);
}