#include "beer_selector.h"

#include <iomanip>
#include <sstream>

#include "booting_state.h"

BeerSelector::BeerSelector(std::shared_ptr<ds::PlatformObjectFactory> factory)
    : ds::BaseApplication(factory)
{
    _output_handler = _factory->get_output_handler();
    _input_handler = _factory->get_input_handler();
}

void BeerSelector::setup()
{
    // Set the state to booting. The booting state will switch to the correct
    // state after booting. This can be a few states, based on the boot
    // conditions.

    _factory->get_os()->sleep_miliseconds(1000);
    set_state(std::make_shared<BootingState>(_factory, *this));
}

void BeerSelector::loop()
{
    _state->loop();
}
