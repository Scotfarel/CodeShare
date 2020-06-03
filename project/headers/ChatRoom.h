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
#include <algorithm>

#include <Connection.h>
#include <Symbol.h>
#include <MsgContext.h>

class Connection;

typedef std::shared_ptr<Connection> users;


//  Container-like class that contains a map of text files and sending msg to users
class ChatRoom : public std::enable_shared_from_this<ChatRoom> {
private:
    int roomId;

    std::set<users> usersInRoom;
    std::vector<Symbol> textMap;

    //  Compare positions of symbols for correct position
    int cmpPosX(std::vector<int> symPos, sId symId, std::vector<int> newSymPos, sId newSymId, int pos);

    int cmpPos(std::vector<int> symPos, sId symId, std::vector<int> newSymPos, sId newSymId, int pos);

public:
    ChatRoom() = default;

    ChatRoom(ChatRoom const &) = delete;

    void operator=(ChatRoom const &) = delete;

    explicit ChatRoom(int Id) : roomId(Id) {};

    int getRoomId();

    //  Adding and deleting users in room
    void enterRoom(const ::users &newUser);

    void exitRoom(const ::users &user);

    //  Sending messages to users
    void sendMsgAllExceptMe(const MsgContext &message, int clientId);


    std::vector<Symbol> getTextMap();

    void setTextMap(const std::vector<Symbol> &symbols);

    void insertTextMap(int index, const Symbol &symbol);

    void eraseTextMap(int index);

    void updateTextMap(int index, const std::vector<Symbol> &symbols);

    int getIndexById(const std::vector<Symbol> &roomSymbols, std::pair<int, int> id);

    int getSymbolIndex(int newIndexPos, const std::vector<Symbol> &symbolsMap, const Symbol &symbol);
};


#endif //CODESHARE_CHATROOM_H