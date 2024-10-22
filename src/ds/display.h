#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdint>

namespace ds
{
    class Display
    {
    public:
        virtual void set_number(uint16_t number) = 0;
        virtual void set_brightness(uint8_t brightness) = 0;
        virtual void set_digit(uint16_t digit, uint16_t number) const = 0;
        virtual void set_all_dashes() const = 0;
        virtual void set_text_boot() const = 0;
        virtual void set_text_help() const = 0;
        virtual void show_time() const = 0;
    };
}

#endif // DISPLAY_H