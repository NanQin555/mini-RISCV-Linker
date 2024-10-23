#include "symbol.hpp"
#include "context.hpp"
#include "inputSection.hpp"
#include "ObjectFile.hpp"
Symbol::Symbol(string name) 
    : File(nullptr), Inputsection(nullptr),
    Name(name), Value(0), SymIdx(-1) {}

void Symbol::SetInputSection(InputSection* isec) {
    Inputsection = isec;
}

Symbol* GetSymbolByName(Context* ctx, string name) {
    auto it = ctx->SymbolMap.find(name);
    if(it != ctx->SymbolMap.end()) {
        return it->second;
    }
    // Symbol temp(name);
    // ctx->SymbolMap[name] = &temp;
    ctx->SymbolMap[name] = new Symbol(name);
    return ctx->SymbolMap[name];
}

Sym* ElfSym(Symbol* s) {
    assert(size_t(s->SymIdx) < s->File->ElfSyms.size());
    return &s->File->ElfSyms[s->SymIdx];
}

void SymbolClear(Symbol* s) {
    s->File = nullptr;
    s->Inputsection = nullptr;
    s->SymIdx = -1;
}