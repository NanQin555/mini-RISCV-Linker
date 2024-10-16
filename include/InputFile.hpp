#pragma once
#include "file.hpp"
#include "ELFheadr.hpp"
#include <vector>
using namespace std;
class InputFile: public File{
    vector<SECheader> ElfSections;
public:
    InputFile(string);
};