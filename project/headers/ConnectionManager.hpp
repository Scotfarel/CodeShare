#ifndef PROJECT_INCLUDE_CONNECTION_MANAGER_H_
#define PROJECT_INCLUDE_CONNECTION_MANAGER_H_

#include <iostream>
#include <vector>

template<class ConnectionType>
class ConnectionManager {
public:
    ConnectionManager() {}
    void start(ConnectionType* connection) {
        connection->start();
    }
    void stop(ConnectionType* connection) {
        connection->stop();
    }
    void stopAll() {
        for (size_t i = 0; i < connections.size(); i++) {
            connections[i].stop();
        }
    }
private:
    std::vector<ConnectionType> connections;
};

#endif  //  PROJECT_INCLUDE_CONNECTION_MANAGER_H_