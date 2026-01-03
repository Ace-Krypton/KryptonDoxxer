#pragma once
#include <string>

enum class log_level {INFO, WARN, ERROR};

void log(log_level level, const std::string &msg);