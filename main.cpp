#include "InputFile.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    if(argc<2) {
        assert(0&&"params number error");
    }    
    InputFile file(argv[1]);

    return 0;
}
  