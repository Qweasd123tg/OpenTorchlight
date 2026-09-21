#include "torchlight/ui_tooltip.hpp"

#include "torchlight/ui_skin.hpp"
#include "torchlight/ui_text.hpp"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <limits>
#include <map>
#include <new>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace torchlight {
namespace {

bool truth(const std::string& value) {
    std::string upper = value;
    std::transform(upper.begin(), upper.end(), upper.begin(), [](unsigned char c) {
        return static_cast<char>(std::toupper(c));
    });
    return upper == "TRUE";
}

std::string relative_area(float x, float y, float width, float height,
                          int viewport_width, int viewport_height) {
    if (viewport_width <= 0 || viewport_height <= 0)
        throw std::invalid_argument("invalid tooltip viewport");
    const float vw = static_cast<float>(viewport_width);
    const float vh = static_cast<float>(viewport_height);
    std::ostringstream out;
    out << std::setprecision(9) << "{{" << x / vw << ",0},{" << y / vh
        << ",0},{" << (x + width) / vw << ",0},{" << (y + height) / vh << ",0}}";
    return out.str();
}

UiWidget tooltip_widget(std::string name, std::string type) {
    UiWidget widget;
    widget.name = std::move(name);
    widget.type = std::move(type);
    widget.properties["UnifiedAreaRect"] = "{{0,0},{0,0},{0,0},{0,0}}";
    widget.properties["AlwaysOnTop"] = "True";
    widget.properties["DestroyedByParent"] = "False";
    widget.properties["ClippedByParent"] = "False";
    widget.properties["MousePassThroughEnabled"] = "True";
    widget.properties["Visible"] = "False";
    widget.properties["Alpha"] = "0";
    // CGameUI installs Serif as System's default font before constructing the
    // default tooltip. The portable resolver has no System font object.
    widget.properties["Font"] = "Serif";
    return widget;
}

} // namespace

struct UiTooltips::Impl {
    struct State {
        explicit State(UiWindowId window) : id(window) {}
        UiWindowId id = 0;
        UiTooltipPhase phase = UiTooltipPhase::inactive;
        float timer = 0.0F;
        float hover = 0.4F;
        float display = 7.5F;
        float fade = 0.33F;
        std::optional<UiWindowId> target;
        std::string text;
    };
    struct Owned {
        std::string type;
        std::optional<UiWindowId> tooltip;
    };

    UiWindowRuntime* windows;
    UiResources* resources;
    UiWindowId default_id;
    std::map<UiWindowId, State> states;
    std::map<UiWindowId, Owned> owned;
    std::optional<UiWindowId> current;
    bool stopped = false;

    Impl(UiWindowRuntime& runtime, UiResources& ui_resources)
        : windows(&runtime), resources(&ui_resources),
          default_id(runtime.create(tooltip_widget("__OpenTorchlightDefaultTooltip",
                                                   "GuiLook/Tooltip"))) {
        try {
            auto state = State{default_id};
            state.hover = 0.0F;
            state.display = 0.0F;
            states.emplace(default_id, std::move(state));
            runtime.activate(default_id);
            if (!runtime.alive(default_id))
                throw std::runtime_error("default tooltip destroyed during initialisation");
        } catch (...) {
            // Port safety: the original external manager may retain a failed
            // factory object.  This owner cannot expose a live window without
            // its State entry when Impl construction itself did not complete.
            states.erase(default_id);
            if (runtime.alive(default_id)) runtime.destroy(default_id);
            throw;
        }
    }

    std::string inherited_property(UiWindowId id, const char* property,
                                   bool require_inherit_flag) const {
        std::set<UiWindowId> visited;
        while (windows->alive(id) && visited.insert(id).second) {
            const auto& widget = windows->window(id);
            const auto value = widget.property(property);
            if (!value.empty()) return value;
            if (require_inherit_flag && !truth(widget.property("InheritsTooltipText"))) return {};
            if (widget.parent < 0) return {};
            id = static_cast<UiWindowId>(widget.parent);
        }
        return {};
    }

