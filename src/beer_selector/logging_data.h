#ifndef LOGGING_DATA_H
#define LOGGING_DATA_H

#include <string>

enum Severity
{
    EMERGENCY,
    ALERT,
    CRITICAL,
    ERROR,
    WARNING,
    NOTICE,
    INFO,
    DEBUG
};

class LoggingData
{
private:
    uint64_t _time;
    std::string _taskname;
    Severity _severity;
    std::string _message;

public:
    LoggingData(Severity severity, const std::string message);
    const std::string get_message() const;
};

#endif /* LOGGING_DATA_H */