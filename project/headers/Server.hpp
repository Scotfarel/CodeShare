#ifndef PROJECT_INCLUDE_SERVER_H_
#define PROJECT_INCLUDE_SERVER_H_

#include <iostream>
#include "Acceptor.hpp"

template<class AcceptorType>
class Server {
public:
    Server(AcceptorType* acceptor) : acceptor_(acceptor) {}
    void run() {
        acceptor_->setOption(true);
        acceptor_->open();
        acceptor_->listen();
    }
private:
    AcceptorType* acceptor_;
};

#endif  //  PROJECT_INCLUDE_SERVER_H_