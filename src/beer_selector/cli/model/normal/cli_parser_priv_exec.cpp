#include "cli_parser_priv_exec.h"

#include "../shared/cli_parser_sys_info.h"
#include "../shared/cli_parser_rtos_info.h"
#include "../shared/cli_parser_write.h"

#include "privileged/license_parsers.h"
#include "privileged/beerlist_parsers.h"

#include "commands/disable.h"
#include "commands/configure.h"
#include "commands/show_log_buffer.h"
#include "commands/show_wifi.h"
#include "commands/external_license_info.h"
#include "commands/ota.h"

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

    // Specific parsers
    parser->add_parser("license", LicenseParserShow().get_parser());
    parser->add_parser("beer-list", ShowBeerList().get_parser());
    parser->add_parser("log-buffer", _get_show_log_parser());
    parser->add_parser("external-license", _get_show_external_license_parser());
    parser->add_parser("wifi", _get_show_wifi_parser());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserPrivExec::_get_show_log_parser()
{
    // disable
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Show the logging buffer",
            "Show the logging buffer in the terminal",
            std::make_shared<ShowLogBuffer>());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserPrivExec::_get_show_wifi_parser()
{
    // show wifi
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Show information about the WiFi",
            "Show information about the WiFi",
            std::make_shared<ShowWifi>());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserPrivExec::_get_show_external_license_parser()
{
    // disable
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Show information about the external license service",
            "Show information about the external license service",
            std::make_shared<ExternalLicenseInfo>());

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

std::shared_ptr<ArgumentedCommandParser> CLIParserPrivExec::_get_ota_parser()
{
    // ota
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Over-the-air update",
            "Install software over the WiFi connection. Updates are installed at the inactive partition. At the next reboot, the inactive partition will become the active partition.");
    
    // ota get-versions
    std::shared_ptr<ArgumentedCommandParser> get =
        std::make_shared<ArgumentedCommandParser>(
            "Get installable versions",
            "Retrieve a list of available versions",
            std::make_shared<OTAGetVersions>());
    
    // ota install
    std::shared_ptr<ArgumentedCommandParser> install =
        std::make_shared<ArgumentedCommandParser>(
            "Install a specific version",
            "Install a specific version of the software. Enter `latest` to install the latest version.",
            std::make_shared<OTAInstall>());
    install->add_argument(
        std::make_shared<StringArgument>(
            "version",
            true,
            "The version to install"));
    
    // Tie the parsers together
    parser->add_parser("get-versions", get);
    parser->add_parser("install", install);

    return parser;
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
    parser->add_parser("ota", _get_ota_parser());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserPrivExec::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}