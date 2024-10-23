#include "inputSection.hpp"

InputSection::InputSection(ObjectFile* file, uint32_t shndx) 
    : File(file), Shndx(shndx) {
    Shdr* shdr = this->getShdr();
    Contents = File->file->contents;
    Contents.assign(Contents.begin()+shdr->Offset, Contents.begin()+shdr->Offset+shdr->Size);
    
}

Shdr* InputSection::getShdr() {
    assert(Shndx < File->ElfSections.size());
    return &(File->ElfSections[this->Shndx]);
}

string InputSection::getName() {
    return ELFGetName(File->ShStrtab, this->getShdr()->Name);
}