#pragma once
#include <string>
#include <vector>
#include <map>
#include "machinetype.hpp"
#include "ObjectFile.hpp"
#include "symbol.hpp"
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
    map<string, Symbol*> SymbolMap;

    Context(): Args(ContextArgs{(string("a.out")),
                    MachineType::None}) {                
    }
};