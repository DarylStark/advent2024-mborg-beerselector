#include "os.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace ds::esp32
{
    void PCOS::sleep_miliseconds(uint32_t miliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
    }
}  // namespace ds::esp32