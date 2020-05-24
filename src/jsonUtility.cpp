#include "jsonUtility.h"

void jsonUtility::to_json(json &j, const std::string &op, const std::string &resp) {
    j = json{
            {"operation", op},
            {"content", {
                {"response", resp}
            }}
    };
}

void jsonUtility::to_json(json &j, const std::string &op, const std::string &user, const std::string &pass) {
    j = json{
            {"operation", op},
            {"content", {
                {"username", user},
                {"password", pass}
            }}
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

void jsonUtility::to_json_format_range(json &j, const std::string &op, const std::vector<sId> &symbolsId, const int &format) {
    j = json{
            {"operation", op},
            {"symbolsId", symbolsId},
            {"format", format}
    };
}

void jsonUtility::to_json_fontsize_change(json &j, const std::string &op, const std::vector<sId> &symbolsId, const int &fontSize) {
    j = json{
            {"operation", op},
            {"symbolsId", symbolsId},
            {"fontSize", fontSize}
    };
}

void jsonUtility::to_json_alignment_change(json &j, const std::string &op, const std::vector<sId> &symbolsId, const int &alignment) {
    j = json{
            {"operation", op},
            {"symbolsId", symbolsId},
            {"alignment", alignment}
    };
}

void jsonUtility::to_json_fontfamily_change(json &j, const std::string &op, const std::vector<sId> &symbolsId, const std::string &fontFamily) {
    j = json{
            {"operation", op},
            {"symbolsId", symbolsId},
            {"fontFamily", fontFamily}
    };
}

void jsonUtility::to_json_collab_colors(json &j, const std::string &op, const std::string &uri) {
    j = json{
        {"operation", op},
        {"uri", uri}
    };
}

void jsonUtility::to_jsonFilename(json &j, const std::string &op, const std::string &user, const std::string &filename) {
    j = json{
            {"operation", op},
            {"content", {
                {"username", user},
                {"filename", filename}
            }}
    };
}

void jsonUtility::to_jsonRenamefile(json &j, const std::string &op, const std::string &nameFile, const std::string &uri, const std::string &username) {
    j = json{
            {"operation", op},
            {"content", {
                {"newNameFile", nameFile},
                {"uri", uri},
                {"username", username}
            }}
    };
}

void jsonUtility::to_jsonUri(json &j, const std::string &op, const std::string &user, const std::string &uri) {
    j = json{
            {"operation", op},
            {"content", {
                {"username", user},
                {"uri", uri}
            }}
    };
}

void jsonUtility::to_json_inviteURI(json &j, const std::string &op, const std::string &invited, const std::string &applicant, const std::string &uri) {
    j = json{
            {"operation", op},
            {"invited", invited},
            {"applicant", applicant},
            {"uri", uri}
    };
}

void jsonUtility::to_json(json &j, const std::string &op, const std::string &user, const std::string &pass, const std::string &email) {
    j = json{
            {"operation", op},
            {"content", {
                {"username", user},
                {"password", pass},
                {"email", email}
            }}
    };
}

void jsonUtility::to_jsonUser(json &j, const std::string &op, const std::string &user) {
    j = json{
            {"operation", op},
            {"content", {
                {"username", user}
            }}
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

void jsonUtility::from_json_inviteURI(const json &j, std::string &op) {
    op = j.at("content").at("response").get<std::string>();
}

void jsonUtility::from_json_collab_colors_map(const json &j, std::string &op) {
    op = j.at("response").get<std::string>();
}

void jsonUtility::from_json_resp(const json &j, std::string &resp) {
    resp = j.at("content").at("response").get<std::string>();
}

/* We need to use this 'from_json' to deserialize std::vector<symbol> (see function from_json_symbols) */
void from_json(const json& j, symbol& s) {
    wchar_t letter = j.at("letter").get<wchar_t>();
    std::pair<int,int> id = j.at("id").get<std::pair<int,int>>();
    std::vector<int> pos = j.at("pos").get<std::vector<int>>();
    s = symbol(letter, id, pos);
}

void jsonUtility::from_json_insertion(const json& j, symbol& s, int &indexInEditor) {
    indexInEditor = j.at("indexInEditor").get<int>();
    wchar_t letter = j.at("letter").get<wchar_t>();
    std::pair<int,int> id = j.at("id").get<std::pair<int,int>>();
    std::vector<int> pos = j.at("pos").get<std::vector<int>>();
    s = symbol(letter, id, pos);
}

void jsonUtility::from_json_symbols(const json &j, std::vector<symbol>& symbols) {
    symbols = j.at("content").at("symVector").get<std::vector<symbol>>(); //use from_json previously defined
}

void jsonUtility::from_json_symbolsAndFilename(const json &j, std::vector<symbol>& symbols, std::string& filename) {
    filename = j.at("content").at("filename").get<std::string>();
    symbols = j.at("content").at("symVector").get<std::vector<symbol>>(); //use from_json previously defined
}

void jsonUtility::from_json_filename(const json &j, std::string& filename) {
    filename = j.at("content").at("filename").get<std::string>();
}

void jsonUtility::from_json_insertion_range(const json &j, int& firstIndex, std::vector<json>& jsonSymbols) {
    firstIndex = j.at("firstIndexRange").get<int>();
    jsonSymbols = j.at("symbols").get<std::vector<json>>();
}

void jsonUtility::from_json_rename_file(const json &j, std::string &resp, std::string& filename) {
    filename = j.at("content").at("filename").get<std::string>();
    resp = j.at("content").at("response").get<std::string>();
}

void jsonUtility::from_json_files(const json &j, std::vector<json>& jsonFiles) {
    jsonFiles = j.at("content").at("vectorFile").get<std::vector<json>>();
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

File* jsonUtility::from_json_file(const json &j) {
    std::string idfile;
    std::string filename;
    std::string owner;
    std::string timestamp;

    try {
        //get symbol values from json
        idfile = j.at("idfile").get<std::string>();
        filename = j.at("filename").get<std::string>();
        owner = j.at("owner").get<std::string>();
        timestamp = j.at("timestamp").get<std::string>();

    } catch (json::exception& e) {
        std::cerr << "Message: " << e.what() << '\n' << "exception id: " << e.id << std::endl;
        return nullptr;
    }
    //now create the file
    File *f = new File(idfile, filename, owner, timestamp);
    return f;
}

void jsonUtility::from_json_usernameLogin(const json &j, std::string &name, std::string &color, std::string &mail, int &siteId) {
    name = j.at("content").at("usernameLogin").get<std::string>();
    color = j.at("content").at("colorLogin").get<std::string>();
    mail = j.at("content").at("mailLogin").get<std::string>();
    siteId = j.at("content").at("siteId").get<int>();
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

void jsonUtility::from_json_collab_colors_resp(const json &j, myCollabColorsMap& collabColorsMap) {
    collabColorsMap = j.at("collabColorsMap").get<myCollabColorsMap>();
}

void jsonUtility::from_json_user_offline(const json &j, std::string &username, myCollabColorsMap& collabColorsMap) {
    username = j.at("username").get<std::string>();
    collabColorsMap = j.at("collabColorsMap").get<myCollabColorsMap>();
}

void jsonUtility::from_json_removal_range(const json &j, std::vector<sId>& symbolsId) {
    symbolsId = j.at("symbolsId").get<std::vector<sId>>();
}


std::vector<json> jsonUtility::fromFormattingSymToJson(const std::vector<symbol>& symbols) {
    if(symbols.empty())
        return json::array();

    // Get jsons from symbols
    std::vector<json> jsons;
    for (auto const &sym: symbols) {
        json j;
        jsonUtility::to_json_FormattingSymbol(j, sym); //convert sym into json
        jsons.push_back(j);
    }
    return jsons;
}
