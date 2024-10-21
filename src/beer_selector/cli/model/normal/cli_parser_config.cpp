#include "cli_parser_config.h"
#include "commands/config_exit.h"
#include "cli_parser_priv_exec.h"
#include "privileged/license_parsers.h"

#include "config_commands/beer_list.h"
#include "config_commands/log_buffer.h"
#include "config_commands/service_uart_licensing.h"
#include "config_commands/set_config_string.h"

#include "../../../logging.h"

std::shared_ptr<ArgumentedCommandParser> CLIParserConfig::_parser = nullptr;

std::shared_ptr<ArgumentedCommandParser> CLIParserConfig::_get_hostname_parser()
{
    std::shared_ptr<SetConfigString> hostname_cmd = std::make_shared<SetConfigString>(
        std::map<std::string, std::string>{{"hostname", "sys.hostname"}});
    hostname_cmd->set_post_execute([]
        (std::map<std::string, std::string> args)
        {
            log(INFO, "Hostname set to: \"" + args["hostname"] + "\"");
            return false;
        });

    // hostname
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Set device hostname",
            "Set the hostname for the device.",
            hostname_cmd);
    
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

std::shared_ptr<ArgumentedCommandParser> CLIParserConfig::_get_service_parser()
{
    // service
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Configure services",
            "Configure the state of services");
    
    // logging-buffer size
    std::shared_ptr<ArgumentedCommandParser> external_licensing =
        std::make_shared<ArgumentedCommandParser>(
            "Enable or disable the external licensing service",
            "Enable or disable the external licensing service which can be used to install licenses using a license adapter.",
            std::make_shared<ServiceUARTLicensing>());
    std::vector<std::string> states = {"enable", "disable"};
    external_licensing->add_argument(std::make_shared<EnumArgument>(
        "state",
        states,
        true,
        "The desired state of the service [enable | disable]"));

    // Tie them together
    parser->add_parser("external-licensing", external_licensing);

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserConfig::_get_wifi_parser()
{
    std::shared_ptr<SetConfigString> wifi_cmd = std::make_shared<SetConfigString>(
        std::map<std::string, std::string>{
            {"ssid", "wifi.ssid"},
            {"password", "wifi.password"}
        });
    wifi_cmd->set_post_execute([]
        (std::map<std::string, std::string> args)
        {
            log(INFO, "Wifi SSID is set to: \"" + args["ssid"] + "\"");
            // TODO: Connect to the (new) wifi network
            return false;
        });

    // Wifi
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Set wifi credentials",
            "Set the credentials for the wifi.",
            wifi_cmd);
    
    parser->add_argument(std::make_shared<StringArgument>(
        "ssid", true, "The SSID to set"));
    parser->add_argument(std::make_shared<StringArgument>(
        "password", true, "The password to set")); // TODO: Make sure a password with spaces can be entered

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
    parser->add_parser("service", _get_service_parser());
    parser->add_parser("wifi", _get_wifi_parser());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserConfig::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}