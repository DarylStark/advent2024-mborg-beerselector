#include "input_handler.h"

#include <memory>
#include <fstream>

#include "uart.h"
#include "esp32_lineinput.h"

namespace ds::esp32
{
    ESP32InputHandler::ESP32InputHandler(std::shared_ptr<ds::esp32::UART> uart)
        : _uart(uart)
    {
    }

    std::string ESP32InputHandler::get_string(
        const std::string prompt,
        std::string default_value
        ) const
    {
        ESP32_LineInput input(*_uart);
        _uart->write_bytes(prompt.c_str(), prompt.length());
        input.set_string(default_value);
        return input.get(true);
    }

    std::string ESP32InputHandler::get_password(
        const std::string prompt,
        std::string default_value
        ) const
    {
        ESP32_LineInput input(*_uart, '*');
        _uart->write_bytes(prompt.c_str(), prompt.length());
        input.set_string(default_value);
        return input.get(true);
    }

    int ESP32InputHandler::get_key_press() const
    {
        char input[4];
        int len = _uart->get_bytes(input, 1, 10);
        return len == 1 ? input[0] : -1;
    }
}  // namespace ds::esp32