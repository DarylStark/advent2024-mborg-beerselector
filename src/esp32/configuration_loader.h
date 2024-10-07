#ifndef __PC_CONFIGURATION_LOADER_H__
#define __PC_CONFIGURATION_LOADER_H__

#include "../ds/configuration_loader.h"

namespace ds::esp32
{
    class PCConfigurationLoader : public ds::ConfigurationLoader
    {
    public:
        void load_configuration() override;
    };
}  // namespace ds::esp32

#endif /* __PC_CONFIGURATION_LOADER_H__ */