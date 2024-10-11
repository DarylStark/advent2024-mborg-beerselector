#include "../../../../../license/license_manager.h"
#include "license_manual.h"

bool LicenseManual::execute(std::map<std::string, std::string> args)
{
    const auto license_manager = LicenseManager::get_instance();
    if (!license_manager->install_license(args["license_key"]))
    {
        _factory->get_output_handler()->println("License key is not installed. Verify if the given key is correct");
        return false;
    }
    
    _factory->get_output_handler()->println("License is installed");
    return false;
}