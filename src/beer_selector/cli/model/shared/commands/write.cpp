#include <sstream>
#include <iomanip>

#include "write.h"

void Write::_save_configuration()
{
    _factory->get_output_handler()->print("Saving configuration... ");
    _factory->get_configuration_manager()->save_configuration();
    _factory->get_output_handler()->println("DONE");
}

void Write::_erase_configuration()
{
    _factory->get_output_handler()->print("Erasing all saved configuration... ");
    _factory->get_configuration_manager()->erase_all();
    _factory->get_output_handler()->println("DONE");
}

bool Write::execute(std::map<std::string, std::string> args)
{
    if (args["erase"] == "erase")
        _erase_configuration();
    else
        _save_configuration();
    return true;
}