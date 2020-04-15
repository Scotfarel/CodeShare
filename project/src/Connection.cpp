#include "Connection.hpp"

Connection::Connection(RequestHandler handler) : requestHandler(handler) {}

void Connection::start() {
    std::cout << "start" << std::endl;
}

void Connection::stop() {
    std::cout << "stop" << std::endl;
}

void Connection::read() {
    std::cout << "read" << std::endl;
    requestHandler.handleRequest();
}

void Connection::write() {
    std::cout << "write" << std::endl;
}