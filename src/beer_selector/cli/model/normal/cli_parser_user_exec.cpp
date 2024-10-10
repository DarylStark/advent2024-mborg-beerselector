#include "cli_parser_user_exec.h"

#include "../shared/cli_parser_sys_info.h"
#include "../shared/cli_parser_rtos_info.h"

std::shared_ptr<ArgumentedCommandParser> CLIParserUserExec::_parser = nullptr;

std::shared_ptr<ArgumentedCommandParser>
CLIParserUserExec::_get_show_parser()
{
    // Show
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Show information",
            "Show statistics and system information.");
    
    // Add shared parsers
    parser->add_parser("system", CLIParserSysInfo().get_parser());
    parser->add_parser("freertos", CLIParserRTOSInfo().get_parser());

    return parser;
}

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

    // Add specific parsers
    parser->add_parser("show", _get_show_parser());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserUserExec::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}