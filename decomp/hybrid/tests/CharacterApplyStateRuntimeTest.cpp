#include <cstring>
#include <clocale>
#include <execinfo.h>
#include <fcntl.h>
#include <ucontext.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "Player.h"
#include "CharacterSaveState.h"
#include "ItemSaveState.h"
#include "Equipment.h"
#include "Inventory.h"
#include "Skill.h"
#include "SkillManager.h"
#include "Effect.h"
#include "EditorScene.h"
#include "UnitSpawner.h"
#include "DataGroup.h"
#include "TRepository.h"
#include "GameGlobals.h"
#include "Graph.h"
#include "GraphManager.h"
#undef private
#undef protected
#include "MenuGuiFixture.h"
#include "tests/FinishLevelFixture.h"
namespace {
#include "CharacterEmptyGlobals.h"
}
TL_ORIGINAL(void,caOld,(CCharacter*,CCharacterSaveState&),"_ZN10CCharacter14applySaveStateER19CCharacterSaveState")
extern "C" void caNew(CCharacter*,CCharacterSaveState&) __asm__("_ZN10CCharacter14applySaveStateER19CCharacterSaveState");
TL_FUNCTION(caPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(caLearn,"_ZN10CCharacter10learnSpellESbIwSt11char_traitsIwESaIwEEi")
TL_FUNCTION(caISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(caGenerate,"_ZN10CCharacter25generateMerchantInventoryEv")
TL_FUNCTION(caSection,"_ZN10CInventory10addSectionE16EINVENTORY_PANESj")
TL_FUNCTION(caCreate,"_ZN16CResourceManager10createUnitExibb")
TL_FUNCTION(caBehind,"_ZN10CEquipment15setRenderBehindEb")
TL_FUNCTION(caPickup,"_ZN10CInventory15pickupEquipmentEP10CEquipmentib")
TL_FUNCTION(caPrice,"_ZN10CEquipment16recalculatePriceEv")
TL_FUNCTION(caEffect,"_ZN9CBaseUnit12addNewEffectEP7CEffect")
TL_FUNCTION(caActivate,"_ZN9CBaseUnit14activateEffectEP7CEffect")
TL_FUNCTION(caObjects,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEEP10TArrayListIP17CEditorBaseObjectE")
TL_FUNCTION(caSpawned,"_ZN12CUnitSpawner14addSpawnedUnitEP9CBaseUnit")
TL_FUNCTION(caTheme,"_ZN9CBaseUnit12addUnitThemeERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(caAlignment,"_ZN10CCharacter12setAlignmentE10EAlignment")
TL_FUNCTION(caMesh,"_ZN10CCharacter14setMeshVisibleEbb")
TL_FUNCTION(caGraph,"_ZN16CResourceManager14getGraphDamageEv")
TL_FUNCTION(caNamedGraph,"_ZN13CGraphManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(caValue,"_ZNK6CGraph8getValueEfj")
TL_FUNCTION(caOwner,"_ZN6CLevel26getCharacterByOriginalGuidExxi")
TL_FUNCTION(caPet,"_ZN10CCharacter6addPetEPS_")
TL_FUNCTION(caKnown,"_ZN13CSkillManager11knownSkillsE22ESKILL_ACTIVATION_TYPE")
TL_FUNCTION(caSkillLevel,"_ZN13CSkillManager13setSkillLevelEP6CSkillj")
TL_FUNCTION(caReload,"_ZN12CGameGlobals6reloadEv")
namespace {
struct Case{unsigned seed,control;};unsigned seed,phase,created,effectCalls;bool armed,oursSide;autotest::Capture*out;nativegame::Services*services;menugui::Fixture*menu;finishlevel::Fixture*world;CCharacter*self,*master,*follower;CPlayer*player;CSkill*skills[4];CEquipment*equipment[8];CEditorScene*scenes[3];CUnitSpawner*spawners[2];CEditorBaseObject*wrong;CGraph*graph;
void fault(int signal,siginfo_t*info,void*context){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/character/character-apply-signal.log",O_WRONLY|O_CREAT|O_APPEND,0600);if(fd>=0){char line[200];ucontext_t*uc=static_cast<ucontext_t*>(context);int n=std::snprintf(line,sizeof(line),"signal%d side%u seed%u phase%u rip%llx address%p\n",signal,unsigned(oursSide),seed,phase,(unsigned long long)uc->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,line,n);void*stack[40];int count=backtrace(stack,40);backtrace_symbols_fd(stack,count,fd);close(fd);}raise(signal);}
void num(unsigned x){if(armed)out->add(&x,4);}void integer(long long x){if(armed)out->add(&x,8);}void fp(float x){if(armed)out->add(&x,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void wide(const std::wstring&s){num(s.size());if(armed)out->add(s.data(),s.size()*sizeof(wchar_t));}unsigned id(const void*p){if(!p)return 0;if(p==self)return 1;if(p==master)return 2;if(p==player)return 3;if(p==follower)return 4;for(unsigned i=0;i<4;++i)if(p==skills[i])return 10+i;for(unsigned i=0;i<created;++i)if(p==equipment[i])return 20+i;return 99;}
class Actor:public CCharacter{public:Actor():CCharacter(NULL){}virtual void setLevel(unsigned level,bool apply){num(101);num(level);num(apply);m_iUnitLevel=level;}virtual void setAIState(EAIState state){num(103);num(state);m_eAIState=state;}virtual void setEnabled(bool flag){num(107);num(flag);m_bEnabled=flag;}virtual void setScale(float scale){num(109);fp(scale);m_vScale=Ogre::Vector3(scale,scale,scale);}virtual void setOrientation(const Ogre::Matrix4&m,bool translation){num(113);num(translation);for(unsigned i=0;i<4;++i)for(unsigned k=0;k<4;++k)fp(m[i][k]);m_mOrientation=m;}};
class Equipment:public CEquipment{public:Equipment():CEquipment(NULL){}virtual ~Equipment(){num(127);num(id(this));}virtual void applySaveState(CItemSaveState&s){num(131);num(id(this));num(s.m_iIndex);integer(s.m_iUnitValue60);num(self->m_pInventory->m_bUnknown15);num(s.m_iStackSize);}};
class Inventory:public CInventory{public:Inventory(CCharacter*p):CInventory(p,17){}virtual ~Inventory(){num(137);}};
void position(CPositionableObject*p,const Ogre::Vector3&v){num(139);num(id(p));vec(v);p->m_vPosition=v;}
void learn(CCharacter*p,std::wstring name,int level){num(149);num(id(p));wide(name);num(level);}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){num(151);num(id(p));num(type);if(type==static_cast<UNITTYPES::EUNITTYPES>(41))return seed%4==0;if(type==static_cast<UNITTYPES::EUNITTYPES>(130))return seed%4==1;if(type==static_cast<UNITTYPES::EUNITTYPES>(127))return seed%3==0;return type==static_cast<UNITTYPES::EUNITTYPES>(28)&&seed%5==0;}
void generate(CCharacter*p){num(157);num(id(p));num(p->m_pInventory!=NULL);fp(p->m_playTime);}
void section(CInventory*p,EINVENTORY_PANES pane,unsigned count){num(163);num(p==self->m_pInventory);num(pane);num(count);}
CBaseUnit*create(CResourceManager*p,long long guid,int count,bool a,bool b){num(167);num(p==&world->resources);integer(guid);num(count);num(a);num(b);if(guid%3==0)return NULL;Equipment*e=new Equipment;equipment[created++]=e;return e;}
void behind(CEquipment*p,bool flag){num(173);num(id(p));num(flag);}
CEquipment*pickup(CInventory*p,CEquipment*e,int slot,bool flag){num(179);num(p==self->m_pInventory);num(id(e));num(slot);num(flag);num(p->m_bUnknown15);return(seed+unsigned(slot))%3==0?NULL:e;}
void price(CEquipment*p){num(181);num(id(p));}
CEffect*effect(CBaseUnit*p,CEffect*e){num(191);num(id(p));fp(e->m_fValueC0);bool keep=(seed+effectCalls++)%3!=0;if(keep)e->m_fValueC0=-777;return keep?e:NULL;}
void activate(CBaseUnit*p,CEffect*e){num(193);num(id(p));fp(e->m_fValueC0);}
void objects(CEditorScene*p,const std::wstring&name,TArrayList<CEditorBaseObject*>*list){num(197);unsigned index=0;while(index<3&&p!=scenes[index])++index;num(index);wide(name);num(list->size());if((seed+index)%2)list->add(wrong);if((seed+index)%3)list->add(spawners[0]);list->add(spawners[1]);list->add(NULL);}
void spawned(CUnitSpawner*p,CBaseUnit*unit){num(199);num(p==spawners[0]?1:p==spawners[1]?2:99);num(id(unit));}
void theme(CBaseUnit*p,const std::wstring&name){num(211);num(id(p));wide(name);}
void alignment(CCharacter*p,EAlignment value){num(223);num(id(p));num(value);p->m_alignment=value;}
void mesh(CCharacter*p,bool visible,bool recursive){num(227);num(id(p));num(visible);num(recursive);p->m_forcedHidden=!visible;}
CGraph*getGraph(CResourceManager*p){num(229);num(p==&world->resources);return graph;}
CGraph*named(CGraphManager*,const std::wstring&name){num(233);wide(name);return graph;}
float value(CGraph*p,float x,unsigned line){num(239);num(p==graph);fp(x);num(line);return float(seed%13)-3.75f;}
CCharacter*owner(CLevel*p,long long guid,long long parent,int room){num(241);num(p==&world->level);integer(guid);integer(parent);num(room);return seed%3==0?master:NULL;}
void pet(CCharacter*p,CCharacter*child){num(251);num(id(p));num(id(child));child->m_pMaster=p;}
int known(CSkillManager*p,ESKILL_ACTIVATION_TYPE activation){num(257);num(p==self->m_pSkillManager);num(activation);return seed%5;}
void skillLevel(CSkillManager*p,CSkill*s,unsigned level){num(263);num(p==self->m_pSkillManager);num(id(s));num(level);s->m_skillLevel=level;}
void reload(CGameGlobals*){}
void snapshot(){vec(self->m_vPosition);vec(self->m_vScale);wide(self->m_characterDisplayName);integer(self->getOriginalGuid());integer(self->m_iQuestGuid);num(self->m_iQuestState);num(self->m_iRoomIndex);num(self->m_bEnabled);num(self->m_iUnitLevel);num(self->m_fameLevel);num(self->m_petMode);num(self->m_bSecondaryWeaponSet);for(unsigned i=0;i<7;++i)num(self->m_damageDefense[i]);fp(self->m_playTime);fp(self->m_bravery);num(self->m_champion);num(self->m_alwaysActive);integer(self->m_originalUnitGuid);num(self->m_experience);num(self->m_fame);fp(self->m_fHPFloat);num(self->m_maxHPBonus);num(self->m_maxHPBase);fp(self->m_fManaFloat);num(self->m_maxManaBase);fp(self->m_maxManaBonus);num(self->m_defenseStat);num(self->m_magicStat);num(self->m_rangedStat);num(self->m_iMeleeStat);num(self->m_experienceReward);num(self->m_fameReward);num(self->m_iUnusedStatPoints);num(self->m_iUnusedSkillPoints);num(self->m_iUnusedPerkPoints);num(self->m_iGold);integer(self->m_activeSkillGuid);integer(self->m_leftSkillGuid);integer(self->m_leftMouseSkillGuid);num(self->m_bInvulnerable);fp(self->m_transformationTime);fp(self->m_townTravelTime);num(self->m_eAIState);num(self->m_alignment);num(self->m_forcedHidden);num(self->m_value6D0);num(id(self->m_pMaster));num(self->m_pInventory!=NULL);if(self->m_pInventory){num(self->m_pInventory->m_bUnknown14);num(self->m_pInventory->m_bUnknown15);}for(unsigned i=0;i<4;++i)num(skills[i]->m_skillLevel);}
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;phase=1;oursSide=ours;armed=false;out=&capture;created=effectCalls=0;std::memset(equipment,0,sizeof(equipment));struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_sigaction=&fault;action.sa_flags=SA_SIGINFO|SA_RESETHAND;sigemptyset(&action.sa_mask);sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);
 self=new Actor;master=new CCharacter(NULL);follower=new CCharacter(NULL);player=nativegame::createPlayer(&world->resources);master->setOriginalGuid(200);player->setOriginalGuid(201);follower->setOriginalGuid(202);player->m_Followers.push_back(follower);menu->nativeClient.client->m_pPlayer=player;world->resources.m_GameClients.clear();world->resources.m_GameClients.add(menu->nativeClient.client);self->m_pResourceManager=&world->resources;self->m_pInventory=seed%3?new Inventory(self):NULL;TSafePointer<CRunicCore>oldInventory;oldInventory.setObject(self->m_pInventory);if(self->m_pInventory){self->m_pInventory->m_bUnknown14=true;self->m_pInventory->m_bUnknown15=false;}self->m_bInvulnerable=false;self->m_alwaysActive=seed&1;self->m_forcedHidden=seed&2;self->m_Padding4A1[0]=bool(seed&4);self->setOriginalGuid(99);self->m_pSkillManager=seed%4?new CSkillManager(NULL,self):NULL;
 for(unsigned i=0;i<4;++i){skills[i]=new CSkill(NULL,NULL);skills[i]->m_skillLevel=77;if(self->m_pSkillManager)self->m_pSkillManager->m_OtherSkills.add((seed+i)%3?skills[i]:NULL);}self->m_pDataGroup=seed%7?new CDataGroup(L"loaded",NULL,4,4,new TRepository<std::wstring>(L"")):NULL;if(self->m_pDataGroup)self->m_pDataGroup->AddDataValue(L"BOSS_CHAMPION",bool(seed&16));
 for(unsigned i=0;i<7;++i){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x14abf40+i*8),8);if(!p)new(reinterpret_cast<void*>(0x14abf40+i*8))std::wstring(L"unit");}spawners[0]=new CUnitSpawner(NULL);spawners[1]=new CUnitSpawner(NULL);spawners[0]->setOriginalGuid(301);spawners[1]->setOriginalGuid(302);wrong=new CEditorBaseObject;world->level.m_RoomScenes.clear();for(unsigned i=0;i<3;++i){scenes[i]=new CEditorScene(L"apply-state");if(i<seed%4)world->level.m_RoomScenes.add(scenes[i]);}
 CCharacterSaveState state;state.m_position=Ogre::Vector3(seed*.25f,-3,7);state.m_orientation=Ogre::Matrix4::IDENTITY;state.m_orientation[0][3]=4;state.m_name=seed%2?L"saved Ж":L"";state.m_value184=int(seed%9)-3;state.m_flag31=seed&1;state.m_valueD0=seed%17;state.m_valueD8=int(seed%9)-4;state.m_guid10=seed%5?0x1234000000LL+seed:-1;state.m_petMode=seed%4;state.m_flag33=seed&2;state.m_guid200=0x556600000000LL+seed;state.m_value208=seed%11;for(unsigned i=0;i<7;++i)state.m_damageDefense[i]=seed+i*13;state.m_playTime=(seed/4)%2?10:100;state.m_scale=.25f*float(seed%5);state.m_bravery=-float(seed)*.1f;state.m_flag32=seed&8;state.m_guid28=0x123456780000LL+seed;state.m_valueD4=seed*17;state.m_valueDC=seed*19;state.m_hp=seed*.3f;state.m_valueE8=seed+3;state.m_valueE4=seed+7;state.m_mana=seed*.7f;state.m_maxManaBase=int(seed)-13;state.m_maxManaBonus=int(seed)-17;state.m_defenseStat=seed+1;state.m_magicStat=seed+2;state.m_rangedStat=seed+3;state.m_meleeStat=seed+4;state.m_experienceReward=seed+5;state.m_fameReward=seed+6;state.m_freeStatPoints=seed+7;state.m_freeSkillPoints=seed+8;state.m_freePerkPoints=seed+9;state.m_value174=seed+10;state.m_guidB8=1000+seed;state.m_guidC0=2000+seed;state.m_guidC8=3000+seed;for(unsigned i=0;i<4;++i){state.m_knownSpells[i]=(seed+i)%3?L"spell Ж":L"";state.m_spellLevels[i]=i+seed;}for(unsigned i=0;i<(seed/3)%5;++i)state.m_values.push_back(i*13+seed);
 for(unsigned i=0;i<seed%5;++i){CItemSaveState*s=new CItemSaveState;s->m_iUnitValue60=i==0?-1LL:100LL+i;s->m_iIndex=int(i)-2;s->m_iStackSize=i+3;state.m_pets.push_back(s);}for(unsigned g=0;g<3;++g)for(unsigned i=0;i<(seed+g)%3;++i){CEffect*e=new CEffect(static_cast<EEFFECT_TYPE>(0),false,static_cast<EEFFECT_ACTIVATION>(g),1,2,3,false);e->m_fValueC0=seed+g*13+i;state.m_items[g].push_back(e);}state.m_guid58=seed%3?-1:301+(seed/3)%3;state.m_transformationTime=float(seed)-9;state.m_townTravelTime=seed%3?0:7;state.m_alignment=seed%7;state.m_flag20C=seed&4;state.m_guid50=seed%5?199+seed%5:-1;
 detour::Set patches;
#define P(name,fn) TL_REDIRECT(patches,ca##name,&fn)
 P(Position,position); P(Learn,learn); P(ISA,isa); P(Generate,generate); P(Section,section); P(Create,create); P(Behind,behind); P(Pickup,pickup); P(Price,price); P(Effect,effect); P(Activate,activate); P(Objects,objects); P(Spawned,spawned); P(Theme,theme); P(Alignment,alignment); P(Mesh,mesh); P(Graph,getGraph); P(NamedGraph,named); P(Value,value); P(Owner,owner); P(Pet,pet); P(Known,known); P(SkillLevel,skillLevel);
#undef P
 if(patches.failed())_exit(43);phase=100;armed=true;typedef void(*F)(CCharacter*,CCharacterSaveState&);F fn=ours?caNew:caOld;if(!autotest::beginInvocation(capture,fn))return;fn(self,state);capture.callCompleted=1;phase=101;if(ours&&c.control)++self->m_iGold;snapshot();num(oldInventory.getObject()==NULL);for(unsigned i=0;i<4;++i)wide(state.m_knownSpells[i]);for(unsigned g=0;g<3;++g)num(state.m_items[g].size());armed=false;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(character_apply_runtime){std::setlocale(LC_CTYPE,"C.UTF-8");initEmptyGlobals();tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services native;if(!native.ready())return 1;services=&native;menugui::Audio audio(native.master);CStringTranslate translate(L"");menugui::Fixture gui(*native.settings,native.scene);menu=&gui;finishlevel::Fixture level;world=&level;world->resources.m_pLevel=&world->level;world->resources.m_pSceneManager=native.scene;graph=new CGraph(GRAPH_LINEAR,L"apply-fixture",1);if(!CGameGlobals::getSingleton()){detour::Set setup;TL_REDIRECT(setup,caReload,&reload);if(setup.failed())return 1;new CGameGlobals(L"fixture");}CGameGlobals::getSingleton()->m_merchantRespawnTime=60;int failures=0;autotest::Coverage coverage("character_apply_runtime",(uintptr_t)&caOld);for(unsigned i=0;i<512;++i){Case c={i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    apply seed%u status%d/%d bytes%lu/%lu\n",i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}for(unsigned j=0;j+3<a.capture.length&&j+3<b.capture.length&&j<400;j+=4){unsigned x,y;std::memcpy(&x,a.capture.data+j,4);std::memcpy(&y,b.capture.data+j,4);host->log("    word%u %u/%u\n",j/4,x,y);}coverage.report(host);return failures;}}coverage.report(host);Case c={31,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    apply negative detected%u\n",unsigned(caught));return failures;}
