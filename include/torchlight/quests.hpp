#pragma once
#include "torchlight/logic_runtime.hpp"
#include <functional>
#include <string>
#include <unordered_map>
namespace torchlight {
struct QuestFlags { std::u16string name; bool active=false, complete=false, accept_dialog=false; };
struct QuestCheckpoint { std::vector<QuestFlags> flags; std::uint32_t completed_count=0; };
void validate_quest_checkpoint(const QuestCheckpoint&);
struct QuestRequirements {
    bool present=false;
    std::int32_t minimum_level=-1, maximum_level=-1, minimum_depth=-1, maximum_depth=-1;
    std::u16string ruleset;
    std::vector<std::u16string> complete, not_complete, active;
};
struct QuestDefinition {
    std::u16string name, display_name, dungeon;
    std::int64_t guid=0;
    bool controller_completes=false, force_accept=false;
    QuestRequirements requirements;
    std::vector<std::u16string> on_complete;
    AdmGroup resource;
    std::string source_path, unavailable_reason;
    [[nodiscard]] bool flag_only() const noexcept { return unavailable_reason.empty(); }
};
// The caller supplies the ORIGINAL player's maximum visited depth, not current
// floor; lookup receives max(0,max_depth+1). Unknown templates fail closed.
struct QuestRequirementContext {
    bool player_present=true, manager_present=true;
    std::uint32_t player_level=1;
    std::function<std::optional<std::int32_t>(std::u16string_view)> maximum_depth;
    std::function<std::optional<std::u16string>(std::u16string_view,std::int32_t)> template_name;
};
[[nodiscard]] bool quest_requirements_met(const QuestDefinition&, const QuestCheckpoint&, const QuestRequirementContext&);
class QuestCatalog {
public:
    explicit QuestCatalog(const PakArchive&);
    [[nodiscard]] const QuestDefinition* find(std::u16string_view) const;
    [[nodiscard]] const std::vector<QuestDefinition>& definitions() const noexcept { return definitions_; }
    void validate(const QuestCheckpoint&) const;
private:
    std::vector<QuestDefinition> definitions_;
    std::unordered_map<std::u16string,std::size_t> by_name_;
};
// Restricted original flag-only controllers. Never fabricates objectives,
// rewards, pet assignment or population. Every unknown side effect blocks the
// entire command and records a diagnostic; no partial reward/flag commit.
// Bind before activate_level, initialize only on a newly generated floor.
class QuestControllerRuntime {
public:
    QuestControllerRuntime(const QuestCatalog&, QuestCheckpoint&, const LayoutManifest&, LogicRuntime&);
    ~QuestControllerRuntime();
    QuestControllerRuntime(const QuestControllerRuntime&)=delete;
    QuestControllerRuntime& operator=(const QuestControllerRuntime&)=delete;
    void initialize();
    [[nodiscard]] const std::vector<std::string>& diagnostics() const noexcept { return diagnostics_; }
private:
    bool input(const LayoutObject&, std::u16string_view);
    void broadcast(std::u16string_view name,std::u16string_view event);
    void broadcast_from(std::u16string name, std::u16string event, std::size_t index);
    void accept(const QuestDefinition&,bool dialog);
    void complete(const QuestDefinition&);
    void complete_after_accept(const QuestDefinition&);
    void complete_successors(const QuestDefinition&, std::size_t index);
    [[nodiscard]] QuestFlags& flags(std::u16string_view);
    const QuestCatalog* catalog_; QuestCheckpoint* state_; const LayoutManifest* layout_; LogicRuntime* logic_;
    std::vector<std::string> diagnostics_;
};
} // namespace torchlight
