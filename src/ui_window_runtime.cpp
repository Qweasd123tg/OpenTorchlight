#include "torchlight/ui_window_runtime.hpp"
#include "torchlight/ui_pointer_timing.hpp"

#include <algorithm>
#include <charconv>
#include <cctype>
#include <limits>
#include <stdexcept>
#include <utility>

namespace torchlight {
namespace {

std::string upper(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
        return static_cast<char>(std::toupper(c));
    });
    return value;
}

bool property_true(const UiWidget& widget, const char* name) {
    return upper(widget.property(name)) == "TRUE";
}

bool property_false(const UiWidget& widget, const char* name) {
    return upper(widget.property(name)) == "FALSE";
}

bool has_type_suffix(const std::string& value, const char* suffix) {
    const std::string tail(suffix);
    return value == tail || (value.size() > tail.size() &&
        value.compare(value.size() - tail.size(), tail.size(), tail) == 0 &&
        value[value.size() - tail.size() - 1] == '/');
}

bool thumb_type(const std::string& type) {
    const auto value = upper(type);
    return has_type_suffix(value, "THUMB") || has_type_suffix(value, "SLIDERTHUMB");
}

enum class ButtonClass { none, push, checkbox, radio, thumb };

ButtonClass button_class(const std::string& type) {
    const auto value = upper(type);
    if (thumb_type(type)) return ButtonClass::thumb;
    if (has_type_suffix(value, "CHECKBOX")) return ButtonClass::checkbox;
    if (has_type_suffix(value, "RADIOTAB") || has_type_suffix(value, "RADIOBUTTON"))
        return ButtonClass::radio;
    if (has_type_suffix(value, "STANDARDBUTTON") || has_type_suffix(value, "PUSHBUTTON") ||
        has_type_suffix(value, "IMAGEBUTTON"))
        return ButtonClass::push;
    return ButtonClass::none;
}

} // namespace

struct UiWindowRuntime::Impl {
    struct Node {
        UiWidget widget;
        std::vector<UiWindowId> children;
        std::vector<UiWindowId> draw_list;
        std::optional<UiWindowId> previous_capture;
        bool allocated = true;
        bool registered = true;
        bool destroying = false;
        bool local_visible = true;
        bool local_enabled = true;
        bool local_active = false;
        bool zero_position = false;
        bool restore_capture = false;
        bool distribute_capture = false;
        bool button = false;
        ButtonClass button_class = ButtonClass::none;
        bool thumb = false;
        bool pushed = false;
        bool hovering = false;
        bool selected = false;
        std::size_t radio_group = 0;
        float thumb_drag_offset = 0;
        UiAutoRepeatTiming repeat;
    };

    std::vector<Node> nodes;
    std::vector<UiWindowId> dead_pool;
    std::optional<UiWindowId> sheet;
    std::optional<UiWindowId> mouse_target;
    std::optional<UiWindowId> modal;
    std::optional<UiWindowId> capture;
    EventListener listener;
    UiWindowLifecycle lifecycle;
    std::size_t revision = 0;

