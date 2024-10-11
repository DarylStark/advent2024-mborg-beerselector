#include "../logging.h"
#include "license_manager.h"

std::shared_ptr<LicenseManager> LicenseManager::_instance = nullptr;
std::shared_ptr<ds::ConfigurationManager> LicenseManager::_cfg_manager = nullptr;

LicenseManager::LicenseManager()
    : _licenses{false, false, false, false}
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

void LicenseManager::set_validator(uint16_t license_number, std::shared_ptr<LicenseValidator> validator)
{
    if (license_number < 4)
        _validators[license_number] = validator;
}

void LicenseManager::update()
{
    // Load licenses from configuration
    for (int i = 0; i < 4; i++)
    {
        _licenses[i] = false;
        std::string license_key = _cfg_manager->get("license." + std::to_string(i));
        if (_validators[i] != nullptr && _validators[i]->validate(license_key))
            _licenses[i] = true;
    }
}

bool LicenseManager::is_license_valid(uint16_t license_number) const
{
    if (license_number < 4)
        return _licenses[license_number];

    return false;
}

const std::string LicenseManager::get_license_code(uint16_t license_number) const
{
    if (license_number < 4)
        return _cfg_manager->get("license." + std::to_string(license_number));

    return "";
}

bool LicenseManager::install_license(const std::string& license_key)
{
    // Find the next license number
    uint16_t license_number = 0;
    for (uint16_t i = 0; i < 4; i++)
    {
        if (!_licenses[i])
        {
            license_number = i;
            break;
        }
    }

    if (license_number > 3)
        return false;

    if (_validators[license_number] == nullptr)
    {
        // TODO: Throw error; no license validator set
        return false;
    }

    // Validate the license
    if (_validators[license_number]->validate(license_key))
    {
        _cfg_manager->set("license." + std::to_string(license_number), license_key);
        log(INFO, "License " + std::to_string(license_number) + " installed");
        _licenses[license_number] = true;
        return true;
    }

    return false;
}