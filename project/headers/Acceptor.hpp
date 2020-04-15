#ifndef PROJECT_INCLUDE_ACCEPTOR_H_
#define PROJECT_INCLUDE_ACCEPTOR_H_

#include <iostream>

class Acceptor {
public:
    Acceptor();
    void open();
    void close();
    void listen();
    void setOption(int option);
private:
    int state;
};

#endif  //  PROJECT_INCLUDE_ACCEPTOR_H_