#ifndef CONFIGURATION_LOADER_H
#define CONFIGURATION_LOADER_H

namespace ds
{
    class ConfigurationLoader
    {
    public:
        virtual void load_configuration() = 0;
    };
}  // namespace ds

#endif  // CONFIGURATION_LOADER_H