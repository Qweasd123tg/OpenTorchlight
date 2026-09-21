#include "torchlight/frontend.hpp"
#include "torchlight/ui_skin.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
namespace {
void require(bool b, const char *message) { if (!b) throw std::runtime_error(message); }
std::string leaf(const std::string &s) { return s.substr(s.find_last_of('/') == s.npos ? 0 : s.find_last_of('/') + 1); }
bool has(const FrontendFrame &frame, const std::string &name) {
    const auto paint = frontend_paint_list(frame);
    return std::any_of(paint.begin(), paint.end(), [&](const auto &p) { return leaf(p.widget.name) == name; });
}
void click(Frontend &ui, const std::string &id) {
    const auto frame = ui.frame(1024,768);
    const auto it = std::find_if(frame.buttons.begin(), frame.buttons.end(), [&](const auto &b) { return b.id == id; });
    require(it != frame.buttons.end(), "missing menu target");
    ui.click(it->rect.x + it->rect.width/2, it->rect.y + it->rect.height/2);
}
}
int main(int argc, char **argv) { try {
    require(argc == 2, "expected external pak.zip");
    PakArchive pak(argv[1]); UiResources resources(pak);
    Frontend ui(resources, {{1,"Destroyer"}});
    auto frame = ui.frame(1024,768);
    require(frame.original_layout && frame.notes.empty(), "main layout has diagnostic presentation chrome");
    require(!has(frame,"DemoVersion") && !has(frame,"CharacterModsWarning"), "createMenus visibility writes lost");
    require(!has(frame,"ContinueLast"), "update must hide Continue when adapter has no save");
    require(!has(frame,"CreditFrame") && !has(frame,"CreditFrameB"), "closed credit windows rendered");
    require(has(frame,"TabB") && has(frame,"TabTextB"), "Linux credit tab absent");
    const auto inspect = [&](const FrontendFrame &f) {
        const auto paint = frontend_paint_list(f);
        require(std::is_sorted(paint.begin(), paint.end(), [](const auto &a, const auto &b) {
            return a.widget.paint_order < b.widget.paint_order;
        }), "painter order differs from resolved window order");
        for (const auto &item : paint) {
            const auto &w = item.widget;
            if (w.type == "DefaultWindow") continue;
            UiSkinState state;
            if (item.button) {
                const auto &b=f.buttons[*item.button];
                state={b.focused&&b.enabled,b.selected&&b.enabled,b.selected};
            }
            const auto skin = resources.skin().compile(resources,w,state,1024,768);
            for (const auto &d : skin.diagnostics) std::cerr << w.name << ": " << d << '\n';
            require(skin.handled && skin.diagnostics.empty(), "main-menu window needs an unreviewed skin fallback");
            for (const auto &d : skin.draws)
                require(d.colours[0]==d.colours[1] && d.colours[0]==d.colours[2] && d.colours[0]==d.colours[3],
                        "main-menu colour exceeds GLES flat-tint adapter");
        }
    };
    inspect(frame);
    const auto count = ui.frame_build_count();
    const auto start = std::chrono::steady_clock::now();
    for (int i=0;i<1000;++i) static_cast<void>(ui.frame(1024,768));
    const auto us=std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()-start).count();
    require(ui.frame_build_count()==count, "idle presentation rebuilt");
    SaveSlotInfo save; save.slot="read-only-probe"; save.class_guid=1;
    ui.set_saves({save}); frame=ui.frame(1024,768);
    require(has(frame,"ContinueLast"), "canContinue adapter update not delivered");
    save.error="unreadable"; ui.set_saves({save});
    require(!has(ui.frame(1024,768),"ContinueLast"), "invalid save leaves stale Continue");
    for (const auto &[open, close, pane, text] : {
            std::array<const char *,4>{"credits-a","credits-b","CreditFrame","Credits"},
            std::array<const char *,4>{"credits-c","credits-d","CreditFrameB","CreditsB"}}) {
        click(ui,open); frame=ui.frame(1024,768); inspect(frame);
        require(has(frame,pane) && has(frame,text), "credit root/child did not inherit open state");
        const auto paint=frontend_paint_list(frame);
        auto parent=std::find_if(paint.begin(),paint.end(),[&](const auto &p){return leaf(p.widget.name)==pane;});
        auto child=std::find_if(paint.begin(),paint.end(),[&](const auto &p){return leaf(p.widget.name)==text;});
        require(parent<child, "credit text painted behind its backing window");
        require(child->widget.text.find(std::string(text)=="CreditsB" ? "OutOfOrder Games" : "Designed by Runic Games")
                    != std::string::npos, "credit window exists but its content was lost");
        require(child->widget.text.find("|c")==std::string::npos, "inline control code leaked through plain-text adapter");
        click(ui,close); require(!has(ui.frame(1024,768),pane), "credit close left stale frame");
    }
    static_cast<void>(ui.frame(640,480)); const auto resized=ui.frame_build_count();
    static_cast<void>(ui.frame(640,480)); require(ui.frame_build_count()==resized, "stable resize rebuilt");
    std::cout << "PASS: reviewed controller properties -> resolved tree -> per-window skin commands; "
                 "1000 cached frame copies " << us << " us (host metric, not desktop FPS or original-frame parity)\n";
    return 0;
} catch (const std::exception &e) { std::cerr << e.what() << '\n'; return 1; } }
