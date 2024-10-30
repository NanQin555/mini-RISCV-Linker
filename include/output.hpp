#pragma once

#include <vector>
#include <string>
#include "utils.hpp"
#include "ELFheadr.hpp"
using namespace std;

vector<string> prefixs = {
    ".text.",
    ".data.rel.ro.",
    ".data.",
    ".rodata.",
    ".bss.rel.ro.",
    ".bss.",
    ".init_array.",
    ".fini_array.",
    ".tbss.",
    ".tdata.",
    ".ctors.",
    ".dtors.",
    ".jcr.",
    ".eh_frame.",
    ".gcc_except_table.",
    ".ctors",
    ".dtors",
    ".jcr",
    ".eh_frame",
    ".gcc_except_table"
};

string GetOutputName(string name, uint64_t flags) {
    if((name == ".rodata" || HasPrefix(name, ".rodata")) 
        && (flags & SHF_MERGE != 0)) {
        if (flags & SHF_STRINGS != 0) {
            return ".rodata.str";
        }
        else return ".rodata.cst";
    }
    for(auto prefix: prefixs) {
        string stem = prefix.assign(prefix.begin(), prefix.end()-1);
        if(name == stem || HasPrefix(name, prefix)) {
            return stem;
        }
    }
    return name;
}