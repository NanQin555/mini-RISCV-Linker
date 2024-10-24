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

Sym* Symbol::ElfSym() {
    assert(size_t(SymIdx) < File->ElfSyms.size());
    return &File->ElfSyms[SymIdx];
}

void Symbol::Clear() {
    File = nullptr;
    Inputsection = nullptr;
    SymIdx = -1;
}

Symbol* GetSymbolByName(Context* ctx, string name) {
    auto it = ctx->SymbolMap.find(name);
    if(it != ctx->SymbolMap.end()) {
        return it->second;
    }
    ctx->SymbolMap[name] = new Symbol(name);
    return ctx->SymbolMap[name];
}