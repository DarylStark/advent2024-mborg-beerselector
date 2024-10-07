#ifndef HELP_COMMAND_H
#define HELP_COMMAND_H

#include <iomanip>

#include "../parser/argumented_command_parser.h"
#include "command.h"

class HelpCommand : public Command
{
private:
    ArgumentedCommandParser* _parser;

public:
    HelpCommand(ArgumentedCommandParser* parser);
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* HELP_COMMAND_H */