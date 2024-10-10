#ifndef GENERIC_STATE_H
#define GENERIC_STATE_H

#include "../ds/base_state.h"
#include "app_info.h"

class GenericState : public ds::BaseState
{
public:
    GenericState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                 ds::BaseApplication &application);

    // Cli
    static void login_prompt(void *args);
    static void normal_cli(void *args);

    // Run
    void run();
};

#endif /* GENERIC_STATE_H */
