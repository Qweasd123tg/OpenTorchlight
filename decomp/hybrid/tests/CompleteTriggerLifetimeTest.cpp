#include "AutoTest.h"
#include <Ogre.h>
#include <cstring>
#include <vector>
#define private public
#define protected public
#include "TriggerUnit.h"
#include "GenericModel.h"
#include "Layout.h"
#include "SoundBank.h"
#include "ResourceManager.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/NativeMenuServices.h"
#include "tests/NativeEditorControls.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/CharacterEmptyGlobals.h"
TL_ORIGINAL(void,triggerCtor,(CTriggerUnit*,CResourceManager*),"_ZN12CTriggerUnitC1EP16CResourceManager")
TL_ORIGINAL(void,triggerDtor,(CTriggerUnit*),"_ZN12CTriggerUnitD1Ev")
extern "C" void triggerRecoveredDtor(CTriggerUnit*) __asm__("_ZN12CTriggerUnitD1Ev");
namespace {
nativegame::Services* services;
struct Case { unsigned seed; };
void number(autotest::Capture& out,unsigned v){out.add(&v,sizeof v);}
void pin(std::vector<TSafePointer<CRunicCore>*>& pins,CRunicCore* object){
    if(!object)return;
    TSafePointer<CRunicCore>* weak=new TSafePointer<CRunicCore>;
    weak->setObject(object);pins.push_back(weak);
}
void side(void* raw,autotest::Capture& out,bool candidate){
    unsigned seed=static_cast<Case*>(raw)->seed;
    CResourceManager resources(services->scene);
    int baseline=g_iTotalCountOfObjects;
    CTriggerUnit* unit=static_cast<CTriggerUnit*>(Ogre::NedAllocImpl::allocBytes(sizeof(CTriggerUnit),0,0,0));
    triggerCtor(unit,seed%2?&resources:NULL);
    std::vector<TSafePointer<CRunicCore>*> pins;
    pin(pins,unit);
    if(seed&1){unit->m_layout=new CLayout(&resources,static_cast<ELAYOUT_TYPES>(0));pin(pins,unit->m_layout);}
    if(seed&2){unit->m_layout2C8=new CLayout(&resources,static_cast<ELAYOUT_TYPES>(1));pin(pins,unit->m_layout2C8);}
    if(seed&4){unit->m_unitModel=new CGenericModel(&resources,services->scene,L"",L"",false);pin(pins,unit->m_unitModel);}
    if(seed&8){unit->m_pSoundBank=new CSoundBank(*services->master->m_pSoundManager,seed&16);pin(pins,unit->m_pSoundBank);}
    unsigned count=seed/16%4;
    for(unsigned i=0;i<count;++i){
        CLayout* layout=(seed+i)%3?new CLayout(&resources,static_cast<ELAYOUT_TYPES>(i%2)):NULL;
        unit->m_stateLayouts.add(layout);pin(pins,layout);
    }
    for(unsigned i=0;i<seed%5;++i){
        unit->m_animations.add(i*seed);
        unit->m_altAnimations.add(i%2?~0u:seed+i);
        unit->m_looping.add((seed+i)%2!=0);
    }
    std::wstring text(seed/64%2?L"shared trigger content":L"");
    if(seed/64%2)text.append(48,wchar_t(L'A'+seed%26));
    unit->m_modelName=text;unit->m_treasureClass=text;
    unit->m_requiredItem=text;unit->m_requiredQuest=text;
    if(seed/32%2)unit->m_requiredQuest.reserve(256);
    std::wstring retained=unit->m_requiredItem;
    number(out,pins.size());
    autotest::invoke(out,candidate?triggerRecoveredDtor:triggerDtor,unit);
    for(unsigned i=0;i<pins.size();++i)number(out,pins[i]->getObject()==NULL);
    int delta=g_iTotalCountOfObjects-baseline;out.add(&delta,sizeof delta);
    out.addText(retained);out.addText(text);
    for(unsigned i=0;i<pins.size();++i)delete pins[i];
    Ogre::NedAllocImpl::deallocBytes(unit);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}
void replacement(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host* host){
    initEmptyGlobals();
    void* value=NULL;std::memcpy(&value,reinterpret_cast<void*>(0x148c4e8),sizeof value);
    if(!value)new(reinterpret_cast<void*>(0x148c4e8))std::wstring;
    nativegame::Services native;services=&native;if(!native.ready())return 1;
    nativeeditor::Controls editor(native);menugui::Audio audio(native.master);
    if(!native.master->m_pSoundManager)std::abort();
    autotest::Coverage coverage("trigger_lifetime_native",reinterpret_cast<uintptr_t>(triggerDtor));
    for(unsigned seed=0;seed<192;++seed){
        Case c={seed};autotest::Outcome before,after;
        autotest::runChild(original,&c,before);autotest::runChild(replacement,&c,after);
        if(coverage.observe(host,before,after)){
            host->log("    trigger lifetime seed%u exits%d/%d issue%u/%u bytes%lu/%lu\n",seed,before.childStatus,after.childStatus,before.capture.issue,after.capture.issue,(unsigned long)before.capture.length,(unsigned long)after.capture.length);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);return 0;
}
}
TL_TEST(trigger_lifetime_native){return systems_fixture::isolated(&worker,host);}