    Node& node(UiWindowId id) {
        if (id >= nodes.size() || !nodes[id].allocated)
            throw std::out_of_range("unknown UI window ID");
        return nodes[id];
    }
    const Node& node(UiWindowId id) const {
        if (id >= nodes.size() || !nodes[id].allocated)
            throw std::out_of_range("unknown UI window ID");
        return nodes[id];
    }
    bool exists(UiWindowId id) const noexcept {
        return id < nodes.size() && nodes[id].allocated;
    }
    bool alive(UiWindowId id) const noexcept {
        return exists(id) && nodes[id].registered;
    }
    std::optional<UiWindowId> parent(UiWindowId id) const {
        if (!exists(id) || nodes[id].widget.parent < 0) return std::nullopt;
        const auto value = static_cast<UiWindowId>(nodes[id].widget.parent);
        return exists(value) ? std::optional<UiWindowId>(value) : std::nullopt;
    }
    bool descendant_or_self(UiWindowId child, UiWindowId ancestor) const {
        for (std::size_t guard = 0; exists(child) && guard <= nodes.size(); ++guard) {
            if (child == ancestor) return true;
            const auto p = parent(child);
            if (!p) return false;
            child = *p;
        }
        return false;
    }
    bool effectively_visible(UiWindowId id) const {
        for (std::size_t guard = 0; exists(id) && guard <= nodes.size(); ++guard) {
            if (!nodes[id].local_visible) return false;
            const auto p = parent(id);
            if (!p) return true;
            id = *p;
        }
        return false;
    }
    bool effectively_enabled(UiWindowId id) const {
        for (std::size_t guard = 0; exists(id) && guard <= nodes.size(); ++guard) {
            if (!nodes[id].local_enabled) return false;
            const auto p = parent(id);
            if (!p) return true;
            id = *p;
        }
        return false;
    }
    bool is_active(UiWindowId id) const {
        for (std::size_t guard = 0; exists(id) && guard <= nodes.size(); ++guard) {
            if (!nodes[id].local_active) return false;
            const auto p = parent(id);
            if (!p) return true;
            id = *p;
        }
        return false;
    }
    void changed() noexcept { ++revision; }
    void emit(UiWindowEventType type, UiWindowId window,
              std::optional<UiWindowId> related = std::nullopt) {
        changed();
        auto callback = listener;
        if (callback) callback({type, window, related});
    }
    bool always_on_top(UiWindowId id) const {
        return property_true(node(id).widget, "AlwaysOnTop");
    }
    bool z_ordering(UiWindowId id) const {
        return !property_false(node(id).widget, "ZOrderingEnabled");
    }
    bool rise_on_click(UiWindowId id) const {
        return !property_false(node(id).widget, "RiseOnClick");
    }
    bool destroyed_by_parent(UiWindowId id) const {
        return !property_false(node(id).widget, "DestroyedByParent");
    }
    void insert_draw(UiWindowId parent_id, UiWindowId child, bool at_back) {
        auto& draw = node(parent_id).draw_list;
        const bool top = always_on_top(child);
        if (at_back) {
            const auto where = top
                ? std::find_if(draw.begin(), draw.end(), [&](UiWindowId id) {
                      return always_on_top(id);
                  })
                : draw.begin();
            draw.insert(where, child);
        } else {
            const auto where = top
                ? draw.end()
                : std::find_if(draw.begin(), draw.end(), [&](UiWindowId id) {
                      return always_on_top(id);
                  });
            draw.insert(where, child);
        }
    }
    void remove_edge(UiWindowId parent_id, UiWindowId child, bool events) {
        auto& p = node(parent_id);
        p.draw_list.erase(std::remove(p.draw_list.begin(), p.draw_list.end(), child),
                          p.draw_list.end());
        const auto found = std::find(p.children.begin(), p.children.end(), child);
        if (found != p.children.end()) {
            p.children.erase(found);
            if (exists(child) && nodes[child].widget.parent == static_cast<std::int32_t>(parent_id))
                nodes[child].widget.parent = -1;
        }
        changed();
        if (events) {
            emit(UiWindowEventType::child_removed, parent_id, child);
            if (exists(child)) emit(UiWindowEventType::z_changed, child, parent_id);
        }
    }
    void on_deactivated(UiWindowId id, std::optional<UiWindowId> other) {
        if (!exists(id)) return;
        const auto descendants = nodes[id].children;
        for (const auto child : descendants)
            if (exists(child) && is_active(child)) on_deactivated(child, other);
        if (!exists(id)) return;
        nodes[id].local_active = false;
        emit(UiWindowEventType::deactivated, id, other);
    }
    void on_activated(UiWindowId id) {
        if (!exists(id)) return;
        nodes[id].local_active = true;
        emit(UiWindowEventType::activated, id);
    }
    bool move_front_impl(UiWindowId id, bool was_clicked) {
        if (!alive(id)) return false;
        const auto p = parent(id);
        bool handled = p ? move_front_impl(*p, was_clicked) : false;
        if (!alive(id)) return handled;
        std::optional<UiWindowId> old_active;
        if (const auto current_parent = parent(id)) {
            const auto siblings = nodes[*current_parent].children;
            for (const auto sibling : siblings)
                if (sibling != id && alive(sibling) && nodes[sibling].local_active) {
                    old_active = sibling;
                    break;
                }
        }
        if (!nodes[id].local_active) { on_activated(id); handled = true; }
        if (old_active && alive(*old_active)) on_deactivated(*old_active, id);
        if (!alive(id)) return handled;
        const auto current_parent = parent(id);
        if (!current_parent || !z_ordering(id) || (was_clicked && !rise_on_click(id))) return handled;
        auto& draw = nodes[*current_parent].draw_list;
        const auto top = std::find_if(draw.rbegin(), draw.rend(), [&](UiWindowId sibling) {
            return always_on_top(sibling) == always_on_top(id);
        });
        // isTopOfZOrder @0x112400 suppresses redundant Z-change events.
        if (top != draw.rend() && *top == id) return handled;
        draw.erase(std::remove(draw.begin(), draw.end(), id), draw.end());
        insert_draw(*current_parent, id, false);
        emit(UiWindowEventType::z_changed, id, *current_parent);
        return true;
    }
    void on_capture_lost(UiWindowId id, std::optional<UiWindowId> related) {
        if (!exists(id)) return;
        nodes[id].repeat.capture_lost();
        const auto prior = nodes[id].restore_capture ? nodes[id].previous_capture : std::nullopt;
        if (prior && exists(*prior)) on_capture_lost(*prior, related);
        if (!exists(id)) return;
        nodes[id].previous_capture.reset();
        // Window::onCaptureLost injects a zero-delta mouse move before firing
        // EventInputCaptureLost. The frontend consumes this event by resolving
        // a fresh target/snapshot and dispatching the real hover update.
        emit(UiWindowEventType::mouse_retarget_requested, id, related);
        if (!exists(id)) return;
        emit(UiWindowEventType::capture_lost, id, related);
        // ButtonBase::onCaptureLost invokes the Window base implementation
        // (and therefore EventInputCaptureLost) before clearing its own flags.
        if (!exists(id)) return;
        if (nodes[id].pushed || nodes[id].hovering) {
            nodes[id].pushed = false;
            nodes[id].hovering = false;
            changed();
        }
        // ButtonBase continues after the Window event and recomputes hover at
        // the cursor's retained position. Reuse the frontend's real retarget
        // consumer after the flags are cleared instead of guessing a cursor.
        if (nodes[id].button)
            emit(UiWindowEventType::mouse_retarget_requested, id, related);
    }
    bool capture_input(UiWindowId id) {
        if (!alive(id) || !is_active(id)) return false;
        if (capture == id) return true;
        const auto old = capture;
        capture = id;
        changed();
        if (nodes[id].restore_capture) {
            nodes[id].previous_capture = old;
        } else if (old && exists(*old)) {
            on_capture_lost(*old, id);
        }
        if (alive(id)) emit(UiWindowEventType::capture_gained, id, old);
        return alive(id) && capture == id;
    }
    void release_input(UiWindowId id) {
        if (!exists(id) || capture != id) return;
        std::optional<UiWindowId> restored;
        if (nodes[id].restore_capture) restored = nodes[id].previous_capture;
        capture = restored && alive(*restored) ? restored : std::nullopt;
        if (nodes[id].restore_capture) nodes[id].previous_capture.reset();
        changed();
        if (capture && alive(*capture)) move_front_impl(*capture, false);
        on_capture_lost(id, id);
    }
    void destroy(UiWindowId id) {
        if (!alive(id) || nodes[id].destroying) return;
        nodes[id].registered = false;
        nodes[id].destroying = true;
        changed();
        release_input(id);
        if (lifecycle.reset_tooltip_target) lifecycle.reset_tooltip_target(id);
        if (lifecycle.release_tooltip) lifecycle.release_tooltip(id);
        // Window::destroy @0x114840: detach and destroy the renderer before
        // EventDestructionStarted and before removing parent/child edges.
        if (lifecycle.detach_renderer) lifecycle.detach_renderer(id, nodes[id].widget);
        if (lifecycle.destroy_renderer) lifecycle.destroy_renderer(id, nodes[id].widget);
        if (exists(id)) emit(UiWindowEventType::destruction_started, id);
        if (!exists(id)) return;
        if (const auto p = parent(id); p && exists(*p)) remove_edge(*p, id, true);
        while (exists(id) && !nodes[id].children.empty()) {
            const auto child = nodes[id].children.front();
            const bool owned = exists(child) && destroyed_by_parent(child);
            remove_edge(id, child, true);
            if (owned) destroy(child);
        }
        if (!exists(id)) return;
        dead_pool.push_back(id);
        if (mouse_target == id) mouse_target.reset();
        if (sheet == id) sheet.reset();
        if (modal == id) modal.reset();
        changed();
    }

