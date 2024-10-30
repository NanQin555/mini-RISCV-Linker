#pragma once
#include <map>
#include "chunk.hpp"
#include "sectionFragment.hpp"
class Context;
using namespace std;

class MergedSection: public Chunk {
public:
    map<string, SectionFragment*> Map;
    
    MergedSection(string, uint64_t, uint32_t);
    SectionFragment* Insert(string, uint32_t);
};
MergedSection* GetMergedSectionInstance(Context*, string, uint32_t, uint64_t);

