#ifndef OTL_GAME_SETUP_CLEAN_BOOTSTRAP_H
#define OTL_GAME_SETUP_CLEAN_BOOTSTRAP_H
#include "tests/SystemsNativeGame.h"
#include "MasterResourceManager.h"
#include <OgreDefaultHardwareBufferManager.h>
#include <dlfcn.h>
namespace game_setup_fixture {
TL_ORIGINAL(void,inheritedMasterDtor,(CMasterResourceManager*),"_ZN22CMasterResourceManagerD1Ev")
// Call only in a private fixture child. Previous tests may leave a genuine
// headless owner graph in the shard parent. Finish its native lifetime before
// this test constructs its independently owned Root/Master graph.
inline bool finishInheritedOwners(){
    Ogre::HardwareBufferManager* buffers=Ogre::HardwareBufferManager::getSingletonPtr();
    Ogre::DefaultHardwareBufferManager* cpu=dynamic_cast<Ogre::DefaultHardwareBufferManager*>(buffers);
    if(buffers&&!cpu)return false;
    if(CMasterResourceManager* master=CMasterResourceManager::getSingleton()){
        inheritedMasterDtor(master);
    }
    if(Ogre::Root* root=Ogre::Root::getSingletonPtr()){
        systemsGameRootDtor(root);
    }
    // NativeGameServices owns the separate CPU buffer manager after Root.
    // A Root which owned its manager may already have destroyed it.
    if(buffers&&Ogre::HardwareBufferManager::getSingletonPtr()==buffers){
        void* library=dlopen("libOgreMain-1.6.5.so",RTLD_NOW|RTLD_NOLOAD);
        if(!library)return false;
        void(*finish)(void*)=reinterpret_cast<void(*)(void*)>(dlsym(library,"_ZN4Ogre28DefaultHardwareBufferManagerD1Ev"));
        if(!finish){dlclose(library);return false;}
        finish(cpu);dlclose(library);
    }
    // Borrowed owners have mixed allocation sites (including raw NedAlloc).
    // End their actual lifetimes, retaining only storage until this child exits.
    return !Ogre::Root::getSingletonPtr()&&!CMasterResourceManager::getSingleton()
        &&!Ogre::HardwareBufferManager::getSingletonPtr();
}
}
#endif
