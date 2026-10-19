#include <string>
#include <vector>
#include <map>
#include <new>
#define private public
#define protected public
#include "Player.h"
#include "Skill.h"
#include "SkillManager.h"
#include "Inventory.h"
#include "GenericModel.h"
#include "DataGroup.h"
#include "TRepository.h"
#include "ResourceManager.h"
#include "MasterResourceManager.h"
#include "SoundBank.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "UnitResourceList.h"
#include "QuestManager.h"
#include "SharedStash.h"
#include "Particle.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldPlayerUnitInit,(CPlayer*,CDataGroup*,bool),"_ZN7CPlayer8unitInitEP10CDataGroupb")
extern "C" void newPlayerUnitInit(CPlayer*,CDataGroup*,bool) __asm__("_ZN7CPlayer8unitInitEP10CDataGroupb");
TL_FUNCTION(pui_base,"_ZN10CCharacter8unitInitEP10CDataGroupb")
TL_FUNCTION(pui_section,"_ZN10CInventory10addSectionE16EINVENTORY_PANESj")
TL_FUNCTION(pui_armor,"_ZN7CPlayer21calculateNaturalArmorEv")
TL_FUNCTION(pui_particle,"_ZN16CResourceManager14createParticleEPKw")
TL_FUNCTION(pui_parent,"_ZN16CSceneNodeObject18sceneNodeSetParentEPN4Ogre9SceneNodeEb")
TL_FUNCTION(pui_position,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(pui_cycle,"_ZN10CCharacter10cycleSkillEi")
TL_FUNCTION(pui_known,"_ZN13CSkillManager11knownSkillsE22ESKILL_ACTIVATION_TYPE")
TL_FUNCTION(pui_master,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(pui_sound,"_ZN25CSoundBankDataInformation18getSoundDataObjectERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(pui_sample,"_ZN10CSoundBank9addSampleEix")
TL_FUNCTION(pui_list,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(pui_group,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEES5_")
TL_FUNCTION(pui_guid,"_ZN16CResourceManager22getUnitGuidByDataGroupEP10CDataGroupRKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(pui_quest,"_ZN13CQuestManager12getSingletonEv")
TL_FUNCTION(pui_setQuest,"_ZN7CPlayer15setQuestManagerEP13CQuestManager")
TL_FUNCTION(pui_stash,"_ZN12CSharedStash12getSingletonEv")
TL_FUNCTION(pui_setStash,"_ZN12CSharedStash9setPlayerEP7CPlayer")
namespace {
struct Case{unsigned index;};struct State{Case c;autotest::Capture*out;CPlayer*self;CDataGroup*requested,*data,*groups[4];CInventory*inventory;CParticle*particle;Ogre::SceneNode*node;CSkillManager*manager;CSkill*skills[5];CResourceManager*resources;CMasterResourceManager*master;CSoundData*sound;CUnitResourceList*list;CGenericModel*model;CQuestManager*quests;CSharedStash*stash;unsigned guidCalls;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned n){active->out->add(&n,4);}void fp(float v){active->out->add(&v,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void wide(const std::wstring&s){num(s.size());active->out->add(s.data(),s.size()*4);}void guid(long long v){active->out->add(&v,8);}unsigned sid(CSkill*p){if(!p)return 0;for(unsigned i=0;i<5;++i)if(p==active->skills[i])return i+1;return 99;}
void base(CCharacter*p,CDataGroup*g,bool f){num(1);num(p==active->self);num(g==active->requested);num(f);p->m_pDataGroup=active->data;}
void section(CInventory*p,EINVENTORY_PANES e,unsigned n){num(2);num(p==active->inventory);num(e);num(n);}void hp(CCharacter*p){num(3);p->m_maxHPBase=p->m_iMeleeStat*3+p->m_magicStat+17;}void mana(CCharacter*p){num(4);p->m_maxManaBase=p->m_rangedStat*2+p->m_defenseStat-5;}void armor(CPlayer*p){num(5);p->m_naturalArmor=p->m_defenseStat+int(hash(1)%9);}
CParticle*particle(CResourceManager*p,const wchar_t*s){num(6);num(p==active->resources);wide(s);return hash(2)%3?active->particle:NULL;}void parent(CSceneNodeObject*p,Ogre::SceneNode*n,bool f){num(7);num(p==active->particle);num(n==active->node);num(f);}void position(CPositionableObject*p,const Ogre::Vector3&v){num(8);num(p==active->particle);vec(v);p->m_vPosition=v;}
void cycle(CCharacter*p,int n){num(9);num(n);p->m_activeSkill=hash(3)%3?active->skills[4]:NULL;p->m_activeSkillGuid=p->m_activeSkill?p->m_activeSkill->m_Guid:-1;}
int known(CSkillManager*p,ESKILL_ACTIVATION_TYPE t){num(10);num(p==active->manager);num(t);return hash(4)%8;}CMasterResourceManager*master(){num(11);return active->master;}CSoundData*sound(CSoundBankDataInformation*p,const std::wstring&s){num(12);num(p==active->master->m_pSoundBankDataInformation);wide(s);return hash(5)%3?active->sound:NULL;}void sample(CSoundBank*,int n,long long g){num(13);num(n);guid(g);}CUnitResourceList*list(CResourceManager*p){num(14);num(p==active->resources);return active->list;}
CDataGroup*group(CUnitResourceList*p,const std::wstring&category,const std::wstring&name){num(15);num(p==active->list);wide(category);wide(name);const wchar_t*names[]={L"Health Potion",L"Mana Potion",L"Town Portal Scroll",L"Identify Scroll"};for(unsigned i=0;i<4;++i)if(name==names[i])return hash(6+i)%3?active->groups[i]:NULL;std::abort();return NULL;}
long long lookup(CResourceManager*p,CDataGroup*g,const std::wstring&name){num(16);num(p==active->resources);unsigned i=0;while(i<4&&g!=active->groups[i])++i;num(i);wide(name);unsigned call=active->guidCalls++;return hash(30+call)%3?static_cast<long long>(hash(40+call))*98765-17:-1;}
void*model(CPlayer*p){num(17);num(p==active->self);return hash(11)%3?active->model:NULL;}CQuestManager*quest(){num(18);return hash(12)%3?active->quests:NULL;}void setQuest(CPlayer*p,CQuestManager*q){num(19);num(p==active->self);num(q==active->quests?1:q==NULL?0:99);p->m_questManager=q;}CSharedStash*stash(){num(20);return active->stash;}void setStash(CSharedStash*p,CPlayer*o){num(21);num(p==active->stash);num(o==active->self);}
CDataGroup*data(){std::wstring empty;return new CDataGroup(L"UNIT",NULL,8,8,new TRepository<std::wstring>(empty));}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;std::memset(&s,0,sizeof s);active=&s;s.c=c;s.out=&out;s.self=static_cast<CPlayer*>(autotest::allocate(sizeof(CPlayer)));s.resources=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));s.requested=static_cast<CDataGroup*>(autotest::allocate(sizeof(CDataGroup)));s.data=data();s.inventory=static_cast<CInventory*>(autotest::allocate(sizeof(CInventory)));s.particle=static_cast<CParticle*>(autotest::allocate(sizeof(CParticle)));s.node=static_cast<Ogre::SceneNode*>(autotest::allocate(sizeof(Ogre::SceneNode)));s.manager=static_cast<CSkillManager*>(autotest::allocate(sizeof(CSkillManager)));s.master=static_cast<CMasterResourceManager*>(autotest::allocate(sizeof(CMasterResourceManager)));s.master->m_pSoundBankDataInformation=static_cast<CSoundBankDataInformation*>(autotest::allocate(sizeof(CSoundBankDataInformation)));s.sound=static_cast<CSoundData*>(autotest::allocate(sizeof(CSoundData)));s.sound->m_iGuid=0x123456789abcdLL;s.list=static_cast<CUnitResourceList*>(autotest::allocate(sizeof(CUnitResourceList)));s.model=static_cast<CGenericModel*>(autotest::allocate(sizeof(CGenericModel)));s.model->m_animationStep=.375f;s.quests=static_cast<CQuestManager*>(autotest::allocate(sizeof(CQuestManager)));s.stash=static_cast<CSharedStash*>(autotest::allocate(sizeof(CSharedStash)));for(unsigned i=0;i<4;++i)s.groups[i]=static_cast<CDataGroup*>(autotest::allocate(sizeof(CDataGroup)));
const wchar_t*keys[]={L"STRENGTH",L"DEXTERITY",L"MAGIC",L"DEFENSE"};for(unsigned i=0;i<4;++i)if(hash(50+i)%3)s.data->AddDataValue(keys[i],int(hash(60+i)%100)-30);const wchar_t*texts[]={L"MANA_GRAPH",L"HEALTH_GRAPH",L"STAT_POINTS_PER_LEVEL",L"SKILL_POINTS_PER_LEVEL",L"SKILL_POINTS_PER_FAME_LEVEL"};for(unsigned i=0;i<5;++i)if(hash(70+i)%3)s.data->AddDataValue(texts[i],hash(80+i)&1?L"":L"custom graph Ж",false);
new(&s.manager->m_OtherSkills)TArrayList<CSkill*>(3);for(unsigned i=0;i<5;++i){s.skills[i]=static_cast<CSkill*>(autotest::allocate(sizeof(CSkill)));s.skills[i]->m_Guid=hash(90+i)%5?static_cast<long long>(hash(100+i))*67891:-1;s.skills[i]->m_skillLevel=hash(110+i)%3;s.skills[i]->m_eActivationType=static_cast<ESKILL_ACTIVATION_TYPE>(hash(120+i)%6);s.skills[i]->m_bEnabled=hash(130+i)&1;s.skills[i]->m_bExecutedByProperty=hash(140+i)&1;}for(unsigned i=0;i<hash(150)%6;++i)s.manager->m_OtherSkills.add(hash(160+i)%4?s.skills[i]:NULL);
CPlayer&p=*s.self;p.m_pResourceManager=s.resources;p.m_pInventory=s.inventory;p.m_pSkillManager=hash(170)%3?s.manager:NULL;p.m_pSceneNode=s.node;p.m_levelSound=hash(171)%3?static_cast<CSoundBank*>(autotest::allocate(sizeof(CSoundBank))):NULL;p.m_activeSkillGuid=15;p.m_leftSkillGuid=16;for(unsigned i=0;i<10;++i){p.m_skillMap[i]=1000+i;p.m_leftSkillMap[i]=2000+i;}p.m_itemLinks[0]=3000;p.m_itemLinks[1]=3001;new(&p.m_manaGraph)std::wstring(L"old");new(&p.m_hpGraph)std::wstring(L"old");new(&p.m_statPointsGraph)std::wstring(L"old");new(&p.m_skillPointsGraph)std::wstring(L"old");new(&p.m_famePointsGraph)std::wstring(L"old");void**v=static_cast<void**>(autotest::allocate(0x440));v[0x418/8]=reinterpret_cast<void*>(&hp);v[0x410/8]=reinterpret_cast<void*>(&mana);v[0x1e0/8]=reinterpret_cast<void*>(&model);*reinterpret_cast<void***>(&p)=v;typedef void(*F)(CPlayer*,CDataGroup*,bool);F f=ours?newPlayerUnitInit:oldPlayerUnitInit;if(!autotest::beginInvocation(out,f))return;f(&p,s.requested,hash(172)&1);out.callCompleted=1;num(p.m_iMeleeStat);num(p.m_rangedStat);num(p.m_magicStat);num(p.m_defenseStat);fp(p.m_fHPFloat);fp(p.m_fManaFloat);num(p.m_naturalArmor);wide(p.m_manaGraph);wide(p.m_hpGraph);wide(p.m_statPointsGraph);wide(p.m_skillPointsGraph);wide(p.m_famePointsGraph);num(sid(p.m_activeSkill));guid(p.m_activeSkillGuid);guid(p.m_leftSkillGuid);for(unsigned i=0;i<10;++i){guid(p.m_skillMap[i]);guid(p.m_leftSkillMap[i]);}guid(p.m_itemLinks[0]);guid(p.m_itemLinks[1]);num(p.m_levelUpParticle==s.particle);vec(s.particle->m_vPosition);fp(s.model->m_animationStep);num(p.m_questManager==s.quests?1:p.m_questManager==NULL?0:99);
p.m_manaGraph.~basic_string();p.m_hpGraph.~basic_string();p.m_statPointsGraph.~basic_string();p.m_skillPointsGraph.~basic_string();p.m_famePointsGraph.~basic_string();s.manager->m_OtherSkills.~TArrayList();delete s.data;}
void before(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),false,o);}void after(void*p,autotest::Capture&o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(all_player_unit_init){detour::Set h;TL_REDIRECT(h,pui_base,&base);TL_REDIRECT(h,pui_section,&section);TL_REDIRECT(h,pui_armor,&armor);TL_REDIRECT(h,pui_particle,&particle);TL_REDIRECT(h,pui_parent,&parent);TL_REDIRECT(h,pui_position,&position);TL_REDIRECT(h,pui_cycle,&cycle);TL_REDIRECT(h,pui_known,&known);TL_REDIRECT(h,pui_master,&master);TL_REDIRECT(h,pui_sound,&sound);TL_REDIRECT(h,pui_sample,&sample);TL_REDIRECT(h,pui_list,&list);TL_REDIRECT(h,pui_group,&group);TL_REDIRECT(h,pui_guid,&lookup);TL_REDIRECT(h,pui_quest,&quest);TL_REDIRECT(h,pui_setQuest,&setQuest);TL_REDIRECT(h,pui_stash,&stash);TL_REDIRECT(h,pui_setStash,&setStash);if(h.failed())return 1;autotest::Coverage coverage("all_player_unit_init",0x8f8a50);for(unsigned i=0;i<4096;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    player init seed%u status%d/%d bytes%lu/%lu\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+k*4,4);std::memcpy(&y,b.capture.data+k*4,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=4096||coverage.different||coverage.missing;}
