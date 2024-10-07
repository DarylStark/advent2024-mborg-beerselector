#ifndef __PC_OBJECT_FACTORY_H__
#define __PC_OBJECT_FACTORY_H__

#include <memory>

#include "../ds/platform_object_factory.h"
#include "uart.h"

namespace ds::esp32
{
    class ESP32ObjectFactory : public ds::PlatformObjectFactory
    {
    private:
        std::shared_ptr<ds::esp32::UART> _uart;
    protected:
        std::shared_ptr<ds::OutputHandler> _get_output_handler();
        std::shared_ptr<ds::InputHandler> _get_input_handler();
        std::shared_ptr<ds::OS> _get_os();
        std::shared_ptr<ds::ConfigurationLoader> _get_configuration_loader();
    public:
        ESP32ObjectFactory(std::shared_ptr<ds::esp32::UART> uart);
    };
}  // namespace ds::esp32

#endif /* __PC_OBJECT_FACTORY_H__ */