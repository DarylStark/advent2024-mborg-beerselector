#ifndef ESP32_OS_H
#define ESP32_OS_H

#include "../ds/os.h"

namespace ds::esp32
{
    class ESP32OS : public ds::OS
    {
    public:
        void sleep_miliseconds(uint32_t miliseconds);
    };
}  // namespace ds::esp32

#endif /* ESP32_OS_H */