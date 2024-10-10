#ifndef LOGGING_H
#define LOGGING_H

#include <queue>
#include <mutex>

#include "logging_data.h"

extern std::queue<LoggingData> logging_queue;
extern std::mutex queue_mutex;

void log(Severity severity, const std::string message);

#endif /* LOGGING_H */