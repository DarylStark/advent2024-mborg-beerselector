#ifndef EXIT_COMMAND_H
#define EXIT_COMMAND_H

#include "command.h"

class ExitCommand : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* EXIT_COMMAND_H */