#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include "Game.h"
#include <string>

class CommandParser {
public:
    CommandParser();
    std::string parse_and_execute(const std::string& input);

private:
    Game game_;
};

#endif
