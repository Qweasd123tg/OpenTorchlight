#include "torchlight/master_resource_index.hpp"

#include <charconv>
#include <stdexcept>
#include <string_view>
#include <system_error>

namespace torchlight {
namespace {

class MasterResourceError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

bool is_text_type(AdmValueType type) noexcept {
    return type == AdmValueType::string || type == AdmValueType::translation ||
           type == AdmValueType::note;
}

bool same_ascii_case_insensitive(std::u16string_view left,
                                 std::u16string_view right) noexcept {
    if (left.size() != right.size()) {
        return false;
    }
    for (std::size_t index = 0; index < left.size(); ++index) {
        const auto fold = [](char16_t character) {
            return character >= u'a' && character <= u'z'
                       ? static_cast<char16_t>(character - u'a' + u'A')
                       : character;
        };
        if (fold(left[index]) != fold(right[index])) {
            return false;
        }
    }
    return true;
}

const AdmProperty& required_property(const AdmGroup& group, const char16_t* name) {
    const auto* property = group.find_property(name);
    if (property == nullptr) {
        throw MasterResourceError("Master resource is missing a required property");
    }
    return *property;
}

std::u16string optional_text(const AdmGroup& group, const char16_t* name) {
    const auto* property = group.find_property(name);
    if (property == nullptr) {
        return {};
    }
    if (!is_text_type(property->type)) {
        throw MasterResourceError("Master resource text property has a non-text type");
    }
    return std::get<std::u16string>(property->value);
}

std::u16string required_text(const AdmGroup& group, const char16_t* name) {
    const auto& property = required_property(group, name);
    if (!is_text_type(property.type)) {
        throw MasterResourceError("Master resource required text property has a non-text type");
    }
    return std::get<std::u16string>(property.value);
}

bool required_boolean(const AdmGroup& group, const char16_t* name) {
    const auto& property = required_property(group, name);
    if (property.type != AdmValueType::boolean) {
        throw MasterResourceError("Master resource boolean property has the wrong type");
    }
    return std::get<bool>(property.value);
}

std::uint32_t required_unsigned(const AdmGroup& group, const char16_t* name) {
    const auto& property = required_property(group, name);
    if (property.type != AdmValueType::unsigned_integer) {
        throw MasterResourceError("Master resource unsigned property has the wrong type");
    }
    return std::get<std::uint32_t>(property.value);
}

std::int64_t parse_guid(const std::u16string& value) {
    std::string ascii;
    ascii.reserve(value.size());
    for (const auto character : value) {
        if (character > 0x7fU) {
            throw MasterResourceError("Master resource GUID contains a non-ASCII character");
        }
        ascii.push_back(static_cast<char>(character));
    }
    std::int64_t result = 0;
    const auto parsed = std::from_chars(ascii.data(), ascii.data() + ascii.size(), result);
    if (ascii.empty() || parsed.ec != std::errc{} || parsed.ptr != ascii.data() + ascii.size()) {
        throw MasterResourceError("Master resource GUID is not a signed 64-bit decimal number");
    }
    return result;
}

MasterResourceKind parse_kind(const std::u16string& name) {
    if (name == u"ITEMS") {
        return MasterResourceKind::item;
    }
    if (name == u"MONSTERS") {
        return MasterResourceKind::monster;
    }
    if (name == u"PLAYERS") {
        return MasterResourceKind::player;
    }
    if (name == u"PROPS") {
        return MasterResourceKind::prop;
    }
    throw MasterResourceError("Unknown top-level master resource group");
}

MasterResourceRecord parse_record(const AdmGroup& group) {
    MasterResourceRecord record;
    record.kind = parse_kind(group.name);
    record.guid = parse_guid(required_text(group, u"UNIT_GUID"));
    record.unit_type = required_text(group, u"UNITTYPE");
    record.create_as = optional_text(group, u"CREATEAS");
    record.file_item = required_text(group, u"FILEITEM");
    record.data_file = required_text(group, u"DATFILE");
    record.base_file = optional_text(group, u"BASEFILE");
    record.name = optional_text(group, u"NAME");
    record.display_name = optional_text(group, u"DISPLAYNAME");
    record.do_not_create = required_boolean(group, u"DONTCREATE");
    record.resource_group = required_unsigned(group, u"RESOURCEGROUP");
    return record;
}

} // namespace

std::string compiled_adm_path(std::u16string_view data_file) {
    std::string result;
    result.reserve(data_file.size() + 4U);
    for (const auto character : data_file) {
        if (character > 0x7fU) {
            throw MasterResourceError("Master resource DATFILE contains a non-ASCII character");
        }
        result.push_back(character == u'\\' ? '/' : static_cast<char>(character));
    }
    result += ".adm";
    return result;
}

std::string MasterResourceRecord::compiled_adm_path() const {
    return torchlight::compiled_adm_path(data_file);
}

MasterResourceIndex::MasterResourceIndex(const AdmDocument& document) {
    if (document.root.name != u"UNITS") {
        throw MasterResourceError("Master resource document root is not UNITS");
    }
    records_.reserve(document.root.groups.size());
    by_guid_.reserve(document.root.groups.size());
    for (const auto& group : document.root.groups) {
        auto record = parse_record(group);
        const auto index = records_.size();
        if (!by_guid_.emplace(record.guid, index).second) {
            throw MasterResourceError("Duplicate master resource GUID");
        }
        records_.push_back(std::move(record));
    }
}

const MasterResourceRecord* MasterResourceIndex::find(std::int64_t guid) const noexcept {
    const auto found = by_guid_.find(guid);
    return found == by_guid_.end() ? nullptr : &records_[found->second];
}

const MasterResourceRecord* MasterResourceIndex::find(MasterResourceKind kind,
                                                      std::u16string_view name) const noexcept {
    for (const auto& record : records_) {
        if (record.kind == kind && record.name == name) {
            return &record;
        }
    }
    return nullptr;
}

const MasterResourceRecord* MasterResourceIndex::find_any(
    std::u16string_view name) const noexcept {
    for (const auto& record : records_) {
        if (same_ascii_case_insensitive(record.name, name)) {
            return &record;
        }
    }
    return nullptr;
}

std::size_t MasterResourceIndex::count(MasterResourceKind kind) const noexcept {
    std::size_t result = 0;
    for (const auto& record : records_) {
        if (record.kind == kind) {
            ++result;
        }
    }
    return result;
}

} // namespace torchlight
