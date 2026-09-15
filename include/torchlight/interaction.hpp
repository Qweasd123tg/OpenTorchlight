#pragma once
#include "torchlight/entity_world.hpp"
namespace torchlight {
enum class InteractionKind { unit_trigger, character };
struct InteractionRequest {
    std::uint64_t generation = 0, sequence = 0, entity_id = 0;
    std::int64_t object_id = 0;
    InteractionKind kind = InteractionKind::unit_trigger;
    std::array<float, 3> position{};
    std::u16string label;
};
enum class InteractionResult {
    stale,
    unavailable,
    approaching,
    triggered,
    unsupported_service,
    player_dead
};
// Selection/arrival plumbing only. Original quest/key/service requirements and
// interaction radii are separate unimplemented boundaries; see research note.
class InteractionDispatcher {
  public:
    InteractionDispatcher(const LayoutManifest &, RuntimeEntityWorld &, LogicRuntime &);
    [[nodiscard]] std::optional<InteractionRequest> select(const std::array<float, 3> &,
                                                           float pick_radius);
    [[nodiscard]] std::optional<InteractionRequest> resolve(const InteractionRequest &) const;
    [[nodiscard]] InteractionResult dispatch(const InteractionRequest &,
                                             const std::array<float, 3> &player, bool alive,
                                             float action_radius);
    void cancel() noexcept {
        active_sequence_ = 0;
        active_.reset();
    }

  private:
    const LayoutManifest *layout_;
    RuntimeEntityWorld *world_;
    LogicRuntime *logic_;
    std::vector<LayoutWorldTransform> transforms_;
    std::uint64_t generation_ = 0, next_sequence_ = 1, active_sequence_ = 0;
    std::optional<InteractionRequest> active_;
};
[[nodiscard]] const char *interaction_result_message(InteractionResult) noexcept;
} // namespace torchlight
