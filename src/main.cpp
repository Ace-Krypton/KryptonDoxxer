#include "collectors/paste_collector.hpp"
#include "parsers/mail_verification.hpp"
#include "parsers/pattern_scanner.hpp"
#include "output/json_writer.hpp"
#include <iostream>
#include <string>

auto main(const int argc, char** argv) -> int {
    if (argc != 3) {
        std::cerr << "Usage: kryptondoxxer <email> <url>\n";
        return 1;
    }

    const auto [normalized, status, reason] = verify_email(argv[1]);

    std::cout << "Email: " << normalized << '\n';
    std::cout << "Status: ";

    switch (status) {
        case email_status::valid: std::cout << "valid"; break;
        case email_status::invalid_syntax: std::cout << "invalid syntax"; break;
        case email_status::invalid_domain_format: std::cout << "invalid domain format"; break;
        case email_status::domain_missing: std::cout << "domain missing"; break;
    }

    std::cout << "\nReason: " << reason << '\n';

    if (status != email_status::valid) return 3;

    const std::string url{argv[2]};
    const auto text = collect_paste(url);

    if (text.empty()) {
        std::cerr << "Failed to fetch content from " << url << '\n';
        return 2;
    }

    const auto hits = scan_patterns(text);
    write_json(url, hits);

    return 0;
}
