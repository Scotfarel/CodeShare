//
// Created by mihail on 15.04.2020.
//

#ifndef CODESHARE_CONNECTIONHANDLER_H
#define CODESHARE_CONNECTIONHANDLER_H


class ConnectionHandler {
public:
    ConnectionHandler();

    bool createRoom();
    bool connectToRoom(int id);
    bool receiveText();
};



#endif //CODESHARE_CONNECTIONHANDLER_H
