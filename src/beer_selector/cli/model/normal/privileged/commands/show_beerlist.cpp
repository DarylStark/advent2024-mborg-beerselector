#include "../../../../../beer_list/beer_list.h"
#include "show_beerlist.h"
#include "../../../../../license/license_manager.h"

#include <sstream>
#include <iomanip>

bool ShowBeerListCmd::execute(std::map<std::string, std::string> args)
{
    BeerList beer_list;

    _factory->get_output_handler()->println("\r\nBeer list for 2024");
    _factory->get_output_handler()->println("");

    // Print table headers
    std::stringstream ss;
    ss << "\r\n"
       << std::left  << std::setw(8) << "Day" << "| "
       << std::left  << std::setw(8) << "Beer" << "| "
       << std::left  << std::setw(16) << "State"
       << "\r\n";
    ss << std::string(32, '-') << "\r\n";
    _factory->get_output_handler()->print(ss.str());

    for (uint32_t day = 1; day <= 31; day++)
    {
        uint16_t beer = beer_list.get_beer_for_day(day);
        uint16_t licensed = beer_list.is_license_valid_for_day(day);

        std::stringstream beer_number;
        if (licensed)
            beer_number << "0x" << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << beer;
        else
            beer_number << "____";

        std::stringstream ss;
        ss << std::right  << std::setw(6) << (day) << "  | "
           << std::right  << std::setw(6) << beer_number.str() << "  | "
           << std::left  << std::setw(16) << (licensed ? "Licensed" : "Not licensed")
           << "\r\n";

        _factory->get_output_handler()->print(ss.str());
    }

    _factory->get_output_handler()->print("\r\n");
    return false;
}