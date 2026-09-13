#include "torchlight/unit_definition.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace torchlight {
namespace {

class UnitDefinitionError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

std::string normalize_path(std::string_view path) {
    std::string result;
    result.reserve(path.size());
    for (const unsigned char character : path) {
        if (character == '\\') {
            result.push_back('/');
        } else if (character >= 'A' && character <= 'Z') {
            result.push_back(static_cast<char>(character - 'A' + 'a'));
        } else {
            result.push_back(static_cast<char>(character));
        }
    }
    return result;
}

const std::u16string* text_property(const AdmGroup& group, const char16_t* name) {
    const auto* property = group.find_property(name);
    if (property == nullptr) {
        return nullptr;
    }
    if (property->type != AdmValueType::string && property->type != AdmValueType::translation &&
        property->type != AdmValueType::note) {
        throw UnitDefinitionError("Unit property expected to contain text");
    }
    return &std::get<std::u16string>(property->value);
}

bool boolean_property(const AdmGroup& group, const char16_t* name, bool fallback) {
    const auto* property = group.find_property(name);
    if (property == nullptr) {
        return fallback;
    }
    if (property->type != AdmValueType::boolean) {
        throw UnitDefinitionError("Unit property expected to contain a boolean");
    }
    return std::get<bool>(property->value);
}

void set_text_property(AdmGroup& group, const char16_t* name, const std::u16string& value) {
    for (auto& property : group.properties) {
        if (property.name == name) {
            property.type = AdmValueType::string;
            property.value = value;
            return;
        }
    }
    AdmProperty property;
    property.name = name;
    property.type = AdmValueType::string;
    property.value = value;
    group.properties.push_back(std::move(property));
}

void set_boolean_property(AdmGroup& group, const char16_t* name, bool value) {
    for (auto& property : group.properties) {
        if (property.name == name) {
            property.type = AdmValueType::boolean;
            property.value = value;
            return;
        }
    }
    AdmProperty property;
    property.name = name;
    property.type = AdmValueType::boolean;
    property.value = value;
    group.properties.push_back(std::move(property));
}

// CDataGroup::CopyDataGroup replaces one existing property with each source
// property of the same name. Additional duplicates are appended. Child groups
// are appended in source order rather than merged by name.
void copy_data_group(AdmGroup& destination, const AdmGroup& source) {
    const auto inherited_property_count = destination.properties.size();
    std::vector<bool> available(inherited_property_count, true);
    for (const auto& source_property : source.properties) {
        auto match = inherited_property_count;
        for (std::size_t index = 0; index < inherited_property_count; ++index) {
            if (available[index] && destination.properties[index].name == source_property.name) {
                match = index;
                break;
            }
        }
        if (match == inherited_property_count) {
            destination.properties.push_back(source_property);
        } else {
            destination.properties[match] = source_property;
            available[match] = false;
        }
    }
    destination.groups.insert(destination.groups.end(), source.groups.begin(), source.groups.end());
}

} // namespace

std::shared_ptr<const UnitDefinition> UnitDefinitionLoader::load(
    const MasterResourceRecord& record) {
    return load(record.data_file);
}

std::shared_ptr<const UnitDefinition> UnitDefinitionLoader::load(std::u16string_view data_file) {
    std::unordered_set<std::string> active_paths;
    return load_compiled(compiled_adm_path(data_file), active_paths);
}

std::shared_ptr<const UnitDefinition> UnitDefinitionLoader::load_compiled(
    std::string path, std::unordered_set<std::string>& active_paths) {
    const auto normalized = normalize_path(path);
    const auto cached = cache_.find(normalized);
    if (cached != cache_.end()) {
        return cached->second;
    }
    if (!active_paths.emplace(normalized).second) {
        throw UnitDefinitionError("Cycle in unit BASEFILE inheritance at " + path);
    }

    const auto* entry = archive_.find_normalized(path);
    if (entry == nullptr) {
        active_paths.erase(normalized);
        throw UnitDefinitionError("Unit file is absent from pak.zip: " + path);
    }
    const auto child_document = parse_adm(archive_.read(*entry));
    if (child_document.root.name != u"UNIT") {
        active_paths.erase(normalized);
        throw UnitDefinitionError("Unit file root is not UNIT: " + entry->name);
    }

    auto result = std::make_shared<UnitDefinition>();
    result->root = child_document.root;
    result->inheritance_chain.push_back(entry->name);
    const auto* base_file = text_property(child_document.root, u"BASEFILE");
    if (base_file != nullptr && !base_file->empty()) {
        const auto child_guid = text_property(child_document.root, u"UNIT_GUID");
        if (child_guid == nullptr || child_guid->empty()) {
            active_paths.erase(normalized);
            throw UnitDefinitionError("Inherited unit has no UNIT_GUID: " + entry->name);
        }
        const auto child_do_not_create = boolean_property(child_document.root, u"DONTCREATE", false);
        auto base = load_compiled(compiled_adm_path(*base_file), active_paths);
        result->root = base->root;
        copy_data_group(result->root, child_document.root);

        // The original parseChildFile restores these values from the child
        // after CopyDataGroup so a spawnable child does not inherit the base's
        // usual DONTCREATE=true marker.
        set_text_property(result->root, u"UNIT_GUID", *child_guid);
        set_boolean_property(result->root, u"DONTCREATE", child_do_not_create);
        result->inheritance_chain.insert(result->inheritance_chain.end(),
                                         base->inheritance_chain.begin(),
                                         base->inheritance_chain.end());
    }

    active_paths.erase(normalized);
    const auto inserted = cache_.emplace(normalized, std::move(result));
    return inserted.first->second;
}

} // namespace torchlight
