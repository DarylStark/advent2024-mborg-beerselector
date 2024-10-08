#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

#include <string>

namespace ds
{
    class OutputHandler
    {
        // Interface for Output Handlers.
    public:
        // Methods to print
        virtual void print(const std::string text) const = 0;
        virtual void println(const std::string text = "") const = 0;

        // Stream maintenance
        virtual void flush() const = 0;
    };
}  // namespace ds

#endif /* OUTPUT_HANDLER_H */