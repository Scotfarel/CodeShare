//
// Created by ivan on 4/15/20.
//

#include <ChatRoom.h>

int ChatRoom::getRoomId() {
    return roomId;
}

void ChatRoom::enterRoom(const ::users &newUser) {
    usersInRoom.insert(newUser);
    newUser->setRoomId(roomId);
}

void ChatRoom::exitRoom(const ::users &user) {
    usersInRoom.erase(user);
}


void ChatRoom::sendMsgAllExceptMe(const MsgContext &message, int clientId) {
    for (const auto& user: usersInRoom) {
        if (user->getId() == clientId) {
            continue;
        }
        user->deliver(message);
    }
}

void ChatRoom::setTextMap(const std::vector<Symbol> &symbols) {
    this->textMap = symbols;
}

void ChatRoom::insertTextMap(int index, const Symbol &symbol) {
    this->textMap.insert(this->textMap.begin() + index, symbol);
}

void ChatRoom::eraseTextMap(int index) {
    this->textMap.erase(this->textMap.begin() + index);
}

void ChatRoom::updateTextMap(int index, const std::vector<Symbol> &symbols) {
    this->textMap.insert(this->textMap.begin() + index, symbols.begin(), symbols.end());
}

std::vector<Symbol> ChatRoom::getTextMap() {
    return textMap;
}

int ChatRoom::getIndexById(const std::vector<Symbol>& roomSymbols, std::pair<int,int> id) {
    auto it = std::find_if(roomSymbols.begin(), roomSymbols.end(), [id](const Symbol& s) { return s.getSymbolId() == id; });
    if (it != roomSymbols.end()) {
        int index = it - roomSymbols.begin();
        return index;
    }
    return -1;
}

int ChatRoom::cmpPosX(std::vector<int> symPos, sId symId, std::vector<int> newSymPos, sId newSymId, int pos) {
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

int ChatRoom::cmpPos(std::vector<int> symPos, sId symId, std::vector<int> newSymPos, sId newSymId, int pos) {
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

int ChatRoom::getSymbolIndex(int newIndexPos, const std::vector<Symbol> &symbolsMap, const Symbol &symbol) {
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