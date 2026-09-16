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
    scroll_ = 0;
}
void Frontend::show_main() {
    buttons_.clear();
    page_ = FrontendPage::main;
    focus_ = 0;
    request_.reset();
    status_.clear();
}
void Frontend::pause() {
    if (page_ == FrontendPage::playing) {
        buttons_.clear();
        page_ = FrontendPage::pause;
        focus_ = 0;
        status_.clear();
    }
}
void Frontend::entered_game() {
    buttons_.clear();
    page_ = FrontendPage::playing;
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
void Frontend::text(char c) {
    if (page_ == FrontendPage::create && name_.size() < 32 &&
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
            else for (std::size_t i = 0; i < 5; ++i)
                if (callback == "GUISELECT" + number(i + 1)) action = "slot-" + number(scroll_ + i);
        } else if (page_ == FrontendPage::pause && callback == "GUICLOSEMENU") action = "resume";
        if (!action.empty()) originals[action] = w;
        else if (!w.callback.empty() && w.visible) unsupported.push_back(w);
    }
    for (std::size_t n = 0; n < widgets.size(); ++n) {
        auto w = widgets[n];
        if (!w.visible || !w.callback.empty()) continue;
        if (!w.image.empty()) frame.decorations.push_back(w);
        const auto name = upper(leaf(w.name)), type = upper(w.type);
        const bool static_text = type.find("STATICTEXT") != std::string::npos ||
                                 type.find("ITEMTEXT") != std::string::npos;
        const bool name_entry = page_ == FrontendPage::create && name == "CHARACTERNAME";
        if (!static_text && !name_entry) continue;
        if (name_entry) { w.text = name_; character_name_bound = true; }
        if (page_ == FrontendPage::load) {
            for (std::size_t i = 0; i < 5; ++i) {
                if (name == "PLAYER" + number(i + 1) + "NAME") {
                    slot_name_bound[i] = true;
                    const auto index = scroll_ + i;
                    w.text = index < saves_.size() ?
                        (saves_[index].name.empty() ? saves_[index].slot : saves_[index].name) : "";
                } else if (name == "PLAYER" + number(i + 1) + "DESC") {
                    // .otc metadata is not an original .SVB description.
                    const auto index = scroll_ + i;
                    w.text = index < saves_.size() ?
                        (saves_[index].loadable() ? "PORT SAVE (.otc)" : "PORT SAVE: UNREADABLE") : "";
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
            for (auto item : {std::pair<const char *, std::string *>{"HoverImage", &b.hover_image},
                              {"PushedImage", &b.pushed_image}, {"DisabledImage", &b.disabled_image}}) {
                const auto value = source->property(item.first);
                if (!value.empty()) *item.second = value;
            }
        } else {
            // Explicit portable fallback/supplement; never original layout geometry.
            const float scale = std::min(width / 1024.0F, height / 768.0F);
            const float x = frame.original_layout ? 16.0F : 302.0F;
            b.rect = {x * scale, (180.0F + static_cast<float>(fallback_row++) * 48.0F) * scale,
                      (frame.original_layout ? 246.0F : 420.0F) * scale, 40.0F * scale};
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
        add("new", "NEW CHARACTER");
        add("loads", "LOAD CHARACTER", !saves_.empty());
        add("continue", "CONTINUE LAST", std::any_of(saves_.begin(), saves_.end(),
                                               [](const auto &s) { return s.loadable(); }));
        add("exit", "EXIT");
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
        add("scroll-down", "NEXT", scroll_ + 5 < saves_.size()); add("back", "BACK");
        if (saves_.empty()) frame.notes.push_back({"PORT: NO SAVED CHARACTERS", false});
        else if (save_index_ < saves_.size()) frame.notes.push_back({"PORT SAVE: " + saves_[save_index_].slot, false});
    } else {
        add("resume", "RESUME"); add("save", "SAVE (.otc)");
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
    buttons_ = frame.buttons;
    return frame;
}
} // namespace torchlight
