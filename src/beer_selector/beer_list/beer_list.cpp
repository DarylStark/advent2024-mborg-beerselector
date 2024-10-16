#include "../license/license_manager.h"
#include "beer_list.h"


std::array<uint16_t, 31> BeerList::_beer_list = {
    7, 8, 6, 20, 21, 26, 18, 22, 10, 24, 14, 12, 11, 30, 27, 29, 25, 17, 3, 16, 4, 2, 13, 23, 31, 5, 1, 28, 15, 19, 9
};

uint16_t BeerList::get_license_number_for_day(uint32_t day) const
{
    uint16_t array_index = day - 1;
    uint16_t license_number = 0;

    if (array_index > 3)
        license_number = ((array_index - 4) / 9)+1;

    return license_number;
}

bool BeerList::is_license_valid_for_day(uint16_t day) const
{
    return LicenseManager::get_instance()->is_license_valid(get_license_number_for_day(day));
}

uint16_t BeerList::get_beer_for_day(uint32_t day) const
{
    if (is_license_valid_for_day(day))
        return _beer_list[day - 1];
    return 0;
}
