#include "Connection.hpp"

Connection::Connection() {}

void Connection::start() {
    std::cout << "start" << std::endl;
}

void Connection::stop() {
    std::cout << "stop" << std::endl;
}

void Connection::read() {
    std::cout << "read" << std::endl;
}

void Connection::write() {
    std::cout << "write" << std::endl;
}