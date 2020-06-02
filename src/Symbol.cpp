#include "headers/Symbol.h"
#include <utility>

Symbol::Symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos)
    : _letter(character), _id(std::move(id)), _pos(std::move(pos)) {}

Symbol::Symbol(wchar_t character)
    : _letter(character) {}


std::vector<int> Symbol::get_pos() const {
    return _pos;
}

wchar_t Symbol::get_letter() const {
    return _letter;
}

std::pair<int, int> Symbol::get_id() const {
    return _id;
}


void Symbol::set_letter(wchar_t letter) {
    this->_letter = letter;
}

void Symbol::set_id(std::pair<int, int> id) {
    this->_id = id;
}

void Symbol::set_pos(std::vector<int> pos) {
    this->_pos = std::move(pos);
}


