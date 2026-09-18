// Explicit test-only preparation: grants one rolled wand (FIREWAND missile
// delivery) so the missile runtime has a real first consumer. No world/NPC/
// skill/gear-state invention beyond the grant itself:
// - the wand record comes from the real index by data file;
// - damage is rolled by roll_weapon_item (real distribution, seeded by the
//   save seed for reproducibility), never hand-picked;
// - everything after the grant (equip, approach, HIT, flight, impact) runs
//   through real input paths and the real application.
#include "torchlight/attack_action.hpp"
#include "torchlight/equipment.hpp"
#include "torchlight/inventory.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/player.hpp"
#include "torchlight/randomizer.hpp"
#include "torchlight/resource_fields.hpp"
#include "torchlight/save_store.hpp"
#include "torchlight/unit_definition.hpp"
#include "torchlight/unit_type.hpp"

#include <iostream>

using namespace torchlight;

int main(int argc, char** argv) {
    try {
        if (argc != 4) throw std::invalid_argument("missile_fixture PAK SAVE_DIR WAND_FILE");
        PakArchive pak(argv[1]);
        MasterResourceIndex index(parse_adm(pak.read_normalized("media/masterresourceunits.dat.adm")));
        UnitDefinitionLoader loader(pak);
        UnitTypeHierarchy types(pak);
        SaveStore saves(argv[2]);
        const std::string want(argv[3]);
        auto slots = saves.list(checkpoint_resource_identity(pak));
        if (slots.size() != 1 || !slots[0].loadable())
            throw std::invalid_argument("exactly one loadable fixture slot required");
        auto c = saves.read(slots[0].slot);
        const MasterResourceRecord* found = nullptr;
        for (const auto& record : index.records()) {
            if (record.kind != MasterResourceKind::item || record.do_not_create) continue;
            if (resource_fields::ascii(record.data_file).find(want) == std::string::npos) continue;
            found = &record;
            break;
        }
        if (found == nullptr) throw std::invalid_argument("wand record not found: " + want);
        const auto definition = loader.load(*found);
        const StatGraph damage_graph(pak, "media/graphs/stats/BASE_WEAPON_DAMAGE.DAT.adm");
        auto prototype = load_weapon_prototype(*found, *definition, damage_graph);
        if (!prototype) throw std::invalid_argument("wand record is not a weapon");
        prototype->attack_traits = weapon_attack_traits(found->unit_type, types);
        const auto attack_catalog = AttackEffectCatalog::discover(pak);
        prototype->attack_effects = load_constant_attack_effects(
            *definition, attack_catalog ? &*attack_catalog : nullptr);
        prototype->ai_attack_cooldown =
            static_cast<float>(resource_fields::number(definition->root, u"AI_ATTACKCOOLDOWN", 0));
        // Same order as real drops: hydrate the split, then roll concrete
        // damage from the hydrated percent (never hand-picked numbers).
        WeaponItem pre;
        pre.prototype = *prototype;
        hydrate_weapon_damage(pre, *definition);
        TorchlightRandom roller(c.seed ^ 0x1f2e3d4cu);
        WeaponItem rolled = roll_weapon_item(pre.prototype, roller, 0);
        InventoryItem item;
        item.id = c.player.inventory.next_id++;
        item.resource_guid = found->guid;
        item.name = found->name;
        item.display_name = found->display_name.empty() ? found->name : found->display_name;
        item.unit_type = found->unit_type;
        item.two_handed = types.is_a_id(found->unit_type, 10);
        {
            auto directory = resource_fields::ascii(resource_fields::text(definition->root, u"RESOURCEDIRECTORY", {}));
            if (!directory.empty() && directory.back() != '/') directory.push_back('/');
            auto file = resource_fields::ascii(resource_fields::text(definition->root, u"MESHFILE", {}));
            if (file.size() < 5U || file.substr(file.size() - 5U) != ".mesh") file += ".mesh";
            if (const auto* mesh = pak.find_normalized(directory + file)) item.mesh_path = mesh->name;
        }
        item.weapon = std::move(rolled);
        const auto id = item.id;
        c.player.inventory.items.push_back(std::move(item));
        // Wield directly: the equip VERB path is already proven by town-new
        // (unequip/equip roundtrip); the missile proof needs a wielded wand,
        // and slot disambiguation by name does not exist in the probe verbs.
        c.player.inventory.slots[static_cast<std::size_t>(InventorySlot::weapon)] = id;
        const auto revision = saves.write(c);
        std::cout << "TEST FIXTURE ONLY: granted rolled wand id=" << id << "; revision=" << revision << '\n';
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
