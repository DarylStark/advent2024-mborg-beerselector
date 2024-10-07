#include "exceptions.h"

ParserException::ParserException(const std::string& message) : _message(message)
{
}

const char* ParserException::what() const noexcept
{
    return _message.c_str();
}

ConstructException::ConstructException(const std::string& message)
    : ParserException(message)
{
}

RequiredArgumentException::RequiredArgumentException(
    const std::string& argument_name)
    : ConstructException(
          "Required argument set after not required argument: \"" +
          argument_name + "\"")
{
}

ParseException::ParseException(const std::string& message)
    : ParserException(message)
{
}

NotImplementedCommandException::NotImplementedCommandException()
    : ParseException("Command not implemented")
{
}

WrongArgumentCountException::WrongArgumentCountException(
    std::vector<std::shared_ptr<Argument>> arguments)
    : ParseException("\nWrong argument count. Expected arguments:\n")
{
    for (const auto& argument : arguments)
    {
        _message += "> " + argument->get_name() + "\n";
    }
}

WrongArgumentTypeException::WrongArgumentTypeException(
    const std::string& argument_name, const std::string& expected_type)
    : ParseException("Wrong argument type for argument \"" + argument_name +
                     "\". Expected " + expected_type)
{
}

WrongEnumArgumentException::WrongEnumArgumentException(
    const std::string& argument_name,
    const std::vector<std::string>& possibilities)
    : ParseException("Wrong argument value for argument \"" + argument_name +
                     "\". Expected one of: ")
{
    for (const auto& possibility : possibilities)
    {
        _message += "> " + possibility + "\n";
    }
}