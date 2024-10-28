#include "./cli_parser_rommon_factory.h"

#include "../shared/cli_parser_sys_info.h"
#include "../shared/cli_parser_rtos_info.h"
#include "../shared/cli_parser_write.h"

std::shared_ptr<ArgumentedCommandParser> CLIParserROMMONFactory::_parser =
    nullptr;

std::shared_ptr<ArgumentedCommandParser>
CLIParserROMMONFactory::_get_show_parser()
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
CLIParserROMMONFactory::_get_write_parser()
{
    return CLIParserWrite().get_parser();
}

std::shared_ptr<ArgumentedCommandParser>
CLIParserROMMONFactory::_create_parser()
{
    // Parser for the ROMMON mode
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "ROMMON mode", "ROMMON mode is for experienced users only!");

    // Add shared parsers
    parser->add_parser("reload", CLISharedParser::get_reload_parser());
    parser->add_parser("exit", CLISharedParser::get_reload_parser());

    // Add specific parsers
    parser->add_parser("show", _get_show_parser());
    parser->add_parser("write", _get_write_parser());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserROMMONFactory::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}