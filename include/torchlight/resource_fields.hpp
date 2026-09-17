#pragma once
// Portable typed reads of already decoded ADM. No gameplay defaults are chosen
// here: every caller must supply a source-backed default or require a field.
#include "torchlight/adm_document.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
namespace torchlight::resource_fields {
inline std::u16string upper(std::u16string s) {
    for (auto& c : s) if (c >= u'a' && c <= u'z') c -= u'a' - u'A';
    return s;
}
inline std::string ascii(const std::u16string& s) {
    std::string r; r.reserve(s.size());
    for (const auto c : s) { if (c > 127) throw std::invalid_argument("non-ASCII resource identifier"); r.push_back(static_cast<char>(c)); }
    return r;
}
inline const AdmProperty* field(const AdmGroup& g, const std::u16string& key) {
    const auto name = upper(key);
    for (const auto& p : g.properties) if (upper(p.name) == name) return &p;
    return nullptr;
}
inline std::u16string text(const AdmGroup& g, const std::u16string& key, std::u16string fallback = {}) {
    const auto* p = field(g, key); if (!p) return fallback;
    if (const auto* s = std::get_if<std::u16string>(&p->value)) return *s;
    throw std::invalid_argument("resource text field has wrong type: " + ascii(key));
}
inline bool flag(const AdmGroup& g, const std::u16string& key, bool fallback = false) {
    const auto* p = field(g,key); if (!p) return fallback;
    if (const auto* v = std::get_if<bool>(&p->value)) return *v;
    throw std::invalid_argument("resource boolean field has wrong type: " + ascii(key));
}
inline double number(const AdmGroup& g, const std::u16string& key, double fallback) {
    const auto* p = field(g,key); if (!p) return fallback;
    const auto result = std::visit([](const auto& v) -> double {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T,std::u16string>) {
            const auto s = ascii(v); std::size_t consumed = 0;
            const auto x = std::stod(s,&consumed);
            if (consumed != s.size()) throw std::invalid_argument("trailing resource number text");
            return x;
        } else if constexpr (std::is_same_v<T,bool>) throw std::invalid_argument("boolean is not a resource number");
        else return static_cast<double>(v);
    },p->value);
    if (!std::isfinite(result)) throw std::invalid_argument("non-finite resource number");
    return result;
}
inline std::int32_t integer(const AdmGroup& g, const std::u16string& key, std::int32_t fallback) {
    const auto n = number(g,key,fallback);
    if (n != std::trunc(n) || n < std::numeric_limits<std::int32_t>::min() || n > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("resource integer out of range: " + ascii(key));
    return static_cast<std::int32_t>(n);
}
inline std::int64_t guid(const AdmGroup& g, const std::u16string& key) {
    const auto* p = field(g,key); if (!p) throw std::invalid_argument("missing resource GUID");
    if (const auto* v = std::get_if<std::int64_t>(&p->value)) return *v;
    if (const auto* v = std::get_if<std::int32_t>(&p->value)) return *v;
    throw std::invalid_argument("GUID must retain its integer representation");
}
inline const AdmGroup* child(const AdmGroup& g, const std::u16string& name) {
    const auto n = upper(name); for (const auto& c : g.groups) if (upper(c.name) == n) return &c;
    return nullptr;
}
} // namespace torchlight::resource_fields
