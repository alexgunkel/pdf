#ifndef PDF_PDFEXTRACTOR_H
#define PDF_PDFEXTRACTOR_H


#include <memory>
#include <string_view>
#include <stdexcept>

class PdfExtractor {
    struct config;
    std::unique_ptr<config> _cfg;
public:
    PdfExtractor();
    ~PdfExtractor();
    [[nodiscard]] std::string parseFile(std::string_view fileName) const;

class NoValidPdf : public std::runtime_error {
public:
    explicit NoValidPdf(const std::string& msg): std::runtime_error(msg) {}
};
};


#endif //PDF_PDFEXTRACTOR_H
