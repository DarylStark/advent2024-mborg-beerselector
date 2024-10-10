#include "hostname.h"

bool Hostname::execute(std::map<std::string, std::string> args)
{
    _factory->get_configuration_manager()->set("sys.hostname", args["hostname"]);
    return false;
}