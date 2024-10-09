#ifndef NVS_H
#define NVS_H

#include <string>
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

#endif /* NVS_H */