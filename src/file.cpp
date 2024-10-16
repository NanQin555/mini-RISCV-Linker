#include "file.hpp"

File::File(string name): file(ifstream(name)) {
    openFile();
}

void File::openFile() {
    if(!file.is_open()) 
        assert(0&&"File can't open.");

    cout << name << endl;
    if(isELFfile()) {
        file.seekg(0,ios::end);
        cout << "File size: " << file.tellg() << endl;
    }
}
bool File::isELFfile() {
    const string prefix = "\177ELF";
    if (contents.size() < prefix.size()) {
        cout << "File is not an ELF file." << endl;
        return false;
    }
    return contents.substr(0, prefix.size()) == prefix;
}

void File::closeFile() {file.close();}
