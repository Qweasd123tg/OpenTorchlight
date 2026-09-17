#include "torchlight/economy.hpp"
#include "torchlight/progression.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
namespace torchlight {
namespace {
std::int32_t checked(std::int64_t value) {
    if (value < 0 || value > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("equipment price outside supported nonnegative int32 domain");
    return static_cast<std::int32_t>(value);
}
std::int32_t truncated(float value) {
    if (!std::isfinite(value) || static_cast<double>(value) < std::numeric_limits<std::int32_t>::min() ||
        static_cast<double>(value) > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("barter contribution overflows int32");
    return static_cast<std::int32_t>(value);
}
StatGraph required(const PakArchive& pak, const char* name) {
    auto graph = find_named_stat_graph(pak,name);
    if (!graph) throw std::invalid_argument(std::string("missing price graph: ") + name);
    return std::move(*graph);
}
}
std::int32_t equipment_base_price(float graph, std::int32_t value) {
    if (!std::isfinite(graph) || graph < 0 || value < 0) throw std::invalid_argument("invalid equipment VALUE/graph");
    if (value == 0) return 1;
    const auto price = std::ceil(graph * (static_cast<float>(value) / 100.0F));
    if (!std::isfinite(price) || static_cast<double>(price) > std::numeric_limits<std::int32_t>::max())
        throw std::invalid_argument("equipment price overflows int32");
    return checked(static_cast<std::int64_t>(price));
}
void validate_equipment_prices(const EquipmentPrices& p) {
    if (p.buy < 0 || p.sell < 0 || p.unidentified_buy < 0 || p.unidentified_sell < 0)
        throw std::invalid_argument("negative equipment price");
}
std::int32_t equipment_buy_price(const EquipmentPrices& p, std::int32_t count, bool identified, float barter) {
    validate_equipment_prices(p);
    if (!std::isfinite(barter)) throw std::invalid_argument("non-finite barter");
    const auto price = checked(static_cast<std::int64_t>(identified ? p.buy : p.unidentified_buy) * std::max(1,count));
    if (!identified || price <= 0) return price;
    const auto reduction = truncated(static_cast<float>(price) * (barter / 100.0F));
    return checked(std::max<std::int64_t>(1,static_cast<std::int64_t>(price) - reduction));
}
std::int32_t equipment_sell_price(const EquipmentPrices& p, std::int32_t count, bool identified, float barter) {
    validate_equipment_prices(p);
    if (!std::isfinite(barter)) throw std::invalid_argument("non-finite barter");
    const auto price = checked(static_cast<std::int64_t>(identified ? p.sell : p.unidentified_sell) * std::max(1,count));
    if (!identified) return price;
    const auto bonus = truncated(static_cast<float>(price) * (barter / 100.0F));
    return checked(static_cast<std::int64_t>(price) + bonus);
}
EquipmentPriceCatalog::EquipmentPriceCatalog(const PakArchive& p)
    : graphs_{required(p,"PRICE_PLAYERBUY_NORMAL"),required(p,"PRICE_PLAYERSELL_NORMAL"),
              required(p,"PRICE_PLAYERBUY_MAGIC"),required(p,"PRICE_PLAYERSELL_MAGIC"),
              required(p,"PRICE_PLAYERBUY_UNIQUE"),required(p,"PRICE_PLAYERSELL_UNIQUE"),
              required(p,"PRICE_PLAYERGAMBLE_MAGIC")} {}
EquipmentPrices EquipmentPriceCatalog::evaluate(std::int32_t level,std::int32_t value,PriceQuality quality,bool gambler) const {
    const auto index = static_cast<std::size_t>(quality);
    if (index > 2 || value < 0) throw std::invalid_argument("invalid equipment price input");
    if (value == 0) return {};
    const auto at = static_cast<float>(std::max(1,level));
    return {equipment_base_price(graphs_[gambler ? 6 : index*2].value(at),value),
            equipment_base_price(graphs_[index*2+1].value(at),value),
            equipment_base_price(graphs_[0].value(at),value),
            equipment_base_price(graphs_[1].value(at),value)};
}
} // namespace torchlight
