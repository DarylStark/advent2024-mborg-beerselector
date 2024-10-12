#include "beerlist_parsers.h"
#include "commands/show_beerlist.h"

std::shared_ptr<ArgumentedCommandParser> ShowBeerList::_parser = nullptr;

std::shared_ptr<ArgumentedCommandParser>
ShowBeerList::_create_parser()
{
    // Parser for the ROMMON mode
    std::shared_ptr<ArgumentedCommandParser> parser =
        std::make_shared<ArgumentedCommandParser>(
            "Show the beer-list",
            "Show the beer-list",
            std::make_shared<ShowBeerListCmd>());

    return parser;
}

std::shared_ptr<ArgumentedCommandParser> ShowBeerList::get_parser()
{
    if (!_parser) _parser = _create_parser();
    return _parser;
}