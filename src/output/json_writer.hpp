#pragma once
#include <string>
#include <vector>

struct finding {
    std::string type;
    std::string value;
};

auto write_json(const std::string &source,
    const std::vector<finding> &hits) -> void;