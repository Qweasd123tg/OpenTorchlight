#include "torchlight/adm_document.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: master_resource_index_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const auto document = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex index(document);

        require(index.records().size() == 3343, "unexpected master resource count");
        require(index.count(torchlight::MasterResourceKind::item) == 2959,
                "unexpected item count");
        require(index.count(torchlight::MasterResourceKind::monster) == 295,
                "unexpected monster count");
        require(index.count(torchlight::MasterResourceKind::player) == 4,
                "unexpected player count");
        require(index.count(torchlight::MasterResourceKind::prop) == 85,
                "unexpected prop count");

        const auto* necklace = index.find(-5728334769957695010LL);
        require(necklace != nullptr, "necklace GUID lookup failed");
        require(necklace->kind == torchlight::MasterResourceKind::item,
                "necklace has the wrong kind");
        require(necklace->unit_type == u"RANDOMMAGIC NECKLACE",
                "necklace has the wrong unit type");
        require(necklace->display_name == u"Enchanted Necklace",
                "necklace has the wrong display name");
        require(necklace->resource_group == 0, "necklace has the wrong resource group");
        require(necklace->compiled_adm_path() ==
                    "MEDIA/UNITS/ITEMS/AMULETS/NECKLACE_MAGIC_01.DAT.adm",
                "necklace has the wrong compiled path");

        const auto* construct = index.find(-3015820510006275618LL);
        require(construct != nullptr, "monster GUID lookup failed");
        require(construct->kind == torchlight::MasterResourceKind::monster,
                "monster has the wrong kind");
        require(construct->create_as.empty(), "monster unexpectedly has CREATEAS");

        std::size_t resolved_paths = 0;
        for (const auto& record : index.records()) {
            require(archive.contains_normalized(record.compiled_adm_path()),
                    "master resource DATFILE is absent from pak.zip");
            ++resolved_paths;
        }
        require(index.find(123456789) == nullptr, "unknown GUID lookup returned a record");
        std::cout << "PASS: indexed 3343 master resources and resolved " << resolved_paths
                  << " compiled DAT paths in the original archive\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
