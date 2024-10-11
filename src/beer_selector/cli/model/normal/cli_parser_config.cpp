#include "cli_parser_config.h"
#include "commands/config_exit.h"
#include "cli_parser_priv_exec.h"

#include "./config_commands/hostname.h"
#include "./config_commands/license_manual.h"

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

std::shared_ptr<ArgumentedCommandParser> CLIParserConfig::_get_license_parser()
{
    // license
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Install licenses",
            "Set licenses for the device");
    
    // license manual
    std::shared_ptr<ArgumentedCommandParser> manual =
        std::make_shared<ArgumentedCommandParser>(
            "Enter a license code",
            "Enter a license code manually.",
            std::make_shared<LicenseManual>());
    manual->add_argument(std::make_shared<StringArgument>(
        "license_code", true, "The code of the license to install"));
    
    // Add the parsers
    parser->add_parser("manual", manual);

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
    parser->add_parser("license", _get_license_parser());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserConfig::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}