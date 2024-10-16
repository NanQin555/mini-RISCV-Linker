#include "file.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    if(argc<2) {
        assert(0&&"error");
    }    
    File file(argv[1]);
    return 0;
}
