#include "auth_enable.h"

bool AuthEnable::execute(std::map<std::string, std::string> args)
{
    // Save the credentials in the configuration
    _factory->get_configuration_manager()->set("auth.enable", args["password"]);
    return true;
}