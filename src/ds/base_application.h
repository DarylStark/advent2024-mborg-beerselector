#ifndef BASE_APPLICATION_H
#define BASE_APPLICATION_H

#include <memory>

#include "application.h"
#include "configuration_loader.h"
#include "platform_object_factory.h"
#include "state.h"

namespace ds
{
    class BaseApplication : public Application
    {
    protected:
        // Object factory (platform specific)
        std::shared_ptr<PlatformObjectFactory> _factory;
        std::shared_ptr<ConfigurationLoader> _config_loader;

        // State
        std::shared_ptr<ds::State> _state;

    public:
        BaseApplication(std::shared_ptr<PlatformObjectFactory> factory);

        // State methods
        void set_state(std::shared_ptr<ds::State> state);
    };
}  // namespace ds

#endif /* BASE_APPLICATION_H */