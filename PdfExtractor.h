#ifndef PDF_PDFEXTRACTOR_H
#define PDF_PDFEXTRACTOR_H


#include <memory>

class PdfExtractor {
    struct config;
    std::unique_ptr<config> _cfg;
public:
    PdfExtractor();
    ~PdfExtractor();
    std::string parseFile(char *fileName) const;
};


#endif //PDF_PDFEXTRACTOR_H