    std::string tooltip_text(UiWindowId id) const {
        return inherited_property(id, "Tooltip", true);
    }

    std::optional<UiWindowId> custom_for(UiWindowId owner) {
        const auto type = windows->window(owner).property("CustomTooltipType");
        auto existing = owned.find(owner);
        if (type.empty()) {
            if (existing != owned.end()) destroy_owned(existing);
            return std::nullopt;
        }
        if (existing != owned.end() && existing->second.type == type)
            return existing->second.tooltip;
        if (existing != owned.end()) destroy_owned(existing);

        std::optional<UiWindowId> created;
        const auto rollback = [&] {
            if (!created) return;
            states.erase(*created);
            if (windows->alive(*created)) windows->destroy(*created);
            created.reset();
        };
        try {
            const auto name = windows->window(owner).name + "__auto_tooltip__";
            const auto id = windows->create(tooltip_widget(name, type));
            created = id;
            states.emplace(id, State{id});
            windows->activate(id);
            if (!windows->alive(id))
                throw std::runtime_error("custom tooltip destroyed during initialisation");
            const auto inserted = owned.emplace(owner, Owned{type, id}).first;
            return inserted->second.tooltip;
        } catch (const std::bad_alloc&) {
            rollback();
            throw;
        } catch (const std::exception&) {
            // Window::setTooltipType catches CEGUI exceptions, clears the
            // owned pointer and leaves the window using the System default.
            // The portable registry rollback also prevents an owned ID from
            // surviving without the State required by the update FSM.
            rollback();
        }
        const auto inserted = owned.emplace(owner, Owned{type, std::nullopt}).first;
        return inserted->second.tooltip;
    }

    void destroy_owned(std::map<UiWindowId, Owned>::iterator entry) {
        if (entry->second.tooltip) {
            const auto id = *entry->second.tooltip;
            if (current == id) current.reset();
            states.erase(id);
            if (windows->alive(id)) windows->destroy(id);
        }
        owned.erase(entry);
    }

    UiWindowId effective(UiWindowId target) {
        return custom_for(target).value_or(default_id);
    }

    void attach(State& state) {
        const auto sheet = windows->sheet();
        if (!sheet || !windows->alive(*sheet)) return;
        const auto parent = windows->window(state.id).parent;
        if (parent == static_cast<std::int32_t>(*sheet)) return;
        windows->add_child(*sheet, state.id);
    }

    void detach(State& state) {
        const auto parent = windows->window(state.id).parent;
        if (parent >= 0 && windows->alive(static_cast<UiWindowId>(parent)))
            windows->remove_child(static_cast<UiWindowId>(parent), state.id);
    }

    std::pair<float, float> cursor_size(UiWindowId target, int width, int height) {
        const auto reference = inherited_property(target, "MouseCursorImage", false);
        const auto image = resources->image(reference);
        if (!image) return {0.0F, 0.0F};
        const auto metrics = image->scaled_metrics(width, height);
        return {metrics[0], metrics[1]};
    }

