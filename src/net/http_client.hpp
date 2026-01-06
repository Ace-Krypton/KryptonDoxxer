#pragma once
#include <string>
#include <vector>

using http_headers = std::vector<std::pair<std::string, std::string>>;

struct http_response {
    long status;
    std::string body;
};

auto http_get(const std::string& url, const http_headers& headers) -> http_response;