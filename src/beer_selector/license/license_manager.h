#ifndef LICENSE_MANAGER_H
#define LICENSE_MANAGER_H

#include <memory>
#include "./validator.h"
#include "../../ds/configuration_manager.h"

class LicenseManager
{
    // This class is a singleton

private:
    static std::shared_ptr<LicenseManager> _instance;
    static std::shared_ptr<ds::ConfigurationManager> _cfg_manager;

    LicenseManager();
    bool _licenses[4];
    std::shared_ptr<LicenseValidator> _validators[4];

public:
    // Delete constructors
    LicenseManager(const LicenseManager&) = delete;
    LicenseManager& operator=(const LicenseManager&) = delete;
    LicenseManager(LicenseManager&&) = delete;

    // Methods for the singleton
    static std::shared_ptr<LicenseManager> get_instance();
    static void set_configuration_manager(std::shared_ptr<ds::ConfigurationManager> cfg_manager);

    // Validators
    void set_validator(uint16_t license_number, std::shared_ptr<LicenseValidator> validator);

    // Update
    void update();

    // Check functions
    bool is_license_valid(uint16_t license_number) const;
    const std::string get_license_code(uint16_t license_number) const;

    // Install license
    bool install_license(const std::string& license_key);
};

#endif /* LICENSE_MANAGER_H */