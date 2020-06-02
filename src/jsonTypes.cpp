#include "headers/jsonTypes.h"

void jsonTypes::to_json(json &j, const std::string &op, const std::string &resp, int id) {
    j = json{
            {"operation", op},
            {"content",   {"response", resp},
            {"room_id",   id}}
    };
}

void jsonTypes::to_json(json &j, const std::string &op) {
    j = json{
            {"operation", op}
    };
}

void jsonTypes::to_json_join_room(json &j, const std::string &op, int id) {
    j = json{
            {"operation", op},
            {"room_id",   id}
    };
}

void
jsonTypes::to_json_insertion(json &j, const std::string &op, const Symbol &symbol, const int &indexInEditor, int id) {
    j = json{
            {"operation",     op},
            {"id", symbol.get_id()},
            {"pos", symbol.get_pos()},
            {"letter", symbol.get_letter()},
            {"indexInEditor", indexInEditor},
            {"room_id",       id}
    };
}

void jsonTypes::to_json_FormattingSymbol(json &j, const Symbol &symbol) {
    j = json{
            {"id", symbol.get_id()},
            {"pos", symbol.get_pos()},
            {"letter", symbol.get_letter()}
    };
}

void jsonTypes::to_json_cursor_change_req(json &j, const std::string &op, const int &index, int id) {
    j = json{
            {"operation", op},
            {"index",     index},
            {"room_id",   id}
    };
}

void jsonTypes::to_json_removal_range(json &j, const std::string &op, const std::vector<int_pair> &symbolsId, int id) {
    j = json{
            {"operation", op},
            {"symbolsId", symbolsId},
            {"room_id",   id}
    };
}


void jsonTypes::to_jsonUri(json &j, const std::string &op, const std::string &user, int id) {
    j = json{
            {"operation", op},
            {"content", {{"username", user},
                         {"room_id", id}}
            }
    };
}


void jsonTypes::to_json_insertion_range(json &j, const std::string &op, const std::vector<json> &symVector,
                                        const int &startIndex,int id) {
    j = json{
            {"operation",           op},
            {"formattingSymVector", symVector},  // JSON vector
            {"startIndex",          startIndex},
            {"room_id",             id}
    };
}

void jsonTypes::from_json(const json &j, std::string &op) {
    op = j.at("operation").get<std::string>();
}

void jsonTypes::from_json_resp(const json &j, std::string &resp) {
    resp = j.at("content").at("response").get<std::string>();
}
void jsonTypes::from_json_join(const json &j, int &id) {
     id = j.at("room_id").get<int>();
}
/* We need to use this 'from_json' to deserialize std::vector<Symbol> (see function from_json_symbols) */
void from_json(const json &j, Symbol &s) {
    auto letter = j.at("letter").get<wchar_t>();
    auto id = j.at("id").get<std::pair<int, int>>();
    auto pos = j.at("pos").get<std::vector<int>>();
    s = Symbol(letter, id, pos);
}

void jsonTypes::from_json_insertion(const json &j, Symbol &s, int &indexInEditor) {
    indexInEditor = j.at("indexInEditor").get<int>();
    auto letter = j.at("letter").get<wchar_t>();
    auto id = j.at("id").get<std::pair<int, int>>();
    auto pos = j.at("pos").get<std::vector<int>>();
    s = Symbol(letter, id, pos);
}

void jsonTypes::from_json_symbols(const json &j, std::vector<Symbol> &symbols) {
    symbols = j.at("content").at("symVector").get<std::vector<Symbol>>();  // use from_json previously defined
}

void jsonTypes::from_json_insertion_range(const json &j, int &firstIndex, std::vector<json> &jsonSymbols) {
    firstIndex = j.at("firstIndexRange").get<int>();
    jsonSymbols = j.at("symbols").get<std::vector<json>>();
}

void jsonTypes::from_jsonUri(const json &j, int &id) {
    id = j.at("room_id").get<int>();
}

Symbol *jsonTypes::from_json_symbol(const json &j) {
    wchar_t letter;
    std::pair<int, int> id;
    std::vector<int> pos;

    try {
        // get Symbol values from json
        letter = j.at("letter").get<wchar_t>();
        id = j.at("id").get<std::pair<int, int>>();
        pos = j.at("pos").get<std::vector<int>>();
    }
    catch (json::exception &e) {
        std::cerr << "Message: " << e.what() << '\n' << "exception id: " << e.id << std::endl;
        return nullptr;
    }
    Symbol *s = new Symbol(letter, id, pos);
    return s;
}

void jsonTypes::from_json(const json &j, std::string &user, std::string &pass, std::string &email) {
    user = j.at("content").at("username").get<std::string>();
    pass = j.at("content").at("password").get<std::string>();
    email = j.at("content").at("email").get<std::string>();
}

void jsonTypes::from_json_removal(const json &j, int &index) {
    index = j.at("index").get<int>();
}

void jsonTypes::from_json_cursor_change(const json &j, std::string &username, std::string &color, int &pos) {
    username = j.at("username").get<std::string>();
    color = j.at("color").get<std::string>();
    pos = j.at("pos").get<int>();
}

void jsonTypes::from_json_removal_range(const json &j, std::vector<int_pair> &symbolsId) {
    symbolsId = j.at("symbolsId").get<std::vector<int_pair>>();
}


std::vector<json> jsonTypes::fromFormattingSymToJson(const std::vector<Symbol> &symbols) {
    if (symbols.empty())
        return json::array();

    std::vector<json> jsons;
    for (auto const &sym : symbols) {
        json j;
        jsonTypes::to_json_FormattingSymbol(j, sym);
        jsons.push_back(j);
    }
    return jsons;
}
