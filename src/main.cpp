#include <memory>

#include "beer_selector/beer_selector.h"
#include "esp32/object_factory.h"
#include "esp32/uart.h"
#include "esp32/configuration_manager.h"

// Dependencies
std::shared_ptr<ds::esp32::UART> uart = std::make_shared<ds::esp32::UART>();
std::shared_ptr<ds::esp32::NVS> nvs = std::make_shared<ds::esp32::NVS>("ac24");

// Object factory
std::shared_ptr<ds::PlatformObjectFactory> object_factory = std::make_shared<ds::esp32::ESP32ObjectFactory>(uart, nvs);

// App object. Dependencies are injected.
std::shared_ptr<BeerSelector> beer_selector = std::make_shared<BeerSelector>(object_factory);

extern "C"
void app_main(void)
{
    // TODO: Make this less `arduino` and more ESP32 / C++
    beer_selector->setup();
    while (true)
        beer_selector->loop();
}