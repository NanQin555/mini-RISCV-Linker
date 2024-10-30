#include "mergedsection.hpp"
// #include "sectionFragment.hpp"

SectionFragment::SectionFragment(MergedSection* m)
: outputSection(m), offset(UINT32_MAX) {
}

