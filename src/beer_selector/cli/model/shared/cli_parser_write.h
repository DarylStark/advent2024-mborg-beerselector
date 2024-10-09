#ifndef CLI_PARSER_WRITE_H
#define CLI_PARSER_WRITE_H

#include "../../../../cli/model/cli_model.h"

class CLIParserWrite : public CLIParserFactory
{
private:
    static std::shared_ptr<ArgumentedCommandParser> _parser;
    std::shared_ptr<ArgumentedCommandParser> _create_parser();

public:
    std::shared_ptr<ArgumentedCommandParser> get_parser();
};

#endif /* CLI_PARSER_WRITE_H */
