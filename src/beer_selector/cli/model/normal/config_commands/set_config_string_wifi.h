#ifndef SET_CONFIG_STRING_WIFI_H
#define SET_CONFIG_STRING_WIFI_H

#include "set_config_string.h"

class SetConfigStringWifi: public SetConfigString {
public:
    SetConfigStringWifi(std::map<std::string, std::string> arg_config_keys);
    bool execute(std::map<std::string, std::string> args) override;
};

#endif // SET_CONFIG_STRING_WIFI_H