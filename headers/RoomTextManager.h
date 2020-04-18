#pragma once
#include "TextManager.h"
#include <map>
#include <queue>

class RoomTextManager: public TextManager {
private:
    std::string prevText;
    std::map<std::string,int> diffToHandle;
    std::map<std::string, int> diffToSend;
public:
    bool addDiff(std::string);
    std::string getDiff();
    std::map<std::string, int> formDiff(std::string cur, std::string prev);

};
