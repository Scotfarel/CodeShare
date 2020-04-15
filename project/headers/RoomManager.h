//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_ROOMMANAGER_H
#define CODESHARE_ROOMMANAGER_H

#include <string>
#include <vector>

#include <ChatRoom.h>


class RoomManager {
public:
    RoomManager();
    ChatRoom* createRoom();
    ChatRoom* getRoom(int id);
    bool connectToRoom(int id);
    void deleteRoom(int id);

private:
    std::vector<ChatRoom> roomsContainer;
};

#endif //CODESHARE_ROOMMANAGER_H
