#pragma once
#include "../output/json_writer.hpp"
#include <string>
#include <vector>

auto scan_patterns(const std::string &text) -> std::vector<finding>;