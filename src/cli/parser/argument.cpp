#include "argument.h"

#include "exceptions.h"

Argument::Argument(std::string name, bool required,
                   const std::string &description)
    : _name(name), _description(description), _required(required)
{
}

const std::string &Argument::get_name() const
{
    return _name;
}

bool Argument::is_required() const
{
    return _required;
}

const std::string &Argument::get_description() const
{
    return _description;
}

StaticArgument::StaticArgument(std::string name, std::string expected_value,
                               bool required, const std::string description)
    : Argument(name, required, description), _expected_value(expected_value)
{
}

void StaticArgument::parse(std::string argument)
{
    // TODO: Implement code to check if this argument is valid
    if (argument != _expected_value)
    {
        throw WrongArgumentTypeException(get_name(), _expected_value);
    }
}

EnumArgument::EnumArgument(std::string name,
                           std::vector<std::string> possibilities,
                           bool required, const std::string description)
    : Argument(name, required, description), _possibilities(possibilities)
{
}

void EnumArgument::parse(std::string argument)
{
    auto it = std::find(_possibilities.begin(), _possibilities.end(), argument);
    if (it == _possibilities.end())
        throw WrongEnumArgumentException(get_name(), _possibilities);
}

void StringArgument::parse(std::string argument)
{
    // Nothing to do here, it is already a string
}

void IntArgument::parse(std::string argument)
{
    try
    {
        int value = std::stoi(argument);
    }
    catch (const std::invalid_argument &e)
    {
        throw WrongArgumentTypeException(get_name(), "a number");
    }
}