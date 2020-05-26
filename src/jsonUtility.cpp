#include "headers/jsonUtility.h"

void jsonUtility::to_json(json &j, const std::string &op, const std::string &resp) {
    j = json{
            {"operation", op},
            {"content", {{"response", resp}}}
    };
}

void jsonUtility::to_json(json &j, const std::string &op, const std::string &user, const std::string &pass) {
    j = json{
            {"operation", op},
            {"content", {{"username", user},
                         {"password", pass} }}
    };
}

void jsonUtility::to_json_insertion(json &j, const std::string &op, const symbol &symbol, const int &indexInEditor) {
    j = json{
            {"operation", op},
            {"id", symbol.getId()},
            {"pos", symbol.getPos()},
            {"letter", symbol.getLetter()},
            {"indexInEditor", indexInEditor}
    };
}

void jsonUtility::to_json_FormattingSymbol(json &j, const symbol &symbol) {
    j = json{
            {"id", symbol.getId()},
            {"pos", symbol.getPos()},
            {"letter", symbol.getLetter()},
    };
}

void jsonUtility::to_json_cursor_change_req(json &j, const std::string &op, const int &index) {
    j = json {
            {"operation", op},
            {"index", index}
    };
}

void jsonUtility::to_json_removal_range(json &j, const std::string &op, const std::vector<sId> &symbolsId) {
    j = json{
            {"operation", op},
            {"symbolsId", symbolsId}
    };
}


void jsonUtility::to_jsonUri(json &j, const std::string &op, const std::string &user, const std::string &uri) {
    j = json{
            {"operation", op},
            {"content", {{"username", user},
                         {"uri", uri}}}
    };
}

void jsonUtility::to_json(json &j, const std::string &op, const std::string &user, const std::string &pass, const std::string &email) {
    j = json{
            {"operation", op},
            {"content", {{"username", user},
                          {"password", pass},
                          {"email", email} }}
    };
}


void jsonUtility::to_json_insertion_range(json &j, const std::string &op, const std::vector<json> &symVector, const int &startIndex) {
    j = json{
            {"operation", op},
            {"formattingSymVector", symVector}, //JSON vector
            {"startIndex", startIndex}
    };
}

void jsonUtility::from_json(const json &j, std::string &op) {
    op = j.at("operation").get<std::string>();
}

void jsonUtility::from_json_resp(const json &j, std::string &resp) {
    resp = j.at("content").at("response").get<std::string>();
}

/* We need to use this 'from_json' to deserialize std::vector<symbol> (see function from_json_symbols) */
void from_json(const json& j, symbol& s) {
    auto letter = j.at("letter").get<wchar_t>();
    auto id = j.at("id").get<std::pair<int,int>>();
    auto pos = j.at("pos").get<std::vector<int>>();
    s = symbol(letter, id, pos);
}

void jsonUtility::from_json_insertion(const json& j, symbol& s, int &indexInEditor) {
    indexInEditor = j.at("indexInEditor").get<int>();
    auto letter = j.at("letter").get<wchar_t>();
    auto id = j.at("id").get<std::pair<int,int>>();
    auto pos = j.at("pos").get<std::vector<int>>();
    s = symbol(letter, id, pos);
}

void jsonUtility::from_json_symbols(const json &j, std::vector<symbol>& symbols) {
    symbols = j.at("content").at("symVector").get<std::vector<symbol>>(); //use from_json previously defined
}

void jsonUtility::from_json_insertion_range(const json &j, int& firstIndex, std::vector<json>& jsonSymbols) {
    firstIndex = j.at("firstIndexRange").get<int>();
    jsonSymbols = j.at("symbols").get<std::vector<json>>();
}

symbol* jsonUtility::from_json_symbol(const json &j) {
    wchar_t letter;
    std::pair<int,int> id;
    std::vector<int> pos;

    try {
        //get symbol values from json
        letter = j.at("letter").get<wchar_t>();
        id = j.at("id").get<std::pair<int, int>>();
        pos = j.at("pos").get<std::vector<int>>();
    }
    catch (json::exception& e) {
        std::cerr << "Message: " << e.what() << '\n' << "exception id: " << e.id << std::endl;
        return nullptr;
    }
    //now create the symbol
    symbol *s = new symbol(letter, id, pos);
    return s;
}


void jsonUtility::from_json(const json &j, std::string &user, std::string &pass) {
    user = j.at("content").at("username").get<std::string>();
    pass = j.at("content").at("password").get<std::string>();
}

void jsonUtility::from_json(const json &j, std::string &user, std::string &pass, std::string &email) {
    user = j.at("content").at("username").get<std::string>();
    pass = j.at("content").at("password").get<std::string>();
    email = j.at("content").at("email").get<std::string>();
}

void jsonUtility::from_jsonUri(const json &j, std::string &uri) {
    uri = j.at("content").at("uri").get<std::string>();
}

void jsonUtility::from_json_removal(const json &j, int& index) {
    index = j.at("index").get<int>();
}

void jsonUtility::from_json_cursor_change(const json &j, std::string& username, std::string& color, int& pos) {
    username = j.at("username").get<std::string>();
    color = j.at("color").get<std::string>();
    pos = j.at("pos").get<int>();
}

void jsonUtility::from_json_removal_range(const json &j, std::vector<sId>& symbolsId) {
    symbolsId = j.at("symbolsId").get<std::vector<sId>>();
}


std::vector<json> jsonUtility::fromFormattingSymToJson(const std::vector<symbol>& symbols) {
    if(symbols.empty())
        return json::array();

    std::vector<json> jsons;
    for (auto const &sym: symbols) {
        json j;
        jsonUtility::to_json_FormattingSymbol(j, sym); //convert sym into json
        jsons.push_back(j);
    }
    return jsons;
}