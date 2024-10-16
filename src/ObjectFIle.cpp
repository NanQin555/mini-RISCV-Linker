#include "ObjectFile.hpp"

ObjectFile::ObjectFile(string name): InputFile(name) {
    Parse();
}

void ObjectFile::Parse() {
    SymtabSec = FindSection((uint32_t)SHT_SYMTAB);
    if(SymtabSec != nullptr) {
        FirstGlobal = (int64_t)SymtabSec->Info;
        FillUpElfSyms(SymtabSec);
        SymbolStrtab = GetBytesFromIdx((int64_t)SymtabSec->Link);
    }
    // for(auto it=ElfSyms.begin(); it!=ElfSyms.end(); ++it) {
    //     Sym sym = *it;
    //     cout << ELFGetName(SymbolStrtab, sym.Name) << endl;
    // }
}