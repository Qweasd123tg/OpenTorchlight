#include "torchlight/ui_dropdown.hpp"
#include "torchlight/generated/ui_state_queries.hpp"
#include <algorithm>
#include <array>
#include <set>
#include <stdexcept>

namespace torchlight {
namespace {
constexpr std::uint64_t double_click_stack = 0x10000;
constexpr std::uint64_t double_click_return = 0x7ff00000;
class DefaultDoubleClickMemory final : public pcode::Memory {
public:
    std::uint64_t read(std::uint64_t address, std::size_t width) override {
        if (address == double_click_stack && width == 8) return double_click_return;
        throw std::logic_error("dropdown default double-click read outside private RET slot");
    }
    void write(std::uint64_t, std::size_t, std::uint64_t) override {
        throw std::logic_error("dropdown default double-click has no memory writes");
    }
};
}

bool dropdown_default_double_click() {
    DefaultDoubleClickMemory memory;
    pcode::RegisterFile registers;
    // The original six-byte body never reads object or argument registers.
    // Its actual RET consumes only this owned, initialized eight-byte slot.
    registers.write(0x20, 8, double_click_stack);
    return pcode_generated::fn_00b05e80(memory, registers, double_click_return) != 0;
}

void map_dropdown_events(DropdownEventTree& tree, DropdownEventTree::Node root) {
    const auto count = tree.child_count(root);
    for (std::size_t i = 0; i < count; ++i)
        map_dropdown_events(tree, tree.child(root, i));
    try {
        if (tree.has_click_property(root) && !tree.click_property(root).empty()) {
            tree.want_multi_click(root);
            tree.subscribe_mouse_down(root);
            tree.subscribe_double_click(root);
        }
    } catch (...) {
        // b17e1b: catch local property/subscription failure, retaining earlier
        // effects. Traversal above is outside this node's catch.
    }
}

namespace {
class LayoutEvents final : public DropdownEventTree {
public:
    explicit LayoutEvents(const UiLayout& layout)
        : widgets_(layout.widgets()), children_(widgets_.size()), bindings(widgets_.size()) {
        for (std::size_t i = 0; i < widgets_.size(); ++i)
            if (widgets_[i].parent >= 0) children_.at(widgets_[i].parent).push_back(i);
    }
    std::size_t child_count(Node n) const override { return children_.at(n).size(); }
    Node child(Node n, std::size_t i) const override { return children_.at(n).at(i); }
    bool has_click_property(Node n) const override { return widgets_.at(n).properties.count("onClick") != 0; }
    std::string click_property(Node n) const override { return widgets_.at(n).property("onClick"); }
    void want_multi_click(Node n) override { bindings.at(n).multi_click = true; }
    void subscribe_mouse_down(Node n) override { ++bindings.at(n).mouse_down; }
    void subscribe_double_click(Node n) override { ++bindings.at(n).double_click; }
private:
    const std::vector<UiWidget>& widgets_;
    std::vector<std::vector<Node>> children_;
public:
    std::vector<DropdownSubscriptions> bindings;
};
}

std::vector<DropdownSubscriptions> dropdown_subscriptions(const UiLayout& layout) {
    LayoutEvents tree(layout);
    for (std::size_t i = 0; i < layout.widgets().size(); ++i)
        if (layout.widgets()[i].parent < 0) map_dropdown_events(tree, i);
    return std::move(tree.bindings);
}

std::optional<std::size_t> dropdown_mouse_down_receiver(
    const std::vector<UiResolvedWidget>& widgets,
    const std::vector<DropdownSubscriptions>& subscriptions, float x, float y) {
    if (widgets.size() != subscriptions.size())
        throw std::invalid_argument("dropdown subscription tree size differs");
    auto target = ui_target_at_position(widgets, x, y);
    for (std::size_t visited = 0; target; ++visited) {
        if (*target >= widgets.size() || visited >= widgets.size())
            throw std::invalid_argument("invalid dropdown parent chain");
        if (subscriptions[*target].mouse_down != 0) return target;
        const auto parent = widgets[*target].parent;
        if (parent < 0) return std::nullopt;
        target = static_cast<std::size_t>(parent);
    }
    return std::nullopt;
}

std::optional<std::size_t> DropdownWindowFrame::target_at_position(float x, float y) const {
    if (subscriptions.size() != widgets.size())
        throw std::invalid_argument("dropdown subscription tree size differs");
    if (!sheet || *sheet >= widgets.size() || !widgets[*sheet].visible)
        return std::nullopt;
    if (runtime) {
        UiWindowSnapshot frame;
        frame.widgets = widgets;
        frame.source_ids = source_ids;
        frame.sheet = sheet;
        frame.width = width;
        frame.height = height;
        frame.layout_state = layout_state;
        std::size_t count = 0;
        for (const auto id : source_ids) count = std::max(count, id + 1);
        frame.resolved_index_by_id.resize(count);
        for (std::size_t i = 0; i < source_ids.size(); ++i)
            frame.resolved_index_by_id[source_ids[i]] = i;
        const auto selected = runtime->target_at_position(frame, x, y);
        if (!selected) return std::nullopt;
        const auto found = std::find(source_ids.begin(), source_ids.end(), *selected);
        return found == source_ids.end() ? std::nullopt
                                         : std::optional<std::size_t>(found - source_ids.begin());
    }
    const auto target = ui_target_at_position(widgets, x, y);
    if (target && (!sheet || *target != *sheet)) return target;
    // System::getTargetWindow returns the active sheet if no child target was
    // found. It does not apply the sheet's own isHit/pass-through/disabled
    // checks; modal/capture state is outside this bounded adapter.
    return sheet;
}

std::optional<std::size_t> DropdownWindowFrame::mouse_down_receiver(float x, float y) const {
    if (subscriptions.size() != widgets.size())
        throw std::invalid_argument("dropdown subscription tree size differs");
    auto target = target_at_position(x, y);
    for (std::size_t visited = 0; target; ++visited) {
        if (*target >= widgets.size() || visited >= widgets.size())
            throw std::invalid_argument("invalid dropdown parent chain");
        if (subscriptions[*target].mouse_down != 0) return target;
        const auto parent = widgets[*target].parent;
        if (parent < 0) return std::nullopt;
        target = static_cast<std::size_t>(parent);
    }
    return std::nullopt;
}

namespace {
std::string service_name(const std::set<std::string>& resource_names, std::string base) {
    if (!resource_names.count(base)) return base;
    for (std::size_t suffix = 1;; ++suffix) {
        auto candidate = base + "#" + std::to_string(suffix);
        if (!resource_names.count(candidate)) return candidate;
    }
}

UiWidget service_widget(std::string name, std::string type, bool pass_through) {
    UiWidget widget;
    widget.name = std::move(name);
    widget.type = std::move(type);
    widget.properties["DestroyedByParent"] = "True";
    widget.properties["MousePassThroughEnabled"] = pass_through ? "True" : "False";
    widget.properties["UnifiedPosition"] = "{{0,0},{0,0}}";
    widget.properties["UnifiedSize"] = "{{1,0},{1,0}}";
    return widget;
}
}

StaticDropdownState::StaticDropdownState()
    : owned_runtime_(std::make_unique<UiWindowRuntime>()), runtime_(owned_runtime_.get()),
      prefix_("__opentorchlight/dropdown") {
    sheet_ = runtime_->create(service_widget(
        "__opentorchlight/dropdown/external-sheet", "DefaultWindow", false));
    runtime_->set_sheet(sheet_);
    create_service_windows(prefix_);
}

StaticDropdownState::StaticDropdownState(UiWindowRuntime& runtime, UiWindowId sheet,
                                         std::string prefix, bool content_parent,
                                         bool zero_resource_roots)
    : runtime_(&runtime), sheet_(sheet), content_parent_(content_parent),
      zero_resource_roots_(zero_resource_roots), shared_runtime_(true),
      prefix_(std::move(prefix)) {
    if (!runtime_->alive(sheet_)) throw std::invalid_argument("dropdown sheet is dead");
    create_service_windows(prefix_);
}

void StaticDropdownState::create_service_windows(std::string prefix) {
    auto unique = [&](std::string suffix) {
        auto name = prefix + suffix;
        while (runtime_->find(name)) name += "#";
        return name;
    };
    auto root = service_widget(unique("/root"), "DefaultWindow", false);
    auto back = service_widget(unique("/back"), "DefaultWindow", false);
    auto content = service_widget(unique("/content"), "DefaultWindow", true);
    for (auto* value : {&root, &back, &content}) {
        value->properties["RiseOnClick"] = "False";
        value->properties["ZOrderingEnabled"] = "False";
    }
    root_ = runtime_->create(std::move(root));
    back_ = runtime_->create(std::move(back));
    content_ = runtime_->create(std::move(content));
    runtime_->add_child(root_, back_);
    runtime_->add_child(root_, content_);
}

void StaticDropdownState::bind_layout(const UiLayout& layout) {
    for (const auto id : resource_roots_)
        if (runtime_->alive(id)) runtime_->destroy(id);
    runtime_->clean_dead_pool();
    resource_roots_.clear();
    resource_ids_.clear();
    subscriptions_.clear();

    const auto bindings = dropdown_subscriptions(layout);
    std::set<std::string> names{
        runtime_->window(root_).name, runtime_->window(back_).name,
        runtime_->window(content_).name};
    resource_ids_.reserve(layout.widgets().size());
    for (const auto& source : layout.widgets()) {
        auto copy = source;
        if (shared_runtime_) copy.name = prefix_ + "/resource/" + copy.name;
        if (names.count(copy.name)) copy.name = service_name(names, copy.name);
        names.insert(copy.name);
        resource_ids_.push_back(runtime_->create(std::move(copy)));
    }
    for (std::size_t i = 0; i < layout.widgets().size(); ++i) {
        const auto parent = layout.widgets()[i].parent;
        if (parent >= 0) {
            runtime_->add_child(resource_ids_.at(static_cast<std::size_t>(parent)),
                                resource_ids_[i]);
        } else {
            resource_roots_.push_back(resource_ids_[i]);
            if (zero_resource_roots_) runtime_->set_zero_position(resource_ids_[i], true);
            runtime_->add_child(content_parent_ ? content_ : root_, resource_ids_[i]);
        }
        subscriptions_[resource_ids_[i]] = bindings[i];
        if (bindings[i].multi_click)
            runtime_->set_property(resource_ids_[i], "WantsMultiClickEvents", "True");
    }
}

DropdownWindowFrame StaticDropdownState::resolve(
    int width, int height, const UiLayoutState& requested_state) const {
    if (width <= 0 || height <= 0) throw std::invalid_argument("invalid UI viewport");
    auto state = requested_state;
    auto resolved = runtime_->snapshot(width, height, state);
    for (const auto root : resource_roots_)
        if (root < resolved.resolved_index_by_id.size() && resolved.resolved_index_by_id[root])
            state.zero_position_nodes.push_back(*resolved.resolved_index_by_id[root]);
    resolved = runtime_->snapshot(width, height, state);
    DropdownWindowFrame frame;
    frame.widgets = std::move(resolved.widgets);
    frame.source_ids = std::move(resolved.source_ids);
    frame.sheet = resolved.sheet;
    frame.width = width;
    frame.height = height;
    frame.layout_state = state;
    frame.runtime = shared_runtime_ ? runtime_ : nullptr;
    frame.subscriptions.reserve(frame.source_ids.size());
    for (const auto id : frame.source_ids) frame.subscriptions.push_back(subscription(id));
    return frame;
}

bool StaticDropdownState::attached() const noexcept {
    return runtime_ && runtime_->alive(root_) &&
        runtime_->window(root_).parent == static_cast<std::int32_t>(sheet_);
}

void StaticDropdownState::attach(bool move_to_back) {
    if (!attached()) {
        runtime_->add_child(sheet_, root_);
        if (move_to_back) runtime_->move_to_back(root_);
    }
}

void StaticDropdownState::detach() {
    if (attached()) runtime_->remove_child(sheet_, root_);
}

void StaticDropdownState::set_open(bool value) {
    // b19180 / b19118: closed is written on detach, retained on attach.
    if (open_ && !value) {
        detach();
        closed_ = true;
    } else if (!open_ && value) {
        attach();
    }
    open_ = value;
}

void StaticDropdownState::set_settings_open(bool value) {
    if (open_ == value) return;
    if (value) {
        runtime_->set_property(content_, "UnifiedPosition", "{{0,0},{0,0}}");
        attach();
    } else {
        detach();
    }
    closed_ = false;
    open_ = value;
}

DropdownSubscriptions StaticDropdownState::subscription(UiWindowId id) const {
    const auto found = subscriptions_.find(id);
    return found == subscriptions_.end() ? DropdownSubscriptions{} : found->second;
}

bool dispatch_main_menu(bool open, bool closed, UiLayoutFunction function, MainMenuActions& out) {
    if (!open && closed) return true;
    switch (function) {
    case UiLayoutFunction::exit_application:
        out.main_request_exit();
        out.main_close_all();
        break;
    case UiLayoutFunction::continue_game:
        out.main_request_state(2, 0);
        out.main_set_open(false);
        break;
    case UiLayoutFunction::new_game_menu:
        out.main_request_state(0, 1);
        out.main_set_open(false);
        break;
    case UiLayoutFunction::continue_game_menu:
        out.main_request_state(0, out.main_can_load() ? 3 : 1);
        out.main_set_open(false);
        break;
    case UiLayoutFunction::select_a: out.main_show_credits(false, true); break;
    case UiLayoutFunction::select_b: out.main_show_credits(false, false); break;
    case UiLayoutFunction::select_c:
        if (out.main_has_linux_credits()) out.main_show_credits(true, true);
        break;
    case UiLayoutFunction::select_d:
        if (out.main_has_linux_credits()) out.main_show_credits(true, false);
        break;
    case UiLayoutFunction::settings_menu: out.main_toggle_settings(); break;
    default: break;
    }
    return true;
}
} // namespace torchlight
