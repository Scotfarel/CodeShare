#ifndef PROJECT_INCLUDE_REQUEST_HANDLER_H_
#define PROJECT_INCLUDE_REQUEST_HANDLER_H_

#include <iostream>

class Connection;
class RoomScheduler;

#include "JsonUtility.h"
#include "json.hpp"
#include "Symbol.h"
#include "RoomScheduler.h"
#include "Connection.h"

class RequestHandler : public std::enable_shared_from_this<RequestHandler> {
public:
    RequestHandler(RoomScheduler& roomScheduler);
    std::string handleRequest(const std::string &requestType, const json &jsonBuf, int &clientId) const;
    std::string newRoom(std::shared_ptr<Connection> connection);
    std::string joinRoom(const json &jsonBuf, std::shared_ptr<Connection> connection);
private:
    RoomScheduler& roomScheduler;
};

#endif  //  PROJECT_INCLUDE_REQUEST_HANDLER_H_
