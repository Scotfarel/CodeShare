#ifndef  HEADERS_JSONTYPES_H_
#define  HEADERS_JSONTYPES_H_
#include <iostream>
#include "json.hpp"
#include "headers/Symbol.h"

using nlohmann::json;
typedef std::pair<int, int> int_pair;

class jsonTypes {
// SERIALIZATION (convert json into string) -> it is obtained with method dump() (e.g. json.dump())
 public:
    static void to_json(json &j, const std::string &op, const std::string &resp,int id);
    static void to_json_join_room(json &j, const std::string &op,int id);
    static void to_json(json& j, const std::string& op);
    static void to_jsonUri(json& j, const std::string& op, const std::string& user, int id);
    static void to_json_insertion(json &j, const std::string &op, const Symbol &symbol, const int &indexInEditor, int id);
    static void to_json_cursor_change_req(json &j, const std::string &op, const int &index,int id);
    static void to_json_removal_range(json &j, const std::string &op, const std::vector<int_pair> &symbolsId, int id);
    static void to_json_insertion_range(json &j, const std::string &op, const std::vector<json> &symVector,  const int &startIndex,int id);
    static void to_json_FormattingSymbol(json &j, const Symbol &symbol);

// DESERIALIZATION (convert data into json) -> it is obtained with method parse() (e.g. json::parse(data_));
    static void from_json_insertion(const json& j, Symbol& s, int &indexInEditor);
    static void from_json(const json& j, std::string& op);
    static void from_json_join(const json &j, int &id);
    static void from_json_resp(const json &j, std::string &resp);
    static void from_json_symbols(const json &j, std::vector<Symbol> &symbols);
    static Symbol* from_json_symbol(const json &j);
    static void from_jsonUri(const json &j, int &id);
    static void from_json(const json& j, std::string& user, std::string& pass);
    static void from_json(const json &j, std::string &user, std::string &pass, std::string &email);
    static void from_json_insertion_range(const json &j, int& firstIndex, std::vector<json>& jsonSymbols);
    static void from_json_cursor_change(const json &j, std::string& username, std::string& color, int& pos);
    static void from_json_removal(const json &j, int& index);
    static void from_json_removal_range(const json& j, std::vector<int_pair>& symbolsId);
    static std::vector<json> fromFormattingSymToJson(const std::vector<Symbol>& symbols);
};
#endif  //  HEADERS_JSONTYPES_H_
