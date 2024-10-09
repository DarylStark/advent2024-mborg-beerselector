#ifndef ESP32_CONFIGURATION_LOADER_H
#define ESP32_CONFIGURATION_LOADER_H

#include <map>
#include <memory>
#include "../ds/configuration_manager.h"

// TODO: Move to own file

#include <nvs_flash.h>
#include <nvs.h>

namespace ds::esp32
{
    class NVS {
    public:
        NVS(const std::string namespace_name);
        ~NVS();

        // NVS management
        bool is_open() const;
        void open();
        void close();
        void format();

        // Configuration
        esp_err_t save_config(const std::string key, const std::string& value);
        std::string get_config(const std::string);

    private:
        nvs_handle_t _handle;
        std::string _namespace_name;
    };
}

// - END TODO

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
    };
}  // namespace ds::esp32

#endif /* ESP32_CONFIGURATION_LOADER_H */