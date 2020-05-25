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
    std::string getText(MockTextBuilder* manager);

    static ChatRoom& getInstance() {
        static ChatRoom instance;
        return instance;
    }
    ChatRoom(ChatRoom const&) = delete;
    void operator=(ChatRoom const&) = delete;

    void join(const users_ptr& participant) {
        users.insert(participant);
        std::cout << "participant #" << participant->getId() << " joined the room" << std::endl;
    }
    void leave(const users_ptr& participant) {
        users.erase(participant);
        std::cout << "participant leaved the room" << std::endl;
    }
    void deliver(const MsgContext& msg) {
        recent_msgs.push_back(msg);
        while (recent_msgs.size() > max_recent_msgs)
            recent_msgs.pop_front();

        for (const auto& p: users)
            p->deliver(msg);
    }

    void deliverToAll(const MsgContext& msg, const int& edId, const std::string& curFile, bool includeThisEditor=false) {
        recent_msgs.push_back(msg);
        while (recent_msgs.size() > max_recent_msgs)
            recent_msgs.pop_front();

        if(!includeThisEditor) {
            for (const auto& p: users) {
                if (p->getId() != edId && p->getCurrentFile() == curFile) //don't send the message to the same client and don't send to clients having other file opened
                    p->deliver(msg);
            }
        } else {
            for (const auto& p: users) {
                if (p->getCurrentFile() == curFile) { //don't send the message to the clients having other file opened
                    p->deliver(msg);
                }
            }
        }
    }

    std::map<std::string, std::vector<Symbol>> getMap() {
        return this->room_map;
    };

    void updateMap(const std::string& key, const std::vector<Symbol>& symbols) {
        this->room_map[key] = symbols;
    }

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

    // There will be more methods for using a DB.
    // Now we don't have enough representations.
    std::string addUser();

    int id = 0;
private:
    std::set<users_ptr> users;
    enum { max_recent_msgs = 100 };
    message_queue recent_msgs;
    std::map<std::string, std::vector<Symbol>> room_map;

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
