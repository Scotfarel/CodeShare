#ifndef PROJECT_INCLUDE_SERVER_H_
#define PROJECT_INCLUDE_SERVER_H_

#include <boost/bind.hpp>

#include <iostream>
#include "Acceptor.hpp"
#include "Connection.hpp"
#include "RequestHandler.hpp"
#include "RoomScheduler.hpp"
#include "ConnectionManager.hpp"

template<class AcceptorType>
class Server {
public:
    Server(boost::asio::io_service& ioService, AcceptorType* acceptor) : 
        ioService(ioService),
        acceptor_(acceptor),
        roomScheduler(),
        newConnection(),
        requestHandler(&roomScheduler),
        connectionManager() {}

    void run(int port) {
        acceptor_->open();
        acceptor_->setOption(true);
        acceptor_->bind();
        acceptor_->listen();
    }

    void startAccept() {
        newConnection.reset(new Connection<RequestHandler<RoomScheduler> >(&requestHandler, ioService));

        auto handler = boost::bind(&Server::handleAccept, this, boost::asio::placeholders::error);
        acceptor_->origin().async_accept(newConnection->getSocket(), handler);
    }

private:
    boost::asio::io_service& ioService;
    AcceptorType* acceptor_;
    RoomScheduler roomScheduler;
    std::shared_ptr<Connection<RequestHandler<RoomScheduler> > > newConnection;
    RequestHandler<RoomScheduler> requestHandler;
    ConnectionManager<Connection<RequestHandler<RoomScheduler> > > connectionManager;

    void handleAccept(const boost::system::error_code& error) {
        if (!error) {
            connectionManager.start(newConnection);
        }
        startAccept();
    }
};

#endif  //  PROJECT_INCLUDE_SERVER_H_