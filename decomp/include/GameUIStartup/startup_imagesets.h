// CGameUI::create phase, aa003f..aa0676.
#ifndef OTL_GAMEUI_STARTUP_IMAGESETS_H
#define OTL_GAMEUI_STARTUP_IMAGESETS_H
#include "startup_sheets.h"
#include <CEGUIImagesetManager.h>
#include <CEGUIImageset.h>
#include <OgreResourceGroupManager.h>
namespace gameui_create_detail {
struct ImagesetState {
    char prefix[0x438];
    CEGUI::Imageset* guiLook;
    TArrayList<std::wstring> itemIconFiles;
    TArrayList<CEGUI::Imageset*> itemImagesets;
    char gap470[0x580-0x470];
    CEGUI::Imageset* statsUI;
    char gap588[0x1310-0x588];
    CEGUI::Imageset* uiIcons;
};
typedef char imagesets_gui[__builtin_offsetof(ImagesetState,guiLook)==0x438?1:-1];
typedef char imagesets_files[__builtin_offsetof(ImagesetState,itemIconFiles)==0x440?1:-1];
typedef char imagesets_items[__builtin_offsetof(ImagesetState,itemImagesets)==0x458?1:-1];
typedef char imagesets_stats[__builtin_offsetof(ImagesetState,statsUI)==0x580?1:-1];
typedef char imagesets_icons[__builtin_offsetof(ImagesetState,uiIcons)==0x1310?1:-1];
inline __attribute__((always_inline)) void findImageset(CEGUI::Imageset*& destination,const char* text) {
    CEGUI::String name(reinterpret_cast<const CEGUI::utf8*>(text));
    destination=CEGUI::ImagesetManager::getSingleton().getImageset(name);
}
inline __attribute__((always_inline)) void loadImagesets(ImagesetState& ui,float nativeWidth) {
    findImageset(ui.statsUI,"StatsMenu_UI");
    ui.statsUI->setNativeResolution(CEGUI::Size(nativeWidth,768.f));
    findImageset(ui.guiLook,"GuiLook");
    ui.guiLook->setNativeResolution(CEGUI::Size(nativeWidth,768.f));
    findImageset(ui.uiIcons,"UIIcons");
    CFileSystem::getSingleton()->getFileList(L"media/ui/itemicons/",ui.itemIconFiles,
        L"*.imageset",false,false,false,false);
    for(unsigned i=0;i<ui.itemIconFiles.size();++i) {
        CFileInfo info;
        const std::wstring& path=ui.itemIconFiles[i];
        CFileSystem::getSingleton()->getFileInfo(path,info,false,true,false);
        if(info.m_bExists) {
          try {
            CEGUI::Imageset* imageset;
            {
                CEGUI::String group(Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
                // Re-read the array: the resolver is allowed to have altered it.
                std::string bytes=STRINGS::StringConvertToUTF8(ui.itemIconFiles[i]);
                // Despite the preceding conversion, the original chooses the
                // byte-widening std::string overload, not String(utf8*).
                CEGUI::String name(bytes);
                imageset=CEGUI::ImagesetManager::getSingleton().createImageset(name,group);
            }
            if(imageset) {
                imageset->setNativeResolution(CEGUI::Size(nativeWidth,768.f));
                ui.itemImagesets.add(imageset);
            }
          } catch(CEGUI::GenericException error) {
            std::string message(reinterpret_cast<const char*>(error.getMessage().c_str()));
            Ogre::LogManager::getSingleton().logMessage(message,Ogre::LML_CRITICAL,false);
          }
        }
    }
}
}
#endif