    void size_and_position(State& state, const UiWindowSnapshot& context, float x, float y) {
        if (!state.target || !windows->alive(*state.target)) return;
        auto* font = resources->font("Serif");
        float text_width = 0.0F;
        float text_height = 0.0F;
        if (font && font->valid() && !state.text.empty()) {
            font->notify_screen_size(static_cast<float>(context.width),
                                     static_cast<float>(context.height));
            const auto lines = ui_text_lines(state.text,
                static_cast<float>(std::numeric_limits<int>::max()), false,
                [&](char32_t c) { return font->advance(c); },
                ui_font_uses_inline_colours("Serif"));
            for (const auto& line : lines) text_width = std::max(text_width, line.width);
            text_height = static_cast<float>(lines.size()) * font->line_height();
            text_width = ui_pixel_aligned(text_width);
            text_height = ui_pixel_aligned(text_height);
        }
        const auto [cursor_width, cursor_height] = cursor_size(
            *state.target, context.width, context.height);
        const float px = x + cursor_width;
        const float py = y + cursor_height;

        // TextArea margins are independent of the provisional pixel size for
        // GuiLook/Tooltip. Resolve a real widget so Falagard's NamedArea
        // evaluator consumes the resource expressions and image dimensions.
        windows->set_property(state.id, "UnifiedAreaRect", relative_area(
            px, py, text_width, text_height, context.width, context.height));
        auto resolved = windows->snapshot(context.width, context.height, context.layout_state);
        float width = text_width;
        float height = text_height;
        if (state.id < resolved.resolved_index_by_id.size()) {
            const auto index = resolved.resolved_index_by_id[state.id];
            if (index) {
                const auto& widget = resolved.widgets[*index];
                if (const auto area = resources->skin().named_area(
                        *resources, widget, "TextArea", context.width, context.height)) {
                    width += widget.rect.width - area->width;
                    height += widget.rect.height - area->height;
                }
            }
        }
        width = std::max(0.0F, width);
        height = std::max(0.0F, height);
        windows->set_property(state.id, "UnifiedAreaRect", relative_area(
            px, py, width, height, context.width, context.height));
    }

    void set_target(State& state, std::optional<UiWindowId> target,
                    const UiWindowSnapshot& context, float x, float y) {
        if (state.target == target) return;
        if (state.phase == UiTooltipPhase::inactive || state.phase == UiTooltipPhase::active)
            state.timer = 0.0F;
        if (target) {
            attach(state);
            state.text = tooltip_text(*target);
            windows->set_property(state.id, "Text", state.text);
            // Original assigns d_target last, after copy/size/position.
            const auto prior = state.target;
            state.target = target;
            try {
                size_and_position(state, context, x, y);
            } catch (...) {
                state.target = prior;
                throw;
            }
        } else {
            state.target.reset();
        }
    }

    void alpha(State& state, float value) {
        windows->set_property(state.id, "Alpha", std::to_string(std::clamp(value, 0.0F, 1.0F)));
    }

    void enter_inactive(State& state) {
        alpha(state, 0.0F);
        state.phase = UiTooltipPhase::inactive;
        state.timer = 0.0F;
        detach(state);
        state.target.reset();
        windows->set_visible(state.id, false);
    }

    void enter_fade_in(State& state, const UiWindowSnapshot& context, float x, float y) {
        size_and_position(state, context, x, y);
        state.phase = UiTooltipPhase::fade_in;
        state.timer = 0.0F;
        windows->set_visible(state.id, true);
    }

    void update_one(State& state, float dt, const UiWindowSnapshot& context, float x, float y) {
        const bool valid = state.target && windows->alive(*state.target) && !state.text.empty();
        switch (state.phase) {
        case UiTooltipPhase::inactive:
            if (valid) {
                state.timer += dt;
                if (state.timer >= state.hover) enter_fade_in(state, context, x, y);
            }
            break;
        case UiTooltipPhase::fade_in:
            if (!valid) enter_inactive(state);
            else {
                state.timer += dt;
                if (state.fade <= 0.0F || state.timer >= state.fade) {
                    alpha(state, 1.0F);
                    state.phase = UiTooltipPhase::active;
                    state.timer = 0.0F;
                } else alpha(state, state.timer / state.fade);
            }
            break;
        case UiTooltipPhase::active:
            if (!valid) enter_inactive(state);
            else if (state.display > 0.0F) {
                state.timer += dt;
                if (state.timer >= state.display) {
                    state.phase = UiTooltipPhase::fade_out;
                    state.timer = 0.0F;
                }
            }
            break;
        case UiTooltipPhase::fade_out:
            if (!valid) enter_inactive(state);
            else {
                state.timer += dt;
                if (state.fade <= 0.0F || state.timer >= state.fade) enter_inactive(state);
                else alpha(state, 1.0F - state.timer / state.fade);
            }
            break;
        }
    }
};

