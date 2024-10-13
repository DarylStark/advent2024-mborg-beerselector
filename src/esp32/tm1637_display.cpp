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

    void TM1637Display::set_digit(uint16_t digit, uint16_t number)
    {
        tm1637_set_segment_number(_lcd, digit, number, false);
    }
}