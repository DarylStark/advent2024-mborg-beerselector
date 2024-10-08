#ifndef ESP32_LINE_INPUT_H
#define ESP32_LINE_INPUT_H

#include <string>
#include "uart.h"

namespace ds::esp32
{
    enum ArrowKey
    {
        ARROW_UP = 0x41,
        ARROW_DOWN = 0x42,
        ARROW_RIGHT = 0x43,
        ARROW_LEFT = 0x44
    };

    class ESP32_LineInput {
    private:
        const UART &_uart;
        char* _data;
        size_t _cursor_position;
        size_t _length;
        char _mask_char;

    protected:
        // Buffer management
        void _delete_buffer();
        void _finish_buffer() const;
        void _shift_left(size_t start);

        // Cursor movement
        void _move_cursor_right(uint32_t count=1);
        void _move_cursor_left(uint32_t count=1);

        // Key handlers
        void _handle_escape_character();
        void _handle_arrow_key(ArrowKey key);
        void _handle_backspace_key();
        void _handle_delete_key();
        void _handle_alfa_character(char *input);

        // Other methods
        void _empty_line();

    public:
        ESP32_LineInput(const UART &uart, char mask_char = '\0');
        ~ESP32_LineInput();

        void reset();
        void set_string(const std::string str);
        std::string get(bool break_on_question_mark = false);
    };
}

#endif /* ESP32_LINE_INPUT_H */