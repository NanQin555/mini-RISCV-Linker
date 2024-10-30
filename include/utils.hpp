#pragma once 
#include <string>
#include <vector>
#include <functional>

using namespace std;
template <typename T>
bool HasPrefix(T contents[], string prefix) {
    string temp;
    for(size_t i=0; i<prefix.size(); i++) {
        temp += contents[i];
    }
    if (temp == prefix) {
        return true;
    }
    return false;
}
template <typename T>
bool HasPrefix(vector<T> contents, string prefix) {
    string temp;
    for(size_t i=0; i<prefix.size(); i++) {
        temp += contents[i];
    }
    if (temp == prefix) {
        return true;
    }
    return false;
}
inline bool HasPrefix(string contents, string prefix) {
    if(contents.substr(0, prefix.size()) == prefix)
        return true;
    return false;
}

bool RemovePrefix(string &s, string prefix);

template <typename T>
vector<T> RemoveIf(vector<T> elems, function<bool(T)> condition) {
    int i = 0;
    for(auto elem: elems) {
        if(condition(elem)) 
            continue;

        elems[i] = elem;            
        i++;
    }
    elems.resize(i);
    return elems;
}

template <typename T>
vector<T> ReadSlice(vector<uint8_t> &data, int size);