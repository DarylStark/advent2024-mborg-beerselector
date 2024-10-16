#include <memory>

#include "beer_selector/beer_selector.h"
#include "esp32/object_factory.h"
#include "esp32/uart.h"
#include "esp32/configuration_manager.h"
#include "esp32/nvs.h"

#include <iostream>

// Dependencies
std::shared_ptr<ds::esp32::UART> uart = std::make_shared<ds::esp32::UART>(UART_NUM_0, 115200);
std::shared_ptr<ds::esp32::UART> uart_license_retriever = std::make_shared<ds::esp32::UART>(UART_NUM_2, 115200, 17, 16);
std::shared_ptr<ds::esp32::NVS> nvs = std::make_shared<ds::esp32::NVS>("ac24");

// Object factory
std::shared_ptr<ds::PlatformObjectFactory> object_factory = std::make_shared<ds::esp32::ESP32ObjectFactory>(
    uart,
    nvs,
    GPIO_NUM_27,
    GPIO_NUM_26);

// App object. Dependencies are injected.
std::shared_ptr<BeerSelector> beer_selector = std::make_shared<BeerSelector>(object_factory);

extern "C"
void app_main(void)
{
    beer_selector->start();
}
