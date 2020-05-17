#ifndef PROJECT_INCLUDE_SERVER_H_
#define PROJECT_INCLUDE_SERVER_H_

#include <iostream>
#include "Acceptor.hpp"

template<class AcceptorType>
class Server {
public:
    Server(boost::asio::io_service* ioService, AcceptorType* acceptor) : ioService(ioService), acceptor_(acceptor) {}

    void run() {
        acceptor_->setOption(true);
        acceptor_->open();
        acceptor_->listen();

        ioService->run();
    }
private:
    boost::asio::io_service* ioService;
    AcceptorType* acceptor_;
};

#endif  //  PROJECT_INCLUDE_SERVER_H_