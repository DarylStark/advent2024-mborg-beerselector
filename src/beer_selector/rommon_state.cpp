#include <functional>
#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include "rommon_state.h"

#include "../cli/cli/cli_runner.h"
#include "cli/model/rommon/cli_parser_rommon_factory.h"

RommonState::RommonState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                         ds::BaseApplication &application)
    : ds::BaseState(factory, application),
      _output_handler(_factory->get_output_handler()),
      _input_handler(_factory->get_input_handler())
{
}

void RommonState::rommon_cli_task(void *args)
{
    RommonState *rommon_state = (RommonState *)args;
    rommon_state->_factory->get_output_handler()->println("INITIALIZING ROMMON\r\n\r\n");

    CLIParserROMMONFactory parser_factory;
    std::shared_ptr<ArgumentedCommandParser> word_parser =
        parser_factory.get_parser();

    rommon_state->_output_handler->println("ROMMON INITIALIZED\r\n\r\n");

    CLIRunner runner(word_parser, "ROMMON> ");
    while (runner.run())
        ;

    rommon_state->_output_handler->println("EXITING ROMMON\r\n\r\n");
}

void RommonState::run()
{
    xTaskCreatePinnedToCore(
        RommonState::rommon_cli_task,
        "rommon_cli",
        4096,
        this,
        1,
        NULL,
        1);
    vTaskDelete(NULL);
}