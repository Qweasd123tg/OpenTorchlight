#include "SmallMassCompare.h"
#include <OgreMemoryAllocatorConfig.h>
#include <new>
#include "GameSpeed.h"
#include "AnimationPlayer.h"
#include "BaseUnit.h"
#include "SafePointer.h"
TL_ORIGINAL(void, oldSpeedCalc, (void*,float), "_ZN10CGameSpeed18calculateGameSpeedEf")
extern "C" void newSpeedCalc(void*,float) __asm__("_ZN10CGameSpeed18calculateGameSpeedEf");
TL_ORIGINAL(void, oldSpeedClear, (void*), "_ZN10CGameSpeed5clearEv")
extern "C" void newSpeedClear(void*) __asm__("_ZN10CGameSpeed5clearEv");
TL_ORIGINAL(void, oldSpeedDestroy, (void*), "_ZN10CGameSpeedD1Ev")
extern "C" void newSpeedDestroy(void*) __asm__("_ZN10CGameSpeedD1Ev");
TL_ORIGINAL(void, oldCameraClear, (void*), "_ZN14CCameraControl17clearCameraShakesEv")
extern "C" void newCameraClear(void*) __asm__("_ZN14CCameraControl17clearCameraShakesEv");
TL_ORIGINAL(void, oldAnimationDestroy, (void*), "_ZN16CAnimationPlayerD1Ev")
extern "C" void newAnimationDestroy(void*) __asm__("_ZN16CAnimationPlayerD1Ev");
TL_FUNCTION(graphValue,"_ZNK6CGraph8getValueEfj")
TL_FUNCTION(coreDestroy,"_ZN10CRunicCoreD2Ev")
TL_FUNCTION(editorDestroy,"_ZN17CEditorBaseObjectD2Ev")
TL_FUNCTION(removeSafe,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
extern "C" void* speedSingleton __asm__("_ZL12g_pGameSpeed");
namespace {
using namespace smallmass;
void** entries;unsigned destroyed;void* allReferences[8];unsigned refCount;
float graph(void* p,float x,unsigned line){event(1,p);floating(x);number(line);return field<float>(p,0x10);}
void destroyedObject(void* p){event(2,p);++destroyed;for(unsigned i=0;i<refCount;++i)if(field<void*>(allReferences[i],0)==p)field<void*>(allReferences[i],0)=0;}
void baseDestroy(void* p){event(3,p);}
void remove(void* p,void* reference,unsigned index){event(4,p);pointer(reference);number(index);}
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;destroyed=refCount=0;
 void* self=object(0x200);void** table=static_cast<void**>(object(16));table[1]=reinterpret_cast<void*>(&destroyedObject);
 detour::Set d;TL_REDIRECT(d,graphValue,&graph);TL_REDIRECT(d,coreDestroy,&baseDestroy);TL_REDIRECT(d,editorDestroy,&baseDestroy);TL_REDIRECT(d,removeSafe,&remove);if(d.failed())_exit(41);
 unsigned count=c.index%5;unsigned capacity=(c.index/5)%2?count:count+2;
 void** data=capacity?new void*[capacity]:0;
 for(unsigned i=0;i<capacity;++i){data[i]=object(0x50);field<void*>(data[i],0)=table;field<int>(data[i],0x10)=(i+c.index)%3;field<float>(data[i],0x14)=float((i+c.index)%4);field<float>(data[i],0x18)=float((c.index/3)%5)*.5f;void* g=object(0x20);field<float>(g,0x10)=c.index%13==0?bits(0x7fc00001):float(int(c.index%7)-3)*.5f;field<void*>(data[i],0x20)=g;field<float>(data[i],0x28)=float(int(i%3)-1);}
 if(c.op<3) {
  list(self,0x28,data,count,capacity);field<float>(self,0x10)=7;speedSingleton=c.index%11?self:0;
  if(c.op==0) {
   const float times[]={0,.25f,1,-.5f,bits(0x7fc00001),bits(0x7f800000),bits(0xff800000),bits(0x80000000)};float delta=times[(c.index/4)%8];
   autotest::invoke(out,ours?newSpeedCalc:oldSpeedCalc,self,delta);
   floating(field<float>(self,0x10));number(field<unsigned>(self,0x30));
   for(unsigned i=0;i<count;++i){pointer(data[i]);floating(field<float>(data[i],0x18));}
   delete[] data;
  } else if(c.op==1) {
   autotest::invoke(out,ours?newSpeedClear:oldSpeedClear,self);
   number(field<unsigned>(self,0x30));number(field<unsigned>(self,0x34));number(field<void*>(self,0x28)==0);
   if(!speedSingleton)delete[] data;
   out.addHeapInUse();
  } else {
   for(unsigned i=0;i<count;++i)if((c.index+i)%3==0)data[i]=0;
   void* a=object(0x20);void* b=object(0x20);field<void*>(a,0)=field<void*>(b,0)=table;
   field<void*>(self,0x18)=c.index&1?a:0;field<void*>(self,0x20)=c.index&2?b:0;
   autotest::invoke(out,ours?newSpeedDestroy:oldSpeedDestroy,self);
   number(speedSingleton==0);number(field<void*>(self,0x18)==0);number(field<void*>(self,0x20)==0);number(field<void*>(self,0x28)==0);out.addHeapInUse();
  }
 } else if(c.op==3) {
  delete[] data;data=capacity?new void*[capacity]:0;
  for(unsigned i=0;i<capacity;++i){void* reference=Ogre::NedAllocImpl::allocBytes(16,0,0,0);field<void*>(reference,0)=(i+c.index)%3?object(0x20):0;field<unsigned>(reference,8)=i+3;if(field<void*>(reference,0))field<void*>(field<void*>(reference,0),0)=table;data[i]=reference;allReferences[refCount++]=reference;}
  void** secondary = new void*[3];
  for (unsigned i = 0; i < 3; ++i) secondary[i] = NULL;
  list(self,0x58,data,count,capacity);list(self,0x70,secondary,2,3);
  autotest::invoke(out,ours?newCameraClear:oldCameraClear,self);
  number(field<unsigned>(self,0x60));number(field<unsigned>(self,0x64));number(field<void*>(self,0x58)==0);number(field<void*>(self,0x70)==0);out.addHeapInUse();
 } else {
  delete[] data;data=capacity?new void*[capacity]:0;
  for(unsigned i=0;i<capacity;++i){if((c.index+i)%3==0){data[i]=0;continue;}void* reference=Ogre::NedAllocImpl::allocBytes(16,0,0,0);field<void*>(reference,0)=(i+c.index)%2?object(0x20):0;field<unsigned>(reference,8)=i+7;data[i]=reference;}
  list(self,0x68,data,count,capacity);new(static_cast<char*>(self)+0x60)std::wstring(c.index&1?L"animation name":L"");new(static_cast<char*>(self)+0x80)std::wstring(L"category");new(static_cast<char*>(self)+0x88)std::wstring(c.index&2?L"unit":L"");field<bool>(self,0x91)=true;
  autotest::invoke(out,ours?newAnimationDestroy:oldAnimationDestroy,self);
  number(field<bool>(self,0x91));number(field<void*>(self,0x68)==0);number(field<unsigned>(self,0x70));out.addHeapInUse();
 }
 number(destroyed);
}
}
TL_TEST(services_speed_calculate){return smallmass::run(host,0,"services_speed_calculate",0xc77d10,execute,128);}
TL_TEST(services_speed_clear){return smallmass::run(host,1,"services_speed_clear",0xc78030,execute,64);}
TL_TEST(services_speed_destroy){return smallmass::run(host,2,"services_speed_destroy",0xc781d0,execute,64);}
TL_TEST(services_camera_clear){return smallmass::run(host,3,"services_camera_clear",0xceb380,execute,64);}
TL_TEST(services_animation_destroy){return smallmass::run(host,4,"services_animation_destroy",0xdd2aa0,execute,64);}

