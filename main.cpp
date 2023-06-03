#include "RequestHandler.h"

#include <pistache/endpoint.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 1;
    }

    auto server = std::make_shared<Pistache::Http::Endpoint>(
            Pistache::Address(Pistache::Ipv4::any(), Pistache::Port(9080)));

    auto opts = Pistache::Http::Endpoint::options().flags(Pistache::Tcp::Options::ReusePort);
    server->init(opts);
    server->setHandler(std::make_shared<RequestHandler>(std::filesystem::path{argv[1]}));
    server->serve();

    return 0;
}
