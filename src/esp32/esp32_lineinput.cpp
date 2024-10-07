#include "esp32_lineinput.h"

#include <cstring>

namespace ds::esp32
{
    ESP32_LineInput::ESP32_LineInput(const UART &serial, char mask_char)
        : _uart(serial), _data(nullptr), _mask_char(mask_char)
    {
        reset();
    }

    ESP32_LineInput::~ESP32_LineInput()
    {
        _delete_buffer();
    }

    void ESP32_LineInput::_delete_buffer()
    {
        if (_data == nullptr)
            return;
        delete[] _data;
        _data = nullptr;
    }

    void ESP32_LineInput::reset()
    {
        _delete_buffer();
        _data = new char[1024];
        _cursor_position = 0;
        _length = 0;
    }

    void ESP32_LineInput::set_string(const std::string str) {
        _length = str.length();
        _cursor_position = _length;
        strcpy(_data, str.c_str());
    }

    void ESP32_LineInput::_finish_buffer() const
    {
        _data[_length] = '\0';
    }

    void ESP32_LineInput::_shift_left(size_t start)
    {
        for (size_t i = start; i < _length; i++) {
            _data[i] = _data[i + 1];
        }
        _length--;
    }

    void ESP32_LineInput::_move_cursor_right(uint32_t count)
    {
        if (_cursor_position == _length)
            return;

        for (size_t i = 0; i < count; i++)
        {
            _cursor_position++;
            _uart.write_bytes("\033[C", 3);
            if (_cursor_position >= _length)
                break;
        }
    }

    void ESP32_LineInput::_move_cursor_left(uint32_t count)
    {
        if (_cursor_position == 0)
            return;
        
        for (size_t i = 0; i < count; i++)
        {
            _cursor_position--;
            _uart.write_bytes("\033[D", 3);
            if (_cursor_position == 0)
                break;
        }
    }

    void ESP32_LineInput::_handle_escape_character()
    {
        char input[2];
        int len = _uart.get_bytes(input, 2);
        if (len == 2)
        {
            if (input[0] == '[')
            {
                // Arrow keys
                if (input[1] == ArrowKey::ARROW_RIGHT ||
                    input[1] == ArrowKey::ARROW_LEFT ||
                    input[1] == ArrowKey::ARROW_UP ||
                    input[1] == ArrowKey::ARROW_DOWN)
                {
                    _handle_arrow_key(static_cast<ArrowKey>(input[1]));
                }
                else if (input[1] == 51) {
                    int len = _uart.get_bytes(input, 1);
                    if (len == 1 && input[0] == '~') {
                        // Delete key
                        _handle_delete_key();
                    }
                }
            }
        }
    }

    void ESP32_LineInput::_handle_arrow_key(ArrowKey key) {
        switch (key)
        {
        case ARROW_RIGHT:
            _move_cursor_right();
            break;
        case ARROW_LEFT:
            _move_cursor_left();
            break;
        case ARROW_UP:

            break;
        case ARROW_DOWN:
            break;
        }
    }

    void ESP32_LineInput::_handle_backspace_key()
    {
        if (_cursor_position > 0) {
            size_t original_cursor_position = _cursor_position;

            // Move all bytes from the cursor position one step to the left
            _shift_left(_cursor_position - 1);

            if (_cursor_position <= _length) {
                _move_cursor_left();

                // Display everything from the cursor position onwards
                for (size_t i = _cursor_position; i < _length; i++) {
                    // _uart.write_bytes(&_data[i], 1);
                    if (_mask_char != '\0')
                    _uart.write_bytes(&_mask_char, 1);
                    else
                        _uart.write_bytes(&_data[i], 1);
                    _cursor_position++;
                }
                // Remove the last character (still on screen)
                _uart.write_bytes(" ", 1);
                _cursor_position++;

                // Rewind cursor to original position
                _move_cursor_left(_cursor_position - original_cursor_position + 1);
            } else {
                _uart.write_bytes("\b \b", 3);
                _cursor_position--;
            }
        }
    }

