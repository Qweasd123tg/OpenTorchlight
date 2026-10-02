#include "torchlight/merchant.hpp"
#include "torchlight/resource_fields.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
namespace torchlight {
namespace { namespace rf=resource_fields; }
PotionMerchantCatalog::PotionMerchantCatalog(const PakArchive&pak,const MasterResourceIndex&index,UnitDefinitionLoader&loader,const SpawnClassCatalog&classes,const UnitTypeHierarchy&types) {
    std::optional<EquipmentPriceCatalog> prices;
    const auto effects=AttackEffectCatalog::discover(pak);
    for(const auto& record:index.records()) {
        if(!types.is_a(record.unit_type,u"MERCHANT"))continue;
        const auto definition=loader.load(record);
        const auto& root=definition->root;
        const auto* treasure=rf::child(root,u"TREASURE");
        if(!treasure||rf::integer(*treasure,u"MIN",0)!=1||rf::integer(*treasure,u"MAX",0)!=1)continue;
        const auto* stock=classes.find(rf::text(*treasure,u"SPAWNCLASS"));
        const auto factor=static_cast<float>(rf::number(root,u"PLAYER_LEVEL_FOR_MERCHANT",0));
        if(!stock||!(factor>0)||!std::isfinite(factor))continue;
        PotionMerchant merchant{record.guid,record.display_name.empty()?record.name:record.display_name,factor,{},{}};
        for(const auto& entry:stock->entries) {
            const auto reject=[&]{merchant.unsupported_entries.push_back(!entry.unit.empty()?entry.unit:!entry.spawn_class.empty()?entry.spawn_class:entry.unit_type);};
            if(entry.unit.empty()||entry.weight!=-1||entry.minimum_count!=1||entry.maximum_count!=1){reject();continue;}
            const auto* item=index.find_case_insensitive(MasterResourceKind::item,entry.unit);
            if(!item||item->do_not_create||!types.is_a(item->unit_type,u"POTION")){reject();continue;}
            AdmGroup entry_fields;entry_fields.properties=entry.properties;
            if(rf::integer(entry_fields,u"RARITY_OVERRIDE",-1)!=1){reject();continue;}
            const auto unit=loader.load(*item);const auto&g=unit->root;
            auto consumable=load_consumable(pak,*unit,effects?&*effects:nullptr);
            if(!consumable||!consumable->unavailable_reason.empty()||consumable->count!=1||consumable->uses!=1||!rf::flag(g,u"MERCHANTINFINITE")){reject();continue;}
            // Only explicit ranges: do not replace an item-range graph with a guessed bound.
            const auto minimum=rf::integer(g,u"MINLEVEL",0),maximum=rf::integer(g,u"MAXLEVEL",0);
            if(maximum<=0||minimum>maximum){reject();continue;}
            if(!prices)prices.emplace(pak);
            PotionOffer offer;
            offer.minimum_level=minimum;offer.maximum_level=maximum;
            offer.prices=prices->evaluate(rf::integer(g,u"LEVEL",1),rf::integer(g,u"VALUE",100),PriceQuality::normal);
            offer.item.resource_guid=item->guid;offer.item.name=item->name;offer.item.display_name=item->display_name;
            offer.item.unit_type=item->unit_type;
            offer.item.mesh_path=unit_model_path(*unit);
            if (const auto* mesh=pak.find_normalized(offer.item.mesh_path)) offer.item.mesh_path=mesh->name;
            offer.item.consumable=std::move(consumable);
            merchant.potions.push_back(std::move(offer));
        }
        if(!merchant.potions.empty())merchants_.push_back(std::move(merchant));
    }
}
const PotionMerchant* PotionMerchantCatalog::find(std::int64_t id)const noexcept {for(const auto&m:merchants_)if(m.guid==id)return &m;return nullptr;}
std::vector<const PotionOffer*> PotionMerchantCatalog::offers(std::int64_t id,std::int32_t level)const {
    std::vector<const PotionOffer*> result;const auto*m=find(id);if(!m||level<1)return result;
    const float scaled=std::ceil(static_cast<float>(level)*m->player_level_factor);
    if(!std::isfinite(scaled)||static_cast<double>(scaled)>std::numeric_limits<std::int32_t>::max())throw std::invalid_argument("merchant level overflow");
    const auto at=static_cast<std::int32_t>(scaled);
    for(const auto&o:m->potions)if(at>=o.minimum_level&&at<=o.maximum_level)result.push_back(&o);
    return result;
}
const PotionOffer* PotionMerchantCatalog::offer(std::int64_t id,std::int64_t item,std::int32_t level)const {for(const auto*o:offers(id,level))if(o->item.resource_guid==item)return o;return nullptr;}
const PotionOffer* PotionMerchantCatalog::trade_offer(std::int64_t id,const InventoryItem& item)const noexcept {
    const auto* merchant=find(id);
    if(!merchant||!item.consumable||item.weapon||item.armor||item.two_handed)return nullptr;
    for(const auto& offer:merchant->potions) {
        const auto& known=offer.item;
        if(item.resource_guid==known.resource_guid&&item.name==known.name&&
           item.display_name==known.display_name&&item.unit_type==known.unit_type&&
           item.mesh_path==known.mesh_path&&same_consumable(*item.consumable,*known.consumable))return &offer;
    }
    return nullptr;
}
const char* purchase_message(PurchaseStatus s)noexcept{switch(s){case PurchaseStatus::purchased:return "POTION PURCHASED";case PurchaseStatus::unsupported:return "MERCHANT SERVICE NOT IMPLEMENTED";case PurchaseStatus::unavailable:return "ITEM NOT AVAILABLE";case PurchaseStatus::insufficient_gold:return "NOT ENOUGH GOLD";case PurchaseStatus::busy:return "FINISH CURRENT ACTION FIRST";case PurchaseStatus::dead:return "PLAYER IS DEAD";}return "PURCHASE FAILED";}
const char* sale_message(SaleStatus s)noexcept{switch(s){case SaleStatus::sold:return "POTION SOLD";case SaleStatus::unsupported:return "ITEM CANNOT BE SOLD";case SaleStatus::unavailable:return "ITEM OR MERCHANT UNAVAILABLE";case SaleStatus::busy:return "FINISH CURRENT ACTION FIRST";case SaleStatus::dead:return "PLAYER IS DEAD";}return "SALE FAILED";}
} // namespace torchlight
