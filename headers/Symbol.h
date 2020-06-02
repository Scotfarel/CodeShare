#ifndef HEADERS_SYMBOL_H_
#define HEADERS_SYMBOL_H_
#include <vector>
#include <string>
#include <array>

class Symbol {
 private:
    wchar_t _letter;
    std::pair<int, int> _id;
    std::vector<int> _pos;

 public:
    Symbol() = default;
    Symbol(wchar_t character, std::pair<int, int> id, std::vector<int> pos);
    explicit Symbol(wchar_t character);
    std::vector<int> get_pos() const;
    wchar_t get_letter() const;
    std::pair<int, int> get_id() const;
    void set_letter(wchar_t letter);
    void set_id(std::pair<int, int> id);
    void set_pos(std::vector<int> pos);
};
#endif  // HEADERS_SYMBOL_H_
