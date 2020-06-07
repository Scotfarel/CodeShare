//
// Created by ivan on 4/15/20.
//

#include <JsonUtility.h>

void JsonUtility::toJsonSymbol(json &j, const Symbol &symbol) {
    j = json{
            {"letter", symbol.getLetter()},
            {"id", symbol.getId()},
            {"pos", symbol.getPos()},
    };
}

void JsonUtility::toJsonRoomId(json &j, const std::string &operation, const int &roomId) {
    j = json{
            {"operation", operation},
            {"room_id", roomId}
    };
}

void JsonUtility::toJsonCursorChange(json &j, const std::string &operation, const int &pos) {
    j = json{
            {"operation", operation},
            {"pos", pos}
    };
}

void JsonUtility::toJsonInsertion(json &j, const std::string &operation, const Symbol &symbol, const int &indexInEditor) {
    j = json{
            {"operation", operation},
            {"id", symbol.getId()},
            {"pos", symbol.getPos()},
            {"letter", symbol.getLetter()},
            {"indexInEditor", indexInEditor}
    };
}

void JsonUtility::toJsonRemovalRange(json &j, const std::string &operation, const std::vector<std::pair<int,int>> &symbolsId) {
    j = json{
            {"operation", operation},
            {"symbolsId", symbolsId}
    };
}

void JsonUtility::toJsonInsertionRange(json &j, const std::string &operation, const int &firstIndexRange, const std::vector<json> &symbols, const int &roomId) {
    j = json{
            {"operation", operation},
            {"firstIndexRange", firstIndexRange},
            {"symbols", symbols},
            {"room_id", roomId}
    };
}

void JsonUtility::fromJsonRoomId(const json &j, int &roomId) {
    roomId = j.at("room_id").get<int>();
}

void JsonUtility::fromJsonInsertion(const json& j, Symbol& s, int &indexInEditor, int &roomId) {
    indexInEditor = j.at("indexInEditor").get<int>();
    wchar_t letter = j.at("letter").get<wchar_t>();
    std::pair<int,int> id = j.at("id").get<std::pair<int,int>>();
    std::vector<int> pos = j.at("pos").get<std::vector<int>>();
    s = Symbol(letter, id, pos);
    roomId = j.at("room_id").get<int>();
}

void JsonUtility::fromJson(const json &j, std::string &operation) {
    operation = j.at("operation").get<std::string>();
}

std::vector<json> JsonUtility::fromSymToJson(const std::vector<Symbol>& symbols) {
    if(symbols.empty())
        return json::array();

    std::vector<json> jsons;
    for (auto const &sym: symbols) {
        json j;
        JsonUtility::toJsonSymbol(j, sym);
        jsons.push_back(j);
    }
    return jsons;
}

std::vector<Symbol> JsonUtility::fromJsonToFormattingSym(const std::vector<json>& jsons) {
    std::vector<Symbol> symbols;
    for (auto const &j: jsons) {
        symbols.push_back(JsonUtility::fromJsonSymbol(j));
    }
    return symbols;
}

Symbol JsonUtility::fromJsonSymbol(const json &j) {
    std::pair<int,int> id = j.at("id").get<std::pair<int,int>>();
    std::vector<int> pos = j.at("pos").get<std::vector<int>>();
    wchar_t letter = j.at("letter").get<wchar_t>();

    Symbol s(letter, id, pos);
    return s;
}

void JsonUtility::fromJsonCursorChangeReq(const json &j, int& index) {
    index = j.at("index").get<int>();
}

void JsonUtility::fromJsonRemovalRange(const json &j, std::vector<sId>& symbolsId, int &roomId) {
    symbolsId = j.at("symbolsId").get<std::vector<sId>>();
    roomId = j.at("room_id").get<int>();
}

void JsonUtility::fromJsonInsertionRange(const json &j, std::vector<json>& symbols, int& startIndex, int &roomId) {
    symbols = j.at("formattingSymVector").get<std::vector<json>>();
    startIndex = j.at("startIndex").get<int>();
    roomId = j.at("roo_id").get<int>();
}
