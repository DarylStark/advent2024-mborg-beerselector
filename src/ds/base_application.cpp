#include "base_application.h"

#include "../cli/cli/cli_runner.h"
#include "../cli/command/command.h"

namespace ds
{
    BaseApplication::BaseApplication(
        std::shared_ptr<PlatformObjectFactory> factory)
        : _factory(factory), _state(nullptr)
    {
        Command::set_factory(factory);
        CLIRunner::set_factory(factory);
    }

    void BaseApplication::set_state(std::shared_ptr<ds::State> state)
    {
        _state = state;
    }
}  // namespace ds