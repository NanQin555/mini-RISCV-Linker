#include "InputFile.hpp"
#include "context.hpp"
#include "utils.hpp"
using namespace std;

InputFile::InputFile(string name): file(new File(name)) {
    InputFIleInit(file);
}

InputFile::InputFile(File* file): file(file) {
    InputFIleInit(file);
}

void InputFile::InputFIleInit(File* file) {
    FirstGlobal = 0;
    if (file->contents.size() < EhdrSize) {
        assert(0&&"File too small");
    }
    CheckMagic(file->contents);
    
    Ehdr elfhead = ReadHeader<Ehdr>(file->contents);

    vector<uint8_t> tempContent;
    tempContent.assign(file->contents.begin()+elfhead.ShOff, file->contents.end());
    Shdr sechead = ReadHeader<Shdr>(tempContent);

    uint64_t numSections = elfhead.ShNum;
    if(numSections==0) {
        numSections = (uint64_t)sechead.Size;
    }
    ElfSections.push_back(sechead);
    while(numSections > 1) {
        tempContent.assign(tempContent.begin() + ShdrSize, tempContent.end());
        ElfSections.push_back(ReadHeader<Shdr>(tempContent));
        numSections--;
    }
 
    uint64_t shstrndx = elfhead.ShStrndx==SHN_XINDEX?sechead.Link:elfhead.ShStrndx;
    ShStrtab = GetBytesFromIdx(shstrndx);
}



vector<uint8_t> InputFile::GetBytesFromShdr(Shdr* s) {
    assert(file->contents.size() > s->Offset+s->Size && "Section header is out of range.");
    vector<uint8_t> vec;
    for(size_t i=s->Offset; i<s->Offset+s->Size; i++) {
        vec.push_back(file->contents[i]);
    }
    return vec;
}

vector<uint8_t> InputFile::GetBytesFromIdx(int idx) {
    Shdr s = ElfSections[idx];
    return GetBytesFromShdr(&s);
}

Shdr* InputFile::FindSection(uint32_t type) {
    for(size_t i=0; i<ElfSections.size(); i++) {
        Shdr* s = &ElfSections[i];
        if(s->Type == type)
            return s;
    }
    return nullptr;
}

void InputFile::FillUpElfSyms(Shdr* s) {
    vector<uint8_t> bytes = GetBytesFromShdr(s);
    ElfSyms = ReadSlice<Sym>(bytes, SymSize);
    return;
}