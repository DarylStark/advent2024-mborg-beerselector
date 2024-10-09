#ifndef RELOAD_COMMAND_H
#define RELOAD_COMMAND_H

#include "command.h"

class ReloadCommand : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* RELOAD_COMMAND_H */
