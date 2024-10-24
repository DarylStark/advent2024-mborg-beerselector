#ifndef OTA_H
#define OTA_H

#include "../../../../../cli/command/command.h"

class OTAGetVersions : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

class OTAInstall : public Command
{
private:
    std::string _get_filename(std::string version) const;

public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* OTA_H */