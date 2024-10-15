#ifndef PLATFORM_OBJECT_FACTORY_H
#define PLATFORM_OBJECT_FACTORY_H

#include <memory>

#include "configuration_manager.h"
#include "input_handler.h"
#include "os.h"
#include "output_handler.h"
#include "display.h"

namespace ds
{
    class PlatformObjectFactory
    {
    private:
        std::shared_ptr<OutputHandler> _output_handler;
        std::shared_ptr<InputHandler> _input_handler;
        std::shared_ptr<OS> _os;
        std::shared_ptr<ConfigurationManager> _configuration_manager;
        std::shared_ptr<Display> _display;

    protected:
        virtual std::shared_ptr<OutputHandler> _get_output_handler() = 0;
        virtual std::shared_ptr<InputHandler> _get_input_handler() = 0;
        virtual std::shared_ptr<OS> _get_os() = 0;
        virtual std::shared_ptr<ConfigurationManager> _get_configuration_manager() = 0;
        virtual std::shared_ptr<Display> _get_display() = 0;

    public:
        std::shared_ptr<OutputHandler> get_output_handler();
        std::shared_ptr<InputHandler> get_input_handler();
        std::shared_ptr<OS> get_os();
        std::shared_ptr<ConfigurationManager> get_configuration_manager();
        std::shared_ptr<Display> get_display();
    };
};  // namespace ds

#endif /* PLATFORM_OBJECT_FACTORY_H */