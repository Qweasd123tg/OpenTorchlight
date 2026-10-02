#pragma once
#include "torchlight/economy.hpp"
#include "torchlight/inventory.hpp"
#include "torchlight/spawn_class.hpp"
#include "torchlight/unit_type.hpp"
namespace torchlight {
struct PotionOffer {
    InventoryItem item;
    EquipmentPrices prices;
    std::int32_t minimum_level=0, maximum_level=0;
};
struct PotionMerchant {
    std::int64_t guid=0;
    std::u16string name;
    float player_level_factor=0;
    std::vector<PotionOffer> potions;
    std::vector<std::u16string> unsupported_entries;
};
// Resource-derived infinite, identified, deterministic potion branch only.
// Random stock, other sale/buyback, scrolls, fish, identification, gambling and
// enchantment are not silently simulated by this service.
class PotionMerchantCatalog {
public:
    PotionMerchantCatalog(const PakArchive&, const MasterResourceIndex&, UnitDefinitionLoader&, const SpawnClassCatalog&, const UnitTypeHierarchy&);
    [[nodiscard]] const PotionMerchant* find(std::int64_t merchant_guid) const noexcept;
    [[nodiscard]] std::vector<const PotionOffer*> offers(std::int64_t merchant_guid, std::int32_t player_level) const;
    [[nodiscard]] const PotionOffer* offer(std::int64_t merchant_guid,std::int64_t item_guid,std::int32_t player_level) const;
    // Only an evaluated descriptor identical to a known identified infinite
    // potion resource can enter the bounded sale/rebuy path. Sale ignores the
    // offer generation level range; counts are kept on the owned instance.
    [[nodiscard]] const PotionOffer* trade_offer(std::int64_t merchant_guid, const InventoryItem&) const noexcept;
private:
    std::vector<PotionMerchant> merchants_;
};
enum class PurchaseStatus { purchased, unsupported, unavailable, insufficient_gold, busy, dead };
struct PurchaseResult { PurchaseStatus status=PurchaseStatus::unavailable; InventoryId item=0; std::int32_t paid=0; };
enum class SaleStatus { sold, unsupported, unavailable, busy, dead };
struct SaleResult { SaleStatus status=SaleStatus::unavailable; InventoryId item=0; std::int32_t price=0; };
[[nodiscard]] const char* purchase_message(PurchaseStatus) noexcept;
[[nodiscard]] const char* sale_message(SaleStatus) noexcept;
} // namespace torchlight
