#ifndef __PC_INPUT_HANDLER_H__
#define __PC_INPUT_HANDLER_H__

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
        bool is_break_pressed() const;
    };
}  // namespace ds::esp32

#endif /* __PC_INPUT_HANDLER_H__ */