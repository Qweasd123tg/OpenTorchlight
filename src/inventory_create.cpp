#include "torchlight/inventory_create.hpp"

// Portable model of verified createMenus pure logic.
// Provenance per item: see include/torchlight/inventory_create.hpp and
// research/inventory-open.md ("createMenus: карта").

namespace torchlight {

std::string original_uint_to_string(unsigned value) {
    // Matches libstdc++ ostringstream decimal output for the C locale:
    // plain base-10 digits, no width/fill/separators (the original sets
    // none). Verified against GetValueAsString @0xc91f60, which only builds
    // the stream and inserts the value.
    if (value == 0)
        return "0";
    std::string out;
    while (value > 0) {
        out.push_back(static_cast<char>('0' + (value % 10)));
        value /= 10;
    }
    return std::string(out.rbegin(), out.rend());
}

std::string UniqueNameState::make(const std::string& prefix) {
    // original-code @0xc8ea50: pre-increment the static, then
    // prefix + '_' + decimal(counter).
    ++counter_;
    return prefix + "_" + original_uint_to_string(counter_);
}

} // namespace torchlight
