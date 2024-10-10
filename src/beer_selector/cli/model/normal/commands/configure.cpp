#include "configure.h"
#include "../../../../globals.h"
#include "../cli_parser_config.h"

bool Configure::execute(std::map<std::string, std::string> args)
{
    next_parser = CLIParserConfig().get_parser();
    prompt = "(config)# ";
    return false;
}