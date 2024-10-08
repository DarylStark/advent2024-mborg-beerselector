#ifndef CLI_PARSER_SYS_INFO_H
#define CLI_PARSER_SYS_INFO_H

#include "../../../../cli/model/cli_model.h"

class CLIParserSysInfo : public CLIParserFactory
{
private:
    static std::shared_ptr<ArgumentedCommandParser> _parser;
    std::shared_ptr<ArgumentedCommandParser> _create_parser();

public:
    std::shared_ptr<ArgumentedCommandParser> get_parser();
};

#endif /* CLI_PARSER_SYS_INFO_H */
