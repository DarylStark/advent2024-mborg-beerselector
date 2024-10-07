#include "output_handler.h"

namespace ds::esp32
{
    ESP32OutputHandler::ESP32OutputHandler(std::shared_ptr<ds::esp32::UART> uart)
        : _uart(uart)
    {
    }

    void ESP32OutputHandler::print(const std::string text) const
    {
        _uart->write_bytes(text.c_str(), text.length());
    }

    void ESP32OutputHandler::println(const std::string text) const
    {
        print(text);
        _uart->write_bytes("\r\n", 2);
    }

    void ESP32OutputHandler::flush() const
    {
        // Not needed for ESP32
    }
}  // namespace ds::esp32