#pragma once

#include "torchlight/adm_document.hpp"

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace torchlight {

[[nodiscard]] std::string compiled_adm_path(std::u16string_view data_file);

enum class MasterResourceKind {
    item,
    monster,
    player,
    prop,
};

struct MasterResourceRecord {
    MasterResourceKind kind = MasterResourceKind::item;
    std::int64_t guid = 0;
    std::u16string unit_type;
    std::u16string create_as;
    std::u16string file_item;
    std::u16string data_file;
    std::u16string base_file;
    std::u16string name;
    std::u16string display_name;
    bool do_not_create = false;
    std::uint32_t resource_group = 0;

    // Converts the ASCII DATFILE used by Torchlight into the compiled path
    // stored in pak.zip. Separators are normalized but letter case is kept.
    [[nodiscard]] std::string compiled_adm_path() const;
};

class MasterResourceIndex {
public:
    explicit MasterResourceIndex(const AdmDocument& document);

    [[nodiscard]] const std::vector<MasterResourceRecord>& records() const noexcept {
        return records_;
    }
    [[nodiscard]] const MasterResourceRecord* find(std::int64_t guid) const noexcept;
    [[nodiscard]] const MasterResourceRecord* find(MasterResourceKind kind,
                                                   std::u16string_view name) const noexcept;
    [[nodiscard]] const MasterResourceRecord* find_case_insensitive(
        MasterResourceKind kind, std::u16string_view name) const noexcept;
    [[nodiscard]] const MasterResourceRecord* find_any(
        std::u16string_view name) const noexcept;
    [[nodiscard]] std::size_t count(MasterResourceKind kind) const noexcept;

private:
    std::vector<MasterResourceRecord> records_;
    std::unordered_map<std::int64_t, std::size_t> by_guid_;
};

} // namespace torchlight
