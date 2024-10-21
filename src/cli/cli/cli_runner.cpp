#include <regex>
#include "cli_runner.h"

#include "../parser/exceptions.h"

std::shared_ptr<ds::PlatformObjectFactory> CLIRunner::_factory = nullptr;

CLIRunner::CLIRunner(std::shared_ptr<ArgumentedCommandParser> parser,
                     const std::string prompt)
    : _parser(parser), _prompt(prompt)
{
    if (_factory == nullptr)
        throw std::runtime_error(
            "PlatformObjectFactory not set for the CLIRunner class");
}

void CLIRunner::set_factory(std::shared_ptr<ds::PlatformObjectFactory> factory)
{
    _factory = factory;
}

void CLIRunner::set_prompt(const std::string prompt)
{
    _prompt = prompt;
}

std::vector<std::string> CLIRunner::split_command_line(const std::string& command_line) const
{
    std::vector<std::string> words;
    std::regex word_regex(R"((\"[^\"]+\"|\S+))");
    auto words_begin = std::sregex_iterator(command_line.begin(), command_line.end(), word_regex);
    auto words_end = std::sregex_iterator();
    
    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        std::smatch match = *i;
        std::string match_str = match.str();

        // Remove quotes from the beginning and end of the string
        if (match_str.front() == '"' && match_str.back() == '"') 
        {
            match_str = match_str.substr(1, match_str.size() - 2);
        }

        words.push_back(match_str);
    }

    return words;
}

bool CLIRunner::run(bool prepend_with_hostname)
{
    const auto& output_handler = _factory->get_output_handler();
    const auto& input_handler = _factory->get_input_handler();

    std::string command = "";

    while (true)
    {
        std::string prompt = _prompt;
        if (prepend_with_hostname)
        {
            std::string hostname = _factory->get_configuration_manager()->get("sys.hostname");
            prompt = hostname + _prompt;
        }
        command = input_handler->get_string(prompt, command);

        const auto& words = split_command_line(command);

        output_handler->println();
        if (words.empty()) continue;

        // Parse
        try
        {
            bool retval = _parser->parse(words);
            if (command[command.length() - 1] == '?')
            {
                command = command.substr(0, command.length() - 1);
                continue;
            }
            return retval;
        }
        catch (const ParseException& e)
        {
            output_handler->println(e.what());
            return true;
        }
    }
}