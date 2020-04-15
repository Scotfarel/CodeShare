//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_CHATROOM_H
#define CODESHARE_CHATROOM_H

#include <string>

#include <MongoConnector.h>
#include <RoomTextManager.h>


template <class MockTextManager>
class ChatRoom {
public:
    ChatRoom()= default;
    std::string getText(MockTextManager* manager);
    std::string addUser();

    int id = 0;
private:
    std::string sharedText;
    bool createDbTask() { return true; };

};

template<class MockTextManager>
std::string ChatRoom<MockTextManager>::addUser() {
    return std::string();
}

template<class MockTextManager>
std::string ChatRoom<MockTextManager>::getText(MockTextManager* manager) {
    return manager->getString();
}

#endif //CODESHARE_CHATROOM_H
