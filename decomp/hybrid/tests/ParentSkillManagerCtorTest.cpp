#include "ParentPairs.h"
#include "Detour.h"
#include <map>
#include <string>
#define private public
#include "SkillManager.h"
#include "BaseUnit.h"
#undef private
TL_ORIGINAL(void,parentSkillCtorOld,(CSkillManager*,CResourceManager*,CBaseUnit*),"_ZN13CSkillManagerC1EP16CResourceManagerP9CBaseUnit")
extern "C" void parentSkillCtorNew(CSkillManager*,CResourceManager*,CBaseUnit*) __asm__("_ZN13CSkillManagerC1EP16CResourceManagerP9CBaseUnit");
TL_FUNCTION(parentSkillAddSafe,"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
namespace {
autotest::Capture* cap;CSkillManager* manager;CRunicCore* ownerCore;TSafePointer<CRunicCore>* unwind;
unsigned addCalls;
void number(unsigned n){parentpairs::scalar(*cap,n);}
void observeList(const TArrayList<CSkill*>& l)
{number(l.m_pData!=NULL);number(l.m_nCount);number(l.m_nCapacity);number(l.m_nGrowBy);}
unsigned throwAdd(CRunicCore* owner,TSafePointer<void*>* reference)
{
    ++addCalls;bool valid=owner==ownerCore&&reference==reinterpret_cast<TSafePointer<void*>*>(&manager->m_Owner);
    parentpairs::scalar(*cap,valid);number(manager->m_Owner.m_pObject==NULL);number(manager->m_Owner.m_nIndex);
    number(manager->m_SkillsByName.size());observeList(manager->m_UpdatingSkills);observeList(manager->m_OtherSkills);
    if(!valid||manager->m_Owner.m_pObject||manager->m_Owner.m_nIndex!=~0u||!manager->m_SkillsByName.empty()||manager->m_UpdatingSkills.m_nGrowBy!=10||manager->m_OtherSkills.m_nGrowBy!=10)cap->issue=autotest::Capture::InvalidReport;
    // An external weak witness observes base cleanup after registration throws.
    // Use the exact typed list consumed by CRunicCore's real destructor.
    manager->m_pSafePointers=new TArrayList<TSafePointer<void*>*>(2);
    unwind->m_pObject=manager;unwind->m_nIndex=0;
    manager->m_pSafePointers->add(reinterpret_cast<TSafePointer<void*>*>(unwind));
    throw 83;
}
void side(void* raw,autotest::Capture& out,bool ours)
{
    unsigned seed=static_cast<parentpairs::Case*>(raw)->seed;cap=&out;addCalls=0;
    // Only CRunicCore's actual methods run on the owner's reachable prefix.
    // No BaseUnit method, vtable or guessed BaseUnit lifetime is fabricated.
    ownerCore=new CRunicCore;
    TSafePointer<CRunicCore> preexisting[4];for(unsigned i=0;i<seed%5;++i)preexisting[i].setObject(ownerCore);
    CBaseUnit* owner=seed%3?reinterpret_cast<CBaseUnit*>(ownerCore):NULL;
    CResourceManager* resource=seed%2?reinterpret_cast<CResourceManager*>(autotest::allocate(16)):NULL;
    void* memory=CSkillManager::operator new(sizeof(CSkillManager));std::memset(memory,0xa5,sizeof(CSkillManager));manager=static_cast<CSkillManager*>(memory);
    TSafePointer<CRunicCore> witness;unwind=&witness;
    bool fault=owner&&seed%4==3;detour::Set patches;if(fault)TL_REDIRECT(patches,parentSkillAddSafe,&throwAdd);
    if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    int caught=0,initialCount=g_iTotalCountOfObjects;
    typedef void(*Fn)(CSkillManager*,CResourceManager*,CBaseUnit*);Fn fn=ours?parentSkillCtorNew:parentSkillCtorOld;
    if(!autotest::beginInvocation(out,fn))return;try{fn(manager,resource,owner);}catch(int n){caught=n;}out.callCompleted=1;
    number(caught);number(addCalls);number(g_iTotalCountOfObjects-initialCount);number(witness.getObject()==NULL);
    if(!caught){
        number(manager->m_pResourceManager==resource);number(manager->m_SkillsByName.size());
        observeList(manager->m_UpdatingSkills);observeList(manager->m_OtherSkills);
        number(manager->m_Owner.m_pObject==owner);number(manager->m_Owner.m_nIndex);
        out.add(manager->m_SkillData78,sizeof(manager->m_SkillData78));
        // Make the initially empty map and lists usable across grow-by-10 boundaries.
        for(unsigned i=0;i<seed%23;++i){CSkill* token=reinterpret_cast<CSkill*>(autotest::allocate(16));manager->m_UpdatingSkills.add(token);manager->m_OtherSkills.add(token);}
        manager->m_SkillsByName[L"probe"]=&manager->m_OtherSkills;
        observeList(manager->m_UpdatingSkills);observeList(manager->m_OtherSkills);number(manager->m_SkillsByName.size());
        if(seed%2){delete ownerCore;ownerCore=NULL;number(manager->m_Owner.m_pObject==NULL);number(manager->m_Owner.m_nIndex);}
        manager->m_SkillsByName.~map();manager->m_UpdatingSkills.~TArrayList();manager->m_OtherSkills.~TArrayList();manager->m_Owner.~TSafePointer();manager->CRunicCore::~CRunicCore();
        if(ownerCore)number(ownerCore->m_pSafePointers?ownerCore->m_pSafePointers->size():0);
    }else if(!fault||caught!=83||witness.getObject()!=NULL)out.issue=autotest::Capture::InvalidReport;
    CSkillManager::operator delete(memory);
    delete ownerCore;ownerCore=NULL;
    for(unsigned i=0;i<seed%5;++i)number(preexisting[i].getObject()==NULL);
    out.addHeapInUse();
}
void a(void*p,autotest::Capture&c){side(p,c,false);}void b(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(parent_skill_manager_ctor){return parentpairs::run(host,"parent_skill_manager_ctor",(uintptr_t)parentSkillCtorOld,96,a,b);}
