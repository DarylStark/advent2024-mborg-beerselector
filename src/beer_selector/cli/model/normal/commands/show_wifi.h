#ifndef SHOW_WIFI_H
#define SHOW_WIFI_H

#include "../../../../../cli/command/command.h"

class ShowWifi : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* SHOW_WIFI_H */