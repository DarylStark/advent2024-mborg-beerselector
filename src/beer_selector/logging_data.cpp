#include <sstream>
#include <iomanip>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "logging_data.h"

LoggingData::LoggingData(Severity severity, const std::string message)
    : _time(xTaskGetTickCount() * portTICK_PERIOD_MS),
      _taskname(pcTaskGetTaskName(NULL)),
      _severity(severity),
        _message(message)
{
    timeval now;
    gettimeofday(&now, NULL);
    tm timeinfo;
    localtime_r(&now.tv_sec, &timeinfo);

    std::stringstream datetime;
    datetime << timeinfo.tm_year + 1900 << "-"
             << std::setw(2) << std::setfill('0') << timeinfo.tm_mon + 1 << "-"
             << std::setw(2) << std::setfill('0') << timeinfo.tm_mday << " "
             << std::setw(2) << std::setfill('0') << timeinfo.tm_hour << ":"
             << std::setw(2) << std::setfill('0') << timeinfo.tm_min << ":"
             << std::setw(2) << std::setfill('0') << timeinfo.tm_sec << "."
             << std::setw(6) << std::setfill('0') << now.tv_usec;
    _datetime = datetime.str();
}

const std::string LoggingData::get_message() const
{
    std::stringstream out;
    out << "[" << _datetime << "] <" << _taskname << "> ";
    
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

const Severity LoggingData::get_severity() const
{
    return _severity;
}