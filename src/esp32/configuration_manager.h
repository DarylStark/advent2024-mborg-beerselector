#ifndef ESP32_CONFIGURATION_LOADER_H
#define ESP32_CONFIGURATION_LOADER_H

#include "../ds/configuration_manager.h"

namespace ds::esp32
{
    class ESP32ConfigurationManager : public ds::ConfigurationManager
    {
    public:
        void load_configuration() override;
    };
}  // namespace ds::esp32

#endif /* ESP32_CONFIGURATION_LOADER_H */