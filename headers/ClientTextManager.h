#pragma once
#include "TextManager.h"
#include <map>
class ClientTextManager: public TextManager {
private:
std::string prevText;
public:
    ClientTextManager();
    bool updateText(std::string,std::map<TextDiff,int>);
};

