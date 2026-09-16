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
    saves_ = std::move(saves);
    save_index_ = std::min(save_index_, saves_.empty() ? 0 : saves_.size() - 1);
    scroll_ = 0;
}
void Frontend::show_main() {
    page_ = FrontendPage::main;
    focus_ = 0;
    request_.reset();
    status_.clear();
}
void Frontend::pause() {
    if (page_ == FrontendPage::playing) {
        page_ = FrontendPage::pause;
        focus_ = 0;
        status_.clear();
    }
}
void Frontend::entered_game() {
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
        if (buttons_[i - 1].enabled && buttons_[i - 1].rect.contains(x, y)) {
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
    FrontendFrame frame;
    std::string path;
    switch (page_) {
    case FrontendPage::main:
        frame.title = "OPENTORCHLIGHT";
        path = "media/UI/mainmenuframe.layout";
        break;
    case FrontendPage::create:
        frame.title = "NEW CHARACTER";
        path = "media/UI/charactercreate.layout";
        break;
    case FrontendPage::load:
        frame.title = "LOAD CHARACTER";
        path = "media/UI/characterload.layout";
        break;
    case FrontendPage::pause:
        frame.title = "PAUSED";
        break;
    default:
        buttons_.clear();
        return frame;
    }
    std::vector<UiResolvedWidget> widgets;
    if (!path.empty())
        try {
            if (const auto *layout = resources_->layout(path)) {
                widgets = layout->resolve(width, height);
                frame.original_layout = true;
            }
        } catch (const std::exception &e) {
            status_ = e.what();
        }
    std::map<std::string, UiRect> originals;
    std::map<std::string, std::string> original_text, original_font, original_type;
    for (const auto &w : widgets) {
        if (!w.visible)
            continue;
        const auto callback = upper(w.callback), name = upper(leaf(w.name));
        std::string action;
        if (page_ == FrontendPage::main) {
            if (callback == "GUINEWGAMEMENU")
                action = "new";
            else if (callback == "GUICONTINUEGAMEMENU")
                action = "loads";
            else if (callback == "GUICONTINUEGAME")
                action = "continue";
            else if (callback == "GUIEXITAPPLICATION")
                action = "exit";
        } else if (page_ == FrontendPage::create) {
            if (callback == "GUIBACK")
                action = "back";
            else if (callback == "GUINEWGAME")
                action = "create";
            else if (callback == "GUISELECT1")
                for (std::size_t i = 0; i < classes_.size(); ++i)
                    if (name == upper(classes_[i].name))
                        action = "class-" + number(i);
        } else if (page_ == FrontendPage::load) {
            if (callback == "GUIBACK")
                action = "back";
            else if (callback == "GUICONTINUEGAME")
                action = "load";
            else if (callback == "GUISCROLLUP")
                action = "scroll-up";
            else if (callback == "GUISCROLLDOWN")
                action = "scroll-down";
            else
                for (std::size_t i = 0; i < 5; ++i)
                    if (callback == "GUISELECT" + number(i + 1))
                        action = "slot-" + number(scroll_ + i);
        }
        if (!action.empty() && w.enabled && w.rect.width > 0 && w.rect.height > 0) {
            originals[action] = w.rect;
            original_text[action] = w.text;
            original_font[action] = w.font;
            original_type[action] = w.type;
        }
        if (w.callback.empty() && !w.image.empty())
            frame.decorations.push_back(w);
    }
    std::size_t row = 0;
    const auto add = [&](std::string id, std::string label, bool enabled = true,
                         bool selected = false) {
        // Standalone fallback / supplemental controls, never claimed as CEGUI skin parity.
        const float scale = std::min(width / 1024.0F, height / 768.0F);
        UiRect rect{width * .5F - 210 * scale, 140 * scale + static_cast<float>(row++) * 48 * scale,
                    420 * scale, 40 * scale};
        if (const auto it = originals.find(id); it != originals.end())
            rect = it->second;
        if (const auto it = original_text.find(id);
            it != original_text.end() && !it->second.empty() && it->second != "1")
            label = it->second;
        FrontendButton button{std::move(id), std::move(label), {}, {}, {}, rect, enabled, false,
                              selected};
        if (const auto it = original_type.find(id); it != original_type.end()) {
            if (const auto images = resources_->widget_images(it->second)) {
                button.image = images->normal;
                button.hover_image = images->hover;
            }
        }
        if (const auto it = original_font.find(id); it != original_font.end())
            button.font = it->second;
        frame.buttons.push_back(std::move(button));
    };
    if (page_ == FrontendPage::main) {
        add("new", "NEW CHARACTER");
        add("loads", "LOAD CHARACTER", !saves_.empty());
        add("continue", "CONTINUE LAST",
            std::any_of(saves_.begin(), saves_.end(), [](const auto &s) { return s.loadable(); }));
        add("exit", "EXIT");
        frame.notes.push_back(
            {"NORMAL ONLY | ORIGINAL LAYOUTS WHEN AVAILABLE | PORT SAVE FORMAT", false});
    } else if (page_ == FrontendPage::create) {
        for (std::size_t i = 0; i < classes_.size(); ++i)
            add("class-" + number(i), upper(classes_[i].name), true, i == class_index_);
        add("create", "CREATE - NORMAL");
        add("back", "BACK");
        frame.notes.push_back({"NAME: " + name_, true});
        frame.notes.push_back(
            {"TYPE A-Z / 0-9; BACKSPACE TO EDIT. PET AND DIFFICULTY OPTIONS NOT IMPLEMENTED.",
             false});
    } else if (page_ == FrontendPage::load) {
        for (std::size_t i = scroll_; i < std::min(saves_.size(), scroll_ + 5); ++i)
            add("slot-" + number(i),
                saves_[i].name.empty()
                    ? saves_[i].slot
                    : saves_[i].name + (saves_[i].loadable() ? "" : " [UNREADABLE]"),
                true, i == save_index_);
        add("load", "LOAD SELECTED", save_index_ < saves_.size() && saves_[save_index_].loadable());
        add("scroll-up", "PREVIOUS", scroll_ > 0);
        add("scroll-down", "NEXT", scroll_ + 5 < saves_.size());
        add("back", "BACK");
        if (saves_.empty())
            frame.notes.push_back({"NO SAVED CHARACTERS", false});
        else if (save_index_ < saves_.size())
            frame.notes.push_back({"SAVE: " + saves_[save_index_].slot, false});
    } else {
        add("resume", "RESUME");
        add("save", "SAVE");
        add("save-menu", "SAVE AND MAIN MENU");
        add("save-exit", "SAVE AND EXIT");
        frame.notes.push_back(
            {"PAUSED: NO SIMULATION ADVANCE. DISK WRITE MUST SUCCEED BEFORE LEAVING.", false});
    }
    if (focus_ >= frame.buttons.size())
        focus_ = 0;
    if (!frame.buttons.empty())
        frame.buttons[focus_].focused = true;
    if (!status_.empty())
        frame.notes.push_back({status_, false});
    if (frame.original_layout)
        frame.notes.push_back(
            {"PROTOTYPE CONTROLS / FONT; RESOURCE RECTANGLES AND SUPPORTED IMAGES", false});
    if (!frame.original_layout)
        frame.notes.push_back(
            {"PROTOTYPE UI: ORIGINAL LAYOUT MISSING OR THIS PAGE IS PORT-SPECIFIC", false});
    buttons_ = frame.buttons;
    return frame;
}
} // namespace torchlight
