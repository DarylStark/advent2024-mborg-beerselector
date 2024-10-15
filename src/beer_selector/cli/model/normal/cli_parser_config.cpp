#include "cli_parser_config.h"
#include "commands/config_exit.h"
#include "cli_parser_priv_exec.h"
#include "privileged/license_parsers.h"

#include "./config_commands/hostname.h"
#include "./config_commands/beer_list.h"
#include "./config_commands/log_buffer.h"

std::shared_ptr<ArgumentedCommandParser> CLIParserConfig::_parser = nullptr;

std::shared_ptr<ArgumentedCommandParser> CLIParserConfig::_get_hostname_parser()
{
    // hostname
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Set device hostname",
            "Set the hostname for the device.",
            std::make_shared<Hostname>());
    
    parser->add_argument(std::make_shared<StringArgument>(
        "hostname", true, "The hostname to set"));

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserConfig::_get_beer_list_parser()
{
    // beer-list
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Configure the beer-list display",
            "Configure the beer-list display");
    
    // Timeout parser
    std::shared_ptr<ArgumentedCommandParser> timeout_parser =
        std::make_shared<ArgumentedCommandParser>(
            "Configure the beer-list display",
            "Configure the beer-list display",
            std::make_shared<BeerListSetTimeOut>());
    timeout_parser->add_argument(std::make_shared<IntArgument>(
        "timeout", true, "The timeout to set"));
    
    // Tie them together
    parser->add_parser("timeout", timeout_parser);

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserConfig::_get_exit_parser()
{
    // exit
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Go back to privileged exec mode",
            "Go back to privileged exec mode.",
            std::make_shared<ConfigExit>());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserConfig::_get_logging_buffer_parser()
{
    // logging-buffer
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Configure logging buffer",
            "Set configuration for the in-memory logging buffer");
    
    // logging-buffer size
    std::shared_ptr<ArgumentedCommandParser> buffer_size =
        std::make_shared<ArgumentedCommandParser>(
            "Set the maximum size of the logging buffer",
            "Set the maximum size of the logging buffer. Setting this to 0 disables the log-buffer",
            std::make_shared<LogBufferSetSize>());
    buffer_size->add_argument(std::make_shared<IntArgument>(
        "max_items",
        true,
        "The maximum number of items in the buffer"));

    // Tie them together
    parser->add_parser("size", buffer_size);

    return parser;
}

std::shared_ptr<ArgumentedCommandParser>
CLIParserConfig::_create_parser()
{
    // Parser for the ROMMON mode
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Privileged exec mode", "Privileged exec mode is for admin users");

    // Add shared parsers
    parser->add_parser("reload", CLISharedParser::get_reload_parser());

    // Add specific parsers
    parser->add_parser("do", CLIParserPrivExec().get_parser());
    parser->add_parser("end", _get_exit_parser());
    parser->add_parser("exit", _get_exit_parser());

    // Configuration
    parser->add_parser("hostname", _get_hostname_parser());
    parser->add_parser("beer-list", _get_beer_list_parser());
    parser->add_parser("license", LicenseConfig().get_parser());
    parser->add_parser("log-buffer", _get_logging_buffer_parser());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserConfig::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}