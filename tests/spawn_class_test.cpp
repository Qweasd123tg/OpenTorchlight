#include "torchlight/adm_document.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/spawn_class.hpp"

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

bool has_unit_name(const torchlight::MasterResourceIndex& resources,
                   const std::u16string& name) {
    return resources.find_any(name) != nullptr;
}

bool same_leaves(const std::vector<torchlight::SpawnLeaf>& left,
                 const std::vector<torchlight::SpawnLeaf>& right) {
    if (left.size() != right.size()) {
        return false;
    }
    for (std::size_t index = 0; index < left.size(); ++index) {
        if (left[index].kind != right[index].kind || left[index].value != right[index].value) {
            return false;
        }
    }
    return true;
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: spawn_class_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const auto master = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex resources(master);
        const torchlight::SpawnClassCatalog catalog(archive);
        require(catalog.classes().size() == 388, "wrong spawn-class count");
        require(catalog.entry_count() == 1215, "wrong spawn-class entry count");

        std::size_t unit_entries = 0;
        std::size_t unit_type_entries = 0;
        std::size_t nested_entries = 0;
        for (const auto& definition : catalog.classes()) {
            require(catalog.find(definition.name) == &definition,
                    "spawn-class lookup did not preserve identity");
            for (const auto& entry : definition.entries) {
                if (!entry.unit.empty()) {
                    ++unit_entries;
                    if (!has_unit_name(resources, entry.unit)) {
                        throw std::runtime_error(
                            "spawn-class UNIT is absent from master resources: " +
                            std::string(entry.unit.begin(), entry.unit.end()));
                    }
                } else if (!entry.unit_type.empty()) {
                    ++unit_type_entries;
                } else {
                    ++nested_entries;
                    require(catalog.find(entry.spawn_class) != nullptr,
                            "nested spawn class is absent");
                }
            }
            for (std::uint32_t seed = 1; seed <= 4; ++seed) {
                torchlight::TorchlightRandom first(seed);
                torchlight::TorchlightRandom second(seed);
                const auto first_roll = catalog.roll(definition.name, first);
                const auto second_roll = catalog.roll(definition.name, second);
                require(same_leaves(first_roll, second_roll),
                        "spawn-class roll is not deterministic");
                for (const auto& leaf : first_roll) {
                    require(!leaf.value.empty(), "spawn-class roll produced an empty leaf");
                    require(leaf.kind != torchlight::SpawnLeafKind::unit ||
                                has_unit_name(resources, leaf.value),
                            "spawn-class roll produced an unresolved UNIT leaf");
                }
            }
        }
        require(unit_entries == 528, "wrong UNIT selector count");
        require(unit_type_entries == 124, "wrong UNITTYPE selector count");
        require(nested_entries == 563, "wrong nested selector count");

        std::set<std::u16string> skeletons;
        for (std::uint32_t seed = 1; seed <= 64; ++seed) {
            torchlight::TorchlightRandom random(seed);
            for (const auto& leaf : catalog.roll(u"SKELETONS", random)) {
                require(leaf.kind == torchlight::SpawnLeafKind::unit,
                        "SKELETONS resolved to a non-unit selector");
                skeletons.insert(leaf.value);
            }
        }
        require(skeletons.size() == 3, "weighted SKELETONS choices were not all reachable");
        require(catalog.find(u"minefloor1") != nullptr,
                "spawn-class lookup is not case-insensitive");
        std::cout << "PASS: parsed " << catalog.classes().size() << " spawn classes with "
                  << catalog.entry_count() << " weighted entries\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
