#include "torchlight/frontend.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>
using namespace torchlight;
namespace {
void require(bool b,const char*s){if(!b)throw std::runtime_error(s);}
void click(Frontend &f,const std::string&id) {
    const auto frame=f.frame(1024,768);
    const auto b=std::find_if(frame.buttons.begin(),frame.buttons.end(),[&](const auto&v){return v.id==id;});
    require(b!=frame.buttons.end() && b->enabled,"expected resource action absent");
    f.click(b->rect.x+b->rect.width/2,b->rect.y+b->rect.height/2);
}
}
int main(int argc,char**argv) {
    try {
        if(argc!=2)throw std::runtime_error("expected external original pak.zip");
        PakArchive pak(argv[1]); UiResources resources(pak);
        Frontend frontend(resources,{{1,"Destroyer"},{2,"Vanquisher"},{3,"Alchemist"}});
        SaveSlotInfo slot;slot.slot="read-only-probe";slot.name="UI Probe";slot.class_guid=1;
        frontend.set_saves({slot});
        unsigned labels=0;
        const auto inspect=[&](const char*path) {
            const auto *layout=resources.layout(path);
            require(layout!=nullptr,"required original menu layout missing");
            const auto frame=frontend.frame(1024,768);
            require(frame.original_layout && frame.title.empty(),"synthetic title over original layout");
            for(const auto &w:layout->resolve(1024,768)) {
                if(!w.visible || !w.callback.empty() || w.text.empty() || w.text=="1" ||
                   w.type.find("StaticText")==std::string::npos)continue;
                const auto leaf=w.name.substr(w.name.find_last_of('/')==std::string::npos?0:w.name.find_last_of('/')+1);
                // Dynamic .otc names/descriptions are verified in the authored test;
                // no original .SVB metadata is inferred here.
                if(leaf.rfind("Player",0)==0 || leaf=="CharacterName")continue;
                const auto found=std::find_if(frame.texts.begin(),frame.texts.end(),[&](const auto&t){return t.name==w.name;});
                require(found!=frame.texts.end() && found->text==w.text && found->font==w.font,
                        "visible original static label lost or replaced");
                ++labels;
            }
            std::cout<<path<<": texts="<<frame.texts.size()<<" buttons="<<frame.buttons.size()<<'\n';
        };
        inspect("media/UI/mainmenuframe.layout");
        click(frontend,"new");inspect("media/UI/charactercreate.layout");
        frontend.show_main();click(frontend,"loads");inspect("media/UI/characterload.layout");
        frontend.entered_game();frontend.pause();inspect("media/UI/optionsmenu.layout");
        click(frontend,"resume");require(frontend.page()==FrontendPage::playing,"resource pause resume failed");
        require(labels>0,"external resource check did not cover any static labels");
        std::cout<<"PASS: "<<labels<<" external static labels retained; resource mapping only, no original-frame parity\n";
        return 0;
    }catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}
}
