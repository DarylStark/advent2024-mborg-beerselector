#ifndef UART_H
#define UART_H

#include <cstddef> // For size_t

#define UART_PORT_NUM      UART_NUM_0
#define UART_BAUD_RATE     115200
#define BUF_SIZE           1024

namespace ds::esp32
{
    class UART {
    private:
        bool _is_initialized;;

    public:
        UART();
        void initialize();
        int get_bytes(char *data, size_t length) const;
        int write_bytes(const char *data, size_t length) const;
    };
} // namespace ds::esp32

#endif /* UART_H */