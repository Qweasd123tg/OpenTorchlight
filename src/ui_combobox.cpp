#include "torchlight/ui_combobox.hpp"

#include "torchlight/ui_font.hpp"
#include "torchlight/ui_skin.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace torchlight {
namespace {

UiWidget child_widget(const std::string& name, const std::string& type,
                      const std::string& position, const std::string& size) {
    UiWidget result;
    result.name = name;
    result.type = type;
    result.properties["UnifiedPosition"] = position;
    result.properties["UnifiedSize"] = size;
    return result;
}

bool contains(const std::vector<UiWindowId>& ids, UiWindowId id) {
    return std::find(ids.begin(), ids.end(), id) != ids.end();
}

UiRect intersect(UiRect a, UiRect b) {
    const float left = std::max(a.x, b.x);
    const float top = std::max(a.y, b.y);
    const float right = std::min(a.x + a.width, b.x + b.width);
    const float bottom = std::min(a.y + a.height, b.y + b.height);
    return {left, top, std::max(0.0F, right - left), std::max(0.0F, bottom - top)};
}

} // namespace

struct UiSettingsComboboxes::Entry {
    UiSettingsComboKind kind{};
    UiComboboxIds ids;
    std::vector<UiComboOption> options;
    std::size_t selected = 0;
    std::optional<std::size_t> highlighted;
    std::size_t selected_on_open = 0;
    bool visible = false;
    bool armed = false;
};

UiSettingsComboboxes::UiSettingsComboboxes(UiWindowRuntime& runtime, UiResources& resources)
    : runtime_(&runtime), resources_(&resources) {
    // UiResources::font intentionally populates the complete shared font
    // catalog.  A Combobox only needs the Serif metric, so resolve this one
    // resource directly just as CEGUI's look property does.
    try {
        constexpr auto path = "media/UI/Serif.font";
        auto definition = parse_ui_font_definition(resources.archive().read_normalized(path), path);
        const float fallback = definition.size * (96.0F / 72.0F);
        font_ = std::make_unique<UiFont>(resources.archive(), std::move(definition));
        const float measured = font_->line_height();
        line_height_ = std::isfinite(measured) && measured > 0.0F ? measured : fallback;
    } catch (const std::exception&) {
        // Resources are externally supplied; preserve deterministic geometry
        // when the font is unavailable instead of preventing Settings setup.
        line_height_ = 16.0F;
    }
}
UiSettingsComboboxes::~UiSettingsComboboxes() = default;

std::vector<UiComboOption> UiSettingsComboboxes::resolution_options(
    const std::vector<UiResolution>& modes) {
    std::vector<UiComboOption> result;
    result.reserve(modes.size());
    for (std::size_t i = 0; i < modes.size(); ++i) {
        if (modes[i].width <= 0 || modes[i].height <= 0) continue;
        if (std::find_if(result.begin(), result.end(), [&](const UiComboOption& option) {
                return option.resolution == modes[i];
            }) != result.end()) continue;
        result.push_back({std::to_string(modes[i].width) + " x " +
                              std::to_string(modes[i].height),
                          i, modes[i], 0.0F, 0.0F});
    }
    return result;
}

std::vector<UiComboOption> UiSettingsComboboxes::shadow_options() {
    // The shipped strings are translated at runtime.  IDs and effects are
    // original-code; these stable English fallbacks describe those effects.
    return {{"Lighting Off", 0}, {"Shadows Off", 1}, {"Shadows 128", 2},
            {"Shadows 256", 3}, {"Shadows 512", 4}, {"Shadows 1024", 5}};
}

std::vector<UiComboOption> UiSettingsComboboxes::particle_options() {
    return {{"Low", 0, {}, 20.0F, 10.0F},
            {"Medium", 1, {}, 30.0F, 50.0F},
            {"High", 2, {}, 40.0F, 100.0F}};
}

