#include "hostname.h"
#include "../../../../logging.h"

bool Hostname::execute(std::map<std::string, std::string> args)
{
    _factory->get_configuration_manager()->set("sys.hostname", args["hostname"]);
    log(INFO, "Hostname set to: \"" + args["hostname"] + "\"");
    return false;
}