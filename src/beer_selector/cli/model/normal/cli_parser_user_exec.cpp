#include "cli_parser_user_exec.h"

std::shared_ptr<ArgumentedCommandParser> CLIParserUserExec::_parser = nullptr;

std::shared_ptr<ArgumentedCommandParser>
CLIParserUserExec::_create_parser()
{
    // Parser for the ROMMON mode
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "User exec mode", "User exec mode is for normal users");

    // Add shared parsers
    parser->add_parser("reload", CLISharedParser::get_reload_parser());
    parser->add_parser("exit", CLISharedParser::get_exit_parser());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserUserExec::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}