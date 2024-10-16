#include "InputFile.hpp"

using namespace std;
InputFile::InputFile(string name): File(name) {
    if (contents.size() < ELFheaderSize) {
        assert(0&&"File too small");
    }
    ELFheader elfhead = ReadHeader<ELFheader>(contents);

    string tempContent = contents.substr(elfhead.ShOff);
    SECheader sechead = ReadHeader<SECheader>(tempContent);

    uint64_t numSections = elfhead.ShNum;
    if(numSections==0) {
        numSections = (uint64_t)sechead.Size;
    }
    ElfSections.push_back(sechead);
    while(numSections > 1) {
        tempContent = tempContent.substr(SECheaderSize);
        ElfSections.push_back(ReadHeader<SECheader>(tempContent));
        numSections--;
    }

}

