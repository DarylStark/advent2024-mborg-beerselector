#ifndef LOG_BUFFER_H
#define LOG_BUFFER_H

#include "../../../../../cli/command/command.h"

class LogBufferSetSize : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* LOG_BUFFER_H */