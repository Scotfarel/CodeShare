#ifndef PROJECT_INCLUDE_SERVER_H_
#define PROJECT_INCLUDE_SERVER_H_

#include <iostream>
#include <boost/asio.hpp>

#include "ConnectionManager.h"

using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint);
private:
    tcp::acceptor acceptor;
    int clientCounter;

    void startAccept();
};


#endif  //  PROJECT_INCLUDE_SERVER_H_
