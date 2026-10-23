#ifndef OTL_PARTICLE_MATERIAL_BOUNDARY_H
#define OTL_PARTICLE_MATERIAL_BOUNDARY_H
#include <Ogre.h>
#include "tests/Detour.h"
namespace particlegraphics {
// Observe CPU material compilation requests at the absent renderer boundary.
inline unsigned& compileCalls(){static unsigned value=0;return value;}
inline void compileWithoutRenderer(Ogre::Material*,bool){++compileCalls();}
struct MaterialCompileBoundary{
 void* trampoline;detour::Set hooks;
 MaterialCompileBoundary():trampoline(MAP_FAILED){
  void*lib=dlopen("libOgreMain-1.6.5.so",RTLD_NOW|RTLD_NOLOAD);if(!lib)std::abort();
  void*entry=dlsym(lib,"_ZN4Ogre8Material7compileEb");dlclose(lib);if(!entry)std::abort();
  trampoline=mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);if(trampoline==MAP_FAILED)std::abort();
  unsigned char code[12]={0x48,0xb8,0,0,0,0,0,0,0,0,0xff,0xe0};
  typedef void(*Fn)(Ogre::Material*,bool);Fn callback=&compileWithoutRenderer;
  std::memcpy(code+2,&callback,8);std::memcpy(trampoline,code,12);
  if(mprotect(trampoline,4096,PROT_READ|PROT_EXEC))std::abort();
  hooks.redirect(static_cast<char*>(entry),static_cast<char*>(entry),reinterpret_cast<Fn>(trampoline));if(hooks.failed())std::abort();compileCalls()=0;
 }
 ~MaterialCompileBoundary(){hooks.restore();if(munmap(trampoline,4096))std::abort();}
};
}
#endif
