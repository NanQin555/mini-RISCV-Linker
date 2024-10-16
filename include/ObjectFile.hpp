#pragma once
#include "InputFile.hpp"

class ObjectFile: public InputFile {
public:
    Shdr* SymtabSec;
    ObjectFile(string);
    void Parse();
};