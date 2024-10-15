#include "configuration_manager.h"

namespace ds::esp32
{
    ESP32ConfigurationManager::ESP32ConfigurationManager(std::shared_ptr<NVS> nvs)
        : _nvs(nvs)
    {
        load_configuration();
    }

    std::string ESP32ConfigurationManager::_get_from_nvs(const std::string& key, const std::string& default_value)
    {
        std::string value = _nvs->get_config(key);
        if (value.length() == 0)
            return default_value;
        return value;
    }

    void ESP32ConfigurationManager::load_configuration()
    {
        // Load configuration for ESP32
        // TODO: This shouldnt be in this directory. This has to be in the
        //       directory of the application. Make something to fix this.

        // Authentication
        _configuration["auth.user"] = _get_from_nvs("auth.user", CONFIG_BS_CONFIG_AUTH_USER);
        _configuration["auth.pass"] = _get_from_nvs("auth.pass", CONFIG_BS_CONFIG_AUTH_PASS);
        _configuration["auth.enable"] = _get_from_nvs("auth.enable", CONFIG_BS_CONFIG_AUTH_ENABLE);

        // System
        _configuration["sys.hostname"] = _get_from_nvs("sys.hostname", CONFIG_BS_CONFIG_SYS_HOSTNAME);

        // Licenses
        _configuration["license.0"] = _get_from_nvs("license.0", "FACLICENSE");
        _configuration["license.1"] = _get_from_nvs("license.1", "");
        _configuration["license.2"] = _get_from_nvs("license.2", "");
        _configuration["license.3"] = _get_from_nvs("license.3", "");

        // Display configuration
        _configuration["display.time_per_beer"] = _get_from_nvs("display.time_per_beer", CONFIG_BS_CONFIG_DISPLAY_TIMEOUT);

        _nvs->close();
    }

    void ESP32ConfigurationManager::save_configuration()
    {
        // Save configuration for ESP32
        for (auto& [key, value] : _configuration)
            _nvs->save_config(key, value);
        
        _nvs->close();
    }

    const std::string ESP32ConfigurationManager::get(const std::string& key) const
    {
        // Get configuration for ESP32
        // TODO: Neat error if key not found
        return _configuration.at(key);
    }

    void ESP32ConfigurationManager::set(const std::string& key, const std::string value)
    {
        // Set configuration for ESP32
        _configuration.at(key) = value;
    }

    void ESP32ConfigurationManager::erase_all()
    {
        // Erase all configuration for ESP32
        _nvs->format();
    }
}  // namespace ds::esp32