#include <sstream>
#include <iomanip>

#include "chip_info.h"
#include "esp_system.h"

constexpr uint32_t COMMAND_COLUMN_LENGTH_FIELD = 32;
constexpr uint32_t COMMAND_COLUMN_LENGTH_INFO = 16;

bool ChipInfo::execute(std::map<std::string, std::string> args)
{
        // Get chip information
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    // Create output stream
    std::stringstream ss;

    ss << "\r\nChip information:\r\n";
    ss << std::string(COMMAND_COLUMN_LENGTH_FIELD + COMMAND_COLUMN_LENGTH_INFO + 1, '-') << "\r\n";

    std::string model = "Unknown model";
    switch (chip_info.model)
    {
    case CHIP_ESP32:
        model = "ESP32";
        break;
    case CHIP_ESP32S2:
        model = "ESP32-S2";
        break;
    case CHIP_ESP32S3:
        model = "ESP32-S3";
        break;
    case CHIP_ESP32C3:
        model = "ESP32-C3";
        break;
    }


    // Add chip information to the output stream
    ss << "Model:    " << model << "\r\n";
    ss << "Cores:    " << static_cast<uint32_t>(chip_info.cores) << "\r\n";
    ss << "Revision: " << static_cast<uint32_t>(chip_info.revision) << "\r\n";
    ss << "Features: "
       << (chip_info.features & CHIP_FEATURE_WIFI_BGN ? "'WiFi BGN' " : "")
       << (chip_info.features & CHIP_FEATURE_BLE ? "'BLE' " : "")
       << (chip_info.features & CHIP_FEATURE_BT ? "'BT' " : "")
       << (chip_info.features & CHIP_FEATURE_EMB_FLASH ? "'Embedded Flash'" : "'External Flash'")
         << "\r\n";

    // Print the output
    _factory->get_output_handler()->println(ss.str());

    return true;
}