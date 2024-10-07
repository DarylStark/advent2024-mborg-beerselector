#ifndef __PC_OUTPUT_HANDLER_H__
#define __PC_OUTPUT_HANDLER_H__

#include <memory>
#include <string>

#include "uart.h"
#include "../ds/output_handler.h"

namespace ds::esp32
{
    class ESP32OutputHandler : public ds::OutputHandler
    {
    private:
        std::shared_ptr<ds::esp32::UART> _uart;

    public:
        ESP32OutputHandler(std::shared_ptr<ds::esp32::UART> uart);
        void print(const std::string text) const;
        void println(const std::string text = "") const;
        void flush() const;
    };
}  // namespace ds::esp32

#endif /* __PC_OUTPUT_HANDLER_H__ */