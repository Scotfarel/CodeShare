//
// Created by ivan on 4/15/20.
//

#include <RoomScheduler.h>


RoomScheduler::RoomScheduler() : roomId(0) {}

std::shared_ptr<ChatRoom> RoomScheduler::createRoom() {
    std::shared_ptr<ChatRoom> newRoom = std::make_shared<ChatRoom>(roomId++);
    roomContainer.push_back(newRoom);
    std::cout << "ROOMS COUNT = " << roomContainer.size() << std::endl;
    return newRoom;
}

void RoomScheduler::eraseUserFromRoom(int Id, const std::shared_ptr<Connection>& user) {
    std::shared_ptr<ChatRoom> room = roomContainer.at(Id);
    room->exitRoom(user);
}

std::shared_ptr<ChatRoom> RoomScheduler::getRoom(int Id) {
    return roomContainer.at(Id);
}

#include <RoomScheduler.h>