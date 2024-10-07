#include "base_state.h"
namespace ds
{
    BaseState::BaseState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                         ds::BaseApplication &application)
        : _factory(factory), _application(application)
    {
    }
}  // namespace ds