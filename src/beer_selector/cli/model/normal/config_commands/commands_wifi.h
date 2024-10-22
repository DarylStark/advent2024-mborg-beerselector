#ifndef COMMANDS_WIFI_H
#define COMMANDS_WIFI_H

#include "set_config_string.h"

class SetConfigStringWifi: public SetConfigString {
public:
    SetConfigStringWifi(std::map<std::string, std::string> arg_config_keys);
    bool execute(std::map<std::string, std::string> args) override;
};

class DisableWifi: public Command {
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif // COMMANDS_WIFI_H