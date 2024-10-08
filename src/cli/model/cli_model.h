#ifndef CLI_MODEL_H
#define CLI_MODEL_H

#include <memory>

#include "../parser/argumented_command_parser.h"

class CLIParserFactory
{
public:
    virtual std::shared_ptr<ArgumentedCommandParser> get_parser() = 0;
};

#endif /* CLI_MODEL_H */