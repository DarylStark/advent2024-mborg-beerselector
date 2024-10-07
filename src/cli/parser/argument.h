#ifndef __ARGUMENT_H__
#define __ARGUMENT_H__

#include <algorithm>
#include <string>
#include <vector>

class Argument
{
private:
    std::string _name;
    const std::string _description;
    bool _required;

public:
    Argument(std::string name, bool required = false,
             const std::string &description = std::string(""));
    const std::string &get_name() const;
    virtual void parse(std::string argument) = 0;
    bool is_required() const;
    const std::string &get_description() const;
};

/* Static argument */

class StaticArgument : public Argument
{
private:
    std::string _expected_value;

public:
    StaticArgument(std::string name, std::string expected_value,
                   bool required = false,
                   const std::string description = std::string(""));
    void parse(std::string argument) override;
};

/* Enum based argument */

class EnumArgument : public Argument
{
private:
    std::vector<std::string> _possibilities;

public:
    EnumArgument(std::string name, std::vector<std::string> possibilities,
                 bool required = false,
                 const std::string description = std::string(""));
    void parse(std::string argument) override;
};

/* Argument for a string */

class StringArgument : public Argument
{
public:
    StringArgument(std::string name, bool required = false,
                   const std::string description = std::string(""))
        : Argument(name, required, description)
    {
    }
    void parse(std::string argument) override;
};

/* Argument for a integer */

class IntArgument : public Argument
{
public:
    IntArgument(std::string name, bool required = false,
                const std::string description = std::string(""))
        : Argument(name, required, description)
    {
    }
    void parse(std::string argument) override;
};

#endif /* __ARGUMENT_H__ */