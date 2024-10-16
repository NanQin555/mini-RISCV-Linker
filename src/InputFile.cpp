#include "InputFile.hpp"

using namespace std;
InputFile::InputFile(string name): File(name) {
    if (contents.size() < EhdrSize) {
        assert(0&&"File too small");
    }
    Ehdr elfhead = ReadHeader<Ehdr>(contents);

    vector<uint8_t> tempContent;
    tempContent.assign(contents.begin()+elfhead.ShOff, contents.end());
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

vector<uint8_t> InputFile::GetBytesFromShdr(Shdr& s) {
    assert(contents.size() > s.Offset+s.Size && "Section header is out of range.");
    vector<uint8_t> vec;
    for(size_t i=s.Offset; i<s.Offset+s.Size; i++) {
        vec.push_back(contents[i]);
    }
    return vec;
}

vector<uint8_t> InputFile::GetBytesFromIdx(int idx) {
    Shdr s = ElfSections[idx];
    return GetBytesFromShdr(s);
}

Shdr* InputFile::FindSection(uint32_t type) {
    for(int i=0; i<ElfSections.size(); i++) {
        Shdr* s = &ElfSections[i];
        if(s->Type == type)
            return s;
    }
    return nullptr;
}

void InputFile::FillUpElfSyms(Shdr* s) {
    vector<uint8_t> bytes = GetBytesFromShdr(*s);
    int nums = bytes.size()/SymSize;
    while(nums) {
        ElfSyms.push_back(ReadHeader<Sym>(bytes));
        bytes.assign(bytes.begin()+SymSize, bytes.end());
        nums--;
    }
}