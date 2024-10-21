#include <esp_wifi.h>
#include <esp_netif.h>
#include <lwip/inet.h>
#include "show_wifi.h"

bool ShowWifi::execute(std::map<std::string, std::string> args)
{
    // Get information about the connected access point
    wifi_ap_record_t ap_info;
    esp_err_t err = esp_wifi_sta_get_ap_info(&ap_info);
    if (err != ESP_OK) {
        _factory->get_output_handler()->println("Not connected to WiFi");
        return false;
    }

    // Get IP information for the STA interface
    tcpip_adapter_ip_info_t ip_info;
    tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip_info);

    // Get the MAC address
    uint8_t mac[6];
    esp_wifi_get_mac(WIFI_IF_STA, mac);
    char mac_str[18];
    snprintf(mac_str, sizeof(mac_str), "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);


    // Get the authentication mode
    std::string auth_mode;
    switch (ap_info.authmode)
    {
        case WIFI_AUTH_OPEN:
            auth_mode = "Open";
            break;
        case WIFI_AUTH_WEP:
            auth_mode = "WEP";
            break;
        case WIFI_AUTH_WPA_PSK:
            auth_mode = "WPA PSK";
            break;
        case WIFI_AUTH_WPA2_PSK:
            auth_mode = "WPA2 PSK";
            break;
        case WIFI_AUTH_WPA_WPA2_PSK:
            auth_mode = "WPA/WPA2 PSK";
            break;
        case WIFI_AUTH_WPA2_ENTERPRISE:
            auth_mode = "WPA2 Enterprise";
            break;
        case WIFI_AUTH_WPA3_PSK:
            auth_mode = "WPA3 PSK";
            break;
        case WIFI_AUTH_WPA2_WPA3_PSK:
            auth_mode = "WPA2/WPA3 PSK";
            break;
        case WIFI_AUTH_WAPI_PSK:
            auth_mode = "WAPI PSK";
            break;
        default:
            auth_mode = "Unknown";
            break;
    }

    _factory->get_output_handler()->println("\r\nWifi information\r\n");
    _factory->get_output_handler()->println(" SSID:            " + std::string(reinterpret_cast<char*>(ap_info.ssid)));
    _factory->get_output_handler()->println(" Channel:         " + std::to_string(ap_info.primary));
    _factory->get_output_handler()->println(" Strength:        " + std::to_string(ap_info.rssi) + " dBm");
    _factory->get_output_handler()->println(" Auth mode:       " + auth_mode);

    _factory->get_output_handler()->println("\r\nEthernet information\r\n");
    _factory->get_output_handler()->println(" MAC address:     " + std::string(mac_str));

    // Print IP address, subnet mask, and default gateway
    _factory->get_output_handler()->println("\r\nIP information\r\n");
    _factory->get_output_handler()->println(" IP Address:      " + std::string(ip4addr_ntoa(&ip_info.ip)));
    _factory->get_output_handler()->println(" Subnet Mask:     " + std::string(ip4addr_ntoa(&ip_info.netmask)));
    _factory->get_output_handler()->println(" Default Gateway: " + std::string(ip4addr_ntoa(&ip_info.gw)));
    _factory->get_output_handler()->println("");
  
    return false;
}