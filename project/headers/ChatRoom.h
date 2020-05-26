//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_CHATROOM_H
#define CODESHARE_CHATROOM_H

#include <string>

#include <MongoConnector.h>
#include <RoomTextBuilder.h>

#include <memory>
#include <string>
#include <set>
#include <deque>
#include <queue>
#include <map>
#include <iostream>
#include "User.h"

typedef std::shared_ptr<User> users_ptr;
typedef std::deque<MsgContext> message_queue;

template <class MockTextBuilder, class MockMongoConnector>
class ChatRoom {
public:
    ChatRoom()= default;
    ChatRoom(MockMongoConnector* dbConnector) : conn(dbConnector) {};

    ChatRoom(ChatRoom const&) = delete;
    void operator=(ChatRoom const&) = delete;
    static ChatRoom& getInstance();


    std::string getText(MockTextBuilder* manager);

    void join(const users_ptr& participant);
    void leave(const users_ptr& participant);
    void deliver(const MsgContext& msg);
    void deliverToAll(const MsgContext& msg, const int& edId, const std::string& curFile, bool includeThisEditor=false);

    std::map<std::string, std::vector<Symbol>> getMap() { return this->room_map; };
    void updateMap(const std::string& key, const std::vector<Symbol>& symbols) { this->room_map[key] = symbols; };
    void insertInSymbolMap(const std::string &key, int index, const Symbol& s) {
        this->room_map[key].insert(this->room_map[key].begin() + index, s);
    }
    void eraseInSymbolMap(const std::string &key, int index) {
        this->room_map[key].erase(this->room_map[key].begin() + index);
    }
    void updateSymbolsMap(const std::string &key, int index, const std::vector<Symbol>& symbols) {
        this->room_map[key].insert(this->room_map[key].begin() + index, symbols.begin(), symbols.end());
    }
    void setMap(const std::map<std::string, std::vector<Symbol>>& m) {
        this->room_map = m;
    }

    std::string addUser();

private:
    std::set<users_ptr> users;
    enum { max_recent_msgs = 100 };
    message_queue recent_msgs;
    std::map<std::string, std::vector<Symbol>> room_map;

    MockMongoConnector* conn;
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

template<class MockTextBuilder, class MockMongoConnector>
ChatRoom<MockTextBuilder, MockMongoConnector> &ChatRoom<MockTextBuilder, MockMongoConnector>::getInstance() {
    static ChatRoom instance;
    return instance;
}

template<class MockTextBuilder, class MockMongoConnector>
void ChatRoom<MockTextBuilder, MockMongoConnector>::join(const users_ptr &participant) {
    users.insert(participant);
    std::cout << "participant #" << participant->getId() << " joined the room" << std::endl;
}

template<class MockTextBuilder, class MockMongoConnector>
void ChatRoom<MockTextBuilder, MockMongoConnector>::leave(const users_ptr &participant) {
    users.erase(participant);
    std::cout << "participant leaved the room" << std::endl;
}

template<class MockTextBuilder, class MockMongoConnector>
void ChatRoom<MockTextBuilder, MockMongoConnector>::deliver(const MsgContext &msg) {
    recent_msgs.push_back(msg);
    while (recent_msgs.size() > max_recent_msgs)
        recent_msgs.pop_front();
    for (const auto& u: users)
        u->deliver(msg);
}

template<class MockTextBuilder, class MockMongoConnector>
void ChatRoom<MockTextBuilder, MockMongoConnector>::deliverToAll(const MsgContext &msg, const int &edId,
                                                                 const std::string &curFile, bool includeThisEditor) {
    recent_msgs.push_back(msg);
    while (recent_msgs.size() > max_recent_msgs)
        recent_msgs.pop_front();

    if(!includeThisEditor) {
        for (const auto& u: users) {
            if (u->getId() != edId && u->getCurrentFile() == curFile)
                u->deliver(msg);
        }
    } else {
        for (const auto& u: users) {
            if (u->getCurrentFile() == curFile) {
                u->deliver(msg);
            }
        }
    }
}

#endif //CODESHARE_CHATROOM_H
