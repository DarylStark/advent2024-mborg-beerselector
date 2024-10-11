#ifndef BOOTING_STATE_H
#define BOOTING_STATE_H

#include "../ds/base_state.h"
#include "app_info.h"

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
    bool _wait_for_keypress_rommon();

    // Boot methods
    void _go_to_rommon();
    void _go_to_normal_state();
    void _load_configuration();
    void _load_licenses();

public:
    BootingState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                 ds::BaseApplication &application);
    void run();
};

#endif /* BOOTING_STATE_H */
