#ifndef CLI_RUNNER_H
#define CLI_RUNNER_H

#include <iterator>
#include <memory>
#include <sstream>

#include "../../cli/parser/argumented_command_parser.h"
#include "../../ds/platform_object_factory.h"

class CLIRunner
{
protected:
    static std::shared_ptr<ds::PlatformObjectFactory> _factory;

private:
    std::shared_ptr<ArgumentedCommandParser> _parser;
    std::string _prompt;

public:
    CLIRunner(std::shared_ptr<ArgumentedCommandParser> parser,
              const std::string prompt);
    static void set_factory(std::shared_ptr<ds::PlatformObjectFactory> factory);
    void set_prompt(const std::string prompt);
    bool run();
};

#endif /* CLI_RUNNER_H */