// CGameUI::create phase, a9f89b..aa003e.
#ifndef OTL_GAMEUI_STARTUP_SHEETS_H
#define OTL_GAMEUI_STARTUP_SHEETS_H
#include "startup_fonts.h"
#include <CEGUIWindowManager.h>
namespace gameui_create_detail {
struct SheetState {
    char prefix[0x470];
    CEGUI::Window* sheet;
    CEGUI::Window* loading;
    CEGUI::Window* tipText;
    CEGUI::Window* ingame;
    CEGUI::Window* clickThrough;
    CEGUI::Window* top;
};
typedef char sheet_main[__builtin_offsetof(SheetState,sheet)==0x470?1:-1];
typedef char sheet_loading[__builtin_offsetof(SheetState,loading)==0x478?1:-1];
typedef char sheet_tip[__builtin_offsetof(SheetState,tipText)==0x480?1:-1];
typedef char sheet_ingame[__builtin_offsetof(SheetState,ingame)==0x488?1:-1];
typedef char sheet_click[__builtin_offsetof(SheetState,clickThrough)==0x490?1:-1];
typedef char sheet_top[__builtin_offsetof(SheetState,top)==0x498?1:-1];
inline __attribute__((always_inline)) void createSheet(CEGUI::Window*& destination,const char* sheetName) {
    CEGUI::String prefix("");
    CEGUI::String name(reinterpret_cast<const CEGUI::utf8*>(sheetName));
    CEGUI::String type(reinterpret_cast<const CEGUI::utf8*>("DefaultWindow"));
    destination=CEGUI::WindowManager::getSingleton().createWindow(type,name,prefix);
}
inline __attribute__((always_inline)) void fillSheet(CEGUI::Window* window) {
    window->setSize(CEGUI::UVector2(CEGUI::UDim(1.f,0.f),CEGUI::UDim(1.f,0.f)));
}
inline __attribute__((always_inline)) void createSheets(CGameUI* self,PrefixState& ui,SheetState& sheets,CFileInfo& info) {
    createSheet(sheets.sheet,"Sheet");
    fillSheet(sheets.sheet);
    ui.system->setGUISheet(sheets.sheet);
    sheets.sheet->setRiseOnClickEnabled(false);
    {
        std::wstring path(L"media/ui/loading.layout");
        CFileSystem::getSingleton()->getFileInfo(path,info,false,true,false);
    }
    {
        CEGUI::String name(info.m_sResourceName);
        sheets.loading=CEGUI::WindowManager::getSingleton().loadWindowLayout(name,true);
    }
    self->convertToScreenScale(sheets.loading,false);
    {
        CEGUI::String name("TipText");
        sheets.tipText=sheets.loading->recursiveChildSearch(name);
    }
    createSheet(sheets.ingame,"Ingame UI Sheet");
    fillSheet(sheets.ingame);
    sheets.ingame->setRiseOnClickEnabled(false);
    sheets.ingame->subscribeEvent(CEGUI::Window::EventMouseMove,
        CEGUI::Event::Subscriber(&CGameUI::handle_MouseThrough,self));
    createSheet(sheets.top,"Top UI Sheet");
    fillSheet(sheets.top);
    sheets.top->setRiseOnClickEnabled(false);
    sheets.top->setMousePassThroughEnabled(true);
    {
        CEGUI::String prefix("");
        std::string seed("gui_");
        std::string generated=STRINGS::uniqueName(seed);
        CEGUI::String name(generated);
        CEGUI::String type(reinterpret_cast<const CEGUI::utf8*>("DefaultWindow"));
        sheets.clickThrough=CEGUI::WindowManager::getSingleton().createWindow(type,name,prefix);
    }
    fillSheet(sheets.clickThrough);
    sheets.ingame->addChildWindow(sheets.clickThrough);
    sheets.clickThrough->setRiseOnClickEnabled(false);
    sheets.clickThrough->subscribeEvent(CEGUI::Window::EventMouseButtonDown,
        CEGUI::Event::Subscriber(&CGameUI::handle_ClickThrough,self));
    sheets.clickThrough->moveToBack();
    sheets.clickThrough->setZOrderingEnabled(false);
}
}
#endif
