#ifndef PROJECT_INCLUDE_CONNECTION_MANAGER_H_
#define PROJECT_INCLUDE_CONNECTION_MANAGER_H_

#include <iostream>
#include <set>

template<class ConnectionType>
class ConnectionManager {
public:
    ConnectionManager() {}

    void start(std::shared_ptr<ConnectionType> connection) {
        std::cout << "start in ConManager" << std::endl;
        connections.insert(connection);
        connection->start();
    }

    void stop(std::shared_ptr<ConnectionType> connection) {
        connections.erase(connection);
        connection->stop();
    }

    void stopAll() {
        for (size_t i = 0; i < connections.size(); i++) {
            connections[i].stop();
        }
        connections.clear();
    }

private:
    std::set<std::shared_ptr<ConnectionType> > connections;
};

#endif  //  PROJECT_INCLUDE_CONNECTION_MANAGER_H_