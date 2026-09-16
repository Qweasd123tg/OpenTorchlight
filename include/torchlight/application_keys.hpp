#pragma once
#include <cstdint>
namespace torchlight::physical_key {
// Explicit portable physical-key wire values, matching the existing Linux
// adapter. These are not an original Torchlight key table or an IME.
inline constexpr std::uint32_t DIGIT_0 = 11;
inline constexpr std::uint32_t DIGIT_1 = 2;
inline constexpr std::uint32_t DIGIT_2 = 3;
inline constexpr std::uint32_t DIGIT_3 = 4;
inline constexpr std::uint32_t DIGIT_4 = 5;
inline constexpr std::uint32_t DIGIT_5 = 6;
inline constexpr std::uint32_t DIGIT_6 = 7;
inline constexpr std::uint32_t DIGIT_7 = 8;
inline constexpr std::uint32_t DIGIT_8 = 9;
inline constexpr std::uint32_t DIGIT_9 = 10;
inline constexpr std::uint32_t A = 30;
inline constexpr std::uint32_t B = 48;
inline constexpr std::uint32_t BACKSPACE = 14;
inline constexpr std::uint32_t C = 46;
inline constexpr std::uint32_t D = 32;
inline constexpr std::uint32_t DOWN = 108;
inline constexpr std::uint32_t E = 18;
inline constexpr std::uint32_t ENTER = 28;
inline constexpr std::uint32_t ESC = 1;
inline constexpr std::uint32_t F = 33;
inline constexpr std::uint32_t G = 34;
inline constexpr std::uint32_t H = 35;
inline constexpr std::uint32_t I = 23;
inline constexpr std::uint32_t J = 36;
inline constexpr std::uint32_t K = 37;
inline constexpr std::uint32_t KPENTER = 96;
inline constexpr std::uint32_t L = 38;
inline constexpr std::uint32_t M = 50;
inline constexpr std::uint32_t MINUS = 12;
inline constexpr std::uint32_t N = 49;
inline constexpr std::uint32_t O = 24;
inline constexpr std::uint32_t P = 25;
inline constexpr std::uint32_t Q = 16;
inline constexpr std::uint32_t R = 19;
inline constexpr std::uint32_t S = 31;
inline constexpr std::uint32_t SPACE = 57;
inline constexpr std::uint32_t T = 20;
inline constexpr std::uint32_t TAB = 15;
inline constexpr std::uint32_t U = 22;
inline constexpr std::uint32_t UP = 103;
inline constexpr std::uint32_t V = 47;
inline constexpr std::uint32_t W = 17;
inline constexpr std::uint32_t X = 45;
inline constexpr std::uint32_t Y = 21;
inline constexpr std::uint32_t Z = 44;
}
