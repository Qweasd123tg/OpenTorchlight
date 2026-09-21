#include "torchlight/inventory_events.hpp"
#include "torchlight/ui_inventory.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace torchlight;
namespace {
void require(bool yes, const char* why) { if (!yes) throw std::runtime_error(why); }
using Trace = std::vector<std::string>;
void print(const Trace& trace) {
    std::cout << '[';
    for (std::size_t i=0;i<trace.size();++i) std::cout << (i ? "," : "") << trace[i];
    std::cout << "]\n";
}
struct Tree final : InventoryEventTree {
    struct Row { int parent; std::optional<std::string> value; };
    std::vector<Row> rows;
    Trace trace;
    int fail_node = -1, fail_stage = -1;
    void fail(Node n, int stage) const { if (static_cast<int>(n)==fail_node && stage==fail_stage) throw std::runtime_error("injected"); }
    std::size_t child_count(Node n) const override {
        fail(n,0); std::size_t count=0; for (const auto& row:rows) count+=row.parent==static_cast<int>(n); return count;
    }
    Node child(Node n, std::size_t index) const override {
        for (Node i=0;i<rows.size();++i) if(rows[i].parent==static_cast<int>(n) && index--==0) return i;
        throw std::runtime_error("child out of bounds");
    }
    bool has_click_property(Node n) const override {
        const_cast<Tree*>(this)->trace.push_back("[\"present\","+std::to_string(n)+"]");
        fail(n,1); return rows[n].value.has_value();
    }
    std::string click_property(Node n) const override {
        const_cast<Tree*>(this)->trace.push_back("[\"get\","+std::to_string(n)+"]");
        fail(n,2); return *rows[n].value;
    }
    void subscribe_mouse_down(Node n) override {
        fail(n,3); trace.push_back("[\"subscribe\","+std::to_string(n)+"]");
    }
    void run() { for(Node i=0;i<rows.size();++i) if(rows[i].parent<0) map_inventory_events(*this,i); }
};
struct Sink final : InventoryTabSink {
    Trace trace;
    bool fail_restore=false;
    void select(std::size_t i,bool b) override { trace.push_back("[\"selected\","+std::to_string(i)+","+(b?"true":"false")+"]"); }
    void show(std::size_t i,bool b) override { trace.push_back("[\"visible\","+std::to_string(i)+","+(b?"true":"false")+"]"); }
    void clear_alert(std::size_t i) override { trace.push_back("[\"alert\","+std::to_string(i)+",false]"); }
    void restore_unselected_image(std::size_t i) override {
        if(fail_restore) throw std::runtime_error("injected restore");
        trace.push_back("[\"restore\","+std::to_string(i)+"]");
    }
    void update_layout() override { trace.push_back("[\"update\"]"); }
};
std::optional<std::string> decode(const std::string& text) {
    if(text=="_") return std::nullopt;
    if(text=="-") return std::string{};
    require(text.size()%2==0,"odd hex"); std::string out;
    for(std::size_t i=0;i<text.size();i+=2) out+=static_cast<char>(std::stoul(text.substr(i,2),nullptr,16));
    return out;
}
void probe() {
    std::string kind;
    while(std::cin>>kind) {
        if(kind=="map") {
            Tree t; unsigned n=0; std::cin>>n; require(n<10000,"too many nodes");
            while(n--) {int p;std::string hex;std::cin>>p>>hex;t.rows.push_back({p,decode(hex)});}
            t.run(); print(t.trace);
        } else if(kind=="tab") {int open,f;std::cin>>open>>f;Sink s;dispatch_inventory_tab(open,f,s);print(s.trace);}
        else throw std::runtime_error("unknown probe input");
        require(static_cast<bool>(std::cin),"truncated input");
    }
}
void unit() {
    Tree t; t.rows={{-1,"unknown"},{0,"guiSelect1"},{0,std::string("\0",1)},{-1,""},{-1,std::nullopt}};
    t.run();
    require(t.trace.front()=="[\"present\",1]","not child first");
    require(t.trace[2]=="[\"subscribe\",1]" && t.trace[5]=="[\"subscribe\",2]" &&
            t.trace[8]=="[\"subscribe\",0]","unknown and NUL must subscribe");
    const auto first=t.trace;t.run();
    require(t.trace.size()==2*first.size(),"repeat mapping must not deduplicate");
    for(int stage=1;stage<=3;++stage) {
        Tree f; f.rows={{-1,"guiSelect1"},{0,"guiSelect2"}};f.fail_node=1;f.fail_stage=stage;f.run();
        require(f.trace.back()=="[\"subscribe\",0]","child local failure swallowed parent");
        f.trace.clear();f.fail_node=0;f.run();
        require(f.trace[2]=="[\"subscribe\",1]","parent failure lost child subscription");
    }
    t.fail_node=1;t.fail_stage=0;bool threw=false;
    try{t.run();}catch(const std::runtime_error&){threw=true;}
    require(threw,"traversal error swallowed");
    Sink sink;sink.fail_restore=true;threw=false;
    try{dispatch_inventory_tab(true,15,sink);}catch(const std::runtime_error&){threw=true;}
    require(threw && sink.trace.size()==7,"tab property error swallowed or update called");
    InventoryMenuState menu;
    require(!menu.click_tab(15),"closed menu changes tabs");
    menu.set_open(true,false);require(menu.click_tab(16),"fish rejected");
    require(menu.tab_selected(2)&&menu.container_visible(2)&&menu.restored_image(2),"tab effects not consumed");
    menu.set_open(true,false);require(menu.tab()==InventoryMenuTab::fish,"repeat open resets tab");
    menu.set_open(false,false);menu.set_open(true,false);
    require(menu.tab()==InventoryMenuTab::backpack&&menu.tab_selected(0)&&menu.container_visible(0)&&
            !menu.tab_selected(2)&&!menu.container_visible(2),"fresh open must reset tabs");
}
UiResolvedWidget find(const std::vector<UiResolvedWidget>& ws,std::string name) {
    for(const auto& w:ws) if(w.name==name || (w.name.size()>name.size() && w.name.substr(w.name.size()-name.size()-1)=="/"+name)) return w;
    throw std::runtime_error("missing widget "+name);
}
void assets(const char* path) {
    PakArchive archive(path);UiResources resources(archive);UiInventoryPreview ui(resources);InventoryMenuState menu;
    require(ui.subscriptions().size()==3,"original inventory must subscribe exactly three tab properties");
    require(ui.frame(1024,768,menu).widgets.empty(),"closed preview visible");
    menu.set_open(true,false);
    for(const auto size: {std::array<int,2>{1024,768},std::array<int,2>{800,600},std::array<int,2>{1280,720}}) {
        for(int tab=14;tab<=16;++tab) {
            menu.click_tab(tab);const auto frame=ui.frame(size[0],size[1],menu);
            require(frame.targets.size()==4,"three tabs plus explicit Close");
            for(int i=0;i<3;++i) {
                const auto& w=find(frame.widgets,i==0?"TabBackpack":i==1?"TabSpell":"TabFish");
                require(w.image==(i==tab-14?"set:ui2 image:StandardTab":"set:ui2 image:StandardTabInactive"),"selected image wrong");
                const auto press=ui.press(frame,w.rect.x+w.rect.width/2,w.rect.y+w.rect.height/2);
                require(press.action==InventoryUiAction::tab&&press.function==14+i,"real pointer tab mapping wrong");
            }
            const auto& close=find(frame.targets,"Close");
            require(ui.press(frame,close.rect.x+close.rect.width/2,close.rect.y+close.rect.height/2).action==InventoryUiAction::close,"explicit close not wired");
            const auto& visible=find(frame.widgets,tab==14?"Slot1":tab==15?"Slot22":"Slot43");
            require(visible.visible,"selected container not visible");
            require(frame.widgets.size()==53,"98 XML windows minus two 22-window containers and SlotGlow");
            auto disabled=frame;for(auto& w:disabled.targets) w.enabled=false;
            require(ui.press(disabled,close.rect.x+1,close.rect.y+1).action==InventoryUiAction::none,"disabled close dispatches");
        }
    }
}
} // namespace
int main(int argc,char**argv) {
    try {
        if(argc==2&&std::string(argv[1])=="--probe") probe();
        else if(argc==3&&std::string(argv[1])=="--pak") assets(argv[2]);
        else unit();
        if(argc!=2 || std::string(argv[1])!="--probe") std::cout<<"PASS inventory events\n";
        return 0;
    } catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}
}
