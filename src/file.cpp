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
