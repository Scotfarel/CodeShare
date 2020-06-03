#include "Server.h"

int main(int argc, char* argv[]) {
    boost::asio::io_service io_service;
    tcp::endpoint endpoint(tcp::v4(), std::atoi("63506"));
    Server server(io_service, endpoint);
    io_service.run();

    return 0;
}
