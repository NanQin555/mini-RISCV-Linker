#pragma once
#include <string>
#include <vector>
#include "machinetype.hpp"
#include "ObjectFile.hpp"
using namespace std;

typedef struct ContextArgs {
    string Output;
    MachineType Emulation;
    vector<string> LibraryPaths; 
}ContextArgs;

class Context {
public:
    ContextArgs Args;
    vector<ObjectFile*> Objs; 

    Context(): Args(ContextArgs{(string("a.out")),
                    MachineType::None}) {};
};