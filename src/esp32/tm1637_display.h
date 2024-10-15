#ifndef TM1637_DISPLAY_H
#define TM1637_DISPLAY_H

#include "../tm1637/tm1637.h"
#include "ds/display.h"
#include "driver/gpio.h"

namespace ds::esp32
{
    class TM1637Display : public ds::Display
    {
    private:
        tm1637_led_t* _lcd;

    public:
        TM1637Display(gpio_num_t clk, gpio_num_t dta);
        void set_number(uint16_t number) override;
        void set_brightness(uint8_t brightness) override;
        void set_digit(uint16_t digit, uint16_t number) const override;
        void set_all_dashes() const override;
        void set_text_boot() const override;
        void set_text_help() const override;
    };
}

#endif // TM1637_DISPLAY_H