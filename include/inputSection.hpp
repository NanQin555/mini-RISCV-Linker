#pragma once
#include "ObjectFile.hpp"
#include <vector>
using namespace std;

class InputSection {
    ObjectFile* File;
    vector<uint8_t> Contents;
    uint32_t Shndx;
    uint32_t ShSize;
    bool isAlive;
    uint8_t P2Align;
    
public:  
    InputSection(ObjectFile*, uint32_t);
    Shdr* getShdr();
    string getName();
};