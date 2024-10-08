#ifndef BEER_SELECTOR_H
#define BEER_SELECTOR_H

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

#endif /* BEER_SELECTOR_H */