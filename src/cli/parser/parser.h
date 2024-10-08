#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <memory>
#include <string>
#include <vector>

class Parser
{
protected:
    std::map<std::string, std::shared_ptr<Parser>> _parsers;
    const std::string _description;
    const std::string _help;
    bool _show_in_help;

public:
    Parser(const std::string description = std::string(""),
           const std::string help = std::string(""), bool show_in_help = true);
    std::shared_ptr<Parser> add_parser(std::string name,
                                       std::shared_ptr<Parser> parser);
    void delete_parser(std::string name);
    std::shared_ptr<Parser> get_parser(std::string name) const;

    virtual bool parse(std::vector<std::string> arguments) = 0;
    virtual bool execute(std::map<std::string, std::string> args) const = 0;

    const std::string &get_description() const;
    const std::string &get_help() const;
    const std::map<std::string, std::shared_ptr<Parser>> &get_parsers() const;
    bool show_in_help() const;
};

#endif /* __CMDLINE_PARSER_H */