#pragma once
#include <cmath>
#include <iomanip>
#include <ostream>
#include <stdexcept>
#include <string_view>
namespace torchlight::diagnostic {
// Stable JSON for verification dumps. Addresses and GPU handles are deliberately
// excluded by callers. max_digits10 elsewhere preserves float32 round trips.
inline void string(std::ostream& out, std::string_view value) {
    constexpr char hex[] = "0123456789abcdef";
    out << '"';
    for (const unsigned char c : value) {
        if (c == '"' || c == '\\') out << '\\' << static_cast<char>(c);
        else if (c < 32) out << "\\u00" << hex[c >> 4] << hex[c & 15];
        else out << static_cast<char>(c);
    }
    out << '"';
}
inline void number(std::ostream& out, float value) {
    if (!std::isfinite(value)) throw std::runtime_error("non-finite diagnostic value");
    out << std::setprecision(9) << value;
}
template<class T> inline void array(std::ostream& out, const T& values) {
    out << '['; bool comma = false;
    for (const auto value : values) { if (comma) out << ','; comma = true; number(out, value); }
    out << ']';
}
} // namespace torchlight::diagnostic
