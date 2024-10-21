#include "../../../../logging.h"
#include "set_config_string_wifi.h"

SetConfigStringWifi::SetConfigStringWifi(std::map<std::string, std::string> arg_config_keys)
    : SetConfigString(arg_config_keys)
{}

bool SetConfigStringWifi::execute(std::map<std::string, std::string> args) {
    SetConfigString::execute(args);

    // Restart wifi
    _factory->get_wifi_manager()->stop();
    _factory->get_wifi_manager()->start();

    return false;
}
