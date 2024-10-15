#include "beer_list.h"
#include "../../../../logging.h"

bool BeerListSetTimeOut::execute(std::map<std::string, std::string> args)
{
    // Convert the string to an integer
    uint32_t timeout = std::stoi(args["timeout"]);

    if (timeout > 180)
    {
        _factory->get_output_handler()->println("Timeout must be below 180 seconds");
        return false;
    }

    _factory->get_configuration_manager()->set("dp.t_beer", args.at("timeout"));
    return false;
}