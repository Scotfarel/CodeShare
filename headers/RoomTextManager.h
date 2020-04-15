#pragma once
#include "TextManager.h"
#include <map>
#include <queue>
class RoomTextManager: public TextManager {
private:
    std::string prevText;
    std::map<TextDiff,int> diffToHandle;
    std::map<TextDiff, int> diffToSend;
public:
    RoomTextManager();
    bool addDiff(TextDiff);
    TextDiff getDiff();
    std::map<TextDiff, int> formDiff(std::string cur, std::string prev);

};
