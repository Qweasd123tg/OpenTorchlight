#include "torchlight/adm_document.hpp"
#include "torchlight/equipment.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/stat_graph.hpp"
#include "torchlight/unit_definition.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

namespace {
void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}
}

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: equipment_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const auto master = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex resources(master);
        torchlight::UnitDefinitionLoader definitions(archive);
        const torchlight::StatGraph armor_graph(
            archive, "media/graphs/stats/ARMOR_PLAYER_BYLEVEL_FORSET.DAT.adm");
        const auto* leather = resources.find_case_insensitive(
            torchlight::MasterResourceKind::item, u"a Leather Vest");
        require(leather != nullptr && leather->unit_type == u"NORMAL CHEST ARMOR",
                "original Leather Vest resource is missing");
        const auto definition = definitions.load(*leather);

        torchlight::TorchlightRandom normal_random(123);
        const auto normal = torchlight::roll_armor_item(
            *leather, *definition, armor_graph, normal_random);
        require(normal && normal->slot == torchlight::ArmorSlot::chest &&
                    normal->level == 1 && normal->armor == 4 &&
                    normal->damage_defense.natural_armor == 4,
                "Leather Vest armor graph calculation changed");

        torchlight::TorchlightRandom rare_random(123);
        const auto rare = torchlight::roll_armor_item(
            *leather, *definition, armor_graph, rare_random, 5);
        require(rare && rare->armor == 9,
                "generated rarity rank was not added to graph armor");
        require(torchlight::armor_slot_for_unit_type(u"MAGIC HELMET") ==
                    torchlight::ArmorSlot::helmet &&
                    !torchlight::armor_slot_for_unit_type(u"MAGIC SWORD"),
                "equipment unit type mapped to the wrong armor slot");

        std::cout << "PASS: rolled original Leather Vest armor=4 rarity5=9\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
