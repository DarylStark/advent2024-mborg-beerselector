#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <vector>

#include "argumented_command_parser.h"

class ParserException : public std::exception
{
protected:
    std::string _message;

public:
    ParserException(const std::string& message);
    virtual const char* what() const noexcept override;
};

class ConstructException : public ParserException
{
public:
    ConstructException(const std::string& message);
};

class RequiredArgumentException : public ConstructException
{
public:
    RequiredArgumentException(const std::string& argument_name);
};

class ParseException : public ParserException
{
public:
    ParseException(const std::string& message);
};

class NotImplementedCommandException : public ParseException
{
public:
    NotImplementedCommandException();
};

class WrongArgumentCountException : public ParseException
{
public:
    WrongArgumentCountException(
        std::vector<std::shared_ptr<Argument>> arguments);
};

class WrongArgumentTypeException : public ParseException
{
public:
    WrongArgumentTypeException(const std::string& argument_name,
                               const std::string& expected_type);
};

class WrongEnumArgumentException : public ParseException
{
public:
    WrongEnumArgumentException(const std::string& argument_name,
                               const std::vector<std::string>& possibilities);
};

#endif /* EXCEPTIONS_H */