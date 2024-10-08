#ifndef AUTH_CREDENTIALS_H
#define AUTH_CREDENTIALS_H

#include "../../../../../cli/command/command.h"

class MemoryInfo : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* AUTH_CREDENTIALS_H */