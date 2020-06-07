//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_JSONUTILITY_H
#define CODESHARE_JSONUTILITY_H

#include "json.hpp"
#include <Symbol.h>

using nlohmann::json;
typedef std::pair<int,int> sId;

class JsonUtility {

public:
    static std::vector<json> fromSymToJson(const std::vector<Symbol>& symbols);
    static std::vector<Symbol> fromJsonToFormattingSym(const std::vector<json>& jsons);
    static Symbol fromJsonSymbol(const json& j);
    static void toJsonSymbol(json &j, const Symbol &Symbol);
    static void toJsonRoomId(json &j, const std::string &operation, const int &roomId);
    static void toJsonCursorChange(json &j, const std::string &operation, const int &pos);
    static void toJsonInsertion(json &j, const std::string &operation, const Symbol &Symbol, const int &indexInEditor);
    static void toJsonRemovalRange(json &j, const std::string &operation, const std::vector<sId> &symbolsId);
    static void toJsonInsertionRange(json &j, const std::string &operation, const int &firstIndex, const std::vector<json> &symbolsJSONS, const int &roomId);
    static void fromJsonRoomId(const json &j, int& roomId);
    static void fromJsonInsertion(const json& j, Symbol& s, int &indexInEditor, int &roomId);
    static void fromJson(const json& j, std::string& operation);
    static void fromJsonCursorChangeReq(const json& j, int& index);
    static void fromJsonRemovalRange(const json& j, std::vector<sId>& symbolsId, int &roomId);
    static void fromJsonInsertionRange(const json &j, std::vector<json>& symbols, int &startIndex, int &roomId);
};

#endif //CODESHARE_JSONUTILITY_H
