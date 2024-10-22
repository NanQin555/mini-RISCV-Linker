#include "machinetype.hpp"
MachineType GetMachineTypeFromContents(vector<uint8_t> contents) {
    FileType ft = GetFileType(contents);\
    if (ft == FileType::FileTypeObject) {
        vector<uint8_t> temp = contents;
        temp.assign(contents.begin()+18, contents.end());
        uint16_t machine = ReadHeader<uint16_t>(temp);
        if (machine == (uint16_t)EM_RISCV) {
            uint8_t Class = contents[4];
            if (Class == ELFCLASS64) {
                return MachineType::RISCV64;
            }
        }
    }
    return MachineType::None;
}