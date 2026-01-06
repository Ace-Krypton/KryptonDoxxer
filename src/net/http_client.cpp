#include "http_client.hpp"
#include <curl/curl.h>
#include <stdexcept>

static auto write_cb(const char* ptr, size_t size, size_t nmemb, void* userdata) -> size_t {
    auto* out = static_cast<std::string*>(userdata);
    out->append(ptr, size * nmemb);
    return size * nmemb;
}

auto http_get(const std::string& url, const http_headers& headers) -> http_response {
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("curl init failed");
    }

    std::string body;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);

    curl_slist* header_list = nullptr;
    for (const auto& [key, value] : headers) {
        const std::string header = key + ": " + value;
        header_list = curl_slist_append(header_list, header.c_str());
    }

    if (header_list) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
    }

    const CURLcode res = curl_easy_perform(curl);

    long status = 0;
    if (res != CURLE_OK) {
        if (header_list) curl_slist_free_all(header_list);
        curl_easy_cleanup(curl);
        throw std::runtime_error(curl_easy_strerror(res));
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);

    if (header_list) {
        curl_slist_free_all(header_list);
    }

    curl_easy_cleanup(curl);

    return { status, body };
}
