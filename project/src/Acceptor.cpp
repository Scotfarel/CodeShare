#include "Acceptor.hpp"

Acceptor::Acceptor(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint): endpoint(endpoint), acceptor_(io_service) {}

void Acceptor::open() {
    acceptor_.open(endpoint.protocol());
}

void Acceptor::close() {
    acceptor_.close();
}

void Acceptor::bind() {
    acceptor_.bind(endpoint);
}

void Acceptor::listen() {
    acceptor_.listen();
}

void Acceptor::setOption(bool reuseAddress) {
    boost::asio::ip::tcp::acceptor::reuse_address option(reuseAddress);
    acceptor_.set_option(option);
}

boost::asio::ip::tcp::acceptor&Acceptor::origin() {
    return acceptor_;
}
