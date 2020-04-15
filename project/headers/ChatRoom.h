//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_CHATROOM_H
#define CODESHARE_CHATROOM_H

#include <string>

#include <MongoConnector.h>

class ChatRoom {
public:
    ChatRoom();
    std::string getText();
    std::string addUser();

private:
    std::string sharedText;
    bool createDbTask();

protected:
    std::string roomUUID;

};

#endif //CODESHARE_CHATROOM_H
