cmake_minimum_required(VERSION 3.26)
project(KryptonDoxxer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(kryptondoxxer
        src/main.cpp
        src/core/logger.cpp
        src/core/logger.hpp
        src/net/http_client.cpp
        src/net/http_client.hpp
        src/collectors/paste_collector.cpp
        src/collectors/paste_collector.hpp
        src/parsers/pattern_scanner.cpp
        src/parsers/pattern_scanner.hpp
        src/output/json_writer.cpp
        src/output/json_writer.hpp
        src/parsers/mail_verification.cpp
        src/parsers/mail_verification.hpp
        src/search/search.cpp
        src/search/search.hpp
)

# --- libcurl ---
find_package(CURL REQUIRED)

# --- nlohmann/json ---
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(kryptondoxxer
        PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
)

target_include_directories(kryptondoxxer
        PRIVATE include
)