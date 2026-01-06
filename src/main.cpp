// main.cpp
#include "collectors/paste_collector.hpp"
#include "parsers/mail_verification.hpp"
#include "parsers/pattern_scanner.hpp"
#include "output/json_writer.hpp"
#include "search/search.hpp"
#include <iostream>
#include <string>

auto main(const int argc, char** argv) -> int {
    if (argc != 3) {
        std::cerr << "Usage: kryptondoxxer <email> <url>\n";
        return 1;
    }

    const auto [normalized, status, reason] = verify_email(argv[1]);
    if (status != email_status::valid) return 3;

    const std::string url{argv[2]};
    if (const auto text = collect_paste(url); text.empty()) return 2;

    // const auto scan_hits = scan_patterns(text);
    // write_json(url, scan_hits);

    const auto search_hits = search_email(normalized);
    write_json("email_search", search_hits);

    return 0;
}
