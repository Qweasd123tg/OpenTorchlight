#pragma once

#include "torchlight/adm_document.hpp"
#include "torchlight/master_resource_index.hpp"
#include "torchlight/pak_archive.hpp"

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace torchlight {

struct UnitDefinition {
    AdmGroup root;
    // Requested file first, followed by each BASEFILE in inheritance order.
    std::vector<std::string> inheritance_chain;

    [[nodiscard]] const AdmProperty* find_property(const std::u16string& name) const noexcept {
        return root.find_property(name);
    }
};

class UnitDefinitionLoader {
public:
    explicit UnitDefinitionLoader(const PakArchive& archive) : archive_(archive) {}

    [[nodiscard]] std::shared_ptr<const UnitDefinition> load(const MasterResourceRecord& record);
    [[nodiscard]] std::shared_ptr<const UnitDefinition> load(std::u16string_view data_file);
    [[nodiscard]] std::size_t cached_definition_count() const noexcept { return cache_.size(); }

private:
    [[nodiscard]] std::shared_ptr<const UnitDefinition>
    load_compiled(std::string path, std::unordered_set<std::string>& active_paths);

    const PakArchive& archive_;
    std::unordered_map<std::string, std::shared_ptr<const UnitDefinition>> cache_;
};

} // namespace torchlight
