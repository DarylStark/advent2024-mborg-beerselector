#ifndef AUTH_ENABLE_H
#define AUTH_ENABLE_H

#include "../../../../../cli/command/command.h"

class AuthEnable : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* AUTH_ENABLE_H */