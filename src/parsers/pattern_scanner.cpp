#include "pattern_scanner.hpp"
#include <regex>

auto scan_patterns(const std::string &text) -> std::vector<finding> {
    std::vector<finding> hits;
    const std::regex email(R"([\w\.-]+@[\w\.-]+\.\w+)");

    for (auto it = std::sregex_iterator(text.begin(), text.end(), email);
        it != std::sregex_iterator(); ++it) {
        hits.push_back({
            "email",
            it->str()
        });
    }

    return hits;
}
