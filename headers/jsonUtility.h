#ifndef  HEADERS_JSONUTILITY_H_
#define  HEADERS_JSONUTILITY_H_
#include <iostream>
#include "json.hpp"
#include "headers/symbol.h"
#include "headers/File.h"

using nlohmann::json;
typedef std::pair<int, int> sId;

class jsonUtility {
// SERIALIZATION (convert json into string) -> it is obtained with method dump() (e.g. json.dump())
 public:
    static void to_json(json &j, const std::string &op, const std::string &resp);
    static void to_json(json& j, const std::string& op, const std::string& user, const std::string& pass);
    static void to_jsonUri(json& j, const std::string& op, const std::string& user, const std::string& uri);
    static void to_json(json& j, const std::string& op, const std::string& user, const std::string& pass, const std::string& email);
    static void to_json_insertion(json &j, const std::string &op, const symbol &symbol, const int &indexInEditor);
    static void to_json_cursor_change_req(json &j, const std::string &op, const int &index);
    static void to_json_removal_range(json &j, const std::string &op, const std::vector<sId> &symbolsId);
    static void to_json_insertion_range(json &j, const std::string &op, const std::vector<json> &symVector,  const int &startIndex);
    static void to_json_FormattingSymbol(json &j, const symbol &symbol);

// DESERIALIZATION (convert data into json) -> it is obtained with method parse() (e.g. json::parse(data_));
    static void from_json_insertion(const json& j, symbol& s, int &indexInEditor);
    static void from_json(const json& j, std::string& op);
    static void from_json_resp(const json &j, std::string &resp);
    static void from_json_symbols(const json &j, std::vector<symbol> &symbols);
    static symbol* from_json_symbol(const json &j);
    static void from_jsonUri(const json& j, std::string& uri);
    static void from_json(const json& j, std::string& user, std::string& pass);
    static void from_json(const json &j, std::string &user, std::string &pass, std::string &email);
    static void from_json_insertion_range(const json &j, int& firstIndex, std::vector<json>& jsonSymbols);
    static void from_json_cursor_change(const json &j, std::string& username, std::string& color, int& pos);
    static void from_json_removal(const json &j, int& index);
    static void from_json_removal_range(const json& j, std::vector<sId>& symbolsId);
    static std::vector<json> fromFormattingSymToJson(const std::vector<symbol>& symbols);
};
#endif  //  HEADERS_JSONUTILITY_H_
