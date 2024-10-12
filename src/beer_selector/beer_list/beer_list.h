#ifndef BEERLIST_H
#define BEERLIST_H

#include <array>

class BeerList
{
private:
    static std::array<uint16_t, 31> _beer_list;

public:
    uint16_t get_license_number_for_day(uint32_t day) const;
    bool is_license_valid_for_day(uint16_t day) const;
    uint16_t get_beer_for_day(uint32_t day) const;
};

#endif // BEERLIST_H