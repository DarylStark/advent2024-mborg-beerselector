#ifndef HOSTNAME_H
#define HOSTNAME_H

#include "../../../../../cli/command/command.h"

class Hostname : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* HOSTNAME_H */