    UiWindowSnapshot resolve_ids(const std::vector<UiWindowId>& roots, int width, int height,
                                 const UiLayoutState& state) const {
        UiWindowSnapshot result;
        result.width = width;
        result.height = height;
        result.layout_state = state;
        result.resolved_index_by_id.resize(nodes.size());
        if (width <= 0 || height <= 0) throw std::invalid_argument("invalid UI viewport");
        struct Pending { UiWindowId id; std::int32_t parent; };
        std::vector<Pending> pending;
        for (auto it = roots.rbegin(); it != roots.rend(); ++it)
            if (alive(*it)) pending.push_back({*it, -1});
        std::vector<UiWidget> widgets;
        while (!pending.empty()) {
            const auto entry = pending.back();
            pending.pop_back();
            if (!alive(entry.id)) continue;
            auto widget = nodes[entry.id].widget;
            widget.parent = entry.parent;
            const auto resolved_parent = static_cast<std::int32_t>(widgets.size());
            result.resolved_index_by_id[entry.id] = widgets.size();
            result.source_ids.push_back(entry.id);
            widgets.push_back(std::move(widget));
            const auto& children = nodes[entry.id].children;
            for (auto it = children.rbegin(); it != children.rend(); ++it)
                if (alive(*it)) pending.push_back({*it, resolved_parent});
        }
        if (!widgets.empty()) {
            auto resolved_state = state;
            for (std::size_t i = 0; i < result.source_ids.size(); ++i)
                if (nodes[result.source_ids[i]].zero_position)
                    resolved_state.zero_position_nodes.push_back(i);
            result.layout_state = resolved_state;
            result.widgets = UiLayout::from_widgets(std::move(widgets)).resolve(
                width, height, resolved_state);
            for (std::size_t i = 0; i < result.widgets.size(); ++i) {
                result.widgets[i].visible = result.widgets[i].visible &&
                    effectively_visible(result.source_ids[i]);
                result.widgets[i].enabled = result.widgets[i].enabled &&
                    effectively_enabled(result.source_ids[i]);
            }
            std::vector<UiWindowId> paint(roots.rbegin(), roots.rend());
            std::size_t order = 0;
            while (!paint.empty()) {
                const auto id = paint.back(); paint.pop_back();
                if (!alive(id) || id >= result.resolved_index_by_id.size() ||
                    !result.resolved_index_by_id[id]) continue;
                result.widgets[*result.resolved_index_by_id[id]].paint_order = order++;
                const auto& draw = nodes[id].draw_list;
                paint.insert(paint.end(), draw.rbegin(), draw.rend());
            }
        }
        return result;
    }
    UiWindowSnapshot resolve_focus(UiWindowId focus, const UiWindowSnapshot& basis) const {
        std::vector<UiWindowId> lineage;
        auto cursor = focus;
        while (alive(cursor)) {
            lineage.push_back(cursor);
            const auto p = parent(cursor);
            if (!p) break;
            cursor = *p;
        }
        std::reverse(lineage.begin(), lineage.end());
        UiWindowSnapshot result;
        result.width = basis.width;
        result.height = basis.height;
        result.layout_state = basis.layout_state;
        result.resolved_index_by_id.resize(nodes.size());
        std::vector<UiWidget> widgets;
        for (std::size_t i = 0; i < lineage.size(); ++i) {
            auto widget = nodes[lineage[i]].widget;
            widget.parent = i == 0 ? -1 : static_cast<std::int32_t>(i - 1);
            result.resolved_index_by_id[lineage[i]] = widgets.size();
            result.source_ids.push_back(lineage[i]);
            widgets.push_back(std::move(widget));
        }
        if (!lineage.empty()) {
            struct Pending { UiWindowId id; std::int32_t parent; };
            std::vector<Pending> pending;
            const auto& children = nodes[focus].children;
            for (auto it = children.rbegin(); it != children.rend(); ++it)
                if (alive(*it)) pending.push_back({*it, static_cast<std::int32_t>(lineage.size() - 1)});
            while (!pending.empty()) {
                const auto entry = pending.back(); pending.pop_back();
                auto widget = nodes[entry.id].widget;
                widget.parent = entry.parent;
                const auto new_parent = static_cast<std::int32_t>(widgets.size());
                result.resolved_index_by_id[entry.id] = widgets.size();
                result.source_ids.push_back(entry.id);
                widgets.push_back(std::move(widget));
                const auto& children = nodes[entry.id].children;
                for (auto it = children.rbegin(); it != children.rend(); ++it)
                    if (alive(*it)) pending.push_back({*it, new_parent});
            }
        }
        if (!widgets.empty()) {
            auto resolved_state = basis.layout_state;
            resolved_state.zero_position_nodes.clear();
            for (std::size_t i = 0; i < result.source_ids.size(); ++i) {
                const auto id = result.source_ids[i];
                bool zero = nodes[id].zero_position;
                if (id < basis.resolved_index_by_id.size() && basis.resolved_index_by_id[id])
                    zero = zero || std::find(basis.layout_state.zero_position_nodes.begin(),
                        basis.layout_state.zero_position_nodes.end(),
                        *basis.resolved_index_by_id[id]) !=
                        basis.layout_state.zero_position_nodes.end();
                if (zero) resolved_state.zero_position_nodes.push_back(i);
            }
            result.layout_state = resolved_state;
            result.widgets = UiLayout::from_widgets(std::move(widgets)).resolve(
                basis.width, basis.height, resolved_state);
            for (std::size_t i = 0; i < result.widgets.size(); ++i) {
                result.widgets[i].visible = result.widgets[i].visible &&
                    effectively_visible(result.source_ids[i]);
                result.widgets[i].enabled = result.widgets[i].enabled &&
                    effectively_enabled(result.source_ids[i]);
            }
            std::size_t order = 0;
            for (const auto id : lineage)
                if (id < result.resolved_index_by_id.size() && result.resolved_index_by_id[id])
                    result.widgets[*result.resolved_index_by_id[id]].paint_order = order++;
            std::vector<UiWindowId> paint;
            const auto& draw = nodes[focus].draw_list;
            paint.insert(paint.end(), draw.rbegin(), draw.rend());
            while (!paint.empty()) {
                const auto id = paint.back(); paint.pop_back();
                if (!alive(id) || id >= result.resolved_index_by_id.size() ||
                    !result.resolved_index_by_id[id]) continue;
                result.widgets[*result.resolved_index_by_id[id]].paint_order = order++;
                const auto& child_draw = nodes[id].draw_list;
                paint.insert(paint.end(), child_draw.rbegin(), child_draw.rend());
            }
        }
        return result;
    }
    bool is_hit(const UiWindowSnapshot& basis, UiWindowId id, float x, float y) const {
        // Window::isHit rejects disabled windows even for their own capture;
        // visibility is intentionally not part of this predicate.
        if (!effectively_enabled(id)) return false;
        UiWindowSnapshot local;
        const UiWindowSnapshot* frame = &basis;
        if (id >= basis.resolved_index_by_id.size() || !basis.resolved_index_by_id[id]) {
            local = resolve_focus(id, basis);
            frame = &local;
        }
        if (id >= frame->resolved_index_by_id.size() || !frame->resolved_index_by_id[id]) return false;
        const auto& widget = frame->widgets[*frame->resolved_index_by_id[id]];
        return widget.rect.contains(x, y) && (!widget.has_clip || widget.clip.contains(x, y));
    }
    void update_button_hover(UiWindowId id, const UiWindowSnapshot& frame, float x, float y) {
        if (!alive(id) || !nodes[id].button) return;
        bool hover = false;
        if (capture == id) hover = is_hit(frame, id, x, y);
        else if (!capture) hover = mouse_target == id && is_hit(frame, id, x, y);
        if (nodes[id].hovering != hover) {
            nodes[id].hovering = hover;
            changed();
        }
    }
    void set_selected(UiWindowId id, bool value) {
        if (!exists(id)) return;
        auto& target = nodes[id];
        if ((target.button_class != ButtonClass::checkbox &&
             target.button_class != ButtonClass::radio) || target.selected == value) return;
        target.selected = value;
        if (target.button_class == ButtonClass::radio && value) {
            const auto p = parent(id);
            const auto siblings = p ? nodes[*p].children : std::vector<UiWindowId>{};
            const auto type = target.widget.type;
            const auto group = target.radio_group;
            for (const auto sibling : siblings) {
                if (!exists(sibling) || sibling == id) continue;
                const auto& candidate = nodes[sibling];
                if (candidate.button_class == ButtonClass::radio && candidate.selected &&
                    candidate.widget.type == type && candidate.radio_group == group)
                    set_selected(sibling, false);
            }
        }
        if (exists(id)) emit(UiWindowEventType::selection_changed, id);
    }
};

