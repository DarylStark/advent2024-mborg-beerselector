#include "./cli_parser_write.h"
#include "commands/write.h"

std::shared_ptr<ArgumentedCommandParser> CLIParserWrite::_parser =
    nullptr;

std::shared_ptr<ArgumentedCommandParser>
CLIParserWrite::_create_parser()
{
    // Parser for the ROMMON mode
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Persistenly save the configuration",
            "Save the configuration to the persistent memory.",
            std::make_shared<Write>());
    
    // Add the `erase` subcommand
    parser->add_argument(std::make_shared<StaticArgument>(
        "erase",
        "erase",
        false,
        "Erase the startup configuration."));

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserWrite::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}