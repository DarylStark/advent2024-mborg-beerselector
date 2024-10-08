#ifndef ROMMON_STATE_H
#define ROMMON_STATE_H

#include <iterator>
#include <sstream>

#include "../ds/base_state.h"

class RommonState : public ds::BaseState
{
private:
    std::shared_ptr<ds::OutputHandler> _output_handler;
    std::shared_ptr<ds::InputHandler> _input_handler;

public:
    RommonState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                ds::BaseApplication &application);
    void loop();
};

#endif /* ROMMON_STATE_H */