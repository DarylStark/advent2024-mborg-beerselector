#ifndef VERSION_H
#define VERSION_H

#include "../../../../../cli/command/command.h"

class Version : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* #define VERSION_H */