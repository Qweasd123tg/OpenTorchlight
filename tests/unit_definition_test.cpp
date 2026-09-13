#include "torchlight/adm_document.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/unit_definition.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

const torchlight::AdmProperty& property(const torchlight::UnitDefinition& unit,
                                        const char16_t* name) {
    const auto* result = unit.find_property(name);
    require(result != nullptr, "expected merged unit property is missing");
    return *result;
}

const std::u16string& text(const torchlight::UnitDefinition& unit, const char16_t* name) {
    const auto& result = property(unit, name);
    require(result.type == torchlight::AdmValueType::string ||
                result.type == torchlight::AdmValueType::translation ||
                result.type == torchlight::AdmValueType::note,
            "expected merged text property has the wrong type");
    return std::get<std::u16string>(result.value);
}

std::int32_t integer(const torchlight::UnitDefinition& unit, const char16_t* name) {
    const auto& result = property(unit, name);
    require(result.type == torchlight::AdmValueType::integer,
            "expected merged integer property has the wrong type");
    return std::get<std::int32_t>(result.value);
}

float floating(const torchlight::UnitDefinition& unit, const char16_t* name) {
    const auto& result = property(unit, name);
    require(result.type == torchlight::AdmValueType::floating,
            "expected merged float property has the wrong type");
    return std::get<float>(result.value);
}

bool boolean(const torchlight::UnitDefinition& unit, const char16_t* name) {
    const auto& result = property(unit, name);
    require(result.type == torchlight::AdmValueType::boolean,
            "expected merged boolean property has the wrong type");
    return std::get<bool>(result.value);
}

std::u16string decimal_guid(std::int64_t guid) {
    const auto ascii = std::to_string(guid);
    return std::u16string(ascii.begin(), ascii.end());
}

} // namespace

int main(int argc, char** argv) {
    try {
        if (argc != 3 || std::string(argv[1]) != "--original") {
            std::cerr << "usage: unit_definition_test --original /path/to/pak.zip\n";
            return 2;
        }
        const torchlight::PakArchive archive(argv[2]);
        const auto master_document = torchlight::parse_adm(
            archive.read("media/MASTERRESOURCEUNITS.DAT.ADM"));
        const torchlight::MasterResourceIndex index(master_document);
        torchlight::UnitDefinitionLoader loader(archive);

        const auto* necklace_record = index.find(-5728334769957695010LL);
        require(necklace_record != nullptr, "necklace is missing from the master index");
        const auto necklace = loader.load(*necklace_record);
        require(necklace->inheritance_chain.size() >= 2,
                "necklace BASEFILE inheritance was not followed");
        require(text(*necklace, u"UNIT_GUID") == u"-5728334769957695010",
                "child UNIT_GUID was not retained");
        require(text(*necklace, u"CREATEAS") == u"EQUIPMENT",
                "CREATEAS was not inherited");
        require(text(*necklace, u"MESHFILE") == u"necklace", "MESHFILE was not inherited");
        require(integer(*necklace, u"LEVEL") == 5, "child LEVEL did not override the base");
        require(!boolean(*necklace, u"DONTCREATE"),
                "child inherited the base DONTCREATE marker");

        const auto* construct_record = index.find(-3015820510006275618LL);
        require(construct_record != nullptr, "construct is missing from the master index");
        const auto construct = loader.load(*construct_record);
        require(floating(*construct, u"WALKINGSPEED") == 3.0F,
                "monster WALKINGSPEED did not override the base");
        require(integer(*construct, u"MINDAMAGE") == 70,
                "monster MINDAMAGE did not override the base");
        require(!boolean(*construct, u"DONTCREATE"),
                "monster inherited the base DONTCREATE marker");

        std::size_t loaded = 0;
        std::size_t longest_chain = 0;
        for (const auto& record : index.records()) {
            const auto unit = loader.load(record);
            require(unit->root.name == u"UNIT", "merged resource root is not UNIT");
            require(text(*unit, u"UNIT_GUID") == decimal_guid(record.guid),
                    "merged unit has the wrong child GUID");
            longest_chain = std::max(longest_chain, unit->inheritance_chain.size());
            ++loaded;
        }
        std::cout << "PASS: loaded and inherited " << loaded
                  << " original unit definitions; longest BASEFILE chain=" << longest_chain
                  << ", cached files=" << loader.cached_definition_count() << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
