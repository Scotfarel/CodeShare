//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_ROOMTEXTBUILDER_H
#define CODESHARE_ROOMTEXTBUILDER_H

#include <string>
#include <vector>
#include <map>

class RoomTextBuilder {
public:
    RoomTextBuilder() = default;
    ~RoomTextBuilder() = default;

    std::string getString() { return currentText; };
    std::string getDiff();

private:
    std::string currentText;
};

#endif //CODESHARE_ROOMTEXTBUILDER_H
