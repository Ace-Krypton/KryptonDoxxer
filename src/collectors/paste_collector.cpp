#include "paste_collector.hpp"
#include "../net/http_client.hpp"

auto collect_paste(const std::string& url) -> std::string {
    const http_headers headers{
            {"User-Agent", "KryptonDoxxer/1.0"}
    };

    const auto [status, body] = http_get(url, headers);
    if (status != 200) {
        return {};
    }

    return body;
}
