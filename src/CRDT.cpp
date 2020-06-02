#include "headers/CRDT.h"
#include <algorithm>
#include <iostream>
#include <utility>

std::vector<int> CRDT::generate_pos(int index) {
    const std::vector<int> pos_before = _symbols[index - 1].get_pos();
    const std::vector<int> pos_after = _symbols[index].get_pos();
    return generate_pos_between(pos_before, pos_after);
}

std::vector<int> CRDT::generate_pos_between(std::vector<int> pos1, std::vector<int> pos2, std::vector<int> new_pos) {
    int id1 = pos1.at(0);
    int id2 = pos2.at(0);

    if (id2 - id1 == 0) {  // [1] [1 0] or [1 0] [1 1]
        new_pos.push_back(id1);
        pos1.erase(pos1.begin());
        pos2.erase(pos2.begin());
        if (pos1.empty()) {
            new_pos.push_back(pos2.front() - 1);  // [1] [1 0] -> [1 -1]
            return new_pos;
        } else {
            return generate_pos_between(pos1, pos2, new_pos);  // [1 0] [1 1] -> recall and enter third if
        }
    } else if (id2 - id1 > 1) {  // [0] [3]
        new_pos.push_back(pos1.front() + 1);  // [0] [3] -> [1]
        return new_pos;
    } else if (id2 - id1 == 1) {  // [1] [2] or [1 1] [2]
        new_pos.push_back(id1);
        pos1.erase(pos1.begin());
        if (pos1.empty()) {
            new_pos.push_back(0);  // [1] [2] -> [1 0]
            return new_pos;
        } else {
            new_pos.push_back(pos1.front() + 1);  // [1 1] [2] -> [1 2]
            return new_pos;
        }
    }
}

int CRDT::compare_posdx(std::vector<int> cur_sym_pos, std::pair<int, int> cur_sym_id,
                        std::vector<int> new_sym_pos, std::pair<int, int> newSymId, int posIndex) {
    int newSymPosSize = static_cast<int>(new_sym_pos.size());
    int curSymPosSize = static_cast<int>(cur_sym_pos.size());
    int curSymPosCurIndex = static_cast<int>(cur_sym_pos.at(posIndex));
    int newSymPosCurIndex = static_cast<int>(new_sym_pos.at(posIndex));

    if (curSymPosCurIndex < newSymPosCurIndex) {
        return 1;
    } else if (curSymPosCurIndex == newSymPosCurIndex) {
        if (newSymPosSize > posIndex + 1 &&
            curSymPosSize <= posIndex + 1)  // new_sym_pos[posIndex+1] != null && cur_sym_pos[posIndex+1] == null
            return 1;  // correct position found
        else if (newSymPosSize <= posIndex + 1 &&
                 curSymPosSize > posIndex + 1)  // new_sym_pos[posIndex+1] == null && cur_sym_pos[posIndex+1] != null
            return -1;  // cur_sym_pos > new_sym_pos  -> make another cycle taking the next Symbol from _symbols
        else if (newSymPosSize > posIndex + 1 &&
                 curSymPosSize > posIndex + 1)  // new_sym_pos[posIndex+1] != null && cur_sym_pos[posIndex+1] != null
            return compare_posdx(cur_sym_pos, cur_sym_id, new_sym_pos,
                                 newSymId, posIndex + 1);  // call recursively this function using next index for posIndex
        else  // new_sym_pos[posIndex+1] == null && cur_sym_pos[posIndex+1] == null
            return newSymId > cur_sym_id ? 1 : -1;
    } else {
        return -1;  // make another cycle taking the next Symbol from _symbols
    }
}

