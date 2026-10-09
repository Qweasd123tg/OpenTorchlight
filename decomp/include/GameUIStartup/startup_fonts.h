// CGameUI::create scheme/font setup, including first-scheme recovery.
// Original normal path a9ec98..a9f899. CFileInfo belongs to the complete caller
// and must survive the later layout/resource phases, through entry completion.
#ifndef OTL_GAMEUI_STARTUP_FONTS_H
#define OTL_GAMEUI_STARTUP_FONTS_H
#include "startup_prefix.h"
#include "FileSystem.h"
#include <CEGUIFont.h>
#include <CEGUIFontManager.h>
#include <CEGUISchemeManager.h>
#include <CEGUIExceptions.h>
#include <elements/CEGUITooltip.h>
namespace gameui_create_detail {
// The game's modified font extends the stock SDK layout. These are only the
// members directly evidenced by assignments in create; no complete class claim.
struct FontMarkupState {
    char prefix[0x368];
    CEGUI::String colourMarker;
    CEGUI::String underlineMarker;
    bool markupEnabled;
};
typedef char font_colour_offset[__builtin_offsetof(FontMarkupState,colourMarker)==0x368?1:-1];
typedef char font_underline_offset[__builtin_offsetof(FontMarkupState,underlineMarker)==0x418?1:-1];
typedef char font_markup_offset[__builtin_offsetof(FontMarkupState,markupEnabled)==0x4c8?1:-1];
inline __attribute__((always_inline)) void resolveScheme(CFileInfo& info,const wchar_t* path) {
    {
        std::wstring name(path);
        CFileSystem::getSingleton()->getFileInfo(name,info,false,true,false);
    }
    CEGUI::String group("");
    CEGUI::String resource(info.m_sResourceName);
    CEGUI::SchemeManager::getSingleton().loadScheme(resource,group);
}
inline __attribute__((always_inline)) void loadSchemes(CFileInfo& info) {
    try {resolveScheme(info,L"media/ui/guilookskin.scheme");}
    catch(CEGUI::GenericException error) {
        std::string message(reinterpret_cast<const char*>(error.getMessage().c_str()));
        Ogre::LogManager::getSingleton().logMessage(message,Ogre::LML_CRITICAL,false);
    }
    {
        CEGUI::String name("GuiLook");
        CEGUI::SchemeManager::getSingleton().getScheme(name);
    }
    resolveScheme(info,L"media/ui/windowslook.scheme");
}
inline __attribute__((always_inline)) CEGUI::Font* findFont(const char* name) {
    // The original uses the UTF-8 overload, even for these ASCII names.
    CEGUI::String text(reinterpret_cast<const CEGUI::utf8*>(name));
    return CEGUI::FontManager::getSingleton().getFont(text);
}
inline __attribute__((always_inline)) void configureFontMarkup(PrefixState& ui) {
    {
        CEGUI::String name(reinterpret_cast<const CEGUI::utf8*>("Serif"));
        ui.system->setDefaultFont(name);
    }
    const char* names[]={"Serif","SerifBig","SerifHuge","SerifSmall"};
    for(unsigned i=0;i<4;++i) {
        FontMarkupState& font=*reinterpret_cast<FontMarkupState*>(findFont(names[i]));
        font.colourMarker=CEGUI::String("|c");
        font.underlineMarker=CEGUI::String("|u");
        font.markupEnabled=true;
    }
}
inline __attribute__((always_inline)) float configureTooltipAndFontSizes(PrefixState& ui,float initialAspect) {
    {
        CEGUI::String name("GuiLook/Tooltip");
        ui.system->setDefaultTooltip(name);
    }
    CEGUI::Tooltip* tooltip=ui.system->getDefaultTooltip();
    tooltip->setAlwaysOnTop(true);
    tooltip->setHoverTime(0.f);
    tooltip->setDisplayTime(0.f);
    tooltip->activate();
    tooltip->setMousePassThroughEnabled(true);
    const float nativeWidth=static_cast<float>(static_cast<int>(initialAspect*768.f));
    ui.system->getDefaultFont()->setNativeResolution(CEGUI::Size(nativeWidth,768.f));
    // SerifHuge is deliberately absent from this second list in the original.
    const char* names[]={"FrizQuadrata","FrizQuadrataBig","FrizQuadrataSmall","SerifBig","Serif","SerifSmall"};
    for(unsigned i=0;i<6;++i) {
        CEGUI::Font* font=findFont(names[i]);
        font->setNativeResolution(CEGUI::Size(nativeWidth,768.f));
    }
    return nativeWidth;
}
}
#endif
