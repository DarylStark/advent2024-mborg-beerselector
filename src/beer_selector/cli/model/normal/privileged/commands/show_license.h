#ifndef SHOW_LICENSE_H
#define SHOW_LICENSE_H

#include "../../../../../../cli/command/command.h"

class ShowLicense : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* SHOW_LICENSE_H */