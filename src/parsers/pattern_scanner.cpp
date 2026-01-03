#include "pattern_scanner.hpp"
#include <regex>

auto scan_patterns(const std::string &text) -> std::vector<std::string> {
    std::vector<std::string> hits;
    const std::regex email(R"([\w\.-]+@[\w\.-]+\.\w+)");
    const std::regex key(R"(BEGIN\s+RSA\s+PRIVATE\s+KEY)");

    if (std::regex_search(text, email)) hits.emplace_back("email");
    if (std::regex_search(text, key)) hits.emplace_back("private_key");

    return hits;
}
