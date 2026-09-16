#include "torchlight/ui_layout.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace torchlight;
namespace { unsigned checks=0; void require(bool b,const char*s){++checks;if(!b)throw std::runtime_error(s);} }
int main(int argc,char**argv) {
    try {
        if(argc!=2)throw std::runtime_error("expected generated font fixture");
        PakArchive pak(argv[1]); UiResources resources(pak);
        auto *font=resources.font("Fixture");
        require(font && font->valid(), "real FreeType fixture did not load");
        const auto initial=font->atlas_revision();
        require(font->glyph(U'A')!=nullptr && font->atlas_revision()>initial,"rasterization revision absent");
        const auto first=font->atlas_revision();
        const float width=font->glyph(U'A')->width;
        require(width>0,"empty authored A glyph");
        require(font->atlas_revision()==first,"cached glyph dirtied atlas");
        font->notify_screen_size(1024,768);
        require(font->atlas_revision()==first,"unchanged resolution reset atlas");
        require(font->glyph(U'B')!=nullptr && font->atlas_revision()>first,"new glyph not marked dirty");
        require(font->glyph(U'Π') && font->glyph(U'Π')->width>0,"Unicode glyph absent");
        font->notify_screen_size(512,384);
        require(font->glyph(U'A') && font->glyph(U'A')->width<width,"resize reused wrong metrics");
        font->notify_screen_size(1024,768);
        require(font->glyph(U'A') && font->glyph(U'A')->width==width,"resize roundtrip changed glyph");
        const auto reset=font->atlas_revision();
        font->notify_screen_size(std::numeric_limits<float>::quiet_NaN(),768);
        require(font->atlas_revision()==reset,"NaN screen altered state");
        font->notify_screen_size(std::numeric_limits<float>::max(),768);
        require(!font->valid(),"oversize dimension not rejected before integer cast");
        font->notify_screen_size(1024,768);
        require(font->valid() && font->glyph(U'A'),"font did not recover from invalid size");
        const auto &atlas=font->atlas_rgba();
        require(std::any_of(atlas.begin(),atlas.end(),[](auto x){return x!=0;}),"CPU atlas empty");
        std::cout<<checks<<" real FreeType / authored atlas checks passed; not original CEGUI parity\n";return 0;
    }catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}
}