UiWindowRuntime::UiWindowRuntime() : impl_(std::make_unique<Impl>()) {}
UiWindowRuntime::~UiWindowRuntime() = default;
UiWindowRuntime::UiWindowRuntime(UiWindowRuntime&&) noexcept = default;
UiWindowRuntime& UiWindowRuntime::operator=(UiWindowRuntime&&) noexcept = default;

UiWindowId UiWindowRuntime::create(UiWidget widget, std::optional<UiLayoutFunction> binding) {
    if (widget.name.empty()) throw std::invalid_argument("window without name");
    if (find(widget.name)) throw std::invalid_argument("duplicate UI window name");
    if (impl_->nodes.size() > static_cast<std::size_t>(std::numeric_limits<std::int32_t>::max()))
        throw std::overflow_error("UI window ID exceeds UiWidget parent range");
    widget.parent = -1;
    if (binding) widget.layout_function = binding;
    Impl::Node node;
    node.local_visible = !property_false(widget, "Visible");
    node.local_enabled = !property_false(widget, "Enabled") && !property_true(widget, "Disabled");
    node.restore_capture = property_true(widget, "RestoreOldCapture");
    node.distribute_capture = property_true(widget, "DistributeCapturedInputs");
    node.button_class = button_class(widget.type);
    node.button = node.button_class != ButtonClass::none;
    node.thumb = thumb_type(widget.type);
    node.selected = property_true(widget, "Selected");
    node.repeat.set_enabled(property_true(widget, "MouseAutoRepeatEnabled"));
    if (const auto value = widget.property("AutoRepeatDelay"); !value.empty()) node.repeat.set_delay(std::stof(value));
    if (const auto value = widget.property("AutoRepeatRate"); !value.empty()) node.repeat.set_rate(std::stof(value));
    if (node.button_class == ButtonClass::radio) {
        const auto raw = widget.property("GroupID");
        if (!raw.empty()) {
            const auto parsed = std::from_chars(raw.data(), raw.data() + raw.size(),
                                                node.radio_group);
            if (parsed.ec != std::errc{} || parsed.ptr != raw.data() + raw.size())
                throw std::invalid_argument("invalid RadioButton GroupID");
        }
    }
    node.widget = std::move(widget);
    impl_->nodes.push_back(std::move(node));
    const auto id = impl_->nodes.size() - 1;
    if (impl_->lifecycle.initialize) {
        // Factory renderer/look initialisation precedes name registration.
        impl_->nodes[id].registered = false;
        const auto properties = impl_->nodes[id].widget;
        impl_->lifecycle.initialize(id, properties);
        impl_->nodes[id].registered = true;
    }
    impl_->changed();
    return id;
}

