#include "auth_credentials.h"

bool AuthCredentials::execute(std::map<std::string, std::string> args)
{
    Command::_factory->get_output_handler()->println(
        "AuthCredentials command executed");
    return true;
}