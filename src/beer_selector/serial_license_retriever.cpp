#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "serial_license_retriever.h"
#include "license/license_manager.h"
#include "logging.h"

constexpr size_t BUFFER_SIZE = 16;

SerialLicenseRetriever::SerialLicenseRetriever(std::shared_ptr<ds::esp32::UART> uart, ds::PlatformObjectFactory* factory)
    : _uart(uart), _factory(factory)
{
}

void SerialLicenseRetriever::_service(void* args)
{
    SerialLicenseRetriever* slr = static_cast<SerialLicenseRetriever*>(args);
    std::shared_ptr<LicenseManager> lm = LicenseManager::get_instance();
    const auto& _uart = *slr->_uart;

    log(INFO, "External Licensing Service is started");

    while (true)
    {
        char buffer[BUFFER_SIZE];
        uint16_t index = 0;

        while(true)
        {
            char input[BUFFER_SIZE];
            int len = _uart.get_bytes(input, 1);
            if (len > 0)
            {
                if (input[0] == '\n' || input[0] == '\r' || input[0] == 3 || index == (BUFFER_SIZE - 1))
                {
                    buffer[index] = '\0';
                    _uart.write_bytes("!", 1);
                    index = 0;
                    break;
                }
                else if (input[0] > 31 && input[0] < 127) {
                    _uart.write_bytes(".", 1);
                    buffer[index] = input[0];
                    index++;
                }
            }
        }

        std::string code(buffer);
        lm->install_license(code);
    }
}

void SerialLicenseRetriever::start()
{
    // Start the FreeRTOS task
    xTaskCreatePinnedToCore(
        SerialLicenseRetriever::_service,
        "license_rx",
        1024,
        this,
        1,
        NULL,
        0);
}

void SerialLicenseRetriever::stop()
{
    // Stop the FreeRTOS task
}

