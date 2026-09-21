#include "torchlight/frontend.hpp"
#include "torchlight/ui_screen_scale.hpp"
#include "torchlight/ui_skin.hpp"
#include <algorithm>
#include <charconv>
#include <cctype>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace torchlight {
namespace {
std::string upper(std::string s) {
    for (auto &c : s)
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return s;
}
std::string leaf(std::string s) {
    const auto p = s.find_last_of('/');
    return p == s.npos ? s : s.substr(p + 1);
}
std::string number(std::size_t n) {
    return std::to_string(n);
}
std::string scalar(float value) {
    char buffer[48];
    const auto result = std::to_chars(buffer, buffer + sizeof(buffer), value,
        std::chars_format::general, std::numeric_limits<float>::max_digits10);
    if (result.ec != std::errc{}) throw std::runtime_error("cannot format UI scalar");
    return {buffer, result.ptr};
}
// original-code data: main-menu credit roll, rodata 0xff2e30 of the
// pinned ELF (headers "Designed by Runic Games", "Voice Talents",
// "Additional QA/Artwork", "Built with Ogre3d, CEGUI, ParticleUniverse, and
// FMOD"). Paragraph breaks and inline colour tags follow the ASCII literal.
std::string main_menu_credits() {
    static const char *const lines[] = {
        "|cFFFFBA00Designed by Runic Games|u",
        "",
        "Adam Perin",
        "Ben Evans",
        "Brock Jones",
        "Erich Schaefer",
        "Greg Brown",
        "Ian Welke",
        "Jamus Thayn",
        "Jason Beck",
        "Jason Lamb",
        "Jeff Mianowski",
        "Jeremy Huxley",
        "John Dunbar",
        "Kevin Green",
        "Kyle Cornelius",
        "Leo Miller",
        "Marsh Lefler",
        "Matt Lefferts",
        "Matt Tanwanteng",
        "Matt Uelmen",
        "Max Schaefer",
        "Mike Fisher",
        "Patrick Blank",
        "Peter Hu",
        "Sirio Brozzi",
        "Travis Baldree",
        "Wonder Russell",
        "",
        "|cFFFFBA00Voice Talents|u",
        "",
        "Lani Minella - Sam Mowry",
        "Eric Newsome - Tim Simmons",
        "Marc Biagi - Bill Corkery",
        "Mark Rose - Dave Rivas",
        "",
        "|cFFFFBA00Additional QA|u",
        "",
        "Nichole Wright - Jeremy Powers",
        "",
        "|cFFFFBA00Additional Artwork|u",
        "ArtCoding - Interserv",
        "",
        "|cFFFFBA00Built with Ogre3d, CEGUI, ParticleUniverse, and FMOD|u",
    };
    std::string out;
    for (const char *line : lines) {
        if (!out.empty()) out += '\n';
        out += line;
    }
    out += '\n';
    return out;
}
} // namespace
UiLayoutState continue_menu_layout_state(const UiLayout& layout, std::size_t count,
                                        std::size_t scroll, std::size_t selected,
                                        bool delete_confirmation) {
    UiLayoutState state;
    // CContinueGameMenu::updateCharacterList @0xc3b2f0, onClick @0xc3fe80.
    // The .otc producer has no mod set; it cannot establish a mod mismatch.
    for (const auto& widget : layout.widgets()) {
        const auto name = leaf(widget.name);
        if (name == "DeleteConfirm") state.visibility[widget.name] = delete_confirmation;
        else if (name == "CharacterModsWarning") state.visibility[widget.name] = false;
        else if (name == "ScrollUp") state.visibility[widget.name] = scroll != 0;
        else if (name == "ScrollDown") state.visibility[widget.name] = scroll < count && count - scroll > 5;
        else if (name == "Continue" || name == "Delete") state.visibility[widget.name] = count != 0;
        for (std::size_t row = 0; row < 5; ++row) {
            const auto suffix = number(row + 1);
            const bool occupied = scroll < count && row < count - scroll;
            if (name == "Player" + suffix || name == "Player" + suffix + "Name" ||
                name == "Player" + suffix + "Desc")
                state.visibility[widget.name] = occupied;
            else if (name == "PlayerHighlight" + suffix)
                state.visibility[widget.name] = occupied && selected == scroll + row;
        }
    }
    // Original raises each highlight after setting its visibility, including
    // unselected rows. Only occupied rows take that branch.
    for (std::size_t row = 0; row < 5 && scroll < count && row < count - scroll; ++row)
        for (const auto& widget : layout.widgets())
            if (leaf(widget.name) == "PlayerHighlight" + number(row + 1))
                state.move_to_front.push_back(widget.name);
    return state;
}
std::vector<FrontendPaintItem> frontend_paint_list(const FrontendFrame &frame) {
    std::vector<FrontendPaintItem> result;
    const auto append = [&](const UiResolvedWidget &widget, std::optional<std::size_t> button) {
        if (!widget.visible) return;
        // A resource window may provide both an image and a text component.
        // Keep its cache together and execute it once.
        if (!widget.name.empty()) {
            const auto it = std::find_if(result.begin(), result.end(), [&](const auto &item) {
                return item.widget.name == widget.name;
            });
            if (it != result.end()) { *it = {widget, button}; return; }
        }
        result.push_back({widget, button});
    };
    for (const auto &w : frame.decorations) append(w, std::nullopt);
    for (const auto &w : frame.texts) append(w, std::nullopt);
    for (std::size_t i = 0; i < frame.buttons.size(); ++i) {
        const auto &b = frame.buttons[i];
        auto w = b.widget;
        w.rect = b.rect; w.text = b.text; w.enabled = b.enabled;
        if (!b.font.empty()) w.font = b.font;
        w.properties["Text"] = w.text;
        if (!w.font.empty()) w.properties["Font"] = w.font;
        append(w, i);
    }
    for (const auto& item : frame.list_items) {
        UiResolvedWidget row;
        row.visible = true;
        row.paint_order = item.paint_order;
        result.push_back({std::move(row), std::nullopt, item.draw});
    }
    for (auto& item : result)
        if (const auto state = frame.window_states.find(item.widget.name); state != frame.window_states.end())
            item.state = state->second;
    std::stable_sort(result.begin(), result.end(), [](const auto &a, const auto &b) {
        return a.widget.paint_order < b.widget.paint_order;
    });
    return result;
}
// The frontend owns its per-window resource bindings even if construction
// fails before its destructor can run. Shared atlas/font storage stays external.
struct Frontend::ResourceWindows {
    UiResources* resources;
    std::map<std::string, std::size_t> names;
    explicit ResourceWindows(UiResources& value) : resources(&value) {}
    void attach(const UiWidget& widget) {
        auto& count = names[widget.name];
        ++count;
        try { resources->attach_window_renderer(widget.name, widget.type); }
        catch (...) { if (--count == 0) names.erase(widget.name); throw; }
    }
    void release(const std::string& name) {
        resources->destroy_window_factory(name);
        const auto it = names.find(name);
        if (it != names.end() && --it->second == 0) names.erase(it);
    }
    ~ResourceWindows() {
        for (const auto& [name, count] : names) {
            resources->detach_window_renderer(name);
            resources->destroy_window_renderer(name);
            for (std::size_t i = 0; i < count; ++i) resources->destroy_window_factory(name);
        }
    }
};
namespace {
std::vector<FrontendClass> validated_classes(std::vector<FrontendClass> classes) {
    if (classes.empty()) throw std::invalid_argument("no frontend classes");
    for (const auto& value : classes)
        if (value.guid == 0 || value.name.empty()) throw std::invalid_argument("invalid frontend class");
    return classes;
}
}
Frontend::Frontend(UiResources &r, std::vector<FrontendClass> c)
    : resources_(&r), classes_(validated_classes(std::move(c))),
      resource_windows_(std::make_unique<ResourceWindows>(r)), sheet_([&] {
          UiWindowLifecycle lifecycle;
          lifecycle.initialize = [this](UiWindowId, const UiWidget& w) {
              resource_windows_->attach(w);
          };
          lifecycle.reset_tooltip_target = [this](UiWindowId id) {
              if (tooltips_) tooltips_->reset_target(id);
          };
          lifecycle.release_tooltip = [this](UiWindowId id) {
              if (tooltips_) tooltips_->release_owned(id);
          };
          lifecycle.detach_renderer = [this](UiWindowId, const UiWidget& w) {
              resources_->detach_window_renderer(w.name);
          };
          lifecycle.destroy_renderer = [this](UiWindowId, const UiWidget& w) {
              resources_->destroy_window_renderer(w.name);
          };
          lifecycle.destroy_factory_object = [this](UiWindowId, const UiWidget& w) {
              resource_windows_->release(w.name);
          };
          lifecycle.mouse_down = [this](UiWindowId) {
              if (tooltips_) tooltips_->down();
          };
          windows_.set_lifecycle(std::move(lifecycle));
          UiWidget sheet;
          sheet.name = "__opentorchlight/frontend/sheet";
          sheet.type = "DefaultWindow";
          sheet.properties["UnifiedSize"] = "{{1,0},{1,0}}";
          return windows_.create(std::move(sheet));
      }()), main_dropdown_(windows_, sheet_, "__opentorchlight/main", false, true) {
    windows_.set_sheet(sheet_);
    tooltips_ = std::make_unique<UiTooltips>(windows_, r);
    comboboxes_ = std::make_unique<UiSettingsComboboxes>(windows_, r);
    windows_.set_event_listener([this](const UiWindowEvent& event) {
        cached_frame_.reset();
        if (event.type == UiWindowEventType::mouse_retarget_requested) retarget_pointer();
        if (event.type == UiWindowEventType::capture_lost &&
            windows_.capture() != event.window) dragging_slider_.clear();
    });
    main_set_open(true);
}
void Frontend::set_saves(std::vector<SaveSlotInfo> saves) {
    cached_frame_.reset();
    buttons_.clear();
    saves_ = std::move(saves);
    save_index_ = std::min(save_index_, saves_.empty() ? 0 : saves_.size() - 1);
    pending_delete_.reset();
    scroll_ = 0;
}
void Frontend::show_main() {
    pending_options_exit_ = false;
    cached_frame_.reset();
    buttons_.clear();
    pressed_window_.clear();
    dragging_slider_.clear();
    page_ = FrontendPage::main;
    main_set_open(true);
    focus_ = 0;
    pending_delete_.reset();
    request_.reset();
    status_.clear();
}
void Frontend::pause() {
    cached_frame_.reset();
    if (page_ == FrontendPage::playing) {
        buttons_.clear();
        page_ = FrontendPage::pause;
        focus_ = 0;
        pending_delete_.reset();
        status_.clear();
    }
}
void Frontend::entered_game() {
    cached_frame_.reset();
    buttons_.clear();
    page_ = FrontendPage::playing;
    main_set_open(false);
    pending_delete_.reset();
    request_.reset();
    status_.clear();
}
void Frontend::error(std::string message) {
    if (pending_options_exit_) { pending_options_exit_ = false; page_ = FrontendPage::pause; }
    cached_frame_.reset();
    status_ = std::move(message);
    request_.reset();
    // The .otc adapter returns a failed load to its originating menu.
    if (page_ == FrontendPage::main) main_set_open(true);
}
void Frontend::saved(FrontendCommand command) {
    cached_frame_.reset();
    request_.reset();
    status_ = "SAVE COMPLETE";
    if (command == FrontendCommand::save_and_menu)
        show_main();
    else if (command == FrontendCommand::save_and_quit)
        page_ = FrontendPage::quit;
}
void Frontend::removed() {
    cached_frame_.reset();
    request_.reset();
    pending_delete_.reset();
    status_ = "SAVE DELETED";
}
void Frontend::applied() {
    cached_frame_.reset();
    request_.reset();
    settings_clean_ = settings_draft_;
    status_ = "SETTINGS SAVED";
}
void Frontend::sync_settings(DisplaySettings settings) {
    cached_frame_.reset();
    settings_clean_ = settings;
    settings_draft_ = settings;
    if (comboboxes_) comboboxes_->sync(settings_draft_);
}
void Frontend::set_resolutions(std::vector<UiResolution> resolutions) {
    if (resolutions_ == resolutions) return;
    resolutions_ = std::move(resolutions);
    if (bound_comboboxes_.count(UiSettingsComboKind::resolution) && !resolutions_.empty()) {
        comboboxes_->update_options(UiSettingsComboKind::resolution,
            UiSettingsComboboxes::resolution_options(resolutions_));
        comboboxes_->sync(settings_draft_);
    }
    cached_frame_.reset();
}
void Frontend::leave_settings() {
    settings_draft_ = settings_clean_;
    if (comboboxes_) comboboxes_->sync(settings_draft_);
    status_.clear();
    if (settings_return_ == FrontendPage::pause) {
        buttons_.clear();
        page_ = FrontendPage::pause;
        focus_ = 0;
    } else {
        show_main();
    }
}
namespace {
// resource-derived: settingsmenu.layout checkbox names to draft flags.
// Sliders and comboboxes use their typed value paths; FSAA remains separate.
const std::pair<const char *, bool DisplaySettings::*> kSettingFlags[] = {
    {"FULLSCREEN", &DisplaySettings::fullscreen},
    {"RENDERBEHIND", &DisplaySettings::render_behind},
    {"RIMLIGHTS", &DisplaySettings::rimlights},
    {"HARDWARESKINNING", &DisplaySettings::hardware_skinning},
    {"VSYNC", &DisplaySettings::vsync},
    {"MUSICMUTE", &DisplaySettings::music_mute},
    {"SOUNDMUTE", &DisplaySettings::sound_mute},
    {"SHOWTIPS", &DisplaySettings::show_tips},
    {"SHOWFLOATYNUMBERS", &DisplaySettings::floaty_numbers},
    {"SHOWBLOOD", &DisplaySettings::show_blood},
    {"NETBOOKMODE", &DisplaySettings::netbook_mode},
};
bool DisplaySettings::*setting_flag(const std::string &upper_name) {
    for (const auto &[name, field] : kSettingFlags)
        if (upper_name == name) return field;
    return nullptr;
}
float DisplaySettings::*setting_volume(const std::string& name) {
    if (name == "MUSICVOLUME") return &DisplaySettings::music_volume;
    if (name == "SOUNDVOLUME") return &DisplaySettings::sound_volume;
    return nullptr;
}
} // namespace
void Frontend::text(char c) {
    cached_frame_.reset();
    // resource-derived: charactercreate.layout EditBox MaxTextLength=12.
    if (page_ == FrontendPage::create && name_.size() < 12 &&
        ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ' ||
         c == '-' || c == '_'))
        name_ += c;
}
void Frontend::key(FrontendKey key) {
    cached_frame_.reset();
    if (request_)
        return;
    if (key == FrontendKey::back) {
        if (page_ == FrontendPage::load && pending_delete_) {
            pending_delete_.reset();
            status_.clear();
        } else if (page_ == FrontendPage::pause)
            entered_game();
        else if (page_ == FrontendPage::settings)
            leave_settings();
        else if (page_ == FrontendPage::load || page_ == FrontendPage::create)
            show_main();
        return;
    }
    if (key == FrontendKey::backspace) {
        if (page_ == FrontendPage::create && !name_.empty())
            name_.pop_back();
        return;
    }
    if (buttons_.empty())
        return;
    if (key == FrontendKey::accept) {
        if (focus_ < buttons_.size() && buttons_[focus_].enabled && buttons_[focus_].owner == page_) {
            const auto action = buttons_[focus_].id;
            const auto function = buttons_[focus_].widget.layout_function;
            activate(action, function);
        }
        return;
    }
    const bool forward = key == FrontendKey::next;
    for (std::size_t n = 0; n < buttons_.size(); ++n) {
        focus_ = forward ? (focus_ + 1) % buttons_.size()
                         : (focus_ + buttons_.size() - 1) % buttons_.size();
        if (buttons_[focus_].enabled && buttons_[focus_].owner == page_)
            break;
    }
}
std::optional<std::size_t> Frontend::button_at(float x, float y) const {
    // Route through the same resource window tree used by the renderer.
    // Pass-through text cannot cover its parent control; an opaque sibling
    // consumes the point even when it has no action in this adapter.
    const auto& windows = input_widgets_;
    const auto id = windows_.target_at_position(window_snapshot_, x, y);
    auto target = id && *id < window_snapshot_.resolved_index_by_id.size()
        ? window_snapshot_.resolved_index_by_id[*id] : std::nullopt;
    for (std::size_t depth = 0; target && depth < windows.size(); ++depth) {
        const auto& widget = windows[*target];
        for (std::size_t i = 0; i < buttons_.size(); ++i)
            if (buttons_[i].enabled && buttons_[i].widget.name == widget.name)
                return i;
        if (widget.parent < 0 || static_cast<std::size_t>(widget.parent) >= windows.size()) break;
        target = static_cast<std::size_t>(widget.parent);
    }
    // Explicit portable controls are outside the original resource tree.
    for (std::size_t i = buttons_.size(); i > 0; --i) {
        const auto& button = buttons_[i - 1];
        if (button.supplemental && button.enabled && button.rect.contains(x, y)) return i - 1;
    }
    return std::nullopt;
}
void Frontend::pointer(const UiPointerState& state) {
    // Ordered events own this state. A host summary already includes later
    // queued events and must not move the cursor/release before their timestamps.
    if (ordered_pointer_) return;
    const bool dragged = state.left_press_origin &&
        state.left_press_origin == pointer_.left_press_origin && state.position != pointer_.position;
    if (!state.left_press_origin) {
        pressed_window_.clear();
        dragging_slider_.clear();
    }
    else if (state.left_press_origin != pointer_.left_press_origin) {
        pressed_window_.clear();
        dragging_slider_.clear();
        const auto& origin = *state.left_press_origin;
        if (const auto button = button_at(origin[0], origin[1])) {
            pressed_window_ = buttons_[*button].widget.name;
            const auto& control = buttons_[*button];
            const auto field = setting_volume(upper(leaf(control.widget.name)));
            if (page_ == FrontendPage::settings && field) {
                const auto thumb = resources_->skin().slider_thumb(*resources_, control.widget,
                    settings_draft_.*field, 1.0F, cached_width_, cached_height_);
                if (thumb && thumb->rect.contains(origin[0], origin[1])) {
                    dragging_slider_ = control.id;
                    slider_drag_offset_ = origin[0] - thumb->rect.x;
                }
            }
        }
    }
    pointer_ = state;
    if (!request_ && dragged && page_ == FrontendPage::settings && !dragging_slider_.empty() && state.position) {
        const auto control = std::find_if(buttons_.begin(), buttons_.end(), [&](const auto& button) {
            return button.id == dragging_slider_;
        });
        if (control == buttons_.end()) return;
        const auto field = setting_volume(upper(leaf(control->widget.name)));
        if (!field) return;
        const auto thumb = resources_->skin().slider_thumb(*resources_, control->widget,
            settings_draft_.*field, 1.0F, cached_width_, cached_height_);
        if (!thumb) return;
        const float value = ui_slider_value_from_thumb((*state.position)[0] - slider_drag_offset_,
                                                       control->rect, thumb->rect.width);
        if (value != settings_draft_.*field) {
            settings_draft_.*field = value;
            cached_frame_.reset();
        }
    }
}
FrontendFrame Frontend::pointer_frame(FrontendFrame frame) const {
    for (const auto& widget : frame.decorations)
        if (const auto id = windows_.find(widget.name); id && windows_.is_button(*id))
            frame.window_states[widget.name] = {windows_.button_hovering(*id),
                windows_.button_pushed(*id), windows_.button_selected(*id)};
    const auto hovered = pointer_.position ?
        button_at((*pointer_.position)[0], (*pointer_.position)[1]) : std::nullopt;
    for (std::size_t i = 0; i < frame.buttons.size(); ++i) {
        auto& button = frame.buttons[i];
        auto id = windows_.find(button.widget.name);
        if (id && slider_thumbs_.count(*id)) id = slider_thumbs_.at(*id);
        if (id && windows_.is_button(*id)) {
            if (upper(button.widget.type).find("CHECKBOX") != std::string::npos ||
                upper(button.widget.type).find("RADIOTAB") != std::string::npos)
                button.selected = windows_.button_selected(*id);
        }
        if (ordered_pointer_ && id && windows_.is_button(*id)) {
            button.hovered = windows_.button_hovering(*id);
            button.pressed = windows_.button_pushed(*id);
        } else {
            button.hovered = hovered == i;
            button.pressed = pointer_.left_press_origin && !pressed_window_.empty() &&
                             button.widget.name == pressed_window_;
        }
    }
    return frame;
}
void Frontend::click(float x, float y) {
    cached_frame_.reset();
    if (request_)
        return;
    if (page_ == FrontendPage::main && main_layout_) {
        // Production route: resolved resource tree -> single topmost window
        // -> subscribed ancestor -> bound command -> CMainMenu dispatcher.
        // Empty buttons mark invalidated/stale input after a page/list change.
        if (buttons_.empty() || !main_dropdown_.attached()) return;
        std::optional<UiWindowId> receiver;
        for (const auto id : windows_.dispatch_path(windows_.target_at_position(window_snapshot_, x, y)))
            if (main_dropdown_.subscription(id).mouse_down) { receiver = id; break; }
        if (!receiver) return;
        const auto widget = windows_.window(*receiver);
        for (std::size_t i = 0; i < buttons_.size(); ++i)
            if (buttons_[i].widget.name == widget.name) { focus_ = i; break; }
        // Unbound onClick still consumes the selected window's subscription;
        // it cannot accidentally execute a lower sibling or a fallback action.
        if (widget.layout_function) activate({}, widget.layout_function);
        return;
    }
    if (const auto button = button_at(x, y)) {
        focus_ = *button;
        const auto& control = buttons_[*button];
        if (control.owner == FrontendPage::pause &&
            (page_ != FrontendPage::pause || (options_animation_ && !options_animation_->open()))) return;
        if (page_ == FrontendPage::settings) {
            if (const auto field = setting_volume(upper(leaf(control.widget.name)))) {
                const auto thumb = resources_->skin().slider_thumb(*resources_, control.widget,
                    settings_draft_.*field, 1.0F, cached_width_, cached_height_);
                if (thumb) {
                    // Slider ctor @0x18a89b: default clickStep=0.01. Native
                    // track clicks step towards the pointer; dragging retains
                    // the grab offset inside the thumb.
                    const float direction = x < thumb->rect.x ? -1.0F :
                        x >= thumb->rect.x + thumb->rect.width ? 1.0F : 0.0F;
                    settings_draft_.*field = std::clamp(settings_draft_.*field + direction * .01F, 0.0F, 1.0F);
                }
                return;
            }
        }
        const auto action = buttons_[*button].id;
        const auto function = buttons_[*button].widget.layout_function;
        activate(action, function);
    }
}
void Frontend::activate(const std::string &id, std::optional<UiLayoutFunction> function) {
    const auto previous_page = page_;
    // Portable confirmation input policy: preserve the selected save while
    // awaiting a destructive choice. The original show's/hide's are below.
    if (pending_delete_ && page_ == FrontendPage::load && id != "accept" && id != "decline") return;
    if (page_ == FrontendPage::main && function) {
        dispatch_main_menu(main_dropdown_.open(), main_dropdown_.closed(), *function, *this);
        if (page_ != previous_page) {
            buttons_.clear();
            pressed_window_.clear();
            dragging_slider_.clear();
        }
        return;
    }
    if (id == "new") {
        page_ = FrontendPage::create;
        focus_ = 0;
        status_.clear();
    } else if (id == "loads") {
        // Portable fallback follows the same empty-list choice as the bound
        // main-menu command; resource input uses dispatch_main_menu above.
        page_ = main_can_load() ? FrontendPage::load : FrontendPage::create;
        focus_ = 0;
        status_.clear();
    } else if (id == "back")
        show_main();
    else if (id == "exit")
        page_ = FrontendPage::quit;
    else if (id == "exit-game" && page_ == FrontendPage::pause) {
        pending_options_exit_ = true;
        page_ = FrontendPage::playing;
    } else if (id == "resume")
        entered_game();
    else if (id == "save" || id == "save-menu" || id == "save-exit")
        request_ =
            FrontendRequest{id == "save" ? FrontendCommand::save
                                         : (id == "save-menu" ? FrontendCommand::save_and_menu
                                                              : FrontendCommand::save_and_quit),
                            0,
                            {},
                            {}};
    else if (id == "create") {
        const auto first = name_.find_first_not_of(' '), last = name_.find_last_not_of(' ');
        if (first == name_.npos) {
            status_ = "ENTER A CHARACTER NAME";
            return;
        }
        request_ = FrontendRequest{FrontendCommand::create,
                                   classes_[class_index_].guid,
                                   name_.substr(first, last - first + 1),
                                   {}};
    } else if (id == "continue" || id == "load") {
        std::size_t index = save_index_;
        if (id == "continue") {
            const auto it = std::find_if(saves_.begin(), saves_.end(),
                                         [](const auto &s) { return s.loadable(); });
            index = static_cast<std::size_t>(it - saves_.begin());
        }
        if (index < saves_.size() && saves_[index].loadable())
            request_ = FrontendRequest{
                FrontendCommand::load, saves_[index].class_guid, {}, saves_[index].slot};
    } else if (id == "scroll-up") {
        if (scroll_ > 0)
            --scroll_;
    } else if (id == "scroll-down") {
        if (scroll_ + 5 < saves_.size())
            ++scroll_;
    } else if (id == "delete") {
        // original-code: CContinueGameMenu guiDelete1 shows DeleteConfirm;
        // guiAccept runs deleteCharacter @0xc3fd00, guiDecline hides it.
        if (page_ == FrontendPage::load && save_index_ < saves_.size()) {
            pending_delete_ = save_index_;
            const auto &slot = saves_[save_index_];
            status_ = "DELETE " + (slot.name.empty() ? slot.slot : slot.name) + "?";
        }
    } else if (id == "accept") {
        if (page_ == FrontendPage::load && pending_delete_ &&
            *pending_delete_ < saves_.size()) {
            request_ = FrontendRequest{FrontendCommand::remove, 0, {},
                                       saves_[*pending_delete_].slot};
            // onClick @0xc3ff57 hides the prompt before deleteCharacter.
            pending_delete_.reset();
            status_.clear();
        }
    } else if (id == "decline") {
        if (page_ == FrontendPage::load) {
            pending_delete_.reset();
            status_.clear();
        }
    } else if (id == "credits-a") {
        // original-code: CMainMenu::onClick opens/closes the two panes.
        // CreditFrameB/CreditsB contains the Linux credits in the layout.
        if (page_ == FrontendPage::main) show_credits_ = true;
    } else if (id == "credits-b") {
        if (page_ == FrontendPage::main) show_credits_ = false;
    } else if (id == "credits-c" || id == "credits-d") {
        if (page_ == FrontendPage::main) show_credits_b_ = id == "credits-c";
    } else if (id == "settings") {
        if (page_ == FrontendPage::main || page_ == FrontendPage::pause) {
            buttons_.clear();
            settings_draft_ = settings_clean_;
            if (comboboxes_) comboboxes_->sync(settings_draft_);
            settings_return_ = page_;
            page_ = FrontendPage::settings;
            focus_ = 0;
            request_.reset();
            status_.clear();
        }
    } else if (id == "apply") {
        if (page_ == FrontendPage::settings)
            request_ = FrontendRequest{FrontendCommand::apply_settings, 0, {}, {},
                                       settings_draft_};
    } else if (id == "decline-settings") {
        if (page_ == FrontendPage::settings) leave_settings();
    } else if (id.rfind("setting-", 0) == 0) {
        if (page_ == FrontendPage::settings) {
            if (const auto field = setting_flag(upper(id.substr(8))))
                settings_draft_.*field = !(settings_draft_.*field);
        }
    } else if (id.rfind("class-", 0) == 0) {
        const auto n = std::stoul(id.substr(6));
        if (n < classes_.size())
            class_index_ = n;
    } else if (id.rfind("slot-", 0) == 0) {
        const auto n = std::stoul(id.substr(5));
        if (n < saves_.size()) {
            save_index_ = n;
            status_ = saves_[n].error;
        }
    }
    if (page_ != previous_page)
        buttons_.clear(); // stale hit rectangles cannot execute on a new page
    if (page_ != previous_page) {
        pressed_window_.clear();
        dragging_slider_.clear();
    }
}

