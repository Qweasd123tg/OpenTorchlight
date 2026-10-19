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
#include "GenericModel.h"
#include "Skill.h"
#include "SkillManager.h"
#include "Equipment.h"
#include "Inventory.h"
#include "AttackDescription.h"
#include "AstarPathfinder.h"
#include "SoundBank.h"
#undef private
#undef protected
#include "MenuGuiFixture.h"
#include "tests/FinishLevelFixture.h"
namespace {
#include "CharacterEmptyGlobals.h"
}
TL_ORIGINAL(bool,csOld,(CCharacter*,long long),"_ZN10CCharacter9castSkillEx")
extern "C" bool csNew(CCharacter*,long long) __asm__("_ZN10CCharacter9castSkillEx");
TL_FUNCTION(csKnown,"_ZN13CSkillManager11knownSkillsE22ESKILL_ACTIVATION_TYPE")
TL_FUNCTION(csFind,"_ZN13CSkillManager14getSkillByGuidEx")
TL_FUNCTION(csMana,"_ZN10CCharacter4manaEv")
TL_FUNCTION(csCost,"_ZN6CSkill11getManaCostEv")
TL_FUNCTION(csCostOT,"_ZN6CSkill13getManaCostOTEv")
TL_FUNCTION(csType,"_ZN6CSkill13getTargetTypeEv")
TL_FUNCTION(csRange,"_ZN6CSkill8getRangeEv")
TL_FUNCTION(csAngle,"_ZN6CSkill18getFindTargetAngleEv")
TL_FUNCTION(csPathable,"_ZN6CSkill19getRequiresPathableEv")
TL_FUNCTION(csInterrupt,"_ZN6CSkill19getCanBeInterruptedEv")
TL_FUNCTION(csAnim,"_ZN6CSkill17getAnimationIndexEv")
TL_FUNCTION(csAnimDW,"_ZN6CSkill19getAnimationIndexDWEv")
TL_FUNCTION(csLoop,"_ZN6CSkill25getAnimationIndexLoopIntoEv")
TL_FUNCTION(csLoopDW,"_ZN6CSkill27getAnimationIndexDWLoopIntoEv")
TL_FUNCTION(csSpeed,"_ZN6CSkill21getAnimationSpeedMultEv")
TL_FUNCTION(csAlignment,"_ZN10CCharacter18getTargetAlignmentEv")
TL_FUNCTION(csFriend,"_ZN10CCharacter8isFriendEPS_")
TL_FUNCTION(csEnemy,"_ZN10CCharacter7isEnemyEPS_")
TL_FUNCTION(csTarget,"_ZN10CCharacter9setTargetEPS_")
TL_FUNCTION(csItem,"_ZN10CCharacter13setTargetItemEP5CItem")
TL_FUNCTION(csFindCharacter,"_ZN6CLevel23findCharacterWithinViewERKN4Ogre7Matrix4E10EAlignmentfffbP10CCharacterP6CSkill")
TL_FUNCTION(csFindItem,"_ZN6CLevel18findItemWithinViewERKN4Ogre7Matrix4Eff")
TL_FUNCTION(csWorld,"_ZN11CGameClient17findWorldLocationERN4Ogre7Vector3Eb")
TL_FUNCTION(csRay,"_ZN6CLevel12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_RjS4_b")
TL_FUNCTION(csPosition,"_ZN13CSkillManager19getPositionForSkillEP6CSkillP9CBaseUnit")
TL_FUNCTION(csCanPath,"_ZN10CCharacter9canPathToEN4Ogre7Vector3E")
TL_FUNCTION(csReached,"_ZN16CAstarPathfinder11reachedGoalEv")
TL_FUNCTION(csAdvance,"_ZN16CAstarPathfinder15advanceNextNodeEv")
TL_FUNCTION(csNodeX,"_ZN16CAstarPathfinder8getNodeXEv")
TL_FUNCTION(csNodeY,"_ZN16CAstarPathfinder8getNodeYEv")
TL_FUNCTION(csExecutable,"_ZN13CSkillManager21getSkillCanBeExecutedEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ES3_b")
TL_FUNCTION(csFacing,"_ZN10CCharacter12facingTargetEv")
TL_FUNCTION(csPerform,"_ZN10CCharacter12performSkillEv")
TL_FUNCTION(csJournal,"_ZN10CCharacter25incrementJournalStatisticE17EJournalStatistici")
TL_FUNCTION(csModifyMana,"_ZN10CCharacter10modifyManaEf")
TL_FUNCTION(csAssign,"_ZN6CSkill21assignSkillAnimationsEP9CBaseUnit")
TL_FUNCTION(csEffect,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(csDual,"_ZN10CCharacter14isDualWieldingEv")
TL_FUNCTION(csIndex,"_ZNK13CGenericModel17getAnimationIndexERKSs")
TL_FUNCTION(csLength,"_ZNK13CGenericModel25getAnimationLengthSecondsEi")
TL_FUNCTION(csClear,"_ZN13CGenericModel21clearQueuedAnimationsEv")
TL_FUNCTION(csQueueName,"_ZN13CGenericModel19queueBlendAnimationERKSsbff")
TL_FUNCTION(csQueueIndex,"_ZN13CGenericModel19queueBlendAnimationEjbff")
TL_FUNCTION(csBlend,"_ZN10CCharacter14blendAnimationEibfff")
TL_FUNCTION(csActive,"_ZN10CCharacter14setActiveSkillEP6CSkillb")
TL_FUNCTION(csBank,"_ZN10CSoundBank11bankPlayingEi")
TL_FUNCTION(csPlay,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(csSound,"_ZN10CSoundBank17queueGlobalSampleEiff")
TL_FUNCTION(csISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(csPlayer,"_ZN9CBaseUnit8isPlayerEv")
TL_FUNCTION(csUI,"_ZN16CResourceManager9getGameUIEv")
TL_FUNCTION(csTip,"_ZN7CGameUI8queueTipE11EContextTip")
namespace {
struct Case{unsigned seed,control;};unsigned seed,mode,variant,phase,pathCalls,nodeCalls;bool armed,oursSide;autotest::Capture*out;nativegame::Services*services;menugui::Fixture*menu;finishlevel::Fixture*world;CCharacter*self,*target;CEquipment*item;CSkill*skills[3];Ogre::Vector3 skillPosition;
void fault(int signal,siginfo_t*info,void*context){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/character/character-cast-signal.log",O_WRONLY|O_CREAT|O_APPEND,0600);if(fd>=0){char line[200];ucontext_t*uc=static_cast<ucontext_t*>(context);int n=std::snprintf(line,sizeof(line),"signal%d side%u seed%u phase%u rip%llx address%p\n",signal,unsigned(oursSide),seed,phase,(unsigned long long)uc->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,line,n);void*stack[40];int count=backtrace(stack,40);backtrace_symbols_fd(stack,count,fd);close(fd);}raise(signal);}
void num(unsigned x){if(armed)out->add(&x,4);}void fp(float x){if(armed)out->add(&x,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void narrow(const std::string&s){num(s.size());if(armed)out->add(s.data(),s.size());}unsigned id(const void*p){if(!p)return 0;if(p==self)return 1;if(p==target)return 2;if(p==item)return 3;for(unsigned i=0;i<3;++i)if(p==skills[i])return 10+i;return 99;}
class Actor:public CCharacter{public:Actor():CCharacter(NULL){}virtual void setAIState(EAIState state){num(101);num(state);m_eAIState=state;}};
int known(CSkillManager*p,ESKILL_ACTIVATION_TYPE activation){num(103);num(p==self->m_pSkillManager);num(activation);return mode==3?0:1;}
CSkill*find(CSkillManager*p,long long guid){num(107);num(p==self->m_pSkillManager);if(armed)out->add(&guid,8);return mode==4?NULL:skills[0];}
int mana(CCharacter*p){num(109);num(id(p));if(mode==6&&(variant&1))self->m_skillLooping=true;return mode==6?5:100;}
unsigned cost(CSkill*p){num(113);num(id(p));return variant%5==4?0xffffffffu:10;}
unsigned costOT(CSkill*p){num(127);num(id(p));return mode==7?110:variant%5==3?0xffffffffu:3;}
int type(CSkill*p){num(131);num(id(p));if(mode>=12&&mode<=16){int types[]={1,11,5,6};return types[variant%4];}return mode==8||mode==9?2:3;}
float range(CSkill*p){num(137);num(id(p));float v[]={0,.2f,1,4,12};return v[variant%5];}
float angle(CSkill*p){num(139);num(id(p));return mode==10||mode==11?45.0f:0.0f;}
bool pathable(CSkill*p){num(149);num(id(p));return mode==15||mode==16;}
bool interrupt(CSkill*p){num(151);num(id(p));return variant&1;}
int anim(CSkill*p){num(157);num(id(p));return variant%4==0||variant%4==2?-1:4;}
unsigned animDW(CSkill*p){num(163);num(id(p));return variant%4==1||variant%4==2?unsigned(-1):7;}
unsigned loop(CSkill*p){num(167);num(id(p));return variant%4<2?unsigned(-1):8;}
unsigned loopDW(CSkill*p){num(173);num(id(p));return variant%4<2?9:unsigned(-1);}
float speed(CSkill*p){num(179);num(id(p));float v[]={.1f,1,2,5};return v[(variant/3)%4];}
EAlignment alignment(CCharacter*p){num(181);num(id(p));return static_cast<EAlignment>(variant%2?6:1);}
bool isfriend(CCharacter*p,CCharacter*q){num(191);num(id(p));num(id(q));return variant%2;}
bool enemy(CCharacter*p,CCharacter*q){num(193);num(id(p));num(id(q));return variant%2;}
void setTarget(CCharacter*p,CCharacter*q){num(197);num(id(p));num(id(q));p->m_targetCharacter.setObject(q);}
void setItem(CCharacter*p,CItem*q){num(199);num(id(p));num(id(q));p->m_targetItem.setObject(q);}
void matrix(const Ogre::Matrix4&m){for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j)fp(m[i][j]);}
CCharacter*findCharacter(CLevel*p,const Ogre::Matrix4&m,EAlignment a,float min,float angle,float distance,bool flag,CCharacter*owner,CSkill*s){num(211);num(p==&world->level);matrix(m);num(a);fp(min);fp(angle);fp(distance);num(flag);num(id(owner));num(id(s));return mode==10?target:NULL;}
CItem*findItem(CLevel*p,const Ogre::Matrix4&m,float angle,float distance){num(223);num(p==&world->level);matrix(m);fp(angle);fp(distance);return variant%2?item:NULL;}
bool worldPosition(CGameClient*p,Ogre::Vector3&v,bool flag){num(227);num(p==menu->nativeClient.client);vec(v);num(flag);v=skillPosition;return variant%2;}
bool ray(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,Ogre::Vector3&hit,Ogre::Vector3&normal,unsigned&material,Ogre::Vector3&point,bool flag){num(229);num(p==&world->level);vec(a);vec(b);num(flag);hit=Ogre::Vector3(2,3,-4);normal=Ogre::Vector3::UNIT_Y;point=Ogre::Vector3::ZERO;material=variant%3==0?100:2;return variant%4!=0;}
Ogre::Vector3*position(CSkillManager*p,CSkill*s,CBaseUnit*t){num(233);num(p==self->m_pSkillManager);num(id(s));num(id(t));return variant%2?&skillPosition:NULL;}
bool canPath(CCharacter*p,Ogre::Vector3 v){num(239);num(id(p));vec(v);++pathCalls;return mode==16&&pathCalls>variant%3;}
bool reached(CAstarPathfinder*p){num(241);num(p==self->m_pathfinder);return nodeCalls>=variant%3;}
void advance(CAstarPathfinder*p){num(251);num(p==self->m_pathfinder);++nodeCalls;}
float nodeX(CAstarPathfinder*p){num(257);num(p==self->m_pathfinder);return 2.25f;}
float nodeY(CAstarPathfinder*p){num(263);num(p==self->m_pathfinder);return -5.5f;}
bool executable(CSkillManager*p,CSkill*s,CBaseUnit*caster,ESKILL_ACTIVATION_TYPE a,const Ogre::Vector3&v,CBaseUnit*t,bool flag){num(269);num(p==self->m_pSkillManager);num(id(s));num(id(caster));num(a);vec(v);num(id(t));num(flag);if(mode==29){skills[0]->m_interruptible=true;self->m_skillLooping=true;}return mode!=17;}
bool facing(CCharacter*p){num(271);num(id(p));return mode!=18;}
CSkill*perform(CCharacter*p){num(277);num(id(p));return mode==19?NULL:skills[1];}
void journal(CCharacter*p,EJournalStatistic statistic,int amount){num(281);num(id(p));num(statistic);num(amount);}
void modifyMana(CCharacter*p,float amount){num(283);num(id(p));fp(amount);p->m_fManaFloat+=amount;}
void assign(CSkill*p,CBaseUnit*unit){num(293);num(id(p));num(id(unit));}
float effect(CCharacter*p,EEFFECT_TYPE type,EDAMAGE_TYPES damage){num(307);num(id(p));num(type);num(damage);float values[]={-200,-20,0,30,250};return type==static_cast<EEFFECT_TYPE>(29)?values[variant%5]:values[(variant/2)%5];}
bool dual(CCharacter*p){num(311);num(id(p));return variant&1;}
unsigned index(CGenericModel*p,const std::string&name){num(313);num(p==self->m_pUnitModel);narrow(name);return variant&2?unsigned(-1):3;}
float length(CGenericModel*p,int animation){num(317);num(p==self->m_pUnitModel);num(animation);return 1.25f+float(variant%4);}
void clear(CGenericModel*p){num(331);num(p==self->m_pUnitModel);}
void queueName(CGenericModel*p,const std::string&name,bool loop,float blend,float speed){num(337);num(p==self->m_pUnitModel);narrow(name);num(loop);fp(blend);fp(speed);}
void queueIndex(CGenericModel*p,unsigned index,bool loop,float blend,float speed){num(347);num(p==self->m_pUnitModel);num(index);num(loop);fp(blend);fp(speed);}
void blend(CCharacter*p,int index,bool loop,float blend,float speed,float length){num(349);num(id(p));num(index);num(loop);fp(blend);fp(speed);fp(length);}
void active(CCharacter*p,CSkill*s,bool flag){num(353);num(id(p));num(id(s));num(flag);p->m_activeSkill=s;}
bool bank(CSoundBank*p,int sample){num(359);num(p==self->m_levelSound);num(sample);return variant&2;}
int play(CSoundBank*p,int sample,Ogre::SceneNode*node,float a,float b,bool flag){num(367);num(p==self->m_levelSound);num(sample);num(node==NULL);fp(a);fp(b);num(flag);return 17;}
void sound(CSoundBank*p,int sample,float a,float b){num(373);num(p==self->m_levelSound);num(sample);fp(a);fp(b);}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){num(379);num(id(p));num(type);return mode==12;}
bool player(CBaseUnit*p){num(383);num(id(p));return mode==12||mode==18||(variant&4);}
CGameUI*ui(CResourceManager*p){num(389);num(p==&world->resources);return menu->ui;}
}
namespace {
void tip(CGameUI*p,EContextTip kind){num(397);num(p==menu->ui);num(kind);}
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;mode=seed%32;variant=seed/32;phase=1;oursSide=ours;armed=false;out=&capture;pathCalls=nodeCalls=0;struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_sigaction=&fault;action.sa_flags=SA_SIGINFO|SA_RESETHAND;sigemptyset(&action.sa_mask);sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);
 self=new Actor;target=new CCharacter(NULL);item=new CEquipment(NULL);for(unsigned i=0;i<3;++i){skills[i]=new CSkill(NULL,NULL);skills[i]->m_Guid=123+i;skills[i]->m_animationSpeed=-3.0f;skills[i]->m_targetPosition=Ogre::Vector3(-9,-8,-7);skills[i]->m_animationID=5;skills[i]->m_interruptible=false;skills[i]->m_iCharges=(variant&8)?0:3;skills[i]->m_iTargetAlignment=mode==8?2:1;skills[i]->m_SkillData6C=mode==5;}
 self->m_pResourceManager=&world->resources;self->m_pSkillManager=mode==2?NULL:new CSkillManager(NULL,self);if(self->m_pSkillManager)self->m_pSkillManager->m_OtherSkills.add(skills[2]);self->m_activeSkill=mode==1||variant%3==0?skills[0]:NULL;self->m_previousSkill=variant&16?skills[2]:NULL;self->m_skillLooping=mode==1;self->m_skillTime=mode==1?1:0;if(mode==1)skills[0]->m_animationID=-1;if(mode==6&&(variant&1))skills[0]->m_animationID=-1;
 self->m_attack=mode==0||mode==5?new CAttackDescription("cast",false,1,2,3,4,5,6):NULL;self->m_attackTime=mode==0?.3f:.1f;self->m_pUnitModel=new CGenericModel(NULL,services->scene,static_cast<OGRE_UTILITIES::EPRIMITIVES>(0));self->m_levelSound=(variant&1)?new CSoundBank(*services->master->m_pSoundManager,false):NULL;self->m_vPosition=Ogre::Vector3(1,-2,3);self->m_pathDestination=Ogre::Vector3(-11,-12,-13);self->m_vScale=Ogre::Vector3(2,3,1.25f);self->m_fBaseUnitValue194=.75f;target->m_fBaseUnitValue194=1.5f;target->m_vPosition=Ogre::Vector3(4,7,9);self->m_targetDirection=Ogre::Vector3::UNIT_Z;self->m_attackRadius=.8f;self->m_attackRangeScale=1.5f;self->m_targetPosition=Ogre::Vector3(variant%5,-7,variant%7+2);skillPosition=Ogre::Vector3(variant%7+2,8,-float(variant%9));
 if(mode==8||mode==9||mode==13||mode==18)self->m_targetCharacter.setObject(target);if(mode==11&&variant&8)self->m_targetItem.setObject(item);self->m_pathfinder=new CAstarPathfinder(0,0,0,0,NULL,NULL,1);self->m_isPathing=variant&1;self->m_pathGraceTime=-2;self->m_skillInterrupted=true;self->m_skillEventTriggered=true;self->m_skillCanInterrupt=false;self->m_Padding4D0[1]=0;self->m_fidgetTime=variant%2?2:8;self->m_fManaFloat=99;::m_gAllowSkillTesting=variant&2;world->level.m_pGameClient=menu->nativeClient.client;
 detour::Set patches;
#define P(name,fn) TL_REDIRECT(patches,cs##name,&fn)
 P(Known,known); P(Find,find); P(Mana,mana); P(Cost,cost); P(CostOT,costOT); P(Type,type); P(Range,range); P(Angle,angle); P(Pathable,pathable); P(Interrupt,interrupt); P(Anim,anim); P(AnimDW,animDW); P(Loop,loop); P(LoopDW,loopDW); P(Speed,speed); P(Alignment,alignment); P(Friend,isfriend); P(Enemy,enemy); P(Target,setTarget); P(Item,setItem); P(FindCharacter,findCharacter); P(FindItem,findItem); P(World,worldPosition); P(Ray,ray); P(Position,position); P(CanPath,canPath); P(Reached,reached); P(Advance,advance); P(NodeX,nodeX); P(NodeY,nodeY); P(Executable,executable); P(Facing,facing); P(Perform,perform); P(Journal,journal); P(ModifyMana,modifyMana); P(Assign,assign); P(Effect,effect); P(Dual,dual); P(Index,index); P(Length,length); P(Clear,clear); P(QueueName,queueName); P(QueueIndex,queueIndex); P(Blend,blend); P(Active,active); P(Bank,bank); P(Play,play); P(Sound,sound); P(ISA,isa); P(Player,player); P(UI,ui); P(Tip,tip);
#undef P
 if(patches.failed())_exit(43);phase=100;armed=true;typedef bool(*F)(CCharacter*,long long);F fn=ours?csNew:csOld;if(!autotest::beginInvocation(capture,fn))return;bool result=fn(self,variant%4?-1:123);capture.callCompleted=1;phase=101;if(ours&&c.control)result=!result;num(result);num(id(self->m_activeSkill));num(id(self->m_previousSkill));num(id(self->m_targetCharacter.getObject()));num(id(self->m_targetItem.getObject()));vec(self->m_targetPosition);vec(self->m_pathDestination);fp(self->m_skillTime);fp(self->m_pathGraceTime);fp(self->m_fidgetTime);fp(self->m_fManaFloat);num(self->m_skillCanInterrupt);num(self->m_isPathing);num(self->m_Padding4D0[1]);num(self->m_skillEventTriggered);num(self->m_skillInterrupted);num(self->m_skillLooping);num(self->m_eAIState);for(unsigned i=0;i<3;++i){fp(skills[i]->m_animationSpeed);vec(skills[i]->m_targetPosition);}armed=false;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(character_cast_runtime){std::setlocale(LC_CTYPE,"C.UTF-8");initEmptyGlobals();tlheadless::Environment environment;environment.loadGameSkin();nativegame::Services native;if(!native.ready())return 1;services=&native;menugui::Audio audio(native.master);CStringTranslate translate(L"");menugui::Fixture gui(*native.settings,native.scene);menu=&gui;finishlevel::Fixture level;world=&level;world->resources.m_pLevel=&world->level;world->resources.m_pSceneManager=native.scene;int failures=0;autotest::Coverage coverage("character_cast_runtime",(uintptr_t)&csOld);for(unsigned i=0;i<1024;++i){Case c={i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    cast seed%u status%d/%d bytes%lu/%lu\n",i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}for(unsigned j=0;j+3<a.capture.length&&j<400;j+=4){unsigned x,y;std::memcpy(&x,a.capture.data+j,4);std::memcpy(&y,b.capture.data+j,4);host->log("    word%u %u/%u\n",j/4,x,y);}coverage.report(host);return failures;}}coverage.report(host);Case c={31,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    cast negative detected%u\n",unsigned(caught));return failures;}
