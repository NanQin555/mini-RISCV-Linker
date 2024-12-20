#pragma once
#include "InputFile.hpp"
#include <functional>
using namespace std;
class InputSection;
class Context;
class ObjectFile: public InputFile {
public:
    Shdr* SymtabSec;
    vector<InputSection*> Sections;
    vector<uint32_t> SymtabShndxSec;
    
    ObjectFile(Context*, string);
    ObjectFile(Context*, File*, bool);
    void Parse(Context*);
    void InitializeSections();
    void FillUpSymtabShndxSec(Shdr*);
    void InitializeSymbols(Context*);
    int32_t GetShndx(Sym*, int32_t);
    void ResolveSymbols();
    InputSection* GetSection(Sym*, int64_t);
    void MarkLiveObjects(Context*, function<void(ObjectFile*)>);
    void ClearSymbols();
};