#pragma once
#include <string>

enum class log_level {INFO, WARN, ERROR};

//this is a test123
auto log(log_level level, const std::string &msg) -> void;