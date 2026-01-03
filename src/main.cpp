#include "collectors/paste_collector.hpp"
#include "parsers/pattern_scanner.hpp"
#include "output/json_writer.hpp"
#include <iostream>
#include <string>

auto main(int argc, char** argv) -> int {
    if (argc < 2) {
        std::cerr << "Usage: kryptondoxxer <url>\n";
        return 1;
    }

    const std::string url{argv[1]};
    const auto text = collect_paste(url);

    if (text.empty()) {
        std::cerr << "Failed to fetch content from " << url << '\n';
        return 2;
    }

    const auto hits = scan_patterns(text);
    write_json(url, hits);

    return 0;
}
