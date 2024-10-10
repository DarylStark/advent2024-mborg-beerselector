#include "./cli_shared_parsers.h"
#include "../../command/reload_command.h"
#include "../../command/exit_command.h"

std::shared_ptr<ArgumentedCommandParser> CLISharedParser::get_reload_parser()
{
    return CLIReloadParserFactory().get_parser();
}

std::shared_ptr<ArgumentedCommandParser> CLISharedParser::get_exit_parser()
{
    return CLIExitParserFactory().get_parser();
}

// Specific parsers

// Reload parser

std::shared_ptr<ArgumentedCommandParser> CLIReloadParserFactory::_parser =
    nullptr;

std::shared_ptr<ArgumentedCommandParser>
CLIReloadParserFactory::_create_parser()
{
    // Parser for the ROMMON mode
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>("Reload",
                                                  "Reload the device.",
                                                  std::make_shared<ReloadCommand>());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIReloadParserFactory::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}

// Exit parser

std::shared_ptr<ArgumentedCommandParser> CLIExitParserFactory::_parser =
    nullptr;

std::shared_ptr<ArgumentedCommandParser>
CLIExitParserFactory::_create_parser()
{
    // Parser for the ROMMON mode
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>("Exit",
                                                  "Exit from current mode.",
                                                  std::make_shared<ExitCommand>());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIExitParserFactory::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}