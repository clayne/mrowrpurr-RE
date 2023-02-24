#pragma once

#include <cstdint>

namespace Fallout1::RE::Addresses {

    // TODO make these each {<address>, <offset>, ...} pairs.
    uintptr_t PlayerPtr  = 0x105734;
    uintptr_t PlayerName = 0x16BF1C;
    uintptr_t PlayerAge  = 0x1076C8;
}