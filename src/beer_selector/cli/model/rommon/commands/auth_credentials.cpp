#include "auth_credentials.h"

bool AuthCredentials::execute(std::map<std::string, std::string> args)
{
    // Save the credentials in the configuration
    _factory->get_configuration_loader()->set("auth.user", args["username"]);
    _factory->get_configuration_loader()->set("auth.pass", args["password"]);
    return true;
}