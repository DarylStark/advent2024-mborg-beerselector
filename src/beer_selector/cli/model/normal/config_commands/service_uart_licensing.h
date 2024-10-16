#ifndef SERVICE_UART_LICENSING_H
#define SERVICE_UART_LICENSING_H

#include "../../../../../cli/command/command.h"

class ServiceUARTLicensing : public Command
{
private:
    void _enable();
    void _disable();
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* SERVICE_UART_LICENSING_H */