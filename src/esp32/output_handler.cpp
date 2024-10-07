#include "output_handler.h"

#include <iostream>

namespace ds::esp32
{
    void PCOutputHandler::print(const std::string text) const
    {
        std::cout << text;
        flush();
    }

    void PCOutputHandler::println(const std::string text) const
    {
        std::cout << text << "\n";
        flush();
    }

    void PCOutputHandler::flush() const
    {
        std::flush(std::cout);
    }
}  // namespace ds::esp32