const UiComboboxIds& UiSettingsComboboxes::add(UiSettingsComboKind kind,
                                                UiWindowId combobox,
                                                std::vector<UiComboOption> options) {
    if (!runtime_->alive(combobox)) throw std::out_of_range("dead combobox window");
    if (options.empty()) throw std::invalid_argument("combobox requires an item");
    if (std::any_of(entries_.begin(), entries_.end(), [&](const Entry& e) {
            return e.kind == kind || e.ids.combobox == combobox;
        })) throw std::invalid_argument("combobox already bound");

    const auto base = runtime_->window(combobox).name;
    const float edit_height = line_height_ * 1.5F;
    const auto px = [](float value) { return std::to_string(value); };
    Entry value;
    value.kind = kind;
    value.ids.combobox = combobox;
    value.options = std::move(options);

    auto edit = child_widget(base + "__auto_editbox__", "GuiLook/ComboEditbox",
        "{{0,0},{0,0}}", "{{1,-" + px(edit_height) + "},{0," + px(edit_height) + "}}");
    edit.properties["ReadOnly"] = "True";
    edit.properties["MousePassThroughEnabled"] = "False";
    value.ids.editbox = runtime_->create(std::move(edit));

    auto list = child_widget(base + "__auto_droplist__", "GuiLook/ComboDropList",
        "{{0,0},{0," + px(edit_height) + "}}", "{{1,0},{1,-" + px(edit_height) + "}}");
    list.properties["AlwaysOnTop"] = "True";
    list.properties["ClippedByParent"] = "False";
    list.properties["MousePassThroughEnabled"] = "False";
    value.ids.droplist = runtime_->create(std::move(list));

    auto button = child_widget(base + "__auto_button__", "GuiLook/ImageButton",
        "{{1,-" + px(edit_height) + "},{0,0}}",
        "{{0," + px(edit_height) + "},{0," + px(edit_height) + "}}");
    button.properties["NormalImage"] = "set:GuiLook image:ComboButton";
    button.properties["HoverImage"] = "set:GuiLook image:ComboButtonHighlight";
    button.properties["PushedImage"] = "set:GuiLook image:ComboButton";
    value.ids.drop_button = runtime_->create(std::move(button));

    auto hscroll = child_widget(base + "__auto_droplist____auto_hscrollbar__",
        "GuiLook/HorizontalScrollbar", "{{0,0},{1,-12}}", "{{1,-12},{0,12}}");
    hscroll.properties["Visible"] = "False";
    value.ids.horizontal_scrollbar = runtime_->create(std::move(hscroll));
    auto vscroll = child_widget(base + "__auto_droplist____auto_vscrollbar__",
        "GuiLook/VerticalScrollbar", "{{1,-12},{0,0}}", "{{0,12},{1,-12}}");
    vscroll.properties["Visible"] = "False";
    value.ids.vertical_scrollbar = runtime_->create(std::move(vscroll));

    runtime_->add_child(combobox, value.ids.editbox);
    runtime_->add_child(combobox, value.ids.droplist);
    runtime_->add_child(combobox, value.ids.drop_button);
    runtime_->add_child(value.ids.droplist, value.ids.horizontal_scrollbar);
    runtime_->add_child(value.ids.droplist, value.ids.vertical_scrollbar);
    runtime_->set_distributes_captured_inputs(value.ids.droplist, true);
    runtime_->set_restore_capture(value.ids.horizontal_scrollbar, true);
    runtime_->set_restore_capture(value.ids.vertical_scrollbar, true);
    runtime_->set_visible(value.ids.droplist, false);
    runtime_->set_visible(value.ids.horizontal_scrollbar, false);
    runtime_->set_visible(value.ids.vertical_scrollbar, false);
    runtime_->set_property(combobox, "ClippedByParent", "False");

    // CGameUI::sizeComboList replaces the authored 130px height by the edit
    // height plus every item extent and the drop-list frame remainder.
    const float total_height = edit_height + line_height_ * value.options.size() + 10.0F;
    runtime_->set_property(combobox, "UnifiedSize",
        "{{0,200},{0," + px(total_height) + "}}");
    entries_.push_back(std::move(value));
    sync(DisplaySettings{});
    return entries_.back().ids;
}

void UiSettingsComboboxes::update_options(UiSettingsComboKind kind,
                                           std::vector<UiComboOption> options) {
    if (options.empty()) throw std::invalid_argument("combobox requires an item");
    auto& e = entry(kind);
    e.options = std::move(options);
    e.selected = std::min(e.selected, e.options.size() - 1);
    e.highlighted = e.selected;
    e.selected_on_open = e.selected;
    runtime_->set_property(e.ids.editbox, "Text", e.options[e.selected].text);
}

bool UiSettingsComboboxes::has(UiSettingsComboKind kind) const noexcept {
    return std::any_of(entries_.begin(), entries_.end(),
        [&](const Entry& e) { return e.kind == kind; });
}

