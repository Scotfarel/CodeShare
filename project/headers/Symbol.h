//
// Created by ivan on 5/19/20.
//

#ifndef CODESHARE_SYMBOL_H
#define CODESHARE_SYMBOL_H

#include <vector>
#include <string>
#include <array>


typedef std::pair<int, int> sId;


//  Symbol is a cell of symbols map, a letter.
//  Every symbol has his own position in a symbols vector.
class Symbol {
private:
    wchar_t letter{};
    sId symbolId;
    std::vector<int> position;

public:
    Symbol() = default;

    Symbol(wchar_t character, sId id, std::vector<int> pos);

    // Getters
    wchar_t getLetter() const;

    sId getSymbolId() const;

    std::vector<int> getPosition() const;

    // Setters
    void setLetter(wchar_t letter);

    void setSymbolId(sId id);

    void setPosition(std::vector<int> pos);

};

#endif //CODESHARE_SYMBOL_H
