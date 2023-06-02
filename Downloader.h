#ifndef PDF_DOWNLOADER_H
#define PDF_DOWNLOADER_H


#include <filesystem>
#include "PdfExtractor.h"

class Downloader {
public:
    explicit Downloader(std::filesystem::path root);

    std::filesystem::path download(std::string_view url);
    [[nodiscard]] const std::filesystem::path& path() const { return root_; }

private:
    std::filesystem::path root_{};
    PdfExtractor pdfExtractor_{};
};

#endif //PDF_DOWNLOADER_H
