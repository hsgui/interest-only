#pragma once

#include <iostream>

using namespace std;

namespace algorithms {

    // http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
    // also known as SWAR (SIMD Within A Register) algorithm
    // http://www.playingwithpointers.com/swar.html
    // http://stackoverflow.com/questions/22081738/how-variable-precision-swar-algorithm-works
    inline unsigned int CountSetBits(unsigned int value)
    {
        value -= (value >> 1) & 0x55555555;
        value = (value & 0x33333333) + ((value >> 2) & 0x33333333);
        return ((value + (value >> 4) & 0x0F0F0F0F) * 0x01010101) >> 24;
    }

    class HAMT
    {
    };
}