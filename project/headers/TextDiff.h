//
// Created by mihail on 15.04.2020.
//

#ifndef CODESHARE_TEXTDIFF_H
#define CODESHARE_TEXTDIFF_H

#include <string>

class TextDiff {
public:
    TextDiff();
private:
    int carriagePosition;
    int textLength;
    std::string diffType;
    std::string body;
};


#endif //CODESHARE_TEXTDIFF_H
