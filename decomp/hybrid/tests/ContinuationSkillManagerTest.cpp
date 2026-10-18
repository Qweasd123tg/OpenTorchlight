#include <cstring>
#include <climits>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "BaseUnit.h"
#include "Character.h"
#include "Item.h"
#include "Skill.h"
#include "SkillManager.h"
#undef private
#define DECL(ret,old,newer,args,sym) TL_ORIGINAL(ret,old,args,sym) extern "C" ret newer args __asm__(sym);
DECL(void,smOldCharacter,smNewCharacter,(CSkillManager*,CCharacter*),"_ZN13CSkillManager16notifyOfDeletionEP10CCharacter")
DECL(void,smOldItem,smNewItem,(CSkillManager*,CItem*),"_ZN13CSkillManager16notifyOfDeletionEP5CItem")
DECL(void,smOldDtor,smNewDtor,(CSkillManager*),"_ZN13CSkillManagerD1Ev")
DECL(void,smOldStopName,smNewStopName,(CSkillManager*,std::wstring,bool),"_ZN13CSkillManager16stopSkillsByNameESbIwSt11char_traitsIwESaIwEEb")
DECL(void,smOldCharges,smNewCharges,(CSkillManager*,CSkill*),"_ZN13CSkillManager21decrementSkillChargesEP6CSkill")
DECL(void,smOldDelete,smNewDelete,(CSkillManager*,const std::wstring&),"_ZN13CSkillManager11deleteSkillERKSbIwSt11char_traitsIwESaIwEE")
DECL(CSkill*,smOldAdd,smNewAdd,(CSkillManager*,const std::wstring&,bool),"_ZN13CSkillManager8addSkillERKSbIwSt11char_traitsIwESaIwEEb")
#undef DECL
TL_FUNCTION(smName,"_ZN6CSkill7getNameEv")
TL_FUNCTION(smOwnerCharacter,"_ZN6CSkill17getOwnerCharacterEv")
TL_FUNCTION(smStop,"_ZN6CSkill9stopSkillEv")
TL_FUNCTION(smAttempt,"_ZN6CSkill18attemptToStopSkillEv")
TL_FUNCTION(smParse,"_ZN12CSkillParser8getSkillEP16CResourceManagerRKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(smAdd,"_ZN13CSkillManager8addSkillEP6CSkillbb")
namespace {
struct Case{unsigned op,seed;};autotest::Capture*cap;unsigned seed;CSkill*objects[6];std::wstring names[6];CRunicCore*units[3];CSkillManager*manager;CResourceManager*resources;
void number(unsigned n){cap->add(&n,4);}int id(CSkill*s){for(int i=0;i<6;++i)if(objects[i]==s)return i;return -1;}int unitId(CBaseUnit*u){for(int i=0;i<3;++i)if(reinterpret_cast<CBaseUnit*>(units[i])==u)return i;return -1;}
// Borrowed skills expose only the manager's typed fields and destructor ABI.
// Their common base and weak registrations have real construction/destruction.
struct SkillLifetime:CRunicCore{unsigned char payload[sizeof(CSkill)-sizeof(CRunicCore)];unsigned identity;SkillLifetime(unsigned n):identity(n){std::memset(payload,0,sizeof(payload));CSkill*s=reinterpret_cast<CSkill*>(this);new(&s->m_Target)TSafePointer<CBaseUnit>;s->m_pOwner=NULL;s->m_iOwnerSafePointerId=0xffffffffu;}virtual~SkillLifetime(){number(181);number(identity);CSkill*s=reinterpret_cast<CSkill*>(this);s->m_Target.~TSafePointer<CBaseUnit>();if(s->m_pOwner){s->m_pOwner->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(&s->m_pOwner),s->m_iOwnerSafePointerId);s->m_pOwner=NULL;}}};
const std::wstring&name(CSkill*s){number(191);int n=id(s);cap->add(&n,4);if(n<0)_exit(51);return names[n];}
CCharacter*ownerCharacter(CSkill*s){number(193);int n=id(s);cap->add(&n,4);int u=unitId(s->m_pOwner);return u==0||u==2?reinterpret_cast<CCharacter*>(units[u]):NULL;}
void stopped(CSkill*s,unsigned event){number(event);int n=id(s);cap->add(&n,4);s->m_interruptible=false;if(seed%7==0)manager->m_UpdatingSkills.remove(s);}
void stop(CSkill*s){stopped(s,197);}void attempt(CSkill*s){stopped(s,199);}
CSkill*parse(CResourceManager*r,const std::wstring&n){number(211);cap->addText(n);if(r!=resources)cap->issue=autotest::Capture::InvalidReport;return seed%4==0?NULL:objects[5];}
CSkill*add(CSkillManager*m,CSkill*s,bool first,bool second){number(223);int n=id(s);cap->add(&n,4);cap->add(&first,1);cap->add(&second,1);if(m!=manager||first)cap->issue=autotest::Capture::InvalidReport;m->m_OtherSkills.add(s);return seed%6==0?NULL:s;}
void state(CSkillManager*p,TSafePointer<CSkill>*weak){number(p->m_SkillsByName.size());for(std::map<std::wstring,TArrayList<CSkill*>*>::iterator i=p->m_SkillsByName.begin();i!=p->m_SkillsByName.end();++i){cap->addText(i->first);number(i->second->size());for(unsigned j=0;j<i->second->size();++j){int n=id((*i->second)[j]);cap->add(&n,4);}}for(unsigned group=0;group<2;++group){TArrayList<CSkill*>&list=group?p->m_OtherSkills:p->m_UpdatingSkills;number(list.size());for(unsigned i=0;i<list.size();++i){int n=id(list[i]);cap->add(&n,4);}}for(unsigned i=0;i<6;++i){bool live=weak[i].getObject()!=NULL;cap->add(&live,1);if(live){CSkill*s=objects[i];cap->add(&s->m_iCharges,4);cap->add(&s->m_interruptible,1);int owner=unitId(s->m_pOwner),target=unitId(s->m_Target.getObject());cap->add(&owner,4);cap->add(&target,4);cap->add(&s->m_iOwnerSafePointerId,4);cap->add(&s->m_Target.m_nIndex,4);}}for(unsigned i=0;i<3;++i)number(units[i]->m_pSafePointers?units[i]->m_pSafePointers->size():0);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);cap=&out;seed=c.seed;CRunicCore unitLife[3];for(unsigned i=0;i<3;++i)units[i]=&unitLife[i];uint64_t resourceWitness=0;resources=reinterpret_cast<CResourceManager*>(&resourceWitness);detour::Set patches;TL_REDIRECT(patches,smName,&name);TL_REDIRECT(patches,smOwnerCharacter,&ownerCharacter);TL_REDIRECT(patches,smStop,&stop);TL_REDIRECT(patches,smAttempt,&attempt);TL_REDIRECT(patches,smParse,&parse);TL_REDIRECT(patches,smAdd,&add);if(patches.failed())_exit(43);
 uint64_t storage[(sizeof(CSkillManager)+7)/8];manager=new(storage)CSkillManager(resources,seed%2?reinterpret_cast<CBaseUnit*>(units[0]):NULL);TSafePointer<CSkillManager> selfWeak;selfWeak.setObject(manager);TSafePointer<CSkill> weak[6];static const int charges[]={-1,0,1,2,INT_MAX};for(unsigned i=0;i<6;++i){objects[i]=reinterpret_cast<CSkill*>(new SkillLifetime(i));weak[i].setObject(objects[i]);names[i]=i<2?L"Alpha":i<4?L"bEtA":i==4?L"Ж":L"orphan";CSkill*s=objects[i];s->m_iCharges=charges[(i+seed)%5];s->m_interruptible=true;if((seed+i)%4){s->m_pOwner=reinterpret_cast<CBaseUnit*>(units[(seed+i)%3]);s->m_iOwnerSafePointerId=s->m_pOwner->addSafePointer(reinterpret_cast<TSafePointer<void*>*>(&s->m_pOwner));}if((seed+i)%5)s->m_Target.setObject(reinterpret_cast<CBaseUnit*>(units[(seed+i+1)%3]));}
 for(unsigned g=0;g<seed%4;++g){TArrayList<CSkill*>*list=new TArrayList<CSkill*>(1);unsigned n=g==2?1:2;for(unsigned i=0;i<n;++i)list->add(objects[g*2+i]);manager->m_SkillsByName[g==0?L"ALPHA":g==1?L"BETA":L"Ж"]=list;}
 for(unsigned i=0;i<6;++i){if((i+seed)%3==0)manager->m_UpdatingSkills.add(objects[i]);if((i+seed)%2==0)manager->m_OtherSkills.add(objects[i]);}
 static const wchar_t*queries[]={L"alpha",L"BETA",L"missing",L"Ж",L"",L"orphan"};std::wstring query=queries[seed%6];
 if(c.op==0)autotest::invoke(out,ours?&smNewCharacter:&smOldCharacter,manager,seed%5==0?NULL:reinterpret_cast<CCharacter*>(units[seed%3]));
 if(c.op==1)autotest::invoke(out,ours?&smNewItem:&smOldItem,manager,seed%5==0?NULL:reinterpret_cast<CItem*>(units[seed%3]));
 if(c.op==3)autotest::invoke(out,ours?&smNewStopName:&smOldStopName,manager,query,seed%2!=0);
 if(c.op==4)autotest::invoke(out,ours?&smNewCharges:&smOldCharges,manager,seed%7==0?NULL:objects[seed%6]);
 if(c.op==5)autotest::invoke<void(*)(CSkillManager*,const std::wstring&),CSkillManager*,const std::wstring&>(out,ours?&smNewDelete:&smOldDelete,manager,query);
 if(c.op==6){typedef CSkill*(*Fn)(CSkillManager*,const std::wstring&,bool);Fn f=ours?&smNewAdd:&smOldAdd;if(!autotest::beginInvocation(out,f))return;CSkill*r=f(manager,query,seed%2!=0);out.callCompleted=1;int n=id(r);out.add(&n,4);}
 if(c.op!=2)state(manager,weak);if(c.op==2)autotest::invoke(out,ours?&smNewDtor:&smOldDtor,manager);else smOldDtor(manager);bool invalid=selfWeak.getObject()==NULL;out.add(&invalid,1);if(!invalid)out.issue=autotest::Capture::InvalidReport;for(unsigned i=0;i<6;++i){CSkill*s=weak[i].getObject();bool live=s!=NULL;out.add(&live,1);if(live)delete s;}for(unsigned i=0;i<3;++i)number(units[i]->m_pSafePointers?units[i]->m_pSafePointers->size():0);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void recovered(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(continuation_skill_manager_ownership){int failures=0;const uintptr_t functions[]={(uintptr_t)&smOldCharacter,(uintptr_t)&smOldItem,(uintptr_t)&smOldDtor,(uintptr_t)&smOldStopName,(uintptr_t)&smOldCharges,(uintptr_t)&smOldDelete,(uintptr_t)&smOldAdd};for(unsigned op=0;op<7;++op){autotest::Coverage coverage("continuation_skill_manager_ownership",functions[op]);for(unsigned i=0;i<40;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage.observe(host,a,b);bool ok=!pair&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus;TL_CHECK(failures,ok);if(!ok){host->log("    skill manager op %u seed %u status %d/%d issue %u/%u bytes %lu/%lu\n",op,i,a.status,b.status,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k<a.capture.length&&k<b.capture.length;++k)if(a.capture.data[k]!=b.capture.data[k])host->log("    skill manager diff byte%u %02x/%02x\n",k,a.capture.data[k],b.capture.data[k]);coverage.report(host);return failures;}}coverage.report(host);}return failures;}
