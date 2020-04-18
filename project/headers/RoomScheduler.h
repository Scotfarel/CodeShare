//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_ROOMMANAGER_H
#define CODESHARE_ROOMMANAGER_H

#include <string>
#include <vector>

#include <ChatRoom.h>

template <class ChatRoomInterface>
class RoomManager {
public:
    RoomManager() = default;
    ~RoomManager() = default;
    ChatRoomInterface* createRoom(int id) { return nullptr; };
    ChatRoomInterface* getRoom(int id);
    bool connectToRoom(ChatRoomInterface* room);
    void deleteRoom(int id) {};

private:
    std::vector<ChatRoomInterface* > roomsContainer;
};

template<class ChatRoomInterface>
bool RoomManager<ChatRoomInterface>::connectToRoom(ChatRoomInterface *room) {
    room->addUser();
    roomsContainer.push_back(room);
    return true;
}

template<class ChatRoomInterface>
ChatRoomInterface* RoomManager<ChatRoomInterface>::getRoom(int id) {
    return roomsContainer[id];
}


#endif //CODESHARE_ROOMMANAGER_H
