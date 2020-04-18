//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_ROOMTEXTMANAGER_H
#define CODESHARE_ROOMTEXTMANAGER_H

#include <string>
#include <vector>
#include <map>

class RoomTextManager {
public:
    RoomTextManager() = default;
    ~RoomTextManager() = default;

    std::string getString() { return currentText; };
    std::string getDiff();

private:
    std::string currentText;
};

#endif //CODESHARE_ROOMTEXTMANAGER_H
