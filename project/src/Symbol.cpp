//
// Created by ivan on 5/19/20.
//

#include <Symbol.h>
#include <utility>

Symbol::Symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos)
        : letter(character), id(std::move(id)), pos(std::move(pos)) {}

std::vector<int> Symbol::getPos() const {
    return pos;
}

wchar_t Symbol::getLetter() const {
    return letter;
}

std::pair<int, int> Symbol::getId() const {
    return id;
}

void Symbol::setLetter(wchar_t new_letter) {
    letter = new_letter;
}

void Symbol::setId(std::pair<int, int> new_id) {
    id = new_id;
}

void Symbol::setPos(std::vector<int> new_pos) {
    pos = std::move(new_pos);
}
