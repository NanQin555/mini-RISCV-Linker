#pragma once
#include "file.hpp"
#include "ELFheadr.hpp"
#include <vector>
using namespace std;
class InputFile: public File{
public:
    vector<Shdr> ElfSections;
    vector<Sym> ElfSyms;
    int64_t FirstGlobal;
    vector<uint8_t> ShStrtab;
    vector<uint8_t> SymbolStrtab;

    InputFile(string);
    vector<uint8_t> GetBytesFromShdr(Shdr&);
    vector<uint8_t> GetBytesFromIdx(int);
    Shdr* FindSection(uint32_t);
    void FillUpElfSyms(Shdr*);
};