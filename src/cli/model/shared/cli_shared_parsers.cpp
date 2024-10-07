#include "./cli_shared_parsers.h"

std::shared_ptr<ArgumentedCommandParser> CLISharedParser::get_reload_parser()
{
    return CLIReloadParserFactory().get_parser();
}

// Specific parsers

std::shared_ptr<ArgumentedCommandParser> CLIReloadParserFactory::_parser =
    nullptr;

std::shared_ptr<ArgumentedCommandParser>
CLIReloadParserFactory::_create_parser()
{
    // Parser for the ROMMON mode
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>("Reload",
                                                  "Reload the device.");

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIReloadParserFactory::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}