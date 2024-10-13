#include "object_factory.h"

#include "configuration_manager.h"
#include "input_handler.h"
#include "os.h"
#include "output_handler.h"
#include "tm1637_display.h"

namespace ds::esp32
{
    ESP32ObjectFactory::ESP32ObjectFactory(
        std::shared_ptr<ds::esp32::UART> uart,
        std::shared_ptr<ds::esp32::NVS> nvs,
        gpio_num_t display_clk,
        gpio_num_t display_dta)
        : _uart(uart), _nvs(nvs), _display_clk(display_clk), _display_dta(display_dta)
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

    std::shared_ptr<ds::Display> ESP32ObjectFactory::_get_display()
    {
        return std::make_shared<ds::esp32::TM1637Display>(_display_clk, _display_dta);
    }
}  // namespace ds::esp32