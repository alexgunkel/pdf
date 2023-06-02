#include "RequestHandler.h"

void RequestHandler::onRequest(const Pistache::Http::Request &request, Pistache::Http::ResponseWriter writer) {
    const auto& resource = request.resource();
    auto p = std::filesystem::path(resource);

    auto rel = std::filesystem::relative(p, "/tmp");
    if (rel.empty() || rel.native()[0] == '.') {
        writer.send(Pistache::Http::Code::Forbidden);
        return;
    }

    auto status{Pistache::Http::Code::Found};
    std::string body{};

    try {
        if (!std::filesystem::exists(p) && request.method() == Pistache::Http::Method::Get) {
            writer.send(Pistache::Http::Code::Not_Found);
            return;
        }

        if (!std::filesystem::exists(p) || request.method() == Pistache::Http::Method::Put) {
            Downloader::download(request.body(), p);
            status = Pistache::Http::Code::Ok;
        }

        body = extractor_->parseFile(p.generic_string());
    } catch (std::exception& ex) {
        status = Pistache::Http::Code::Internal_Server_Error;
        std::cerr << ex.what() << std::endl;
    }

    writer.headers().add<Pistache::Http::Header::ContentType>("text/plain; charset=utf-8");
    writer.send(status, body);
}
