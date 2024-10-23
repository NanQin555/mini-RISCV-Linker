#pragma once
#include <cstdint>
#include <vector>
#include "file.hpp"
using namespace std;
class Context;
enum FileType {
    FileTypeUnknown,
    FileTypeEmpty,
    FileTypeObject,
    FileTypeArchive
};
FileType GetFileType(vector<uint8_t>);
void CheckFileCompatibility(Context* ctx, File* file);