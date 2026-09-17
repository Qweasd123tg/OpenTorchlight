#pragma once
#include "torchlight/stat_graph.hpp"
#include "torchlight/unit_definition.hpp"
#include <array>
#include <optional>
namespace torchlight {
enum class PriceQuality : std::uint8_t { normal, magic, unique };
struct EquipmentPrices {
    std::int32_t buy = 1, sell = 1, unidentified_buy = 1, unidentified_sell = 1;
};
// original-code scalar kernels. Invalid/overflowing values are rejected rather
// than emulating signed integer wraparound in the original machine code.
[[nodiscard]] std::int32_t equipment_base_price(float graph_value, std::int32_t value);
[[nodiscard]] std::int32_t equipment_buy_price(const EquipmentPrices&, std::int32_t count,
                                               bool identified, float barter_percent);
[[nodiscard]] std::int32_t equipment_sell_price(const EquipmentPrices&, std::int32_t count,
                                                bool identified, float barter_percent);
void validate_equipment_prices(const EquipmentPrices&);
class EquipmentPriceCatalog {
public:
    explicit EquipmentPriceCatalog(const PakArchive&);
    [[nodiscard]] EquipmentPrices evaluate(std::int32_t level, std::int32_t value,
                                           PriceQuality, bool gambler = false) const;
private:
    std::array<StatGraph, 7> graphs_;
};
} // namespace torchlight
