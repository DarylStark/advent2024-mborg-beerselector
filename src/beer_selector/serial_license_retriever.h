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

public:
    SerialLicenseRetriever(std::shared_ptr<ds::esp32::UART> uart, ds::PlatformObjectFactory* factory);
    void start();
    void stop();
};

#endif // SERIAL_LICENSE_RETRIEVER_H
