#include "reload_command.h"

#include <iostream>

bool ReloadCommand::execute(std::map<std::string, std::string> args)
{
    std::cout << "RELOADING" << std::endl;
    _factory->get_os()->restart();
    return false;
}
