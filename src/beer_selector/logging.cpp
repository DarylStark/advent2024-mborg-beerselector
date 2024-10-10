#include "logging.h"

std::queue<LoggingData> logging_queue;
std::mutex queue_mutex;

void log(Severity severity, const std::string message)
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    logging_queue.push(LoggingData(severity, message));
}