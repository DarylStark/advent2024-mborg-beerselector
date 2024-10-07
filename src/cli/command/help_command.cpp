#include <sstream>
#include "help_command.h"

constexpr uint32_t COMMAND_COLUMN_LENGTH = 24;

HelpCommand::HelpCommand(ArgumentedCommandParser *parser) : _parser(parser) {}

bool HelpCommand::execute(std::map<std::string, std::string> args)
{
    // TODO: Only show `Subcommands` and `Arguments` headers when there is
    // something to show

    const auto &output_handler = Command::_factory->get_output_handler();

    output_handler->println();
    output_handler->println(_parser->get_help());

    output_handler->println("\nSubcommands");
    for (const auto &subparser : _parser->get_parsers())
    {
        if (!subparser.second->show_in_help()) continue;
        std::stringstream subparser_help;
        subparser_help << "  " << std::left << std::setw(COMMAND_COLUMN_LENGTH)
                       << subparser.first
                       << subparser.second->get_description();
        output_handler->println(subparser_help.str());
    }

    output_handler->println("\nArguments");
    for (const auto &argument : _parser->get_argumentes())
    {
        std::stringstream arg_name;
        if (argument->is_required())
        {
            arg_name << "<" << argument->get_name() << ">";
        }
        else
        {
            arg_name << "[" << argument->get_name() << "]";
        }
        std::stringstream arg_help;
        arg_help << "  " << std::left << std::setw(COMMAND_COLUMN_LENGTH)
                 << arg_name.str() << argument->get_description();
        output_handler->println(arg_help.str());
    }
    output_handler->println();

    return true;
}