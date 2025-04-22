#include "CommandParser.h"
#include <iostream>
#include <string>

int main() {
    CommandParser parser;
    std::string line;

    while (std::getline(std::cin, line)) {
        std::string response = parser.parse_and_execute(line);
        std::cout << response;
        if (line == "exit") {
            break;
        }
    }

    return 0;
}
