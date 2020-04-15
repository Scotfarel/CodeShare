//
// Created by mihail on 15.04.2020.
//

#ifndef CODESHARE_TEXTMANAGER_H
#define CODESHARE_TEXTMANAGER_H

#include <string>
#include <map>
#include "TextDiff.h"

class TextManager {
public:
    TextManager();

protected:
    std::string currentText;
    std::map<TextDiff, int> formDiff();
    std::string getString();
};


#endif //CODESHARE_TEXTMANAGER_H
