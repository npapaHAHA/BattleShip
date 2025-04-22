#include "CommandParser.h"

CommandParser::CommandParser() {}

std::string CommandParser::parse_and_execute(const std::string& input) {
    return game_.process_command(input);
}
