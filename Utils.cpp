#include "Utils.h"
#include <sstream>
#include <cctype>

namespace Utils {
    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    bool is_number(const std::string& s) {
        if (s.empty()) return false;
        for (char c : s) {
            if (!std::isdigit(c)) return false;
        }
        return true;
    }
}
