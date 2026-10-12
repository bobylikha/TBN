#pragma once

#include<stdexcept>
#include<cstdint>

struct TernaryBits{
std::uint8_t positive;
std::uint8_t negative;
};

inline TernaryBits encode_ternary(int x){
    if(x == 1){
        return {1, 0};
    }
    if(x == 0){
        return {0, 0};
    }
    if(x == -1){
        return {0, 1};
    }

    throw std::invalid_argument(
        "Ternary value must be -1, 0 or 1"
    );
}

inline std::uint8_t encode_binary(int x){
    if(x == 1){
        return 0;
    }
    if(x == -1){
        return 1;
    }

    throw std::invalid_argument(
        "Ternary value must be -1 or 1"
    );
}
