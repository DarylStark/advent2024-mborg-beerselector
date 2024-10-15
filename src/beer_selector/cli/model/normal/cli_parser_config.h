#ifndef CLI_PARSER_CONFIG_H
#define CLI_PARSER_CONFIG_H

#include "../../../../cli/model/cli_model.h"
#include "../../../../cli/model/shared/cli_shared_parsers.h"

class CLIParserConfig : public CLIParserFactory
{
private:
    static std::shared_ptr<ArgumentedCommandParser> _parser;

    // Configuration parsers
    std::shared_ptr<ArgumentedCommandParser> _get_hostname_parser();
    std::shared_ptr<ArgumentedCommandParser> _get_beer_list_parser();
    std::shared_ptr<ArgumentedCommandParser> _get_logging_buffer_parser();

    // Leave mode
    std::shared_ptr<ArgumentedCommandParser> _get_exit_parser();
    std::shared_ptr<ArgumentedCommandParser> _create_parser();

public:
    std::shared_ptr<ArgumentedCommandParser> get_parser();
};

#endif /* CLI_PARSER_CONFIG_H */
