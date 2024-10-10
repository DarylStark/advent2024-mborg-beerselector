#include <memory>
#include "../cli/model/cli_model.h"

//
// Global variables
//
// Globals are nasty. Avoid them if possible. But I still use them cause I
// didn't think ahead and didn't figure out a way to switch between CLI modes
// in the CLIRunner. I could have used a state machine, but to refactor it now
// would be too much work and there is a deadline. So I'm using globals.
//
// The next_parser is used to switch between CLI modes. The prompt is used to
// display the current mode in the CLI.
//

extern std::shared_ptr<ArgumentedCommandParser> next_parser;
extern std::string prompt;