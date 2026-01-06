#include "mail_verification.hpp"
#include <algorithm>
#include <cctype>
#include <regex>
#include <string>
#include <netdb.h>

static auto to_lower(std::string str) -> std::string {
    std::ranges::transform(str, str.begin(),
        [](const unsigned char c) {
            return static_cast<char>(std::tolower(c));
        }
    );
    return str;
}

static auto trim(std::string str) -> std::string {
    str.erase(
        str.begin(),
        std::ranges::find_if(str,
            [](const unsigned char c) {
            return !std::isspace(c);
        })
    );

    str.erase(
        std::ranges::find_if(str.rbegin(), str.rend(),
            [](const unsigned char c) {
            return !std::isspace(c);
        }).base(),
        str.end()
    );

    return str;
}

static auto domain_resolves(const std::string &domain) -> bool {
    addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    addrinfo *res = nullptr;

    if (const int rc = getaddrinfo(domain.c_str(),
        nullptr, &hints, &res); rc == 0) {
        freeaddrinfo(res);
        return true;
    }

    return false;

}

auto verify_email(const std::string& input) -> email_verification {
    const std::string email = trim(to_lower(input));

    static const std::regex syntax(
        R"(^[a-z0-9._%+\-]+@[a-z0-9.\-]+\.[a-z]{2,}$)",
        std::regex::icase
    );

    if (!std::regex_match(email, syntax)) {
        return {
            email,
            email_status::invalid_syntax,
            "invalid email syntax"
        };
    }

    const auto at = email.find('@');
    const std::string domain = email.substr(at + 1);

    static const std::regex domain_re(
        R"(^[a-z0-9\-]+(\.[a-z0-9\-]+)+$)",
        std::regex::icase
    );

    if (!std::regex_match(domain, domain_re)) {
        return {
            email,
            email_status::invalid_domain_format,
            "invalid domain format"
        };
    }

    if (!domain_resolves(domain)) {
        return {
            email,
            email_status::domain_missing,
            "domain does not resolve"
        };
    }

    return {
        email,
        email_status::valid,
        "email is syntactically and domain valid"
    };
}