std::vector<UiWindowId> UiWindowRuntime::create(const UiLayout& layout) {
    std::vector<UiWindowId> ids;
    ids.reserve(layout.widgets().size());
    for (const auto& source : layout.widgets()) ids.push_back(create(source));
    for (std::size_t i = 0; i < layout.widgets().size(); ++i)
        if (layout.widgets()[i].parent >= 0)
            add_child(ids.at(static_cast<std::size_t>(layout.widgets()[i].parent)), ids[i]);
    return ids;
}

void UiWindowRuntime::add_child(UiWindowId parent, UiWindowId child) {
    if (!impl_->alive(parent) || !impl_->alive(child))
        throw std::out_of_range("add_child uses dead UI window");
    if (parent == child || impl_->descendant_or_self(parent, child))
        throw std::invalid_argument("cyclic UI window parent");
    if (const auto old = impl_->parent(child)) impl_->remove_edge(*old, child, true);
    if (!impl_->alive(parent) || !impl_->alive(child)) return;
    impl_->insert_draw(parent, child, false);
    impl_->nodes[parent].children.push_back(child);
    impl_->nodes[child].widget.parent = static_cast<std::int32_t>(parent);
    impl_->changed();
    impl_->emit(UiWindowEventType::parent_sized, child, parent);
    if (!impl_->alive(parent) || !impl_->alive(child)) return;
    impl_->emit(UiWindowEventType::child_added, parent, child);
    if (impl_->alive(child)) impl_->emit(UiWindowEventType::z_changed, child, parent);
}

void UiWindowRuntime::remove_child(UiWindowId parent, UiWindowId child) {
    impl_->node(parent);
    impl_->node(child);
    impl_->remove_edge(parent, child, true);
}

void UiWindowRuntime::destroy(UiWindowId id) { impl_->destroy(id); }

void UiWindowRuntime::clean_dead_pool() {
    for (auto it = impl_->dead_pool.rbegin(); it != impl_->dead_pool.rend(); ++it) {
        const auto id = *it;
        if (!impl_->exists(id)) continue;
        if (impl_->lifecycle.destroy_factory_object)
            impl_->lifecycle.destroy_factory_object(id, impl_->nodes[id].widget);
        for (auto& candidate : impl_->nodes)
            if (candidate.allocated && candidate.previous_capture == id)
                candidate.previous_capture.reset();
        impl_->nodes[id].children.clear();
        impl_->nodes[id].draw_list.clear();
        impl_->nodes[id].widget = {};
        impl_->nodes[id].allocated = false;
        impl_->nodes[id].destroying = false;
        impl_->changed();
    }
    impl_->dead_pool.clear();
}

bool UiWindowRuntime::alive(UiWindowId id) const noexcept { return impl_->alive(id); }
const UiWidget& UiWindowRuntime::window(UiWindowId id) const { return impl_->node(id).widget; }
const std::vector<UiWindowId>& UiWindowRuntime::children(UiWindowId id) const {
    return impl_->node(id).children;
}
std::optional<UiWindowId> UiWindowRuntime::find(std::string_view name) const {
    for (UiWindowId id = 0; id < impl_->nodes.size(); ++id)
        if (impl_->alive(id) && impl_->nodes[id].widget.name == name) return id;
    return std::nullopt;
}

