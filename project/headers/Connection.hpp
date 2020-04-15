#ifndef PROJECT_INCLUDE_CONNECTION_H_
#define PROJECT_INCLUDE_CONNECTION_H_

#include "RequestHandler.hpp"
#include <iostream>
#include <vector>

class Connection {
public:
    Connection(RequestHandler handler = RequestHandler());
    void start();
    void stop();
private:
    std::vector<char> buffer;
    RequestHandler requestHandler;
    void read();
    void write();
};

#endif  //  PROJECT_INCLUDE_CONNECTION_H_