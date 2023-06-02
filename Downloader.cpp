#include "Downloader.h"
#include "PdfExtractor.h"

#include <curl/curl.h>
#include <utility>

namespace {
    size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
        size_t written = fwrite(ptr, size, nmemb, stream);
        return written;
    }
}

Downloader::Downloader(std::filesystem::path root): root_{std::move(root)} {
    if (!is_directory(root_)) {
        throw std::runtime_error("root must be a directory");
    }
}

std::filesystem::path Downloader::download(std::string_view url) {
    CURL *curl;
    FILE *fp;
    auto out = root_;
    out.append("test-file.pdf");
    curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error{"unable to initialize curl"};
    }
    fp = fopen(out.c_str(), "wb");
    curl_easy_setopt(curl, CURLOPT_URL, url.data());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(fp);

    auto content = pdfExtractor_.parseFile(out.generic_string());

    return content;
}
