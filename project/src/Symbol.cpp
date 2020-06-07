//
// Created by ivan on 5/19/20.
//

#include <utility>

#include <Symbol.h>


Symbol::Symbol(wchar_t character, sId symbolId, std::vector<int> position) : letter(character),
    symbolId(std::move(symbolId)), position(std::move(position)) {}


std::vector<int> Symbol::getPosition() const {
    return this->position;
}

wchar_t Symbol::getLetter() const {
    return this->letter;
}

sId Symbol::getSymbolId() const {
    return this->symbolId;
}


void Symbol::setLetter(wchar_t newLetter) {
    this->letter = newLetter;
}

void Symbol::setSymbolId(sId newSymbolId) {
    this->symbolId = newSymbolId;
}

void Symbol::setPosition(std::vector<int> newSymbolPos) {
    this->position = std::move(newSymbolPos);
}
