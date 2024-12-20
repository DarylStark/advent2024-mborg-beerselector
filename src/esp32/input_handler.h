#ifndef ESP32_INPUT_HANDLER_H
#define ESP32_INPUT_HANDLER_H

#include <memory>
#include <limits>
#include <string>

#include "../ds/input_handler.h"
#include "uart.h"


namespace ds::esp32
{
    class ESP32InputHandler : public ds::InputHandler
    {
    private:
        std::shared_ptr<ds::esp32::UART> _uart;

    public:
        ESP32InputHandler(std::shared_ptr<ds::esp32::UART> uart);
        std::string get_string(const std::string prompt, std::string default_value) const;
        std::string get_password(const std::string prompt, std::string default_value) const;
        int get_key_press() const;
    };
}  // namespace ds::esp32

#endif /* ESP32_INPUT_HANDLER_H */