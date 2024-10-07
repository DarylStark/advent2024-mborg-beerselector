#include "command.h"

std::shared_ptr<ds::PlatformObjectFactory> Command::_factory = nullptr;

Command::Command()
{
    if (_factory == nullptr)
        throw std::runtime_error(
            "PlatformObjectFactory not set for the Command class");
}

void Command::set_factory(std::shared_ptr<ds::PlatformObjectFactory> factory)
{
    _factory = factory;
}