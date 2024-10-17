#ifndef EXTERNAL_LICENSE_H
#define EXTERNAL_LICENSE_H

#include "../../../../../cli/command/command.h"

class ExternalLicenseInfo : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* EXTERNAL_LICENSE_H */