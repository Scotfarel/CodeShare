#ifndef PROJECT_INCLUDE_ACCEPTOR_H_
#define PROJECT_INCLUDE_ACCEPTOR_H_

#include <iostream>
#include <boost/asio.hpp>

class Acceptor {
public:
    Acceptor(boost::asio::io_service& io_service);
    void open();
    void close();
    void listen();
    void setOption(int option);
private:
    int state;
    boost::asio::ip::tcp::acceptor acceptor_; 
};

#endif  //  PROJECT_INCLUDE_ACCEPTOR_H_