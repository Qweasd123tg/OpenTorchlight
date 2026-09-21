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
        require(ui_font_uses_inline_colours("Serif") && ui_font_uses_inline_colours("SerifBig") &&
                ui_font_uses_inline_colours("SerifHuge") && ui_font_uses_inline_colours("SerifSmall") &&
                !ui_font_uses_inline_colours("FrizQuadrata"), "font inline-colour allowlist wrong");
        const auto markup = ui_text_lines("A|cFF112233BC|uD",100,false,advance,true);
        require(markup.size() == 1 && markup[0].text == U"ABCD" && markup[0].colors.size() == 4,
                "inline tags were not removed");
        require(!markup[0].colors[0].has_value() && markup[0].colors[1] == 0xff112233U &&
                markup[0].colors[2] == 0xff112233U && !markup[0].colors[3].has_value(),
                "inline colour/reset state wrong");
        const auto truncated = ui_text_lines("A|cFF",100,false,advance,true);
        require(truncated[0].text == U"A|cFF" && truncated[0].colors.size() == 5,
                "truncated colour tag was not literal");
        const auto malformed = ui_text_lines("A|cGGGGGGGGB",100,false,advance,true);
        require(malformed[0].text == U"AB" && malformed[0].colors[1] == 0U,
                "full malformed colour payload was not consumed");
        const auto wrapped_markup = ui_text_lines("|cFF112233AB",5,true,advance,true);
        require(wrapped_markup.size() == 2 && wrapped_markup[0].colors[0] == 0xff112233U &&
                !wrapped_markup[1].colors[0].has_value(),
                "colour leaked across wrapped physical lines");
        const auto utf_markup = ui_text_lines("|cFF112233\xCE\xA9",100,false,advance,true);
        require(utf_markup[0].text == U"Ω" && utf_markup[0].colors[0] == 0xff112233U,
                "UTF8 inline colour failed");
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
