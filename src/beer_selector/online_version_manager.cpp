#include <iostream>
#include <json.h>
#include <esp_http_client.h>
#include <esp_https_ota.h>

#include "online_version_manager.h"

OnlineVersionManagerException::OnlineVersionManagerException(const std::string &error)
    : _error(error)
{}

const char* OnlineVersionManagerException::what() const noexcept
{
    std::string error = "Error while retrieving data. Error: " + _error;
    return error.c_str();
}

OnlineVersionManager::OnlineVersionManager()
    : _error(""), _up_to_date(false)
{
}

std::string Version::download_url() const
{
    return std::string(CONFIG_BS_OTA_BASE) + filename;
}

esp_err_t OnlineVersionManager::_http_event_handler(esp_http_client_event_t *evt) {
    OnlineVersionManager *ovm = static_cast<OnlineVersionManager *>(evt->user_data);
    switch (evt->event_id) {
        case HTTP_EVENT_ERROR:
            ovm->_error = "HTTP_EVENT_ERROR";
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ovm->_error = "HTTP_EVENT_ON_CONNECTED";
            break;
        case HTTP_EVENT_HEADER_SENT:
            ovm->_error = "HTTP_EVENT_HEADER_SENT";
            break;
        case HTTP_EVENT_ON_HEADER:
            ovm->_error = "HTTP_EVENT_ON_HEADER";
            break;
        case HTTP_EVENT_ON_FINISH:
            ovm->_error = "HTTP_EVENT_ON_FINISH";
            break;
        case HTTP_EVENT_DISCONNECTED:
            ovm->_error = "HTTP_EVENT_DISCONNECTED";
            break;
        case HTTP_EVENT_ON_DATA:
            if (evt->data_len > 0) {
                ovm->_json_content.append(static_cast<const char *>(evt->data), evt->data_len);
            }
            break;
    }
    return ESP_OK;
}

esp_err_t OnlineVersionManager::_http_event_handler_ota(esp_http_client_event_t *evt) {
    OnlineVersionManager *ovm = static_cast<OnlineVersionManager *>(evt->user_data);

    switch (evt->event_id) {
        case HTTP_EVENT_ERROR:
            ovm->_error = "HTTP_EVENT_ERROR";
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ovm->_error = "HTTP_EVENT_ON_CONNECTED";
            break;
        case HTTP_EVENT_HEADER_SENT:
            ovm->_error = "HTTP_EVENT_HEADER_SENT";
            break;
        case HTTP_EVENT_ON_HEADER:
            ovm->_error = "HTTP_EVENT_ON_HEADER";
            break;
        case HTTP_EVENT_DISCONNECTED:
            ovm->_error = "HTTP_EVENT_DISCONNECTED";
            break;
        default:
            ovm->_error = "Unknown error";
            break;
        }
    return ESP_OK;
}

void OnlineVersionManager::update_versions(bool force)
{
    using json = nlohmann::json;

    if (_up_to_date && !force)
        return;

    _json_content.clear();

    // Compile the URL
    // TODO: make this configurable
    std::string url = std::string(CONFIG_BS_OTA_BASE) + "bs_ac24.json";

    esp_http_client_config_t config = {
        .url = url.c_str(),
        .event_handler = _http_event_handler,
        .user_data = this // Pass the instance to the event handler
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK)
    {
        json j = json::parse(_json_content);

        for (auto it = j["versions"].begin(); it != j["versions"].end(); ++it) {
            std::string key = it.key();
            _versions[key] = Version{
                .version = key,
                .name = it.value()["name"],
                .filename = it.value()["filename"],
                .date = it.value()["date"],
                .latest = key == j["latest"]
            };

            if (_versions[key].latest)
                _latest = _versions[key];
        }
        _up_to_date = true;
    }
    else
    {
        throw OnlineVersionManagerException(_error);
        _up_to_date = true;
    }

    esp_http_client_cleanup(client);
}

const std::map<std::string, Version> &OnlineVersionManager::get_versions()
{
    if (!_up_to_date)
        update_versions();

    return _versions;
}

const Version &OnlineVersionManager::get_latest()
{
    if (!_up_to_date)
        update_versions();

    return _latest;
}

void OnlineVersionManager::do_ota(std::string url)
{
    esp_http_client_config_t config = {
        .url = url.c_str(),
        .event_handler = _http_event_handler_ota,
        .user_data = this // Pass the instance to the event handler
    };

    esp_err_t ret = esp_https_ota(&config);
    if (ret != ESP_OK)
        throw OnlineVersionManagerException(_error);
}
