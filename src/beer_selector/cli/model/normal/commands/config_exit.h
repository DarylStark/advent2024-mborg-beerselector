#ifndef CONFIG_EXIT_H
#define CONFIG_EXIT_H

#include "../../../../../cli/command/command.h"

class ConfigExit : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* CONFIG_EXIT_H */