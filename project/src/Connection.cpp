#include "Connection.h"

using boost::asio::ip::tcp;
using json = nlohmann::json;

Connection::Connection(tcp::socket socket) : socket(std::move(socket)) {
    RequestHandler<RoomScheduler> handler(RoomScheduler::getInstance());
    requestHandler = std::make_shared<RequestHandler<RoomScheduler>>(handler);
}

int Connection::getId() const {
    return this->id;
}

void Connection::setRoomId(int id) {
    this->roomId = id;
}

int Connection::getRoomId() const {
    return this->roomId;
}

void Connection::start(int clientId) {
    this->id = clientId;
    readHeader();
}

void Connection::stop() {
    socket.close();
}

void Connection::deliver(const MsgContext &msg) {
    bool isEmpty = messageQueue.empty();
    messageQueue.push(msg);
    if (isEmpty) {
        writeClient();
    }
}

void Connection::writeClient() {
    auto self(shared_from_this());
    boost::asio::async_write(socket,
                             boost::asio::buffer(messageQueue.front().data(), messageQueue.front().length() + 1),
                             [this, self](boost::system::error_code ec, std::size_t) {
        if (!ec) {
            messageQueue.pop();
            if (!messageQueue.empty()) {
                writeClient();
            }
        } else {
            RoomScheduler::getInstance().eraseUserFromRoom(getRoomId(), shared_from_this());
            ConnectionManager<Connection>::getInstance().stop(shared_from_this());
        }
    });
}

void Connection::readHeader() {
    memset(messageBuffer.getData(), 0, messageBuffer.length() + 1);
    auto self(shared_from_this());
    boost::asio::async_read(socket,
                            boost::asio::buffer(messageBuffer.getData(), HEADER + 1),
                            [this, self](boost::system::error_code ec, std::size_t) {
        if (!ec) {
            messageBuffer.decodeHeader();
            readBody();
        } else {
            RoomScheduler::getInstance().eraseUserFromRoom(getRoomId(), shared_from_this());
            ConnectionManager<Connection>::getInstance().stop(shared_from_this());
        }
    });
}

void Connection::readBody() {
    auto self(shared_from_this());
    boost::asio::async_read(socket,
                            boost::asio::buffer(messageBuffer.getBody() + 1, messageBuffer.getBodyLength()),
                            [this, self](boost::system::error_code ec, std::size_t) {

        if (!ec) {
            messageBuffer.getData()[messageBuffer.length() + 1] = '\0';
            messageBody.append(messageBuffer.body() + 1);

            if (messageBuffer.isThisLastChunk() == '0') {
                readHeader();
                return;
            }

            std::string requestType;
            json jsonBuf;
            try {
                jsonBuf = json::parse(messageBody);
                JsonUtility::fromJsonOperation(jsonBuf, requestType);

                int clientId = shared_from_this()->getId();
                if (requestType == "CREATE_ROOM_REQUEST") {
                    const std::string response = requestHandler->newRoom(self);

                    std::cout << "Sent:" << response << "END" << std::endl;
                    this->sendMsg(response);
                } else if (requestType == "JOIN_ROOM_REQUEST") {
                    const std::string response = requestHandler->joinRoom(jsonBuf, self);

                    std::cout << "Sent:" << response << "END" << std::endl;
                    this->sendMsg(response);
                } else if (requestType == "INSERTION_REQUEST" || requestType == "REMOVAL_REQUEST" ||
                           requestType == "INSERTIONRANGE_REQUEST" || requestType == "CURSOR_CHANGE_REQUEST") {

                    const std::string response = requestHandler->handleRequest(requestType, jsonBuf, clientId);

                    std::cout << "Sent:" << response << "END" << std::endl;
                    this->sendMsgAll(response, clientId);
                }

                messageBody.clear();
                readHeader();

            } catch (json::exception &e) {
                std::cerr << "MsgContext: " << e.what() << '\n' << "exception id: " << e.id << std::endl;
                messageBody.clear();
                readHeader();
            }
        } else {
            RoomScheduler::getInstance().eraseUserFromRoom(getRoomId(), shared_from_this());
            ConnectionManager<Connection>::getInstance().stop(shared_from_this());
        }
    });
}

void Connection::sendMsg(const std::string &response) {
    int mod = (response.length() % MAX_CHUNK_SIZE == 0) ? 1 : 0;
    int numChanks = (int) ((response.length() / MAX_CHUNK_SIZE) + 1 - mod);
    int chunkSize = MAX_CHUNK_SIZE;
    char isLastChunk = '0';
    std::string chunkResponse = response;

    for (int i = 0; i < numChanks; i++) {
        if (i == numChanks - 1) {
            chunkSize = (int) (response.length() % MAX_CHUNK_SIZE);
            isLastChunk = '1';
        }

        MsgContext msg = MsgContext::createMessage(std::string(chunkResponse.begin(), chunkResponse.begin() + chunkSize), isLastChunk);
        chunkResponse.erase(0, chunkSize);
        shared_from_this()->deliver(msg);
    }
}

void Connection::sendMsgAll(const std::string &response, const int &clientId) {
    int mod = (response.length() % MAX_CHUNK_SIZE == 0) ? 1 : 0;
    int numChanks = (int) ((response.length() / MAX_CHUNK_SIZE) + 1 - mod);
    int chunkSize = MAX_CHUNK_SIZE;
    char isLastChunk = '0';
    std::string chunkResponse = response;

    for (int i = 0; i < numChanks; i++) {
        if (i == numChanks - 1) {
            chunkSize = (int) (response.length() % MAX_CHUNK_SIZE);
            isLastChunk = '1';
        }

        MsgContext msg = MsgContext::createMessage(std::string(chunkResponse.begin(), chunkResponse.begin() + chunkSize), isLastChunk);
        chunkResponse.erase(0, chunkSize);
        std::shared_ptr<ChatRoom> room = RoomScheduler::getInstance().getRoom(getRoomId());
        room->sendMsgAllExceptMe(msg, clientId);
    }
}
