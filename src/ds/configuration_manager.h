#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include <string>

namespace ds
{
    class ConfigurationManager
    {
    public:
        virtual void load_configuration() = 0;
        virtual void save_configuration() = 0;
        virtual const std::string get(const std::string& key) const = 0;
        virtual void set(const std::string& key, const std::string) = 0;
    };
}  // namespace ds

#endif  // CONFIGURATION_MANAGER_H