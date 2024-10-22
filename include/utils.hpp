#pragma once 
#include <string>
#include <vector>
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
bool RemovePrefix(string &s, string prefix);