void UiWindowRuntime::set_sheet(std::optional<UiWindowId> id) {
    if (id && !impl_->alive(*id)) throw std::out_of_range("dead UI sheet");
    if (impl_->sheet != id) { impl_->sheet = id; impl_->changed(); }
}
void UiWindowRuntime::set_mouse_target(std::optional<UiWindowId> id) {
    if (id && !impl_->alive(*id)) throw std::out_of_range("dead mouse target");
    if (impl_->mouse_target != id) { impl_->mouse_target = id; impl_->changed(); }
}
void UiWindowRuntime::set_modal(UiWindowId id, bool value) {
    if (!impl_->alive(id)) throw std::out_of_range("dead modal window");
    if ((impl_->modal == id) == value) return;
    if (value) { activate(id); impl_->modal = id; impl_->changed(); }
    else if (impl_->modal == id) { impl_->modal.reset(); impl_->changed(); }
}
bool UiWindowRuntime::capture_input(UiWindowId id) { return impl_->capture_input(id); }
void UiWindowRuntime::release_input(UiWindowId id) { impl_->release_input(id); }
void UiWindowRuntime::set_restore_capture(UiWindowId id, bool value) {
    if (!impl_->alive(id)) throw std::out_of_range("dead UI window");
    std::vector<UiWindowId> pending{id};
    while (!pending.empty()) {
        const auto current = pending.back(); pending.pop_back();
        if (!impl_->alive(current)) continue;
        impl_->nodes[current].restore_capture = value;
        const auto& children = impl_->nodes[current].children;
        pending.insert(pending.end(), children.rbegin(), children.rend());
        impl_->changed();
    }
}
void UiWindowRuntime::set_distributes_captured_inputs(UiWindowId id, bool value) {
    auto& node = impl_->node(id);
    if (!node.registered) throw std::out_of_range("dead UI window");
    if (node.distribute_capture != value) { node.distribute_capture = value; impl_->changed(); }
}

void UiWindowRuntime::activate(UiWindowId id) {
    if (!impl_->alive(id)) throw std::out_of_range("dead UI window");
    if (!impl_->effectively_visible(id)) return;
    if (impl_->capture && *impl_->capture != id) {
        const auto old = impl_->capture;
        impl_->capture.reset();
        impl_->changed();
        if (old && impl_->exists(*old)) impl_->on_capture_lost(*old, std::nullopt);
    }
    impl_->move_front_impl(id, false);
}
void UiWindowRuntime::deactivate(UiWindowId id) {
    if (!impl_->alive(id)) throw std::out_of_range("dead UI window");
    impl_->on_deactivated(id, std::nullopt);
}
void UiWindowRuntime::set_visible(UiWindowId id, bool value) {
    auto& node = impl_->node(id);
    if (!node.registered) throw std::out_of_range("dead UI window");
    if (node.local_visible == value) return;
    node.local_visible = value;
    node.widget.properties["Visible"] = value ? "True" : "False";
    impl_->changed();
    if (!value && impl_->is_active(id)) impl_->on_deactivated(id, std::nullopt);
    if (impl_->alive(id)) impl_->emit(value ? UiWindowEventType::shown : UiWindowEventType::hidden, id);
}
void UiWindowRuntime::set_enabled(UiWindowId id, bool value) {
    auto& node = impl_->node(id);
    if (!node.registered) throw std::out_of_range("dead UI window");
    if (node.local_enabled == value) return;
    node.local_enabled = value;
    node.widget.properties["Enabled"] = value ? "True" : "False";
    node.widget.properties.erase("Disabled");
    impl_->changed();
    const auto type = value ? UiWindowEventType::enabled : UiWindowEventType::disabled;
    std::vector<UiWindowId> pending{id};
    while (!pending.empty()) {
        const auto current = pending.back(); pending.pop_back();
        if (!impl_->alive(current)) continue;
        impl_->emit(type, current, id == current ? std::nullopt : std::optional<UiWindowId>(id));
        const auto& children = impl_->nodes[current].children;
        for (auto it = children.rbegin(); it != children.rend(); ++it)
            if (impl_->alive(*it) && impl_->nodes[*it].local_enabled) pending.push_back(*it);
    }
}
void UiWindowRuntime::set_zero_position(UiWindowId id, bool value) {
    auto& node = impl_->node(id);
    if (!node.registered) throw std::out_of_range("dead UI window");
    if (node.zero_position != value) { node.zero_position = value; impl_->changed(); }
}
void UiWindowRuntime::move_to_front(UiWindowId id) {
    if (!impl_->alive(id)) throw std::out_of_range("dead UI window");
    impl_->move_front_impl(id, false);
}
void UiWindowRuntime::move_to_back(UiWindowId id) {
    if (!impl_->alive(id)) throw std::out_of_range("dead UI window");
    if (impl_->is_active(id)) impl_->on_deactivated(id, std::nullopt);
    if (!impl_->alive(id)) return;
    const auto p = impl_->parent(id);
    if (p && impl_->z_ordering(id)) {
        auto& draw = impl_->nodes[*p].draw_list;
        draw.erase(std::remove(draw.begin(), draw.end(), id), draw.end());
        impl_->insert_draw(*p, id, true);
        impl_->emit(UiWindowEventType::z_changed, id, *p);
    }
    if (p && impl_->alive(*p)) move_to_back(*p);
}
void UiWindowRuntime::set_property(UiWindowId id, std::string key, std::string value) {
    auto& node = impl_->node(id);
    if (!node.registered) throw std::out_of_range("dead UI window");
    if (key == "Visible") { set_visible(id, upper(value) != "FALSE"); return; }
    if (key == "Enabled") { set_enabled(id, upper(value) != "FALSE"); return; }
    if (key == "Disabled") { set_enabled(id, upper(value) != "TRUE"); return; }
    if (key == "MouseAutoRepeatEnabled") node.repeat.set_enabled(upper(value) == "TRUE");
    else if (key == "AutoRepeatDelay") node.repeat.set_delay(std::stof(value));
    else if (key == "AutoRepeatRate") node.repeat.set_rate(std::stof(value));
    if (key == "Selected" && (node.button_class == ButtonClass::checkbox || node.button_class == ButtonClass::radio))
        set_button_selected(id, upper(value) == "TRUE");
    else if (key == "ModalState") set_modal(id, upper(value) == "TRUE");
    else if (key == "RestoreOldCapture") set_restore_capture(id, upper(value) == "TRUE");
    else if (key == "DistributeCapturedInputs") set_distributes_captured_inputs(id, upper(value) == "TRUE");
    // Callbacks above may append to the registry. Reacquire the node below.
    auto& properties = impl_->node(id).widget.properties;
    const auto old = properties.find(key);
    if (old != properties.end() && old->second == value) return;
    properties[std::move(key)] = std::move(value);
    impl_->changed();
}

