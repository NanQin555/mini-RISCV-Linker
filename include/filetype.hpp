#pragma once
#include <cstdint>
#include <vector>
#include "ObjectFile.hpp"
using namespace std;
enum FileType {
    FileTypeUnknown,
    FileTypeEmpty,
    FileTypeObject
};

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
    return FileType::FileTypeUnknown;
}   