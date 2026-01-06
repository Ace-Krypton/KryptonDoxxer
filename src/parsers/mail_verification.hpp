#pragma once
#include <string>

enum class email_status {
    valid,
    invalid_syntax,
    invalid_domain_format,
    domain_missing
};

struct email_verification {
    std::string normalized;
    email_status status;
    std::string reason;
};

auto verify_email(const std::string &input) -> email_verification;