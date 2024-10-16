#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cassert>
using namespace std;
class File {
public:
    string name;
    string contents;
    ifstream file;

    File(string name);
    void openFile();
    bool isELFfile();
    void readFile();
    void closeFile();
};

