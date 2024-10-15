#ifndef SHOW_LOGBUFFER_H
#define SHOW_LOGBUFFER_H

#include "../../../../../cli/command/command.h"

class ShowLogBuffer : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* SHOW_LOGBUFFER_H */