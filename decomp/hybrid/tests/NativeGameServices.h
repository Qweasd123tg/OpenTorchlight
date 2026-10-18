#ifndef NATIVE_GAME_SERVICES_H
#define NATIVE_GAME_SERVICES_H
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include <dlfcn.h>
#include <OgreRoot.h>
#include <OgreHardwareBufferManager.h>
#include <OgreMaterialManager.h>
#include "Settings.h"
#include "MasterResourceManager.h"
#include "GameGlobals.h"
#include "GraphManager.h"
#include "Player.h"
#include "LinuxUtils.h"
#include "AutoTest.h"
#include "tests/Detour.h"
namespace nativegame {
TL_ORIGINAL(void, spawnSettingsCtor, (CSettings*,std::wstring,std::wstring,std::wstring,std::wstring), "_ZN9CSettingsC1ESbIwSt11char_traitsIwESaIwEES3_S3_S3_")
TL_ORIGINAL(void, spawnMasterCtor, (CMasterResourceManager*,CSettings*), "_ZN22CMasterResourceManagerC1EP9CSettings")
TL_ORIGINAL(void, spawnMasterDtor, (CMasterResourceManager*), "_ZN22CMasterResourceManagerD1Ev")
TL_ORIGINAL(void, spawnSettingsDtor, (CSettings*), "_ZN9CSettingsD1Ev")
TL_ORIGINAL(void, spawnPlayerCtor, (CPlayer*,CResourceManager*), "_ZN7CPlayerC1EP16CResourceManager")
TL_ORIGINAL(void, spawnPlayerDtor, (CPlayer*), "_ZN7CPlayerD1Ev")
extern "C" void spawnRootCtor(void*,const std::string&,const std::string&,const std::string&) __asm__("_ZN4Ogre4RootC1ERKSsS2_S2_");
extern "C" void spawnRootDtor(void*) __asm__("_ZN4Ogre4RootD1Ev");
extern "C" char spawnSetMaterial[] __asm__("_ZN4Ogre16SimpleRenderable11setMaterialERKSs");

struct Services {
    void*root;
    CSettings*settings;
    CMasterResourceManager*master;
    std::string base;
    std::wstring previousHome;
    void*buffers;
    void(*bufferDtor)(void*);
    Ogre::SceneManager*scene;
    Services():root(NULL),settings(NULL),master(NULL),previousHome(LinuxUtils::gameHomePath),buffers(NULL),bufferDtor(NULL),scene(NULL) {
        char path[]="/tmp/otl-spawn-XXXXXX";if(!mkdtemp(path))std::abort();
        base=std::string(path)+"/";mkdir((base+".runicgames").c_str(),0700);mkdir((base+".runicgames/Torchlight").c_str(),0700);
        LinuxUtils::gameHomePath=std::wstring(base.begin(),base.end());
        if (!Ogre::Root::getSingletonPtr()) {
            root=Ogre::NedAllocImpl::allocBytes(0x398,0,0,0);std::string empty;
            spawnRootCtor(root,empty,empty,empty);
        }
        if(!CMasterResourceManager::getSingleton()) {
            settings=static_cast<CSettings*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSettings),0,0,0));
            spawnSettingsCtor(settings,L"",L"",L"",L"");
            master=static_cast<CMasterResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CMasterResourceManager),0,0,0));
            spawnMasterCtor(master,settings);
        }
        if(!Ogre::HardwareBufferManager::getSingletonPtr()){
            void*lib=dlopen("libOgreMain-1.6.5.so",RTLD_NOW|RTLD_NOLOAD);if(!lib)std::abort();
            void(*ctor)(void*)=reinterpret_cast<void(*)(void*)>(dlsym(lib,"_ZN4Ogre28DefaultHardwareBufferManagerC1Ev"));
            bufferDtor=reinterpret_cast<void(*)(void*)>(dlsym(lib,"_ZN4Ogre28DefaultHardwareBufferManagerD1Ev"));if(!ctor||!bufferDtor)std::abort();
            buffers=Ogre::NedAllocImpl::allocBytes(0x130,0,0,0);ctor(buffers);dlclose(lib);
        }
        scene=Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC);
        if(Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting").isNull())
            Ogre::MaterialManager::getSingleton().initialise();
        void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x148a300),sizeof p);if(!p)new(reinterpret_cast<void*>(0x148a300))std::string;
        std::memcpy(&p,reinterpret_cast<void*>(0x148a308),sizeof p);if(!p)new(reinterpret_cast<void*>(0x148a308))std::wstring;
    }
    ~Services() {
        if(scene)Ogre::Root::getSingleton().destroySceneManager(scene);
        if(master){spawnMasterDtor(master);Ogre::NedAllocImpl::deallocBytes(master);spawnSettingsDtor(settings);Ogre::NedAllocImpl::deallocBytes(settings);}
        if(root){spawnRootDtor(root);Ogre::NedAllocImpl::deallocBytes(root);}
        if(buffers){bufferDtor(buffers);Ogre::NedAllocImpl::deallocBytes(buffers);}
        LinuxUtils::gameHomePath=previousHome;
        unlink((base+".runicgames/Torchlight/resourceconfig.dat").c_str());rmdir((base+".runicgames/Torchlight").c_str());rmdir((base+".runicgames").c_str());rmdir(base.c_str());
    }
    bool ready(){CMasterResourceManager*p=CMasterResourceManager::getSingleton();return p&&p->m_pHierarchy&&CGraphManager::getSingleton()&&CGameGlobals::getSingleton();}
};

inline unsigned& materialCalls(){static unsigned calls=0;return calls;}
inline void fishingMaterial(Ogre::SimpleRenderable*,const std::string& name){
    if(name!="FishingLine")std::abort();++materialCalls();
}
// Only the native Player constructor's unused fishing-line GPU upload is
// observed and replaced. All owners are real; the hook ends before invocation.
inline CPlayer* createPlayer(CResourceManager* resources){
    CPlayer* player=static_cast<CPlayer*>(Ogre::NedAllocImpl::allocBytes(sizeof(CPlayer),0,0,0));
    detour::Set graphics;materialCalls()=0;
    graphics.redirect(spawnSetMaterial,spawnSetMaterial,&fishingMaterial);
    if(graphics.failed())std::abort();spawnPlayerCtor(player,resources);
    if(materialCalls()!=1)std::abort();return player;
}
inline void destroyPlayer(CPlayer* player){spawnPlayerDtor(player);Ogre::NedAllocImpl::deallocBytes(player);}
}
#endif
