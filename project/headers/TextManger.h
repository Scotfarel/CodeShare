//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_TEXTMANGER_H
#define CODESHARE_TEXTMANGER_H

#include <string>

class TextManager {
public:
    TextManager() = default;
    ~TextManager() = default;

    std::string getString() { return currentText; };
private:
    std::string currentText;
};

#endif //CODESHARE_TEXTMANGER_H
