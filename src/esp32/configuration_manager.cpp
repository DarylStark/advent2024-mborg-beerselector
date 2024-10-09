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
        _configuration["auth.user"] = _get_from_nvs("auth.user", "admin_default");
        _configuration["auth.pass"] = _get_from_nvs("auth.pass", "pass_default");
        _configuration["auth.enable"] = _get_from_nvs("auth.enable", "cisco");

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
        _configuration.clear();
        _nvs->format();
    }
}  // namespace ds::esp32