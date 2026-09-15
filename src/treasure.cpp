#include "torchlight/treasure.hpp"
#include <stdexcept>

namespace torchlight {
TreasureProfile load_treasure_profile(const UnitDefinition& definition) {
    TreasureProfile result;
    // CDataGroup::GetDataGroupByName @0xc61d30 returns the FIRST match.
    for (const auto& group : definition.root.groups) {
        if (group.name != u"TREASURE") continue;
        if (const auto* property = group.find_property(u"SPAWNCLASS")) {
            if (property->type != AdmValueType::string &&
                property->type != AdmValueType::translation &&
                property->type != AdmValueType::note) {
                throw std::runtime_error("TREASURE/SPAWNCLASS must be text");
            }
            result.spawn_class = std::get<std::u16string>(property->value);
        }
        const auto integer = [&](const char16_t* name) {
            const auto* property = group.find_property(name);
            if (!property) return std::int32_t{1};
            if (property->type != AdmValueType::integer)
                throw std::runtime_error("TREASURE count must be an integer");
            return std::get<std::int32_t>(property->value);
        };
        result.minimum_rolls = integer(u"MIN");
        result.maximum_rolls = integer(u"MAX");
        // Portable validation, not a recovered game clamp. Match the existing
        // spawn expansion safety budget; never silently truncate a table.
        if (result.minimum_rolls < 0 || result.maximum_rolls < 0 ||
            result.minimum_rolls > 4096 || result.maximum_rolls > 4096)
            throw std::runtime_error("TREASURE count exceeds the portable safety budget");
        break;
    }
    return result;
}
} // namespace torchlight
