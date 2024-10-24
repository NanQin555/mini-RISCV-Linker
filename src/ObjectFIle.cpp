#include "ObjectFile.hpp"
#include "context.hpp"
#include "inputSection.hpp"
ObjectFile::ObjectFile(Context* ctx, string name): InputFile(name) {
    Parse(ctx);
}
ObjectFile::ObjectFile(Context* ctx, File* file, bool isAlive): InputFile(file) {
    this->IsAlive = isAlive;
    Parse(ctx);
}

void ObjectFile::Parse(Context* ctx) {

    SymtabSec = FindSection((uint32_t)SHT_SYMTAB);
    if(SymtabSec != nullptr) {
        FirstGlobal = (int64_t)SymtabSec->Info;
        FillUpElfSyms(SymtabSec);
        SymbolStrtab = GetBytesFromIdx((int64_t)SymtabSec->Link);
    }
    InitializeSections();
    InitializeSymbols(ctx);
}

void ObjectFile::InitializeSections() {
    Sections.resize(ElfSections.size());
    for(size_t i=0; i<ElfSections.size(); i++) {
        Shdr* shdr = &ElfSections[i];
        switch (shdr->Type) {
        case SHT_GROUP:
        case SHT_SYMTAB:
        case SHT_STRTAB:
        case SHT_REL:
        case SHT_RELA:
        case SHT_NULL:
            break;
        case SHT_SYMTAB_SHNDX:
            FillUpSymtabShndxSec(shdr);
            break;
        default:
            Sections[i] = new InputSection(this, (uint32_t)i);
        }
    }
}

void ObjectFile::FillUpSymtabShndxSec(Shdr* s) {
    vector<uint8_t> bs = GetBytesFromShdr(s);
    size_t nums = bs.size()/4;
    while(nums > 0) {
        SymtabShndxSec.push_back(ReadHeader<uint32_t>(bs));
        bs.assign(bs.begin()+4, bs.end());
        nums--;
    }
    return;
}

void ObjectFile::InitializeSymbols(Context* ctx) {
    if(SymtabSec == nullptr)
        return;
    
    LocalSymbols.resize((size_t)FirstGlobal, Symbol(""));
    LocalSymbols[0].File = this;

    for(size_t i=1; i<LocalSymbols.size(); i++) {
        Sym* esym =  &ElfSyms[i];
        Symbol* sym = &LocalSymbols[i];
        sym->Name = ELFGetName(SymbolStrtab, esym->Name);
        sym->File = this;
        sym->Value = esym->Val;
        sym->SymIdx = i;
        
        if(!IsAbs(esym)) {
            sym->SetInputSection(Sections[GetShndx(esym,i)]);
        }
    }
    Symbols.resize(ElfSyms.size(), new Symbol(""));
    for(size_t i=0; i<LocalSymbols.size(); i++) {
        Symbols[i] = &LocalSymbols[i];
    }
    for(size_t i=LocalSymbols.size(); i<ElfSyms.size(); i++) {
        Sym* esym = &ElfSyms[i];
        string name = ELFGetName(SymbolStrtab, esym->Name);
        Symbols[i] = GetSymbolByName(ctx, name);
    }
}

int32_t ObjectFile::GetShndx(Sym* esym, int32_t idx) {
    assert(idx>=0&&idx<(int32_t)ElfSyms.size());
    if(esym->Shndx == SHN_XINDEX) {
        return SymtabShndxSec[idx];
    }
    return esym->Shndx;
}

void ObjectFile::ResolveSymbols() {
    for (int64_t i=FirstGlobal; i< (int64_t)ElfSyms.size(); i++) {
        Symbol* sym = Symbols[i];
        Sym* esym = &ElfSyms[i];
        if (IsUndef(esym)) 
            continue;
        InputSection* isec;
        if (!IsAbs(esym)) {
            isec = GetSection(esym, i);
            if (isec == nullptr) 
                continue;
        }
        if (sym->File == nullptr) {
            sym->File = this;
            sym->SetInputSection(isec);
            sym->SymIdx = i;
        }
        
    }
}

InputSection* ObjectFile::GetSection(Sym* esym, int64_t idx) {
    return Sections[GetShndx(esym, idx)];  
}

void ObjectFile::MarkLiveObjects(Context* ctx, function<void(ObjectFile*)> feeder) {
    assert(this->IsAlive);
    for (int64_t i=FirstGlobal; i< (int64_t)ElfSyms.size(); i++) {
        Symbol* sym = Symbols[i];
        Sym* esym = &ElfSyms[i];
        if(sym->File == nullptr)
            continue;
        if(IsUndef(esym) && !sym->File->IsAlive) {
            sym->File->IsAlive = true;
            feeder(sym->File);
        }
    }
}

void ObjectFile::ClearSymbols() {
    if(Symbols.size()==0)
        return;
    for(auto it=Symbols.begin()+FirstGlobal; it!=Symbols.end(); it++) {
        Symbol* sym = *it;
        if(sym->File == this) {
            sym->Clear();
        }
    }
}