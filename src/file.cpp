#include <filesystem>
#include "file.hpp"
#include "context.hpp"
using namespace std;
string current_path = filesystem::current_path().string();

File::File(string name): name(name), file(ifstream(name)) {
#ifdef DEBUG
    cout << "Creating File object for: " << name << endl;
#endif
    openFile();
    readFile();
}

File::File(string name, vector<uint8_t> contents, File* file):
    name(name), contents(contents), parent(file) {
#ifdef DEBUG
    cout << "Creating File object with contents for: " << name << endl;
#endif
}

void File::openFile() {
    if(!file.is_open()) {
        name = current_path + "/../" + name;
        file = ifstream(name);
        if(!file.is_open())
            cout << "File can't open" << endl;
    }
}

void File::readFile() {
    file.seekg(0, ios::end);
    streampos fileSizePos = file.tellg();
    size_t fileSize = static_cast<size_t>(fileSizePos);
    file.seekg(0, ios::beg);

    const size_t bufferSize = 1024 * 1024;
    contents.resize(fileSize);

    char* buffer = new char[fileSize];
    size_t totalRead = 0;
    while(totalRead < fileSize) {
        size_t bytesToRead = min(bufferSize, static_cast<size_t>(fileSize - totalRead));
        file.read(buffer, bytesToRead);
        if (file.gcount() != static_cast<streamsize>(bytesToRead)) {
            throw runtime_error("Read file failed!");
        }
        memcpy(&contents[totalRead], buffer, bytesToRead);
        totalRead += bytesToRead;
    }
    delete[] buffer;
}

void File::closeFile() {file.close();}

bool CheckMagic(vector<uint8_t> contents) {
    const string prefix = "\177ELF";
    if(!HasPrefix(contents, prefix)) {
        cout << "File is not an ELF file." << endl;
        return false;
    }
    return true;
}

File* OpenLibrary(string filepath) {
    ifstream file(filepath);
    if(file.is_open()) {
        return new File(filepath);
    }
    return nullptr;
}

File* FindLibrary(Context* ctx, string name) {
    for(auto dir: ctx->Args.LibraryPaths) {
        string stem = dir + "/lib" + name + ".a";
        if(File* file = OpenLibrary(stem); file != nullptr) 
            return file;
    }
    assert(0&&"Library not found");
    return nullptr;
}