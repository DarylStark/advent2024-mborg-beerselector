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

    if (_buffer.size() >= _max_size)
        _buffer.erase(_buffer.begin());
    _buffer.push_back(value);
}

const std::vector<std::string>& CircularBuffer::get_buffer() const
{
    return _buffer;
}

void CircularBuffer::set_max_size(uint16_t max_size)
{
    _max_size = max_size;
    _buffer.reserve(max_size);
}