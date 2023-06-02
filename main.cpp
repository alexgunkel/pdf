#include <iostream>
#include "PdfExtractor.h"
#include "RequestHandler.h"

#include <pistache/endpoint.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 1;
    }

    auto opts = Pistache::Http::Endpoint::options().flags(Pistache::Tcp::Options::ReusePort);
    Pistache::Http::listenAndServe<RequestHandler>(Pistache::Address("127.0.0.1:9080"), opts);
    return 0;
}
