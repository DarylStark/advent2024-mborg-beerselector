#include "object_factory.h"

#include "configuration_loader.h"
#include "input_handler.h"
#include "os.h"
#include "output_handler.h"

namespace ds::esp32
{
    ESP32ObjectFactory::ESP32ObjectFactory(std::shared_ptr<ds::esp32::UART> uart)
        : _uart(uart)
    {
    }

    std::shared_ptr<ds::OutputHandler> ESP32ObjectFactory::_get_output_handler()
    {
        return std::make_shared<PCOutputHandler>();
    }

    std::shared_ptr<ds::InputHandler> ESP32ObjectFactory::_get_input_handler()
    {
        return std::make_shared<PCInputHandler>(_uart);
    }

    std::shared_ptr<ds::OS> ESP32ObjectFactory::_get_os()
    {
        return std::make_shared<ds::esp32::PCOS>();
    }

    std::shared_ptr<ds::ConfigurationLoader>
    ESP32ObjectFactory::_get_configuration_loader()
    {
        return std::make_shared<ds::esp32::PCConfigurationLoader>();
    }
}  // namespace ds::esp32