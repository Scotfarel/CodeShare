#include "Server.h"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint)
    : acceptor(io_service, endpoint), clientCounter(0) {

    startAccept();
}

void Server::startAccept() {
    std::cout << "Waiting for clients..." << std::endl;
    acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::shared_ptr<Connection> newConnection = std::make_shared<Connection>(std::move(socket));
            ConnectionManager<Connection>::getInstance().start(newConnection, clientCounter++);
            startAccept();
        }
    });
}
