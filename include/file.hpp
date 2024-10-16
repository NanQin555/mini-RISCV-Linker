
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cassert>
using namespace std;
class File {
private:
    string name;
    string contents;
    ifstream file;
public:
    File(string name);
    void openFile();
    bool isELFfile();
    void closeFile();
};