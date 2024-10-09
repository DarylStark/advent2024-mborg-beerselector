#include "reload_command.h"

bool ReloadCommand::execute(std::map<std::string, std::string> args)
{
    _factory->get_os()->restart();
    return false;
}
