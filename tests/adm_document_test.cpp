#include "torchlight/adm_document.hpp"
#include "torchlight/pak_archive.hpp"

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

struct TreeStats {
    std::size_t groups = 0;
    std::size_t properties = 0;
};

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void add_stats(const torchlight::AdmGroup& group, TreeStats& stats) {
    ++stats.groups;
    stats.properties += group.properties.size();
    for (const auto& child : group.groups) {
        add_stats(child, stats);
    }
}

TreeStats stats(const torchlight::AdmGroup& root) {
    TreeStats result;
    add_stats(root, result);
    return result;
}

void check_document(const torchlight::PakArchive& archive, const char* path,
                    std::size_t dictionary_size, const char16_t* root_name,
                    std::size_t group_count, std::size_t property_count) {
    const auto document = torchlight::parse_adm(archive.read(path));
    require(document.version == 1, "unexpected ADM version");
    require(document.dictionary.size() == dictionary_size, "unexpected ADM dictionary size");
    require(document.root.name == root_name, "unexpected ADM root name");
    const auto totals = stats(document.root);
    require(totals.groups == group_count, "unexpected ADM group count");
    require(totals.properties == property_count, "unexpected ADM property count");
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: adm_document_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        check_document(archive, "media/GLOBALS.DAT.adm", 565, u"GLOBALS", 5, 332);
        check_document(archive, "media/EFFECTSLIST.DAT.adm", 745, u"EFFECTLIST", 146, 2052);
        check_document(archive, "media/MASTERRESOURCEUNITS.DAT.ADM", 18667, u"UNITS", 15154,
                       142433);

        const auto globals = torchlight::parse_adm(archive.read("media/GLOBALS.DAT.adm"));
        const auto* weight = globals.root.find_property(u"NORMAL_ITEM_WEIGHT");
        require(weight != nullptr, "NORMAL_ITEM_WEIGHT is missing");
        require(weight->type == torchlight::AdmValueType::integer, "unexpected property type");
        require(std::get<std::int32_t>(weight->value) == 5000, "unexpected property value");
        std::cout << "PASS: parsed 3 original ADM trees with 15305 groups and 144817 properties\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
