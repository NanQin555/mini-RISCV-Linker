#include "utils.hpp"


bool RemovePrefix(string &s, string prefix) {
    if(s.substr(0, prefix.size()) == prefix) {
        s.erase(0, prefix.size());
        return true;
    }
    return false;
}