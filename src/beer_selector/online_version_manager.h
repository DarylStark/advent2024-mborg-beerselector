#ifndef ONLINE_VERSION_MANAGER_H
#define ONLINE_VERSION_MANAGER_H

#include <map>
#include <string>
#include <exception>
#include <esp_http_client.h>

class OnlineVersionManagerException : public std::exception
{
private:
    std::string _error;
public:
    OnlineVersionManagerException(const std::string &error);
    const char *what() const noexcept override;
};

struct Version
{
    std::string version;
    std::string name;
    std::string filename;
    std::string date;
    bool latest;

    std::string download_url() const;
};

class OnlineVersionManager
{
private:
    std::map<std::string, Version> _versions;
    Version _latest;
    std::string _error;
    bool _up_to_date;

    static esp_err_t _http_event_handler(esp_http_client_event_t *evt);
    static esp_err_t _http_event_handler_ota(esp_http_client_event_t *evt);
    std::string _json_content;

public:
    OnlineVersionManager();
    void update_versions(bool force = false);
    const std::map<std::string, Version> &get_versions();
    const Version& get_latest();
    void do_ota(std::string url);
};

#endif /* ONLINE_VERSION_MANAGER_H */