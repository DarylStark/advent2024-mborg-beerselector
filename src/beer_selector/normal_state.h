#ifndef NORMAL_STATE_H
#define NORMAL_STATE_H

#include <queue>
#include <mutex>
#include "../ds/base_state.h"
#include "app_info.h"
#include "logging_data.h"

#include "freertos/FreeRTOS.h"
#include <freertos/semphr.h>
#include <freertos/timers.h>

class NormalState : public ds::BaseState
{
private:
    static void _isr_mode_button_state_change(void * args);
    TimerHandle_t _display_beer_list_timer;
    SemaphoreHandle_t _mode_button_semaphore;
    uint16_t _beer_list_index;

public:
    NormalState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                 ds::BaseApplication &application);

    // Service starts
    void start_logging_service();
    void start_cli_service();
    void start_login_service();
    void start_input_service();

    // Timer creations
    void create_display_beer_list_timer();

    // Service workers
    static void login_prompt(void *args);
    static void logging_service(void *args);
    static void normal_cli(void *args);
    static void input_service(void *args);

    // Timer services
    static void display_beer_list(TimerHandle_t xTimer);

    // Run
    void run();
};

#endif /* NORMAL_STATE_H */
