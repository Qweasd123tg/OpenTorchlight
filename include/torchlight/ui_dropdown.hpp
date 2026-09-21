#pragma once
#include "torchlight/ui_window_runtime.hpp"
#include <array>
#include <map>
#include <memory>
#include <optional>

namespace torchlight {
// original-code: CDropdownMenu::mapEventHandlers @0xb179e0.
// See research/dropdown-mainmenu.md for the full call/cleanup boundary.
class DropdownEventTree {
public:
    using Node = std::size_t;
    virtual ~DropdownEventTree() = default;
    virtual std::size_t child_count(Node) const = 0;
    virtual Node child(Node, std::size_t) const = 0;
    virtual bool has_click_property(Node) const = 0;
    virtual std::string click_property(Node) const = 0;
    virtual void want_multi_click(Node) = 0;
    virtual void subscribe_mouse_down(Node) = 0;
    virtual void subscribe_double_click(Node) = 0;
};
void map_dropdown_events(DropdownEventTree&, DropdownEventTree::Node);
struct DropdownSubscriptions {
    bool multi_click = false;
    std::size_t mouse_down = 0, double_click = 0;
};

struct DropdownWindowFrame {
    std::vector<UiResolvedWidget> widgets;
    std::vector<DropdownSubscriptions> subscriptions;
    std::vector<UiWindowId> source_ids;
    // The port supplies a bounded stand-in for CEGUI System's external sheet.
    std::optional<std::size_t> sheet;
    const UiWindowRuntime* runtime = nullptr;
    int width = 0, height = 0;
    UiLayoutState layout_state;
    [[nodiscard]] std::optional<std::size_t> target_at_position(float x, float y) const;
    [[nodiscard]] std::optional<std::size_t> mouse_down_receiver(float x, float y) const;
};
[[nodiscard]] std::vector<DropdownSubscriptions> dropdown_subscriptions(const UiLayout&);
// First subscribed ancestor of the single topmost target. Empty subscription
// does not expose a lower sibling. research/mainmenu-pointer-routing.md.
[[nodiscard]] std::optional<std::size_t> dropdown_mouse_down_receiver(
    const std::vector<UiResolvedWidget>&, const std::vector<DropdownSubscriptions>&,
    float x, float y);

// CMainMenu ctor @0xc53b18 selects flags=1: no dropdown model. This bounded
// owner retains the service/resource window graph across detach/reopen. It is
// an explicit Frontend lifetime adapter: the native menu destructor leaves
// CEGUI windows under WindowManager ownership.
class StaticDropdownState {
public:
    StaticDropdownState();
    StaticDropdownState(UiWindowRuntime&, UiWindowId sheet, std::string prefix,
                        bool content_parent = false, bool zero_resource_roots = false);
    void bind_layout(const UiLayout&);
    [[nodiscard]] DropdownWindowFrame resolve(
        int width, int height, const UiLayoutState& state = {}) const;
    void attach(bool move_to_back = true);
    void detach();
    void set_open(bool value);
    void set_settings_open(bool value);
    [[nodiscard]] bool open() const noexcept { return open_; }
    [[nodiscard]] bool closed() const noexcept { return closed_; }
    [[nodiscard]] bool attached() const noexcept;
    [[nodiscard]] UiWindowId root() const noexcept { return root_; }
    [[nodiscard]] UiWindowId content() const noexcept { return content_; }
    [[nodiscard]] const std::vector<UiWindowId>& resource_roots() const noexcept {
        return resource_roots_;
    }
    [[nodiscard]] const std::vector<UiWindowId>& resource_ids() const noexcept {
        return resource_ids_;
    }
    [[nodiscard]] DropdownSubscriptions subscription(UiWindowId) const;
    [[nodiscard]] UiWindowRuntime& manager() noexcept { return *runtime_; }
    [[nodiscard]] const UiWindowRuntime& manager() const noexcept { return *runtime_; }
private:
    void create_service_windows(std::string prefix);
    std::unique_ptr<UiWindowRuntime> owned_runtime_;
    UiWindowRuntime* runtime_ = nullptr;
    UiWindowId sheet_ = 0, root_ = 0, back_ = 0, content_ = 0;
    std::vector<UiWindowId> resource_roots_, resource_ids_;
    std::map<UiWindowId, DropdownSubscriptions> subscriptions_;
    bool content_parent_ = false;
    bool zero_resource_roots_ = true;
    bool shared_runtime_ = false;
    std::string prefix_;
    bool open_ = false, closed_ = true;
};

// Direct call boundaries of CMainMenu::onClick @0xc4ae80. Each operation has
// a production Frontend consumer; native saves/state-controller remain an
// explicitly documented adapter. Exceptions propagate like the source body.
class MainMenuActions {
public:
    virtual ~MainMenuActions() = default;
    virtual bool main_can_load() const = 0;
    virtual void main_request_state(int game_state, int menu) = 0;
    virtual void main_set_open(bool) = 0;
    virtual void main_request_exit() = 0;
    virtual void main_close_all() = 0;
    virtual void main_toggle_settings() = 0;
    virtual bool main_has_linux_credits() const = 0;
    virtual void main_show_credits(bool linux_panel, bool visible) = 0;
};
bool dispatch_main_menu(bool open, bool closed, UiLayoutFunction, MainMenuActions&);
} // namespace torchlight
