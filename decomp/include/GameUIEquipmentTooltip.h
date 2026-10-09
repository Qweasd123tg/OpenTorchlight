#ifndef GAMEUI_EQUIPMENT_TOOLTIP_H
#define GAMEUI_EQUIPMENT_TOOLTIP_H
#include "EquipmentTooltip.h"
#include "Equipment.h"
#include "Character.h"
#include "Inventory.h"
#include "SubMenu.h"
#include "GameGlobals.h"
#include "StringTranslate.h"
#include "StringUtilities.h"
#include <CEGUI.h>
namespace equipment_tooltip {
struct Size {float width,height;};
struct UIFields {char prefix[0x4f0];CSubMenu* merchant;};
inline __attribute__((always_inline)) CEGUI::String utf8(const std::string& value){return CEGUI::String(reinterpret_cast<const unsigned char*>(value.c_str()));}
inline __attribute__((always_inline)) float maxSecond(float a,float b){return a>b?a:b;}
inline __attribute__((always_inline)) Size measure(CEGUI::Font* font,const std::string& text,float bound,int formatting,float leading=2.0f){
 float lineHeight=font->getFontHeight();if(leading!=0.0f)lineHeight+=leading;
 CEGUI::Rect area(0,0,bound,1000.0f);
 Size size;size.width=font->getFormattedTextExtent(utf8(text),area,static_cast<CEGUI::TextFormatting>(formatting),1.0f)+4.0f;
 int lines=static_cast<int>(font->getFormattedLineCount(utf8(text),area,static_cast<CEGUI::TextFormatting>(formatting),1.0f));size.height=float(lines)*lineHeight;return size;
}
inline __attribute__((always_inline)) void size(CEGUI::Window*& window,const Size& s){window->setSize(CEGUI::UVector2(CEGUI::UDim(0,s.width),CEGUI::UDim(0,s.height)));}
inline __attribute__((always_inline)) void text(CEGUI::Window*& window,const std::string& s){window->setText(utf8(s));}
inline __attribute__((always_inline)) void moveY(CEGUI::Window*& window,float y){
 CEGUI::UDim x=window->getPosition().d_x+CEGUI::UDim(0,0);
 window->setPosition(CEGUI::UVector2(x,CEGUI::UDim(0,y+0.0f)));
}
inline __attribute__((always_inline)) void addRow(CEGUI::Window*& window,const std::string& value,float& width,float& y){
 Size s=measure(window->getFont(true),value,1000.0f,2);size(window,s);text(window,value);moveY(window,y);
 width=maxSecond(s.width+40.0f,width);y=(s.height+4.0f)+y;
}
inline __attribute__((always_inline)) void whiteOrRed(CEGUI::Window*& window,bool red){
 window->setProperty("TextColour",CEGUI::PropertyHelper::colourToString(CEGUI::colour(1.0f,red?0.0f:1.0f,red?0.0f:1.0f,1.0f)));
}
inline __attribute__((always_inline)) void caption(CEGUI::Window*& window,const std::wstring& label){text(window,STRINGS::StringConvertToUTF8(std::wstring(label.c_str())));}
inline __attribute__((always_inline)) void description(CEquipmentTooltip* tip,const std::wstring& value,bool warning,float& width,float& y){
 std::string bytes=STRINGS::StringConvertToUTF8(value);
 // The original uses the defense-requirement font for this description too.
 Size s=measure(tip->m_pDefenseRequirement->getFont(true),bytes,width*1.5f,4);
 size(tip->m_pDescription,s);text(tip->m_pDescription,bytes);
 tip->m_pDescription->setProperty("TextColour",warning?"FFff3636":"FFd6d6d7");moveY(tip->m_pDescription,y);
 width=maxSecond(s.width+40.0f,width);y=(s.height+4.0f)+y;
}
}
// Placement portion of showEquipmentTooltip, recovered from0xaa822f onward.
// Candidate only; no behavior accepted until the complete entry comparison.
namespace equipment_tooltip {
struct PointerFields {
    char prefix[0x12d0];
    long mouseX;
    long mouseY;
};
inline __attribute__((always_inline)) void place(CGameUI* ui,CEquipmentTooltip* tip,
                                                CEquipmentTooltip* first,
                                                CEquipmentTooltip* second)
{
    unsigned viewportWidth=static_cast<unsigned>(static_cast<long>(ui->getWindowWidth()));
    unsigned viewportHeight=static_cast<unsigned>(static_cast<long>(ui->getWindowHeight()));
    CEGUI::UDim ownWidth=tip->m_pRoot->getWidth();
    CEGUI::UDim ownHeight=tip->m_pRoot->getHeight();
    PointerFields& pointer=*reinterpret_cast<PointerFields*>(ui);
    long mouseY=pointer.mouseY;
    float width=ownWidth.asAbsolute(1.0f);
    long mouseX=pointer.mouseX;
    float x;
    if(first) {
        CEGUI::UDim firstWidth=first->m_pRoot->getWidth();
        first->m_pRoot->getHeight(); // The original performs this unused query.
        float firstX=first->m_pRoot->getPosition().d_x.d_offset;
        x=(firstX-width)-52.0f;
        if(0.0f>x-26.0f)x=(firstX+firstWidth.asAbsolute(1.0f))+52.0f;
    } else x=(float(mouseX)-width)-39.0f;
    float height=ownHeight.asAbsolute(1.0f);
    float y;
    if(second) {
        second->m_pRoot->getWidth(); // Also deliberately queried, despite no use.
        CEGUI::UDim secondHeight=second->m_pRoot->getHeight();
        float secondY=second->m_pRoot->getPosition().d_y.d_offset;
        float secondX=second->m_pRoot->getPosition().d_x.d_offset;
        y=(secondY-height)-26.0f;
        if(0.0f>y-26.0f)y=(secondY+secondHeight.asAbsolute(1.0f))+26.0f;
        if((y+height)+26.0f>float(viewportHeight)) {
            y=second->m_pRoot->getPosition().d_y.d_offset;
            float currentX=second->m_pRoot->getPosition().d_x.d_offset;
            if(currentX>first->m_pRoot->getPosition().d_x.d_offset) {
                float nextX=second->m_pRoot->getPosition().d_x.d_offset;
                float nextWidth=second->m_pRoot->getWidth().asAbsolute(1.0f);
                x=(nextX+nextWidth)+52.0f;
            } else x=(secondX-width)-52.0f;
        }
    } else {
        if((x+width)+26.0f>float(viewportWidth))x=float(viewportWidth)-(width+26.0f);
        y=(float(mouseY)-height)-26.0f;
        if((height+y)+26.0f>float(viewportHeight))y=float(viewportHeight)-(height+26.0f);
        if(0.0f>x-26.0f)x=float(pointer.mouseX)+26.0f;
        if(y-26.0f<0.0f)y=26.0f; // Unordered values retain their original NaN.
    }
    tip->m_pRoot->setPosition(CEGUI::UVector2(CEGUI::UDim(0,x),CEGUI::UDim(0,y)));
}
}

