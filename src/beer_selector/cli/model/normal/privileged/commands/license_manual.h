#ifndef LICENSE_MANUAL_H
#define LICENSE_MANUAL_H

#include "../../../../../../cli/command/command.h"

class LicenseManual : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* LICENSE_MANUAL_H */