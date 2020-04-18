//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_CHATROOM_H
#define CODESHARE_CHATROOM_H

#include <string>

#include <MongoConnector.h>
#include <RoomTextBuilder.h>


template <class MockTextBuilder, class MockMongoConnector>
class ChatRoom {
public:
    ChatRoom()= default;
    ChatRoom(MockMongoConnector* dbConnector) : conn(dbConnector) {};
    std::string getText(MockTextBuilder* manager);

    // There will be more methods for using a DB.
    // Now we don't have enough representations.
    std::string addUser();

    int id = 0;
private:
    std::string sharedText;
    MockMongoConnector* conn;

    bool createDbTask() { return true; };
};

template<class MockTextBuilder, class MockMongoConnector>
std::string ChatRoom<MockTextBuilder, MockMongoConnector>::addUser() {
    conn->getCurrText();
    conn->getChunk();
    conn->saveDiff();
    conn->createRoomTable("testTableName");
    return std::string();
}

template<class MockTextBuilder, class MockMongoConnector>
std::string ChatRoom<MockTextBuilder, MockMongoConnector>::getText(MockTextBuilder* builder) {
    builder->getString();
    return "";
}


#endif //CODESHARE_CHATROOM_H
