#include "set_config_string.h"

SetConfigString::SetConfigString(std::map<std::string, std::string> arg_config_keys)
    : _arg_config_keys(arg_config_keys)
{
}

bool SetConfigString::execute(std::map<std::string, std::string> args) {
    if (_pre_execute)
        if (!_pre_execute(args))
            return false;
    
    for (const auto& arg: _arg_config_keys) {
        _factory->get_configuration_manager()->set(arg.second, args[arg.first]);
    }

    if (_post_execute)
        return _post_execute(args);
    return false;
}

void SetConfigString::set_pre_execute(std::function<bool(std::map<std::string, std::string> args)> pre_execute)
{
    _pre_execute = pre_execute;
}

void SetConfigString::set_post_execute(std::function<bool(std::map<std::string, std::string> args)> post_execute)
{
    _post_execute = post_execute;
}