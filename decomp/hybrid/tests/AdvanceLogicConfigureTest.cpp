#include "ParentPairs.h"
#include "Detour.h"
#include "SkillController.h"
#include "MasterResourceManager.h"
#include "DataGroup.h"
#include "Hierarchy.h"
#include "Level.h"
#include "GameClient.h"
#include "GameVariables.h"
#include <new>
TL_ORIGINAL(bool,oldConfigure,(CSkillController*),"_ZN16CSkillController13configureUnitEv")
extern "C" bool newConfigure(CSkillController*) __asm__("_ZN16CSkillController13configureUnitEv");
TL_FUNCTION(masterSingleton,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(typeID,"_ZN10CHierarchy15getTypeIDByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(isType,"_ZN10CHierarchy3ISAEjj")
TL_FUNCTION(levelPlayer,"_ZN6CLevel9getPlayerEv")
TL_FUNCTION(levelUnit,"_ZN6CLevel22getBaseUnitByDataGroupEP10CDataGroup")
namespace {
autotest::Capture*cap;CMasterResourceManager*master;CHierarchy*hierarchy;CLevel*level;CDataGroup*data;CRunicCore*target;unsigned seed;
void n(unsigned x){parentpairs::scalar(*cap,x);}CMasterResourceManager* singleton(){n(1);return master;}
UNITTYPES::EUNITTYPES lookup(CHierarchy*p,const std::wstring&s){n(2);n(p==hierarchy);cap->addText(s);if(p!=hierarchy)cap->issue=autotest::Capture::InvalidReport;return static_cast<UNITTYPES::EUNITTYPES>(seed+17);}
bool isa(CHierarchy*p,unsigned type,unsigned parent){n(3);n(type);n(parent);if(p!=hierarchy||type!=seed+17||parent!=28)cap->issue=autotest::Capture::InvalidReport;return seed&1;}
CPlayer* player(CLevel*p){n(4);n(p==level);if(p!=level)cap->issue=autotest::Capture::InvalidReport;return reinterpret_cast<CPlayer*>(target);}
CBaseUnit* unit(CLevel*p,CDataGroup*d){n(5);n(p==level);n(d==data);if(p!=level||d!=data)cap->issue=autotest::Capture::InvalidReport;return reinterpret_cast<CBaseUnit*>(target);}
void side(void*raw,autotest::Capture&out,bool ours){seed=static_cast<parentpairs::Case*>(raw)->seed;cap=&out;unsigned long long memory[(sizeof(CSkillController)+7)/8]={0},resourceMem[(sizeof(CResourceManager)+7)/8]={0},masterMem[(sizeof(CMasterResourceManager)+7)/8]={0},hierarchyMem[32]={0},levelMem[8]={0},clientMem[(sizeof(CGameClient)+7)/8]={0};CSkillController*self=reinterpret_cast<CSkillController*>(memory);CResourceManager*resources=reinterpret_cast<CResourceManager*>(resourceMem);master=reinterpret_cast<CMasterResourceManager*>(masterMem);hierarchy=reinterpret_cast<CHierarchy*>(hierarchyMem);level=reinterpret_cast<CLevel*>(levelMem);master->m_pHierarchy=hierarchy;std::memcpy(reinterpret_cast<char*>(resources)+0x18,&level,sizeof(level));TArrayList<CGameClient*>*clients=new(reinterpret_cast<char*>(resources)+0x28) TArrayList<CGameClient*>(2);CGameClient*client=reinterpret_cast<CGameClient*>(clientMem);clients->add(client);
 CRunicCore first,second;target=seed%5?&first:NULL;CRunicCore*old=seed%7==0?&second:NULL;CDataGroup group(L"UNIT",NULL,2,2,NULL);data=&group;if(seed%4)group.AddDataValue(L"UNITTYPE",L"PLAYER",false);new(&self->m_sCategory) std::wstring(seed%3==0?gRESOURCE_GROUP_NAMES[2]:seed%3==1?gRESOURCE_GROUP_NAMES[1]:L"other category");new(&self->m_sUnitInteractWith) std::wstring(L"fixture unit");new(&self->m_sSkillName) std::wstring(L"fixture skill");self->m_pResourceManager=resources;self->m_pUnitInteractDataGroup=seed%4<2?&group:NULL;self->m_pRunicCore=old;self->m_iRunicCoreSafePointerId=old?old->addSafePointer(reinterpret_cast<TSafePointer<void*>*>(&self->m_pRunicCore)):-1;CPlayer*p=reinterpret_cast<CPlayer*>(target);std::memcpy(reinterpret_cast<char*>(client)+0x58,&p,sizeof(p));detour::Set patches;TL_REDIRECT(patches,masterSingleton,&singleton);TL_REDIRECT(patches,typeID,&lookup);TL_REDIRECT(patches,isType,&isa);TL_REDIRECT(patches,levelPlayer,&player);TL_REDIRECT(patches,levelUnit,&unit);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef bool(*Fn)(CSkillController*);Fn fn=ours?newConfigure:oldConfigure;if(!autotest::beginInvocation(out,fn))return;bool result=fn(self);out.callCompleted=1;n(result);n(self->m_pRunicCore==NULL?0:self->m_pRunicCore==&first?1:self->m_pRunicCore==&second?2:99);parentpairs::scalar(out,self->m_iRunicCoreSafePointerId);out.addText(self->m_sCategory);
 // Real CRunicCore destruction must invalidate the pointer registered by the
 // method, beyond merely returning the expected candidate identity.
 if(self->m_pRunicCore){CRunicCore*registered=self->m_pRunicCore;registered->~CRunicCore();n(self->m_pRunicCore==NULL);parentpairs::scalar(out,self->m_iRunicCoreSafePointerId);if(self->m_pRunicCore)out.issue=autotest::Capture::InvalidReport;new(registered) CRunicCore;}
 self->m_sSkillName.~basic_string();self->m_sUnitInteractWith.~basic_string();self->m_sCategory.~basic_string();clients->~TArrayList();}
void a(void*p,autotest::Capture&c){side(p,c,false);}void b(void*p,autotest::Capture&c){side(p,c,true);}
}
TL_TEST(advance_logic_configure){return parentpairs::run(host,"advance_logic_configure",(uintptr_t)oldConfigure,84,a,b);}