std::optional<UiWindowId> UiWindowRuntime::sheet() const noexcept { return impl_->sheet; }
std::optional<UiWindowId> UiWindowRuntime::mouse_target() const noexcept { return impl_->mouse_target; }
std::optional<UiWindowId> UiWindowRuntime::modal() const noexcept { return impl_->modal; }
std::optional<UiWindowId> UiWindowRuntime::capture() const noexcept { return impl_->capture; }
bool UiWindowRuntime::is_active(UiWindowId id) const { impl_->node(id); return impl_->is_active(id); }
std::size_t UiWindowRuntime::revision() const noexcept { return impl_->revision; }

UiWindowSnapshot UiWindowRuntime::snapshot(int width, int height, const UiLayoutState& state) const {
    std::vector<UiWindowId> roots;
    if (impl_->sheet && impl_->alive(*impl_->sheet)) roots.push_back(*impl_->sheet);
    auto result = impl_->resolve_ids(roots, width, height, state);
    if (impl_->sheet && *impl_->sheet < result.resolved_index_by_id.size())
        result.sheet = result.resolved_index_by_id[*impl_->sheet];
    return result;
}

std::optional<UiWindowId> UiWindowRuntime::target_at_position(
    const UiWindowSnapshot& frame, float x, float y) const {
    if (!impl_->sheet || !impl_->alive(*impl_->sheet) || !frame.sheet ||
        *frame.sheet >= frame.widgets.size() || !frame.widgets[*frame.sheet].visible)
        return std::nullopt;
    std::optional<UiWindowId> target;
    if (impl_->capture && impl_->alive(*impl_->capture)) {
        target = impl_->capture;
        if (impl_->nodes[*impl_->capture].distribute_capture) {
            const auto local = impl_->resolve_focus(*impl_->capture, frame);
            const auto hit = ui_target_at_position(local.widgets, x, y);
            if (hit && *hit < local.source_ids.size()) {
                const auto candidate = local.source_ids[*hit];
                if (candidate != *impl_->capture &&
                    impl_->descendant_or_self(candidate, *impl_->capture)) target = candidate;
            }
        }
    } else {
        const auto hit = ui_target_at_position(frame.widgets, x, y);
        target = hit && *hit < frame.source_ids.size()
            ? std::optional<UiWindowId>(frame.source_ids[*hit]) : impl_->sheet;
    }
    if (impl_->modal && impl_->alive(*impl_->modal) && target &&
        !impl_->descendant_or_self(*target, *impl_->modal)) target = impl_->modal;
    return target;
}

std::vector<UiWindowId> UiWindowRuntime::dispatch_path(
    std::optional<UiWindowId> target) const {
    std::vector<UiWindowId> result;
    for (std::size_t guard = 0; target && guard <= impl_->nodes.size(); ++guard) {
        if (!impl_->alive(*target)) break;
        result.push_back(*target);
        if (impl_->modal == target) break;
        target = impl_->parent(*target);
    }
    return result;
}

