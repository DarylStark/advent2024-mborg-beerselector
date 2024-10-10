#include "disable.h"
#include "../../../../globals.h"
#include "../cli_parser_user_exec.h"

bool Disable::execute(std::map<std::string, std::string> args)
{
    next_parser = CLIParserUserExec().get_parser();
    prompt = "> ";
    return false;
}