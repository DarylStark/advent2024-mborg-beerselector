#include "wifi_manager.h"

#include <cstring>
#include <sstream>
#include "../beer_selector/logging.h"

namespace ds::esp32
{
    ESP32WifiManager::ESP32WifiManager(std::shared_ptr<ds::ConfigurationManager> configuration_manager)
        : _configuration_manager(configuration_manager), _initialized(false)
    {
    }

    void ESP32WifiManager::_wifi_event(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
    {
        if (event_base == WIFI_EVENT)
        {
            if (event_id == WIFI_EVENT_STA_START)
            {
                logging_queue.push(LoggingData(Severity::INFO, "Connecting to WiFi"));
                esp_wifi_connect();
            }
            else if (event_id == WIFI_EVENT_STA_CONNECTED)
            {
                logging_queue.push(LoggingData(Severity::INFO, "Connected to WiFi"));
            }
            else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
            {
                logging_queue.push(LoggingData(Severity::INFO, "Disconnected from Wifi"));
            }
        }

        if (event_base == IP_EVENT)
        {
            if (event_id == IP_EVENT_STA_GOT_IP)
            {
                ip_event_got_ip_t *event = reinterpret_cast<ip_event_got_ip_t*>(event_data);
                uint32_t octets[4] = {
                    (event->ip_info.ip.addr >> 0) & 0xFF,
                    (event->ip_info.ip.addr >> 8) & 0xFF,
                    (event->ip_info.ip.addr >> 16) & 0xFF,
                    (event->ip_info.ip.addr >> 24) & 0xFF};
                std::stringstream ss;
                ss << "Got IP address: " << octets[0] << "." << octets[1] << "." << octets[2] << "." << octets[3];
                logging_queue.push(LoggingData(Severity::INFO, ss.str()));
            }
        }
    }

    void ESP32WifiManager::_initialize()
    {
        // Initialize the WiFi manager
        if (!_initialized)
        {
            if (_configuration_manager->get("wifi.ssid") == "")
                return;

            // Initialize network
            esp_netif_init();
            esp_event_loop_create_default();
            esp_netif_create_default_wifi_sta();

            // Configure Wifi
            wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
            esp_wifi_init(&cfg);
            esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, ESP32WifiManager::_wifi_event, this);
            esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, ESP32WifiManager::_wifi_event, this);

            // Configure the SSID and password
            std::string ssid = _configuration_manager->get("wifi.ssid");
            std::string password = _configuration_manager->get("wifi.password");
            wifi_config_t wifi_config;
            memset(&wifi_config, 0, sizeof(wifi_config));
            memcpy(wifi_config.sta.ssid, ssid.c_str(), ssid.size());
            memcpy(wifi_config.sta.password, password.c_str(), password.size());
            wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;

            // Set hostname
            tcpip_adapter_set_hostname(TCPIP_ADAPTER_IF_STA, _configuration_manager->get("sys.hostname").c_str());

            // Connect to the network
            esp_wifi_set_mode(WIFI_MODE_STA);
            esp_wifi_set_config(WIFI_IF_STA, &wifi_config);

            _initialized = true;
        }
    }
    
    void ESP32WifiManager::start()
    {
        _initialize();

        // Start the Wifi task
        esp_wifi_start();
    }

    void ESP32WifiManager::stop()
    {
        esp_wifi_stop();
        _initialized = false;
    }
}