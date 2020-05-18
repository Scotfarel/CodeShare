#ifndef PROJECT_INCLUDE_CONNECTION_H_
#define PROJECT_INCLUDE_CONNECTION_H_

#include <iostream>
#include <vector>

template<class HandlerType>
class Connection {
public:
    Connection(HandlerType* handler, boost::asio::io_service& ioService) : requestHandler(handler), socket_(ioService) {}

    void start() {
        read();
    }

    void stop() {
        std::cout << "stop" << std::endl;
    }

    boost::asio::ip::tcp::socket& getSocket() {
        return socket_;
    }
private:
    std::vector<char> buffer;
    HandlerType* requestHandler;
    boost::asio::ip::tcp::socket socket_;

    void read() {
        requestHandler->handleRequest(0);
    }

    void write() {
        std::cout << "write" << std::endl;
    }
};

#endif  //  PROJECT_INCLUDE_CONNECTION_H_