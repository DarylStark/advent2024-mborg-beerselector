#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "serial_license_retriever.h"
#include "license/license_manager.h"
#include "logging.h"

constexpr size_t BUFFER_SIZE = 16;

SerialLicenseRetriever::SerialLicenseRetriever(std::shared_ptr<ds::esp32::UART> uart, ds::PlatformObjectFactory *factory)
    : _uart(uart), _factory(factory), _task_handle(nullptr), _stopping(false)
{
}

void SerialLicenseRetriever::_service(void* args)
{
    SerialLicenseRetriever* slr = static_cast<SerialLicenseRetriever*>(args);
    std::shared_ptr<LicenseManager> lm = LicenseManager::get_instance();
    auto& _uart = *slr->_uart;

    log(INFO, "External Licensing Service is started");

    while (true)
    {
        char buffer[BUFFER_SIZE];
        uint16_t index = 0;
        _uart.flush();

        while(true)
        {
            char input[BUFFER_SIZE];
            int len = _uart.get_bytes(input, 1);
            if (slr->_stopping)
                break;
            
            if (len > 0)
            {
                if (input[0] == '\n' || input[0] == '\r' || index == (BUFFER_SIZE - 1))
                {
                    buffer[index] = '\0';
                    index = 0;
                    break;
                }
                else if (input[0] > 31 && input[0] < 127) {
                    buffer[index] = input[0];
                    index++;
                }
            }
        }

        if (slr->_stopping)
        {
            slr->_task_handle = nullptr;
            vTaskDelete(NULL);
        }

        std::string code(buffer);
        slr->_factory->get_os()->sleep_miliseconds(10);
        lm->install_license(code);
    }
}

void SerialLicenseRetriever::start()
{
    if (_task_handle != nullptr)
        return;

    _stopping = false;

    // Start the FreeRTOS task
    xTaskCreatePinnedToCore(
        SerialLicenseRetriever::_service,
        "license_rx",
        1024,
        this,
        1,
        &_task_handle,
        0);
}

void SerialLicenseRetriever::stop()
{
    if (_task_handle == nullptr)
        return;
    log(INFO, "Stopping External Licensing Service");
    _stopping = true;
}

