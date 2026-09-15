#include "torchlight/unit_type.hpp"

#include "torchlight/adm_document.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace torchlight {
namespace {

class UnitTypeError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

std::u16string normalized_name(std::u16string_view value) {
    std::u16string result;
    result.reserve(value.size());
    for (const auto character : value) {
        result.push_back(character >= u'a' && character <= u'z'
                             ? static_cast<char16_t>(character - u'a' + u'A')
                             : character);
    }
    return result;
}

std::int32_t required_integer(const AdmGroup& group, const char16_t* name) {
    const auto* property = group.find_property(name);
    if (property == nullptr || property->type != AdmValueType::integer) {
        throw UnitTypeError("Unit type is missing an integer ID");
    }
    return std::get<std::int32_t>(property->value);
}

std::int32_t optional_integer(const UnitDefinition& definition,
                              const char16_t* name,
                              std::int32_t fallback) {
    const auto* property = definition.find_property(name);
    if (property == nullptr) {
        return fallback;
    }
    if (property->type != AdmValueType::integer) {
        throw UnitTypeError("UNIT selection property has the wrong type");
    }
    return std::get<std::int32_t>(property->value);
}

bool is_text(AdmValueType type) noexcept {
    return type == AdmValueType::string || type == AdmValueType::translation ||
           type == AdmValueType::note;
}

std::u16string optional_text(const UnitDefinition& definition,
                             const char16_t* name) {
    const auto* property = definition.find_property(name);
    if (property == nullptr) {
        return {};
    }
    if (!is_text(property->type)) {
        throw UnitTypeError("UNIT selection text property has the wrong type");
    }
    return std::get<std::u16string>(property->value);
}

const AdmGroup* find_child(const AdmGroup& parent, std::u16string_view name) {
    const auto found = std::find_if(parent.groups.begin(), parent.groups.end(),
                                    [name](const auto& group) {
                                        return group.name == name;
                                    });
    return found == parent.groups.end() ? nullptr : &*found;
}

bool starts_with_child(std::u16string_view name) noexcept {
    constexpr std::u16string_view prefix = u"CHILD";
    return name.size() >= prefix.size() &&
           name.compare(0, prefix.size(), prefix) == 0;
}

} // namespace

UnitTypeHierarchy::UnitTypeHierarchy(const PakArchive& archive) {
    const auto document = parse_adm(archive.read_normalized("media/UNITTYPES.HIE.adm"));
    if (document.root.name != u"HIERACHY") {
        throw UnitTypeError("Unit-type document root is not HIERACHY");
    }
    const auto* groups = find_child(document.root, u"UNITTYPES");
    if (groups == nullptr) {
        throw UnitTypeError("Unit-type document has no UNITTYPES group");
    }

    types_.reserve(groups->groups.size());
    by_name_.reserve(groups->groups.size());
    by_id_.reserve(groups->groups.size());
    for (const auto& group : groups->groups) {
        UnitTypeDefinition definition;
        definition.name = group.name;
        definition.id = required_integer(group, u"ID");
        for (const auto& property : group.properties) {
            if (!starts_with_child(property.name)) {
                continue;
            }
            if (property.type != AdmValueType::integer) {
                throw UnitTypeError("Unit-type CHILD property is not an integer");
            }
            const auto ancestor = std::get<std::int32_t>(property.value);
            if (std::find(definition.ancestors.begin(), definition.ancestors.end(),
                          ancestor) == definition.ancestors.end()) {
                definition.ancestors.push_back(ancestor);
            }
        }
        const auto index = types_.size();
        if (!by_name_.emplace(normalized_name(definition.name), index).second) {
            throw UnitTypeError("Duplicate unit-type name");
        }
        if (!by_id_.emplace(definition.id, index).second) {
            throw UnitTypeError("Duplicate unit-type ID");
        }
        types_.push_back(std::move(definition));
    }

    for (const auto& definition : types_) {
        for (const auto ancestor : definition.ancestors) {
            if (by_id_.find(ancestor) == by_id_.end()) {
                throw UnitTypeError("Unit type references an absent ancestor ID");
            }
        }
    }
}

const UnitTypeDefinition* UnitTypeHierarchy::find(
    std::u16string_view name) const noexcept {
    const auto found = by_name_.find(normalized_name(name));
    return found == by_name_.end() ? nullptr : &types_[found->second];
}

