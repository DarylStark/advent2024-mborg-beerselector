#ifndef __BASE_STATE_H__
#define __BASE_STATE_H__

#include "base_application.h"
#include "platform_object_factory.h"
#include "state.h"

namespace ds
{
    class BaseState : public ds::State
    {
    protected:
        std::shared_ptr<ds::PlatformObjectFactory> _factory;
        ds::BaseApplication &_application;

    public:
        BaseState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                  ds::BaseApplication &application);
    };
}  // namespace ds

#endif /* __BASE_STATE_H__ */