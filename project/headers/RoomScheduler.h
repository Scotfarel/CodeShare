//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_ROOMSCHEDULER_H
#define CODESHARE_ROOMSCHEDULER_H

#include <iostream>
#include <vector>

#include <ChatRoom.h>

class ChatRoom;
class Connection;

class RoomScheduler {
public:
    static RoomScheduler& getInstance() {
        static RoomScheduler instance;
        return instance;
    }

    RoomScheduler(RoomScheduler const&) = delete;

    void operator=(RoomScheduler const&) = delete;

    std::shared_ptr<ChatRoom> createRoom();

    void eraseUserFromRoom(int Id, const std::shared_ptr<Connection>& user);

    std::shared_ptr<ChatRoom> getRoom(int id);
private:
    std::vector<std::shared_ptr<ChatRoom>> roomContainer;
    int roomId;

    RoomScheduler();
};

#endif //CODESHARE_ROOMSCHEDULER_H
