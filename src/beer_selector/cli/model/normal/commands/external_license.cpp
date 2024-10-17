#include "../../../../serial_license_retriever.h"
#include "external_license_info.h"

bool ExternalLicenseInfo::execute(std::map<std::string, std::string> args)
{
    _factory->get_output_handler()->println("\r\nExternal License Service Information");
    _factory->get_output_handler()->println("Received bytes: " + std::to_string(SerialLicenseRetriever::get_received_bytes()));
    _factory->get_output_handler()->println("Received codes:  " + std::to_string(SerialLicenseRetriever::get_received_codes()));
    _factory->get_output_handler()->println("\r\n");

    return false;
}

