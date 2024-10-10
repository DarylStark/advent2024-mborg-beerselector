#include "enable.h"
#include "../../../../globals.h"
#include "../cli_parser_priv_exec.h"

bool Enable::execute(std::map<std::string, std::string> args)
{
    int counter = 0;

    while (counter < 3)
    {
        std::string password = _factory->get_input_handler()->get_password("Enable password: ", "");
        _factory->get_output_handler()->println("");
        if (password == _factory->get_configuration_manager()->get("auth.enable"))
        {
            next_parser = CLIParserPrivExec().get_parser();
            prompt = "# ";
            return false;
        }
        counter++;
    }

    _factory->get_output_handler()->println("Incorrect password");
    return false;
}