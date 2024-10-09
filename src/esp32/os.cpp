#include "os.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <chrono>
#include <thread>

#include <esp_system.h>

namespace ds::esp32
{
    void ESP32OS::sleep_miliseconds(uint32_t miliseconds) const
    {
        vTaskDelay(pdMS_TO_TICKS(miliseconds));
    }

    void ESP32OS::restart() const
    {
        esp_restart();
    }
}  // namespace ds::esp32
