//
// Created by ivan on 5/24/20.
//

#ifndef CODESHARE_USER_H
#define CODESHARE_USER_H

#include <vector>

#include "MsgContext.h"
#include "Symbol.h"

typedef std::pair<int,int> sId;

class User {

private:
    int id;
    std::string currentFile;
    std::string username;
    std::vector<Symbol> symbols;
    int cmpPosX(std::vector<int> symPos, std::pair<int,int> symId, std::vector<int> newSymPos,
                std::pair<int,int> newSymId, int pos);
    int cmpPos(std::vector<int> symPos, std::pair<int,int> symId, std::vector<int> newSymPos,
               std::pair<int,int> newSymId, int pos);

public:
    virtual ~User() = default;
    virtual void deliver(const MsgContext& msg) = 0;

    int getId() const;
    int getIndexById(const std::vector<Symbol>& roomSymbols, sId id);
    std::string getCurrentFile();
    std::string getUsername();

    void setSymbols(std::vector<Symbol> symbols);
    void setCurrentFile(std::string uri);
    void setUsername(std::string userName);
    void setSiteId(int edId);

    int process(int type, int indexEditor, const std::vector<Symbol>& roomSymbols, const Symbol& newSymbol);
    int process(int type, int indexEditor, const std::vector<Symbol>& roomSymbols, const std::vector<Symbol>& newSymbols);

    std::string to_string();
    std::vector<Symbol> getSymbols();
};

#endif //CODESHARE_USER_H
