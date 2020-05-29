//
// Created by ivan on 5/21/20.
//

#ifndef CODESHARE_USER_H
#define CODESHARE_USER_H

#include <vector>

#include "MsgContext.h"
#include "Symbol.h"


typedef std::pair<int, int> sId;


//  Class that contains users info
//  Grants methods to calculate an indexes for a new symbol element
class User {
private:
    std::string editingText = "TextShare";
    std::vector<Symbol> symbols;

    //  Compare positions of symbols for correct position
    int cmpPosX(std::vector<int> symPos, sId symId, std::vector<int> newSymPos, sId newSymId, int pos);

    int cmpPos(std::vector<int> symPos, sId symId, std::vector<int> newSymPos, sId newSymId, int pos);

public:
    virtual ~User() = default;

    //  Function to be overrided by derived session class, pure virtual
    virtual void deliver(const MsgContext &msg) = 0;

    //  Getters
    std::string getEditingText();

    std::vector<Symbol> getSymbols();

    //  Setters
    void setSymbols(std::vector<Symbol> symbols);

    void setEditingText(std::string textName);

    //  Getting an index in symbols map for a new symbol
    int getSymbolIndex(int indexEditor, const std::vector<Symbol> &roomSymbols, const Symbol &symbol);

    int getSymbolIndexById(const std::vector<Symbol> &roomSymbols, sId id);

    //  Formatting
    std::string symbolsToString();
};

#endif //CODESHARE_USER_H
