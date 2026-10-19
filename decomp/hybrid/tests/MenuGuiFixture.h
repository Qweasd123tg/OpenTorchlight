#ifndef OTL_MENU_GUI_FIXTURE_H
#define OTL_MENU_GUI_FIXTURE_H
#include "NativeMenuClient.h"
TL_ORIGINAL(void,mgUICtor,(CGameUI*,CSettings&,CGameClient&,void*,Ogre::RenderWindow*,Ogre::Camera*,Ogre::SceneManager*,Ogre::SceneManager*,Ogre::SceneManager*,CResourceManager*),"_ZN7CGameUIC1ER9CSettingsR11CGameClientPvPN4Ogre12RenderWindowEPNS5_6CameraEPNS5_12SceneManagerESB_SB_P16CResourceManager")
TL_ORIGINAL(void,mgQuestCtor,(CQuestMenu*,CGameUI&,CSettings&,Ogre::RenderWindow*,Ogre::SceneManager*,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN10CQuestMenuC1ER7CGameUIR9CSettingsPN4Ogre12RenderWindowEPNS4_12SceneManagerES8_PN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,mgDialogCtor,(CQuestDialogMenu*,CGameUI&,CSettings&,Ogre::SceneManager*,CEGUI::Window*,CResourceManager*),"_ZN16CQuestDialogMenuC1ER7CGameUIR9CSettingsPN4Ogre12SceneManagerEPN5CEGUI6WindowEP16CResourceManager")
TL_ORIGINAL(void,mgQuestDtor,(CQuestMenu*),"_ZN10CQuestMenuD1Ev")
TL_ORIGINAL(void,mgDialogDtor,(CQuestDialogMenu*),"_ZN16CQuestDialogMenuD1Ev")
TL_FUNCTION(mgUICreate,"_ZN7CGameUI6createEv")
TL_FUNCTION(mgQuestCreate,"_ZN10CQuestMenu11createMenusEv")
TL_FUNCTION(mgDialogCreate,"_ZN16CQuestDialogMenu11createMenusEv")
TL_FUNCTION(mgDropdownCreate,"_ZN13CDropdownMenu11createMenusEv")
TL_FUNCTION(mgTitle,"_ZN13CDropdownMenu8setTitleERKSbIwSt11char_traitsIwESaIwEE")
namespace menugui {
inline bool skipCreate(CGameUI*){return false;}
inline void skipQuest(CQuestMenu*){}
inline void skipDialog(CQuestDialogMenu*){}
inline void skipDropdown(CDropdownMenu*){}
inline void skipTitle(CDropdownMenu*,const std::wstring&){}
struct Fixture {
    Client nativeClient;
    CResourceManager& resources;
    CGameUI*ui;
    CQuestMenu*quest;
    CQuestDialogMenu*dialog;
    CEGUI::Window*root;
    Fixture(CSettings&settings,Ogre::SceneManager*scene):nativeClient(settings,CMasterResourceManager::getSingleton(),*CMasterResourceManager::getSingleton()->m_pSoundManager),resources(*nativeClient.resources),ui(NULL),quest(NULL),dialog(NULL),root(NULL){
        scene=nativeClient.scenes[0];
        root=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","menu-proof-root");
        root->setSize(CEGUI::UVector2(CEGUI::UDim(0,1024),CEGUI::UDim(0,768)));
        CEGUI::System::getSingleton().setGUISheet(root);
        detour::Set setup;
        TL_REDIRECT(setup,mgUICreate,&skipCreate);TL_REDIRECT(setup,mgQuestCreate,&skipQuest);
        TL_REDIRECT(setup,mgDialogCreate,&skipDialog);TL_REDIRECT(setup,mgDropdownCreate,&skipDropdown);TL_REDIRECT(setup,mgTitle,&skipTitle);
        if(setup.failed())std::abort();
        ui=static_cast<CGameUI*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGameUI),0,0,0));
        mgUICtor(ui,settings,*nativeClient.client,NULL,NULL,nativeClient.camera->m_cameras[0],scene,nativeClient.scenes[1],nativeClient.scenes[2],&resources);
        quest=static_cast<CQuestMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CQuestMenu),0,0,0));
        mgQuestCtor(quest,*ui,settings,NULL,scene,scene,root,&resources);
        dialog=static_cast<CQuestDialogMenu*>(Ogre::NedAllocImpl::allocBytes(sizeof(CQuestDialogMenu),0,0,0));
        mgDialogCtor(dialog,*ui,settings,scene,root,&resources);
    }
    ~Fixture(){
        mgDialogDtor(dialog);Ogre::NedAllocImpl::deallocBytes(dialog);
        mgQuestDtor(quest);Ogre::NedAllocImpl::deallocBytes(quest);
        CEGUI::System::getSingleton().setGUISheet(NULL);CEGUI::WindowManager::getSingleton().destroyWindow(root);
        // The native UI remains alive until this isolated child exits. Its
        // unrelated full shutdown requires graphics lists excluded at setup.
    }
};
}
#endif
