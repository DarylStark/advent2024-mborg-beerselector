#ifndef COMMAND_H
#define COMMAND_H

#include <map>
#include <memory>
#include <string>

#include "../../ds/platform_object_factory.h"

class Command
{
protected:
    static std::shared_ptr<ds::PlatformObjectFactory> _factory;

public:
    Command();
    static void set_factory(std::shared_ptr<ds::PlatformObjectFactory> factory);
    virtual bool execute(std::map<std::string, std::string> args) = 0;
};

#endif /* COMMAND_H */