bool UiWindowRuntime::is_button(UiWindowId id) const { return impl_->node(id).button; }
bool UiWindowRuntime::window_mouse_down(UiWindowId id, std::uint8_t button,
                                       const ButtonCallback& callback) {
    if (!impl_->alive(id)) return false;
    if (impl_->lifecycle.mouse_down) impl_->lifecycle.mouse_down(id);
    if (!impl_->alive(id)) return false;
    const bool handled = button == 0 && impl_->move_front_impl(id, true);
    if (!impl_->alive(id)) return handled;
    if (impl_->nodes[id].repeat.wants_capture_on_down())
        static_cast<void>(impl_->capture_input(id));
    if (!impl_->alive(id)) return handled;
    impl_->nodes[id].repeat.button_down(button, impl_->capture == id);
    if (callback) callback(id);
    return handled;
}
void UiWindowRuntime::window_mouse_up(UiWindowId id) {
    if (impl_->exists(id) && impl_->nodes[id].repeat.button_up()) impl_->release_input(id);
}
void UiWindowRuntime::advance(float seconds, const RepeatCallback& callback) {
    if (!impl_->sheet || !impl_->alive(*impl_->sheet)) return;
    std::vector<UiWindowId> pending{*impl_->sheet};
    while (!pending.empty()) {
        const auto id = pending.back(); pending.pop_back();
        if (!impl_->alive(id)) continue;
        const auto repeat = impl_->nodes[id].repeat.advance(seconds);
        if (repeat && callback) callback(id, *repeat);
        if (!impl_->alive(id)) continue;
        const auto children = impl_->nodes[id].children;
        pending.insert(pending.end(), children.rbegin(), children.rend());
    }
}
bool UiWindowRuntime::button_mouse_down(UiWindowId id, const UiWindowSnapshot& frame,
                                        float x, float y, const ButtonCallback& callback) {
    if (!impl_->alive(id) || !impl_->nodes[id].button) return false;
    window_mouse_down(id, 0, callback);
    if (!impl_->capture_input(id)) return true;
    if (!impl_->exists(id)) return true;
    impl_->nodes[id].pushed = true;
    impl_->changed();
    impl_->update_button_hover(id, frame, x, y);
    return true;
}
bool UiWindowRuntime::button_mouse_up(UiWindowId id, const UiWindowSnapshot& frame,
                                      float x, float y, const ButtonCallback& effect) {
    if (!impl_->exists(id) || !impl_->nodes[id].button) return false;
    bool exact_hit = false;
    if (impl_->sheet && frame.sheet && *frame.sheet < frame.widgets.size()) {
        const auto hit = ui_target_at_position(frame.widgets, x, y);
        exact_hit = hit && *hit < frame.source_ids.size() && frame.source_ids[*hit] == id;
    }
    if (impl_->nodes[id].pushed && exact_hit) {
        if (impl_->nodes[id].button_class == ButtonClass::checkbox) {
            impl_->set_selected(id, !impl_->nodes[id].selected);
        } else if (impl_->nodes[id].button_class == ButtonClass::radio &&
                   !impl_->nodes[id].selected) {
            impl_->set_selected(id, true);
        }
        if (effect) effect(id);
    }
    window_mouse_up(id);
    impl_->release_input(id);
    return true;
}
void UiWindowRuntime::button_mouse_move(UiWindowId id, const UiWindowSnapshot& frame,
                                        float x, float y) {
    impl_->update_button_hover(id, frame, x, y);
}
void UiWindowRuntime::button_mouse_leave(UiWindowId id) {
    auto& node = impl_->node(id);
    if (!node.button || !node.hovering) return;
    node.hovering = false;
    impl_->changed();
}
bool UiWindowRuntime::button_pushed(UiWindowId id) const { return impl_->node(id).pushed; }
bool UiWindowRuntime::button_hovering(UiWindowId id) const { return impl_->node(id).hovering; }
bool UiWindowRuntime::button_selected(UiWindowId id) const {
    const auto& node = impl_->node(id);
    return node.button && node.selected;
}
void UiWindowRuntime::set_button_selected(UiWindowId id, bool value) {
    auto& node = impl_->node(id);
    if (!node.registered || (node.button_class != ButtonClass::checkbox &&
                             node.button_class != ButtonClass::radio))
        throw std::invalid_argument("window is not a selectable live button");
    impl_->set_selected(id, value);
}
bool UiWindowRuntime::is_thumb(UiWindowId id) const { return impl_->node(id).thumb; }
bool UiWindowRuntime::thumb_mouse_down(UiWindowId id, const UiWindowSnapshot& frame,
                                       float x, float y, const ButtonCallback& callback) {
    if (!impl_->alive(id) || !impl_->nodes[id].thumb) return false;
    if (!button_mouse_down(id, frame, x, y, callback)) return false;
    if (impl_->capture != id || !impl_->exists(id)) return true;
    UiWindowSnapshot local;
    const UiWindowSnapshot* geometry = &frame;
    if (id >= frame.resolved_index_by_id.size() || !frame.resolved_index_by_id[id]) {
        local = impl_->resolve_focus(id, frame);
        geometry = &local;
    }
    if (id < geometry->resolved_index_by_id.size() && geometry->resolved_index_by_id[id]) {
        const auto& resolved = geometry->widgets[*geometry->resolved_index_by_id[id]];
        impl_->nodes[id].thumb_drag_offset = x - resolved.rect.x;
        impl_->changed();
    }
    return true;
}
void UiWindowRuntime::thumb_mouse_move(UiWindowId id, const UiWindowSnapshot& frame,
                                       float x, float y, const ThumbMoveCallback& callback) {
    if (!impl_->alive(id) || !impl_->nodes[id].thumb) return;
    button_mouse_move(id, frame, x, y);
    if (impl_->capture != id || !callback) return;
    const auto parent = impl_->parent(id);
    if (!parent) return;
    UiWindowSnapshot local;
    const UiWindowSnapshot* geometry = &frame;
    if (id >= frame.resolved_index_by_id.size() || !frame.resolved_index_by_id[id] ||
        *parent >= frame.resolved_index_by_id.size() || !frame.resolved_index_by_id[*parent]) {
        local = impl_->resolve_focus(id, frame);
        geometry = &local;
    }
    if (id >= geometry->resolved_index_by_id.size() || !geometry->resolved_index_by_id[id] ||
        *parent >= geometry->resolved_index_by_id.size() ||
        !geometry->resolved_index_by_id[*parent]) return;
    const auto& thumb = geometry->widgets[*geometry->resolved_index_by_id[id]].rect;
    const auto& owner = geometry->widgets[*geometry->resolved_index_by_id[*parent]].rect;
    const float left = std::clamp(x - impl_->nodes[id].thumb_drag_offset, owner.x,
                                  std::max(owner.x, owner.x + owner.width - thumb.width));
    callback(id, left);
}
bool UiWindowRuntime::thumb_mouse_up(UiWindowId id, const UiWindowSnapshot& frame,
                                     float x, float y) {
    if (!impl_->exists(id) || !impl_->nodes[id].thumb) return false;
    const bool handled = button_mouse_up(id, frame, x, y);
    if (impl_->exists(id)) impl_->nodes[id].thumb_drag_offset = 0;
    return handled;
}
void UiWindowRuntime::set_event_listener(EventListener listener) {
    impl_->listener = std::move(listener);
}

void UiWindowRuntime::set_lifecycle(UiWindowLifecycle lifecycle) {
    impl_->lifecycle = std::move(lifecycle);
}

} // namespace torchlight
