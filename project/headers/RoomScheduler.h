//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_ROOMSCHEDULER_H
#define CODESHARE_ROOMSCHEDULER_H

#include <string>
#include <vector>
#include <memory>

#include <ChatRoom.h>

template <class ChatRoomInterface>
class RoomScheduler {
public:
    RoomScheduler() = default;
    ~RoomScheduler() = default;
    ChatRoomInterface* createRoom(int id) { return nullptr; };
    ChatRoomInterface* getRoom(int id);
    bool connectToRoom(ChatRoomInterface* room);
    bool leave();
    void deleteRoom(int id) {};

private:
    std::vector<ChatRoomInterface* > roomsContainer;
};

template<class ChatRoomInterface>
bool RoomScheduler<ChatRoomInterface>::connectToRoom(ChatRoomInterface *room) {
    room->addUser();
    roomsContainer.push_back(room);
    return true;
}

template<class ChatRoomInterface>
ChatRoomInterface* RoomScheduler<ChatRoomInterface>::getRoom(int id) {
    return roomsContainer[id];
}

template<class ChatRoomInterface>
bool RoomScheduler<ChatRoomInterface>::leave() {
    return false;
}


#endif //CODESHARE_ROOMSCHEDULER_H
