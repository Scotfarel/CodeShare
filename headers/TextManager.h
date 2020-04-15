#pragma once
#include <string>
#include <map>

struct TextDiff {
public:
    int carriagePosition;
    int textLength;
    std::string diffType;
    std::string body;
};

class TextManager {
protected:
    std::string currentText;

public:
    std::map<TextDiff,int> formDiff(std::string cur, std::string prev);
    TextManager();
    std::string getString();
};