// Independent lifetime probes run the original constructors and actual base
// destructors. The counter records constructions; D1 must not decrement it.
TL_ORIGINAL(void, realSpeedCtor, (CGameSpeed*,std::wstring,std::wstring), "_ZN10CGameSpeedC1ESbIwSt11char_traitsIwESaIwEES3_")
TL_ORIGINAL(void, realGraphCtor, (CGraph*,EGRAPH_TYPES,std::wstring,unsigned), "_ZN6CGraphC1E12EGRAPH_TYPESSbIwSt11char_traitsIwESaIwEEj")
TL_ORIGINAL(void, realAnimationCtor, (CAnimationPlayer*,CResourceManager*), "_ZN16CAnimationPlayerC1EP16CResourceManager")
TL_FUNCTION(graphFileCtor,"_ZN6CGraphC1ERKSbIwSt11char_traitsIwESaIwEE")
namespace {
unsigned lifetimeDestroyed, lifetimeFreed;
void graphWithoutFile(CGraph* self,const std::wstring& name)
{
    // The filename constructor loads resources; the other original constructor
    // with zero graph lines gives the same owned graph a complete lifetime.
    realGraphCtor(self,GRAPH_LINEAR,name,0);
}
struct SpeedLifetimeWitness : CGameSpeed::CSpeedInstance
{
    SpeedLifetimeWitness()
    {
        m_type=static_cast<EGAMESPEED_TYPE>(0);m_duration=0;m_elapsed=0;
        m_graph=NULL;m_scale=1;
    }
    virtual ~SpeedLifetimeWitness() { ++lifetimeDestroyed; }
    void operator delete(void* memory)
    {
        ++lifetimeFreed;
        CGameSpeed::CSpeedInstance::operator delete(memory);
    }
};
void realLifetime(smallmass::Case& c,bool ours,autotest::Capture& out)
{
    using namespace smallmass;
    input=&c;output=&out;lifetimeDestroyed=lifetimeFreed=0;
    int before=g_iTotalCountOfObjects;
    if(c.op==0)
    {
        CGameSpeed* self=static_cast<CGameSpeed*>(CGameSpeed::operator new(sizeof(CGameSpeed)));
        speedSingleton=NULL;
        {
            detour::Set constructors;
            TL_REDIRECT(constructors,graphFileCtor,&graphWithoutFile);
            if(constructors.failed()){out.issue=autotest::Capture::InvalidReport;return;}
            realSpeedCtor(self,L"first lifetime graph",L"second lifetime graph");
        }
        if(g_iTotalCountOfObjects!=before+3||speedSingleton!=self)
            out.issue=autotest::Capture::InvalidReport;
        TSafePointer<CGraph> graphObservers[2];
        graphObservers[0].setObject(self->m_pGraph1);
        graphObservers[1].setObject(self->m_pGraph2);
        if(c.index&1){delete self->m_pGraph1;self->m_pGraph1=NULL;}
        if(c.index&2){delete self->m_pGraph2;self->m_pGraph2=NULL;}
        TSafePointer<CGameSpeed::CSpeedInstance> modifierObservers[8];
        unsigned expected=0;
        for(unsigned i=0;i<c.index%7;++i)
        {
            CGameSpeed::CSpeedInstance* value=NULL;
            if((i+c.index)%3)
            {
                value=new SpeedLifetimeWitness;
                modifierObservers[i].setObject(value);
                ++expected;
            }
            self->m_lSpeedModifiers.add(value);
        }
        if(c.index%11==0)speedSingleton=NULL;
        TSafePointer<CGameSpeed> observers[3];
        for(unsigned i=0;i<3;++i)observers[i].setObject(self);
        // Removing the middle registered observer exercises real index repair.
        observers[1].setObject(NULL);
        if(observers[0].getObject()!=self||observers[2].getObject()!=self)
            out.issue=autotest::Capture::InvalidReport;
        int constructed=g_iTotalCountOfObjects;
        if(constructed!=before+3+int(expected))out.issue=autotest::Capture::InvalidReport;
        autotest::invoke(out,ours?newSpeedDestroy:oldSpeedDestroy,static_cast<void*>(self));
        number(lifetimeDestroyed);number(lifetimeFreed);number(expected);
        for(unsigned i=0;i<2;++i){number(graphObservers[i].getObject()==NULL);if(graphObservers[i].getObject())out.issue=autotest::Capture::InvalidReport;}
        for(unsigned i=0;i<8;++i){number(modifierObservers[i].getObject()==NULL);if(modifierObservers[i].getObject())out.issue=autotest::Capture::InvalidReport;}
        for(unsigned i=0;i<3;++i){number(observers[i].getObject()==NULL);if(observers[i].getObject())out.issue=autotest::Capture::InvalidReport;}
        number(g_iTotalCountOfObjects-before);number(speedSingleton==NULL);
        if(lifetimeDestroyed!=expected||lifetimeFreed!=expected||g_iTotalCountOfObjects!=constructed||speedSingleton)
            out.issue=autotest::Capture::InvalidReport;
        CGameSpeed::operator delete(self);
    }
    else
    {
        CAnimationPlayer* self=static_cast<CAnimationPlayer*>(CAnimationPlayer::operator new(sizeof(CAnimationPlayer)));
        // The original C1 calls the original CEditorBaseObject C1, initializes
        // its wstring and core safe-pointer list, then all AnimationPlayer members.
        realAnimationCtor(self,NULL);
        if(g_iTotalCountOfObjects!=before+1)out.issue=autotest::Capture::InvalidReport;
        self->m_sAnimationName=c.index%3?std::wstring(40+c.index,L'a'):L"";
        self->m_sCategory=std::wstring(50+c.index,L'c');
        self->m_sUnitType=c.index&1?L"unit lifetime":L"";
        self->m_bAnimationPlaying=true;
        for(unsigned i=0;i<c.index%7;++i)
        {
            TSafePointer<CBaseUnit>* reference=NULL;
            if((i+c.index)%3)
            {
                void* memory=Ogre::NedAllocImpl::allocBytes(sizeof(TSafePointer<CBaseUnit>),NULL,0,NULL);
                reference=new(memory) TSafePointer<CBaseUnit>;
            }
            self->m_lAnimationTargets.add(reference);
        }
        TSafePointer<CAnimationPlayer> observers[4];
        for(unsigned i=0;i<4;++i)observers[i].setObject(self);
        observers[1].setObject(NULL);
        observers[3].setObject(NULL);
        if(observers[0].getObject()!=self||observers[2].getObject()!=self)
            out.issue=autotest::Capture::InvalidReport;
        int constructed=g_iTotalCountOfObjects;
        autotest::invoke(out,ours?newAnimationDestroy:oldAnimationDestroy,static_cast<void*>(self));
        for(unsigned i=0;i<4;++i){number(observers[i].getObject()==NULL);if(observers[i].getObject())out.issue=autotest::Capture::InvalidReport;}
        number(g_iTotalCountOfObjects-before);
        if(g_iTotalCountOfObjects!=constructed)out.issue=autotest::Capture::InvalidReport;
        CAnimationPlayer::operator delete(self);
    }
}
}
TL_TEST(services_speed_real_lifetime){return smallmass::run(host,0,"services_speed_real_lifetime",0xc781d0,realLifetime,64);}
TL_TEST(services_animation_real_lifetime){return smallmass::run(host,1,"services_animation_real_lifetime",0xdd2aa0,realLifetime,64);}
