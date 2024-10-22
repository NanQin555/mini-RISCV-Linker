#pragma once
#include <cstdint>
#include <vector>
#include <sstream>
#include <string>
#include <array>
#include <algorithm>
#include "utils.hpp"
#define Arhdr_Name_Size 16
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

typedef struct Arhdr {
    uint8_t Name[16];
    uint8_t Date[12];
    uint8_t Uid[6];
    uint8_t Gid[6];
    uint8_t Mode[8];
    uint8_t Size[10];
    uint8_t Fmag[2];
} Arhdr;

const int EhdrSize = sizeof(Ehdr);
const int ShdrSize = sizeof(Shdr);
const int SymSize = sizeof(Sym);
const int ArdrSize = sizeof(Arhdr);

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

inline Arhdr cpyArhdr(const vector<uint8_t>& data) {
    Arhdr arhdr;
    memcpy(&arhdr.Name, data.data(), 16);
    memcpy(&arhdr.Date, data.data() + 16, 12);
    memcpy(&arhdr.Uid, data.data() + 28, 6);
    memcpy(&arhdr.Gid, data.data() + 34, 6);
    memcpy(&arhdr.Mode, data.data() + 40, 8);
    memcpy(&arhdr.Size, data.data() + 48, 10);
    memcpy(&arhdr.Fmag, data.data() + 58, 2);
    return arhdr;
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
template <>
inline Arhdr ReadHeader<Arhdr>(const vector<uint8_t>& data) {
    return cpyArhdr(data);
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

inline int GetArhdrSize(Arhdr* hdr) {
    string result;
    for (uint8_t value: hdr->Size) {
        if (value == 32)
            break;
        result += static_cast<char>(value);
    }
    stringstream ss(result);
    int size;
    ss >> size;
    if (ss.fail())
        throw runtime_error("Conversion failed");
    return size;
}

inline std::string TrimSpace(const std::string& str) {
    auto start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) return "";
    auto end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start, end - start + 1);
}

inline string ReadArhdrName(Arhdr* hdr, vector<uint8_t> strTab) {
    // long filename
    
    if (HasPrefix(hdr->Name, "/")) {
        string nameStr(reinterpret_cast<const char*>(hdr->Name + 1), 15);
        string trimmedStr = TrimSpace(nameStr);
        int start = stoi(trimmedStr);
        array<uint8_t, 2> target = { '/', '\n' };
        auto it = search(strTab.begin() + start, strTab.end(), 
                              begin(target), end(target));
        if (it == strTab.end()) {
            throw runtime_error("can't find '/\\n'");
        }
        size_t end = distance(strTab.begin(), it);
        return string(reinterpret_cast<const char*>(strTab.data() + start), end - start);
    }
    // short filename 
    array<uint8_t, 1> target = { '/' };
    auto it = search(hdr->Name, hdr->Name+16, 
                     begin(target), end(target));
    size_t end = distance(hdr->Name, it);
    assert(end!=16&&"can't find /\n");
    return string(reinterpret_cast<const char*>(hdr->Name), end);
}

inline bool IsStrtab(Arhdr* hdr) {
    return HasPrefix(hdr->Name, "//");
}

inline bool IsSymtab(Arhdr* hdr) {
    return HasPrefix(hdr->Name, "/ ") || HasPrefix(hdr->Name, "/SYM64/");
}
