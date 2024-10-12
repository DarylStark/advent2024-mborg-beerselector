#ifndef SHOW_BEERLIST_H
#define SHOW_BEERLIST_H

#include "../../../../../../cli/command/command.h"

class ShowBeerListCmd : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* SHOW_BEERLIST_H */