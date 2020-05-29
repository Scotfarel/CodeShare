//
// Created by ivan on 4/15/20.
//

#include <ChatRoom.h>

ChatRoom &ChatRoom::getInstance() {
    static ChatRoom room;
    return room;
}


void ChatRoom::enterRoom(const ::users &newUser) {
    usersInRoom.insert(newUser);
    std::cout << "New user connected to room!" << std::endl;
}

void ChatRoom::exitRoom(const ::users &user) {
    usersInRoom.erase(user);
    std::cout << "User has left the room" << std::endl;
}

void ChatRoom::sendMessage(const MsgContext &message) {
    recentMessages.push_back(message);
    while (recentMessages.size() > MAX_RECENT_MSG) {
        recentMessages.pop_front();
    }
    for (const auto &user: usersInRoom) {
        user->deliver(message);
    }
}


std::map<std::string, std::vector<Symbol>> ChatRoom::getMap() {
    return this->textMap;
}

void ChatRoom::setTextMap(const std::string &name, const std::vector<Symbol> &symbols) {
    this->textMap[name] = symbols;
}

void ChatRoom::insertTextMap(const std::string &name, int index, const Symbol &symbol) {
    this->textMap[name].insert(this->textMap[name].begin() + index, symbol);
}

void ChatRoom::eraseTextMap(const std::string &name, int index) {
    this->textMap[name].erase(this->textMap[name].begin() + index);
}

void ChatRoom::updateTextMap(const std::string &name, int index, const std::vector<Symbol> &symbols) {
    this->textMap[name].insert(this->textMap[name].begin() + index, symbols.begin(), symbols.end());
}

std::vector<Symbol> ChatRoom::getTextMap(const std::string &name) {
    if (textMap.empty()) {
        return std::vector<Symbol>();
    }
    return textMap.at(name);
}