void UiSettingsComboboxes::sync(const DisplaySettings& settings) {
    for (auto& e : entries_) {
        std::size_t selected = 0;
        if (e.kind == UiSettingsComboKind::resolution) {
            const UiResolution current{settings.res_width, settings.res_height};
            const auto found = std::find_if(e.options.begin(), e.options.end(), [&](const auto& o) {
                return o.resolution == current;
            });
            if (found != e.options.end()) selected = static_cast<std::size_t>(found - e.options.begin());
        } else if (e.kind == UiSettingsComboKind::shadow) {
            if (!settings.lighting_enabled) selected = 0;
            else if (!settings.shadows_enabled) selected = 1;
            else selected = static_cast<std::size_t>(std::clamp(settings.shadows_detail, 2, 5));
        } else {
            const auto found = std::find_if(e.options.begin(), e.options.end(),
                [&](const auto& o) {
                    return o.particle_fps == settings.particle_fps &&
                           o.particle_percent == settings.particle_percent;
                });
            if (found != e.options.end()) selected = static_cast<std::size_t>(found - e.options.begin());
        }
        e.selected = std::min(selected, e.options.size() - 1);
        e.highlighted = e.selected;
        runtime_->set_property(e.ids.editbox, "Text", e.options[e.selected].text);
    }
}

void UiSettingsComboboxes::layout(const UiWindowSnapshot& frame) {
    const float height = line_height(frame.width, frame.height);
    const float ratio = frame.layout_state.offset_ratio &&
                                std::isfinite(*frame.layout_state.offset_ratio) &&
                                *frame.layout_state.offset_ratio > 0.0F
                            ? *frame.layout_state.offset_ratio
                            : 1.0F;
    for (auto& e : entries_) {
        // CGameUI::sizeComboList uses the look's ItemRenderingArea rather
        // than a literal border. Resolve the same resource geometry from the
        // pre-layout snapshot; its dimensions are already viewport pixels.
        float frame_margin = 10.0F * ratio;
        if (e.ids.droplist < frame.resolved_index_by_id.size()) {
            const auto index = frame.resolved_index_by_id[e.ids.droplist];
            if (index && *index < frame.widgets.size()) {
                const auto& list = frame.widgets[*index];
                try {
                    if (const auto area = resources_->skin().named_area(
                            *resources_, list, "ItemRenderingArea", frame.width, frame.height)) {
                        const float measured = list.rect.height - area->height;
                        if (std::isfinite(measured) && measured >= 0.0F)
                            frame_margin = measured;
                    }
                } catch (const std::exception&) {
                    // The documented 10 native pixels remain a deterministic
                    // fallback when external frame imagery is unavailable.
                }
            }
        }
        layout_entry(e, height, ratio, frame_margin);
    }
}

bool UiSettingsComboboxes::handles(UiWindowId id) const noexcept { return owner(id) != nullptr; }

bool UiSettingsComboboxes::pointer_down(UiWindowId id, const UiWindowSnapshot& frame,
                                        float x, float y) {
    auto* e = owner(id);
    if (!e) return false;
    reconcile_capture();
    if (id == e->ids.drop_button) {
        // Combobox::initialiseComponents @0x1393f2 subscribes the button's
        // EventMouseButtonDown to button_PressHandler.  show() activates and
        // captures the list during Window's base event; the later ButtonBase
        // capture attempt then fails because the button was deactivated.
        return runtime_->button_mouse_down(id, frame, x, y,
            [&](UiWindowId) { show(*e); });
    }
    if (id == e->ids.editbox) {
        runtime_->window_mouse_down(id, 0, [&](UiWindowId) { show(*e); });
        return true;
    }
    if (e->visible && (id == e->ids.droplist || id == e->ids.horizontal_scrollbar ||
                       id == e->ids.vertical_scrollbar)) {
        runtime_->window_mouse_down(id, 0);
        if (const auto item = item_at(*e, frame, x, y)) {
            e->highlighted = *item;
            e->armed = true;
        } else {
            e->highlighted.reset();
            hide(*e, true);
        }
        return true;
    }
    if (id == e->ids.combobox) {
        runtime_->window_mouse_down(id, 0);
        return true;
    }
    return false;
}

void UiSettingsComboboxes::pointer_move(const UiWindowSnapshot& frame, float x, float y,
                                        bool left_down) {
    reconcile_capture();
    for (auto& e : entries_) if (e.visible) {
        const auto item = item_at(e, frame, x, y);
        e.highlighted = item;
        // Settings enables ComboDropList single-click operation.  The pinned
        // onMouseMove arms over an item even when no button is held.
        if (item) e.armed = true;
    }
    static_cast<void>(left_down); // retained for a future non-single-click owner.
}

