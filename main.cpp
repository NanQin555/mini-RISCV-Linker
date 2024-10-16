#include "ObjectFile.hpp"
using namespace std;
#ifdef DEBUG
void printArgs(int argc, char* argv[]) {
    cout << "Args list: " << endl;
    for(int i=0; i<argc; i++)
        cout << argv[i] << endl;
    cout << endl;
}
#endif
vector<string> parseArgs(int argc, char* argv[]) {
#ifdef DEBUG
    printArgs(argc, argv);
#endif
    vector<string> args;
    for(int i=1; i<argc; i++) {
        string arg = argv[i];
        args.push_back(arg);
    }
    while(args.size()>0) {
        

        args.assign(args.begin()+1, args.end());
    }
    return args;
}

int main(int argc, char* argv[]) {
    if(argc<2) {
        assert(0&&"params number error");
    }    
    parseArgs(argc, argv);
    ObjectFile file(argv[1]);

    return 0;
}
  