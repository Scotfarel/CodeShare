#ifndef PROJECT_INCLUDE_REQUEST_HANDLER_H_
#define PROJECT_INCLUDE_REQUEST_HANDLER_H_

#include <iostream>

template <class RoomSchedulerType>
class RequestHandler {
public:
    RequestHandler(RoomSchedulerType* scheduler) : roomScheduler(scheduler) {}
    void handleRequest(int request) {
        switch (request)
        {
        case 0:
            roomScheduler->createRoom();
        case 1:
            roomScheduler->getRoom();
        case 2:
            roomScheduler->connectToRoom();
        case 3:
            roomScheduler->deleteRoom();
        default:
            break;
        }
    }
private:
    RoomSchedulerType *roomScheduler;
};

#endif  //  PROJECT_INCLUDE_REQUEST_HANDLER_H_