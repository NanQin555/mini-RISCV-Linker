#include "ObjectFile.hpp"
#include "context.hpp"
ObjectFile::ObjectFile(string name): InputFile(name) {
    Parse();
}
ObjectFile::ObjectFile(File* file, bool isAlive): InputFile(file) {
    this->IsAlive = isAlive;
    Parse();
}

void ObjectFile::Parse() {
    SymtabSec = FindSection((uint32_t)SHT_SYMTAB);
    if(SymtabSec != nullptr) {
        FirstGlobal = (int64_t)SymtabSec->Info;
        FillUpElfSyms(SymtabSec);
        SymbolStrtab = GetBytesFromIdx((int64_t)SymtabSec->Link);
    }
}
