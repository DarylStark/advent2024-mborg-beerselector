#ifndef SERIAL_LICENSE_RETRIEVER_H
#define SERIAL_LICENSE_RETRIEVER_H

#include <memory>
#include "../ds/service.h"
#include "../ds/platform_object_factory.h"
#include "../esp32/uart.h"

class SerialLicenseRetriever: public ds::Service
{
private:
    std::shared_ptr<ds::esp32::UART> _uart;
    ds::PlatformObjectFactory* _factory;
    TaskHandle_t _task_handle;
    bool _stopping;

    static void _service(void* args);

    static uint64_t _received_bytes;
    static uint64_t _received_codes;

public:
    SerialLicenseRetriever(std::shared_ptr<ds::esp32::UART> uart, ds::PlatformObjectFactory* factory);
    void start();
    void stop();
    static uint64_t get_received_bytes();
    static uint64_t get_received_codes();
};

#endif // SERIAL_LICENSE_RETRIEVER_H
