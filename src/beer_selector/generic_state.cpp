#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include "generic_state.h"

GenericState::GenericState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                           ds::BaseApplication &application)
    : ds::BaseState(factory, application)
{
}

void GenericState::login_prompt(void *args) {
    GenericState *generic_state = (GenericState *)args;
    uint32_t incorrect_counter = 0;
    
    while (true)
    {
        generic_state->_factory->get_output_handler()->println("\r\n\r\nLOGIN TO CONTINUE\r\n\r\n");
        std::string username = generic_state->_factory->get_input_handler()->get_string("Username: ", "");
        if (username.length() == 0)
            continue;

        generic_state->_factory->get_output_handler()->print("\r\n");
        std::string password = generic_state->_factory->get_input_handler()->get_password("Password: ", "");

        // Compare the username and password. If correct, proceed. Otherwise, freeze
        auto configuration_manager = generic_state->_factory->get_configuration_manager();
        const std::string expected_username = configuration_manager->get("auth.user");
        const std::string expected_password = configuration_manager->get("auth.pass");

        if (username == expected_username && password == expected_password)
        {
            generic_state->_factory->get_output_handler()->println("");
            break;
        }
        else
        {
            generic_state->_factory->get_output_handler()->println("\r\n\r\nCredentials are incorrect!");
            incorrect_counter++;
            if (incorrect_counter >= 3)
            {
                generic_state->_factory->get_output_handler()->println("\r\nBlocking login for 10 seconds");
                generic_state->_factory->get_os()->sleep_miliseconds(10 * 1000);
                incorrect_counter = 0;
            }
        }
    }

    xTaskCreatePinnedToCore(
        GenericState::normal_cli,
        "console_cli",
        4096,
        args,
        2,
        NULL,
        1);
    vTaskDelete(NULL);
}

void GenericState::normal_cli(void *args)
{
    GenericState *generic_state = (GenericState *)args;
    generic_state->_factory->get_output_handler()->println("Welkom in the normal CLI");
    vTaskSuspend(NULL);
}

void GenericState::run() {
    xTaskCreatePinnedToCore(
        GenericState::login_prompt,
        "login_prompt",
        4096,
        this,
        2,
        NULL,
        1);
    vTaskDelete(NULL);
}