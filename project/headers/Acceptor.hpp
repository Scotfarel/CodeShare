#ifndef PROJECT_INCLUDE_ACCEPTOR_H_
#define PROJECT_INCLUDE_ACCEPTOR_H_

#include <iostream>

class Acceptor {
public:
    Acceptor();
    virtual ~Acceptor() = default;
    virtual void open();
    virtual void close();
    virtual void listen();
    virtual void setOption();
private:
    int state;
};

#endif  //  PROJECT_INCLUDE_ACCEPTOR_H_