//
// Created by alexander on 02.06.23.
//

#ifndef PDF_REQUESTHANDLER_H
#define PDF_REQUESTHANDLER_H


#include <filesystem>
#include "pistache/http.h"
#include "PdfExtractor.h"

class RequestHandler : public Pistache::Http::Handler {
public:
    RequestHandler(): pdfExtractor_{std::make_shared<PdfExtractor>()} {};
HTTP_PROTOTYPE(RequestHandler)
    void onRequest(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter writer) override ;
private:
    std::shared_ptr<PdfExtractor> pdfExtractor_{};
};


#endif //PDF_REQUESTHANDLER_H
