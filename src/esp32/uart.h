#ifndef UART_H
#define UART_H

#include <cstddef> // For size_t
#include <cstdint> // For uint32_t
#include <driver/uart.h>

#define BUF_SIZE           1024

namespace ds::esp32
{
    class UART {
    public:
        uart_port_t _port;
        int32_t _baud_rate;
        int _tx_pin;
        int _rx_pin;
        bool _is_initialized;

    public:
        UART(uart_port_t port, int32_t baud_rate, int tx_pin = 1, int rx_pin = 3);
        void initialize();
        int get_bytes(char *data, size_t length, uint32_t timeout = 1000) const;
        int write_bytes(const char *data, size_t length) const;
        void flush();
    };
} // namespace ds::esp32

#endif /* UART_H */
