#ifndef PROJECT_INCLUDE_ACCEPTOR_H_
#define PROJECT_INCLUDE_ACCEPTOR_H_

#include <iostream>
#include <boost/asio.hpp>

class Acceptor {
public:
    Acceptor(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint);
    void open();
    void close();
    void listen();
    void setOption(bool reuseAddress);
private:
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::ip::tcp::acceptor acceptor_;
};

#endif  //  PROJECT_INCLUDE_ACCEPTOR_H_