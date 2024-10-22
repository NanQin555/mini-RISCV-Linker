#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cassert>
#include <elf.h>
#include "ELFheadr.hpp"
using namespace std;
class Context;
class File {
public:
    string name;
    vector<uint8_t> contents;
    File* parent;
    ifstream file;

    File(string);
    File(string, vector<uint8_t>, File*);
    ~File() {closeFile();}
    void openFile();
    void readFile();
    void closeFile();
};

bool CheckMagic(vector<uint8_t>);
File* FindLibrary(Context*, string);
