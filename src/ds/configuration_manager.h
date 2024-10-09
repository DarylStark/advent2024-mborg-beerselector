#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

namespace ds
{
    class ConfigurationManager
    {
    public:
        virtual void load_configuration() = 0;
    };
}  // namespace ds

#endif  // CONFIGURATION_MANAGER_H