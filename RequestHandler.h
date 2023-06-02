//
// Created by alexander on 02.06.23.
//

#ifndef PDF_REQUESTHANDLER_H
#define PDF_REQUESTHANDLER_H


#include <filesystem>
#include "pistache/http.h"
#include "Downloader.h"

class RequestHandler : public Pistache::Http::Handler {
public:
    RequestHandler(): downloader_{std::make_shared<Downloader>("/tmp")} {};
HTTP_PROTOTYPE(RequestHandler)
    void onRequest(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter writer) override ;
private:
    std::shared_ptr<Downloader> downloader_{};
};


#endif //PDF_REQUESTHANDLER_H
