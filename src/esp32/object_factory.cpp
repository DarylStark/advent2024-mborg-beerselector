#include "object_factory.h"

#include "configuration_manager.h"
#include "input_handler.h"
#include "os.h"
#include "output_handler.h"

namespace ds::esp32
{
    ESP32ObjectFactory::ESP32ObjectFactory(std::shared_ptr<ds::esp32::UART> uart, std::shared_ptr<ds::esp32::NVS> nvs)
        : _uart(uart), _nvs(nvs)
    {
    }

    std::shared_ptr<ds::OutputHandler> ESP32ObjectFactory::_get_output_handler()
    {
        return std::make_shared<ESP32OutputHandler>(_uart);
    }

    std::shared_ptr<ds::InputHandler> ESP32ObjectFactory::_get_input_handler()
    {
        return std::make_shared<ESP32InputHandler>(_uart);
    }

    std::shared_ptr<ds::OS> ESP32ObjectFactory::_get_os()
    {
        return std::make_shared<ds::esp32::ESP32OS>();
    }

    std::shared_ptr<ds::ConfigurationManager>
    ESP32ObjectFactory::_get_configuration_manager()
    {
        return std::make_shared<ds::esp32::ESP32ConfigurationManager>(_nvs);
    }
}  // namespace ds::esp32