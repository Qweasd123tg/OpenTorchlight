#pragma once

#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/randomizer.hpp"
#include "torchlight/stat_graph.hpp"
#include "torchlight/unit_definition.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace torchlight {

struct UnitTypeDefinition {
    std::u16string name;
    std::int32_t id = 0;
    std::vector<std::int32_t> ancestors;
};

class UnitTypeHierarchy {
public:
    explicit UnitTypeHierarchy(const PakArchive& archive);

    [[nodiscard]] const UnitTypeDefinition* find(
        std::u16string_view name) const noexcept;
    [[nodiscard]] bool is_a(std::u16string_view candidate,
                            std::u16string_view requested) const noexcept;
    [[nodiscard]] bool is_a_id(std::u16string_view candidate,
                               std::int32_t original_type_id) const noexcept;
    [[nodiscard]] const std::vector<UnitTypeDefinition>& types() const noexcept {
        return types_;
    }

private:
    std::vector<UnitTypeDefinition> types_;
    std::unordered_map<std::u16string, std::size_t> by_name_;
    std::unordered_map<std::int32_t, std::size_t> by_id_;
};

struct UnitTypeCandidate {
    const MasterResourceRecord* resource = nullptr;
    std::int32_t rarity = 1;
    std::int32_t item_level = 1;
    std::int32_t minimum_level = 0;
    std::int32_t maximum_level = 0;
    bool equipment = false;
};

class UnitTypeResourceIndex {
public:
    UnitTypeResourceIndex(const PakArchive& archive,
                          const UnitTypeHierarchy& hierarchy,
                          const MasterResourceIndex& resources,
                          UnitDefinitionLoader& definitions);

    [[nodiscard]] std::vector<const UnitTypeCandidate*> candidates(
        std::u16string_view type, std::int32_t level) const;
    [[nodiscard]] const MasterResourceRecord* roll(
        std::u16string_view type, std::int32_t level,
        TorchlightRandom& random) const;
    [[nodiscard]] bool is_a_id(std::u16string_view candidate,
                               std::int32_t original_type_id) const noexcept {
        return hierarchy_->is_a_id(candidate, original_type_id);
    }
    [[nodiscard]] std::size_t indexed_resource_count() const noexcept {
        return candidates_.size();
    }

private:
    [[nodiscard]] bool accepts_level(const UnitTypeCandidate& candidate,
                                     std::int32_t level) const noexcept;

    const UnitTypeHierarchy* hierarchy_ = nullptr;
    StatGraph item_range_minimum_;
    StatGraph item_range_maximum_;
    std::vector<UnitTypeCandidate> candidates_;
};

} // namespace torchlight
