#include "Acceptor.hpp"

Acceptor::Acceptor(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint): endpoint(endpoint), acceptor_(io_service) {}

void Acceptor::open() {
    acceptor_.open(endpoint.protocol());
}

void Acceptor::close() {
    acceptor_.close();
}

void Acceptor::listen() {
    acceptor_.listen();
}
void Acceptor::setOption(int option) {
    std::cout << "option is " << option << std::endl;
}