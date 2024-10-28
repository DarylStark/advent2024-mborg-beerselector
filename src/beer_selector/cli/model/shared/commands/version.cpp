#include <sstream>
#include <iomanip>
#include "version.h"
#include "../../../../app_info.h"

bool Version::execute(std::map<std::string, std::string> args)
{
    const auto& output_handler = _factory->get_output_handler();

    {
        std::stringstream out;
        output_handler->println("");
        out << PUBLISHER << " " << HW_TYPE;
        std::string title_text = out.str();
        output_handler->println(title_text);
        output_handler->println("");
    }

    {
        std::stringstream out;
        out << std::setw(18) << std::left << "Model"
            << ": " << HW_TYPE << " REV " << HW_REV;
        output_handler->println(out.str());
    }

    {
        std::stringstream out;
        out << std::setw(18) << std::left << "Software version"
            << ": " << APP_NAME << " " << APP_VERSION;
        output_handler->println(out.str());
    }

    {
        std::stringstream out;
        out << std::setw(18) << std::left << "Serial number"
            << ": " << HW_SERIAL;
        output_handler->println(out.str());
    }
    output_handler->println("");

    return true;
}