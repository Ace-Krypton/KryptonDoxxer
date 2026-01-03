#include "paste_collector.hpp"
#include "../net/http_client.hpp"

auto collect_paste(const std::string &url) -> std::string {
    auto [status, body] = http_get(url);
    if (status != 200) return {};
    return body;
}
