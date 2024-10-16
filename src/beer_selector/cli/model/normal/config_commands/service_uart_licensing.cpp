#include "service_uart_licensing.h"
#include "../../../../logging.h"

void ServiceUARTLicensing::_enable()
{
    _factory->get_serial_license_retriever()->start();
    _factory->get_configuration_manager()->set("svc.uart_lic", "1");
}

void ServiceUARTLicensing::_disable()
{
    _factory->get_serial_license_retriever()->stop();
    _factory->get_configuration_manager()->set("svc.uart_lic", "0");
}

bool ServiceUARTLicensing::execute(std::map<std::string, std::string> args)
{
    std::string state = args["state"];
    if (state == "enable")
        _enable();
    else
        _disable();

    return false;
}