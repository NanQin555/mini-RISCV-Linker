#include "file.hpp"

File::File(string name): name(name), file(ifstream(name)) {
    openFile();
    readFile();
    closeFile();
}

void File::openFile() {
    if(!file.is_open())
        assert(0&&"File can't open.");
    cout << name << ": ";
    isELFfile();

}
bool File::isELFfile() {
    const string prefix = "\177ELF";
    char buffer[5];
    file.read(buffer, 4);
    string temp(buffer, 4);
    if(temp != prefix) {
        cout << "File is not an ELF file." << endl;
        assert(0&&"not elf");
        return false;
    }
    return true;
}

void File::readFile() {
    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();
    file.seekg(0, ios::beg);

    const size_t bufferSize = 1024 * 1024;
    contents.reserve(fileSize);
    vector<char> buffer(bufferSize);
    while (file.read(buffer.data(), bufferSize)) {
        contents.append(buffer.data(), file.gcount());
    }
    contents.append(buffer.data(), file.gcount());
}

void File::closeFile() {file.close();}
