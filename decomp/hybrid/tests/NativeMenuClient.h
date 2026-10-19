#ifndef OTL_NATIVE_MENU_CLIENT_H
#define OTL_NATIVE_MENU_CLIENT_H
#include "NativeMenuServices.h"
#define private public
#define protected public
#include "GameClient.h"
#include "CameraControl.h"
#include "DungeonManager.h"
#include "Dungeon.h"
#include "QuestManager.h"
#undef protected
#undef private
#include <OgreTextureManager.h>
TL_ORIGINAL(void,mgClientCtor,(CGameClient*,CSettings&,CMasterResourceManager*,Ogre::RenderWindow*,Ogre::Root*,CCameraControl*,Ogre::SceneManager*,Ogre::SceneManager*,Ogre::SceneManager*,CSoundManager&),"_ZN11CGameClientC1ER9CSettingsP22CMasterResourceManagerPN4Ogre12RenderWindowEPNS4_4RootEP14CCameraControlPNS4_12SceneManagerESC_SC_R13CSoundManager")
TL_ORIGINAL(void,mgClientDtor,(CGameClient*),"_ZN11CGameClientD1Ev")
TL_ORIGINAL(void,mgCameraCtor,(CCameraControl*,Ogre::Camera*,Ogre::Camera*,Ogre::Camera*,Ogre::Camera*,Ogre::Camera*),"_ZN14CCameraControlC1EPN4Ogre6CameraES2_S2_S2_S2_")
TL_ORIGINAL(void,mgCameraDtor,(CCameraControl*),"_ZN14CCameraControlD1Ev")
TL_ORIGINAL(void,mgDungeonManagerCtor,(CDungeonManager*,std::wstring),"_ZN15CDungeonManagerC1ESbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,mgDungeonManagerDtor,(CDungeonManager*),"_ZN15CDungeonManagerD1Ev")
TL_ORIGINAL(void,mgDungeonCtor,(CDungeon*),"_ZN8CDungeonC1Ev")
namespace menugui {
inline unsigned& projectionCalls(){static unsigned n=0;return n;}
inline void skipProjection(const Ogre::Frustum*){++projectionCalls();}
// Camera construction converts a projection through Root's RenderSystem.
// Only that display-bound collaborator is suppressed during fixture C1.
// A nearby executable trampoline lets the normal reversible Detour own the
// actual library patch; no native vtable or SDK object is fabricated.
struct ProjectionDuringConstruction {
    void* trampoline;detour::Set hooks;
    ProjectionDuringConstruction():trampoline(MAP_FAILED){
        void*lib=dlopen("libOgreMain-1.6.5.so",RTLD_NOW|RTLD_NOLOAD);if(!lib)std::abort();
        void*entry=dlsym(lib,"_ZNK4Ogre7Frustum17updateFrustumImplEv");dlclose(lib);if(!entry)std::abort();
        trampoline=mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);if(trampoline==MAP_FAILED)std::abort();
        unsigned char code[12]={0x48,0xb8,0,0,0,0,0,0,0,0,0xff,0xe0};
        typedef void(*Fn)(const Ogre::Frustum*);Fn callback=&skipProjection;std::memcpy(code+2,&callback,8);std::memcpy(trampoline,code,12);
        if(mprotect(trampoline,4096,PROT_READ|PROT_EXEC))std::abort();
        hooks.redirect(static_cast<char*>(entry),static_cast<char*>(entry),reinterpret_cast<Fn>(trampoline));if(hooks.failed())std::abort();projectionCalls()=0;
    }
    ~ProjectionDuringConstruction(){hooks.restore();if(munmap(trampoline,4096))std::abort();}
};
// The real SceneManager destructor notifies its absent renderer about each
// removed camera before calling genuine Camera D0 and clearing its maps.
// Suppress only that notification sequence, with exact shipped-library bytes.
struct CameraNotificationDuringCleanup {
    unsigned char*at;unsigned char saved[9];
    CameraNotificationDuringCleanup(){
        if(Ogre::Root::getSingleton().getRenderSystem())std::abort();
        void*lib=dlopen("libOgreMain-1.6.5.so",RTLD_NOW|RTLD_NOLOAD);if(!lib)std::abort();
        at=static_cast<unsigned char*>(dlsym(lib,"_ZN4Ogre12SceneManager17destroyAllCamerasEv"));dlclose(lib);if(!at)std::abort();at+=0x21;
        const unsigned char expected[]={0x48,0x8b,0x07,0xff,0x90,0,3,0,0};
        if(std::memcmp(at,expected,9))std::abort();std::memcpy(saved,at,9);change(false);
    }
    void change(bool restore){
        uintptr_t page=reinterpret_cast<uintptr_t>(at)&~uintptr_t(4095);
        uintptr_t end=(reinterpret_cast<uintptr_t>(at)+9+4095)&~uintptr_t(4095);
        if(mprotect(reinterpret_cast<void*>(page),end-page,PROT_READ|PROT_WRITE|PROT_EXEC))std::abort();
        if(restore)std::memcpy(at,saved,9);else std::memset(at,0x90,9);
        if(mprotect(reinterpret_cast<void*>(page),end-page,PROT_READ|PROT_EXEC))std::abort();
    }
    ~CameraNotificationDuringCleanup(){
#ifndef OTL_TEST_MENU_LEAVE_NOTIFY_PATCH
        change(true);
#endif
    }
};
struct DefaultSceneDuringConstruction {
    CMasterResourceManager*master;Ogre::SceneManager*previous;
    DefaultSceneDuringConstruction(CMasterResourceManager*m,Ogre::SceneManager*scene):master(m),previous(m->m_pDefaultSceneManager){master->m_pDefaultSceneManager=scene;}
    ~DefaultSceneDuringConstruction(){master->m_pDefaultSceneManager=previous;}
};
// Native objects only. The absent TextureManager and RenderWindow select the
// original constructor's checked headless path; no constructor branches hook.
struct Client {
    CGameClient*client;
    CResourceManager*resources;
    CCameraControl*camera;
    CDungeonManager*dungeons;
    CDungeonManager*previousDungeons;
    CCameraControl*previousCamera;
    Ogre::SceneManager*scenes[3];
    Client(CSettings&settings,CMasterResourceManager*master,CSoundManager&audio):client(NULL),resources(NULL),camera(NULL),dungeons(NULL),previousDungeons(CDungeonManager::getSingleton()),previousCamera(CCameraControl::getSingleton()){
        typedef char ClientSize[(sizeof(CGameClient)==0x3910)?1:-1];
        if(Ogre::TextureManager::getSingletonPtr())std::abort();
        Ogre::Root&root=Ogre::Root::getSingleton();
        ProjectionDuringConstruction projection;
        for(unsigned i=0;i<3;++i)scenes[i]=root.createSceneManager(Ogre::ST_GENERIC);
        Ogre::Camera*c[5];for(unsigned i=0;i<5;++i){char n[40];std::sprintf(n,"menu-bootstrap-camera-%u",i);c[i]=scenes[2]->createCamera(n);}
        camera=static_cast<CCameraControl*>(Ogre::NedAllocImpl::allocBytes(sizeof(CCameraControl),0,0,0));mgCameraCtor(camera,c[0],c[1],c[2],c[3],c[4]);
        dungeons=static_cast<CDungeonManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CDungeonManager),0,0,0));
        mgDungeonManagerCtor(dungeons,L"menu_bootstrap_no_resource_directory/");
        if(!dungeons->m_lDungeons.size()){
            CDungeon*d=static_cast<CDungeon*>(Ogre::NedAllocImpl::allocBytes(sizeof(CDungeon),0,0,0));mgDungeonCtor(d);d->m_sName=L"MENU_BOOTSTRAP";dungeons->m_lDungeons.add(d);
        }
        client=static_cast<CGameClient*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGameClient),0,0,0));
        {DefaultSceneDuringConstruction defaultScene(master,scenes[0]);
         mgClientCtor(client,settings,master,NULL,&root,camera,scenes[0],scenes[1],scenes[2],audio);}
        // Native C1 5886c2..5886e6 stores/registers its owned ResourceManager at
        // 2b8; +40 belongs to the master's borrowed unit resource collection.
        std::memcpy(&resources,reinterpret_cast<char*>(client)+0x2b8,sizeof(resources));
        if(!resources||client->m_cameraControl!=camera||client->m_pGameUI||!client->m_questManager)std::abort();
    }
    ~Client(){
        #ifndef OTL_TEST_MENU_SKIP_CLIENT_DTOR
        mgClientDtor(client);Ogre::NedAllocImpl::deallocBytes(client);
#endif
        mgCameraDtor(camera);Ogre::NedAllocImpl::deallocBytes(camera);
        *reinterpret_cast<CCameraControl**>(0x14f6eb8)=previousCamera;
        mgDungeonManagerDtor(dungeons);Ogre::NedAllocImpl::deallocBytes(dungeons);
        // Native manager D1 clears the singleton. Restore a borrowed predecessor.
        *reinterpret_cast<CDungeonManager**>(0x151f650)=previousDungeons;
        CameraNotificationDuringCleanup notifications;
        for(unsigned i=0;i<3;++i)Ogre::Root::getSingleton().destroySceneManager(scenes[i]);
    }
};
}
#endif
