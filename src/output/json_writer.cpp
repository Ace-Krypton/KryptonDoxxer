#include "json_writer.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

auto write_json(const std::string &source, std::vector<std::string> &hits) -> void {
    nlohmann::json json;
    json["source"] = source;
    json["matches"] = hits;

    std::cout << json.dump(2) << '\n';
}
