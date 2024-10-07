#ifndef __BEER_SELECTOR_H__
#define __BEER_SELECTOR_H__

#include <memory>

#include "../ds/base_application.h"

class BeerSelector : public ds::BaseApplication
{
private:
    // Handlers
    std::shared_ptr<ds::OutputHandler> _output_handler;
    std::shared_ptr<ds::InputHandler> _input_handler;

public:
    BeerSelector(std::shared_ptr<ds::PlatformObjectFactory> factory);

    // Overrides
    void setup();
    void loop();
};

#endif /* __BEER_SELECTOR_H__ */