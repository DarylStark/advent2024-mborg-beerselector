#ifndef CLI_PARSER_USER_EXEC_H
#define CLI_PARSER_USER_EXEC_H

#include "../../../../cli/model/cli_model.h"
#include "../../../../cli/model/shared/cli_shared_parsers.h"

class CLIParserUserExec : public CLIParserFactory
{
private:
    static std::shared_ptr<ArgumentedCommandParser> _parser;

    std::shared_ptr<ArgumentedCommandParser> _get_show_parser();
    std::shared_ptr<ArgumentedCommandParser> _get_enable_parser();
    std::shared_ptr<ArgumentedCommandParser> _create_parser();

public:
    std::shared_ptr<ArgumentedCommandParser> get_parser();
};

#endif /* CLI_PARSER_USER_EXEC_H */
