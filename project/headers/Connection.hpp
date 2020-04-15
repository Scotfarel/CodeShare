#ifndef PROJECT_INCLUDE_CONNECTION_H_
#define PROJECT_INCLUDE_CONNECTION_H_

#include <iostream>
#include <vector>

class Connection {
public:
    Connection();
    void start();
    void stop();
private:
    std::vector<char> buffer;
    void read();
    void write();
};

#endif  //  PROJECT_INCLUDE_CONNECTION_H_