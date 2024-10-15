#include "show_log_buffer.h"
#include "../../../../logging.h"

bool ShowLogBuffer::execute(std::map<std::string, std::string> args)
{
    const auto& buffer = log_buffer.get_buffer();
    for (const auto& line : buffer)
    {
        _factory->get_output_handler()->println(line);
    }
    return false;
}