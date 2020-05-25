//
// Created by ivan on 5/24/20.
//

#include "User.h"
#include <algorithm>
#include <iostream>
#include <utility>

int User::getId() const {
    return id;
}

int User::cmpPosX(std::vector<int> symPos, std::pair<int,int> symId, std::vector<int> newSymPos,
                  std::pair<int,int> newSymId, int pos) {
    if (symPos.at(pos) < newSymPos.at(pos)) {
        return 1;
    }
    else if (symPos.at(pos) == newSymPos.at(pos)) {
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

int User::cmpPos(std::vector<int> symPos, std::pair<int,int> symId, std::vector<int> newSymPos,
                 std::pair<int,int> newSymId, int pos) {
    if(symPos.at(pos) > newSymPos.at(pos)) {
        return 1;
    }
    else if (symPos.at(pos) == newSymPos.at(pos)) {
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

int User::process(int type, int indexEditor, const std::vector<Symbol>& roomSymbols, const Symbol& newSymbol) {
    if (type == 0) {
        int symbols_index = 0, pos_index = 0;
        int startIndex = roomSymbols.size();

        if (indexEditor > roomSymbols.size() / 2) {
            std::cout << std::endl << "RIGHT TO LEFT: " << startIndex << std::endl << std::endl;
            for (auto s = roomSymbols.crbegin(); s != roomSymbols.crend(); s++) {
                startIndex--;
                int retValue = cmpPosX(s->getPos(), s->getId(), newSymbol.getPos(), newSymbol.getId(), pos_index);

                if (retValue == -1)
                    continue;
                else if (retValue == 1) {
                    startIndex ++;
                    break;
                }
            }
        }
        else {
            std::cout << std::endl << "LEFT TO RIGHT: " << startIndex << std::endl << std::endl;
            for (const auto &s: roomSymbols) {
                symbols_index++;
                int retValue = cmpPos(s.getPos(), s.getId(), newSymbol.getPos(), newSymbol.getId(), pos_index);

                if (retValue == -1)
                    continue;
                else if (retValue == 1) {
                    startIndex = symbols_index - 1;
                    break;
                }
            }
        }
        return startIndex;
    }
}

int User::process(int type, int indexEditor, const std::vector<Symbol>& roomSymbols,
        const std::vector<Symbol>& newSymbols) {
    if(type == 6) {
        int symbols_index = 0, pos_index = 0;
        int startIndex = roomSymbols.size();

        if(indexEditor > roomSymbols.size() / 2) {
            for (auto s = roomSymbols.crbegin(); s != roomSymbols.crend(); s++) {
                startIndex--;
                int retValue = cmpPosX(s->getPos(), s->getId(), newSymbols.at(0).getPos(),
                                       newSymbols.at(0).getId(), pos_index);
                if (retValue == -1)
                    continue;
                else if (retValue == 1) {
                    startIndex ++;
                    break;
                }
            }
        }
        else {
            for (const auto &s: roomSymbols) {
                symbols_index++;
                int retValue = cmpPos(s.getPos(), s.getId(), newSymbols.at(0).getPos(),
                                      newSymbols.at(0).getId(), pos_index);
                if (retValue == -1)
                    continue;
                else if (retValue == 1) {
                    startIndex = symbols_index - 1;
                    break;
                }
            }
        }
        return startIndex;
    }
}

int User::getIndexById(const std::vector<Symbol>& roomSymbols, sId id) {
    auto it = std::find_if(roomSymbols.begin(), roomSymbols.end(), [id](const Symbol& s) {return s.getId() == id;});
    if (it != roomSymbols.end()) {
        int index = it - roomSymbols.begin();
        return index;
    }
    return -1;
}

std::vector<Symbol> User::getSymbols() {
    return symbols;
}

std::string User::getCurrentFile() {
    return this->currentFile;
}

std::string User::getUsername() {
    return this->username;
}

std::string User::to_string() {
    std::string my_string;
    for(const auto& s: symbols)
        my_string.push_back(s.getLetter());
    return my_string;
}

void User::setSiteId(int edId) {
    this->id = edId;
}

void User::setSymbols(std::vector<Symbol> newSymbols) {
    this->symbols = std::move(newSymbols);
}

void User::setCurrentFile(std::string uri) {
    this->currentFile = std::move(uri);
}

void User::setUsername(std::string userName) {
    this->username = std::move(userName);
}
