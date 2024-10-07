#include "os.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <chrono>
#include <iostream>
#include <thread>

namespace ds::esp32
{
    void ESP32OS::sleep_miliseconds(uint32_t miliseconds)
    {
        vTaskDelay(pdMS_TO_TICKS(miliseconds));
    }
}  // namespace ds::esp32