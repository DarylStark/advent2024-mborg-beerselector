#ifndef CHIP_INFO_H
#define CHIP_INFO_H

#include "../../../../../cli/command/command.h"

class ChipInfo : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* #define CHIP_INFO_H
 */