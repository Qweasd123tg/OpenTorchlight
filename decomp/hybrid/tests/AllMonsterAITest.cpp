#include <string>
#include <vector>
#include <map>
#include <new>
#include <stdint.h>
#include <cstdlib>
#define private public
#define protected public
#include "Monster.h"
#include "Player.h"
#include "GameClient.h"
#include "Level.h"
#include "LevelTemplateData.h"
#include "Skill.h"
#include "SkillProperty.h"
#include "SkillManager.h"
#include "AIManager.h"
#include "MasterResourceManager.h"
#include "Settings.h"
#include "Equipment.h"
#include "GenericModel.h"
#include "SoundBank.h"
#include "PathController.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void, oldMonsterUpdate, (CMonster*,float,bool), "_ZN8CMonster8updateAIEfb")
extern "C" void newMonsterUpdate(CMonster*,float,bool) __asm__("_ZN8CMonster8updateAIEfb");
TL_FUNCTION(monsterUpdateBoundary,"_ZN8CMonster8updateAIEfb")
TL_ORIGINAL(void, oldMonsterReact, (CMonster*,CCharacter*,bool), "_ZN8CMonster13reactToDamageEP10CCharacterb")
extern "C" void newMonsterReact(CMonster*,CCharacter*,bool) __asm__("_ZN8CMonster13reactToDamageEP10CCharacterb");
TL_FUNCTION(monsterReactBoundary,"_ZN8CMonster13reactToDamageEP10CCharacterb")
TL_ORIGINAL(void, oldMonsterHunt, (CMonster*,float,CLevel&), "_ZN8CMonster6huntAIEfR6CLevel")
extern "C" void newMonsterHunt(CMonster*,float,CLevel&) __asm__("_ZN8CMonster6huntAIEfR6CLevel");
TL_FUNCTION(monsterHuntBoundary,"_ZN8CMonster6huntAIEfR6CLevel")
TL_ORIGINAL(void, oldMonsterAttack, (CMonster*,float,CLevel&), "_ZN8CMonster8attackAIEfR6CLevel")
extern "C" void newMonsterAttack(CMonster*,float,CLevel&) __asm__("_ZN8CMonster8attackAIEfR6CLevel");
TL_FUNCTION(monsterAttackBoundary,"_ZN8CMonster8attackAIEfR6CLevel")
TL_ORIGINAL(void, oldMonsterIdle, (CMonster*,float,CLevel&,bool), "_ZN8CMonster6idleAIEfR6CLevelb")
extern "C" void newMonsterIdle(CMonster*,float,CLevel&,bool) __asm__("_ZN8CMonster6idleAIEfR6CLevelb");
TL_FUNCTION(monsterIdleBoundary,"_ZN8CMonster6idleAIEfR6CLevelb")
TL_FUNCTION(monster_performingSkill,"_ZN10CCharacter15performingSkillEv")
TL_FUNCTION(monster_performingAttack,"_ZN10CCharacter16performingAttackEv")
TL_FUNCTION(monster_petNearDeath,"_ZN10CCharacter14isPetNearDeathEv")
TL_FUNCTION(monster_isFriend,"_ZN10CCharacter8isFriendEPS_")
TL_FUNCTION(monster_isEnemy,"_ZN10CCharacter7isEnemyEPS_")
TL_FUNCTION(monster_unitISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(monster_masterSingleton,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(monster_getInt,"_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(monster_isDormant,"_ZN6CLevel9isDormantEv")
TL_FUNCTION(monster_stopSkills,"_ZN13CSkillManager13stopAllSkillsEbbb")
TL_FUNCTION(monster_attemptStopSkill,"_ZN10CCharacter24attemptStopOfActiveSkillEv")
TL_FUNCTION(monster_getHP,"_ZN10CCharacter2HPEv")
TL_FUNCTION(monster_getMaxHP,"_ZN10CCharacter5maxHPEv")
TL_FUNCTION(monster_getBravery,"_ZN10CCharacter10getBraveryEv")
TL_FUNCTION(monster_interrupt,"_ZN10CCharacter9interruptEb")
TL_FUNCTION(monster_removeTheme,"_ZN9CBaseUnit15removeUnitThemeERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(monster_hasTheme,"_ZN9CBaseUnit12hasUnitThemeERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(monster_position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(monster_rng,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(monster_integerRng,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(monster_setDestination,"_ZN10CCharacter14setDestinationER6CLevelff")
TL_FUNCTION(monster_stopPathing,"_ZN10CCharacter11stopPathingEv")
TL_FUNCTION(monster_playSound,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(monster_blendAnimation,"_ZN10CCharacter14blendAnimationERKSsbfff")
TL_FUNCTION(monster_queueAnimation,"_ZN10CCharacter19queueBlendAnimationERKSsbff")
TL_FUNCTION(monster_hasFlag,"_ZN10CAIManager9hasAIFlagE13EAIFLAG_TYPES")
TL_FUNCTION(monster_calculateTarget,"_ZN10CCharacter22calculateTargetInSightE10EAlignmentb")
TL_FUNCTION(monster_attemptJump,"_ZN10CCharacter15attemptJumpDownEv")
TL_FUNCTION(monster_effectValue,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(monster_lineOfSight,"_ZN10CCharacter16validLineOfSightER6CLevelb")
TL_FUNCTION(monster_attackRange,"_ZN10CCharacter13inAttackRangeE18EATTACK_RANGE_TYPE")
TL_FUNCTION(monster_walkingSpeed,"_ZN10CCharacter12walkingSpeedEv")
TL_FUNCTION(monster_runningSpeed,"_ZN10CCharacter12runningSpeedEv")
TL_FUNCTION(monster_followCharacter,"_ZN10CCharacter15followCharacterEPS_R6CLevel")
TL_FUNCTION(monster_canCast,"_ZN10CCharacter19canCastCurrentSkillEP9CBaseUnitbb")
TL_FUNCTION(monster_selectOffensive,"_ZN8CMonster20selectOffensiveSkillEb")
TL_FUNCTION(monster_setActiveSkill,"_ZN10CCharacter14setActiveSkillEP6CSkillb")
TL_FUNCTION(monster_selectAttack,"_ZN10CCharacter12selectAttackE18EATTACK_RANGE_TYPE")
TL_FUNCTION(monster_skillRange,"_ZN10CCharacter12inSkillRangeExb")
TL_FUNCTION(monster_castSkill,"_ZN10CCharacter9castSkillEx")
TL_FUNCTION(monster_turnToward,"_ZN10CCharacter18turnTowardPositionERKN4Ogre7Vector3Ef")
TL_FUNCTION(monster_facingTarget,"_ZN10CCharacter12facingTargetEv")
TL_FUNCTION(monster_attack,"_ZN10CCharacter6attackEv")
TL_FUNCTION(monster_idleNormal,"_ZN8CMonster12idleAINormalEfR6CLevelb")
TL_FUNCTION(monster_idleRangedDefender,"_ZN8CMonster20idleAIRangedDefenderEfR6CLevelb")
TL_FUNCTION(monster_idleRangedCaster,"_ZN8CMonster18idleAIRangedCasterEfR6CLevelb")
TL_FUNCTION(monster_idleCircler,"_ZN8CMonster13idleAICirclerEfR6CLevelb")
TL_FUNCTION(monster_modelExists,"_ZNK13CGenericModel24animationExistsSubstringERKSs")
TL_FUNCTION(monster_modelRandom,"_ZN13CGenericModel19findRandomAnimationERKSs")
TL_FUNCTION(monster_modelBlend,"_ZN13CGenericModel14blendAnimationEjbfff")
TL_FUNCTION(monster_pathFollowing,"_ZN10CCharacter19updatePathFollowingEb")
TL_FUNCTION(monster_attaches,"_ZN10CCharacter16attachesToMasterEv")
TL_FUNCTION(monster_teleport,"_ZN10CCharacter16teleportToMasterEf")
TL_FUNCTION(monster_fidget,"_ZN8CMonster8fidgetAIEfR6CLevel")
TL_FUNCTION(monster_flee,"_ZN8CMonster6fleeAIEfR6CLevel")
TL_FUNCTION(monster_getRange,"_ZN8CMonster10getRangeAIEfR6CLevel")
TL_FUNCTION(monster_jump,"_ZN8CMonster10jumpDownAIEfR6CLevel")
TL_FUNCTION(monster_animationPlay,"_ZN10CCharacter15animationPlayAIEf")
namespace {
struct Case {unsigned mode,index;};
struct State {autotest::Capture* out;Case c;CMonster* monster;CCharacter *target,*alternative,*master;CItem* item;CEquipment* weapon;CSkill* skill;CAttackDescription* attack;CResourceManager* resources;CLevel* level;CMasterResourceManager* manager;unsigned rngCalls;};
State* active;
unsigned hash(unsigned label){unsigned v=active->c.index*2654435761u+label*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}
bool bit(unsigned label){return (hash(label)&7)==0;}
void num(unsigned n){active->out->add(&n,4);}void fp(float n){active->out->add(&n,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void text(const std::string&v){num(v.size());active->out->add(v.data(),v.size());}void wide(const std::wstring&v){num(v.size());active->out->add(v.data(),v.size()*4);}
unsigned id(const void*p){if(!p)return 0;if(p==active->monster)return 1;if(p==active->target)return 2;if(p==active->alternative)return 3;if(p==active->master)return 4;if(p==active->item)return 5;if(p==active->weapon)return 6;if(p==active->skill)return 7;if(p==active->attack)return 8;return 99;}
void event(unsigned n){num(n);}
bool enabled(CSceneNodeObject*p){event(1);num(id(p));return p->m_bEnabled;}
const Ogre::Vector3& forward(CCharacter*p){event(2);num(id(p));return p->m_vForward;}
void state(CCharacter*p,EAIState value){event(3);num(value);p->m_eAIState=value;}
bool weaponAvailable(CCharacter*){event(4);return !bit(4);}
template<unsigned N>void ai(CCharacter*,float elapsed,CLevel&level){event(N);fp(elapsed);num(&level==active->level);}
template<unsigned N>void scalarAI(CCharacter*,float elapsed){event(N);fp(elapsed);}
void approachSkill(CCharacter*,float elapsed,CLevel&level,long long guid){event(49);fp(elapsed);num(&level==active->level);num(guid);}
bool performingSkill(CCharacter*){event(50);return bit(50);}bool performingAttack(CCharacter*){event(51);return bit(51);}
bool petNearDeath(CCharacter*p){event(52);num(id(p));return bit(p==active->monster?52:53);}
bool friendly(CCharacter*,CCharacter*p){event(54);num(id(p));return bit(54);}bool enemy(CCharacter*,CCharacter*p){event(55);num(id(p));return !bit(54);}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){event(56);num(id(p));num(type);return bit(type+id(p)*13);}
CMasterResourceManager* singleton(){event(57);return active->manager;}
int getInt(CDynamicPropertyFile*,unsigned index){event(58);num(index);if(index==42)return bit(58)?1:0;return bit(59)?1:0;}
bool dormant(CLevel*){event(60);return bit(60);}
void stopSkills(CSkillManager*,bool a,bool b,bool c){event(61);num(a);num(b);num(c);}
void attemptStop(CCharacter*){event(62);}
int hp(CCharacter*){event(63);return int(hash(63)%9)*17-13;}int maxhp(CCharacter*){event(64);return int(hash(64)%4)*50;}
float bravery(CCharacter*){event(65);return (hash(65)%6)*0.25f;}
void interrupt(CCharacter*,bool value){event(66);num(value);}
void removeTheme(CBaseUnit*,const std::wstring&name){event(67);wide(name);}bool hasTheme(CBaseUnit*,const std::wstring&name){event(68);wide(name);return bit(68);}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){event(69);num(id(p));num(absolute);return p->m_vPosition;}
float rng(float lo,float hi){event(70);fp(lo);fp(hi);unsigned v=hash(70+active->rngCalls++);return v%3==0?lo:v%3==1?hi:(lo+hi)*0.5f;}
int integerRng(int lo,int hi){event(71);num(lo);num(hi);unsigned v=hash(71+active->rngCalls++);static const int values[]={0,9,10,24,25,49,50,99,100};return values[v%9];}
void destination(CCharacter*p,CLevel&level,float x,float z){event(72);num(&level==active->level);fp(x);fp(z);p->m_targetPosition=Ogre::Vector3(x,0,z);p->m_isPathing=!bit(72);}
void stopPath(CCharacter*p){event(73);p->m_isPathing=false;}
int sound(CSoundBank*,int index,Ogre::SceneNode*,float volume,float radius,bool flag){event(74);num(index);fp(volume);fp(radius);num(flag);return 0;}
void blend(CCharacter*,const std::string&name,bool loop,float a,float b,float c){event(75);text(name);num(loop);fp(a);fp(b);fp(c);}
void queue(CCharacter*,const std::string&name,bool loop,float a,float b){event(76);text(name);num(loop);fp(a);fp(b);}
bool aiFlag(CAIManager*,EAIFLAG_TYPES type){event(77);num(type);return type==1&&!bit(77);}
CCharacter* targetInSight(CCharacter*,EAlignment alignment,bool flag){event(78);num(alignment);num(flag);return bit(78)?NULL:active->alternative;}
bool jump(CCharacter*p){event(79);if(bit(79))p->m_targetCharacter.setObject(NULL);return bit(79);}
float effect(CCharacter*,EEFFECT_TYPE type,EDAMAGE_TYPES damage){event(80);num(type);num(damage);return (int(hash(80)%3)-1)*50.0f;}
bool sight(CCharacter*,CLevel&l,bool flag){event(81);num(&l==active->level);num(flag);return !bit(81);}
bool range(CCharacter*,EATTACK_RANGE_TYPE type){event(82);num(type);return !bit(82);}
float walk(CCharacter*p){event(83);num(id(p));return bit(83)?0.0f:2.5f;}float runSpeed(CCharacter*){event(84);return bit(84)?0.0f:5.0f;}
void follow(CCharacter*p,CCharacter*target,CLevel&l){event(85);num(id(target));num(&l==active->level);p->m_isPathing=!bit(85);}
bool canCast(CCharacter*,CBaseUnit*p,bool a,bool b){event(86);num(id(p));num(a);num(b);return !bit(86);}
void offensive(CMonster*p,bool flag){event(87);num(flag);p->m_activeSkill=bit(87)?NULL:active->skill;}
void activeSkill(CCharacter*p,CSkill*skill,bool flag){event(88);num(id(skill));num(flag);p->m_activeSkill=skill;}
void selectAttack(CCharacter*p,EATTACK_RANGE_TYPE type){event(89);num(type);p->m_attack=bit(89)?NULL:active->attack;}
int skillRange(CCharacter*,long long guid,bool flag){event(90);num(guid);num(flag);return hash(90)%3;}
bool cast(CCharacter*,long long guid){event(91);num(guid);return true;}
void turn(CCharacter*,const Ogre::Vector3&p,float elapsed){event(92);vec(p);fp(elapsed);}
bool facing(CCharacter*){event(93);return !bit(93);}
bool attack(CCharacter*){event(94);return !bit(94);}
template<unsigned N>bool idle(CMonster*,float elapsed,CLevel&l,bool flag){event(N);fp(elapsed);num(&l==active->level);num(flag);return bit(N);}
bool modelExists(const CGenericModel*,const std::string&name){event(101);text(name);return !bit(101);}
unsigned modelRandom(CGenericModel*,const std::string&name){event(102);text(name);return 12;}
void modelBlend(CGenericModel*,unsigned index,bool loop,float a,float b,float c){event(103);num(index);num(loop);fp(a);fp(b);fp(c);}
void path(CCharacter*p,bool flag){event(104);num(flag);if(bit(104))p->m_pathToFollow.setObject(NULL);}
bool attaches(CCharacter*){event(105);return bit(105);}void teleport(CCharacter*,float distance){event(106);fp(distance);}
void idleBoundary(CMonster*,float elapsed,CLevel&l,bool flag){event(107);fp(elapsed);num(&l==active->level);num(flag);}
void core(CRunicCore*p){new(p) CRunicCore();}
void initCharacter(CCharacter*p,unsigned n){
    core(p);new(&p->m_targetCharacter) TSafePointer<CCharacter>;new(&p->m_targetItem) TSafePointer<CItem>;new(&p->m_pathToFollow) TSafePointer<CPathController>;
    p->m_eAIState=static_cast<EAIState>(n%17==0?5:n%17==1?6:n%17==2?41:n%17==3?42:2);p->m_bInActiveRange=n&1;p->m_damageShapeEnabled=n&2;
    p->m_vPosition=Ogre::Vector3(float(int(n%7)-3)*5.25f,float(n%3)*2.5f,float(int(n%11)-5)*3.125f);p->m_vForward=Ogre::Vector3(0.25f,0.5f,-0.75f);
    p->m_bEnabled=!bit(140+n%3);p->m_pResourceManager=active->resources;p->m_runningSpeed=5;p->m_walkingSpeed=2.5f;
}
void snapshot(CMonster*p){num(p->m_eAIState);fp(p->m_attackDelay);fp(p->m_aiThinkTime);num(p->m_returningToTown);num(p->m_isPathing);num(id(p->m_targetCharacter.getObject()));num(p->m_targetCharacter.m_nIndex);num(id(p->m_targetItem.getObject()));num(p->m_targetItem.m_nIndex);num(id(p->m_activeSkill));num(id(p->m_attack));vec(p->m_targetPosition);fp(p->m_idleSoundTime);fp(p->m_fidgetTime);num(p->m_pathToFollow.getObject()!=NULL);num(std::rand());}
void cleanup(CCharacter*p){p->m_targetCharacter.~TSafePointer();p->m_targetItem.~TSafePointer();p->m_pathToFollow.~TSafePointer();p->CRunicCore::~CRunicCore();}
void side(Case&c,bool ours,autotest::Capture&out){
    autotest::g_arenaUsed=0;State s;active=&s;s.out=&out;s.c=c;s.rngCalls=0;std::srand(c.index+31);
    s.resources=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));s.level=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));s.resources->m_pLevel=s.level;
    CLevelTemplateData* ld=static_cast<CLevelTemplateData*>(autotest::allocate(sizeof(CLevelTemplateData)));ld->m_sightRangeModifier=float(int(hash(110)%4)-1)*5.0f;s.level->m_pLevelTemplateData=ld;
    s.manager=static_cast<CMasterResourceManager*>(autotest::allocate(sizeof(CMasterResourceManager)));s.manager->m_pSettings=static_cast<CSettings*>(autotest::allocate(sizeof(CSettings)));KSETTINGS_AI_FREEZE=42;KSETTINGS_PLAYER_UNTARGETABLE=43;
    CGameClient* client=static_cast<CGameClient*>(autotest::allocate(sizeof(CGameClient)));client->m_gameState=static_cast<EGameState>(bit(111)?1:0);client->m_cameraState=bit(144)?1:0;new(&s.resources->m_GameClients) TArrayList<CGameClient*>;s.resources->m_GameClients.add(client);
    s.monster=static_cast<CMonster*>(autotest::allocate(sizeof(CMonster)));s.target=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.alternative=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.master=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));
    initCharacter(s.monster,c.index);initCharacter(s.target,c.index/3);initCharacter(s.alternative,c.index/5);initCharacter(s.master,c.index/7);
    s.item=static_cast<CItem*>(autotest::allocate(sizeof(CItem)));core(s.item);s.weapon=static_cast<CEquipment*>(autotest::allocate(sizeof(CEquipment)));s.weapon->m_fUnknown408=float(hash(112)%4)*0.25f;
    s.skill=static_cast<CSkill*>(autotest::allocate(sizeof(CSkill)));s.skill->m_property=static_cast<CSkillProperty*>(autotest::allocate(sizeof(CSkillProperty)));s.skill->m_property->m_iSkillLevel=bit(113)?1:2;
    s.attack=reinterpret_cast<CAttackDescription*>(autotest::allocate(16));CMonster*p=s.monster;
    p->m_eAIState=static_cast<EAIState>(c.mode<2?c.index%48:c.mode==2?4:c.mode==3?3:2);p->m_aiType=hash(114)%7;p->m_aiThinkTier=c.index%4;p->m_aiThinkTime=float(hash(115)%9)*0.1f;
    p->m_attackDelay=c.mode==0?float(int(hash(116)%7)-3)*0.125f:bit(116)?0.25f:-0.125f;p->m_initialAttackDelay=0.375f;
    p->m_nearWalkRadius=float(hash(117)%3)*8.0f;p->m_followRange=float(hash(118)%3)*12.0f+1;p->m_allowJumpDown=!bit(119);p->m_isPathing=bit(120);p->m_pathGraceTime=float(hash(121)%5)*0.25f;p->m_fidgetTime=float(hash(122)%4)*10.0f;p->m_idleSoundTime=13;
    p->m_petMode=hash(123)%3;p->m_attack=bit(124)?NULL:s.attack;p->m_attackFlag1F5=bit(125);p->m_activeSkill=bit(126)?s.skill:NULL;p->m_attackItem=bit(127)?s.weapon:NULL;p->m_monsterFlag=bit(128);p->m_deathPathActive=bit(129);
    p->m_pSkillManager=bit(130)?NULL:static_cast<CSkillManager*>(autotest::allocate(sizeof(CSkillManager)));p->m_pAIManager=bit(131)?NULL:static_cast<CAIManager*>(autotest::allocate(sizeof(CAIManager)));p->m_pUnitModel=bit(132)?NULL:static_cast<CGenericModel*>(autotest::allocate(sizeof(CGenericModel)));p->m_levelSound=bit(133)?NULL:static_cast<CSoundBank*>(autotest::allocate(sizeof(CSoundBank)));
    if(!bit(134))p->m_targetCharacter.setObject(s.target);if(bit(135))p->m_targetItem.setObject(s.item);p->m_pMaster=bit(136)?NULL:s.master;if(bit(137))s.master->m_targetCharacter.setObject(s.alternative);if(bit(138))s.target->m_targetCharacter.setObject(p);
    CPathController* controller=static_cast<CPathController*>(autotest::allocate(sizeof(CPathController)));core(controller);if(bit(139))p->m_pathToFollow.setObject(controller);
    void** storage=static_cast<void**>(autotest::allocate(0x500+16));void**vt=storage+2;std::memcpy(storage,reinterpret_cast<void*>(0xfd2680),0x500+16);vt[0x48/8]=reinterpret_cast<void*>(&enabled);vt[0x130/8]=reinterpret_cast<void*>(&forward);vt[0x348/8]=reinterpret_cast<void*>(&state);vt[0x3f8/8]=reinterpret_cast<void*>(&weaponAvailable);
    typedef void(*AIFn)(CCharacter*,float,CLevel&);typedef void(*ScalarFn)(CCharacter*,float);
    vt[0x360/8]=reinterpret_cast<void*>(static_cast<AIFn>(&ai<20>));vt[0x368/8]=reinterpret_cast<void*>(static_cast<AIFn>(&ai<21>));vt[0x378/8]=reinterpret_cast<void*>(static_cast<AIFn>(&ai<22>));vt[0x388/8]=reinterpret_cast<void*>(static_cast<ScalarFn>(&scalarAI<23>));vt[0x390/8]=reinterpret_cast<void*>(static_cast<AIFn>(&ai<24>));vt[0x3b8/8]=reinterpret_cast<void*>(static_cast<AIFn>(&ai<25>));vt[0x3c0/8]=reinterpret_cast<void*>(&approachSkill);vt[0x3c8/8]=reinterpret_cast<void*>(static_cast<AIFn>(&ai<26>));vt[0x3d0/8]=reinterpret_cast<void*>(static_cast<AIFn>(&ai<27>));vt[0x3d8/8]=reinterpret_cast<void*>(static_cast<AIFn>(&ai<28>));vt[0x3e0/8]=reinterpret_cast<void*>(static_cast<AIFn>(&ai<29>));
    *reinterpret_cast<void***>(p)=vt;*reinterpret_cast<void***>(s.master)=vt;
    if(c.mode==0){typedef void(*F)(CMonster*,float,bool);F f=ours?newMonsterUpdate:oldMonsterUpdate;if(!autotest::beginInvocation(out,f))return;f(p,float(hash(141)%6)*0.125f,c.index&1);out.callCompleted=1;}
    if(c.mode==1){typedef void(*F)(CMonster*,CCharacter*,bool);F f=ours?newMonsterReact:oldMonsterReact;if(!autotest::beginInvocation(out,f))return;f(p,bit(142)?NULL:bit(143)?p:s.target,c.index&1);out.callCompleted=1;}
    if(c.mode==2){typedef void(*F)(CMonster*,float,CLevel&);F f=ours?newMonsterHunt:oldMonsterHunt;if(!autotest::beginInvocation(out,f))return;f(p,0.125f,*s.level);out.callCompleted=1;}
    if(c.mode==3){typedef void(*F)(CMonster*,float,CLevel&);F f=ours?newMonsterAttack:oldMonsterAttack;if(!autotest::beginInvocation(out,f))return;f(p,0.125f,*s.level);out.callCompleted=1;}
    if(c.mode==4){typedef void(*F)(CMonster*,float,CLevel&,bool);F f=ours?newMonsterIdle:oldMonsterIdle;if(!autotest::beginInvocation(out,f))return;f(p,0.125f,*s.level,c.index&1);out.callCompleted=1;}
    snapshot(p);cleanup(p);cleanup(s.target);cleanup(s.alternative);cleanup(s.master);s.item->CRunicCore::~CRunicCore();controller->CRunicCore::~CRunicCore();s.resources->m_GameClients.~TArrayList();
}
void before(void*c,autotest::Capture&o){side(*static_cast<Case*>(c),false,o);}void after(void*c,autotest::Capture&o){side(*static_cast<Case*>(c),true,o);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t address,unsigned count){
    detour::Set hooks;
    TL_REDIRECT(hooks,monster_performingSkill,&performingSkill);
    TL_REDIRECT(hooks,monster_performingAttack,&performingAttack);
    TL_REDIRECT(hooks,monster_petNearDeath,&petNearDeath);
    TL_REDIRECT(hooks,monster_isFriend,&friendly);
    TL_REDIRECT(hooks,monster_isEnemy,&enemy);
    TL_REDIRECT(hooks,monster_unitISA,&isa);
    TL_REDIRECT(hooks,monster_masterSingleton,&singleton);
    TL_REDIRECT(hooks,monster_getInt,&getInt);
    TL_REDIRECT(hooks,monster_isDormant,&dormant);
    TL_REDIRECT(hooks,monster_stopSkills,&stopSkills);
    TL_REDIRECT(hooks,monster_attemptStopSkill,&attemptStop);
    TL_REDIRECT(hooks,monster_getHP,&hp);
    TL_REDIRECT(hooks,monster_getMaxHP,&maxhp);
    TL_REDIRECT(hooks,monster_getBravery,&bravery);
    TL_REDIRECT(hooks,monster_interrupt,&interrupt);
    TL_REDIRECT(hooks,monster_removeTheme,&removeTheme);
    TL_REDIRECT(hooks,monster_hasTheme,&hasTheme);
    TL_REDIRECT(hooks,monster_position,&position);
    TL_REDIRECT(hooks,monster_rng,&rng);
    TL_REDIRECT(hooks,monster_integerRng,&integerRng);
    TL_REDIRECT(hooks,monster_setDestination,&destination);
    TL_REDIRECT(hooks,monster_stopPathing,&stopPath);
    TL_REDIRECT(hooks,monster_playSound,&sound);
    TL_REDIRECT(hooks,monster_blendAnimation,&blend);
    TL_REDIRECT(hooks,monster_queueAnimation,&queue);
    TL_REDIRECT(hooks,monster_hasFlag,&aiFlag);
    TL_REDIRECT(hooks,monster_calculateTarget,&targetInSight);
    TL_REDIRECT(hooks,monster_attemptJump,&jump);
    TL_REDIRECT(hooks,monster_effectValue,&effect);
    TL_REDIRECT(hooks,monster_lineOfSight,&sight);
    TL_REDIRECT(hooks,monster_attackRange,&range);
    TL_REDIRECT(hooks,monster_walkingSpeed,&walk);
    TL_REDIRECT(hooks,monster_runningSpeed,&runSpeed);
    TL_REDIRECT(hooks,monster_followCharacter,&follow);
    TL_REDIRECT(hooks,monster_canCast,&canCast);
    TL_REDIRECT(hooks,monster_selectOffensive,&offensive);
    TL_REDIRECT(hooks,monster_setActiveSkill,&activeSkill);
    TL_REDIRECT(hooks,monster_selectAttack,&selectAttack);
    TL_REDIRECT(hooks,monster_skillRange,&skillRange);
    TL_REDIRECT(hooks,monster_castSkill,&cast);
    TL_REDIRECT(hooks,monster_turnToward,&turn);
    TL_REDIRECT(hooks,monster_facingTarget,&facing);
    TL_REDIRECT(hooks,monster_attack,&attack);
    TL_REDIRECT(hooks,monster_idleNormal,&idle<95>);
    TL_REDIRECT(hooks,monster_idleRangedDefender,&idle<96>);
    TL_REDIRECT(hooks,monster_idleRangedCaster,&idle<97>);
    TL_REDIRECT(hooks,monster_idleCircler,&idle<98>);
    TL_REDIRECT(hooks,monster_modelExists,&modelExists);
    TL_REDIRECT(hooks,monster_modelRandom,&modelRandom);
    TL_REDIRECT(hooks,monster_modelBlend,&modelBlend);
    TL_REDIRECT(hooks,monster_pathFollowing,&path);
    TL_REDIRECT(hooks,monster_attaches,&attaches);
    TL_REDIRECT(hooks,monster_teleport,&teleport);
    TL_REDIRECT(hooks,monster_fidget,&ai<30>);
    TL_REDIRECT(hooks,monster_flee,&ai<31>);
    TL_REDIRECT(hooks,monster_getRange,&ai<32>);
    TL_REDIRECT(hooks,monster_jump,&ai<33>);
    TL_REDIRECT(hooks,monster_animationPlay,&scalarAI<34>);
    if(mode==0)TL_REDIRECT(hooks,monsterIdleBoundary,&idleBoundary);
    if(hooks.failed())return 1;autotest::Coverage coverage(name,address);
    for(unsigned i=0;i<count;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    monster mode%u seed%u exits%d/%d issues%u/%u\n",mode,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    bytes %lu/%lu first diff %lu word%lu\n",(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at,(unsigned long)(at/4));for(size_t k=at/4>8?at/4-8:0;k<at/4+16&&k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned av,bv;std::memcpy(&av,a.capture.data+k*4,4);std::memcpy(&bv,b.capture.data+k*4,4);host->log("    word%lu %08x/%08x\n",(unsigned long)k,av,bv);}coverage.report(host);return 1;}}
    coverage.report(host);return coverage.completed!=count||coverage.different||coverage.missing;
}
}
TL_TEST(all_monster_update_ai){return run(host,0,"all_monster_update_ai",0x8e3a40,4096);}
TL_TEST(all_monster_react_damage){return run(host,1,"all_monster_react_damage",0x8d5470,4096);}
TL_TEST(all_monster_hunt_ai){return run(host,2,"all_monster_hunt_ai",0x8df370,4096);}
TL_TEST(all_monster_attack_ai){return run(host,3,"all_monster_attack_ai",0x8dfd80,4096);}
TL_TEST(all_monster_idle_ai){return run(host,4,"all_monster_idle_ai",0x8e2d30,4096);}
