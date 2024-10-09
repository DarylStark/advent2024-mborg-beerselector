#include "booting_state.h"

#include <iomanip>
#include <sstream>

#include "rommon_state.h"

ScopedAction::ScopedAction(std::string title,
                           std::shared_ptr<ds::OutputHandler> output_handler)
    : _success(true), _output_handler(output_handler)
{
    std::stringstream out;
    out << "\r\n" << std::setw(50) << std::setfill('.') << std::left << title;
    _output_handler->print(out.str());
    _output_handler->flush();
}

ScopedAction::~ScopedAction()
{
    if (_success)
    {
        _print_done();
        return;
    }
    _print_fail();
}

void ScopedAction::_print_done()
{
    _output_handler->println("DONE");
    _output_handler->flush();
}

void ScopedAction::_print_fail()
{
    _output_handler->println("FAIL");
    _output_handler->flush();
}

BootingState::BootingState(std::shared_ptr<ds::PlatformObjectFactory> factory,
                           ds::BaseApplication &application)
    : ds::BaseState(factory, application),
      _output_handler(_factory->get_output_handler()),
      _input_handler(_factory->get_input_handler())
{
}

void BootingState::_print_logo() const
{
    _output_handler->println("");
    _output_handler->println("");

    // Create the title and center it
    std::stringstream title;
    title << PUBLISHER << " " << HW_TYPE;
    std::string title_text = title.str();
    uint16_t spaces = 47 / 2 - (title_text.length() / 2);

    _output_handler->print(std::string(spaces, ' '));
    _output_handler->println(title_text);

    _output_handler->println("");
    _output_handler->println("                  | | | | | |");
    _output_handler->println("            | | | | | | | | | | | |");
    _output_handler->println("        | | | | | | | | | | | | | | | |");
    _output_handler->println("    . | | | | | | | | | | | | | | | | | | .");
    _output_handler->println("===============================================");
    _output_handler->println("");
}

void BootingState::_print_device_information() const
{
    {
        std::stringstream out;
        out << std::setw(18) << std::left << "Model"
            << ": " << HW_TYPE << " REV " << HW_REV;
        _output_handler->println(out.str());
    }

    {
        std::stringstream out;
        out << std::setw(18) << std::left << "Software version"
            << ": " << APP_NAME << " " << APP_VERSION;
        _output_handler->println(out.str());
    }

    {
        std::stringstream out;
        out << std::setw(18) << std::left << "Serial number"
            << ": " << HW_SERIAL;
        _output_handler->println(out.str());
    }
    _output_handler->println("");
}

bool BootingState::_wait_for_keypress_rommon()
{
    _output_handler->println(
        "PRESS CTRL+C OR CTRL+B TO SKIP BOOTING AND GO TO ROMMON.");
    auto os = _factory->get_os();

    uint16_t counter = 0;
    uint32_t sleep = 100;
    uint32_t dots = (BOOT_SECONDS_WAIT_FOR_KEYPRESS * 1000) / sleep;
    while (counter++ < dots)
    {
        _output_handler->print(".");
        _output_handler->flush();
        if (_input_handler->is_break_pressed())
        {
            _output_handler->println("\r\n\r\nGOING TO ROMMON...");
            _go_to_rommon();
            return true;
        }
        os->sleep_miliseconds(sleep - 5);
    }
    return false;
}

void BootingState::_load_configuration()
{
    ScopedAction action("Loading configuration", _output_handler);
    _factory->get_configuration_manager()->load_configuration();
}

void BootingState::_go_to_rommon()
{
    _application.set_state(
        std::make_shared<RommonState>(_factory, _application));
}

void BootingState::run()
{
    _print_logo();
    _print_device_information();

    // Start with the system boot
    _output_handler->println("SYSTEM BOOTING ...");
    _output_handler->flush();

    // Retrieve the configuration
    _load_configuration();

    _output_handler->println("");
    _output_handler->flush();

    // Give the user the option to skip the booting and go to ROMMON
    if (_wait_for_keypress_rommon())
        return;
    
    _output_handler->println("\r\n\r\nCONTINUE BOOTING SYSTEM NORMALLY...");

    // Check if a license is given and try to retrieve it if it isn't given.
    // Connect with the configured WiFi if needed for this.

    // If the license is correct, boot into user mode
}