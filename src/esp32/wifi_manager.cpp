#include "esp_sntp.h"

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
                log(INFO, "Connecting to WiFi");
                esp_wifi_connect();
            }
            else if (event_id == WIFI_EVENT_STA_CONNECTED)
            {
                log(INFO, "Connected to WiFi");
                sntp_restart();
            }
            else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
            {
                log(INFO, "Disconnected from Wifi");
                sntp_stop();
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
                log(INFO, ss.str());
            }
        }
    }

    void ESP32WifiManager::_initialize()
    {
        // Initialize the WiFi manager
        if (_initialized)
            return;

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

        // Configure SNTP
        sntp_setoperatingmode(SNTP_OPMODE_POLL);
        sntp_setservername(0, "pool.ntp.org"); // TODO: Make this configurable
        sntp_init();

        _set_wifi_credentials();

        _initialized = true;
    }

    void ESP32WifiManager::_set_wifi_credentials()
    {
       
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

        esp_wifi_set_mode(WIFI_MODE_STA);
        esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    }
    
    void ESP32WifiManager::start()
    {
        if (!_initialized)
            _initialize();
        else
            _set_wifi_credentials();

        // Start the Wifi task
        esp_wifi_start();
    }

    void ESP32WifiManager::stop()
    {
        if (!_initialized)
            return;

        esp_wifi_stop();
    }
}