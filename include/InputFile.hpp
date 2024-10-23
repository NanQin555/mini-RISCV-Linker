#pragma once
#include "file.hpp"
#include "symbol.hpp"
using namespace std;
class Context;
class InputFile{
public:
    File* file;
    vector<Shdr> ElfSections;
    vector<Sym> ElfSyms;
    int64_t FirstGlobal;
    vector<uint8_t> ShStrtab;
    vector<uint8_t> SymbolStrtab;
    bool IsAlive;
    vector<Symbol*> Symbols;
    vector<Symbol> LocalSymbols;

    
    InputFile(string);
    InputFile(File*);
    void InputFIleInit(File*);
    vector<uint8_t> GetBytesFromShdr(Shdr*);
    vector<uint8_t> GetBytesFromIdx(int);
    Shdr* FindSection(uint32_t);
    void FillUpElfSyms(Shdr*);
};