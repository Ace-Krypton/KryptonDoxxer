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