namespace equipment_tooltip {
typedef char size_tooltip[sizeof(CEquipmentTooltip)==0x98?1:-1];
typedef char offset_m_iCachedItemGuid[__builtin_offsetof(CEquipmentTooltip,m_iCachedItemGuid)==16?1:-1];
typedef char offset_m_pParent[__builtin_offsetof(CEquipmentTooltip,m_pParent)==24?1:-1];
typedef char offset_m_pRoot[__builtin_offsetof(CEquipmentTooltip,m_pRoot)==32?1:-1];
typedef char offset_m_pItemName[__builtin_offsetof(CEquipmentTooltip,m_pItemName)==40?1:-1];
typedef char offset_m_pItemType[__builtin_offsetof(CEquipmentTooltip,m_pItemType)==48?1:-1];
typedef char offset_m_pItemHanded[__builtin_offsetof(CEquipmentTooltip,m_pItemHanded)==56?1:-1];
typedef char offset_m_pBigDPS[__builtin_offsetof(CEquipmentTooltip,m_pBigDPS)==64?1:-1];
typedef char offset_m_pDPS[__builtin_offsetof(CEquipmentTooltip,m_pDPS)==72?1:-1];
typedef char offset_m_pStats[__builtin_offsetof(CEquipmentTooltip,m_pStats)==80?1:-1];
typedef char offset_m_pEffects[__builtin_offsetof(CEquipmentTooltip,m_pEffects)==88?1:-1];
typedef char offset_m_pLevelRequirement[__builtin_offsetof(CEquipmentTooltip,m_pLevelRequirement)==96?1:-1];
typedef char offset_m_pStrengthRequirement[__builtin_offsetof(CEquipmentTooltip,m_pStrengthRequirement)==104?1:-1];
typedef char offset_m_pDexterityRequirement[__builtin_offsetof(CEquipmentTooltip,m_pDexterityRequirement)==112?1:-1];
typedef char offset_m_pMagicRequirement[__builtin_offsetof(CEquipmentTooltip,m_pMagicRequirement)==120?1:-1];
typedef char offset_m_pDefenseRequirement[__builtin_offsetof(CEquipmentTooltip,m_pDefenseRequirement)==128?1:-1];
typedef char offset_m_pDescription[__builtin_offsetof(CEquipmentTooltip,m_pDescription)==136?1:-1];
typedef char offset_m_pPrice[__builtin_offsetof(CEquipmentTooltip,m_pPrice)==144?1:-1];
typedef char pointer_mouse_x[__builtin_offsetof(PointerFields,mouseX)==0x12d0?1:-1];
typedef char pointer_mouse_y[__builtin_offsetof(PointerFields,mouseY)==0x12d8?1:-1];
typedef char merchant_offset[__builtin_offsetof(UIFields,merchant)==0x4f0?1:-1];
}
#endif
