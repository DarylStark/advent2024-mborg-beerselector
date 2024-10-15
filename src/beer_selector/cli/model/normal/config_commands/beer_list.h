#ifndef BEERLIST_H
#define BEERLIST_H

#include "../../../../../cli/command/command.h"

class BeerListSetTimeOut : public Command
{
public:
    bool execute(std::map<std::string, std::string> args) override;
};

#endif /* BEERLIST_H */