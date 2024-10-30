#include "inputSection.hpp"

InputSection::InputSection(ObjectFile* file, uint32_t shndx) 
    : File(file), Shndx(shndx), isAlive(true) {
    Shdr* shdr = this->getShdr();
    Contents = File->file->contents;
    Contents.assign(Contents.begin()+shdr->Offset, Contents.begin()+shdr->Offset+shdr->Size);
    // assert(shdr->Flags & (uint64_t)SHF_COMPRESSED == 0);
    ShSize = (uint32_t)shdr->Size;
    
    auto toP2Align = [](uint64_t align) -> uint8_t {
        if(align == 0) 
            return 0;
        for(int i=0; i<64; i++) {
            if((uint64_t)1<<i == align)
                return uint8_t(i);
        }
        assert(false);
    };
    P2Align = toP2Align(shdr->AddrAlign);
}

Shdr* InputSection::getShdr() {
    assert(Shndx < (uint32_t)File->ElfSections.size());
    return &(File->ElfSections[this->Shndx]);
}

string InputSection::getName() {
    return ELFGetName(File->ShStrtab, this->getShdr()->Name);
}