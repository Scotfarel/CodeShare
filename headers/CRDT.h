#ifndef HEADERS_CRDT_H_
#define HEADERS_CRDT_H_
#include <vector>
#include "Symbol.h"
#include <QDebug>

typedef std::pair<int,int> int_pair;

class CRDT {

 public:
    CRDT() = default;
    virtual ~CRDT() = default;
    Symbol localInsert(int index, wchar_t value);
    std::vector<Symbol> localInsert(int startIndex, std::vector<Symbol> symbols);
    std::vector<int_pair> localErase(int startIndex, int endIndex);
    int process(int type, int indexEditor, const Symbol& newSym);
    int process(int type, int indexEditor, std::vector<Symbol> newSymbols);
    int processErase(int_pair id);
    void set_symbols(std::vector<Symbol> symbols);

    std::vector<Symbol> get_symbols();

 private:
    std::vector<Symbol> _symbols;
    int _counter = 0;
    int _siteId;
    std::vector<int> generate_pos(int index);
    std::vector<int> generate_pos_between(std::vector<int> pos1, std::vector<int> pos2, std::vector<int> new_pos = {});
    int compare_posdx(std::vector<int> cur_sym_pos, std::pair<int, int> cur_sym_id, std::vector<int> new_sym_pos,
                      std::pair<int, int> newSymId, int posIndex);
    int compare_pos(std::vector<int> curSymPos, std::pair<int, int> curSymId, std::vector<int> newSymPos,
                    std::pair<int, int> newSymId, int posIndex);
};
#endif  // HEADERS_CRDT_H_
