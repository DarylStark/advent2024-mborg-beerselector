#ifndef RTOS_TASKS_H
#define RTOS_TASKS_H

#include "../../../../../cli/command/command.h"

class RTOSTasks : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* #define RTOS_TASKS_H */