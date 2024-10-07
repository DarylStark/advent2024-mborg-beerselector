#include "input_handler.h"

#include <memory>
#include <fstream>
#include <iostream>

#include "uart.h"
#include "esp32_lineinput.h"

namespace ds::esp32
{
    PCInputHandler::PCInputHandler(std::shared_ptr<ds::esp32::UART> uart)
        : _uart(uart)
    {
    }

    std::string PCInputHandler::get_string(
        const std::string prompt,
        std::string default_value
        ) const
    {
        ESP32_LineInput input(*_uart);
        _uart->write_bytes(prompt.c_str(), prompt.length());
        input.set_string(default_value);
        return input.get(true);
    }

    bool PCInputHandler::is_mode_pressed() const
    {
        // TODO: Implement
        return true;
    }
}  // namespace ds::esp32