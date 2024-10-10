#include "config_exit.h"
#include "../../../../globals.h"
#include "../cli_parser_priv_exec.h"

bool ConfigExit::execute(std::map<std::string, std::string> args)
{
    next_parser = CLIParserPrivExec().get_parser();
    prompt = "# ";
    return false;
}