#include "../../../../logging.h"
#include "commands_wifi.h"

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

bool DisableWifi::execute(std::map<std::string, std::string> args) {
    _factory->get_configuration_manager()->set("wifi.ssid", "");
    _factory->get_configuration_manager()->set("wifi.password", "");
    _factory->get_wifi_manager()->stop();
    return false;
}