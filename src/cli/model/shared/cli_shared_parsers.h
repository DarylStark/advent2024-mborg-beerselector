#ifndef CLI_SHARED_PARSERS_H
#define CLI_SHARED_PARSERS_H

#include "../cli_model.h"

class CLISharedParser
{
public:
    static std::shared_ptr<ArgumentedCommandParser> get_reload_parser();
};

class CLIReloadParserFactory : public CLIParserFactory
{
private:
    static std::shared_ptr<ArgumentedCommandParser> _parser;
    std::shared_ptr<ArgumentedCommandParser> _create_parser();

public:
    std::shared_ptr<ArgumentedCommandParser> get_parser();
};

#endif /* CLI_SHARED_PARSERS_H */
