#pragma once
#include "TextManager.h"
#include <map>

class ClientTextManager: public TextManager {
private:
std::string prevText;
public:
    bool updateText(std::string,std::string);
};

