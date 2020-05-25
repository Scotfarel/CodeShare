#ifndef CRDT_H
#define CRDT_H

#include <vector>
#include <headers/symbol.h>
#include <QDebug>

typedef std::pair<int,int> sId;

class crdt {

public:
    crdt() = default;
    virtual ~crdt() = default;
    symbol localInsert(int index, wchar_t value);
    std::vector<symbol> localInsert(int startIndex, std::vector<symbol> symbols);
    std::vector<sId> localErase(int startIndex, int endIndex);
    int process(int type, int indexEditor, symbol newSym);
    int process(int type, int indexEditor, std::vector<symbol> newSymbols);
    int processErase(sId id);
    void setSiteId(int id);
    void setCounter(int counter);
    void setSymbols(std::vector<symbol> symbols);
    int getCounter();
    int getSiteId();
    std::vector<symbol> getSymbols();

private:
    std::vector<symbol> _symbols;
    int _counter = 0;
    int _siteId;
    std::vector<int> generatePos(int index);
    std::vector<int> generatePosBetween(std::vector<int> pos1, std::vector<int> pos2, std::vector<int> newPos = {});
    int comparePosdx(std::vector<int> curSymPos, std::pair<int,int> curSymId, std::vector<int> newSymPos, std::pair<int,int> newSymId, int posIndex);
    int comparePos(std::vector<int> curSymPos, std::pair<int,int> curSymId, std::vector<int> newSymPos, std::pair<int,int> newSymId, int posIndex);

};

#endif // CRDT_H
