#include "json_writer.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

auto write_json(const std::string &source, const std::vector<finding> &hits) -> void {
    nlohmann::json json;
    json["source"] = source;
    json["findings"] = nlohmann::json::array();

    for (const auto &[type, value] : hits) {
        json["findings"].push_back({
                {"type", type},
                {"value", value}
        });
    }

    std::cout << json.dump(2) << '\n';
}
