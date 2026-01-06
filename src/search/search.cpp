#include "search.hpp"
#include "../net/http_client.hpp"
#include <vector>
#include <string>

auto search_email(const std::string& email) -> std::vector<finding> {
    std::vector<finding> results;

    const std::string url =
        "https://haveibeenpwned.com/api/v3/breachedaccount/" + email;

    const http_headers headers{
            {"hibp-api-key", "00000000000000000000000000000000"},
            {"User-Agent", "KryptonDoxxer/1.0 (contact@example.com)"}
    };

    switch (const auto [status, body] = http_get(url, headers); status) {
        case 200:
            results.push_back({
                "hibp_breach",
                email
            });
            break;

        case 404: std::cout << "404" << std::endl; break;
        case 401: std::cout << "401" << std::endl; break;
        case 403: std::cout << "403" << std::endl; break;
        case 429: std::cout << "429" << std::endl; break;
        default: std::cout << "default" << std::endl; break;
    }

    return results;
}
