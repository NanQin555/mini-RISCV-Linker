#pragma once
#include "InputFile.hpp"
using namespace std;
class Context;
class ObjectFile: public InputFile {
public:
    Shdr* SymtabSec;
    ObjectFile(string);
    ObjectFile(File*, bool);
    void Parse();
};