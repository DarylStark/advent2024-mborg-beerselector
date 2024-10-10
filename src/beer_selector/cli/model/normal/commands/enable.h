#ifndef ENABLE_H
#define ENABLE_H

#include "../../../../../cli/command/command.h"

class Enable : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* ENABLE_H */