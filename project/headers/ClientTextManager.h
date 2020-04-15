//
// Created by mihail on 15.04.2020.
//

#ifndef CODESHARE_CLIENTTEXTMANAGER_H
#define CODESHARE_CLIENTTEXTMANAGER_H

#include <string>
#include "TextDiff.h"
#include <map>

class ClientTextManager {
public:
    ClientTextManager();
    std::map<TextDiff, int> formDiff(std::string a, std::string b);
private:
    std::string prevText;
    std::string currentText;
};



#endif //CODESHARE_CLIENTTEXTMANAGER_H
