#ifndef ARGUMENTED_COMMAND_PARSER_H
#define ARGUMENTED_COMMAND_PARSER_H

#include "../command/command.h"
#include "argument.h"
#include "parser.h"

class ArgumentedCommandParser : public Parser
{
private:
    std::vector<std::shared_ptr<Argument>> _arguments;
    uint32_t _required_arguments;
    std::shared_ptr<Command> _command;

public:
    ArgumentedCommandParser(const std::string description = std::string(""),
                            const std::string help = std::string(""),
                            std::shared_ptr<Command> command = nullptr,
                            bool add_helper = true, bool show_in_help = true);
    virtual bool parse(std::vector<std::string> arguments) override;
    virtual bool execute(std::map<std::string, std::string> args) const;
    void add_argument(std::shared_ptr<Argument> argument);
    const std::vector<std::shared_ptr<Argument>> &get_argumentes() const;
};

#endif /* ARGUMENTED_COMMAND_PARSER_H */
