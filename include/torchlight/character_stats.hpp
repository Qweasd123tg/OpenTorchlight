#pragma once
#include <cstdint>

namespace torchlight {
struct AttackEffects;

// original-code: CCharacter::walkingSpeed/runningSpeed @0x815a20/0x815ad0.
// These functions consume evaluated effects, not raw affix percentages/graphs.
[[nodiscard]] float evaluated_movement_speed(float base, float percent, float slow_resistance);
[[nodiscard]] float evaluated_movement_speed(float base, const AttackEffects& effects);

// original-code: CCharacter::defense @0x814530. Query 7 (unfiltered) and
// query 6 (ALL channel) are deliberately separate, as in the original calls.
[[nodiscard]] std::int32_t evaluated_defense_attribute(std::int32_t base,
    float percent, float all_percent, float flat);
[[nodiscard]] std::int32_t evaluated_defense_attribute(std::int32_t base,
    const AttackEffects& effects);

// original-code: armorBonus @0x8145c0 -> AC @0x814670. base_armor includes
// natural/equipped armor only, NOT the flat ARMOR BONUS effect. Owner percent
// is an optional already-evaluated pet-master effect, not pet AI support.
[[nodiscard]] std::int32_t evaluated_physical_armor(std::int32_t base_armor,
    std::int32_t defense, float armor_percent, float flat_armor,
    float degrade_armor, float owner_armor_percent = 0.0F);
[[nodiscard]] std::int32_t evaluated_character_armor(std::int32_t base_armor,
    std::int32_t base_defense, const AttackEffects& effects);
} // namespace torchlight