    void ESP32_LineInput::_handle_delete_key()
    {
        if (_cursor_position < _length) {
            size_t original_cursor_position = _cursor_position;
            _shift_left(_cursor_position);

            // Display everything from the cursor position onwards
            for (size_t i = _cursor_position; i < _length; i++) {
                if (_mask_char != '\0')
                    _uart.write_bytes(&_mask_char, 1);
                else
                    _uart.write_bytes(&_data[i], 1);
                _cursor_position++;
            }

            // Remove the last character (still on screen)
            _uart.write_bytes(" ", 1);
            _cursor_position++;

            // Rewind cursor to original position
            _move_cursor_left(_cursor_position - original_cursor_position);
        }
    }

    void ESP32_LineInput::_handle_alfa_character(char* input)
    {
        if (_mask_char != '\0')
            _uart.write_bytes(&_mask_char, 1);
        else
            _uart.write_bytes(input, 1);

        if (_cursor_position != _length) {
            // Move all data after the cursor position one step to the
            // right
            for (size_t i = _length; i > _cursor_position; i--) {
                _data[i] = _data[i - 1];
            }

            // Display everything from the cursor position onwards
            for (size_t i = _cursor_position + 1; i <= _length; i++) {
                if (_mask_char != '\0')
                    _uart.write_bytes(&_mask_char, 1);
                else
                    _uart.write_bytes(&_data[i], 1);
            }

            // Rewind cursor to original position
            for (size_t i = _cursor_position + 1; i <= _length; i++) {
                _uart.write_bytes("\033[D", 3);
            }
        }

        _data[_cursor_position] = input[0];
        _cursor_position++;
        _length++;
    }

    void ESP32_LineInput::_empty_line()
    {
        _move_cursor_left(_cursor_position);
        for (size_t i = 0; i < _length; i++) {
            _uart.write_bytes(" ", 1);
            _cursor_position++;
        }
        _move_cursor_left(_length);
        _length = 0;
    }

    std::string ESP32_LineInput::get(bool break_on_question_mark)
    {
        if (_length == 0)
            reset();
        _uart.write_bytes(_data, _length);

        while (1)
        {
            char input[8];
            int len = _uart.get_bytes(input, 1);

            if (len > 0)
            {
                // if (input[0] == 10 || input[0] == 13)
                // {
                //     std::cout << "--------------" << std::endl;
                //     continue;
                // }
                // std::cout << static_cast<int>(input[0]) << std::endl;
                // continue;

                if (input[0] == '\n' || input[0] == '\r')
                {
                    _finish_buffer();
                    break;
                }
                else if (input[0] == 1)
                {
                    // CTRL + A; move the cursor to the beginning of the line
                    _move_cursor_left(_length);
                }
                else if (input[0] == 3)
                {
                    // CTRL + C; return with a empty string
                    reset();
                    _finish_buffer();
                    break;
                }
                else if (input[0] == 4)
                {
                    // CTRL + D; empty the current lint
                    _empty_line();
                }
                else if (input[0] == 5)
                {
                    // CTRL + E; move the cursor to the end of the line
                    _move_cursor_right(_length - _cursor_position);
                }
                else if (input[0] == 26)
                {
                    // CTRL + Z; if the line is empty, return with 'exit
                    if (_length == 0)
                    {
                        strcpy(_data, "exit");
                    }
                    else
                    {
                        reset();
                        _finish_buffer();
                    }
                    break;
                }
                else if (input[0] == '\b' || input[0] == 127)
                {
                    _handle_backspace_key();
                }
                else if (input[0] == 27)
                {
                    _handle_escape_character();
                }
                else if (input[0] > 31 && input[0] < 127) {
                    _handle_alfa_character(input);
                    if (break_on_question_mark && input[0] == '?') {
                        _finish_buffer();
                        break;
                    }
                }
            }
        }

        std::string retval(_data);
        reset();
        return retval;
    }
}