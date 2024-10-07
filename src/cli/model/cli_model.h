#ifndef __CLI_MODEL_H__
#define __CLI_MODEL_H__

#include <iostream>
#include <memory>

#include "../parser/argumented_command_parser.h"

class CLIParserFactory
{
public:
    virtual std::shared_ptr<ArgumentedCommandParser> get_parser() = 0;
};

#endif /* __CLI_MODEL_H__ */