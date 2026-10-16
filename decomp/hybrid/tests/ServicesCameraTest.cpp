#include "SmallMassCompare.h"
#include <new>
TL_ORIGINAL(void, oldAspect, (void*,int,float,float), "_ZN14CCameraControl14setAspectRatioE8ECAMERASff")
extern "C" void newAspect(void*,int,float,float) __asm__("_ZN14CCameraControl14setAspectRatioE8ECAMERASff");
TL_ORIGINAL(void, oldConstruct, (void*,void*), "_ZN17CCameraControllerC1EP16CResourceManager")
extern "C" void newConstruct(void*,void*) __asm__("_ZN17CCameraControllerC1EP16CResourceManager");
TL_ORIGINAL(void, oldDestroy, (void*), "_ZN17CCameraControllerD1Ev")
extern "C" void newDestroy(void*) __asm__("_ZN17CCameraControllerD1Ev");
TL_FUNCTION(positionCtor,"_ZN19CPositionableObjectC2EP16CResourceManagerPN4Ogre12SceneManagerE")
TL_FUNCTION(positionDtor,"_ZN19CPositionableObjectD2Ev")
TL_FUNCTION(graphCtor,"_ZN6CGraphC1E12EGRAPH_TYPESSbIwSt11char_traitsIwESaIwEEj")
TL_FUNCTION(graphDtor,"_ZN6CGraphD1Ev")
TL_FUNCTION(safeRemove,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
namespace {
using namespace smallmass;
void aspect(void* p,float f){event(1,p);floating(f);}
void window(void* p,float a,float b,float c,float d){event(2,p);floating(a);floating(b);floating(c);floating(d);}
void extents(void* p,float a,float b,float c,float d){event(3,p);floating(a);floating(b);floating(c);floating(d);}
void positionConstruct(void* p,void* resource,void* manager){event(4,p);pointer(resource);pointer(manager);}
void positionDestroy(void* p){event(5,p);}
void graphConstruct(void* p,int type,std::wstring name,unsigned n){event(6,p);number(type);text(name);number(n);}
void graphDestroy(void* p){event(7,p);}
void remove(void* p,void* ref,unsigned n){event(8,p);pointer(ref);number(n);}
void execute(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;void* self=object(0x200);
 if(c.op==0){
  void** table=static_cast<void**>(object(0x430));table[0x278/8]=reinterpret_cast<void*>(&aspect);table[0x428/8]=reinterpret_cast<void*>(&window);table[0x2b0/8]=reinterpret_cast<void*>(&extents);
  for(unsigned i=0;i<5;++i){void* camera=object(0x20);field<void*>(camera,0)=table;field<void*>(self,0x10+i*8)=camera;}
  const float widths[]={0,1,640,1280,-100,bits(0x7fc00001),bits(0x7f800000)};const float heights[]={0,1,480,-720};
  autotest::invoke(out,ours?newAspect:oldAspect,self,int(c.index%5),widths[(c.index/5)%7],heights[(c.index/35)%4]);
 }else{
  detour::Set d;TL_REDIRECT(d,positionCtor,&positionConstruct);TL_REDIRECT(d,positionDtor,&positionDestroy);TL_REDIRECT(d,graphCtor,&graphConstruct);TL_REDIRECT(d,graphDtor,&graphDestroy);TL_REDIRECT(d,safeRemove,&remove);if(d.failed())_exit(41);
  if(c.op==1){
   memset(self,0x5a,0x1c8);void* resource=c.index&1?object(0x30):0;
   autotest::invoke(out,ours?newConstruct:oldConstruct,self,resource);
   pointer(field<void*>(self,0x100));text(field<std::wstring>(self,0x108));text(field<std::wstring>(self,0x110));pointer(field<void*>(self,0x118));pointer(field<void*>(self,0x120));number(field<unsigned>(self,0x128));out.add(static_cast<char*>(self)+0x148,0x1c);number(field<unsigned>(self,0x1c0));number(field<bool>(self,0x82));
   field<std::wstring>(self,0x108).~basic_string();field<std::wstring>(self,0x110).~basic_string();
  }else{
   new(static_cast<char*>(self)+0x108)std::wstring(c.index&1?L"category":L"");new(static_cast<char*>(self)+0x110)std::wstring(c.index&2?L"unit name":L"");field<void*>(self,0x120)=c.index%3?object(0x20):0;field<unsigned>(self,0x128)=c.index;
   autotest::invoke(out,ours?newDestroy:oldDestroy,self);number(field<void*>(self,0x120)==0);number(field<unsigned>(self,0x128));out.addHeapInUse();
  }
 }
}
}
TL_TEST(services_camera_aspect){return smallmass::run(host,0,"ServicesCameraAspect",0xce9ef0,execute,140);}
TL_TEST(services_controller_construct){return smallmass::run(host,1,"ServicesControllerConstruct",0xd977d0,execute,24);}
TL_TEST(services_controller_destroy){return smallmass::run(host,2,"ServicesControllerDestroy",0xd97660,execute,48);}
