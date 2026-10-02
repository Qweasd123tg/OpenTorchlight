#include "torchlight/consumable.hpp"
#include "torchlight/recovered/gameplay_numeric.hpp"
#include "torchlight/original_combat_inputs.hpp"
#include "torchlight/progression.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace torchlight {
namespace {
std::u16string upper(std::u16string s) {
    for (auto& c : s) if (c >= u'a' && c <= u'z') c -= u'a' - u'A';
    return s;
}
std::u16string text(const AdmGroup& g, const char16_t* key, std::u16string fallback = {}) {
    const auto* p = g.find_property(key);
    if (!p) return fallback;
    if (const auto* s = std::get_if<std::u16string>(&p->value)) return *s;
    throw std::invalid_argument("consumable text field has wrong type");
}
std::string ascii(const std::u16string& s) {
    std::string r;
    for (auto c : s) {
        if (c > 127) throw std::invalid_argument("non-ASCII consumable numeric/graph field");
        r.push_back(static_cast<char>(c));
    }
    return r;
}
bool flag(const AdmGroup& g, const char16_t* key, bool fallback = false) {
    const auto* p = g.find_property(key);
    if (!p) return fallback;
    if (const auto* v = std::get_if<bool>(&p->value)) return *v;
    throw std::invalid_argument("consumable flag is not boolean");
}
float number(const AdmGroup& g, const char16_t* key, float fallback) {
    const auto* p = g.find_property(key);
    if (!p) return fallback;
    const auto value = std::visit([](const auto& v) -> float {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, std::u16string>) {
            const auto s = ascii(v);
            std::size_t n = 0;
            const auto x = std::stof(s, &n);
            if (n != s.size()) throw std::invalid_argument("trailing consumable numeric text");
            return x;
        } else if constexpr (std::is_same_v<T, bool>) {
            throw std::invalid_argument("boolean consumable number");
        } else return static_cast<float>(v);
    }, p->value);
    if (!std::isfinite(value)) throw std::invalid_argument("nonfinite consumable number");
    return value;
}
std::int32_t integer(const AdmGroup& g, const char16_t* key, std::int32_t fallback) {
    const auto n = number(g, key, static_cast<float>(fallback));
    if (n != std::trunc(n) || n < -100000 || n > 100000)
        throw std::invalid_argument("invalid consumable integer");
    return static_cast<std::int32_t>(n);
}
void validate_effect(const RecoveryEffect& e) {
    if (e.name.empty() || e.name.size() > 256 || e.name.find(char16_t{}) != std::u16string::npos ||
        (!is_health_recovery(e.type) && !is_mana_recovery(e.type)) ||
        !std::isfinite(e.duration) || e.duration <= 0 || e.duration > 86400 ||
        !std::isfinite(e.value) || e.value <= 0 || e.value > 1e9F)
        throw std::invalid_argument("invalid finite recovery effect");
}
}
bool is_health_recovery(std::uint16_t type) noexcept { return type == 7 || type == 124; }
bool is_mana_recovery(std::uint16_t type) noexcept { return type == 6 || type == 123; }
float finite_recovery_rate(float value) noexcept { return recovered::finite_recovery_rate(value); }
void validate_consumable(const ConsumableItem& c) {
    if (c.count == 0 || c.maximum_stack == 0 || c.maximum_stack > 100000 || c.count > c.maximum_stack ||
        (c.uses <= 0 && c.uses != -9999) || c.uses > 100000 || c.level_required < 0 ||
        c.level_required > 100000 || c.effects.size() > 64 || c.unavailable_reason.size() > 4096 ||
        (c.unavailable_reason.empty() && c.effects.empty()))
        throw std::invalid_argument("invalid consumable instance");
    for (const auto& e : c.effects) validate_effect(e);
}
void validate_active_recovery(const std::vector<ActiveRecovery>& active) {
    if (active.size() > 256) throw std::invalid_argument("too many active recovery effects");
    for (const auto& a : active) {
        validate_effect(a.effect);
        if (!std::isfinite(a.remaining) || a.remaining <= 0 || a.remaining > a.effect.duration)
            throw std::invalid_argument("invalid remaining recovery time");
    }
}
bool same_consumable(const ConsumableItem& a, const ConsumableItem& b) noexcept {
    if (a.maximum_stack != b.maximum_stack || a.uses != b.uses || a.level_required != b.level_required ||
        a.dont_use_on_full != b.dont_use_on_full || a.unavailable_reason != b.unavailable_reason ||
        a.effects.size() != b.effects.size()) return false;
    for (std::size_t i = 0; i < a.effects.size(); ++i) {
        const auto& x = a.effects[i]; const auto& y = b.effects[i];
        if (x.name != y.name || x.type != y.type || x.duration != y.duration || x.value != y.value)
            return false;
    }
    return true;
}
std::optional<ConsumableItem> load_consumable(const PakArchive& archive,
    const UnitDefinition& d, const AttackEffectCatalog* catalog) {
    if (!d.find_property(u"USES")) return std::nullopt;
    ConsumableItem c;
    try {
        c.uses = integer(d.root, u"USES", 0);
        if (c.uses == 0) return std::nullopt;
        const auto maximum = integer(d.root, u"MAXSTACKSIZE", 1);
        if (maximum <= 0) throw std::invalid_argument("invalid stack capacity");
        c.maximum_stack = static_cast<std::uint32_t>(maximum);
        c.dont_use_on_full = flag(d.root, u"DONT_USE_ON_FULL");
        c.level_required = integer(d.root, u"LEVEL_REQUIRED", 0);
        if (!catalog) throw std::invalid_argument("original effect catalog unavailable");
        const auto effect_defs = parse_adm(archive.read_normalized(original_combat_inputs::effect_catalog_compiled_path));
        for (const auto& g : d.root.groups) {
            if (upper(g.name) == u"SKILL") throw std::invalid_argument("item skill is not implemented");
            if (upper(g.name) != u"EFFECT") continue;
            RecoveryEffect e;
            e.name = upper(text(g, u"NAME"));
            const auto type = catalog->find(text(g, u"TYPE"));
            if (!type || (!is_health_recovery(*type) && !is_mana_recovery(*type)))
                throw std::invalid_argument("item effect is not finite recovery");
            e.type = *type;
            if (upper(text(g, u"ACTIVATION", u"DYNAMIC")) != u"DYNAMIC")
                throw std::invalid_argument("item activation is not DYNAMIC");
            // Fail closed for conditions/stat scaling, pet transforms, exclusivity,
            // linked expirations and random rolls. Do not consume only half a skill.
            for (const auto& p : g.properties) {
                const auto k = upper(p.name);
                if (k == u"NAME" || k == u"TYPE" || k == u"ACTIVATION" || k == u"DURATION" ||
                    k == u"MIN" || k == u"MAX" || k == u"LEVEL" || k == u"NOGRAPH" ||
                    k == u"GRAPHOVERRIDE" || k == u"PARTICLE_FX" || k == u"SAVE") continue;
                if ((k == u"EXCLUSIVE" || k == u"USEOWNERLEVEL") && !flag(g, p.name.c_str())) continue;
                throw std::invalid_argument("item effect has unsupported qualifiers");
            }
            if (!g.groups.empty()) throw std::invalid_argument("conditional item effect is unsupported");
            e.duration = number(g, u"DURATION", 0);
            e.value = number(g, u"MIN", 0);
            auto maximum_value = number(g, u"MAX", e.value);
            if (maximum_value == 0) maximum_value = e.value;
            if (maximum_value != e.value) throw std::invalid_argument("random item recovery is unsupported");
            if (!flag(g, u"NOGRAPH")) {
                const auto& graph_def = effect_defs.root.groups.at(*type);
                const auto graph1 = text(g, u"GRAPHOVERRIDE", text(graph_def, u"GRAPH1"));
                const auto graph2 = text(g, u"GRAPHOVERRIDE", text(graph_def, u"GRAPH2"));
                if (upper(graph1) != upper(graph2)) throw std::invalid_argument("different MIN/MAX recovery graphs");
                if (!graph1.empty()) {
                    const auto graph = find_named_stat_graph(archive, ascii(graph1));
                    if (!graph) throw std::invalid_argument("recovery graph missing");
                    auto level = integer(g, u"LEVEL", 0); // CEffect constructor, NOT item LEVEL.
                    if (level < 0 || level > 1000) level = 0;
                    e.value = (e.value / 100.0F) * graph->value(static_cast<float>(level));
                }
            }
            validate_effect(e);
            c.effects.push_back(std::move(e));
        }
        validate_consumable(c);
    } catch (const std::exception& e) {
        // Retain unsupported items as owned data, never drink a partial definition.
        c = ConsumableItem{};
        c.unavailable_reason = e.what();
    }
    return c;
}
const char* consumable_use_message(ConsumableUse use) noexcept {
    switch (use) {
    case ConsumableUse::used: return "POTION USED. RECOVERY RUNS IN GAME TIME.";
    case ConsumableUse::not_found: return "NO MATCHING POTION IN BAG.";
    case ConsumableUse::unsupported: return "THIS ITEM'S EFFECT IS NOT IMPLEMENTED. ITEM KEPT.";
    case ConsumableUse::dead: return "PLAYER IS DEAD. ITEM KEPT.";
    case ConsumableUse::level_required: return "PLAYER LEVEL TOO LOW. ITEM KEPT.";
    case ConsumableUse::full_or_active: return "RESOURCE FULL OR SAME RECOVERY ALREADY ACTIVE. ITEM KEPT.";
    case ConsumableUse::exhausted: return "ITEM HAS NO USES LEFT.";
    }
    return "UNKNOWN ITEM RESULT.";
}
} // namespace torchlight
