#pragma once
#include "torchlight/unit_definition.hpp"
#include <cstdint>
#include <string>

namespace torchlight {
// original-code: CCharacter::unitInit @0x853800..0x853932. Empty/missing
// spawn class resolves through CLevel::rollTreasure, not a made-up drop rate.
struct TreasureProfile {
    std::u16string spawn_class;
    std::int32_t minimum_rolls = 1;
    std::int32_t maximum_rolls = 1;
};
[[nodiscard]] TreasureProfile load_treasure_profile(const UnitDefinition& definition);
} // namespace torchlight
