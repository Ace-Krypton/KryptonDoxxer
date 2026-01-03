#pragma once
#include <string>

struct http_response {
    long status;
    std::string body;
};

auto http_get(const std::string& url) -> http_response;