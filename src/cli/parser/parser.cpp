#include "parser.h"

Parser::Parser(const std::string description, const std::string help,
               bool show_in_help)
    : _description(description), _help(help), _show_in_help(show_in_help)
{
}

std::shared_ptr<Parser> Parser::add_parser(std::string name,
                                           std::shared_ptr<Parser> parser)
{
    _parsers[name] = parser;
    return parser;
}

std::shared_ptr<Parser> Parser::get_parser(std::string name) const
{
    try
    {
        return _parsers.at(name);
    }
    catch (const std::out_of_range &e)
    {
        return nullptr;
    }
}

void Parser::delete_parser(std::string name)
{
    _parsers.erase(name);
}

const std::string &Parser::get_description() const
{
    return _description;
}

const std::string &Parser::get_help() const
{
    return _help;
}

const std::map<std::string, std::shared_ptr<Parser>> &Parser::get_parsers()
    const
{
    return _parsers;
}

bool Parser::show_in_help() const
{
    return _show_in_help;
}