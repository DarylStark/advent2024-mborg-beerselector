#ifndef CLI_PARSER_PRIV_EXEC_H
#define CLI_PARSER_PRIV_EXEC_H

#include "../../../../cli/model/cli_model.h"
#include "../../../../cli/model/shared/cli_shared_parsers.h"

class CLIParserPrivExec : public CLIParserFactory
{
private:
    static std::shared_ptr<ArgumentedCommandParser> _parser;

    std::shared_ptr<ArgumentedCommandParser> _get_show_parser();
    std::shared_ptr<ArgumentedCommandParser> _get_show_log_parser();
    std::shared_ptr<ArgumentedCommandParser> _get_disable_parser();
    std::shared_ptr<ArgumentedCommandParser> _get_config_parser();
    std::shared_ptr<ArgumentedCommandParser> _get_write_parser();
    std::shared_ptr<ArgumentedCommandParser> _create_parser();

public:
    std::shared_ptr<ArgumentedCommandParser> get_parser();
};

#endif /* CLI_PARSER_PRIV_EXEC_H */
