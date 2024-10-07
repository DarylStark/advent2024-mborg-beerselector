#ifndef __PC_OS_H__
#define __PC_OS_H__

#include "../ds/os.h"

namespace ds::esp32
{
    class ESP32OS : public ds::OS
    {
    public:
        void sleep_miliseconds(uint32_t miliseconds);
    };
}  // namespace ds::esp32

#endif /* __PC_OS_H__ */