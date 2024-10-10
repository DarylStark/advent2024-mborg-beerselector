#ifndef NORMAL_STATE_H
#define NORMAL_STATE_H

#include "../ds/base_state.h"
#include "app_info.h"

class NormalState : public ds::BaseState
{
public:
    NormalState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                 ds::BaseApplication &application);

    // Cli
    static void login_prompt(void *args);
    static void normal_cli(void *args);

    // Run
    void run();
};

#endif /* NORMAL_STATE_H */
