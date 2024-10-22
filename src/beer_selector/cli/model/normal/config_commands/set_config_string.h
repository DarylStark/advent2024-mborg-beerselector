#ifndef SET_CONFIG_STRING_H
#define SET_CONFIG_STRING_H

#include <functional>
#include "../../../../../cli/command/command.h"

class SetConfigString: public Command {
private:
    std::map<std::string, std::string> _arg_config_keys;
    std::function<bool(std::map<std::string, std::string> args)> _pre_execute;
    std::function<bool(std::map<std::string, std::string> args)> _post_execute;

public:
    SetConfigString(std::map<std::string, std::string> arg_config_keys);
    virtual bool execute(std::map<std::string, std::string> args) override;
    void set_pre_execute(std::function<bool(std::map<std::string, std::string> args)> pre_execute);
    void set_post_execute(std::function<bool(std::map<std::string, std::string> args)> post_execute);
};

#endif // SET_CONFIG_STRING_H