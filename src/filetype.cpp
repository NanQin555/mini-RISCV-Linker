#include "filetype.hpp"

FileType GetFileType(vector<uint8_t> contents) {
    if (contents.size()==0)
        return FileType::FileTypeEmpty;
    if (CheckMagic(contents)) {
        contents.assign(contents.begin()+16, contents.end());
        uint16_t et = ReadHeader<uint16_t>(contents);
        switch (et) {
            case ET_REL: 
                return FileType::FileTypeObject;
                break;
            default:
                return FileType::FileTypeUnknown;
                break;
        }
    }
    if (HasPrefix(contents, string("!<arch>\n"))) {
        return FileType::FileTypeArchive;
    }
    return FileType::FileTypeUnknown;
}   