UiTooltips::UiTooltips(UiWindowRuntime& windows, UiResources& resources)
    : impl_(std::make_unique<Impl>(windows, resources)) {}

UiTooltips::~UiTooltips() { shutdown(); }

UiWindowId UiTooltips::default_tooltip() const noexcept { return impl_->default_id; }

std::optional<UiWindowId> UiTooltips::current_tooltip() const noexcept { return impl_->current; }

std::optional<UiWindowId> UiTooltips::target(UiWindowId tooltip) const {
    const auto found = impl_->states.find(tooltip);
    if (found == impl_->states.end()) throw std::out_of_range("unknown tooltip window");
    return found->second.target;
}

UiTooltipPhase UiTooltips::phase(UiWindowId tooltip) const {
    const auto found = impl_->states.find(tooltip);
    if (found == impl_->states.end()) throw std::out_of_range("unknown tooltip window");
    return found->second.phase;
}

void UiTooltips::enter(UiWindowId target, const UiWindowSnapshot& snapshot, float x, float y) {
    if (impl_->stopped || !impl_->windows->alive(target)) return;
    const auto tooltip = impl_->effective(target);
    if (impl_->current && *impl_->current != tooltip) {
        auto old = impl_->states.find(*impl_->current);
        if (old != impl_->states.end())
            impl_->set_target(old->second, std::nullopt, snapshot, x, y);
    }
    impl_->current = tooltip;
    impl_->set_target(impl_->states.at(tooltip), target, snapshot, x, y);
}

void UiTooltips::move(float, float) {
    if (!impl_->current) return;
    auto found = impl_->states.find(*impl_->current);
    if (found != impl_->states.end() &&
        (found->second.phase == UiTooltipPhase::inactive ||
         found->second.phase == UiTooltipPhase::active))
        found->second.timer = 0.0F;
}

void UiTooltips::leave() {
    if (!impl_->current) return;
    auto found = impl_->states.find(*impl_->current);
    if (found != impl_->states.end()) {
        if (found->second.phase == UiTooltipPhase::inactive ||
            found->second.phase == UiTooltipPhase::active)
            found->second.timer = 0.0F;
        found->second.target.reset();
    }
    impl_->current.reset();
}

void UiTooltips::down() { leave(); }

void UiTooltips::advance(float dt, const UiWindowSnapshot& snapshot, float x, float y) {
    if (impl_->stopped) return;
    if (!std::isfinite(dt) || dt < 0.0F) throw std::invalid_argument("invalid tooltip delta");
    for (auto& [id, state] : impl_->states)
        if (impl_->windows->alive(id)) impl_->update_one(state, dt, snapshot, x, y);
}

void UiTooltips::reset_target(UiWindowId id) {
    for (auto& [tooltip, state] : impl_->states)
        if (state.target == id) {
            if (state.phase == UiTooltipPhase::inactive || state.phase == UiTooltipPhase::active)
                state.timer = 0.0F;
            state.target.reset();
        }
    if (impl_->current) {
        const auto found = impl_->states.find(*impl_->current);
        if (found == impl_->states.end() || !found->second.target) impl_->current.reset();
    }
}

void UiTooltips::release_owned(UiWindowId id) {
    const auto found = impl_->owned.find(id);
    if (found != impl_->owned.end()) impl_->destroy_owned(found);
}

void UiTooltips::shutdown() {
    if (!impl_ || impl_->stopped) return;
    impl_->stopped = true;
    while (!impl_->owned.empty()) impl_->destroy_owned(impl_->owned.begin());
    impl_->states.erase(impl_->default_id);
    if (impl_->windows->alive(impl_->default_id)) impl_->windows->destroy(impl_->default_id);
    impl_->current.reset();
}

} // namespace torchlight
