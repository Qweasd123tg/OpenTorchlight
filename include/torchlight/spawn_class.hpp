#pragma once

#include "torchlight/adm_document.hpp"
#include "torchlight/pak_archive.hpp"
#include "torchlight/randomizer.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace torchlight {

enum class SpawnLeafKind {
    unit,
    unit_type,
};

struct SpawnClassEntry {
    std::u16string unit;
    std::u16string unit_type;
    std::u16string spawn_class;
    std::int32_t weight = -1;
    std::int32_t minimum_count = 1;
    std::int32_t maximum_count = 1;
    std::vector<AdmProperty> properties;
};

struct SpawnClassDefinition {
    std::u16string name;
    std::string source_path;
    std::vector<SpawnClassEntry> entries;
};

struct SpawnLeaf {
    SpawnLeafKind kind = SpawnLeafKind::unit;
    std::u16string value;
};

class SpawnClassCatalog {
public:
    explicit SpawnClassCatalog(const PakArchive& archive);

    [[nodiscard]] const SpawnClassDefinition* find(std::u16string_view name) const noexcept;
    [[nodiscard]] std::vector<SpawnLeaf> roll(std::u16string_view name,
                                              TorchlightRandom& random) const;
    [[nodiscard]] const std::vector<SpawnClassDefinition>& classes() const noexcept {
        return classes_;
    }
    [[nodiscard]] std::size_t entry_count() const noexcept { return entry_count_; }

private:
    void roll_class(const SpawnClassDefinition& definition, TorchlightRandom& random,
                    std::vector<std::u16string>& active_classes,
                    std::vector<SpawnLeaf>& output) const;

    std::vector<SpawnClassDefinition> classes_;
    std::unordered_map<std::u16string, std::size_t> by_name_;
    std::size_t entry_count_ = 0;
};

} // namespace torchlight
