#ifndef __CONFIGURATION_LOADER_H__
#define __CONFIGURATION_LOADER_H__

namespace ds
{
    class ConfigurationLoader
    {
    public:
        virtual void load_configuration() = 0;
    };
}  // namespace ds

#endif  // __CONFIGURATION_LOADER_H__