int CRDT::compare_pos(std::vector<int> curSymPos, std::pair<int, int> curSymId, std::vector<int> newSymPos,
                      std::pair<int, int> newSymId, int posIndex) {
    int newSymPosSize = static_cast<int>(newSymPos.size());
    int curSymPosSize = static_cast<int>(curSymPos.size());
    int curSymPosCurIndex = static_cast<int>(curSymPos.at(posIndex));
    int newSymPosCurIndex = static_cast<int>(newSymPos.at(posIndex));

    if (curSymPosCurIndex > newSymPosCurIndex) {
        return 1;  // correct position found
    } else if (curSymPosCurIndex == newSymPosCurIndex) {
        if (newSymPosSize > posIndex + 1 &&
            curSymPosSize <= posIndex + 1)  // newSymPos[posIndex+1] != null && curSymPos[posIndex+1] == null
            return -1;  // newSymPos > curSymPos -> make another cycle taking the next Symbol from _symbols
        else if (newSymPosSize <= posIndex + 1 &&
                 curSymPosSize > posIndex + 1)  // newSymPos[posIndex+1] == null && curSymPos[posIndex+1] != null
            return 1;  // correct position found
        else if (newSymPosSize > posIndex + 1 &&
                 curSymPosSize > posIndex + 1)  // newSymPos[posIndex+1] != null && curSymPos[posIndex+1] != null
            return compare_pos(curSymPos, curSymId, newSymPos,
                               newSymId, posIndex + 1);  // call recursively this function using next index for posIndex
        else  // newSymPos[posIndex+1] == null && curSymPos[posIndex] == null
            return newSymId.first < curSymId.first ? 1 : -1;
    } else {
        return -1;  // make another cycle taking the next Symbol from _symbols
    }
}

Symbol CRDT::localInsert(int index, wchar_t value) noexcept(false) {
    std::vector<int> pos;

    if (_symbols.empty()) {
        pos = {0};
        index = 0;
    } else if (index > static_cast<int>(_symbols.size())-1) {
        pos = {_symbols.back().get_pos().at(0) + 1};  // last element will not have fraction -> pos will be [x] not [x,y]
        index = static_cast<int>(_symbols.size());
    } else if (index == 0) {
        pos = {_symbols.front().get_pos().at(0) - 1};  // put negative pos
    } else {
        pos = generate_pos(index);
    }

    Symbol s(value, std::make_pair(_siteId, ++_counter), pos);
    _symbols.insert(_symbols.begin() + index, s);

    return s;
}

std::vector<Symbol> CRDT::localInsert(int startIndex, std::vector<Symbol> symbols) noexcept(false) {
    std::vector<int> pos;
    // generate initial pos and initial index
    if (_symbols.empty()) {
        pos = {0};
        startIndex = 0;
    } else if (startIndex > static_cast<int>(_symbols.size())-1) {
        pos = {_symbols.back().get_pos().at(0) + 1};  // last element will not have fraction -> pos will be [x] not [x,y]
        startIndex = static_cast<int>(_symbols.size());
    } else if (startIndex == 0) {
        pos = {_symbols.front().get_pos().at(0) - 1};  // put negative pos
    } else {
        pos = generate_pos(startIndex);
    }

    std::vector<Symbol> symbolVector;
    bool firstTime = true;
    bool secondTime = true;
    int counter = 0;

    std::for_each(symbols.begin(), symbols.end(), [&firstTime, &secondTime, &counter,
                                                   &pos, &symbolVector, this](const Symbol& s) {
        // get values
        wchar_t value = s.get_letter();
        // generate next pos
        if (firstTime) {
            firstTime = false;
        } else {
            if (secondTime) {
                pos.push_back(counter++);
                secondTime = false;
            } else {
                pos.back() = counter++;
            }
        }

        // insert Symbol
        Symbol sym(value, std::make_pair(_siteId, ++_counter), pos);
        symbolVector.push_back(sym);
    });
    _symbols.insert(_symbols.begin() + startIndex, symbolVector.begin(), symbolVector.end());
    return std::move(symbolVector);
}

