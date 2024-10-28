#ifndef CLI_PARSER_SHOW_VERION_H
#define CLI_PARSER_SHOW_VERION_H

#include "../../../../cli/model/cli_model.h"

class CLIParserShowVersion : public CLIParserFactory
{
private:
    static std::shared_ptr<ArgumentedCommandParser> _parser;
    std::shared_ptr<ArgumentedCommandParser> _create_parser();

public:
    std::shared_ptr<ArgumentedCommandParser> get_parser();
};

#endif /* CLI_PARSER_SHOW_VERION_H */
