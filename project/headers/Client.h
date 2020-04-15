//
// Created by mihail on 15.04.2020.
//

#ifndef CODESHARE_CLIENT_H
#define CODESHARE_CLIENT_H


#include "ConnectionHandler.h"
#include "GUI.h"

class Client {
public:
    Client();
    bool run();
private:
    ConnectionHandler connect;
    GUI frame;
};


#endif //CODESHARE_CLIENT_H
