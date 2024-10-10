#include "cli_parser_priv_exec.h"

#include "../shared/cli_parser_sys_info.h"
#include "../shared/cli_parser_rtos_info.h"
#include "../shared/cli_parser_write.h"

#include "commands/disable.h"
#include "commands/configure.h"

std::shared_ptr<ArgumentedCommandParser> CLIParserPrivExec::_parser = nullptr;

std::shared_ptr<ArgumentedCommandParser>
CLIParserPrivExec::_get_show_parser()
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

std::shared_ptr<ArgumentedCommandParser> CLIParserPrivExec::_get_disable_parser()
{
    // disable
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Leave privileged mode",
            "Go to user exec mode.",
            std::make_shared<Disable>());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserPrivExec::_get_config_parser()
{
    // configure
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Enter configuration mode",
            "Go to configuration mode.",
            std::make_shared<Configure>());
    
    parser->add_argument(std::make_shared<StaticArgument>(
        "mode", "terminal", true, "The configuration mode (terminal)"));

    return parser;
}

std::shared_ptr<ArgumentedCommandParser>
CLIParserPrivExec::_get_write_parser()
{
    return CLIParserWrite().get_parser();
}

std::shared_ptr<ArgumentedCommandParser>
CLIParserPrivExec::_create_parser()
{
    // Parser for the ROMMON mode
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Privileged exec mode", "Privileged exec mode is for admin users");

    // Add shared parsers
    parser->add_parser("reload", CLISharedParser::get_reload_parser());

    // Add specific parsers
    parser->add_parser("configure", _get_config_parser());
    parser->add_parser("disable", _get_disable_parser());
    parser->add_parser("exit", _get_disable_parser());
    parser->add_parser("show", _get_show_parser());
    parser->add_parser("write", _get_write_parser());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserPrivExec::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}