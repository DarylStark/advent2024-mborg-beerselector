#include "license_parsers.h"
#include "commands/show_license.h"
#include "commands/license_manual.h"

std::shared_ptr<ArgumentedCommandParser> LicenseParserShow::_parser = nullptr;

std::shared_ptr<ArgumentedCommandParser>
LicenseParserShow::_create_parser()
{
    // Parser for the ROMMON mode
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "License information",
            "Show license information",
            std::make_shared<ShowLicense>());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> LicenseParserShow::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}

std::shared_ptr<ArgumentedCommandParser> LicenseConfig::_parser = nullptr;

std::shared_ptr<ArgumentedCommandParser>
LicenseConfig::_create_parser()
{
    // license
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Install licenses",
            "Set licenses for the device");
    
    // license manual
    std::shared_ptr<ArgumentedCommandParser> manual =
        std::make_shared<ArgumentedCommandParser>(
            "Enter a license key",
            "Enter a license key manually.",
            std::make_shared<LicenseManual>());
    manual->add_argument(std::make_shared<StringArgument>(
        "license_key", true, "The key of the license to install"));
    
    // Add the parsers
    parser->add_parser("manual", manual);

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> LicenseConfig::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}