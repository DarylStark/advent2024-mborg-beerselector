#include "../license/license_manager.h"
#include "beer_list.h"


std::array<uint16_t, 31> BeerList::_beer_list = {
    7, 8, 6, 141, 190, 192, 188, 180, 170, 160, 155, 238, 255, 202, 171, 169,
    187, 204, 221, 175, 191, 207, 223, 239, 240, 173, 189, 205, 237, 253, 222
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