std::vector<int_pair> CRDT::localErase(int startIndex, int endIndex) noexcept(false) {
    // create vector of id to be sent (in removal we need only id, not entire Symbol)
    std::vector<int_pair> symbolsId;
    std::for_each(_symbols.begin() + startIndex, _symbols.begin() + endIndex, [&symbolsId](const Symbol& s) {
        symbolsId.push_back(s.get_id());
    });

    // erase local symbols
    _symbols.erase(_symbols.begin() + startIndex, _symbols.begin() + endIndex);
    return symbolsId;
}

int CRDT::process(int type, int indexEditor, Symbol newSym) {
    /* Insertion */
    if (type == 0) {
        int symbols_index = 0, pos_index = 0;
        int startIndex = static_cast<int>(_symbols.size());

        // get first index
        if (indexEditor > static_cast<int>(_symbols.size()/2)) {  // LOOP FROM RIGHT TO LEFT
            for (auto s = _symbols.crbegin(); s != _symbols.crend(); s++) {
                startIndex--;
                int retValue = compare_posdx(s->get_pos(), s->get_id(), newSym.get_pos(), newSym.get_id(), pos_index);

                if (retValue == -1) {
                    continue;
                } else if (retValue == 1) {
                    startIndex++;
                    break;
                }
            }
        } else {  // LOOP FROM LEFT TO RIGHT
            for (const auto &s : _symbols) {
                symbols_index++;
                int retValue = compare_pos(s.get_pos(), s.get_id(), newSym.get_pos(), newSym.get_id(), pos_index);

                if (retValue == -1) {
                    continue;
                } else if (retValue == 1) {
                    startIndex = symbols_index - 1;
                    break;
                }
            }
        }
        // update symbols vector
        _symbols.insert(_symbols.begin() + startIndex, newSym);
        return startIndex;
    }
}

int CRDT::process(int type, int indexEditor, std::vector<Symbol> newSymbols) {
    /* Insertion range */
    if (type == 6) {
        int symbols_index = 0, pos_index = 0;
        int startIndex = static_cast<int>(_symbols.size());

        // get first index
        if (indexEditor > static_cast<int>(_symbols.size()/2)) {  // LOOP FROM RIGHT TO LEFT
            for (auto s = _symbols.crbegin(); s != _symbols.crend(); s++) {
                startIndex--;
                int retValue = compare_posdx(s->get_pos(), s->get_id(), newSymbols.at(0).get_pos(),
                                             newSymbols.at(0).get_id(), pos_index);
                if (retValue == -1) {
                    continue;
                } else if (retValue == 1) {
                    startIndex++;
                    break;
                }
            }
        } else {  // LOOP FROM LEFT TO RIGHT
            for (const auto &s : _symbols) {
                symbols_index++;
                int retValue = compare_pos(s.get_pos(), s.get_id(), newSymbols.at(0).get_pos(),
                                           newSymbols.at(0).get_id(), pos_index);
                if (retValue == -1) {
                    continue;
                } else if (retValue == 1) {
                    startIndex = symbols_index - 1;
                    break;
                }
            }
        }
        // update symbols vector
        _symbols.insert(_symbols.begin() + startIndex, newSymbols.begin(), newSymbols.end());
        return startIndex;
    }
}

int CRDT::processErase(int_pair id) {
    auto it = std::find_if(_symbols.begin(), _symbols.end(), [id](const Symbol& s) {return s.get_id() == id;});
    if (it != _symbols.end()) {
        int index = it - _symbols.begin();

        // update symbols vector
        _symbols.erase(_symbols.begin() + index);
        return index;
    }
    return -1;
}

int CRDT::get_site_id() {
    return this->_siteId;
}

int CRDT::get_counter() {
    return this->_counter;
}

std::vector<Symbol> CRDT::get_symbols() {
    return _symbols;
}

void CRDT::set_site_id(int id) {
    this->_siteId = id;
}

void CRDT::set_counter(int counter) {
    this->_counter = counter;
}

void CRDT::set_symbols(std::vector<Symbol> symbols) {
    this->_symbols = std::move(symbols);
}
