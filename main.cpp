#include <iostream>
#include "PdfExtractor.h"
#include <filesystem>

#include <pistache/endpoint.h>

char *gFile;

struct HelloHandler : public Pistache::Http::Handler {
    HelloHandler(): pdfExtractor_{std::make_shared<PdfExtractor>()} {};
    HTTP_PROTOTYPE(HelloHandler)
    void onRequest(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter writer) override {
        const auto& resource = request.resource();
        auto p = std::filesystem::path(resource);
        if (!is_regular_file(p)) {
            writer.send(Pistache::Http::Code::Not_Found);
            return;
        }

        auto rel = std::filesystem::relative(p, "/home/alexander/Dokumente/OParl");
        if (rel.empty() || rel.native()[0] == '.') {
            writer.send(Pistache::Http::Code::Forbidden);
            return;
        }
        writer.headers().add<Pistache::Http::Header::ContentType>("text/plain; charset=utf-8");
        writer.send(Pistache::Http::Code::Ok, pdfExtractor_->parseFile(resource));
    }
private:
    std::shared_ptr<PdfExtractor> pdfExtractor_{};
};

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 1;
    }
    gFile = argv[1];

    auto opts = Pistache::Http::Endpoint::options().flags(Pistache::Tcp::Options::ReusePort);
    Pistache::Http::listenAndServe<HelloHandler>(Pistache::Address("127.0.0.1:9080"), opts);

    try {
        PdfExtractor extractor;
        std::cout << extractor.parseFile(argv[1]);
    } catch (std::runtime_error& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }
    return 0;
}
