#ifndef NORMAL_STATE_H
#define NORMAL_STATE_H

#include <queue>
#include <mutex>
#include "../ds/base_state.h"
#include "app_info.h"
#include "logging_data.h"

class NormalState : public ds::BaseState
{
private:
    std::queue<LoggingData> _logging_queue;
    std::mutex _queue_mutex;

public:
    NormalState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                 ds::BaseApplication &application);

    // Logging
    void log(Severity severity, const std::string message);

    // Service starts
    void start_logging_service();
    void start_cli_service();
    void start_login_service();

    // Service workers
    static void login_prompt(void *args);
    static void logging_service(void *args);
    static void normal_cli(void *args);

    // Run
    void run();
};

#endif /* NORMAL_STATE_H */
