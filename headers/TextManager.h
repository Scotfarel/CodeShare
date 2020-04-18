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
    std::map<std::string,int> formDiff(std::string cur, std::string prev);
    std::string getString();
};



