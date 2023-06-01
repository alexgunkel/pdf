#ifndef PDF_PDFEXTRACTOR_H
#define PDF_PDFEXTRACTOR_H


#include <memory>
#include <string_view>

class PdfExtractor {
    struct config;
    std::unique_ptr<config> _cfg;
public:
    PdfExtractor();
    ~PdfExtractor();
    [[nodiscard]] std::string parseFile(std::string_view fileName) const;
};


#endif //PDF_PDFEXTRACTOR_H
