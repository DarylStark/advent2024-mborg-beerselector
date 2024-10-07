#ifndef __BOOTING_STATE_H__
#define __BOOTING_STATE_H__

#include "../ds/base_state.h"
#include "app_info.h"

#define SECONDS_WAIT_FOR_KEYPRESS 10  // TODO: Set to a normal number

class ScopedAction
{
private:
    bool _success;
    std::shared_ptr<ds::OutputHandler> _output_handler;
    void _print_done();
    void _print_fail();

public:
    ScopedAction(std::string title,
                 std::shared_ptr<ds::OutputHandler> output_handler);
    ~ScopedAction();
};

class BootingState : public ds::BaseState
{
private:
    std::shared_ptr<ds::OutputHandler> _output_handler;
    std::shared_ptr<ds::InputHandler> _input_handler;

    void _print_logo() const;
    void _print_device_information() const;
    void _wait_for_keypress_rommon();

    // Boot methods
    void _go_to_rommon();
    void _load_configuration();

public:
    BootingState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                 ds::BaseApplication &application);
    void loop();
};

#endif /* __BOOTING_STATE_H__ */