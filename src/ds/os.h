#ifndef __OS_H__
#define __OS_H__

#include <string>

namespace ds
{
    class OS
    {
        // Interface for OS specific operations
    public:
        virtual void sleep_miliseconds(uint32_t miliseconds) = 0;
    };
}  // namespace ds

#endif /* __OS_H__ */