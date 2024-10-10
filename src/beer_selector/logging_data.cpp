#include <sstream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "logging_data.h"

LoggingData::LoggingData(Severity severity, const std::string message)
    : _time(xTaskGetTickCount() * portTICK_PERIOD_MS),
      _taskname(pcTaskGetTaskName(NULL)),
      _severity(severity),
        _message(message)
{
}

const std::string LoggingData::get_message() const
{
    std::stringstream out;
    out << "[" << _time << "] <" << _taskname << "> ";
    
    switch (_severity)
    {
    case EMERGENCY:
        out << "EMERGENCY: ";
        break;
    case ALERT:
        out << "ALERT: ";
        break;
    case CRITICAL:
        out << "CRITICAL: ";
        break;
    case ERROR:
        out << "ERROR: ";
        break;
    case WARNING:
        out << "WARNING: ";
        break;
    case NOTICE:
        out << "NOTICE: ";
        break;
    case INFO:
        out << "INFO: ";
        break;
    case DEBUG:
        out << "DEBUG: ";
        break;
    }

    out << _message;
    return out.str();
}