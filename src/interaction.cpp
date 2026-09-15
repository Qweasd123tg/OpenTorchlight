#include "torchlight/interaction.hpp"
#include <atomic>
#include <cmath>
#include <limits>
#include <stdexcept>
namespace torchlight {
namespace {
std::atomic<std::uint64_t> generations{1};
bool point(const std::array<float, 3> &p) {
    for (const auto v : p)
        if (!std::isfinite(v))
            return false;
    return true;
}
float distance(const std::array<float, 3> &a, const std::array<float, 3> &b) {
    return std::hypot(a[0] - b[0], a[2] - b[2]);
}
} // namespace
InteractionDispatcher::InteractionDispatcher(const LayoutManifest &l, RuntimeEntityWorld &w,
                                             LogicRuntime &r)
    : layout_(&l), world_(&w), logic_(&r), transforms_(resolve_layout_world_transforms(l)),
      generation_(generations.fetch_add(1)) {
    if (!generation_)
        throw std::overflow_error("interaction generation exhausted");
}
std::optional<InteractionRequest> InteractionDispatcher::select(const std::array<float, 3> &p,
                                                                float radius) {
    cancel();
    if (!point(p) || !std::isfinite(radius) || radius < 0)
        return std::nullopt;
    if (next_sequence_ == std::numeric_limits<std::uint64_t>::max())
        throw std::overflow_error("interaction sequence exhausted");
    std::optional<InteractionRequest> result;
    for (std::size_t i = 0; i < layout_->objects.size(); ++i) {
        const auto &o = layout_->objects[i];
        const auto *state = logic_->state(o.id);
        if (o.descriptor != u"Unit Trigger" || !state || !state->enabled || !state->visible)
            continue;
        const auto d = distance(p, transforms_[i].position);
        if (d > radius)
            continue;
        radius = d;
        result = InteractionRequest{generation_,
                                    next_sequence_,
                                    0,
                                    o.id,
                                    InteractionKind::unit_trigger,
                                    transforms_[i].position,
                                    o.name.empty() ? o.descriptor : o.name};
    }
    for (const auto &e : world_->entities()) {
        // This is a service INSPECTION capability, not a newly inferred faction.
        if (e.kind != MasterResourceKind::monster || e.combat_targetable || !e.alive ||
            !e.enabled || !e.visible)
            continue;
        const auto d = distance(p, e.position);
        if (d >= radius)
            continue;
        radius = d;
        result = InteractionRequest{generation_,
                                    next_sequence_,
                                    e.id,
                                    0,
                                    InteractionKind::character,
                                    e.position,
                                    e.display_name.empty() ? e.name : e.display_name};
    }
    if (result) {
        active_sequence_ = next_sequence_++;
        active_ = result;
    }
    return result;
}
std::optional<InteractionRequest>
InteractionDispatcher::resolve(const InteractionRequest &request) const {
    if (request.generation != generation_ || request.sequence == 0 ||
        request.sequence != active_sequence_)
        return std::nullopt;
    if (!active_ || active_->kind != request.kind || active_->object_id != request.object_id ||
        active_->entity_id != request.entity_id)
        return std::nullopt;
    auto current = request;
    if (request.kind == InteractionKind::character) {
        const auto *e = world_->find(request.entity_id);
        if (!e || e->kind != MasterResourceKind::monster || e->combat_targetable || !e->alive ||
            !e->enabled || !e->visible)
            return std::nullopt;
        current.position = e->position;
        return current;
    }
    for (std::size_t i = 0; i < layout_->objects.size(); ++i)
        if (layout_->objects[i].id == request.object_id &&
            layout_->objects[i].descriptor == u"Unit Trigger") {
            const auto *state = logic_->state(request.object_id);
            if (!state || !state->enabled || !state->visible)
                return std::nullopt;
            current.position = transforms_[i].position;
            return current;
        }
    return std::nullopt;
}
InteractionResult InteractionDispatcher::dispatch(const InteractionRequest &request,
                                                  const std::array<float, 3> &player, bool alive,
                                                  float radius) {
    if (request.generation != generation_ || request.sequence != active_sequence_ ||
        request.sequence == 0)
        return InteractionResult::stale;
    if (!alive) {
        cancel();
        return InteractionResult::player_dead;
    }
    const auto current = resolve(request);
    if (!current) {
        cancel();
        return InteractionResult::unavailable;
    }
    if (!point(player) || !std::isfinite(radius) || radius < 0 ||
        distance(current->position, player) > radius)
        return InteractionResult::approaching;
    cancel(); // before synchronous callbacks; recursive delivery cannot repeat it
    if (current->kind == InteractionKind::character)
        return InteractionResult::unsupported_service;
    logic_->trigger(current->object_id);
    return InteractionResult::triggered;
}
const char *interaction_result_message(InteractionResult r) noexcept {
    switch (r) {
    case InteractionResult::stale:
        return "INTERACTION CANCELLED";
    case InteractionResult::unavailable:
        return "OBJECT NO LONGER AVAILABLE";
    case InteractionResult::approaching:
        return "APPROACHING OBJECT";
    case InteractionResult::triggered:
        return "INTERACTION ACTIVATED";
    case InteractionResult::unsupported_service:
        return "NPC SELECTED. DIALOG / MERCHANT / STASH SERVICE NOT IMPLEMENTED.";
    case InteractionResult::player_dead:
        return "CANNOT INTERACT WHILE DEAD";
    }
    return "UNKNOWN INTERACTION";
}
} // namespace torchlight
