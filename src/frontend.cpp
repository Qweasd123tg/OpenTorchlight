#include "torchlight/frontend.hpp"
#include <algorithm>
#include <cctype>
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
// original-code data: main-menu credit roll, rodata 0xbf2e30..0xbf313f of the
// pinned ELF (headers "Designed by Runic Games", "Voice Talents",
// "Additional QA/Artwork", "Built with Ogre3d, CEGUI, ParticleUniverse, and
// FMOD"). Inline |c..|u colour markup is stripped: inline spans stay open.
// Newline joins are inferred (single setText into one ItemText); the exact
// separator trace stays open.
std::string main_menu_credits() {
    static const char *const lines[] = {
        "Designed by Runic Games",
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
        "Voice Talents",
        "Lani Minella - Sam Mowry",
        "Eric Newsome - Tim Simmons",
        "Marc Biagi - Bill Corkery",
        "Mark Rose - Dave Rivas",
        "Additional QA",
        "Nichole Wright - Jeremy Powers",
        "Additional Artwork",
        "ArtCoding - Interserv",
        "Built with Ogre3d, CEGUI, ParticleUniverse, and FMOD",
    };
    std::string out;
    for (const char *line : lines) {
        if (!out.empty()) out += '\n';
        out += line;
    }
    return out;
}
} // namespace
Frontend::Frontend(UiResources &r, std::vector<FrontendClass> c)
    : resources_(&r), classes_(std::move(c)) {
    if (classes_.empty())
        throw std::invalid_argument("no frontend classes");
    for (const auto &p : classes_)
        if (p.guid == 0 || p.name.empty())
            throw std::invalid_argument("invalid frontend class");
}
void Frontend::set_saves(std::vector<SaveSlotInfo> saves) {
    buttons_.clear();
    saves_ = std::move(saves);
    save_index_ = std::min(save_index_, saves_.empty() ? 0 : saves_.size() - 1);
    pending_delete_.reset();
    scroll_ = 0;
}
void Frontend::show_main() {
    buttons_.clear();
    page_ = FrontendPage::main;
    focus_ = 0;
    pending_delete_.reset();
    request_.reset();
    status_.clear();
}
void Frontend::pause() {
    if (page_ == FrontendPage::playing) {
        buttons_.clear();
        page_ = FrontendPage::pause;
        focus_ = 0;
        pending_delete_.reset();
        status_.clear();
    }
}
void Frontend::entered_game() {
    buttons_.clear();
    page_ = FrontendPage::playing;
    pending_delete_.reset();
    request_.reset();
    status_.clear();
}
void Frontend::error(std::string message) {
    status_ = std::move(message);
    request_.reset();
}
void Frontend::saved(FrontendCommand command) {
    request_.reset();
    status_ = "SAVE COMPLETE";
    if (command == FrontendCommand::save_and_menu)
        show_main();
    else if (command == FrontendCommand::save_and_quit)
        page_ = FrontendPage::quit;
}
void Frontend::removed() {
    request_.reset();
    pending_delete_.reset();
    status_ = "SAVE DELETED";
}
void Frontend::applied() {
    request_.reset();
    settings_clean_ = settings_draft_;
    status_ = "SETTINGS SAVED";
}
void Frontend::sync_settings(DisplaySettings settings) {
    settings_clean_ = settings;
    settings_draft_ = settings;
}
void Frontend::leave_settings() {
    settings_draft_ = settings_clean_;
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
// Sliders/comboboxes and FSAA have no clean bool mapping and stay display-only.
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
} // namespace
void Frontend::text(char c) {
    // resource-derived: charactercreate.layout EditBox MaxTextLength=12.
    if (page_ == FrontendPage::create && name_.size() < 12 &&
        ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ' ||
         c == '-' || c == '_'))
        name_ += c;
}
void Frontend::key(FrontendKey key) {
    if (request_)
        return;
    if (key == FrontendKey::back) {
        if (page_ == FrontendPage::pause)
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
        if (focus_ < buttons_.size() && buttons_[focus_].enabled)
            activate(buttons_[focus_].id);
        return;
    }
    const bool forward = key == FrontendKey::next;
    for (std::size_t n = 0; n < buttons_.size(); ++n) {
        focus_ = forward ? (focus_ + 1) % buttons_.size()
                         : (focus_ + buttons_.size() - 1) % buttons_.size();
        if (buttons_[focus_].enabled)
            break;
    }
}
void Frontend::click(float x, float y) {
    if (request_)
        return;
    for (std::size_t i = buttons_.size(); i > 0; --i)
        if (buttons_[i - 1].enabled && buttons_[i - 1].rect.contains(x, y) &&
            buttons_[i - 1].widget.clip.contains(x, y)) {
            focus_ = i - 1;
            activate(buttons_[i - 1].id);
            return;
        }
}
void Frontend::activate(const std::string &id) {
    const auto previous_page = page_;
    if (id == "new") {
        page_ = FrontendPage::create;
        focus_ = 0;
        status_.clear();
    } else if (id == "loads") {
        page_ = FrontendPage::load;
        focus_ = 0;
        status_.clear();
    } else if (id == "back")
        show_main();
    else if (id == "exit")
        page_ = FrontendPage::quit;
    else if (id == "resume")
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
            *pending_delete_ < saves_.size())
            request_ = FrontendRequest{FrontendCommand::remove, 0, {},
                                       saves_[*pending_delete_].slot};
    } else if (id == "decline") {
        if (page_ == FrontendPage::load) {
            pending_delete_.reset();
            status_.clear();
        }
    } else if (id == "credits-a") {
        // original-code: CMainMenu::onClick toggles the two fullscreen credit
        // panes (A/B pane @+0xe8, C/D pane @+0xf0). Pane 1 content is the exact
        // rodata roll below; pane 2 content (likely active mods, cf. update()
        // getEnabledModNames) stays open, so C/D stay known-inert.
        if (page_ == FrontendPage::main) show_credits_ = true;
    } else if (id == "credits-b") {
        if (page_ == FrontendPage::main) show_credits_ = false;
    } else if (id == "credits-c" || id == "credits-d") {
        // Routed so the tabs stop masquerading as unsupported controls; the
        // second pane has no proven content yet and stays closed.
        if (page_ == FrontendPage::main) show_credits_b_ = false;
    } else if (id == "settings") {
        if (page_ == FrontendPage::main || page_ == FrontendPage::pause) {
            buttons_.clear();
            settings_draft_ = settings_clean_;
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
}
std::optional<FrontendRequest> Frontend::take_request() {
    auto result = std::move(request_);
    request_.reset();
    return result;
}
FrontendFrame Frontend::frame(int width, int height) {
    if (width <= 0 || height <= 0) throw std::invalid_argument("invalid UI viewport");
    FrontendFrame frame;
    std::string path, fallback_title;
    switch (page_) {
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
            widgets = layout->resolve(width, height);
            frame.original_layout = true;
        }
    } catch (const std::exception &e) { status_ = e.what(); }
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
        const auto callback = upper(w.callback), name = upper(leaf(w.name));
        auto &action = actions[n];
        if (page_ == FrontendPage::main) {
            if (callback == "GUINEWGAMEMENU") action = "new";
            else if (callback == "GUICONTINUEGAMEMENU") action = "loads";
            else if (callback == "GUICONTINUEGAME") action = "continue";
            else if (callback == "GUIEXITAPPLICATION") action = "exit";
            else if (callback == "GUISETTINGSMENU") action = "settings";
            else if (callback == "GUISELECTA") action = "credits-a";
            else if (callback == "GUISELECTB") action = "credits-b";
            else if (callback == "GUISELECTC") action = "credits-c";
            else if (callback == "GUISELECTD") action = "credits-d";
        } else if (page_ == FrontendPage::create) {
            if (callback == "GUIBACK") action = "back";
            else if (callback == "GUINEWGAME") action = "create";
            else if (callback == "GUISELECT1")
                for (std::size_t i = 0; i < classes_.size(); ++i)
                    if (name == upper(classes_[i].name)) action = "class-" + number(i);
        } else if (page_ == FrontendPage::load) {
            if (callback == "GUIBACK") action = "back";
            else if (callback == "GUICONTINUEGAME") action = "load";
            else if (callback == "GUISCROLLUP") action = "scroll-up";
            else if (callback == "GUISCROLLDOWN") action = "scroll-down";
            else if (callback == "GUIDELETE1") action = "delete";
            else if (callback == "GUIACCEPT") action = "accept";
            else if (callback == "GUIDECLINE") action = "decline";
            else for (std::size_t i = 0; i < 5; ++i)
                if (callback == "GUISELECT" + number(i + 1)) action = "slot-" + number(scroll_ + i);
        } else if (page_ == FrontendPage::pause && callback == "GUICLOSEMENU") action = "resume";
        else if (page_ == FrontendPage::pause && callback == "GUISETTINGSMENU") action = "settings";
        else if (page_ == FrontendPage::settings) {
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
        // Credit panes carry their toggle callback on the text widget itself;
        // show them only while their tab state is open (both CreditFrames
        // start Visible=False in the layout).
        if (page_ == FrontendPage::main && !w.callback.empty()) {
            const auto pane = upper(leaf(w.name));
            if (pane == "CREDITS" && show_credits_) {
                auto open = w;
                open.text = main_menu_credits();
                frame.texts.push_back(std::move(open));
            }
            continue;
        }
        if (!w.visible || !w.callback.empty()) continue;
        if (!w.image.empty()) frame.decorations.push_back(w);
        const auto name = upper(leaf(w.name)), type = upper(w.type);
        const bool static_text = type.find("STATICTEXT") != std::string::npos ||
                                 type.find("ITEMTEXT") != std::string::npos;
        // resource-derived: the create-screen name field is GuiLook/Editbox
        // Name=EditBox (MaxTextLength=12); CHARACTERNAME is kept for layouts
        // that address the field by the legacy name.
        const bool name_entry = page_ == FrontendPage::create &&
                                (name == "CHARACTERNAME" || name == "EDITBOX");
        if (!static_text && !name_entry) continue;
        if (name_entry) { w.text = name_; character_name_bound = true; }
        // resource-derived: charactercreate.layout ships CharacterClass /
        // CharacterClassDescription with placeholder Text=1; the runtime fills
        // them from the selected UNIT (NAME/DESCRIPTION). Header keeps resource text.
        if (page_ == FrontendPage::create && !classes_.empty()) {
            const auto selected = std::min(class_index_, classes_.size() - 1);
            if (name == "CHARACTERCLASS" && !classes_[selected].name.empty())
                w.text = classes_[selected].name;
            else if (name == "CHARACTERCLASSDESCRIPTION" && !classes_[selected].description.empty())
                w.text = classes_[selected].description;
        }
        if (page_ == FrontendPage::load) {
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
        b.id = std::move(id); b.text = std::move(label); b.enabled = enabled; b.selected = selected;
        b.supplemental = source == nullptr;
        if (source) {
            b.widget = *source; b.rect = source->rect; b.font = source->font;
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
    if (page_ == FrontendPage::main) {
        // Tabs are pure resource chrome: without the layout widget there is
        // nothing to anchor, and a portable fallback would steal keyboard
        // focus and pixels on synthetic layouts. Real mainmenuframe always
        // provides TabA (RadioTab 50x14).
        if (originals.find("credits-a") != originals.end()) add("credits-a", "");
        add("new", "NEW CHARACTER");
        add("loads", "LOAD CHARACTER", !saves_.empty());
        add("continue", "CONTINUE LAST", std::any_of(saves_.begin(), saves_.end(),
                                               [](const auto &s) { return s.loadable(); }));
        add("exit", "EXIT");
        add("settings", "SETTINGS");
        frame.notes.push_back({"PORT: NORMAL ONLY; SAVES USE .otc, NOT ORIGINAL .SVB", false});
    } else if (page_ == FrontendPage::create) {
        for (std::size_t i = 0; i < classes_.size(); ++i)
            add("class-" + number(i), upper(classes_[i].name), true, i == class_index_);
        add("create", "CREATE - NORMAL"); add("back", "BACK");
        if (!character_name_bound) frame.notes.push_back({"PORT NAME: " + name_, true});
        frame.notes.push_back({"PORT: TYPE A-Z / 0-9; BACKSPACE. PET / DIFFICULTY NOT IMPLEMENTED.", false});
    } else if (page_ == FrontendPage::load) {
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
    } else if (page_ == FrontendPage::settings) {
        // resource-derived: settingsmenu.layout checkboxes toggle the live
        // draft; sliders/comboboxes show the draft value but stay disabled
        // (drag/dropdown interaction stays open). Apply persists the file.
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
                // The looks define no TextComponent: the original renders no
                // value text here (drag/dropdown interaction stays open), so
                // the box alone marks the control footprint. Headers from the
                // layout name the rows.
                add("setting-" + key, std::string{}, false);
            }
        }
        add("apply", "APPLY");
        add("decline-settings", "CANCEL");
        frame.notes.push_back(
            {"PORT: VIDEO CHANGES NEED A RESTART; SLIDERS, LISTS AND FSAA ARE DISPLAY-ONLY.", false});
    } else {
        add("resume", "RESUME"); add("settings", "SETTINGS"); add("save", "SAVE (.otc)");
        add("save-menu", "SAVE AND MAIN MENU"); add("save-exit", "SAVE AND EXIT");
        frame.notes.push_back({"PORT: PAUSED. .otc WRITE MUST SUCCEED BEFORE LEAVING.", false});
    }
    for (const auto &w : unsupported) {
        make_button("unsupported:" + w.name, w.text == "1" ? "" : w.text, &w, false, false);
    }
    // original-code: the open credit pane is a fullscreen AlwaysOnTop overlay
    // closed by clicking it (guiSelectB). Its layout source stays invisible,
    // so the close target is an explicit topmost button, not invented geometry:
    // it covers exactly the viewport the pane covers.
    if (page_ == FrontendPage::main && show_credits_) {
        FrontendButton close;
        close.id = "credits-b";
        close.rect = {0, 0, static_cast<float>(width), static_cast<float>(height)};
        close.widget.rect = close.widget.clip = close.rect;
        close.enabled = true;
        frame.buttons.push_back(std::move(close));
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
    buttons_ = frame.buttons;
    return frame;
}
} // namespace torchlight
