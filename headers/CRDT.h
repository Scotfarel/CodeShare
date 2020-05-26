#ifndef HEADERS_CRDT_H_
#define HEADERS_CRDT_H_
#include <vector>
#include "symbol.h"
#include <QDebug>

typedef std::pair<int,int> sId;

class CRDT {

 public:
    CRDT() = default;
    virtual ~CRDT() = default;
    symbol localInsert(int index, wchar_t value);
    std::vector<symbol> localInsert(int startIndex, std::vector<symbol> symbols);
    std::vector<sId> localErase(int startIndex, int endIndex);
    int process(int type, int indexEditor, symbol newSym);
    int process(int type, int indexEditor, std::vector<symbol> newSymbols);
    int processErase(sId id);
    void setVector(std::vector<symbol> symbols);
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
    int comparePosdx(std::vector<int> curSymPos, std::pair<int, int> curSymId, std::vector<int> newSymPos,
            std::pair<int, int> newSymId, int posIndex);
    int comparePos(std::vector<int> curSymPos, std::pair<int, int> curSymId, std::vector<int> newSymPos,
            std::pair<int, int> newSymId, int posIndex);
};
#endif  // HEADERS_CRDT_H_
