#pragma once
#include <cstdint>
#include <vector>
using namespace std;
// ELF header
typedef struct Ehdr {
    uint8_t Ident[16];
    uint16_t Type;
    uint16_t Machine;
    uint32_t Version;
    uint64_t Entry;
    uint64_t PhOff;
    uint64_t ShOff;
    uint32_t Flags;
    uint16_t EhSize;
    uint16_t PhEntSize;
    uint16_t PhNum;
    uint16_t ShEntSize;
    uint16_t ShNum;
    uint16_t ShStrndx;
} Ehdr;

// Section header
typedef struct Shdr {
    uint32_t Name;
    uint32_t Type;
    uint64_t Flags;
    uint64_t Addr;
    uint64_t Offset;
    uint64_t Size;
    uint32_t Link;
    uint32_t Info;
    uint64_t AddrAlign;
    uint64_t EntSize;
} Shdr;

typedef struct Sym {
    uint32_t Name;
    uint8_t Info;
    uint8_t Other;
    uint16_t Shndx;
    uint64_t Val;
    uint64_t Size;
} Sym;

const int EhdrSize = sizeof(Ehdr);
const int ShdrSize = sizeof(Shdr);
const int SymSize = sizeof(Sym);

template <typename T>
T inline swapBytes(T value) {
    if constexpr (is_same_v<T, uint8_t>)
        return value;
    else if constexpr (is_same_v<T, uint16_t>)
        return (value >> 8) | (value << 8);
    else if constexpr (is_same_v<T, uint32_t>) {
        return ((value & 0x000000FF) << 24) |
               ((value & 0x0000FF00) << 8)  |
               ((value & 0x00FF0000) >> 8)  |
               ((value & 0xFF000000) >> 24);
    }
    else if constexpr (is_same_v<T, uint64_t>) {
        return ((value & 0x00000000FFFFFFFFULL) << 32) |
               ((value & 0xFFFFFFFF00000000ULL) >> 32);
    }
    else assert(0&&"unsupported type");
}



inline Ehdr cpyEhdr(const vector<uint8_t>& data) {
    Ehdr header;
    memcpy(header.Ident, data.data(), 16);
    memcpy(&header.Type, data.data() + 16, sizeof(uint16_t));
    memcpy(&header.Machine, data.data() + 18, sizeof(uint16_t));
    memcpy(&header.Version, data.data() + 20, sizeof(uint32_t));
    memcpy(&header.Entry, data.data() + 24, sizeof(uint64_t));
    memcpy(&header.PhOff, data.data() + 32, sizeof(uint64_t));
    memcpy(&header.ShOff, data.data() + 40, sizeof(uint64_t));
    memcpy(&header.Flags, data.data() + 48, sizeof(uint32_t));
    memcpy(&header.EhSize, data.data() + 52, sizeof(uint16_t));
    memcpy(&header.PhEntSize, data.data() + 54, sizeof(uint16_t));
    memcpy(&header.PhNum, data.data() + 56, sizeof(uint16_t));
    memcpy(&header.ShEntSize, data.data() + 58, sizeof(uint16_t));
    memcpy(&header.ShNum, data.data() + 60, sizeof(uint16_t));
    memcpy(&header.ShStrndx, data.data() + 62, sizeof(uint16_t));
    return header;
    // This machine is small endian already.

    // header.Type = swapBytes(header.Type);
    // header.Machine = swapBytes(header.Machine);
    // header.Version = swapBytes(header.Version);
    // header.Entry = swapBytes(header.Entry);
    // header.PhOff = swapBytes(header.PhOff);
    // header.ShOff = swapBytes(header.ShOff);
    // header.Flags = swapBytes(header.Flags);
    // header.EhSize = swapBytes(header.EhSize);
    // header.PhEntSize = swapBytes(header.PhEntSize);
    // header.PhNum = swapBytes(header.PhNum);
    // header.ShEntSize = swapBytes(header.ShEntSize);
    // header.ShNum = swapBytes(header.ShNum);
    // header.ShStrndx = swapBytes(header.ShStrndx);
}
inline Shdr cpyShdr(const vector<uint8_t>& data) {
    Shdr header;
    memcpy(&header.Name, data.data(), sizeof(uint32_t));
    memcpy(&header.Type, data.data() + 4, sizeof(uint32_t));
    memcpy(&header.Flags, data.data() + 8, sizeof(uint64_t));
    memcpy(&header.Addr, data.data() + 16, sizeof(uint64_t));
    memcpy(&header.Offset, data.data() + 24, sizeof(uint64_t));
    memcpy(&header.Size, data.data() + 32, sizeof(uint64_t));
    memcpy(&header.Link, data.data() + 40, sizeof(uint32_t));
    memcpy(&header.Info, data.data() + 44, sizeof(uint32_t));
    memcpy(&header.AddrAlign, data.data() + 48, sizeof(uint64_t));
    memcpy(&header.EntSize, data.data() + 56, sizeof(uint64_t));
    return header;
    // header.Name = swapBytes(header.Name);
    // header.Type = swapBytes(header.Type);
    // header.Flags = swapBytes(header.Flags);
    // header.Addr = swapBytes(header.Addr);
    // header.Offset = swapBytes(header.Offset);
    // header.Size = swapBytes(header.Size);
    // header.Link = swapBytes(header.Link);
    // header.Info = swapBytes(header.Info);
    // header.AddrAlign = swapBytes(header.AddrAlign);
    // header.EntSize = swapBytes(header.EntSize);
}
inline Sym cpySym(const vector<uint8_t>& data) {
    Sym sym;
    memcpy(&sym.Name, data.data(), sizeof(uint32_t));
    memcpy(&sym.Info, data.data() + 4, sizeof(uint8_t));
    memcpy(&sym.Other, data.data() + 5, sizeof(uint8_t));
    memcpy(&sym.Shndx, data.data() + 6, sizeof(uint16_t));
    memcpy(&sym.Val, data.data() + 8, sizeof(uint64_t));
    memcpy(&sym.Size, data.data() + 16, sizeof(uint64_t));
    return sym;
}
template <typename T>
inline T ReadHeader(const vector<uint8_t>& data);
template <>
inline Ehdr ReadHeader<Ehdr>(const vector<uint8_t>& data) {
    return cpyEhdr(data);
}
template <>
inline Shdr ReadHeader<Shdr>(const vector<uint8_t>& data) {
    return cpyShdr(data);
}
template <>
inline Sym ReadHeader<Sym>(const vector<uint8_t>& data) {
    return cpySym(data);
}
template <typename T>
inline T ReadHeader(const vector<uint8_t>& data) {
    T container;
    memcpy(&container, data.data(), sizeof(T));
    return container;
}

inline string ELFGetName(vector<uint8_t> strTab, uint32_t offset) {
    string result;
    for(size_t i=offset; i<strTab.size(); i++) {
        if(strTab[i] == 0)
            break;
        result += static_cast<char>(strTab[i]);
    }
    return result;
}