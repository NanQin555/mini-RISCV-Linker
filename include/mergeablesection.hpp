#pragma once 
#include <vector>
#include <string>

#include "mergedsection.hpp"
class MergeableSection {
public:
    MergedSection* parent;
    uint8_t P2Align;
    vector<string> Strs;
    vector<uint32_t> FragOffsets;
    vector<SectionFragment*> Fragments;
    pair<SectionFragment*, uint32_t>  GetFragment(uint32_t);
};