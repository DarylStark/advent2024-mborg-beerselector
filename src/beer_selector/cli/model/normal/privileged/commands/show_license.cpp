#include "show_license.h"
#include "../../../../../logging.h"

#include "../../../../../license/license_manager.h"

#include "qrcode.h"

bool ShowLicense::execute(std::map<std::string, std::string> args)
{
    const auto license_manager = LicenseManager::get_instance();
    _factory->get_output_handler()->println("\r\nLicenses:");
    for (int i = 0; i < 4; i++)
    {
        _factory->get_output_handler()->print(" License " + std::to_string(i) + ": ");
        if (license_manager->is_license_valid(i))
        {
            _factory->get_output_handler()->print("Installed, license key: \"");
            _factory->get_output_handler()->println(license_manager->get_license_code(i) + "\"");
        }
        else
        {
            _factory->get_output_handler()->println("Not installed");
        }
    }
    _factory->get_output_handler()->println("");

    if (!license_manager->is_license_valid(1))
    {
        _factory->get_output_handler()->println("License 1 is not installed. You can retrieve this license for free at the following website:\r\n");
        
        esp_qrcode_config_t cfg = ESP_QRCODE_CONFIG_DEFAULT();
        esp_qrcode_generate(&cfg, CONFIG_BS_LICENSE_WEBSITE_URL);
        
        _factory->get_output_handler()->println();
        return false;
    }

    return false;
}