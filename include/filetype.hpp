#pragma once
#include <cstdint>
#include <vector>
#include "file.hpp"
using namespace std;
enum FileType {
    FileTypeUnknown,
    FileTypeEmpty,
    FileTypeObject,
    FileTypeArchive
};
FileType GetFileType(vector<uint8_t>);