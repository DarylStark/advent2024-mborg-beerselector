#ifndef MEMORY_INFO_H
#define MEMORY_INFO_H

#include "../../../../../cli/command/command.h"

class MemoryInfo : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* MEMORY_INFO_H */