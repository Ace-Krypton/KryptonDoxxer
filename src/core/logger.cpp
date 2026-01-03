#include "logger.hpp"

#include <iostream>
#include <ostream>

void log(log_level level, const std::string &msg) {
    const char *prefix =
        level == log_level::INFO  ? "[INFO] " :
        level == log_level::WARN  ? "[WARN] " :
                                   "[ERROR] ";

    std::cerr << prefix << msg << '\n';
}
