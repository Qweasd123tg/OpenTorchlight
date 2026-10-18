#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <stdint.h>
#include <new>
#include <OgreSceneManager.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#define protected public
#include "LayoutDescriptor.h"
#include "MonsterDescriptor.h"
#include "Layout.h"
#include "Monster.h"
#include "ResourceManager.h"
#include "Level.h"
#include "LevelTemplateData.h"
#include "GameClient.h"
#undef private
#undef protected
#define TARGET(ret,old,newer,args,symbol) TL_ORIGINAL(ret,old,args,symbol) extern "C" ret newer args __asm__(symbol);
TARGET(void,cdOldLoaded,cdNewLoaded,(CLayoutDescriptor*,CEditorScene*),"_ZN17CLayoutDescriptor21descriptorSceneLoadedEP12CEditorScene")
TARGET(void,cdOldActivated,cdNewActivated,(CLayoutDescriptor*,CEditorScene*),"_ZN17CLayoutDescriptor24descriptorSceneActivatedEP12CEditorScene")
TARGET(void,cdOldReload,cdNewReload,(CMonsterDescriptor*),"_ZN18CMonsterDescriptor14ReloadMonstersEv")
TARGET(void,cdOldInput,cdNewInput,(CMonsterDescriptor*,CEditorBaseObject*,unsigned,CEditorBaseObject*),"_ZN18CMonsterDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
TARGET(void,cdOldMonsterActivated,cdNewMonsterActivated,(CMonsterDescriptor*,CEditorScene*),"_ZN18CMonsterDescriptor24descriptorSceneActivatedEP12CEditorScene")
TL_FUNCTION(cdInit,"_ZN7CLayout10initOnLoadEv")
TL_FUNCTION(cdLoops,"_ZN12CEditorScene30getNumberOfTimelinesThatDoLoopEv")
TL_FUNCTION(cdStart,"_ZN7CLayout5startEv")
TL_FUNCTION(cdStop,"_ZN7CLayout4stopEb")
TL_FUNCTION(cdActive,"_ZN12CEditorScene12setActivatedEb")
TL_FUNCTION(cdDelete,"_ZN12CEditorScene23deleteUnusedDescriptorsEv")
TL_FUNCTION(cdConvert,"_ZN10CCharacter16convertCharacterESbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(cdVisible,"_ZN10CCharacter10setVisibleEb")
TL_FUNCTION(cdEnabled,"_ZN16CSceneNodeObject10setEnabledEb")
TL_FUNCTION(cdMesh,"_ZN10CCharacter14setMeshVisibleEbb")
TL_FUNCTION(cdParticles,"_ZN10CCharacter13stopParticlesEb")
TL_FUNCTION(cdQuest,"_ZN13CQuestManager12getSingletonEv")
TL_FUNCTION(cdIcon,"_ZN13CQuestManager16calculateNPCIconEP10CCharacter")
TL_FUNCTION(cdBroadcast,"_ZN17CEditorBaseObject14BroadcastEventEj")
TL_FUNCTION(cdUI,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(cdDialog,"_ZN7CGameUI22forceInteractiveDialogEP7CPlayerP9CBaseUnitP6CQuest")
TL_FUNCTION(cdPath,"_ZN10CCharacter11stopPathingEv")
TL_FUNCTION(cdAIState,"_ZN10CCharacter10setAIStateE8EAIState")
TL_FUNCTION(cdPlayerAI,"_ZN7CPlayer10setAIStateE8EAIState")
TL_FUNCTION(cdPlayer,"_ZN6CLevel9getPlayerEv")
TL_FUNCTION(cdAffix,"_ZN9CBaseUnit8addAffixERKSbIwSt11char_traitsIwESaIwEEjPS_f")
TL_FUNCTION(cdRemoveAffix,"_ZN9CBaseUnit11removeAffixERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cdFlag,"_ZN10CAIManager9addAIFlagE13EAIFLAG_TYPESf")
TL_FUNCTION(cdTarget,"_ZN10CCharacter9setTargetEPS_")
TL_FUNCTION(cdAddPet,"_ZN10CCharacter6addPetEPS_")
TL_FUNCTION(cdRemovePet,"_ZN10CCharacter9removePetEPS_")
TL_FUNCTION(cdHP,"_ZN10CCharacter7HPFloatEv")
TL_FUNCTION(cdMaxHP,"_ZN10CCharacter5maxHPEv")
TL_FUNCTION(cdModify,"_ZN10CCharacter8modifyHPEf")
TL_FUNCTION(cdSkills,"_ZN13CSkillManager13stopAllSkillsEbbb")
TL_FUNCTION(cdDie,"_ZN10CCharacter3dieEPS_PKN4Ogre7Vector3Efb")

TL_FUNCTION(cdEditor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(cdOrientation,"_ZN19CPositionableObject32getOrientationQuaternionAbsoluteEv")
TL_FUNCTION(cdSetOrientation,"_ZN19CPositionableObject14setOrientationERKN4Ogre10QuaternionE")
TL_FUNCTION(cdPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(cdParent,"_ZN16CSceneNodeObject18sceneNodeSetParentEPN4Ogre9SceneNodeEb")
TL_FUNCTION(cdRemoveCharacter,"_ZN6CLevel15removeCharacterEP10CCharacterb")
TL_FUNCTION(cdAddCharacter,"_ZN6CLevel12addCharacterEP10CCharacterRKN4Ogre7Vector3Eb")
TL_FUNCTION(cdFollowPath,"_ZN10CCharacter21setPathToFollowByNameERKSbIwSt11char_traitsIwESaIwEE")
extern "C" char cdLayoutTable[] __asm__("_ZTV7CLayout");
extern "C" char cdMonsterTable[] __asm__("_ZTV8CMonster");
extern "C" char cdPlayerTable[] __asm__("_ZTV7CPlayer");
extern "C" char cdBaseTable[] __asm__("_ZTV17CEditorBaseObject");
namespace {
struct Case{unsigned mode,seed;};autotest::Capture* out;unsigned seed,variant;void* current;void* player;void* follower;void* ai;void* skill;void* scene;void* level;void* ui;void* quest;CResourceManager* activeResources;void* manager;void* rootNode;
void number(unsigned x){out->add(&x,4);}void real(float x){out->add(&x,4);}void identity(void*p,void*expect){number(p==expect);if(p!=expect)out->issue=autotest::Capture::InvalidReport;}
void init(void*p){number(1);identity(p,current);}unsigned loops(void*p){number(2);identity(p,current);return variant&2?0:2;}
void start(void*p){number(3);identity(p,current);}void stop(void*p,bool v){number(4);identity(p,current);number(v);}void active(void*p,bool v){number(5);identity(p,current);number(v);}void remove(void*p){number(6);identity(p,current);}
void convert(void*p,std::wstring name,bool flag){number(7);identity(p,current);out->addText(name);number(flag);}bool enabledGet(void*p){number(8);identity(p,current);return variant&4;}void visible(void*p,bool v){number(9);identity(p,current);number(v);}void enabled(void*p,bool v){number(10);identity(p,current);number(v);}
void mesh(void*p,bool v,bool cascade){number(11);identity(p,current);number(v);number(cascade);}void particles(void*p,bool v){number(12);identity(p,current);number(v);}void* getQuest(){number(13);return quest;}void icon(void*p,void*target){number(14);identity(p,quest);identity(target,current);}void broadcast(void*p,unsigned event){number(15);identity(p,current);number(event);}void* getUI(){number(16);return ui;}void dialog(void*p,void*a,void*b,void*q){number(17);identity(p,ui);identity(a,player);identity(b,current);number(q==NULL);}void path(void*p){number(18);identity(p,player);}void state(void*p,unsigned value){number(19);number(p==player?1:p==current?2:0);number(value);}void* getPlayer(void*p){number(20);identity(p,level);return player;}
void* affix(void*p,const std::wstring& name,unsigned value,void*source,float scale){number(21);identity(p,current);out->addText(name);number(value);identity(source,current);real(scale);return NULL;}bool removeAffix(void*p,const std::wstring& name){number(22);identity(p,current);out->addText(name);return variant&1;}void flag(void*p,unsigned v,float time){number(23);identity(p,ai);number(v);real(time);}void target(void*p,void*t){number(24);identity(p,current);number(t==NULL?0:t==player?1:2);}void addPet(void*p,void*t){number(25);identity(p,player);identity(t,current);}void removePet(void*p,void*t){number(26);identity(p,player);identity(t,current);}float hp(void*p){number(27);identity(p,current);return variant&2?-0.0f:123.75f;}int maxHP(void*p){number(28);identity(p,current);return variant&2?-7:4097;}void modify(void*p,float change){number(29);number(p==current?1:p==follower?2:0);real(change);}void skills(void*p,bool a,bool b,bool c){number(30);identity(p,skill);number(a);number(b);number(c);}void die(void*p,void*a,void*b,float f,bool flag){number(31);identity(p,follower);number(a==NULL);number(b==NULL);real(f);number(flag);}

bool editor(void*p){number(32);identity(p,activeResources);return variant&16;}
Ogre::Quaternion orientation(void*p){number(33);identity(p,current);return Ogre::Quaternion(0.25f,0.5f,-0.75f,seed*0.125f);}
void setOrientation(void*p,const Ogre::Quaternion& q){number(34);identity(p,current);out->add(&q,16);}
Ogre::Vector3 position(void*p,bool absolute){number(35);identity(p,current);number(absolute);if(variant&8)activeResources->m_pLevel=NULL;return Ogre::Vector3(seed*1.25f,-2.5f,3.75f);}
void* root(void*p){number(36);identity(p,manager);return rootNode;}
void parent(void*p,void*n,bool keep){number(37);identity(p,current);identity(n,rootNode);number(keep);}
void removeCharacter(void*p,void*character,bool flag){number(38);identity(p,level);identity(character,current);number(flag);}
void* addCharacter(void*p,void*character,const Ogre::Vector3& v,bool activate){number(39);identity(p,level);identity(character,current);out->add(&v,12);number(activate);return character;}
void followPath(void*p,const std::wstring& path){number(40);identity(p,current);out->addText(path);}
void side(void*raw,autotest::Capture& capture,bool ours){Case c=*static_cast<Case*>(raw);out=&capture;seed=c.seed;variant=seed^(3*(seed/72));uint64_t descMem[128]={0},layoutMem[(sizeof(CLayout)+7)/8]={0},monsterMem[(sizeof(CMonster)+7)/8]={0},followerMem[(sizeof(CMonster)+7)/8]={0},playerMem[1024]={0},sceneMem[(sizeof(CEditorScene)+7)/8]={0},resMem[(sizeof(CResourceManager)+7)/8]={0},levelMem[(sizeof(CLevel)+7)/8]={0},clientMem[(sizeof(CGameClient)+7)/8]={0};uint64_t templateMem[(sizeof(CLevelTemplateData)+7)/8]={0},managerMem[8]={0},rootMem[8]={0};void* managerTable[80]={0};managerTable[0x250/8]=reinterpret_cast<void*>(&root);managerMem[0]=reinterpret_cast<uintptr_t>(managerTable);manager=managerMem;rootNode=rootMem;void* table[134];std::memcpy(table,cdMonsterTable,sizeof(table));table[2+6]=reinterpret_cast<void*>(&broadcast);table[2+9]=reinterpret_cast<void*>(&enabledGet);CLayout* layout=reinterpret_cast<CLayout*>(layoutMem);CMonster* monster=reinterpret_cast<CMonster*>(monsterMem);CMonster* follow=reinterpret_cast<CMonster*>(followerMem);CResourceManager* resources=reinterpret_cast<CResourceManager*>(resMem);CEditorScene* owner=reinterpret_cast<CEditorScene*>(sceneMem);CLevel* lev=reinterpret_cast<CLevel*>(levelMem);CGameClient* client=reinterpret_cast<CGameClient*>(clientMem);CDescriptor* desc=reinterpret_cast<CDescriptor*>(descMem);activeResources=resources;resources->m_pSceneManager=reinterpret_cast<Ogre::SceneManager*>(manager);lev->m_pLevelTemplateData=reinterpret_cast<CLevelTemplateData*>(templateMem);lev->m_flag1A1=variant&1;lev->m_pLevelTemplateData->m_isTown=variant&2;scene=owner;level=lev;player=playerMem;follower=follow;current=c.mode<2?static_cast<void*>(layout):static_cast<void*>(monster);ai=descMem+100;skill=descMem+104;ui=descMem+108;quest=descMem+112;
 *reinterpret_cast<void**>(layout)=cdLayoutTable+16;*reinterpret_cast<void**>(monster)=table+2;*reinterpret_cast<void**>(follow)=cdMonsterTable+16;*reinterpret_cast<void**>(player)=(c.mode==2?cdBaseTable:cdPlayerTable)+16;monster->m_pResourceManager=resources;owner->m_pResourceManager=resources;resources->m_pLevel=lev;new(&resources->m_GameClients)TArrayList<CGameClient*>(2);resources->m_GameClients.add(client);client->m_pPlayer=reinterpret_cast<CPlayer*>(player);new(&desc->m_Objects)TArrayList<CEditorBaseObject*>(2);desc->m_pSceneOwner=owner;
 unsigned kind=c.mode==3?(seed/24)%3:seed%4;desc->m_Objects.add(kind==1?NULL:kind==2?reinterpret_cast<CEditorBaseObject*>(player):static_cast<CEditorBaseObject*>(current));layout->m_bStartOnLoad=variant&1;layout->m_Unknown1B8=static_cast<ELAYOUT_TYPES>(seed%3);lev->m_flag258=variant&4;if(seed%7==0)resources->m_pLevel=NULL;monster->m_pAIManager=variant&1?reinterpret_cast<CAIManager*>(ai):NULL;monster->m_pSkillManager=variant&2?reinterpret_cast<CSkillManager*>(skill):NULL;monster->m_bInvulnerable=variant&1;monster->m_targetLocked=variant&2;monster->m_damageShapeEnabled=variant&4;monster->m_bVisible=variant&1;monster->m_forcedHidden=variant&4;monster->m_bBaseUnitFlag190=variant&2;monster->m_bSaveFlag191=variant&4;new(&monster->m_pathName)std::wstring(variant&1?L"Жpath":L"");new(&monster->m_sName)std::wstring(variant&2?L"Жmonster":L"");new(&monster->m_Followers)std::vector<CCharacter*>;monster->m_Followers.push_back(NULL);if(variant&1)monster->m_Followers.push_back(follow);monster->m_Followers.push_back(follow);
 detour::Set d;TL_REDIRECT(d,cdInit,&init);TL_REDIRECT(d,cdLoops,&loops);TL_REDIRECT(d,cdStart,&start);TL_REDIRECT(d,cdStop,&stop);TL_REDIRECT(d,cdActive,&active);TL_REDIRECT(d,cdDelete,&remove);TL_REDIRECT(d,cdConvert,&convert);TL_REDIRECT(d,cdVisible,&visible);TL_REDIRECT(d,cdEnabled,&enabled);TL_REDIRECT(d,cdMesh,&mesh);TL_REDIRECT(d,cdParticles,&particles);TL_REDIRECT(d,cdQuest,&getQuest);TL_REDIRECT(d,cdIcon,&icon);TL_REDIRECT(d,cdUI,&getUI);TL_REDIRECT(d,cdDialog,&dialog);TL_REDIRECT(d,cdPath,&path);TL_REDIRECT(d,cdAIState,&state);TL_REDIRECT(d,cdPlayerAI,&state);TL_REDIRECT(d,cdPlayer,&getPlayer);TL_REDIRECT(d,cdAffix,&affix);TL_REDIRECT(d,cdRemoveAffix,&removeAffix);TL_REDIRECT(d,cdFlag,&flag);TL_REDIRECT(d,cdTarget,&target);TL_REDIRECT(d,cdAddPet,&addPet);TL_REDIRECT(d,cdRemovePet,&removePet);TL_REDIRECT(d,cdHP,&hp);TL_REDIRECT(d,cdMaxHP,&maxHP);TL_REDIRECT(d,cdModify,&modify);TL_REDIRECT(d,cdSkills,&skills);TL_REDIRECT(d,cdDie,&die);
 if(d.failed()){capture.issue=autotest::Capture::InvalidReport;return;}
 if(c.mode==4){TL_REDIRECT(d,cdEditor,&editor);TL_REDIRECT(d,cdOrientation,&orientation);TL_REDIRECT(d,cdSetOrientation,&setOrientation);TL_REDIRECT(d,cdPosition,&position);TL_REDIRECT(d,cdParent,&parent);TL_REDIRECT(d,cdRemoveCharacter,&removeCharacter);TL_REDIRECT(d,cdAddCharacter,&addCharacter);TL_REDIRECT(d,cdFollowPath,&followPath);typedef void(*Fn)(CMonsterDescriptor*,CEditorScene*);Fn fn=ours?cdNewMonsterActivated:cdOldMonsterActivated;if(d.failed()){out->issue=autotest::Capture::InvalidReport;return;}if(!autotest::beginInvocation(capture,fn))return;fn(reinterpret_cast<CMonsterDescriptor*>(desc),owner);capture.callCompleted=1;number(monster->m_bBaseUnitFlag190);number(monster->m_bSaveFlag191);number(monster->m_forcedHidden);number(resources->m_pLevel==NULL);
 }else if(c.mode<2){typedef void(*Fn)(CLayoutDescriptor*,CEditorScene*);Fn fn=c.mode==0?(ours?cdNewLoaded:cdOldLoaded):(ours?cdNewActivated:cdOldActivated);if(!autotest::beginInvocation(capture,fn))return;fn(reinterpret_cast<CLayoutDescriptor*>(desc),owner);capture.callCompleted=1;
 }else if(c.mode==2){typedef void(*Fn)(CMonsterDescriptor*);Fn fn=ours?cdNewReload:cdOldReload;if(!autotest::beginInvocation(capture,fn))return;fn(reinterpret_cast<CMonsterDescriptor*>(desc));capture.callCompleted=1;
 }else{const unsigned events[]={0,1,2,3,4,48,49,50,61,62,63,64,65,70,71,72,73,74,82,83,84,0xffffffffu,0x80000000u,60};unsigned event=events[seed%24];if(event==61||event==64)resources->m_pLevel=lev;typedef void(*Fn)(CMonsterDescriptor*,CEditorBaseObject*,unsigned,CEditorBaseObject*);Fn fn=ours?cdNewInput:cdOldInput;if(!autotest::beginInvocation(capture,fn))return;fn(reinterpret_cast<CMonsterDescriptor*>(desc),kind==1?NULL:kind==2?reinterpret_cast<CEditorBaseObject*>(player):monster,event,NULL);capture.callCompleted=1;number(monster->m_bInvulnerable);number(monster->m_targetLocked);number(monster->m_damageShapeEnabled);}
 monster->m_pathName.~basic_string();monster->m_Followers.~vector();monster->m_sName.~basic_string();desc->m_Objects.~TArrayList();resources->m_GameClients.~TArrayList();
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char* name,uintptr_t address,unsigned count){autotest::Coverage coverage(name,address);for(unsigned i=0;i<count;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(h,a,b)){h->log("    descriptors op%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",mode,i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k<a.capture.length&&k<b.capture.length;k+=4){unsigned av=0,bv=0;std::memcpy(&av,a.capture.data+k,4);std::memcpy(&bv,b.capture.data+k,4);h->log("    word%u %x/%x\n",k,av,bv);}coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(continuation_layout_loaded){return run(host,0,"continuation_layout_loaded",(uintptr_t)&cdOldLoaded,48);}
TL_TEST(continuation_layout_activated){return run(host,1,"continuation_layout_activated",(uintptr_t)&cdOldActivated,48);}
TL_TEST(continuation_monster_reload){return run(host,2,"continuation_monster_reload",(uintptr_t)&cdOldReload,32);}
TL_TEST(continuation_monster_input){return run(host,3,"continuation_monster_input",(uintptr_t)&cdOldInput,96);}

TL_TEST(continuation_monster_activated){return run(host,4,"continuation_monster_activated",(uintptr_t)&cdOldMonsterActivated,48);}
