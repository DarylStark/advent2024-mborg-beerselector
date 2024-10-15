#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <string>
#include <vector>
#include <cstdint>

class CircularBuffer
{
private:
    uint16_t _max_size;
    std::vector<std::string> _buffer;

public:
    CircularBuffer(uint16_t max_size);
    void push_back(const std::string& value);
    const std::vector<std::string>& get_buffer() const;
    void set_max_size(uint16_t max_size);
};

#endif // CIRCULAR_BUFFER_H