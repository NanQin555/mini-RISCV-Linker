#include "mergeablesection.hpp"
#include <functional>
using namespace std;
pair<SectionFragment*, uint32_t>  MergeableSection::GetFragment(uint32_t offset) {
    auto it = std::lower_bound(FragOffsets.begin(), FragOffsets.end(), offset, [](uint32_t off, uint32_t fragOffset) {
        return off < fragOffset;
    });
    size_t pos = it - FragOffsets.begin();
    if (pos == 0) {
        return {nullptr, 0};
    }
    return {Fragments[pos - 1], offset - FragOffsets[pos - 1]};
}