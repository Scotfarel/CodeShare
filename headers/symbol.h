#pragma once
#include <vector>
#include <string>
#include <array>

class symbol {

private:
    wchar_t _letter;
    std::pair<int, int> _id;
    std::vector<int> _pos;

public:
    symbol() = default;
    symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos);
    symbol(wchar_t character);
    std::vector<int> getPos() const;
    wchar_t getLetter() const;
    std::pair<int, int> getId() const;
    void setLetter(wchar_t letter);
    void setId(std::pair<int,int> id);
    void setPos(std::vector<int> pos);
};