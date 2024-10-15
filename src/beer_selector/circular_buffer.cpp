#include "circular_buffer.h"

CircularBuffer::CircularBuffer(uint16_t max_size)
    : _max_size(max_size)
{
    _buffer.reserve(max_size);
}

void CircularBuffer::push_back(const std::string& value)
{
    if (_max_size == 0)
        return;

    _buffer.push_back(value);
    if (_buffer.size() >= _max_size)
        resize_buffer();
}

const std::vector<std::string>& CircularBuffer::get_buffer() const
{
    return _buffer;
}

void CircularBuffer::set_max_size(uint16_t max_size)
{
    _max_size = max_size;
    _buffer.reserve(max_size);
    resize_buffer();
}

void CircularBuffer::resize_buffer()
{
    if (_max_size == 0)
    {
        _buffer.clear();
    }

    if (_max_size > _buffer.size())
        return;

    for (uint16_t i = 0; i < _buffer.size() - _max_size; i++)
        _buffer.erase(_buffer.begin());
}
