#ifndef PDF_REQUESTHANDLER_H
#define PDF_REQUESTHANDLER_H

#include <filesystem>
#include <utility>
#include "pistache/http.h"
#include "Downloader.h"

class RequestHandler : public Pistache::Http::Handler {
public:
    RequestHandler(): extractor_{std::make_shared<PdfExtractor>()} {};
    explicit RequestHandler(std::filesystem::path root): extractor_{std::make_shared<PdfExtractor>()}, root_{std::move(root)} {};
HTTP_PROTOTYPE(RequestHandler)
    void onRequest(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter writer) override ;
private:
    std::shared_ptr<PdfExtractor> extractor_{};
    std::filesystem::path root_;
};

#endif //PDF_REQUESTHANDLER_H
