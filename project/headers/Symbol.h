//
// Created by ivan on 5/19/20.
//

#ifndef CODESHARE_SYMBOL_H
#define CODESHARE_SYMBOL_H

#include <vector>
#include <string>
#include <array>

class Symbol {

private:
    wchar_t letter{};
    std::pair<int, int> id;
    std::vector<int> pos;

public:
    Symbol() = default;
    Symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos);
    void setLetter(wchar_t letter);
    void setId(std::pair<int,int> id);
    void setPos(std::vector<int> pos);
    wchar_t getLetter() const;
    std::pair<int, int> getId() const;
    std::vector<int> getPos() const;
};

#endif //CODESHARE_SYMBOL_H
