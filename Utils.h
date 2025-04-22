#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace Utils {
    std::vector<std::string> split(const std::string& str, char delimiter = ' ');
    bool is_number(const std::string& s);
}

#endif
