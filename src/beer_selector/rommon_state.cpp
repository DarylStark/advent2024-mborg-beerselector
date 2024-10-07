#include "rommon_state.h"

#include "../cli/cli/cli_runner.h"
#include "../cli/model/rommon/cli_parser_rommon_factory.h"

RommonState::RommonState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                         ds::BaseApplication &application)
    : ds::BaseState(factory, application),
      _output_handler(_factory->get_output_handler()),
      _input_handler(_factory->get_input_handler())
{
}

void RommonState::loop()
{
    _output_handler->println("INITIALIZING ROMMON\n\n");

    CLIParserROMMONFactory parser_factory;
    std::shared_ptr<ArgumentedCommandParser> word_parser =
        parser_factory.get_parser();

    _output_handler->println("ROMMON INITIALIZED\n\n");

    CLIRunner runner(word_parser, "ROMMON> ");
    while (runner.run())
        ;

    _output_handler->println("EXITING ROMMON\n\n");
}