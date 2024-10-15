#include "tm1637_display.h"
namespace ds::esp32
{
    TM1637Display::TM1637Display(gpio_num_t clk, gpio_num_t dta)
    {
        _lcd = tm1637_init(clk, dta);
    }

    void TM1637Display::set_number(uint16_t number)
    {
        tm1637_set_number(_lcd, number);
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
}