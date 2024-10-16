#include "uart.h"

namespace ds::esp32
{
    UART::UART(uart_port_t port, int32_t baud_rate, int tx_pin, int rx_pin)
        : _port(port), _baud_rate(baud_rate), _tx_pin(tx_pin), _rx_pin(rx_pin), _is_initialized(false)
    {
        initialize();
    }

    void UART::initialize()
    {
        // TODO: Make the variables configurable

        if (_is_initialized)
            return;

        uart_config_t uart_config = {
            .baud_rate = _baud_rate,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
            .rx_flow_ctrl_thresh = 122,
            .source_clk = UART_SCLK_APB};

        // Install UART driver
        if (uart_driver_install(_port, BUF_SIZE * 2, 0, 0, NULL, 0) != ESP_OK) {
            //std::cerr << "Failed to install UART driver" << std::endl;
            // TODO: Exception
            return;
        }

        // Configure UART parameters
        if (uart_param_config(_port, &uart_config) != ESP_OK) {
            //std::cerr << "Failed to configure UART parameters" << std::endl;
            // TODO: Exception
            return;
        }

        // Set UART pins
        if (uart_set_pin(_port, _tx_pin, _rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) != ESP_OK) {
            //std::cerr << "Failed to set UART pins" << std::endl;
            // TODO: Exception
            return;
        }

        _is_initialized = true;
    }

    int UART::get_bytes(char *data, size_t length, uint32_t timeout) const
    {
        // TODO: Make the wait time configurable
        return uart_read_bytes(_port, data, length, pdMS_TO_TICKS(timeout));
    }

    int UART::write_bytes(const char *data, size_t length) const
    {
        return uart_write_bytes(_port, data, length);
    }
}  // namespace ds::esp32
