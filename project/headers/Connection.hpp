#ifndef PROJECT_INCLUDE_CONNECTION_H_
#define PROJECT_INCLUDE_CONNECTION_H_

#include <iostream>
#include <vector>

template<class HandlerType>
class Connection {
public:
    Connection(HandlerType* handler) : requestHandler(handler) {}

    void start() {
        read();
    }

    void stop() {
        std::cout << "stop" << std::endl;
    }
private:
    std::vector<char> buffer;
    HandlerType* requestHandler;

    void read() {
        requestHandler->handleRequest();
    }

    void write() {
        std::cout << "write" << std::endl;
    }
};

#endif  //  PROJECT_INCLUDE_CONNECTION_H_