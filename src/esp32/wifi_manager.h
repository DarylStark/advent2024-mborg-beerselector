#ifndef ESP32_WIFI_MANAGER_H
#define ESP32_WIFI_MANAGER_H

#include <memory>
#include "esp_wifi.h"
#include "../ds/configuration_manager.h"
#include "../ds/wifi_manager.h"

namespace ds::esp32 {
    class ESP32WifiManager: public ds::WifiManager
    {
    private:
        std::shared_ptr<ds::ConfigurationManager> _configuration_manager;
        bool _initialized;

        void _initialize();
        static void _wifi_event(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

    public:
        ESP32WifiManager(std::shared_ptr<ds::ConfigurationManager> configuration_manager);
        void start() override;
        void stop() override;
    };
}

#endif /* ESP32_WIFI_MANAGER_H */