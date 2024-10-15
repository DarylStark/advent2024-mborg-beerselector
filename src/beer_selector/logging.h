#ifndef LOGGING_H
#define LOGGING_H

#include <queue>
#include <mutex>

#include "logging_data.h"
#include "circular_buffer.h"

extern std::queue<LoggingData> logging_queue;
extern std::mutex queue_mutex;
extern CircularBuffer log_buffer;
extern uint16_t log_buffer_size;
extern uint8_t log_buffer_level;

void log(Severity severity, const std::string message);

#endif /* LOGGING_H */