#include "./cli_parser_rommon_factory.h"

#include "../../../beer_selector/cli/commands/auth_credentials.h"

std::shared_ptr<ArgumentedCommandParser> CLIParserROMMONFactory::_parser =
    nullptr;

std::shared_ptr<ArgumentedCommandParser>
CLIParserROMMONFactory::_get_auth_parser()
{
    // Auth
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Authentication configuration",
            "Configure authentication settings like username and password and "
            "the password to enter privileged mode.");

    // auth credentials <username> <password>
    std::shared_ptr<ArgumentedCommandParser> credentials =
        std::make_shared<ArgumentedCommandParser>(
            "Authentication credentials",
            "Set the credentials to log in to the device.",
            std::make_shared<AuthCredentials>());
    credentials->add_argument(std::make_shared<StringArgument>(
        "username", true, "The username to set"));
    credentials->add_argument(std::make_shared<StringArgument>(
        "password", true, "The password to set"));

    // auth enable <password>
    std::shared_ptr<ArgumentedCommandParser> enable =
        std::make_shared<ArgumentedCommandParser>(
            "Set password for privilegd mode",
            "Set the password that is used "
            "to enter privileged mode.");
    enable->add_argument(std::make_shared<StringArgument>(
        "password", true, "The password to set"));

    // Add the `credentials` subparser to the `auth` parser
    parser->add_parser("credentials", credentials);
    parser->add_parser("enable", enable);

    return parser;
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
    parser->add_parser("auth", _get_auth_parser());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> CLIParserROMMONFactory::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}