std::optional<UiComboSelection> UiSettingsComboboxes::pointer_up(
    UiWindowId id, const UiWindowSnapshot& frame, float x, float y) {
    auto* e = owner(id);
    if (!e) return std::nullopt;
    if (id == e->ids.drop_button) {
        static_cast<void>(runtime_->button_mouse_up(id, frame, x, y, {}));
        return std::nullopt;
    }
    runtime_->window_mouse_up(id);
    if (!e->visible) return std::nullopt;
    // ComboDropList starts unarmed.  The release belonging to the press that
    // opened it only arms the list; a later release may accept an item.
    if (!e->armed) {
        e->armed = true;
        return std::nullopt;
    }
    const auto item = item_at(*e, frame, x, y);
    if (!item) {
        hide(*e, true);
        return std::nullopt;
    }
    e->selected = *item;
    e->highlighted = *item;
    runtime_->set_property(e->ids.editbox, "Text", e->options[*item].text);
    UiComboSelection result{e->kind, *item, e->options[*item]};
    // Native order: selection accepted updates ComboEditbox and emits the
    // Combobox event, then releaseInput causes capture-lost and hides popup.
    hide(*e, false);
    runtime_->activate(e->ids.editbox);
    return result;
}

void UiSettingsComboboxes::hide_all() {
    for (auto& e : entries_) if (e.visible) hide(e, true);
}

void UiSettingsComboboxes::reconcile_capture() {
    for (auto& e : entries_) if (e.visible && runtime_->capture() != e.ids.droplist)
        hide(e, true);
}

bool UiSettingsComboboxes::popup_visible(UiSettingsComboKind kind) const {
    return entry(kind).visible;
}
const UiComboboxIds& UiSettingsComboboxes::ids(UiSettingsComboKind kind) const {
    return entry(kind).ids;
}
const std::vector<UiComboOption>& UiSettingsComboboxes::options(UiSettingsComboKind kind) const {
    return entry(kind).options;
}
std::size_t UiSettingsComboboxes::selected(UiSettingsComboKind kind) const {
    return entry(kind).selected;
}

std::vector<UiComboPaintRow> UiSettingsComboboxes::paint(
    const UiWindowSnapshot& frame) const {
    std::vector<UiComboPaintRow> result;
    for (const auto& e : entries_) {
        if (!e.visible || e.ids.droplist >= frame.resolved_index_by_id.size()) continue;
        const auto index = frame.resolved_index_by_id[e.ids.droplist];
        if (!index || *index >= frame.widgets.size()) continue;
        const auto& list = frame.widgets[*index];
        const float row_height = line_height(frame.width, frame.height);
        UiRect item_area = list.rect;
        try {
            if (const auto area = resources_->skin().named_area(
                    *resources_, list, "ItemRenderingArea", frame.width, frame.height))
                item_area = *area;
        } catch (const std::exception&) {
            // Missing external imagery leaves a bounded full-list area; do
            // not substitute an unverified fixed frame thickness.
        }
        for (std::size_t i = 0; i < e.options.size(); ++i) {
            UiRect rect{item_area.x, item_area.y + row_height * i,
                        std::max(0.0F, item_area.width), row_height};
            rect = intersect(rect, list.clip);
            if (rect.width <= 0 || rect.height <= 0) continue;
            result.push_back({e.ids.droplist, i, e.options[i].text, rect, list.clip,
                              i == e.selected, e.highlighted && *e.highlighted == i,
                              list.paint_order});
        }
    }
    return result;
}

void UiSettingsComboboxes::apply(const UiComboSelection& selection,
                                 DisplaySettings& settings) {
    if (selection.kind == UiSettingsComboKind::resolution) {
        settings.res_width = selection.option.resolution.width;
        settings.res_height = selection.option.resolution.height;
    } else if (selection.kind == UiSettingsComboKind::shadow) {
        settings.shadows_detail = static_cast<int>(selection.option.id);
        settings.shadows_enabled = selection.option.id >= 2;
        settings.lighting_enabled = selection.option.id != 0;
        if (selection.option.id >= 2 && selection.option.id <= 5)
            settings.shadow_resolution = 128 << (selection.option.id - 2);
    } else if (selection.kind == UiSettingsComboKind::particle) {
        settings.particle_fps = selection.option.particle_fps;
        settings.particle_percent = selection.option.particle_percent;
    }
}

