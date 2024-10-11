#include "license_parsers.h"
#include "commands/show_license.h"

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