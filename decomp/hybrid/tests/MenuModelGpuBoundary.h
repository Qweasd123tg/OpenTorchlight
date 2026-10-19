#ifndef OTL_MENU_MODEL_GPU_BOUNDARY_H
#define OTL_MENU_MODEL_GPU_BOUNDARY_H
#include "NativeMenuServices.h"
namespace menugui {
inline unsigned&materialPreparationCalls(){static unsigned n=0;return n;}
inline unsigned&materialLoadCalls(){static unsigned n=0;return n;}
inline bool gpuRules(Ogre::Technique*,std::ostringstream&){++materialPreparationCalls();return true;}
inline unsigned&automaticHardwareChecks(){static unsigned n=0;return n;}
inline bool hardwareSupport(Ogre::Technique*,bool automatic,std::ostringstream&){++materialPreparationCalls();if(automatic)++automaticHardwareChecks();return true;}
inline unsigned&texturePreparationCalls(){static unsigned n=0;return n;}
inline unsigned&textureLoadCalls(){static unsigned n=0;return n;}
inline void textureLoad(Ogre::TextureUnitState*p){if(!p)std::abort();++textureLoadCalls();}
inline void texturePrepare(Ogre::TextureUnitState*p){if(!p)std::abort();++texturePreparationCalls();}
inline void skipMaterialLoad(Ogre::Material*){++materialLoadCalls();}
// Real material resources remain real; only their graphics-device preparation
// is excluded. Genuine Entity/Mesh/Skeleton/Bone construction is retained.
struct ModelGpuBoundary {
    void*trampoline;detour::Set hooks;
    ModelGpuBoundary():trampoline(MAP_FAILED){
        if(Ogre::Root::getSingleton().getRenderSystem())std::abort();
        void*lib=dlopen("libOgreMain-1.6.5.so",RTLD_NOW|RTLD_NOLOAD);if(!lib)std::abort();
        const char*names[]={"_ZN4Ogre9Technique13checkGPURulesERSt19basic_ostringstreamIcSt11char_traitsIcESaIcEE","_ZN4Ogre9Technique20checkHardwareSupportEbRSt19basic_ostringstreamIcSt11char_traitsIcESaIcEE","_ZN4Ogre8Material8loadImplEv","_ZN4Ogre16TextureUnitState8_prepareEv","_ZN4Ogre16TextureUnitState5_loadEv"};
        typedef void(*Fn)(Ogre::Material*);
        uintptr_t callbacks[]={reinterpret_cast<uintptr_t>(&gpuRules),reinterpret_cast<uintptr_t>(&hardwareSupport),reinterpret_cast<uintptr_t>(&skipMaterialLoad),reinterpret_cast<uintptr_t>(&texturePrepare),reinterpret_cast<uintptr_t>(&textureLoad)};void*entry[5];
        for(unsigned i=0;i<5;++i){entry[i]=dlsym(lib,names[i]);if(!entry[i])std::abort();}dlclose(lib);
        trampoline=mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);if(trampoline==MAP_FAILED)std::abort();
        for(unsigned i=0;i<5;++i){unsigned char code[12]={0x48,0xb8,0,0,0,0,0,0,0,0,0xff,0xe0};std::memcpy(code+2,&callbacks[i],8);std::memcpy(static_cast<char*>(trampoline)+16*i,code,12);}
        if(mprotect(trampoline,4096,PROT_READ|PROT_EXEC))std::abort();
        for(unsigned i=0;i<5;++i)hooks.redirect(static_cast<char*>(entry[i]),static_cast<char*>(entry[i]),reinterpret_cast<Fn>(static_cast<char*>(trampoline)+16*i));
        if(hooks.failed())std::abort();materialPreparationCalls()=materialLoadCalls()=texturePreparationCalls()=automaticHardwareChecks()=textureLoadCalls()=0;
    }
    ~ModelGpuBoundary(){hooks.restore();if(munmap(trampoline,4096))std::abort();}
};
}
#endif
