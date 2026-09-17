#include "torchlight/spawn_class.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <utility>

namespace torchlight {
namespace {

constexpr std::size_t kMaximumSpawnLeaves = 4096;

class SpawnClassError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

bool is_text(AdmValueType type) noexcept {
    return type == AdmValueType::string || type == AdmValueType::translation ||
           type == AdmValueType::note;
}

const std::u16string* optional_text(const AdmGroup& group, const char16_t* name) {
    const auto* property = group.find_property(name);
    if (property == nullptr) {
        return nullptr;
    }
    if (!is_text(property->type)) {
        throw SpawnClassError("Spawn-class selector has the wrong type");
    }
    return &std::get<std::u16string>(property->value);
}

std::int32_t optional_integer(const AdmGroup& group, const char16_t* name,
                              std::int32_t fallback) {
    const auto* property = group.find_property(name);
    if (property == nullptr) {
        return fallback;
    }
    if (property->type != AdmValueType::integer) {
        throw SpawnClassError("Spawn-class integer has the wrong type");
    }
    return std::get<std::int32_t>(property->value);
}

std::u16string required_text(const AdmGroup& group, const char16_t* name) {
    const auto* value = optional_text(group, name);
    if (value == nullptr || value->empty()) {
        throw SpawnClassError("Spawn class has no name");
    }
    return *value;
}

std::u16string normalized_name(std::u16string_view name) {
    std::u16string result;
    result.reserve(name.size());
    for (const auto character : name) {
        result.push_back(character >= u'a' && character <= u'z'
                             ? static_cast<char16_t>(character - u'a' + u'A')
                             : character);
    }
    return result;
}

bool is_spawn_class_path(std::string_view path) {
    std::string normalized;
    normalized.reserve(path.size());
    for (const unsigned char character : path) {
        normalized.push_back(character >= 'A' && character <= 'Z'
                                 ? static_cast<char>(character - 'A' + 'a')
                                 : static_cast<char>(character));
    }
    constexpr std::string_view prefix = "media/spawnclasses/";
    constexpr std::string_view suffix = ".dat.adm";
    return normalized.size() > prefix.size() + suffix.size() &&
           normalized.compare(0, prefix.size(), prefix) == 0 &&
           normalized.compare(normalized.size() - suffix.size(), suffix.size(), suffix) == 0;
}

SpawnClassEntry parse_entry(const AdmGroup& group) {
    if (group.name != u"OBJECT") {
        throw SpawnClassError("Spawn-class child is not OBJECT");
    }
    SpawnClassEntry result;
    if (const auto* value = optional_text(group, u"UNIT")) {
        result.unit = *value;
    }
    if (const auto* value = optional_text(group, u"UNITTYPE")) {
        result.unit_type = *value;
    }
    if (const auto* value = optional_text(group, u"SPAWNCLASS")) {
        result.spawn_class = *value;
    }
    const auto selector_count = static_cast<unsigned>(!result.unit.empty()) +
                                static_cast<unsigned>(!result.unit_type.empty()) +
                                static_cast<unsigned>(!result.spawn_class.empty());
    if (selector_count != 1U) {
        throw SpawnClassError("Spawn-class entry must have exactly one selector");
    }
    // addSpawnClassData 0xa7623e: default -1; 0xa76342..4f: zero -> -1.
    result.weight = optional_integer(group, u"WEIGHT", -1);
    if (result.weight == 0) result.weight = -1;
    result.minimum_count = optional_integer(group, u"MINCOUNT", 1);
    result.maximum_count = optional_integer(group, u"MAXCOUNT", 1);
    if (result.weight < -1 || result.minimum_count < 0 || result.maximum_count < 0) {
        throw SpawnClassError("Spawn-class entry has an invalid weight or count range: weight=" +
                              std::to_string(result.weight) + " min=" +
                              std::to_string(result.minimum_count) + " max=" +
                              std::to_string(result.maximum_count));
    }
    result.properties = group.properties;
    return result;
}

} // namespace

SpawnClassCatalog::SpawnClassCatalog(const PakArchive& archive) {
    for (const auto& entry : archive.entries()) {
        if (!entry.is_directory() && is_spawn_class_path(entry.name)) {
            const auto document = parse_adm(archive.read(entry));
            if (document.root.name != u"SPAWNCLASS") {
                throw SpawnClassError("Spawn-class file root is not SPAWNCLASS: " + entry.name);
            }
            SpawnClassDefinition definition;
            definition.name = required_text(document.root, u"NAME");
            definition.source_path = entry.name;
            definition.entries.reserve(document.root.groups.size());
            for (const auto& group : document.root.groups) {
                try {
                    definition.entries.push_back(parse_entry(group));
                } catch (const std::exception& error) {
                    throw SpawnClassError(entry.name + ": " + error.what());
                }
            }
            entry_count_ += definition.entries.size();
            const auto index = classes_.size();
            const auto key = normalized_name(definition.name);
            if (!by_name_.emplace(key, index).second) {
                throw SpawnClassError("Duplicate spawn-class name");
            }
            classes_.push_back(std::move(definition));
        }
    }

    for (const auto& definition : classes_) {
        for (const auto& entry : definition.entries) {
            if (!entry.spawn_class.empty() && find(entry.spawn_class) == nullptr) {
                throw SpawnClassError("Spawn class references an absent nested class");
            }
        }
    }
}

const SpawnClassDefinition* SpawnClassCatalog::find(std::u16string_view name) const noexcept {
    const auto found = by_name_.find(normalized_name(name));
    return found == by_name_.end() ? nullptr : &classes_[found->second];
}

std::vector<SpawnLeaf> SpawnClassCatalog::roll(std::u16string_view name,
                                               TorchlightRandom& random) const {
    const auto* definition = find(name);
    if (definition == nullptr) {
        throw SpawnClassError("Requested spawn class is absent");
    }
    std::vector<std::u16string> active_classes;
    std::vector<SpawnLeaf> result;
    roll_class(*definition, random, active_classes, result);
    return result;
}

void SpawnClassCatalog::roll_class(const SpawnClassDefinition& definition,
                                   TorchlightRandom& random,
                                   std::vector<std::u16string>& active_classes,
                                   std::vector<SpawnLeaf>& output) const {
    const auto normalized = normalized_name(definition.name);
    if (std::find(active_classes.begin(), active_classes.end(), normalized) !=
        active_classes.end()) {
        throw SpawnClassError("Cycle in nested spawn classes");
    }
    if (definition.entries.empty()) {
        return;
    }
    active_classes.push_back(normalized);
    try {
        const auto expand = [&](const SpawnClassEntry& selected) {
            // Both forced and weighted branches clamp repetitions to at least one
            // (0xa752bf / 0xa7578d), even when authored count endpoints are zero.
            const auto count = std::max(1, random.integer_between(selected.minimum_count,
                                                      selected.maximum_count));
            for (std::int32_t index = 0; index < count; ++index) {
                if (output.size() >= kMaximumSpawnLeaves) {
                    throw SpawnClassError("Spawn class expanded beyond the safety limit");
                }
                if (!selected.unit.empty()) {
                    output.push_back({SpawnLeafKind::unit, selected.unit});
                } else if (!selected.unit_type.empty()) {
                    if (normalized_name(selected.unit_type) != u"NONE") {
                        output.push_back({SpawnLeafKind::unit_type, selected.unit_type});
                    }
                } else {
                    roll_class(*find(selected.spawn_class), random, active_classes, output);
                }
            }
        };

        std::vector<float> weights;
        std::vector<std::size_t> weighted_entries;
        for (std::size_t index = 0; index < definition.entries.size(); ++index) {
            const auto& entry = definition.entries[index];
            if (entry.weight == -1) {
                expand(entry);
            } else if (entry.weight > 0) {
                weights.push_back(static_cast<float>(entry.weight));
                weighted_entries.push_back(index);
            }
        }
        if (!weighted_entries.empty()) {
            expand(definition.entries[weighted_entries[weighted_index(weights, random)]]);
        }
        active_classes.pop_back();
    } catch (...) {
        active_classes.pop_back();
        throw;
    }
}

} // namespace torchlight
