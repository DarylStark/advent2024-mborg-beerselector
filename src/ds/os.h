#ifndef OS_H
#define OS_H

#include <string>

namespace ds
{
    class OS
    {
        // Interface for OS specific operations
    public:
        virtual void sleep_miliseconds(uint32_t miliseconds) const = 0;
        virtual void restart() const = 0;
    };
}  // namespace ds

#endif /* OS_H */
