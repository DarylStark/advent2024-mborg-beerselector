#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include "normal_state.h"

NormalState::NormalState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                           ds::BaseApplication &application)
    : ds::BaseState(factory, application)
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
            if (incorrect_counter >= 3)
            {
                normal_state->_factory->get_output_handler()->println("\r\nBlocking login for 10 seconds");
                normal_state->_factory->get_os()->sleep_miliseconds(10 * 1000);
                incorrect_counter = 0;
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
    normal_state->_factory->get_output_handler()->println("Welkom in the normal CLI");
    vTaskSuspend(NULL);
}

void NormalState::run() {
    xTaskCreatePinnedToCore(
        NormalState::login_prompt,
        "login_prompt",
        4096,
        this,
        2,
        NULL,
        1);
    vTaskDelete(NULL);
}