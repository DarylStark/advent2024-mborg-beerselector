#ifndef CONFIGURE_H
#define CONFIGURE_H

#include "../../../../../cli/command/command.h"

class Configure : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* CONFIGURE_H */