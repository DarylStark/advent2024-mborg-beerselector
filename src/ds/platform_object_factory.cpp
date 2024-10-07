#include "platform_object_factory.h"

namespace ds
{
    std::shared_ptr<OutputHandler> PlatformObjectFactory::get_output_handler()
    {
        if (!_output_handler) _output_handler = _get_output_handler();
        return _output_handler;
    }

    std::shared_ptr<InputHandler> PlatformObjectFactory::get_input_handler()
    {
        if (!_input_handler) _input_handler = _get_input_handler();
        return _input_handler;
    }

    std::shared_ptr<OS> PlatformObjectFactory::get_os()
    {
        if (!_os) _os = _get_os();
        return _os;
    }

    std::shared_ptr<ConfigurationLoader>
    PlatformObjectFactory::get_configuration_loader()
    {
        if (!_configuration_loader)
            _configuration_loader = _get_configuration_loader();
        return _configuration_loader;
    }
}  // namespace ds