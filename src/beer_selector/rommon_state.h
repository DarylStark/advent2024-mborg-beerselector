#ifndef __ROMMON_STATE_H__
#define __ROMMON_STATE_H__

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

#endif /* __ROMMON_STATE_H__ */