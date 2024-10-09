#ifndef ESP32_CONFIGURATION_MANAGER_H
#define ESP32_CONFIGURATION_MANAGER_H

#include <map>
#include <memory>
#include "../ds/configuration_manager.h"
#include "nvs.h"

namespace ds::esp32
{
    class ESP32ConfigurationManager : public ds::ConfigurationManager
    {
    private:
        std::shared_ptr<NVS> _nvs;
        std::string _get_from_nvs(const std::string &key, const std::string &default_value);
        std::map<std::string, std::string> _configuration;

    public:
        ESP32ConfigurationManager(std::shared_ptr<NVS> nvs);
        void load_configuration() override;
        void save_configuration();
        const std::string get(const std::string& key) const;
        void set(const std::string& key, const std::string);
        void erase_all();
    };
}  // namespace ds::esp32

#endif /* ESP32_CONFIGURATION_MANAGER_H */