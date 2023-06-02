#include "RequestHandler.h"

void RequestHandler::onRequest(const Pistache::Http::Request &request, Pistache::Http::ResponseWriter writer) {
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
