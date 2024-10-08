#include "./cli_parser_sys_info.h"

#include "commands/memory_info.h"
#include "commands/chip_info.h"

std::shared_ptr<ArgumentedCommandParser> CLIParserSysInfo::_parser =
    nullptr;

std::shared_ptr<ArgumentedCommandParser>
CLIParserSysInfo::_create_parser()
{
    // Parser for the ROMMON mode
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "System information", "Get system information");
    
    // Parser for memory information
    std::shared_ptr<ArgumentedCommandParser> memory_parser =
        std::make_shared<ArgumentedCommandParser>(
            "Memory information",
            "Get memory information",
            std::make_shared<MemoryInfo>());
    
    // Parser for chip information
    std::shared_ptr<ArgumentedCommandParser> chip_parser =
        std::make_shared<ArgumentedCommandParser>(
            "Chip information",
            "Get information about the chip",
            std::make_shared<ChipInfo>());

    // Add parsers
    parser->add_parser("memory", memory_parser);
    parser->add_parser("chip", chip_parser);

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserSysInfo::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}