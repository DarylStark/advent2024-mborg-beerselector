#ifndef ESP32_OBJECT_FACTORY_H
#define ESP32_OBJECT_FACTORY_H

#include <memory>

#include "../ds/platform_object_factory.h"
#include "configuration_manager.h" // For NVS
#include "uart.h"

#include "driver/gpio.h"

namespace ds::esp32
{
    class ESP32ObjectFactory : public ds::PlatformObjectFactory
    {
    private:
        std::shared_ptr<ds::esp32::UART> _uart;
        std::shared_ptr<ds::esp32::NVS> _nvs;
        gpio_num_t _display_clk;
        gpio_num_t _display_dta;

    protected:
        std::shared_ptr<ds::OutputHandler> _get_output_handler();
        std::shared_ptr<ds::InputHandler> _get_input_handler();
        std::shared_ptr<ds::OS> _get_os();
        std::shared_ptr<ds::ConfigurationManager> _get_configuration_manager();
        std::shared_ptr<ds::Display> _get_display();
    public:
        ESP32ObjectFactory(
            std::shared_ptr<ds::esp32::UART> uart,
            std::shared_ptr<ds::esp32::NVS> nvs,
            gpio_num_t display_clk,
            gpio_num_t display_dta);
    };
}  // namespace ds::esp32

#endif /* ESP32_OBJECT_FACTORY_H */