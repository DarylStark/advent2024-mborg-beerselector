#ifndef __PC_OUTPUT_HANDLER_H__
#define __PC_OUTPUT_HANDLER_H__

#include <string>

#include "../ds/output_handler.h"

namespace ds::esp32
{
    class PCOutputHandler : public ds::OutputHandler
    {
    public:
        void print(const std::string text) const;
        void println(const std::string text = "") const;
        void flush() const;
    };
}  // namespace ds::esp32

#endif /* __PC_OUTPUT_HANDLER_H__ */