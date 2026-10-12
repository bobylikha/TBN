#pragma once

#include "encoding.hpp"

#include <array>
#include <cstdint>

struct PackedTernary {
    std::uint8_t positive = 0;
    std::uint8_t negative = 0;
};

inline PackedTernary pack_ternary(
    const std::array<int, 8>& values
) {
    PackedTernary packed;

    for (std::size_t i = 0; i < 8; ++i) {
        TernaryBits bits = encode_ternary(values[i]);

        packed.positive |=
            static_cast<std::uint8_t>(bits.positive << i);

        packed.negative |=
            static_cast<std::uint8_t>(bits.negative << i);
    }

    return packed;
}

inline std::uint8_t pack_binary(
    const std::array<int, 8>& values
) {
    std::uint8_t packed = 0;

    for (std::size_t i = 0; i < 8; ++i) {
        std::uint8_t bit = encode_binary(values[i]);

        packed |= static_cast<std::uint8_t>(bit << i);
    }

    return packed;
}
