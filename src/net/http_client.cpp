#include "http_client.hpp"
#include <curl/curl.h>
#include <stdexcept>

static auto write_cb(const char *ptr, const size_t size, const size_t nmemb, void *userdata) -> size_t {
    auto *out = static_cast<std::string*>(userdata);
    out->append(ptr, size * nmemb);
    return size * nmemb;
}

auto http_get(const std::string& url) -> http_response {
    CURL *curl = curl_easy_init();
    if (!curl) { throw std::runtime_error("curl init failed"); }

    std::string body;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);

    if (const CURLcode res = curl_easy_perform(curl); res != CURLE_OK)
        { throw std::runtime_error(curl_easy_strerror(res)); }

    long status;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
    curl_easy_cleanup(curl);

    return { status, body };
}
