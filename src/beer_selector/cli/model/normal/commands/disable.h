#ifndef DISABLE_H
#define DISABLE_H

#include "../../../../../cli/command/command.h"

class Disable : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* DISABLE_H */