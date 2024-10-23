#pragma once
#include <cstdint>
#include "ELFheadr.hpp"

using namespace std;
class Context;
class ObjectFile;
class InputSection;
class Symbol {
public:
    ObjectFile* File;
    InputSection* Inputsection;
    string Name;
    uint64_t Value;
    int32_t SymIdx;

    Symbol(string);
    ~Symbol() = default;
    void SetInputSection(InputSection*);
};
Symbol* GetSymbolByName(Context*, string);
Sym* ElfSym(Symbol*);
void SymbolClear(Symbol*);