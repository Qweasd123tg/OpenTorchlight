#include "SmallMassCompare.h"
#include "Particle.h"
#include "SafePointer.h"
TL_ORIGINAL(bool,oUpdate,(void*,float,Ogre::Camera*,const Ogre::Vector3&),"_ZN9CParticle17updateLevelObjectEfPN4Ogre6CameraERKNS0_7Vector3E")
extern "C" bool nUpdate(void*,float,Ogre::Camera*,const Ogre::Vector3&) __asm__("_ZN9CParticle17updateLevelObjectEfPN4Ogre6CameraERKNS0_7Vector3E");
TL_ORIGINAL(void,oCtor,(CParticle*,CParticlePreloader*,const std::wstring&,CResourceManager*),"_ZN9CParticleC1EP18CParticlePreloaderRKSbIwSt11char_traitsIwESaIwEEP16CResourceManager")
extern "C" void nCtor(CParticle*,CParticlePreloader*,const std::wstring&,CResourceManager*) __asm__("_ZN9CParticleC1EP18CParticlePreloaderRKSbIwSt11char_traitsIwESaIwEEP16CResourceManager");
TL_FUNCTION(stop,"_ZN9CParticle4StopEb")
TL_FUNCTION(count,"_ZN9CParticle28getNumberOfParticlesUpdatingEb")
TL_FUNCTION(baseCtor,"_ZN19CPositionableObjectC1EP16CResourceManagerPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,realBaseCtor,(CPositionableObject*,CResourceManager*,Ogre::SceneManager*),"_ZN19CPositionableObjectC1EP16CResourceManagerPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,realBaseDtor,(CPositionableObject*),"_ZN19CPositionableObjectD1Ev")
namespace {
using namespace smallmass;
unsigned stopCalls,countCalls,baseCalls;
CResourceManager* expectedResources;
detour::Set* constructorPatch;
int countParticles(void* p,bool check) { ++countCalls;event(1,p);number(check);return int(input->index/8)%3; }
void stopParticle(void* p,bool immediate) { ++stopCalls;event(2,p);number(immediate);field<bool>(p,0x81)=false;field<bool>(p,0x127)=true; }
void constructBase(CPositionableObject* p,CResourceManager* resources,Ogre::SceneManager* scene) {
    ++baseCalls; number(resources==expectedResources);number(scene==NULL);
    if(resources!=expectedResources||scene!=NULL) output->issue=autotest::Capture::InvalidReport;
    constructorPatch->restore();
    realBaseCtor(p,NULL,NULL);
}
int references(const std::wstring& value) { int result; std::memcpy(&result,reinterpret_cast<const char*>(value.c_str())-8,4); return result; }
void execute(Case& c,bool ours,autotest::Capture& out) {
    input=&c;output=&out;autotest::g_arenaUsed=0;stopCalls=countCalls=baseCalls=0;
    detour::Set patches;
    if(c.op==0) {
        void* self=object(sizeof(CParticle));
        field<bool>(self,0x81)=c.index&1;
        field<bool>(self,0x128)=c.index&2;
        field<bool>(self,0x126)=c.index&4;
        const float timers[]={-1,0,.25f,1,2,bits(0x7fc00000),bits(0x7f800000),bits(0xff800000)};
        float timer=timers[(c.index/8)%8];float elapsed=c.index&4?.5f:0.0f;
        field<float>(self,0x120)=timer;
        TL_REDIRECT(patches,stop,&stopParticle);TL_REDIRECT(patches,count,&countParticles);
        if(patches.failed()) {out.issue=autotest::Capture::InvalidReport;return;}
        Ogre::Vector3 position(2,-3,7);
        autotest::invoke(out,ours?nUpdate:oUpdate,self,elapsed,static_cast<Ogre::Camera*>(NULL),position);
        number(stopCalls);number(countCalls);
        number(field<bool>(self,0x81));number(field<bool>(self,0x126));number(field<bool>(self,0x127));
        floating(field<float>(self,0x120));
        // Witnesses distinguish timeout, hidden, live-emitter and NaN branches.
        if((c.index==0&&!stopCalls)||(c.index==11&&!countCalls)||(c.index==41&&stopCalls)) out.issue=autotest::Capture::InvalidReport;
    } else {
        uint64_t storage[(sizeof(CParticle)+7)/8]; std::memset(storage,0xa5,sizeof(storage));
        CParticle* self=reinterpret_cast<CParticle*>(storage);
        std::wstring file=c.index%4==0?L"":c.index%4==1?L"media/particles/test":c.index%4==2?L"Ж/fx":std::wstring(96,L'p');
        if(!file.empty()&&(c.index&4)) file[0]=L'x';
        CParticlePreloader* preloader=c.index&1?static_cast<CParticlePreloader*>(object(16)):NULL;
        expectedResources=c.index&2?static_cast<CResourceManager*>(object(16)):NULL;
        constructorPatch=&patches;
        TL_REDIRECT(patches,baseCtor,&constructBase);
        if(patches.failed()) {out.issue=autotest::Capture::InvalidReport;return;}
        int refsBefore=references(file);
        int countBefore=g_iTotalCountOfObjects;
        autotest::invoke(out,ours?nCtor:oCtor,self,preloader,file,expectedResources);
        number(g_iTotalCountOfObjects-countBefore);
        number(references(file)-refsBefore);
        pointer(field<void*>(self,0));pointer(field<void*>(self,0x100));
        number(baseCalls);number(self->m_pParticlePreloader==preloader);number(self->m_pParticleCache==NULL);
        text(self->m_pUnknown110);number(self->m_iUnknown118);number(self->m_iUnknown11C);floating(self->m_fUnknown120);
        number(self->m_bUnknown124);number(self->m_bUnknown125);number(self->m_bUnknown126);number(self->m_bUnknown127);number(self->m_bUnknown128);
        if(baseCalls!=1||self->m_pUnknown110!=file) out.issue=autotest::Capture::InvalidReport;
        patches.restore();
        TSafePointer<CParticle> observer; observer.setObject(self);
        number(observer.getObject()==self);
        self->m_pUnknown110.~basic_string();
        realBaseDtor(self);
        number(observer.getObject()==NULL);
        number(references(file)-refsBefore);number(g_iTotalCountOfObjects-countBefore);
        if(references(file)!=refsBefore||g_iTotalCountOfObjects-countBefore!=1) out.issue=autotest::Capture::InvalidReport;
        if(observer.getObject()!=NULL) out.issue=autotest::Capture::InvalidReport;
    }
}
}
TL_TEST(continue_particle_update) {return smallmass::run(host,0,"continue_particle_update",(uint64_t)(uintptr_t)oUpdate,execute,128);}
TL_TEST(continue_particle_construct) {return smallmass::run(host,1,"continue_particle_construct",(uint64_t)(uintptr_t)oCtor,execute,32);}
