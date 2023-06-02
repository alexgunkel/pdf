#include <iostream>
#include "PdfExtractor.h"
#include "RequestHandler.h"

#include <pistache/endpoint.h>

char *gFile;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 1;
    }
    gFile = argv[1];

    auto opts = Pistache::Http::Endpoint::options().flags(Pistache::Tcp::Options::ReusePort);
    Pistache::Http::listenAndServe<RequestHandler>(Pistache::Address("127.0.0.1:9080"), opts);

    try {
        PdfExtractor extractor;
        std::cout << extractor.parseFile(argv[1]);
    } catch (std::runtime_error& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }
    return 0;
}
