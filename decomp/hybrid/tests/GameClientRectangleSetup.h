#ifndef GAMECLIENT_RECTANGLE_SETUP_H
#define GAMECLIENT_RECTANGLE_SETUP_H
#include "tests/NativeMenuClient.h"
#include <OgreSimpleRenderable.h>
namespace gameclient_fixture {
inline void rectangleMaterial(Ogre::SimpleRenderable*,const std::string&name){if(name!="BaseWhiteNoLighting")std::abort();}
struct RectangleDuringConstruction {
    void* trampoline;detour::Set hooks;
    RectangleDuringConstruction():trampoline(MAP_FAILED){
        void*lib=dlopen("libOgreMain-1.6.5.so",RTLD_NOW|RTLD_NOLOAD);if(!lib)std::abort();
        void*entry=dlsym(lib,"_ZN4Ogre16SimpleRenderable11setMaterialERKSs");dlclose(lib);if(!entry)std::abort();
        trampoline=mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);if(trampoline==MAP_FAILED)std::abort();
        unsigned char code[12]={0x48,0xb8,0,0,0,0,0,0,0,0,0xff,0xe0};
        typedef void(*Fn)(Ogre::SimpleRenderable*,const std::string&);Fn callback=&rectangleMaterial;std::memcpy(code+2,&callback,8);std::memcpy(trampoline,code,12);
        if(mprotect(trampoline,4096,PROT_READ|PROT_EXEC))std::abort();
        hooks.redirect(static_cast<char*>(entry),static_cast<char*>(entry),reinterpret_cast<Fn>(trampoline));if(hooks.failed())std::abort();
    }
    ~RectangleDuringConstruction(){hooks.restore();if(munmap(trampoline,4096))std::abort();}
};
}
#endif
