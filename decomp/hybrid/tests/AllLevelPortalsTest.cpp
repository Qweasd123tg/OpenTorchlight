#include "StringTranslate.h"
#include <string>
#include <map>
#include <vector>
#include "tests/FinishLevelFixture.h"
#define private public
#define protected public
#include "Skill.h"
#include "SkillManager.h"
#include "SkillProperty.h"
#include "SkillEvent.h"
#include "SkillEffectAndAffixes.h"
#include "EffectManager.h"
#include "Hierarchy.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
TL_ORIGINAL(void,lpOldDelete,(CLevel*,std::wstring),"_ZN6CLevel29deleteTemporaryDungeonPortalsESbIwSt11char_traitsIwESaIwEE")
extern "C" void lpNewDelete(CLevel*,std::wstring) __asm__("_ZN6CLevel29deleteTemporaryDungeonPortalsESbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(Ogre::Vector3,lpOldFind,(CLevel*,std::wstring),"_ZN6CLevel26findTemporaryDungeonPortalESbIwSt11char_traitsIwESaIwEE")
extern "C" Ogre::Vector3 lpNewFind(CLevel*,std::wstring) __asm__("_ZN6CLevel26findTemporaryDungeonPortalESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(lpEffect,"_ZN14CEffectManager9hasEffectE12EEFFECT_TYPERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(lpName,"_ZN22CSkillEffectAndAffixes18getPortalSkillNameEv")
TL_FUNCTION(lpClear,"_ZN7CPlayer19clearDungeonHistoryESbIwSt11char_traitsIwESaIwEE")
namespace {
autotest::Capture* output;unsigned seed;CEffectManager* managers[4];CEffectManager* originalEffects[4];CSkillManager* originalManagers[4];CSkillEffectAndAffixes* affixes[4];CPlayer* player;Ogre::SceneManager* scene;
void number(unsigned n){output->add(&n,4);}void text(const std::wstring&s){number(s.size());if(!s.empty())output->add(s.data(),s.size()*sizeof(wchar_t));}
const wchar_t*names[]={L"",L"DUNGEON",L"other",L"\x041b\x0435\x0441"};
bool effect(CEffectManager*p,EEFFECT_TYPE t,const std::wstring&name){unsigned id=0;while(id<4&&managers[id]!=p)++id;number(10);number(id);number(t);text(name);return (seed+id)%3!=0;}
std::wstring name(CSkillEffectAndAffixes*p){unsigned id=0;while(id<4&&affixes[id]!=p)++id;number(11);number(id);return names[(seed/4+id)%4];}
void clear(CPlayer*p,std::wstring s){number(12);number(p==player);text(s);}
struct Case{unsigned mode,index;};
void execute(void*raw,autotest::Capture&out,bool ours){
 Case c=*static_cast<Case*>(raw);output=&out;seed=c.index;
 for(unsigned i=0;i<2;++i){void*q=NULL;void*a=reinterpret_cast<void*>(0x14ee340+8*i);std::memcpy(&q,a,8);if(!q){if(i)new(a)std::wstring;else new(a)std::string;}}
 finishlevel::Fixture f;f.resources.m_pSceneManager=scene;f.resources.m_pHierarchy=CMasterResourceManager::getSingleton()->m_pHierarchy;
 unsigned types[]={0,173,165,174};for(unsigned i=0;i<4;++i){std::vector<unsigned>&v=f.resources.m_pHierarchy->m_parentTypes[types[i]];v.clear();if(i&1)v.push_back(173);if(i&2)v.push_back(165);}
 finishlevel::Item*items[4];CSkillManager*skills[4];CSkill*skill[4];CSkillProperty*properties[4];CSkillEvent*events[4][3];
 CStringTranslate translation(L"");CDataGroup data(L"PORTAL",NULL,2,2,NULL);player=nativegame::createPlayer(&f.resources);
 union Client{long double alignment;unsigned char data[sizeof(CGameClient)];}client;std::memset(client.data,0,sizeof(client.data));CGameClient*receiver=reinterpret_cast<CGameClient*>(client.data);receiver->m_pPlayer=seed%5?player:NULL;f.level.m_pGameClient=seed%7?receiver:NULL;
 for(unsigned i=0;i<4;++i){
  items[i]=new finishlevel::Item(&f.resources);items[i]->m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>(types[(seed/16+i)%4]);items[i]->m_vPosition=Ogre::Vector3(float(i),float(seed%5)*.5f,float(i)*-2);items[i]->m_bBaseUnitFlag190=(seed+i)%5==0;
  originalManagers[i]=items[i]->m_pSkillManager;originalEffects[i]=items[i]->m_pEffectManager;managers[i]=new CEffectManager(items[i]);items[i]->m_pEffectManager=(seed+i)%7?managers[i]:NULL;
  skills[i]=new CSkillManager(&f.resources,items[i]);skill[i]=new CSkill(&f.resources,NULL);properties[i]=new CSkillProperty(skill[i],&f.resources,NULL,NULL,0);
  TArrayList<CSkillEvent*>*list=new TArrayList<CSkillEvent*>(1);properties[i]->m_eventLists.add((seed+i)%11?list:NULL);
  affixes[i]=new CSkillEffectAndAffixes(skill[i],&data,NULL);
  for(unsigned j=0;j<3;++j){events[i][j]=new CSkillEvent(NULL,NULL,NULL,NULL);events[i][j]->m_pSkillEffectAndAffixes=(seed+i+j)%3?affixes[i]:NULL;if(j<(seed/3+i)%4)list->add(events[i][j]);}
  if((seed+i)%11==0)delete list;
  skill[i]->m_property=(seed+i)%4?properties[i]:NULL;
  TArrayList<CSkillProperty*>*levels=reinterpret_cast<TArrayList<CSkillProperty*>*>(&skill[i]->m_levelPropertyData);
  if((seed+i)%3)levels->add((seed+i)%5?properties[i]:NULL);
  if((seed+i)%8)skills[i]->m_OtherSkills.add((seed+i)%9?skill[i]:NULL);
  // Native item construction owns a manager. Borrow this separate graph only
  // for the target, and restore the original manager before destruction.
  items[i]->m_pSkillManager=skills[i];if(seed%13==0&&i==0)items[i]->m_pSkillManager=NULL;
  if(i<seed%5)finishlevel::prepend(f.level.m_items,static_cast<CItem*>(items[i]));
 }
 TLinkedList<CItem*>*saved=f.level.m_items;if(seed%17==0)f.level.m_items=NULL;
 detour::Set hooks;TL_REDIRECT(hooks,lpEffect,&effect);TL_REDIRECT(hooks,lpName,&name);TL_REDIRECT(hooks,lpClear,&clear);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.mode==0){typedef void(*Fn)(CLevel*,std::wstring);Fn fn=ours?lpNewDelete:lpOldDelete;if(!autotest::beginInvocation(out,fn))return;fn(&f.level,names[seed%4]);out.callCompleted=1;}
 else{typedef Ogre::Vector3(*Fn)(CLevel*,std::wstring);Fn fn=ours?lpNewFind:lpOldFind;if(!autotest::beginInvocation(out,fn))return;Ogre::Vector3 p=fn(&f.level,names[seed%4]);out.callCompleted=1;out.add(&p,sizeof p);}
 for(unsigned i=0;i<4;++i){number(items[i]->m_bBaseUnitFlag190);items[i]->m_pEffectManager=originalEffects[i];delete managers[i];items[i]->m_pSkillManager=originalManagers[i];skills[i]->m_OtherSkills.clear();delete skills[i];skill[i]->m_property=NULL;skill[i]->m_iSkillLevelCount=0;delete skill[i];for(unsigned j=0;j<3;++j)events[i][j]->m_pSkillEffectAndAffixes=NULL;for(unsigned j=0;j<3;++j)delete events[i][j];if(properties[i]->m_eventLists[0])properties[i]->m_eventLists[0]->clear();if(!properties[i]->m_eventLists[0])properties[i]->m_eventLists.clear();delete properties[i];delete affixes[i];delete items[i];}
 f.level.m_items=saved;f.level.m_pGameClient=NULL;nativegame::destroyPlayer(player);
}
void original(void*p,autotest::Capture&o){execute(p,o,false);}void candidate(void*p,autotest::Capture&o){execute(p,o,true);}
int run(const tlhybrid_host*host,unsigned mode,const char*test,uintptr_t address){nativegame::Services services;if(!services.ready())return 1;scene=services.scene;autotest::Coverage coverage(test,address);for(unsigned i=0;i<512;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    portals seed%u issue%u/%u status%d/%d length%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(all_level_delete_portals){return run(host,0,"all_level_delete_portals",(uintptr_t)&lpOldDelete);}
TL_TEST(all_level_find_portal){return run(host,1,"all_level_find_portal",(uintptr_t)&lpOldFind);}
