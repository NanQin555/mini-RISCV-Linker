#include "mergedsection.hpp"
#include "context.hpp"
#include "output.hpp"
#include "ELFheadr.hpp"
MergedSection::MergedSection(string _name, uint64_t flags, uint32_t type)
: Chunk() {
    name = _name;
    shdr.Flags = flags;
    shdr.Type = type;
}

SectionFragment* MergedSection::Insert(string key, uint32_t p2align) {
    if(Map.find(key) == Map.end()) {
        Map[key] = new SectionFragment(this);
    }
    SectionFragment* frag = Map[key];
    if(frag->P2Align < p2align) {
        frag->P2Align = p2align;
    }
    return frag;
}

MergedSection* GetMergedSectionInstance(Context* ctx, string name, uint32_t type, uint64_t flags) {
    name = GetOutputName(name, flags);
    flags = flags ^ (uint64_t)SHF_GROUP ^ (uint64_t)SHF_MERGE ^ 
            (uint64_t)SHF_STRINGS ^ (uint64_t)SHF_COMPRESSED;
    
    auto find = [&]() -> MergedSection* {
        for(auto osec: ctx->MergedSections) {
            if( name == osec->name && 
                flags == osec->shdr.Flags &&
                type == osec->shdr.Type) {
                    return osec;
                }
        }
        return nullptr;
    };
    
    MergedSection* osec = find();
    if (osec != nullptr) {
        return osec;
    }
    osec = new MergedSection(name, flags, type);
    ctx->MergedSections.push_back(osec);
    return osec;
}