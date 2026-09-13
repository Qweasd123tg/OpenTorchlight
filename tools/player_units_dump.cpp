#include "torchlight/adm_document.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/unit_definition.hpp"

#include <iostream>
#include <string>
#include <type_traits>

namespace {

std::string narrow(const std::u16string& value) {
    return std::string(value.begin(), value.end());
}

void print_group(const torchlight::AdmGroup& group, unsigned depth) {
    const std::string indent(depth * 2U, ' ');
    std::cout << indent << '[' << narrow(group.name) << "]\n";
    for (const auto& property : group.properties) {
        std::cout << indent << narrow(property.name) << '=';
        std::visit([](const auto& value) {
            using Value = std::decay_t<decltype(value)>;
            if constexpr (std::is_same_v<Value, std::u16string>) {
                std::cout << narrow(value);
            } else if constexpr (std::is_same_v<Value, bool>) {
                std::cout << (value ? "true" : "false");
            } else {
                std::cout << value;
            }
        }, property.value);
        std::cout << '\n';
    }
    for (const auto& child : group.groups) {
        print_group(child, depth + 1U);
    }
}

} // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: torchlight_player_units_dump pak.zip\n";
        return 2;
    }
    try {
        const torchlight::PakArchive archive(argv[1]);
        const auto master = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex index(master);
        torchlight::UnitDefinitionLoader loader(archive);
        for (const auto& record : index.records()) {
            if (record.kind != torchlight::MasterResourceKind::player) {
                continue;
            }
            std::cout << "PLAYER guid=" << record.guid << " name=" << narrow(record.name)
                      << " display=" << narrow(record.display_name)
                      << " data=" << narrow(record.data_file) << '\n';
            const auto definition = loader.load(record);
            print_group(definition->root, 0);
        }
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
