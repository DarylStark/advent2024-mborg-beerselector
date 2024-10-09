#include "nvs.h"

namespace ds::esp32
{
    NVS::NVS(const std::string namespace_name)
        : _handle(0), _namespace_name(namespace_name)
    {   
    }

    NVS::~NVS() {
        close();
    }

    bool NVS::is_open() const {
        return _handle != 0;
    }

    void NVS::open() {
        if (is_open())
            return;

        esp_err_t err = nvs_flash_init();
        if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
            nvs_flash_erase();
            nvs_flash_init();
        }
        nvs_open(_namespace_name.c_str(), NVS_READWRITE, &_handle);
    }

    void NVS::close() {
        if (!is_open())
            return;
        nvs_close(_handle);
        _handle = 0;
    }

    void NVS::format() {
        open();
        nvs_erase_all(_handle);
        nvs_commit(_handle);
        close();
    }

    esp_err_t NVS::save_config(const std::string key, const std::string& value) {
        open();
        esp_err_t err = nvs_set_str(_handle, key.c_str(), value.c_str());
        if (err == ESP_OK)
            err = nvs_commit(_handle);
        else
            nvs_commit(_handle);
        return err;
    }

    std::string NVS::get_config(const std::string key) {
        open();
        size_t required_size;
        esp_err_t err = nvs_get_str(_handle, key.c_str(), NULL, &required_size);
        if (err == ESP_OK) {
            char* buffer = new char[required_size];
            err = nvs_get_str(_handle, key.c_str(), buffer, &required_size);
            if (err == ESP_OK) {
                std::string value = std::string(buffer);
                close();
                return value;
            }
            delete[] buffer;
        }
        return "";
    }
}