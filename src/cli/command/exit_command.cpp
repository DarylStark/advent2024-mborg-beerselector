#include "../../beer_selector/globals.h"
#include "exit_command.h"

bool ExitCommand::execute(std::map<std::string, std::string> args)
{
    next_parser = nullptr;
    return false;
}