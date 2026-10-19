#ifndef GAMECLIENT_OWNED_NATIVE_H
#define GAMECLIENT_OWNED_NATIVE_H
#include "tests/NativeMenuClient.h"
namespace menugui {
struct OwnedClient {
    CGameClient*client;
    CResourceManager*resources;
    CCameraControl*camera;
    CDungeonManager*dungeons;
    CDungeonManager*previousDungeons;
    CCameraControl*previousCamera;
    Ogre::SceneManager*scenes[3];
    OwnedClient(CSettings&settings,CMasterResourceManager*master,CSoundManager&audio):client(NULL),resources(NULL),camera(NULL),dungeons(NULL),previousDungeons(CDungeonManager::getSingleton()),previousCamera(CCameraControl::getSingleton()){
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
    ~OwnedClient(){
        if(client){mgClientDtor(client);Ogre::NedAllocImpl::deallocBytes(client);}
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
