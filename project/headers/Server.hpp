#ifndef PROJECT_INCLUDE_SERVER_H_
#define PROJECT_INCLUDE_SERVER_H_

#include <iostream>
#include "Acceptor.hpp"
#include "Connection.hpp"
#include "RequestHandler.hpp"
#include "RoomScheduler.hpp"

template<class AcceptorType>
class Server {
public:
    Server(boost::asio::io_service* ioService, AcceptorType* acceptor) : 
        ioService(ioService),
        acceptor_(acceptor),
        roomScheduler(),
        newConnection(),
        requestHandler(&roomScheduler) {}

    void run() {
        acceptor_->open();
        acceptor_->setOption(true);
        acceptor_->listen();

        ioService->run();
    }

    void startAccept() {
        newConnection.reset(new Connection<RequestHandler<RoomScheduler> >(&requestHandler));
    }

private:
    boost::asio::io_service* ioService;
    AcceptorType* acceptor_;
    RoomScheduler roomScheduler;
    std::shared_ptr<Connection<RequestHandler<RoomScheduler> > > newConnection;
    RequestHandler<RoomScheduler> requestHandler;
};

#endif  //  PROJECT_INCLUDE_SERVER_H_