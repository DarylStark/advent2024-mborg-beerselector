#ifndef BEERLIST_PARSERS_H
#define BEERLIST_PARSERS_H

#include "../../../../../cli/model/cli_model.h"

class ShowBeerList : public CLIParserFactory
{
private:
    static std::shared_ptr<ArgumentedCommandParser> _parser;

    std::shared_ptr<ArgumentedCommandParser> _create_parser();

public:
    std::shared_ptr<ArgumentedCommandParser> get_parser();
};

#endif /* BEERLIST_PARSERS_H */