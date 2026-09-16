#include "torchlight/ui_text.hpp"
#include "torchlight/ui_layout.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace torchlight;
namespace { unsigned checks=0; void require(bool b,const char*s){++checks;if(!b)throw std::runtime_error(s);} }
int main() {
    try {
        require(ui_decode_utf8("AΠЯ\xF0\x9F\x98\x80") == U"AΠЯ\U0001f600", "UTF8 codepoint decoding failed");
        for (const auto *bad : {"\xc0\xaf", "\xed\xa0\x80", "\xf4\x90\x80\x80", "\xff", "\xe2\x82"}) {
            const auto result=ui_decode_utf8(bad);
            require(!result.empty() && result[0]==U'\ufffd', "invalid UTF8 was accepted");
        }
        const auto advance=[](char32_t){return 5.0F;};
        const auto a=ui_text_lines("AA BB\r\nC",15,true,advance);
        require(a.size()==3 && a[0].text==U"AA" && a[1].text==U"BB" && a[2].text==U"C", "word wrap / CRLF wrong");
        const auto b=ui_text_lines("ABCDE",10,true,advance);
        require(b.size()==3 && b[0].width==10 && b[2].text==U"E", "long token splitting failed");
        require(ui_text_lines("ABC",1,false,advance)[0].text==U"ABC", "clipped text was silently changed");
        require(ui_text_lines("",20,true,advance).empty(), "empty label made a line");
        require(ui_text_lines("A",0,true,advance).empty(), "zero width not handled");
        std::string xml="<Window Name='root'><Property Name='UnifiedSize' Value='{{0,100},{0,100}}'/>"
                        "<Window Name='child'><Property Name='UnifiedPosition' Value='{{0,80},{0,90}}'/>"
                        "<Property Name='UnifiedSize' Value='{{0,80},{0,40}}'/>"
                        "<Property Name='HorzFormatting' Value='WordWrapRightAligned'/>"
                        "<Property Name='VertFormatting' Value='BottomAligned'/></Window></Window>";
        const auto ws=UiLayout::parse({xml.begin(),xml.end()}).resolve(1024,768);
        require(ws[1].clip.x==80 && ws[1].clip.width==20 && ws[1].clip.height==10, "parent clip lost");
        require(ws[1].text_style().wrap && ws[1].text_style().horizontal==UiTextHorizontal::right &&
                ws[1].text_style().vertical==UiTextVertical::bottom, "text formatting properties lost");
        std::cout<<checks<<" text decoding / wrapping / clipping checks passed\n"; return 0;
    } catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}
}
