#ifndef PROJECT_INCLUDE_SERVER_H_
#define PROJECT_INCLUDE_SERVER_H_

#include <iostream>
#include "Acceptor.hpp"

template<class T>
class Server {
public:
    Server(T* acceptor) {
        acceptor_ = acceptor;
    }
    void run() {
        acceptor_->setOption(0);
        acceptor_->open();
        acceptor_->listen();
    }
private:
    T* acceptor_;
};

#endif  //  PROJECT_INCLUDE_SERVER_H_