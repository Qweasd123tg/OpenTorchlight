#include "torchlight/adm_document.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/spawn_class.hpp"
#include "torchlight/unit_definition.hpp"
#include "torchlight/unit_type.hpp"

#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

bool has_name(const std::vector<const torchlight::UnitTypeCandidate*>& candidates,
              std::u16string_view name) {
    for (const auto* candidate : candidates) {
        if (candidate->resource->name == name) {
            return true;
        }
    }
    return false;
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: unit_type_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const auto master = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex resources(master);
        torchlight::UnitDefinitionLoader definitions(archive);
        const torchlight::UnitTypeHierarchy hierarchy(archive);
        require(hierarchy.types().size() == 162, "wrong UNITTYPE hierarchy size");
        require(hierarchy.is_a(u"NORMAL BELT", u"BELT"),
                "NORMAL BELT is not recognized as BELT");
        require(hierarchy.is_a(u"UNIQUE SWORD", u"SWORD"),
                "UNIQUE SWORD is not recognized as SWORD");
        require(hierarchy.is_a(u"UNIQUE SWORD", u"UNIQUE"),
                "UNIQUE SWORD is not recognized as UNIQUE");
        require(!hierarchy.is_a(u"SWORD", u"UNIQUE SWORD"),
                "UNITTYPE ancestry was accepted in reverse");
        require(hierarchy.find(u"normal belt") != nullptr,
                "UNITTYPE lookup is not case-insensitive");

        for (const auto& resource : resources.records()) {
            require(hierarchy.find(resource.unit_type) != nullptr,
                    "master resource references an unknown UNITTYPE");
        }
        const torchlight::SpawnClassCatalog spawn_classes(archive);
        std::set<std::u16string> selectors;
        for (const auto& definition : spawn_classes.classes()) {
            for (const auto& entry : definition.entries) {
                if (!entry.unit_type.empty() && entry.unit_type != u"NONE") {
                    selectors.insert(entry.unit_type);
                }
            }
        }
        require(selectors.size() == 67, "wrong distinct UNITTYPE selector count");
        for (const auto& selector : selectors) {
            require(hierarchy.find(selector) != nullptr,
                    "spawn class references an unknown UNITTYPE");
        }

        const torchlight::UnitTypeResourceIndex index(
            archive, hierarchy, resources, definitions);
        require(index.indexed_resource_count() > 3000,
                "too few createable positive-rarity resources were indexed");
        const auto belts = index.candidates(u"BELT", 1);
        require(!belts.empty(), "generic BELT did not include concrete subtypes");
        bool normal_belt = false;
        bool magic_belt = false;
        bool unique_belt = false;
        for (const auto* candidate : belts) {
            normal_belt = normal_belt ||
                          candidate->resource->unit_type == u"NORMAL BELT";
            magic_belt = magic_belt ||
                         candidate->resource->unit_type == u"MAGIC BELT";
            unique_belt = unique_belt ||
                          candidate->resource->unit_type == u"UNIQUE BELT";
        }
        require(normal_belt && magic_belt && unique_belt,
                "BELT hierarchy omitted a concrete rarity family");

        const auto level_one_swords = index.candidates(u"SWORD", 1);
        const auto level_two_swords = index.candidates(u"SWORD", 2);
        require(has_name(level_one_swords, u"Rusty Blade") &&
                    !has_name(level_one_swords, u"Polished Shiv") &&
                    has_name(level_two_swords, u"Polished Shiv"),
                "original item spawn range graphs were not applied");

        const auto level_one_potions = index.candidates(u"POTION", 1);
        require(level_one_potions.size() == 2 &&
                    has_name(level_one_potions, u"Health Potion") &&
                    has_name(level_one_potions, u"Mana Potion"),
                "level-one potion range or zero-rarity filtering is wrong");
        const auto level_seven_potions = index.candidates(u"POTION", 7);
        require(level_seven_potions.size() == 2 &&
                    has_name(level_seven_potions, u"Health Potion 2") &&
                    has_name(level_seven_potions, u"Mana Potion 2"),
                "level-seven potion range is wrong");
        require(index.candidates(u"UNIQUE CROSSBOW", 1).empty(),
                "absent UNIQUE CROSSBOW data unexpectedly resolved");

        torchlight::TorchlightRandom first(17);
        torchlight::TorchlightRandom second(17);
        const auto* first_roll = index.roll(u"POTION", 1, first);
        const auto* second_roll = index.roll(u"potion", 1, second);
        require(first_roll != nullptr && second_roll != nullptr &&
                    first_roll->guid == second_roll->guid,
                "UNITTYPE weighted choice is not deterministic");
        std::set<std::u16string> potion_results;
        for (std::uint32_t seed = 1; seed <= 64; ++seed) {
            torchlight::TorchlightRandom random(seed);
            const auto* result = index.roll(u"POTION", 1, random);
            require(result != nullptr, "eligible potion roll returned no resource");
            potion_results.insert(result->name);
        }
        require(potion_results.size() == 2,
                "positive-rarity level-one potion choices are not both reachable");

        std::cout << "PASS: resolved " << selectors.size()
                  << " spawn selectors through " << hierarchy.types().size()
                  << " original UNITTYPE definitions\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
