#include "Acceptor.hpp"

Acceptor::Acceptor(boost::asio::io_service& io_service): acceptor_(io_service), state(0) {}

void Acceptor::open() {
    std::cout << "open" << std::endl;
}

void Acceptor::close() {
    std::cout << "close" << std::endl;
}
void Acceptor::listen() {
    std::cout << "listen" << std::endl;
}
void Acceptor::setOption(int option) {
    std::cout << "option is " << option << std::endl;
}