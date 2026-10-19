#ifndef OTL_LEVEL_NATIVE_AUTOMAP_FIXTURE_H
#define OTL_LEVEL_NATIVE_AUTOMAP_FIXTURE_H
#include "tests/NativeMenuClient.h"
#include "tests/MenuModelGpuBoundary.h"
#include "Automap.h"
namespace level_native {
// Native destroyCamera(string) always notifies its RenderSystem. The CPU
// fixture has none. Suppress only that exact nine-byte notification, leaving
// native camera D0 and both owning SceneManager map removals intact.
struct CameraNotificationDuringCleanup {
    unsigned char*at;unsigned char saved[9];
    CameraNotificationDuringCleanup(){
        if(Ogre::Root::getSingleton().getRenderSystem())std::abort();
        void*lib=dlopen("libOgreMain-1.6.5.so",RTLD_NOW|RTLD_NOLOAD);if(!lib)std::abort();
        at=static_cast<unsigned char*>(dlsym(lib,"_ZN4Ogre12SceneManager13destroyCameraERKSs"));dlclose(lib);if(!at)std::abort();at+=0x1e1;
        const unsigned char expected[]={0x48,0x8b,0x07,0xff,0x90,0,3,0,0};
        if(std::memcmp(at,expected,9))std::abort();std::memcpy(saved,at,9);change(false);
    }
    void change(bool restore){uintptr_t page=reinterpret_cast<uintptr_t>(at)&~uintptr_t(4095),end=(reinterpret_cast<uintptr_t>(at)+9+4095)&~uintptr_t(4095);if(mprotect(reinterpret_cast<void*>(page),end-page,PROT_READ|PROT_WRITE|PROT_EXEC))std::abort();if(restore)std::memcpy(at,saved,9);else std::memset(at,0x90,9);if(mprotect(reinterpret_cast<void*>(page),end-page,PROT_READ|PROT_EXEC))std::abort();}
    ~CameraNotificationDuringCleanup(){change(true);}
};
struct Automap {
    CAutomap*map;std::vector<Ogre::MaterialPtr>created;
    Automap(CResourceManager*resources,Ogre::SceneManager*scene):map(NULL){
        menugui::ModelGpuBoundary gpu;
        const char*names[]={"BaseWhite","BaseWhiteNoLighting","AutomapCull","AutomapOverlay","Automap"};
        for(unsigned i=0;i<5;++i){Ogre::MaterialPtr m=Ogre::MaterialManager::getSingleton().getByName(names[i]);if(m.isNull()){m=Ogre::MaterialManager::getSingleton().create(names[i],"General");created.push_back(m);}m->compile();}
        menugui::ProjectionDuringConstruction projection;
        map=new CAutomap(resources,scene);
    }
    ~Automap(){
        {CameraNotificationDuringCleanup notification;delete map;}
        for(unsigned i=0;i<created.size();++i)Ogre::MaterialManager::getSingleton().remove(created[i]->getHandle());
    }
private:Automap(const Automap&);Automap&operator=(const Automap&);
};
}
#endif
