//
// Created by ivan on 5/21/20.
//

#include <algorithm>
#include <utility>

#include "User.h"


int User::getSymbolIndex(int newIndexPos, const std::vector<Symbol> &symbolsMap, const Symbol &symbol) {
    int elemIndex = 0;
    int position = 0;
    int nextPosIndex = symbolsMap.size();

    if (symbolsMap.size() / 2 < newIndexPos) {
        for (auto s = symbolsMap.crbegin(); s != symbolsMap.crend(); s++) {
            nextPosIndex--;
            int res = cmpPosX(s->getPosition(), s->getSymbolId(), symbol.getPosition(), symbol.getSymbolId(), position);
            if (res == -1) {
                continue;
            } else if (res == 1) {
                nextPosIndex++;
                break;
            }
        }
    } else {
        for (const auto &s: symbolsMap) {
            elemIndex++;
            int res = cmpPos(s.getPosition(), s.getSymbolId(), symbol.getPosition(), symbol.getSymbolId(), position);
            if (res == -1) {
                continue;
            } else if (res == 1) {
                nextPosIndex = elemIndex - 1;
                break;
            }
        }
    }

    return nextPosIndex;
}

int User::getSymbolIndexById(const std::vector<Symbol> &roomSymbols, sId id) {
    auto it = std::find_if(roomSymbols.begin(), roomSymbols.end(),
                           [id](const Symbol &s) { return s.getSymbolId() == id; });
    if (it != roomSymbols.end()) {
        int index = it - roomSymbols.begin();
        return index;
    }
    return -1;
}


int User::cmpPosX(std::vector<int> symPos, sId symId, std::vector<int> newSymPos, sId newSymId, int pos) {
    if (symPos.at(pos) < newSymPos.at(pos)) {
        return 1;
    } else if (symPos.at(pos) == newSymPos.at(pos)) {
        if (newSymPos.size() > pos + 1 && symPos.size() <= pos + 1) {
            return 1;
        } else if (newSymPos.size() <= pos + 1 && symPos.size() > pos + 1) {
            return -1;
        } else if (newSymPos.size() > pos + 1 && symPos.size() > pos + 1) {
            return cmpPosX(symPos, symId, newSymPos, newSymId, pos + 1);
        } else {
            return newSymId > symId ? 1 : -1;
        }
    } else {
        return -1;
    }
}

int User::cmpPos(std::vector<int> symPos, sId symId, std::vector<int> newSymPos, sId newSymId, int pos) {
    if (symPos.at(pos) > newSymPos.at(pos)) {
        return 1;
    } else if (symPos.at(pos) == newSymPos.at(pos)) {
        if (newSymPos.size() > pos + 1 && symPos.size() <= pos + 1) {
            return -1;
        } else if (newSymPos.size() <= pos + 1 && symPos.size() > pos + 1) {
            return 1;
        } else if (newSymPos.size() > pos + 1 && symPos.size() > pos + 1) {
            return cmpPos(symPos, symId, newSymPos, newSymId, pos + 1);
        } else {
            return newSymId.first < symId.first ? 1 : -1;
        }
    } else {
        return -1;
    }
}


void User::setSymbols(std::vector<Symbol> newSymbols) {
    this->symbols = std::move(newSymbols);
}

void User::setEditingText(std::string textName) {
    this->editingText = std::move(textName);
}


std::vector<Symbol> User::getSymbols() {
    return this->symbols;
}

std::string User::getEditingText() {
    return this->editingText;
}


std::string User::symbolsToString() {
    std::string my_string;
    for (const auto &s: symbols)
        my_string.push_back(s.getLetter());
    return my_string;
}
