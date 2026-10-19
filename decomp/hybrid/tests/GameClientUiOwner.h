#ifndef GAMECLIENT_UI_OWNER_H
#define GAMECLIENT_UI_OWNER_H
#include "tests/MenuGuiFixture.h"
#include "GameUITextEventList.h"
TL_ORIGINAL(void,gameClientUiOwnerDtor,(CGameUI*),"_ZN7CGameUID1Ev")
namespace gameclient_fixture {
// Real CGameUI C1/D1. The unrelated create collaborator is disabled during C1.
// Its minimal empty owned pools and five cursor slots are then initialized
// with their real C++ types. This is fixture setup, not UI/create acceptance.
struct UiOwner {
    CGameUI* ui;
    UiOwner(CSettings&settings,CGameClient&client,Ogre::Camera*camera,
            Ogre::SceneManager*mainScene,Ogre::SceneManager*inventoryScene,
            Ogre::SceneManager*petScene,CResourceManager*resources):ui(NULL) {
        ui=static_cast<CGameUI*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGameUI),0,0,0));
        std::memset(ui,0,sizeof(*ui));
        {
            detour::Set construction;
            TL_REDIRECT(construction,mgUICreate,&menugui::skipCreate);
            if(construction.failed())std::abort();
            mgUICtor(ui,settings,client,NULL,NULL,camera,mainScene,inventoryScene,petScene,resources);
        }
        if(!ui->m_cursors.empty())std::abort();
        ui->m_cursors.resize(5,NULL);
        if(!ui->m_freeEvents)ui->m_freeEvents=new gameui_create_detail::TextEventList;
        if(!ui->m_activeEvents)ui->m_activeEvents=new gameui_create_detail::TextEventList;
    }
    ~UiOwner(){if(ui){gameClientUiOwnerDtor(ui);Ogre::NedAllocImpl::deallocBytes(ui);}}
    CGameUI*release(){CGameUI*result=ui;ui=NULL;return result;}
private:
    UiOwner(const UiOwner&);
    UiOwner&operator=(const UiOwner&);
};
}
#endif
