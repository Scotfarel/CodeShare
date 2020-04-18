//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_TEXTBUILDER_H
#define CODESHARE_TEXTBUILDER_H

#include <string>

class TextBuilder {
public:
    TextBuilder() = default;
    ~TextBuilder() = default;

    std::string getString() { return currentText; };
private:
    std::string currentText;
};

#endif //CODESHARE_TEXTBUILDER_H
