#pragma once
#include "torchlight/attack_action.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace torchlight {
// Narrow supported EFFECT domain: positive, constant, finite DYNAMIC recovery.
// These are evaluated values, not pointers into the pak or the original ABI.
struct RecoveryEffect {
    std::u16string name;
    std::uint16_t type = 124;
    float duration = 0;
    float value = 0; // after original graph evaluation, before finite-effect scale
};
struct ConsumableItem {
    std::uint32_t count = 1, maximum_stack = 1;
    std::int32_t uses = 1, level_required = 0;
    bool dont_use_on_full = false;
    std::vector<RecoveryEffect> effects;
    std::string unavailable_reason;
};
struct ActiveRecovery {
    RecoveryEffect effect;
    float remaining = 0;
    std::int64_t source_guid = 0;
};
enum class ConsumableUse { used, not_found, unsupported, dead, level_required, full_or_active, exhausted };
[[nodiscard]] const char* consumable_use_message(ConsumableUse) noexcept;
[[nodiscard]] bool is_health_recovery(std::uint16_t type) noexcept;
[[nodiscard]] bool is_mana_recovery(std::uint16_t type) noexcept;
// Original scalar at ELF 0xfa86dc, applied to finite effects of type 6/7/123/124.
[[nodiscard]] float finite_recovery_rate(float value) noexcept;
void validate_consumable(const ConsumableItem&);
void validate_active_recovery(const std::vector<ActiveRecovery>&);
[[nodiscard]] bool same_consumable(const ConsumableItem&, const ConsumableItem&) noexcept;
[[nodiscard]] std::optional<ConsumableItem> load_consumable(
    const PakArchive&, const UnitDefinition&, const AttackEffectCatalog*);
} // namespace torchlight
