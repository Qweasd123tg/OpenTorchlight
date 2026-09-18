#include "torchlight/damage.hpp"
#include "torchlight/typed_damage.hpp"
namespace torchlight {
std::int32_t DamageDefense::effective(DamageType type) const noexcept {
    const auto index = static_cast<std::size_t>(type);
    if (index >= elemental_armor.size()) return 0;
    try { return evaluate_damage_defense(*this, {}).maximum[index]; }
    catch (...) { return 0; } // Compatibility API: invalid out-of-domain raw data.
}
DamageMitigation mitigate_damage(std::int32_t damage, std::int32_t maximum_damage,
    DamageType type, float multiplier, const DamageDefense& defense, TorchlightRandom& random) noexcept {
    try { return mitigate_evaluated_damage(damage, maximum_damage, type, multiplier,
        evaluate_damage_defense(defense, {}), random); }
    catch (...) { return {}; }
}
} // namespace torchlight
