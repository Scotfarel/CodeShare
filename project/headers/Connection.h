#ifndef PROJECT_INCLUDE_CONNECTION_H_
#define PROJECT_INCLUDE_CONNECTION_H_

template<class RoomSchedulerType>
class RequestHandler;

class RoomScheduler;

#include <iostream>
#include <utility>
#include <queue>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

#include "json.hpp"
#include "MsgContext.h"
#include "ConnectionManager.h"
#include "RequestHandler.h"

using boost::asio::ip::tcp;
using json = nlohmann::json;
typedef std::pair<int,int> symbolId;

class Connection : public std::enable_shared_from_this<Connection> {
public:
    explicit Connection(tcp::socket socket);

    int getId() const;

    void setRoomId(int id);

    int getRoomId() const;

    void start(int editorId);

    void stop();

    void deliver(const MsgContext& msg);

private:
    int id;
    int roomId;
    tcp::socket socket;
    MsgContext messageBuffer;
    std::queue<MsgContext> messageQueue;
    std::string messageBody;
    std::shared_ptr<RequestHandler<RoomScheduler>> requestHandler;

    virtual void readHeader();

    virtual void readBody();

    virtual void writeClient();

    void sendMsg(const std::string& response);

    void sendMsgAll(const std::string& response, const int& clientId);
};

#endif  //  PROJECT_INCLUDE_CONNECTION_H_
