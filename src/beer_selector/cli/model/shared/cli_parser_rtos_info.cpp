#include "./cli_parser_rtos_info.h"
#include "commands/rtos_tasks.h"

std::shared_ptr<ArgumentedCommandParser> CLIParserRTOSInfo::_parser =
    nullptr;

std::shared_ptr<ArgumentedCommandParser>
CLIParserRTOSInfo::_create_parser()
{
    // Parser for the ROMMON mode
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "RTOS information", "Get information from FreeRTOS");
    
    // Parser for memory information
    std::shared_ptr<ArgumentedCommandParser> tasks =
        std::make_shared<ArgumentedCommandParser>(
            "Running tasks",
            "Get all tasks",
            std::make_shared<RTOSTasks>());

    // Add parsers
    parser->add_parser("tasks", tasks);

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserRTOSInfo::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}