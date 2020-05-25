//
// Created by ivan on 4/15/20.
//

#include <iostream>
#include "boost/asio.hpp"

#include "Acceptor.hpp"
#include "Server.hpp"

int main() {
    int port = 6666;
    boost::asio::io_service ioService;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);

    Acceptor acceptor(ioService, endpoint);

    Server<Acceptor> server(ioService, &acceptor);
    server.run(port);
    server.startAccept();
    ioService.run();
}
