//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_CHATROOM_H
#define CODESHARE_CHATROOM_H

#include <string>
#include <memory>
#include <string>
#include <set>
#include <deque>
#include <queue>
#include <map>
#include <iostream>

#include "User.h"

#define MAX_RECENT_MSG 50


typedef std::shared_ptr<User> users;
typedef std::deque<MsgContext> messages;


//  Container-like class for users and their messages that contains a map of text files
class ChatRoom {
private:
    std::set<users> usersInRoom;
    messages recentMessages;
    std::map<std::string, std::vector<Symbol>> textMap;

public:
    ChatRoom() = default;

    ChatRoom(ChatRoom const &) = delete;

    void operator=(ChatRoom const &) = delete;

    static ChatRoom &getInstance();

    //  Adding and deleting users in room
    void enterRoom(const ::users &newUser);

    void exitRoom(const ::users &user);

    //  Sending messages to users
    void sendMessage(const MsgContext &message);


    //  Interaction with map
    std::map<std::string, std::vector<Symbol>> getMap();

    std::vector<Symbol> getTextMap(const std::string &name);

    void setTextMap(const std::string &name, const std::vector<Symbol> &symbols);

    void insertTextMap(const std::string &name, int index, const Symbol &symbol);

    void eraseTextMap(const std::string &name, int index);

    void updateTextMap(const std::string &name, int index, const std::vector<Symbol> &symbols);

};


#endif //CODESHARE_CHATROOM_H