bool UnitTypeHierarchy::is_a(std::u16string_view candidate,
                             std::u16string_view requested) const noexcept {
    const auto* candidate_type = find(candidate);
    const auto* requested_type = find(requested);
    if (candidate_type == nullptr || requested_type == nullptr) {
        return false;
    }
    return candidate_type->id == requested_type->id ||
           std::find(candidate_type->ancestors.begin(), candidate_type->ancestors.end(),
                     requested_type->id) != candidate_type->ancestors.end();
}

bool UnitTypeHierarchy::is_a_id(std::u16string_view candidate,
                                std::int32_t original_type_id) const noexcept {
    const auto requested = by_id_.find(original_type_id);
    return requested != by_id_.end() && is_a(candidate, types_[requested->second].name);
}

UnitTypeResourceIndex::UnitTypeResourceIndex(
    const PakArchive& archive, const UnitTypeHierarchy& hierarchy,
    const MasterResourceIndex& resources,
    UnitDefinitionLoader& definitions)
    : hierarchy_(&hierarchy),
      item_range_minimum_(
          archive, "media/graphs/stats/ITEM_SPAWN_RANGE_MINIMUM.DAT.adm"),
      item_range_maximum_(
          archive, "media/graphs/stats/ITEM_SPAWN_RANGE_MAXIMUM.DAT.adm") {
    candidates_.reserve(resources.records().size());
    for (const auto& resource : resources.records()) {
        if (resource.do_not_create) {
            continue;
        }
        if (hierarchy.find(resource.unit_type) == nullptr) {
            throw UnitTypeError("Master resource has an unknown UNITTYPE");
        }
        const auto definition = definitions.load(resource);
        UnitTypeCandidate candidate;
        candidate.resource = &resource;
        candidate.rarity = optional_integer(*definition, u"RARITY", 1);
        candidate.item_level = optional_integer(*definition, u"LEVEL", 1);
        candidate.minimum_level = optional_integer(*definition, u"MINLEVEL", 0);
        candidate.equipment = normalized_name(optional_text(*definition, u"CREATEAS")) ==
                              u"EQUIPMENT";
        candidate.maximum_level = optional_integer(
            *definition, u"MAXLEVEL", candidate.equipment ? 0 : 99999);
        if (candidate.maximum_level != 0 &&
            candidate.minimum_level > candidate.maximum_level) {
            std::swap(candidate.minimum_level, candidate.maximum_level);
        }
        if (candidate.rarity > 0) {
            candidates_.push_back(candidate);
        }
    }
}

bool UnitTypeResourceIndex::accepts_level(const UnitTypeCandidate& candidate,
                                          std::int32_t level) const noexcept {
    if (candidate.equipment && candidate.maximum_level == 0) {
        const auto minimum = static_cast<std::int32_t>(std::floor(
            item_range_minimum_.value(static_cast<float>(candidate.item_level))));
        const auto maximum = static_cast<std::int32_t>(std::ceil(
            item_range_maximum_.value(static_cast<float>(candidate.item_level))));
        return level >= minimum && level <= maximum;
    }
    return level >= candidate.minimum_level && level <= candidate.maximum_level;
}

std::vector<const UnitTypeCandidate*> UnitTypeResourceIndex::candidates(
    std::u16string_view type, std::int32_t level) const {
    std::vector<const UnitTypeCandidate*> result;
    if (hierarchy_->find(type) == nullptr) {
        return result;
    }
    const auto effective_level = std::max<std::int32_t>(1, level);
    for (const auto& candidate : candidates_) {
        if (accepts_level(candidate, effective_level) &&
            hierarchy_->is_a(candidate.resource->unit_type, type)) {
            result.push_back(&candidate);
        }
    }
    return result;
}

const MasterResourceRecord* UnitTypeResourceIndex::roll(
    std::u16string_view type, std::int32_t level,
    TorchlightRandom& random) const {
    const auto choices = candidates(type, level);
    if (choices.empty()) {
        return nullptr;
    }
    std::vector<float> weights;
    weights.reserve(choices.size());
    for (const auto* choice : choices) {
        weights.push_back(static_cast<float>(choice->rarity));
    }
    return choices[weighted_index(weights, random)]->resource;
}

} // namespace torchlight