bool Frontend::main_can_load() const {
    // CMenuManager::canLoad @0xc2b700 tests list count. The list producer is
    // still our .otc adapter, not the original .SVB reader.
    return !saves_.empty();
}
void Frontend::main_request_state(int state, int menu) {
    // CGameUI::requestSetGameState @0xa828f0 stores this pair. Consume it in
    // the existing application policy; native CGameStateController is open.
    if (state == 0 && (menu == 1 || menu == 3)) {
        page_ = menu == 1 ? FrontendPage::create : FrontendPage::load;
        focus_ = 0;
        status_.clear();
    } else if (state == 2 && menu == 0) {
        const auto it = std::find_if(saves_.begin(), saves_.end(), [](const auto& s) { return s.loadable(); });
        if (it != saves_.end())
            request_ = FrontendRequest{FrontendCommand::load, it->class_guid, {}, it->slot};
    } else throw std::logic_error("unsupported main-menu state pair");
}
void Frontend::main_set_open(bool value) {
    main_dropdown_.set_open(value);
    cached_frame_.reset();
    buttons_.clear();
    input_widgets_.clear();
    pressed_window_.clear();
}
void Frontend::main_request_exit() { main_exit_requested_ = true; }
void Frontend::main_close_all() {
    main_set_open(false);
    if (main_exit_requested_) page_ = FrontendPage::quit;
}
void Frontend::main_toggle_settings() { activate("settings"); }
bool Frontend::main_has_linux_credits() const { return main_linux_credits_; }
void Frontend::main_show_credits(bool linux_panel, bool visible) {
    (linux_panel ? show_credits_b_ : show_credits_) = visible;
    cached_frame_.reset();
    buttons_.clear(); // input is enabled again after resolving the changed tree
}
std::optional<FrontendRequest> Frontend::take_request() {
    auto result = std::move(request_);
    request_.reset();
    return result;
}
Frontend::~Frontend() {
    // CEGUI WindowManager owns the windows, not CDropdownMenu's destructor.
    // Tear the sheet down while callback consumers are still alive, then
    // release the dead pool in the manager's reverse destruction order.
    windows_.set_event_listener({});
    windows_.destroy(sheet_);
    for (auto& [page, container] : dropdowns_) {
        (void)page;
        if (windows_.alive(container->root())) windows_.destroy(container->root());
    }
    if (windows_.alive(main_dropdown_.root())) windows_.destroy(main_dropdown_.root());
    if (tooltips_) tooltips_->shutdown();
    windows_.clean_dead_pool();
    windows_.set_lifecycle({});
}
StaticDropdownState& Frontend::dropdown(FrontendPage page) {
    if (page == FrontendPage::main) return main_dropdown_;
    auto& result = dropdowns_[page];
    if (!result) {
        const bool content = page == FrontendPage::pause || page == FrontendPage::settings;
        result = std::make_unique<StaticDropdownState>(windows_, sheet_,
            "__opentorchlight/page/" + std::to_string(static_cast<int>(page)), content);
        if (page == FrontendPage::pause) {
            // COptionsMenu::createMenus @0xb8829a..0xb882b1.
            windows_.set_property(result->root(), "AlwaysOnTop", "True");
        }
    }
    return *result;
}
void Frontend::sync_windows() {
    if (page_ != FrontendPage::main &&
        !(page_ == FrontendPage::settings && settings_return_ == FrontendPage::main))
        main_dropdown_.set_open(false);
    for (auto page : {FrontendPage::create, FrontendPage::load, FrontendPage::settings}) {
        const bool wanted = page_ == page;
        if (wanted || dropdowns_.count(page)) {
            if (page == FrontendPage::settings) dropdown(page).set_settings_open(wanted);
            else dropdown(page).set_open(wanted);
        }
    }
    if (page_ != FrontendPage::settings && comboboxes_) comboboxes_->hide_all();
    const bool wanted = page_ == FrontendPage::pause;
    if (wanted && !options_animation_attempted_) {
        options_animation_attempted_ = true;
        // Missing assets remain an explicit portable fallback, not an
        // invented model. Original assets are loaded and validated here.
        if (resources_->archive().find_normalized("media/ui/models/dropdown/dropdown.mesh"))
            options_animation_ = std::make_unique<DropdownAnimation>(resources_->archive());
    }
    if (wanted || dropdowns_.count(FrontendPage::pause)) {
        auto& options = dropdown(FrontendPage::pause);
        if (options_animation_) {
            if (options_animation_->open() != wanted) {
                options_animation_->set_open(wanted);
                if (wanted) {
                    options.attach(false);
                    windows_.move_to_front(options.root()); // COptionsMenu @0xb87229
                }
            }
            if (!wanted && options_animation_->closed()) options.detach();
        } else options.set_open(wanted);
    }
}
void Frontend::bind_settings_combos() {
    const auto found = bound_layouts_.find(FrontendPage::settings);
    if (found == bound_layouts_.end() || !found->second) return;
    const auto& ids = dropdown(FrontendPage::settings).resource_ids();
    const auto& widgets = found->second->widgets();
    for (std::size_t i = 0; i < widgets.size(); ++i) {
        if (widgets[i].type != "GuiLook/Combobox") continue;
        const auto name = leaf(widgets[i].name);
        const auto kind = name == "ResolutionDropdown" ? UiSettingsComboKind::resolution :
            name == "ShadowDropdown" ? UiSettingsComboKind::shadow : UiSettingsComboKind::particle;
        if (name != "ResolutionDropdown" && name != "ShadowDropdown" && name != "ParticleDropdown") continue;
        if (bound_comboboxes_.count(kind)) continue;
        auto options = kind == UiSettingsComboKind::resolution
            ? UiSettingsComboboxes::resolution_options(resolutions_.empty()
                ? std::vector<UiResolution>{{settings_draft_.res_width, settings_draft_.res_height}}
                : resolutions_)
            : kind == UiSettingsComboKind::shadow ? UiSettingsComboboxes::shadow_options()
                                                 : UiSettingsComboboxes::particle_options();
        comboboxes_->add(kind, ids.at(i), std::move(options));
        bound_comboboxes_[kind] = ids.at(i);
        comboboxes_->sync(settings_draft_);
    }
}
void Frontend::resolve_windows(int width, int height) {
    UiLayoutState state;
    state.offset_ratio = static_cast<float>(height) / 768.0F;
    if (options_animation_ && dropdowns_.count(FrontendPage::pause)) {
        const auto position = options_animation_->content_position(width, height);
        // Relative coordinates avoid scaling an already projected pixel offset
        // again in convertToScreenScale's immutable layout adapter.
        windows_.set_property(dropdown(FrontendPage::pause).content(), "UnifiedPosition",
            "{{" + scalar(position[0] / width) + ",0},{" + scalar(position[1] / height) + ",0}}");
    }
    window_snapshot_ = windows_.snapshot(width, height, state);
    if (comboboxes_) {
        const auto revision = windows_.revision();
        comboboxes_->layout(window_snapshot_);
        comboboxes_->reconcile_capture();
        if (revision != windows_.revision()) window_snapshot_ = windows_.snapshot(width, height, state);
    }
    // Falagard creates a real Thumb child. Its geometry comes from the same
    // looknfeel compiler as the painter; capture belongs to this child.
    bool thumbs_changed = false;
    const auto snapshot = window_snapshot_;
    for (std::size_t i = 0; i < snapshot.widgets.size(); ++i) {
        const auto& slider = snapshot.widgets[i];
        const auto field = setting_volume(upper(leaf(slider.name)));
        if (!field || slider.type != "GuiLook/Slider") continue;
        const auto thumb = resources_->skin().slider_thumb(*resources_, slider,
            settings_draft_.*field, 1.0F, width, height);
        if (!thumb) continue;
        const auto parent = snapshot.source_ids[i];
        if (!slider_thumbs_.count(parent)) {
            UiWidget child;
            child.name = thumb->name;
            child.type = thumb->type;
            const auto id = windows_.create(std::move(child));
            slider_thumbs_[parent] = id;
            windows_.add_child(parent, id);
        }
        const auto id = slider_thumbs_.at(parent);
        const auto before = windows_.revision();
        windows_.set_property(id, "UnifiedPosition", "{{" +
            scalar((thumb->rect.x - slider.rect.x) / slider.rect.width) + ",0},{0,0}}");
        windows_.set_property(id, "UnifiedSize", "{{" + scalar(thumb->rect.width / slider.rect.width) +
            ",0},{" + scalar(thumb->rect.height / slider.rect.height) + ",0}}");
        thumbs_changed = thumbs_changed || before != windows_.revision();
    }
    if (thumbs_changed) {
        window_snapshot_ = windows_.snapshot(width, height, state);
    }
    input_widgets_ = window_snapshot_.widgets;
}
void Frontend::advance(float seconds) {
    if (!std::isfinite(seconds) || seconds < 0) throw std::invalid_argument("invalid frontend delta");
    pointer_clock_ += seconds;
    sync_windows();
    windows_.advance(seconds, [this](UiWindowId id, std::uint8_t button) {
        const UiPointerEvent repeat{UiPointerEventKind::button_down,
            last_pointer_position_[0], last_pointer_position_[1], button, pointer_clock_};
        dispatch_pointer_down(id, repeat, {}, false);
    });
    if (tooltips_ && cached_width_ > 0 && cached_height_ > 0) {
        resolve_windows(cached_width_, cached_height_);
        const auto p = pointer_.position.value_or(std::array<float, 2>{});
        tooltips_->advance(seconds, window_snapshot_, p[0], p[1]);
    }
    if (options_animation_ && options_animation_->visible()) {
        options_animation_->advance(seconds);
        if (!options_animation_->open() && options_animation_->closed())
            dropdown(FrontendPage::pause).detach();
        cached_frame_.reset();
    }
    if (pending_options_exit_ && (!options_animation_ || options_animation_->closed()) && !request_)
        // COptionsMenu::update @0xb8019d requests state(0,0) only after
        // CLOSE. The existing .otc owner saves before leaving the session.
        request_ = FrontendRequest{FrontendCommand::save_and_menu, 0, {}, {}};
    windows_.clean_dead_pool();
}
bool Frontend::has_closing_windows() const noexcept {
    return pending_options_exit_ ||
        (options_animation_ && !options_animation_->open() && !options_animation_->closed());
}
std::vector<DropdownSoundRequest> Frontend::take_dropdown_sounds() {
    return options_animation_ ? options_animation_->consume_sound_requests() :
        std::vector<DropdownSoundRequest>{};
}
FrontendFrame Frontend::compose_frame(int width, int height) {
    FrontendFrame result;
    // Each page contributes windows from the one WindowManager snapshot.
    // Global paint_order keeps overlapping and closing trees in CEGUI order.
    std::vector<FrontendPage> pages;
    if (main_dropdown_.attached()) pages.push_back(FrontendPage::main);
    for (const auto& [page, container] : dropdowns_)
        if (container->attached()) pages.push_back(page);
    // Bind every participating tree before assigning snapshot/paint indices.
    for (const auto page : pages) {
        const char* path = page == FrontendPage::main ? "media/UI/mainmenuframe.layout" :
            page == FrontendPage::pause ? "media/UI/optionsmenu.layout" :
            page == FrontendPage::settings ? "media/UI/settingsmenu.layout" :
            page == FrontendPage::create ? "media/UI/charactercreate.layout" : "media/UI/characterload.layout";
        if (const auto* layout = resources_->layout(path); layout && bound_layouts_[page] != layout) {
            auto& container = dropdown(page);
            container.bind_layout(*layout);
            bound_layouts_[page] = layout;
            if (page != FrontendPage::main)
                for (const auto id : container.resource_roots()) windows_.set_visible(id, true);
        }
    }
    bind_settings_combos();
    resolve_windows(width, height);
    for (const auto page : pages) {
        auto f = build_frame(page, width, height);
        if (page == page_) {
            result.title = std::move(f.title);
            result.notes = std::move(f.notes);
        }
        result.original_layout = result.original_layout || f.original_layout;
        result.decorations.insert(result.decorations.end(), f.decorations.begin(), f.decorations.end());
        result.texts.insert(result.texts.end(), f.texts.begin(), f.texts.end());
        for (auto& button : f.buttons)
            if (!button.supplemental || page == page_) result.buttons.push_back(std::move(button));
    }
    if (comboboxes_) for (const auto& row : comboboxes_->paint(window_snapshot_)) {
        const auto index = window_snapshot_.resolved_index_by_id.at(row.droplist);
        if (!index) continue;
        result.list_items.push_back({resources_->skin().combobox_text_item(
            row.text, row.rect, row.clip, window_snapshot_.widgets[*index].effective_alpha), row.paint_order});
    }
    for (const auto& widget : window_snapshot_.widgets)
        if (widget.visible && widget.type == "GuiLook/Tooltip")
            result.decorations.push_back(widget);
    if (options_animation_) result.dropdown_meshes = options_animation_->draws(width, height);
    return result;
}
FrontendFrame Frontend::frame(int width, int height) {
    if (width <= 0 || height <= 0) throw std::invalid_argument("invalid UI viewport");
    sync_windows();
    if (cached_frame_ && cached_width_ == width && cached_height_ == height &&
        cached_revision_ == windows_.revision()) return pointer_frame(*cached_frame_);
    cached_width_ = width;
    cached_height_ = height;
    ++frame_build_count_;
    auto result = compose_frame(width, height);
    resolve_windows(width, height);
    if (focus_ >= result.buttons.size() || !result.buttons[focus_].enabled ||
        result.buttons[focus_].owner != page_) {
        const auto eligible = std::find_if(result.buttons.begin(), result.buttons.end(), [&](const auto& b) {
            return b.enabled && b.owner == page_;
        });
        focus_ = static_cast<std::size_t>(eligible - result.buttons.begin());
    }
    for (std::size_t i = 0; i < result.buttons.size(); ++i)
        result.buttons[i].focused = i == focus_ && result.buttons[i].owner == page_;
    buttons_ = result.buttons;
    cached_revision_ = windows_.revision();
    cached_frame_ = result;
    if (ordered_pointer_) retarget_pointer();
    return pointer_frame(std::move(result));
}
void Frontend::retarget_pointer() {
    if (retargeting_ || cached_width_ <= 0 || cached_height_ <= 0) return;
    retargeting_ = true;
    try {
        resolve_windows(cached_width_, cached_height_);
        const auto old = windows_.mouse_target();
        const auto target = pointer_.position ? windows_.target_at_position(window_snapshot_,
            (*pointer_.position)[0], (*pointer_.position)[1]) : std::nullopt;
        if (old != target && old && windows_.alive(*old) && windows_.is_button(*old))
            windows_.button_mouse_leave(*old);
        if (old != target && tooltips_) tooltips_->leave();
        windows_.set_mouse_target(target);
        if (old != target && target && pointer_.position && tooltips_)
            tooltips_->enter(*target, window_snapshot_, (*pointer_.position)[0], (*pointer_.position)[1]);
        if (target && windows_.is_button(*target) && pointer_.position)
            windows_.button_mouse_move(*target, window_snapshot_,
                (*pointer_.position)[0], (*pointer_.position)[1]);
    } catch (...) { retargeting_ = false; throw; }
    retargeting_ = false;
}
void Frontend::dispatch_pointer_down(UiWindowId target, const UiPointerEvent& event,
                                      UiPointerDownDecision decision, bool bubble) {
    const auto path = bubble ? windows_.dispatch_path(target) : std::vector<UiWindowId>{target};
    for (const auto id : path) {
        const auto widget = windows_.window(id);
        const auto kind = decision.dispatch_kind(upper(widget.property("WantsMultiClickEvents")) != "FALSE");
        const auto subscribed = [&](bool double_click) {
            auto sub = main_dropdown_.subscription(id);
            if (double_click ? sub.double_click : sub.mouse_down) return true;
            for (const auto& [page, container] : dropdowns_) {
                (void)page;
                sub = container->subscription(id);
                if (double_click ? sub.double_click : sub.mouse_down) return true;
            }
            return false;
        };
        if (kind == UiPointerDispatchKind::triple_click) continue;
        if (kind == UiPointerDispatchKind::double_click) {
            if (!subscribed(true)) continue;
            // CDropdownMenu::onDoubleClick @0xb05e80 is a handled no-op.
            // Continue overrides @0xc334e0: only enums 14..17 and alive saves.
            if (!request_ && page_ == FrontendPage::load && widget.layout_function &&
                static_cast<int>(*widget.layout_function) >= 14 &&
                static_cast<int>(*widget.layout_function) <= 17 && save_index_ < saves_.size() &&
                saves_[save_index_].loadable() && saves_[save_index_].health > 0.0F)
                activate("load");
            return;
        }
        if (event.button == 0 && comboboxes_ && comboboxes_->handles(id) &&
            comboboxes_->pointer_down(id, window_snapshot_, event.x, event.y)) return;
        bool command_handled = false;
        const auto dispatch = [&](UiWindowId receiver) {
            if (request_) return;
            const auto receiver_widget = windows_.window(receiver);
            if (main_dropdown_.subscription(receiver).mouse_down) {
                if (receiver_widget.layout_function)
                    dispatch_main_menu(main_dropdown_.open(), main_dropdown_.closed(),
                        *receiver_widget.layout_function, *this);
                command_handled = true;
                return;
            }
            const auto found = std::find_if(buttons_.begin(), buttons_.end(), [&](const auto& button) {
                return button.widget.name == receiver_widget.name && button.enabled;
            });
            if (found == buttons_.end()) return;
            if (upper(receiver_widget.type).find("CHECKBOX") != std::string::npos) return;
            command_handled = true;
            if (found->owner == FrontendPage::pause &&
                (page_ != FrontendPage::pause || (options_animation_ && !options_animation_->open())))
                return;
            const auto action = found->id;
            if (action.rfind("setting-", 0) == 0 && setting_volume(upper(action.substr(8)))) {
                if (event.button == 0) click(event.x, event.y);
            } else activate(action, receiver_widget.layout_function);
        };
        bool handled = false;
        if (event.button == 0 && windows_.is_button(id)) {
            handled = windows_.is_thumb(id)
                ? windows_.thumb_mouse_down(id, window_snapshot_, event.x, event.y, {})
                : windows_.button_mouse_down(id, window_snapshot_, event.x, event.y, dispatch);
        } else handled = windows_.window_mouse_down(id, event.button, dispatch);
        if (handled || command_handled) return;
    }
}
void Frontend::pointer_event(const UiPointerEvent& event) {
    ordered_pointer_ = true;
    if (event.kind == UiPointerEventKind::leave) pointer_.position.reset();
    else {
        last_pointer_position_ = {event.x, event.y};
        pointer_.position = last_pointer_position_;
    }
    retarget_pointer();
    const auto target = windows_.mouse_target();
    if (event.kind == UiPointerEventKind::leave || event.kind == UiPointerEventKind::move) {
        if (event.kind == UiPointerEventKind::move) {
            if (tooltips_) tooltips_->move(event.x, event.y);
            if (comboboxes_) comboboxes_->pointer_move(window_snapshot_, event.x, event.y,
                                                       pointer_.left_press_origin.has_value());
        }
        if (event.kind == UiPointerEventKind::move && target && windows_.is_thumb(*target)) {
            windows_.thumb_mouse_move(*target, window_snapshot_, event.x, event.y,
                [&](UiWindowId id, float left) {
                    if (request_) return;
                    const auto parent = windows_.window(id).parent;
                    if (parent < 0) return;
                    const auto index = window_snapshot_.resolved_index_by_id.at(parent);
                    if (!index) return;
                    const auto& slider = window_snapshot_.widgets[*index];
                    const auto field = setting_volume(upper(leaf(slider.name)));
                    const auto thumb = window_snapshot_.resolved_index_by_id.at(id);
                    if (field && thumb) {
                        settings_draft_.*field = ui_slider_value_from_thumb(left, slider.rect,
                            window_snapshot_.widgets[*thumb].rect.width);
                        cached_frame_.reset();
                    }
                });
        }
        // Combo hover/selection belongs to the list's renderer state.
        if (comboboxes_) cached_frame_.reset();
        return;
    }
    if (event.button >= 5) return;
    const auto timestamp = event.time_seconds.value_or(pointer_clock_);
    if (event.time_seconds) pointer_clock_ = *event.time_seconds;
    if (event.kind == UiPointerEventKind::button_down) {
        if (event.button == 0) pointer_.left_press_origin = std::array<float, 2>{event.x, event.y};
        const auto decision = pointer_timing_.button_down(event.button, event.x, event.y, timestamp, target);
        if (target) dispatch_pointer_down(*target, event, decision);
        // Portable supplements keep their explicit adapter, outside CEGUI.
        if (const auto index = button_at(event.x, event.y); event.button == 0 &&
            !request_ && index && buttons_[*index].supplemental) {
            const auto action = buttons_[*index].id;
            activate(action);
        }
    } else {
        bool combo = false;
        if (event.button == 0 && target && comboboxes_ && comboboxes_->handles(*target)) {
            combo = true;
            if (const auto selection = comboboxes_->pointer_up(*target, window_snapshot_, event.x, event.y);
                selection && !request_) UiSettingsComboboxes::apply(*selection, settings_draft_);
        }
        if (target && !combo) for (const auto id : windows_.dispatch_path(target)) {
            if (event.button != 0 || !windows_.is_button(id)) {
                windows_.window_mouse_up(id);
                continue;
            }
            if (windows_.is_thumb(id)) {
                static_cast<void>(windows_.thumb_mouse_up(id, window_snapshot_, event.x, event.y));
                break;
            }
            static_cast<void>(windows_.button_mouse_up(id, window_snapshot_, event.x, event.y,
                [&](UiWindowId clicked) {
                    if (request_) return;
                    const auto widget = windows_.window(clicked);
                    if (page_ == FrontendPage::settings &&
                        upper(widget.type).find("CHECKBOX") != std::string::npos)
                        if (const auto field = setting_flag(upper(leaf(widget.name))))
                            settings_draft_.*field = windows_.button_selected(clicked);
                }));
            break;
        }
        // System MouseClicked is distinct from PushButton EventClicked; the
        // current menu subscribes to down/double/selection, not System click.
        static_cast<void>(pointer_timing_.button_up(event.button, event.x, event.y, timestamp, target));
        if (event.button == 0) pointer_.left_press_origin.reset();
        dragging_slider_.clear();
    }
    sync_windows();
    cached_frame_.reset();
}
FrontendFrame Frontend::build_frame(FrontendPage render_page, int width, int height) {
    FrontendFrame frame;
    std::string path, fallback_title;
    switch (render_page) {
    case FrontendPage::main:
        fallback_title = "OPENTORCHLIGHT"; path = "media/UI/mainmenuframe.layout"; break;
    case FrontendPage::create:
        fallback_title = "NEW CHARACTER"; path = "media/UI/charactercreate.layout"; break;
    case FrontendPage::load:
        fallback_title = "LOAD CHARACTER"; path = "media/UI/characterload.layout"; break;
    case FrontendPage::pause:
        fallback_title = "PAUSED"; path = "media/UI/optionsmenu.layout"; break;
    case FrontendPage::settings:
        fallback_title = "SETTINGS"; path = "media/UI/settingsmenu.layout"; break;
    default: buttons_.clear(); return frame;
    }
    std::vector<UiResolvedWidget> widgets;
    try {
        if (const auto *layout = resources_->layout(path)) {
            auto& container = dropdown(render_page);
            if (bound_layouts_[render_page] != layout) {
                container.bind_layout(*layout);
                bound_layouts_[render_page] = layout;
                // Non-main pages retain their existing controller's root show.
                if (render_page != FrontendPage::main)
                    for (const auto id : container.resource_roots()) windows_.set_visible(id, true);
            }
            if (render_page == FrontendPage::main && main_layout_ != layout) {
                // CMainMenu::createMenus calls mapEventHandlers after binding
                // commands. These registrations drive actual resource input.
                main_linux_credits_ = std::any_of(layout->widgets().begin(), layout->widgets().end(),
                    [](const auto& w) { return leaf(w.name) == "CreditFrameB"; });
                main_layout_ = layout;
            }
            // original-code: the five controller menus scale their layout
            // with YRATIO (see ui_screen_scale_for_layout); other pages keep
            // ratio 1 rather than an invented policy.
            const auto policy = ui_screen_scale_for_layout(path);
            const float screen_scale =
                policy ? ui_screen_ratio(width, height, *policy) : 1.0F;
            UiLayoutState state;
            if (render_page == FrontendPage::load)
                state = continue_menu_layout_state(*layout, saves_.size(), scroll_, save_index_,
                    pending_delete_ && *pending_delete_ < saves_.size());
            state.offset_ratio = screen_scale;
            if (render_page == FrontendPage::main) {
                const bool can_continue = std::any_of(saves_.begin(), saves_.end(),
                                                     [](const auto &s) { return s.loadable(); });
                for (const auto &w : layout->widgets()) {
                    const auto name = leaf(w.name);
                    // original-code: createMenus writes these properties after
                    // loadWindowLayout; update drives ContinueLast visibility.
                    // .otc supplies canContinue here; .SVB/mod producer is open.
                    // See research/mainmenu-controller-painter.md.
                    if (name == "DemoVersion" || name == "CharacterModsWarning")
                        state.visibility[w.name] = false;
                    else if (name == "ContinueLast") state.visibility[w.name] = can_continue;
                    else if (name == "CreditFrame") state.visibility[w.name] = show_credits_;
                    else if (name == "CreditFrameB") state.visibility[w.name] = show_credits_b_;
                }
            }
            if (render_page == FrontendPage::settings)
                for (std::size_t i = 0; i < layout->widgets().size(); ++i) {
                    const auto id = container.resource_ids().at(i);
                    if (const auto field = setting_flag(upper(leaf(layout->widgets()[i].name))); field && windows_.is_button(id))
                        windows_.set_button_selected(id, settings_draft_.*field);
                }
            // The manager gives each layout its native-style name prefix;
            // controller references are bound by resource index, not a global
            // unprefixed name lookup (several layouts have a Frame root).
            for (std::size_t i = 0; i < layout->widgets().size(); ++i) {
                const auto& name = layout->widgets()[i].name;
                if (const auto it = state.visibility.find(name); it != state.visibility.end())
                    windows_.set_visible(container.resource_ids().at(i), it->second);
            }
            for (const auto& name : state.move_to_front)
                for (std::size_t i = 0; i < layout->widgets().size(); ++i)
                    if (layout->widgets()[i].name == name)
                        windows_.move_to_front(container.resource_ids().at(i));
            resolve_windows(width, height);
            widgets = window_snapshot_.widgets;
            for (std::size_t i = 0; i < widgets.size(); ++i) {
                const auto chain = windows_.dispatch_path(window_snapshot_.source_ids[i]);
                if (std::find(chain.begin(), chain.end(), container.root()) == chain.end()) {
                    widgets[i].visible = false;
                    widgets[i].callback.clear();
                    widgets[i].layout_function.reset();
                    widgets[i].type = "DefaultWindow";
                }
            }
            frame.original_layout = true;
        }
    } catch (const std::exception &e) {
        status_ = e.what();
    }
    // A resource page gets only its own titles, never a synthetic logo/header.
    if (!frame.original_layout) frame.title = fallback_title;
    std::map<std::string, UiResolvedWidget> originals;
    std::vector<UiResolvedWidget> unsupported;
    std::vector<std::string> actions(widgets.size());
    bool character_name_bound = false;
    std::vector<bool> slot_name_bound(5, false);
    for (std::size_t n = 0; n < widgets.size(); ++n) {
        const auto &w = widgets[n];
        // Retain hidden/disabled known actions in originals so a fallback cannot
        // resurrect a control explicitly hidden/disabled by a resource.
        // Consume mapToFunctions' result, not a second independent string matcher.
        const std::string callback(w.layout_function ? ui_function_name(*w.layout_function) : std::string_view{});
        const auto name = upper(leaf(w.name));
        auto &action = actions[n];
        if (render_page == FrontendPage::main) {
            if (main_dropdown_.subscription(window_snapshot_.source_ids[n]).mouse_down == 0) continue;
            if (callback == "GUINEWGAMEMENU") action = "new";
            else if (callback == "GUICONTINUEGAMEMENU") action = "loads";
            else if (callback == "GUICONTINUEGAME") action = "continue";
            else if (callback == "GUIEXITAPPLICATION") action = "exit";
            else if (callback == "GUISETTINGSMENU") action = "settings";
            else if (callback == "GUISELECTA") action = "credits-a";
            else if (callback == "GUISELECTB") action = "credits-b";
            else if (callback == "GUISELECTC") action = "credits-c";
            else if (callback == "GUISELECTD") action = "credits-d";
        } else if (render_page == FrontendPage::create) {
            if (callback == "GUIBACK") action = "back";
            else if (callback == "GUINEWGAME") action = "create";
            else if (callback == "GUISELECT1")
                for (std::size_t i = 0; i < classes_.size(); ++i)
                    if (name == upper(classes_[i].name)) action = "class-" + number(i);
        } else if (render_page == FrontendPage::load) {
            if (callback == "GUIBACK") action = "back";
            else if (callback == "GUICONTINUEGAME") action = "load";
            else if (callback == "GUISCROLLUP") action = "scroll-up";
            else if (callback == "GUISCROLLDOWN") action = "scroll-down";
            else if (callback == "GUIDELETE1") action = "delete";
            else if (callback == "GUIACCEPT") action = "accept";
            else if (callback == "GUIDECLINE") action = "decline";
            else for (std::size_t i = 0; i < 5; ++i)
                if (callback == "GUISELECT" + number(i + 1)) action = "slot-" + number(scroll_ + i);
        } else if (render_page == FrontendPage::pause && callback == "GUICLOSEMENU") action = "resume";
        else if (render_page == FrontendPage::pause && callback == "GUISETTINGSMENU") action = "settings";
        else if (render_page == FrontendPage::pause && callback == "GUIEXITGAME") action = "exit-game";
        else if (render_page == FrontendPage::settings) {
            if (callback == "GUIACCEPT") action = "apply";
            else if (callback == "GUIDECLINE") action = "decline-settings";
            else {
                const auto kind = upper(w.type);
                if (kind.find("CHECKBOX") != std::string::npos ||
                    kind.find("SLIDER") != std::string::npos ||
                    kind.find("COMBOBOX") != std::string::npos)
                    action = "setting-" + name;
            }
        }
        if (!action.empty()) originals[action] = w;
        else if (!w.callback.empty() && w.visible) unsupported.push_back(w);
    }
    for (std::size_t n = 0; n < widgets.size(); ++n) {
        auto w = widgets[n];
        if (render_page == FrontendPage::main && w.visible && leaf(w.name) == "Credits") {
            w.text = main_menu_credits();
            frame.texts.push_back(std::move(w));
            continue;
        }
        if (render_page == FrontendPage::main && w.visible && leaf(w.name) == "CreditsB") {
            frame.texts.push_back(std::move(w));
            continue;
        }
        if (!w.visible || w.type == "GuiLook/SliderThumb") continue;
        if (!w.callback.empty()) {
            // Keep every main-menu resource window in the paint tree even
            // when several nodes share one command (CreditFrame / Credits).
            // Button entries replace the same node in frontend_paint_list;
            // subscriptions and input targets are independent of that list.
            if (render_page == FrontendPage::main) frame.decorations.push_back(std::move(w));
            continue;
        }
        const auto name = upper(leaf(w.name)), type = upper(w.type);
        const bool static_text = type.find("STATICTEXT") != std::string::npos ||
                                 type.find("ITEMTEXT") != std::string::npos;
        // resource-derived: the create-screen name field is GuiLook/Editbox
        // Name=EditBox (MaxTextLength=12); CHARACTERNAME is kept for layouts
        // that address the field by the legacy name.
        const bool name_entry = render_page == FrontendPage::create &&
                                (name == "CHARACTERNAME" || name == "EDITBOX");
        // Windows with frame/background imagery can have an empty Image.
        if (!w.image.empty() || (!static_text && !name_entry && w.type != "DefaultWindow"))
            frame.decorations.push_back(w);
        if (!static_text && !name_entry) continue;
        if (render_page == FrontendPage::main && leaf(w.name) == "CopyrightInfo")
            // original-code: global CopyrightInfo initialized @0xc4f708 from
            // UTF-32 literal @0xff2d00, applied by createMenus @0xc53560.
            w.text = "(v1.15) Torchlight (C) 2009 Runic Games Inc.";
        if (name_entry) { w.text = name_; character_name_bound = true; }
        // resource-derived: charactercreate.layout ships CharacterClass /
        // CharacterClassDescription with placeholder Text=1; the runtime fills
        // them from the selected UNIT (NAME/DESCRIPTION). Header keeps resource text.
        if (render_page == FrontendPage::create && !classes_.empty()) {
            const auto selected = std::min(class_index_, classes_.size() - 1);
            if (name == "CHARACTERCLASS" && !classes_[selected].name.empty())
                w.text = classes_[selected].name;
            else if (name == "CHARACTERCLASSDESCRIPTION" && !classes_[selected].description.empty())
                w.text = classes_[selected].description;
        }
        if (render_page == FrontendPage::load) {
            if (name == "CHARACTERNAME")
                w.text = save_index_ < saves_.size() ? saves_[save_index_].name : "";
            for (std::size_t i = 0; i < 5; ++i) {
                if (name == "PLAYER" + number(i + 1) + "NAME") {
                    slot_name_bound[i] = true;
                    const auto index = scroll_ + i;
                    w.text = index < saves_.size() ?
                        (saves_[index].name.empty() ? saves_[index].slot : saves_[index].name) : "";
                } else if (name == "PLAYER" + number(i + 1) + "DESC") {
                    // resource-derived from our own checkpoint (level, class,
                    // hardcore). The exact original Desc wording (difficulty
                    // words, playtime, Dead/Retired) stays open.
                    const auto index = scroll_ + i;
                    if (index >= saves_.size())
                        w.text.clear();
                    else if (!saves_[index].loadable())
                        w.text = "PORT SAVE: UNREADABLE";
                    else {
                        const auto &slot = saves_[index];
                        std::string class_name;
                        for (const auto &c : classes_)
                            if (c.guid == slot.class_guid) {
                                class_name = c.name;
                                break;
                            }
                        w.text = "Level " + std::to_string(slot.level) +
                                 (class_name.empty() ? "" : " " + class_name) +
                                 (slot.hardcore ? ", Hardcore" : "");
                    }
                }
            }
        }
        if (w.text.empty() || w.text == "1") continue;
        bool duplicate = false;
        for (auto p = w.parent; p >= 0; p = widgets[static_cast<std::size_t>(p)].parent) {
            const auto &ancestor = widgets[static_cast<std::size_t>(p)];
            if (!actions[static_cast<std::size_t>(p)].empty() && ancestor.text == w.text) {
                duplicate = true; break;
            }
        }
        if (!duplicate) frame.texts.push_back(std::move(w));
    }
    // PORT: portable supplements are not original controls; anchor them below
    // the resolved original rectangles so no recovered button is covered.
    float supplemental_left = -1.0F, supplemental_bottom = 0.0F, supplemental_width = 0.0F;
    const auto consider_anchor = [&](const UiResolvedWidget &w) {
        if (!w.visible || w.rect.width <= 0 || w.rect.height <= 0) return;
        supplemental_left = supplemental_left < 0 ? w.rect.x : std::min(supplemental_left, w.rect.x);
        supplemental_bottom = std::max(supplemental_bottom, w.rect.y + w.rect.height);
        supplemental_width = std::max(supplemental_width, w.rect.width);
    };
    for (const auto &entry : originals) consider_anchor(entry.second);
    for (const auto &w : unsupported) consider_anchor(w);
    std::size_t fallback_row = 0;
    const auto make_button = [&](std::string id, std::string label,
                                  const UiResolvedWidget *source, bool enabled, bool selected) {
        FrontendButton b;
        b.owner = render_page;
        b.id = std::move(id); b.text = std::move(label); b.enabled = enabled; b.selected = selected;
        b.supplemental = source == nullptr;
        if (source) {
            b.widget = *source; b.rect = source->rect; b.font = source->font;
            if (render_page == FrontendPage::settings)
                if (const auto field = setting_volume(upper(leaf(source->name)))) {
                    b.widget.properties["CurrentValue"] = scalar(settings_draft_.*field);
                    b.widget.properties["MaximumValue"] = "1";
                }
            b.enabled = b.enabled && source->enabled;
            if (!source->text.empty() && source->text != "1" && b.id.rfind("slot-", 0) != 0)
                b.text = source->text;
            if (const auto images = resources_->widget_images(source->type)) {
                b.image = images->normal; b.hover_image = images->hover;
                b.pushed_image = images->pushed; b.disabled_image = images->disabled;
            }
            if (!source->image.empty()) b.image = source->image;
            for (auto item : {std::pair<const char *, std::string *>{"NormalImage", &b.image},
                              {"HoverImage", &b.hover_image}, {"PushedImage", &b.pushed_image},
                              {"DisabledImage", &b.disabled_image}}) {
                // An explicitly empty property clears the look's default.
                // It is not the same thing as an absent property.
                const auto property = source->properties.find(item.first);
                if (property != source->properties.end()) *item.second = property->second;
            }
        } else {
            // Explicit portable fallback/supplement; never original layout geometry.
            const float scale = std::min(width / 1024.0F, height / 768.0F);
            if (supplemental_left >= 0) {
                b.rect = {supplemental_left,
                          supplemental_bottom + 18.0F * scale +
                              static_cast<float>(fallback_row++) * 48.0F * scale,
                          supplemental_width, 40.0F * scale};
            } else {
                b.rect = {(frame.original_layout ? 16.0F : 302.0F) * scale,
                          (180.0F + static_cast<float>(fallback_row++) * 48.0F) * scale,
                          (frame.original_layout ? 246.0F : 420.0F) * scale, 40.0F * scale};
            }
            b.widget.rect = b.widget.clip = b.rect;
            b.text = "PORT: " + b.text;
        }
        frame.buttons.push_back(std::move(b));
    };
    const auto add = [&](const std::string &id, std::string label, bool enabled = true,
                         bool selected = false) {
        const auto it = originals.find(id);
        if (it != originals.end() && (!it->second.visible || it->second.rect.width <= 0 ||
                                     it->second.rect.height <= 0 || it->second.clip.width <= 0 ||
                                     it->second.clip.height <= 0)) return;
        make_button(id, std::move(label), it == originals.end() ? nullptr : &it->second,
                    enabled, selected);
    };
    if (render_page == FrontendPage::main) {
        // Tabs are pure resource chrome: without the layout widget there is
        // nothing to anchor, and a portable fallback would steal keyboard
        // focus and pixels on synthetic layouts. Real mainmenuframe always
        // provides TabA (RadioTab 50x14).
        if (originals.find("credits-a") != originals.end()) add("credits-a", "");
        if (originals.find("credits-c") != originals.end()) add("credits-c", "");
        add("new", "NEW CHARACTER");
        // c4af32..c4aff0: an empty list selects the new-character menu.
        add("loads", "LOAD CHARACTER");
        add("continue", "CONTINUE LAST", std::any_of(saves_.begin(), saves_.end(),
                                               [](const auto &s) { return s.loadable(); }));
        add("exit", "EXIT");
        add("settings", "SETTINGS");
        // The main menu's presentation comes from the layout/controller.
        // Save-format limitations are documented alongside the launcher.
    } else if (render_page == FrontendPage::create) {
        for (std::size_t i = 0; i < classes_.size(); ++i)
            add("class-" + number(i), upper(classes_[i].name), true, i == class_index_);
        add("create", "CREATE - NORMAL"); add("back", "BACK");
        if (!character_name_bound) frame.notes.push_back({"PORT NAME: " + name_, true});
        frame.notes.push_back({"PORT: TYPE A-Z / 0-9; BACKSPACE. PET / DIFFICULTY NOT IMPLEMENTED.", false});
    } else if (render_page == FrontendPage::load) {
        for (std::size_t i = scroll_; i < std::min(saves_.size(), scroll_ + 5); ++i) {
            const auto label = slot_name_bound[i - scroll_] ? std::string{} :
                               saves_[i].name.empty() ? saves_[i].slot : saves_[i].name;
            add("slot-" + number(i), label, true, i == save_index_);
        }
        add("load", "LOAD SELECTED", save_index_ < saves_.size() && saves_[save_index_].loadable());
        add("scroll-up", "PREVIOUS", scroll_ > 0);
        add("scroll-down", "NEXT", scroll_ + 5 < saves_.size());
        add("delete", "DELETE", !saves_.empty());
        // original-code: DeleteConfirm pair is visible only while a delete is
        // pending (CContinueGameMenu shows/hides it around deleteCharacter).
        if (pending_delete_ && *pending_delete_ < saves_.size()) {
            add("accept", "DELETE");
            add("decline", "CANCEL");
        }
        add("back", "BACK");
        if (saves_.empty()) frame.notes.push_back({"PORT: NO SAVED CHARACTERS", false});
        else if (save_index_ < saves_.size()) frame.notes.push_back({"PORT SAVE: " + saves_[save_index_].slot, false});
    } else if (render_page == FrontendPage::settings) {
        // Checkboxes and the two original horizontal volume sliders mutate
        // the draft. The application previews audio and commits on Apply.
        for (const auto &widget : widgets) {
            const auto kind = upper(widget.type);
            const auto key = upper(leaf(widget.name));
            if (kind.find("CHECKBOX") != std::string::npos) {
                if (const auto field = setting_flag(key))
                    add("setting-" + key, std::string{}, true, settings_draft_.*field);
                else if (key == "ANTIALIASING")
                    // No clean bool mapping (FSAA levels, needs restart): show
                    // the resource footprint display-only like sliders/lists.
                    add("setting-" + key, std::string{}, false);
            } else if (kind.find("SLIDER") != std::string::npos ||
                       kind.find("COMBOBOX") != std::string::npos) {
                bool supported = kind.find("COMBOBOX") != std::string::npos &&
                    (key == "RESOLUTIONDROPDOWN" || key == "SHADOWDROPDOWN" || key == "PARTICLEDROPDOWN");
                if (const auto field = setting_volume(key))
                    supported = resources_->skin().slider_thumb(*resources_, widget,
                        settings_draft_.*field, 1.0F, width, height).has_value();
                add("setting-" + key, std::string{}, supported);
            }
        }
        add("apply", "APPLY");
        add("decline-settings", "CANCEL");
        frame.notes.push_back(
            {"VIDEO CHANGES TAKE EFFECT AFTER RESTART.", false});
    } else {
        add("resume", "RESUME"); add("settings", "SETTINGS");
        if (originals.count("exit-game")) add("exit-game", "MAIN MENU");
        add("save", "SAVE (.otc)");
        add("save-menu", "SAVE AND MAIN MENU"); add("save-exit", "SAVE AND EXIT");
        frame.notes.push_back({"PORT: PAUSED. .otc WRITE MUST SUCCEED BEFORE LEAVING.", false});
    }
    for (const auto &w : unsupported) {
        make_button("unsupported:" + w.name, w.text == "1" ? "" : w.text, &w, false, false);
    }
    if (!unsupported.empty()) frame.notes.push_back({
        "PORT: DISABLED RESOURCE CONTROLS ARE NOT IMPLEMENTED (SETTINGS / ORIGINAL EXIT / OTHER MENUS).", false});
    if (focus_ >= frame.buttons.size()) focus_ = 0;
    if (!frame.buttons.empty()) {
        for (std::size_t n = 0; n < frame.buttons.size() && !frame.buttons[focus_].enabled; ++n)
            focus_ = (focus_ + 1) % frame.buttons.size();
        if (frame.buttons[focus_].enabled) frame.buttons[focus_].focused = true;
    }
    if (!status_.empty()) frame.notes.push_back({status_, false});
    if (!frame.original_layout) frame.notes.push_back({"PORT FALLBACK: ORIGINAL LAYOUT UNAVAILABLE", false});
    return frame;
}
} // namespace torchlight
