#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace utils {
    // Splits a string by a given delimiter.
    inline std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
}