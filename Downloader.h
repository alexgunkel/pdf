#ifndef PDF_DOWNLOADER_H
#define PDF_DOWNLOADER_H


#include <filesystem>

class Downloader {
public:
    explicit Downloader(std::filesystem::path root);

    std::filesystem::path download(std::string_view url);

private:
    std::filesystem::path root_;
};

#endif //PDF_DOWNLOADER_H
