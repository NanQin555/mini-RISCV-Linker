#pragma once
#include <cstdint>
using namespace std;
class MergedSection;
class SectionFragment {
public:
    MergedSection* outputSection;
    uint32_t offset;
    uint32_t P2Align;
    bool isAlive;

    SectionFragment(MergedSection*);
};

