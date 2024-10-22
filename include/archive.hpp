#pragma once
#include "filetype.hpp"
#include "ObjectFile.hpp"

vector<File*> ReadArchiveMembers(File* file) {
    assert(GetFileType(file->contents)==FileType::FileTypeArchive&&"not archive file");
    size_t pos = 8;
    vector<uint8_t> strTab;
    vector<File*> files;
    // 2 byte aligned
    while (file->contents.size() - pos > 1) {
        if (pos % 2 == 1)
            pos += 1;
        vector<uint8_t> temp = file->contents;
        temp.assign(temp.begin()+pos, temp.end());
        Arhdr hdr = ReadHeader<Arhdr>(temp);
        size_t data_start = pos + ArdrSize;
        pos = data_start + GetArhdrSize(&hdr);
        size_t data_end = pos;
        temp.assign(file->contents.begin()+data_start, file->contents.begin()+data_end);
        if (IsSymtab(&hdr))
            continue;
        else if (IsStrtab(&hdr)) {
            strTab = temp;
            continue;
        }
        files.emplace_back(new File(ReadArhdrName(&hdr, strTab), temp, file));
    }
    return files;
}