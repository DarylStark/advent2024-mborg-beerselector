#ifndef LICENSE_PARSERS_H
#define LICENSE_PARSERS_H

#include "../../../../../cli/model/cli_model.h"

class LicenseParserShow : public CLIParserFactory
{
private:
    static std::shared_ptr<ArgumentedCommandParser> _parser;

    std::shared_ptr<ArgumentedCommandParser> _create_parser();

public:
    std::shared_ptr<ArgumentedCommandParser> get_parser();
};

class LicenseConfig : public CLIParserFactory
{
private:
    static std::shared_ptr<ArgumentedCommandParser> _parser;

    std::shared_ptr<ArgumentedCommandParser> _create_parser();

public:
    std::shared_ptr<ArgumentedCommandParser> get_parser();
};

#endif /* LICENSE_PARSERS_H */
