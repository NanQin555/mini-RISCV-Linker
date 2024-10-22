#pragma once
#include <cstdint>
#include "MagicEnum.hpp"
#include "filetype.hpp"
enum MachineType {
    None,
    RISCV64
};
MachineType GetMachineTypeFromContents(vector<uint8_t>);
