#include "./cli_parser_show_version.h"
#include "commands/version.h"

std::shared_ptr<ArgumentedCommandParser> CLIParserShowVersion::_parser =
    nullptr;

std::shared_ptr<ArgumentedCommandParser>
CLIParserShowVersion::_create_parser()
{
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Version information",
            "Get information about the running software.",
            std::make_shared<Version>());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserShowVersion::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}