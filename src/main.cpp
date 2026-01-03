#include "collectors/paste_collector.hpp"
#include "parsers/pattern_scanner.hpp"
#include "output/json_writer.hpp"
#include <iostream>

auto main(const int argc, char** argv) -> int {
    if (argc < 2) {
        std::cerr << "Usage: kryptondoxxer <url>\n";
        return 1;
    }

    const auto text = collect_paste(argv[1]);
    auto hits = scan_patterns(text);
    write_json(argv[1], hits);
}
