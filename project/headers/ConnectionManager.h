#ifndef PROJECT_INCLUDE_CONNECTION_MANAGER_H_
#define PROJECT_INCLUDE_CONNECTION_MANAGER_H_

#include <iostream>
#include <set>

#include "MsgContext.h"
#include "Connection.h"

template<class ConnectionType>
class ConnectionManager {
public:
    static ConnectionManager& getInstance() {
        static ConnectionManager instance;
        return instance;
    }

    void start(std::shared_ptr<ConnectionType> connection, int clientId);

    void stop(std::shared_ptr<ConnectionType> connection);

    void stopAll();

    void sendMsgAllExceptMe(MsgContext message, int clientId);

    ConnectionManager(ConnectionManager const&) = delete;

    void operator=(ConnectionManager const&) = delete;
private:
    ConnectionManager() = default;
    std::set<std::shared_ptr<ConnectionType>> connections;
};

template<class ConnectionType>
void ConnectionManager<ConnectionType>::start(std::shared_ptr<ConnectionType> connection, int clientId) {
    std::cout << "start in ConManager" << std::endl;
    connections.insert(connection);
    connection->start(clientId);
}

template<class ConnectionType>
void ConnectionManager<ConnectionType>::stop(std::shared_ptr<ConnectionType> connection) {
    connection->stop();
    connections.erase(connection);
}

template<class ConnectionType>
void ConnectionManager<ConnectionType>::stopAll() {
    for (auto connection : connections) {
        connection->stop();
    }
    connections.clear();
}

template<class ConnectionType>
void ConnectionManager<ConnectionType>::sendMsgAllExceptMe(MsgContext message, int clientId) {
    for (const auto& connection: connections) {
        if (connection->getId() == clientId) {
            continue;
        }
        connection->deliver(message);
    }
}

#endif  //  PROJECT_INCLUDE_CONNECTION_MANAGER_H_
