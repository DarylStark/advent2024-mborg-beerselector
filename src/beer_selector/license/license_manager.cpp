#include "license_manager.h"

std::shared_ptr<LicenseManager> LicenseManager::_instance = nullptr;
std::shared_ptr<ds::ConfigurationManager> LicenseManager::_cfg_manager = nullptr;

LicenseManager::LicenseManager()
    : _licenses{true, false, false, false}
{}

std::shared_ptr<LicenseManager> LicenseManager::get_instance()
{
    if (_cfg_manager == nullptr)
        throw std::runtime_error("Configuration Manager not set before creating License Manager");

    if (_instance == nullptr)
        _instance = std::shared_ptr<LicenseManager>(new LicenseManager);
    return _instance;
}

void LicenseManager::set_configuration_manager(std::shared_ptr<ds::ConfigurationManager> cfg_manager)
{
    _cfg_manager = cfg_manager;
}

void LicenseManager::update()
{
    // Load licenses from configuration
    for (int i = 0; i < 4; i++)
    {
        _licenses[i] = false;
        std::string license_key = _cfg_manager->get("license." + std::to_string(i));
        if (license_key.length() > 0)
            _licenses[i] = true;
    }
}

bool LicenseManager::is_license_valid(uint16_t license_number) const
{
    if (license_number < 4)
        return _licenses[license_number];

    return false;
}

bool LicenseManager::install_license(uint16_t license_number, const std::string& license_key)
{
    if (license_number > 3)
        return false;

    if (_licenses[license_number])
        return false;

    if (license_number > 0 && license_number < 4)
    {
        // TODO: Validate the license
        _licenses[license_number] = true;
        return true;
    }

    return false;
}