#include "utils.hpp"
#include "ELFheadr.hpp"

bool RemovePrefix(string &s, string prefix) {
    if(s.substr(0, prefix.size()) == prefix) {
        s.erase(0, prefix.size());
        return true;
    }
    return false;
}

template <typename T>
vector<T> ReadSlice(vector<uint8_t> &data, int size) {
    size_t nums = data.size() / size;
    vector<T> res;
    res.reserve(nums);
    while(nums) {
        res.push_back(ReadHeader<T>(data));
        data.assign(data.begin()+size, data.end());
        nums--;
    }
    return res;
}

template std::vector<Sym> ReadSlice<Sym>(std::vector<uint8_t>& data, int size);
template std::vector<unsigned int> ReadSlice<unsigned int>(std::vector<uint8_t>& data, int size);
