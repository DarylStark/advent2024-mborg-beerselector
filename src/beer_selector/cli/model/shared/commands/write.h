#ifndef WRITE_H
#define WRITE_H

#include "../../../../../cli/command/command.h"

class Write : public Command
{
private:
    void _save_configuration();
    void _erase_configuration();
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* #define WRITE_H */