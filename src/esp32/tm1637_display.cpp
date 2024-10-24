#include <ctime>
#include "tm1637_display.h"
#include "../tm1637/tm1637.h"

namespace ds::esp32
{
    TM1637Display::TM1637Display(gpio_num_t clk, gpio_num_t dta)
    {
        _lcd = tm1637_init(clk, dta);
    }

    void TM1637Display::set_number(uint16_t number)
    {
        tm1637_set_number_lead_dot(_lcd, number, true, 4);
    }

    void TM1637Display::set_beer(uint16_t day, uint16_t beer)
    {
        tm1637_set_segment_number(_lcd, 0, day / 10, false);
        tm1637_set_segment_number(_lcd, 1, day % 10, true);
        if (beer == 0)
        {
            set_digit(2, 17);
            set_digit(3, 17);
        } else {
            // We display the beer in hexadecimal
            tm1637_set_segment_number(_lcd, 2, (beer & 0xf0) >> 4, false);
            tm1637_set_segment_number(_lcd, 3, beer & 0x0f, false);
        }
    }

    void TM1637Display::set_brightness(uint8_t brightness)
    {
        tm1637_set_brightness(_lcd, brightness);
    }

    void TM1637Display::set_digit(uint16_t digit, uint16_t number) const
    {
        tm1637_set_segment_number(_lcd, digit, number, false);
    }

    void TM1637Display::set_all_dashes() const
    {
        for (uint8_t index = 0; index < 4; index++)
            set_digit(index, 16);
    }

    void TM1637Display::set_text_boot() const
    {
        tm1637_set_segment_raw(_lcd, 0, 124); // b
        tm1637_set_segment_raw(_lcd, 1, 92); // o
        tm1637_set_segment_raw(_lcd, 2, 92); // o
        tm1637_set_segment_raw(_lcd, 3, 120); // t
    }

    void TM1637Display::set_text_help() const
    {
        tm1637_set_segment_raw(_lcd, 0, 118); // H
        tm1637_set_segment_raw(_lcd, 1, 121); // E
        tm1637_set_segment_raw(_lcd, 2, 56); // L
        tm1637_set_segment_raw(_lcd, 3, 115); // P
    }

    void TM1637Display::show_time() const
    {
        time_t now;
        tm timeinfo;

        time(&now);

        localtime_r(&now, &timeinfo);
        tm1637_set_number_lead_dot(
            _lcd,
            (timeinfo.tm_hour * 100) + timeinfo.tm_min,
            true,
            4);
    }
}