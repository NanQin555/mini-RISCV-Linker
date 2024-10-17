#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cassert>
#include <elf.h>
using namespace std;
class File {
public:
    string name;
    vector<uint8_t> contents;
    ifstream file;

    File(string name);
    void openFile();
    bool isELFfile();
    void readFile();
    void closeFile();
};

bool CheckMagic(vector<uint8_t>);

