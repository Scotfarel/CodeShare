#include "headers/symbol.h"
#include <utility>

symbol::symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos)
    : _letter(character), _id(std::move(id)), _pos(std::move(pos)){}

symbol::symbol(wchar_t character)
    : _letter(character) {}


std::vector<int> symbol::getPos() const {
    return _pos;
}

wchar_t symbol::getLetter() const {
    return _letter;
}

std::pair<int, int> symbol::getId() const {
    return _id;
}


void symbol::setLetter(wchar_t letter) {
    this->_letter = letter;
}

void symbol::setId(std::pair<int, int> id) {
    this->_id = id;
}

void symbol::setPos(std::vector<int> pos) {
    this->_pos = std::move(pos);
}


