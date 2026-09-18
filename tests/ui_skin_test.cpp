#include "torchlight/ui_skin.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <cctype>
using namespace torchlight;
namespace {
unsigned checks=0;
void require(bool v,const std::string& s){++checks;if(!v)throw std::runtime_error(s);}
void eq(float a,float b,const char* why){require(std::abs(a-b)<1e-5F,why);}
UiResolvedWidget widget(const char* type){UiResolvedWidget w;w.name="fixture";w.type=type;w.rect={40,40,80,64};w.clip={0,0,256,192};w.has_clip=true;return w;}
}
int main(int argc,char**argv){try{
    if(argc!=2&&argc!=3)throw std::runtime_error("usage: ui_skin_test pak.zip [original]");
    PakArchive pak(argv[1]);UiResources r(pak);auto& skin=r.skin();
    if(argc==3){
        auto w=widget("GuiLook/WeaponSwitch");auto base=skin.compile(r,w,{},1024,768);auto selected=skin.compile(r,w,{false,false,true},1024,768);
        require(base.handled&&base.diagnostics.empty(),"original WeaponSwitch baseline");
        require(selected.diagnostics.empty(),"original WeaponSwitch selected diagnostics");
        require(base.draws.size()==1&&selected.draws.size()==2,"WeaponSwitch must overlay selected mark, not replace base");
        auto im=r.image("set:ui2 image:WeaponSwitchChecked");require(bool(im),"selected image missing");
        eq(selected.draws[1].source.x,im->x,"wrong selected image UV");
        w=widget("GuiLook/ItemTooltip");w.text="text";auto tooltip=skin.compile(r,w,{},1024,768);
        for(const auto& d:tooltip.diagnostics)std::cerr<<d<<"\n";
        require(tooltip.handled&&tooltip.diagnostics.empty(),"tooltip frame unsupported");
        require(tooltip.draws.size()>1,"tooltip lost frame");
        
        // File-wide metadata: at least one real image carries a nonzero offset.
        const auto offset_left=r.image("set:GuiLook image:WindowLeftEdge");
        const auto offset_right=r.image("set:GuiLook image:WindowRightEdge");
        require(offset_left&&offset_right,"source frame edges missing");
        eq(offset_left->offset_x,4,"left edge offset lost");
        eq(offset_right->offset_x,-5,"right edge offset lost");
        unsigned layouts=0,compiled=0;
        for(const auto&e:pak.entries()){
            std::string n=e.name;for(auto&c:n)c=char(std::tolower(static_cast<unsigned char>(c)));
            if(n.rfind("media/ui/",0)!=0||n.size()<7||n.substr(n.size()-7)!=".layout")continue;
            const auto* l=r.layout(e.name);if(!l)continue;++layouts;
            for(const auto& x:l->resolve(1024,768)){
                
                const auto f=skin.compile(r,x,{},1024,768);if(f.handled)++compiled;
                for(const auto&q:f.draws)require(std::isfinite(q.destination.x)&&std::isfinite(q.destination.y),"non-finite real draw");
            }
        }
        require(layouts==35,"original layout count changed");require(compiled>800,"too few original windows compiled");
        std::cout<<"original layouts="<<layouts<<" handled widgets="<<compiled<<"\n";
    }else{
        auto w=widget("Test/Toggle");auto a=skin.compile(r,w,{},256,192);
        require(a.handled&&a.diagnostics.empty()&&a.draws.size()==1,"normal toggle");eq(a.draws[0].source.x,0,"normal image");
        a=skin.compile(r,w,{false,false,true},256,192);require(a.draws.size()==2,"selected needs 2 layers");eq(a.draws[0].source.x,0,"selected lost base");eq(a.draws[1].source.x,16,"selected mark missing");
        a=skin.compile(r,w,{true,true,true},256,192);require(a.states[0]=="SelectedHover","pushed state fallback");eq(a.draws[0].source.x,8,"hover base");
        w.enabled=false;a=skin.compile(r,w,{false,false,true},256,192);require(a.handled&&a.draws.empty(),"empty disabled state resurrected");
        w=widget("Test/Frame");a=skin.compile(r,w,{},256,192);require(a.diagnostics.empty()&&a.draws.size()==9,"nine source frame pieces");
        eq(a.draws[0].destination.width,8,"corner stretched");eq(a.draws[4].destination.width,64,"edge length");eq(a.draws.back().destination.width,64,"background insets");
        w.properties["FrameColours"]="tl:FFFF0000 tr:FF00FF00 bl:FF0000FF br:FFFFFFFF";
        auto first=skin.compile(r,w,{},256,192);w.rect.x+=20;w.rect.y+=10;
        auto moved=skin.compile(r,w,{},256,192);
        require(first.draws.size()==9&&moved.draws.size()==9,"gradient frame missing");
        for(std::size_t i=0;i<first.draws.size();++i)require(first.draws[i].colours==moved.draws[i].colours,"window translation changed cached gradient");
        w=widget("Test/Mixed");w.text="HELLO";a=skin.compile(r,w,{},256,192);
        require(a.draws.size()==10&&a.draws.back().kind==UiSkinDraw::Kind::text,"RenderCache must put frame images before same-window text");
        w=widget("Test/Label");w.text="SHOULD NOT DRAW";a=skin.compile(r,w,{},256,192);require(a.handled&&a.draws.empty(),"unreferenced text leaked into state");
        w=widget("Test/Operator");a=skin.compile(r,w,{},256,192);require(a.diagnostics.empty(),"operator failed");eq(a.draws[0].destination.x,43,"sibling operand must replace root");eq(a.draws[0].destination.y,46,"nested operator must add");
        w=widget("Test/Image");w.image="set:Fixture image:Offset";w.effective_alpha=.5F;
        w.properties["ImageColours"]="tl:FFFF0000 tr:FF00FF00 bl:FF0000FF br:FFFFFFFF";
        a=skin.compile(r,w,{},256,192);for(const auto& d:a.diagnostics)std::cerr<<d<<"\n";require(a.diagnostics.empty()&&a.draws.size()==1,"image compile");eq(a.draws[0].destination.x,37,"negative half offset");eq(a.draws[0].destination.y,42,"positive half offset");eq(a.draws[0].colours[1][1],1,"vertex green");eq(a.draws[0].colours[0][3],.5F,"effective alpha");
        a=skin.compile(r,w,{},512,384);eq(a.draws[0].destination.x,35,"scaled offset");eq(a.draws[0].destination.width,80,"destination scaled twice");
        w.clip={40,40,20,20};a=skin.compile(r,w,{},256,192);eq(a.draws[0].destination.x,40,"clipping before offset");eq(a.draws[0].destination.width,20,"image clip width");
        w.clip={0,0,0,0};a=skin.compile(r,w,{},256,192);require(a.draws.empty(),"empty clip ignored");
        w=widget("Test/Image");w.image="set:Fixture image:Red";w.rect={40,40,21,13};w.properties["HorzFormatting"]="Tiled";w.properties["VertFormatting"]="Tiled";
        a=skin.compile(r,w,{},256,192);require(a.diagnostics.empty()&&a.draws.size()==6,"tiling dimensions");eq(a.draws.back().destination.width,5,"last tile squeezed");eq(a.draws.back().source.width,5,"last tile UV not cropped");
        w.properties["HorzFormatting"]="invented";a=skin.compile(r,w,{},256,192);require(!a.diagnostics.empty()&&a.draws.empty(),"unknown format silently guessed");
        eq(ui_pixel_aligned(-2.5F),-3,"round away from zero");eq(ui_pixel_aligned(-.4F),0,"round near zero");require(!std::signbit(ui_pixel_aligned(0)),"negative zero differs from original");
        const std::string xml="<GUILayout><Window Name='parent'><Property Name='Alpha' Value='0.5'/><Window Name='a'><Property Name='Alpha' Value='0.5'/></Window><Window Name='b'><Property Name='Alpha' Value='0.6'/><Property Name='InheritsAlpha' Value='False'/></Window></Window></GUILayout>";
        auto v=UiLayout::parse({xml.begin(),xml.end()}).resolve(256,192);eq(v[1].effective_alpha,.25F,"inherited alpha");eq(v[2].effective_alpha,.6F,"InheritsAlpha=False");
    }
    std::cout<<"PASS "<<checks<<" skin checks; resource/compiler boundary, not complete game UI\n";return 0;
}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
