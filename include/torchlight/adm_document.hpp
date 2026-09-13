#pragma once

#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace torchlight {

enum class AdmValueType : std::uint32_t {
    integer = 1,
    floating = 2,
    double_precision = 3,
    unsigned_integer = 4,
    string = 5,
    boolean = 6,
    integer64 = 7,
    translation = 8,
    note = 9,
};

using AdmValue = std::variant<std::int32_t, float, double, std::uint32_t, std::u16string, bool,
                              std::int64_t>;

struct AdmDictionaryEntry {
    std::uint32_t id = 0;
    std::u16string text;
};

struct AdmProperty {
    std::uint32_t name_id = 0;
    std::u16string name;
    AdmValueType type = AdmValueType::integer;
    AdmValue value = std::int32_t{0};
};

struct AdmGroup {
    std::uint32_t name_id = 0;
    std::u16string name;
    std::vector<AdmProperty> properties;
    std::vector<AdmGroup> groups;

    [[nodiscard]] const AdmProperty* find_property(const std::u16string& property_name) const noexcept;
};

struct AdmDocument {
    std::uint32_t version = 0;
    std::vector<AdmDictionaryEntry> dictionary;
    AdmGroup root;
};

// Parses Torchlight 1's compiled DAT/ADM representation. The parser owns all
// strings and values; the source byte vector may be released after this call.
[[nodiscard]] AdmDocument parse_adm(const std::vector<std::uint8_t>& bytes);

} // namespace torchlight
