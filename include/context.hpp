#include <string>
#include <vector>
#include "machinetype.hpp"
using namespace std;

typedef struct ContextArgs {
    string Output;
    MachineType Emulation;
    vector<string> LibraryPaths;
}ContextArgs;

class Context {
public:
    ContextArgs Args;

    Context(): Args(ContextArgs{(string("a.out")),
                    MachineType::None}) {};
};