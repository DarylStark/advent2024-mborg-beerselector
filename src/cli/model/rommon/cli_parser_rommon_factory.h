#ifndef __CLI_PARSER_ROMMON_FACTORY_H__
#define __CLI_PARSER_ROMMON_FACTORY_H__

#include "../cli_model.h"
#include "../shared/cli_shared_parsers.h"

class CLIParserROMMONFactory : public CLIParserFactory
{
private:
    static std::shared_ptr<ArgumentedCommandParser> _parser;

    std::shared_ptr<ArgumentedCommandParser> _create_parser();
    std::shared_ptr<ArgumentedCommandParser> _get_auth_parser();

public:
    std::shared_ptr<ArgumentedCommandParser> get_parser();
};

#endif /* __CLI_PARSER_ROMMON_FACTORY_H__ */
