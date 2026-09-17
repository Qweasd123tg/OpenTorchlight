#pragma once

#include "torchlight/adm_document.hpp"
#include "torchlight/attack_action.hpp"
#include "torchlight/pak_archive.hpp"

#include <cstdint>
#include <optional>

namespace torchlight {

// resource-derived values from media/globals.dat.adm. Unknown is not zero.
struct VitalRecoveryRules {
    std::optional<float> health_percent_per_second;
    std::optional<float> pet_health_percent_per_second;
    std::optional<float> mana_percent_per_second;
};
[[nodiscard]] VitalRecoveryRules parse_vital_recovery_rules(const AdmDocument&);
[[nodiscard]] VitalRecoveryRules load_vital_recovery_rules(const PakArchive&);
void validate_vital_recovery_rules(const VitalRecoveryRules&);

// original-code, ordinary unowned CCharacter::maxHP @0x813e60.
// HP uses integer growth and divides the percent BEFORE multiplying the base.
[[nodiscard]] std::int32_t evaluated_maximum_health(std::int32_t base,
    std::int32_t growth, const AttackEffects& effects);
[[nodiscard]] float evaluated_health_rate(const AttackEffects&) noexcept;
[[nodiscard]] float evaluated_mana_rate(const AttackEffects&) noexcept;

// Normal modifyHP/modifyMana arithmetic: two sources, two clamps. The caller
// supplies state/lifecycle gating. Returns nullopt on invalid/nonfinite input,
// leaving caller state unchanged. No duration normalization is inferred.
[[nodiscard]] std::optional<float> advance_vital(float current, float maximum,
    std::optional<float> percent_per_second, float flat_per_second, float seconds) noexcept;
// CCharacter::modifyHP rejects partial positive healing after HP reaches zero,
// including between the two recovery sources within one update.
[[nodiscard]] std::optional<float> advance_health(float current, float maximum,
    std::optional<float> percent_per_second, float flat_per_second, float seconds) noexcept;

} // namespace torchlight
