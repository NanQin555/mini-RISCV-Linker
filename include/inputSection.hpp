#pragma once
#include "ObjectFile.hpp"
#include <vector>
using namespace std;

class InputSection {
    ObjectFile* File;
    vector<uint8_t> Contents;
    uint32_t Shndx;
    
public:  
    InputSection(ObjectFile*, uint32_t);
    Shdr* getShdr();
    string getName();
};