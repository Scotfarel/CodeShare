#include "Acceptor.hpp"

    Acceptor::Acceptor() {
        state = 0;
    }

    void Acceptor::open() {
        std::cout << "open" << std::endl;
    }
    void Acceptor::close() {
        std::cout << "close" << std::endl;
    }
    void Acceptor::listen() {
        std::cout << "listen" << std::endl;
    }
    void Acceptor::setOption() {
        std::cout << "setOption" << std::endl;
    }