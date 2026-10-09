// CGameUI::create platform, display, sound and renderer setup.
// Original ASM: a9e4a0..a9ec93.
#ifndef OTL_GAMEUI_STARTUP_PREFIX_H
#define OTL_GAMEUI_STARTUP_PREFIX_H
#include "GameUI.h"
#include "SDL.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
#include "MasterResourceManager.h"
#include "SoundBank.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "OgreCEGUIRenderer.h"
#include <OgreLogManager.h>
#include <CEGUISystem.h>
#include <vector>
namespace gameui_create_detail {
struct PrefixState {
    char prefix[0x18];
    Ogre::SceneManager* scene;
    char gap20[0x78-0x20];
    CSettings* settings;
    char gap80[0x428-0x80];
    CEGUI::OgreCEGUIRenderer* renderer;
    CEGUI::System* system;
    char gap438[0x4d0-0x438];
    Ogre::RenderWindow* renderWindow;
    char gap4D8[0x16a8-0x4d8];
    CSoundBank* soundBank;
    char gap16B0[0x19f0-0x16b0];
    std::vector<SDL_Cursor*> cursors;
};
typedef char prefix_full_size[sizeof(PrefixState)==0x1a08?1:-1];
typedef char prefix_scene[__builtin_offsetof(PrefixState,scene)==0x18?1:-1];
typedef char prefix_settings[__builtin_offsetof(PrefixState,settings)==0x78?1:-1];
typedef char prefix_renderer[__builtin_offsetof(PrefixState,renderer)==0x428?1:-1];
typedef char prefix_system[__builtin_offsetof(PrefixState,system)==0x430?1:-1];
typedef char prefix_window[__builtin_offsetof(PrefixState,renderWindow)==0x4d0?1:-1];
typedef char prefix_bank[__builtin_offsetof(PrefixState,soundBank)==0x16a8?1:-1];
typedef char prefix_cursors[__builtin_offsetof(PrefixState,cursors)==0x19f0?1:-1];
typedef char sound_guid_offset[__builtin_offsetof(CSoundData,m_iGuid)==0x20?1:-1];
typedef char renderer_size[sizeof(CEGUI::OgreCEGUIRenderer)==0x2c8?1:-1];
typedef char system_size[sizeof(CEGUI::System)==0x258?1:-1];
inline __attribute__((always_inline)) void createCursors(PrefixState& ui) {
    std::string application=STRINGS::StringConvertToUTF8(FILESYSTEM::GetApplicationPath());
    ui.cursors.resize(5,static_cast<SDL_Cursor*>(NULL));
    const char* files[]={"icons/pointer.bmp","icons/hourglass.bmp","icons/attack.bmp","icons/pointerident.bmp"};
    for(unsigned i=0;i<4;++i) {
        SDL_Surface* surface=SDL_LoadBMP_RW(SDL_RWFromFile((application+files[i]).c_str(),"rb"),1);
        SDL_Cursor*& cursor=ui.cursors[i];
        cursor=SDL_CreateColorCursor(surface,0,0);
        if(i==3) {
            SDL_Cursor*& duplicate=ui.cursors[4];
            duplicate=SDL_CreateColorCursor(surface,0,0);
        }
        SDL_FreeSurface(surface);
    }
}
inline __attribute__((always_inline)) float logDisplay(CGameUI* self) {
    float originalAspect=self->getAspectRatio();
    {
        std::string height=STRINGS::GetValueAsString(self->getWindowHeight());
        std::string width=STRINGS::GetValueAsString(self->getWindowWidth());
        std::string message="GAMEUI AspectRatio message - "+width+" x "+height;
        Ogre::LogManager::getSingleton().logMessage(message,Ogre::LML_CRITICAL,false);
    }
    std::string message="GAMEUI AspectRatio message AR - "+STRINGS::GetValueAsString(self->getAspectRatio());
    Ogre::LogManager::getSingleton().logMessage(message,Ogre::LML_CRITICAL,false);
    return originalAspect;
}
inline __attribute__((always_inline)) void createSounds(PrefixState& ui) {
    CSoundManager* manager=CMasterResourceManager::getSingleton()->m_pSoundManager;
    ui.soundBank=new CSoundBank(*manager,false);
    CSoundBankDataInformation* data=CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
    const wchar_t* names[]={L"GOLDBUY",L"ERROR",L"REVEAL",L"ASSIGNSKILL"};
    const int identifiers[]={23,24,36,30};
    for(unsigned i=0;i<4;++i) {
        CSoundData* sound=data->getSoundDataObject(names[i]);
        if(sound)ui.soundBank->addSample(identifiers[i],sound->m_iGuid);
    }
}
inline __attribute__((always_inline)) void createRenderer(PrefixState& ui) {
    ui.renderer=new CEGUI::OgreCEGUIRenderer(ui.renderWindow,100,false,3000,ui.scene);
}
inline __attribute__((always_inline)) void createSystem(PrefixState& ui,const std::wstring& logPath) {
    CEGUI::String config("");
    std::string bytes=STRINGS::StringConvertToNarrow(logPath.c_str());
    CEGUI::String logName(bytes);
    ui.system=new CEGUI::System(ui.renderer,NULL,NULL,NULL,config,logName);
}
// The complete caller must create logPath = GetAppDataPath() + L"CEGUI.log"
// after createRenderer and keep that wstring alive until the entry returns.
}
#endif
