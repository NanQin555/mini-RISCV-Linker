#pragma once 
#include <string>
#include "ELFheadr.hpp"
using namespace std;
class Chunk {
public:
    string name;
    Shdr shdr;
    Chunk();
};