UiSettingsComboboxes::Entry& UiSettingsComboboxes::entry(UiSettingsComboKind kind) {
    const auto it = std::find_if(entries_.begin(), entries_.end(),
        [&](const Entry& e) { return e.kind == kind; });
    if (it == entries_.end()) throw std::out_of_range("unbound settings combobox");
    return *it;
}
const UiSettingsComboboxes::Entry& UiSettingsComboboxes::entry(UiSettingsComboKind kind) const {
    const auto it = std::find_if(entries_.begin(), entries_.end(),
        [&](const Entry& e) { return e.kind == kind; });
    if (it == entries_.end()) throw std::out_of_range("unbound settings combobox");
    return *it;
}
UiSettingsComboboxes::Entry* UiSettingsComboboxes::owner(UiWindowId id) noexcept {
    const auto it = std::find_if(entries_.begin(), entries_.end(), [&](const Entry& e) {
        const std::vector<UiWindowId> ids{e.ids.combobox, e.ids.editbox, e.ids.droplist,
            e.ids.drop_button, e.ids.horizontal_scrollbar, e.ids.vertical_scrollbar};
        return contains(ids, id);
    });
    return it == entries_.end() ? nullptr : &*it;
}
const UiSettingsComboboxes::Entry* UiSettingsComboboxes::owner(UiWindowId id) const noexcept {
    return const_cast<UiSettingsComboboxes*>(this)->owner(id);
}

void UiSettingsComboboxes::show(Entry& e) {
    hide_all();
    e.selected_on_open = e.selected;
    e.highlighted = e.selected;
    e.armed = false;
    e.visible = true;
    runtime_->set_visible(e.ids.droplist, true);
    runtime_->activate(e.ids.droplist);
    if (!runtime_->capture_input(e.ids.droplist)) {
        e.visible = false;
        runtime_->set_visible(e.ids.droplist, false);
    }
}

void UiSettingsComboboxes::hide(Entry& e, bool restore_selection) {
    if (!e.visible) return;
    if (restore_selection) {
        e.selected = e.selected_on_open;
        e.highlighted = e.selected;
    }
    e.visible = false;
    e.armed = false;
    if (runtime_->capture() == e.ids.droplist) runtime_->release_input(e.ids.droplist);
    runtime_->set_visible(e.ids.droplist, false);
}

std::optional<std::size_t> UiSettingsComboboxes::item_at(
    const Entry& e, const UiWindowSnapshot& frame, float x, float y) const {
    const auto rows = paint(frame);
    for (const auto& row : rows)
        if (row.droplist == e.ids.droplist && row.rect.contains(x, y)) return row.option;
    return std::nullopt;
}

float UiSettingsComboboxes::line_height(int width, int height) const {
    if (!font_ || width <= 0 || height <= 0) return line_height_;
    font_->notify_screen_size(static_cast<float>(width), static_cast<float>(height));
    const float measured = font_->line_height();
    return std::isfinite(measured) && measured > 0.0F ? measured : line_height_;
}

void UiSettingsComboboxes::layout_entry(Entry& e, float line, float offset_ratio,
                                         float vertical_frame_margin) {
    const float edit_height = line * 1.5F;
    const auto px = [](float value) { return std::to_string(value); };
    // UiLayout applies offset_ratio to every Unified offset. Font and image
    // metrics above are already viewport pixels, so encode them back into
    // native offset units exactly once.
    const float edit_offset = edit_height / offset_ratio;
    const float total_offset =
        (edit_height + line * e.options.size() + vertical_frame_margin) / offset_ratio;
    runtime_->set_property(e.ids.editbox, "UnifiedPosition", "{{0,0},{0,0}}");
    runtime_->set_property(e.ids.editbox, "UnifiedSize",
        "{{1,-" + px(edit_offset) + "},{0," + px(edit_offset) + "}}");
    runtime_->set_property(e.ids.droplist, "UnifiedPosition",
        "{{0,0},{0," + px(edit_offset) + "}}");
    runtime_->set_property(e.ids.droplist, "UnifiedSize",
        "{{1,0},{1,-" + px(edit_offset) + "}}");
    runtime_->set_property(e.ids.drop_button, "UnifiedPosition",
        "{{1,-" + px(edit_offset) + "},{0,0}}");
    runtime_->set_property(e.ids.drop_button, "UnifiedSize",
        "{{0," + px(edit_offset) + "},{0," + px(edit_offset) + "}}");
    runtime_->set_property(e.ids.combobox, "UnifiedSize",
        "{{0,200},{0," + px(total_offset) + "}}");
}

} // namespace torchlight
