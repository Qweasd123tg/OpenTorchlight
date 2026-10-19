#include <cstring>
#include <limits>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "Item.h"
#include "Skill.h"
#include "SkillManager.h"
#include "AttackDescription.h"
#include "Level.h"
#include "GameClient.h"
#include "GameUI.h"
#include "QuestManager.h"
#include "Quest.h"
#include "SoundBank.h"
#undef protected
#undef private
#define DECL(name,method) TL_ORIGINAL(void,old##name,(CCharacter*,float,CLevel&),method) extern "C" void new##name(CCharacter*,float,CLevel&) __asm__(method);
DECL(Approach,"_ZN10CCharacter10approachAIEfR6CLevel")
DECL(Attack,"_ZN10CCharacter8attackAIEfR6CLevel")
DECL(Skill,"_ZN10CCharacter7skillAIEfR6CLevel")
DECL(Hunt,"_ZN10CCharacter6huntAIEfR6CLevel")
DECL(Item,"_ZN10CCharacter9getItemAIEfR6CLevel")
#undef DECL
TL_ORIGINAL(void,oldSkillApproach,(CCharacter*,float,CLevel&,long long),"_ZN10CCharacter15skillApproachAIEfR6CLevelx")
extern "C" void newSkillApproach(CCharacter*,float,CLevel&,long long) __asm__("_ZN10CCharacter15skillApproachAIEfR6CLevelx");
TL_ORIGINAL(bool,oldCastCheck,(CCharacter*,CBaseUnit*,bool,bool),"_ZN10CCharacter19canCastCurrentSkillEP9CBaseUnitbb")
extern "C" bool newCastCheck(CCharacter*,CBaseUnit*,bool,bool) __asm__("_ZN10CCharacter19canCastCurrentSkillEP9CBaseUnitbb");
#define FN(name,sym) TL_FUNCTION(ai_##name,sym)
FN(position,"_ZN19CPositionableObject11getPositionEb")
FN(isa,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
FN(player,"_ZN9CBaseUnit8isPlayerEv")
FN(near,"_ZN10CCharacter14isPetNearDeathEv")
FN(available,"_ZN10CCharacter19availableForCommandEv")
FN(friend,"_ZN10CCharacter8isFriendEPS_")
FN(target,"_ZN10CCharacter9setTargetEPS_")
FN(targetItem,"_ZN10CCharacter13setTargetItemEP5CItem")
FN(select,"_ZN10CCharacter12selectAttackE18EATTACK_RANGE_TYPE")
FN(range,"_ZN10CCharacter13inAttackRangeE18EATTACK_RANGE_TYPE")
FN(skillRange,"_ZN10CCharacter12inSkillRangeExb")
FN(sight,"_ZN10CCharacter16validLineOfSightER6CLevelb")
FN(turn,"_ZN10CCharacter18turnTowardPositionERKN4Ogre7Vector3Ef")
FN(facing,"_ZN10CCharacter12facingTargetEv")
FN(attack,"_ZN10CCharacter6attackEv")
FN(cast,"_ZN10CCharacter9castSkillEx")
FN(follow,"_ZN10CCharacter15followCharacterEPS_R6CLevel")
FN(destination,"_ZN10CCharacter14setDestinationER6CLevelff")
FN(interaction,"_ZN10CCharacter18inInteractionRangeEv")
FN(getItem,"_ZN10CCharacter7getItemEP5CItemR6CLevel")
FN(targetType,"_ZN6CSkill13getTargetTypeEv")
FN(cancel,"_ZN6CSkill16rollCancelChanceEv")
FN(known,"_ZN13CSkillManager11knownSkillsE22ESKILL_ACTIVATION_TYPE")
FN(skillGuid,"_ZN13CSkillManager14getSkillByGuidEx")
FN(check,"_ZN10CCharacter19canCastCurrentSkillEP9CBaseUnitbb")
FN(questManager,"_ZN13CQuestManager12getSingletonEv")
FN(quest,"_ZN13CQuestManager14getQuestForNPCEP9CBaseUnit")
FN(cheat,"_ZN11CGameClient16getPlayerIsCheatEv")
FN(mana,"_ZN10CCharacter4manaEv")
FN(cost,"_ZN6CSkill11getManaCostEv")
FN(costOT,"_ZN6CSkill13getManaCostOTEv")
FN(chance,"_ZN6CSkill14rollCastChanceEv")
FN(cooling,"_ZN13CSkillManager17getSkillIsCoolingEP6CSkill")
FN(execute,"_ZN13CSkillManager21getSkillCanBeExecutedEP6CSkillP9CBaseUnit22ESKILL_ACTIVATION_TYPERKN4Ogre7Vector3ES3_b")
FN(alignment,"_ZN10CCharacter18getTargetAlignmentEv")
FN(valid,"_ZN6CSkill16getTargetIsValidEP10CCharacterS1_PKN4Ogre7Vector3Eb")
FN(skillDistance,"_ZN6CSkill8getRangeEv")
FN(angle,"_ZN6CSkill18getFindTargetAngleEv")
FN(find,"_ZN6CLevel23findCharacterWithinViewERKN4Ogre7Matrix4E10EAlignmentfffbP10CCharacterP6CSkill")
FN(tip,"_ZN7CGameUI8queueTipE11EContextTip")
FN(sound,"_ZN10CSoundBank17queueGlobalSampleEiff")
#undef FN
namespace {
struct Case{unsigned op,seed,control;};struct State{Case c;autotest::Capture*out;bool armed;CCharacter*self,*target,*master,*found;CItem*item;CSkill*skill,*alternate;CSkillManager*manager;CAttackDescription*attack;CResourceManager*resources;CLevel*level;CGameClient*client;CGameUI*ui;CSoundBank*sound;CQuestManager*quests;CQuest*quest;};State*s;
unsigned hash(unsigned n){unsigned v=s->c.seed*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned v){if(s->armed)s->out->add(&v,4);}void fp(float v){if(s->armed)s->out->add(&v,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}unsigned id(const void*p){return !p?0:p==s->self?1:p==s->target?2:p==s->master?3:p==s->found?4:p==s->item?5:p==s->skill?6:p==s->alternate?7:p==s->manager?8:p==s->level?9:99;}
float scalar(unsigned k){const float v[]={0,.1f,.2f,.5f,1,1.01f,2,2.75f,3,4,10,34.99f,35,35.01f,100,std::numeric_limits<float>::quiet_NaN()};return v[hash(k)%16];}
class Character:public CCharacter{public:Character():CCharacter(NULL){}virtual bool getEnabled(){num(1);num(id(this));return hash(1)%11!=0;}virtual void setAIState(EAIState state){num(2);num(id(this));num(state);m_eAIState=state;}virtual void updateAI(float elapsed,bool force){num(3);num(id(this));fp(elapsed);num(force);}virtual bool canAttackWithCurrentWeapon(){num(4);return hash(2)%3!=0;}virtual void startFishing(){num(5);}virtual void removeFromAvoidanceMap(CLevel&l){num(6);num(id(&l));}};
class Item:public CItem{public:Item():CItem(NULL){}virtual void setActiveInLevel(bool){}virtual void*getUnitModel(){return NULL;}virtual void*getUnitCollisionModel(){return NULL;}virtual bool interact(CCharacter*p){num(7);num(id(p));return hash(3)&1;}};
void initStrings(){const unsigned long strings[]={0x1479460,0x147c340,0x1480a40,0x1484120,0x145dd00,0x14e5948,0x14f6ec0,0x14ee340};for(unsigned i=0;i<sizeof(strings)/sizeof(*strings);++i){void*p=NULL;memcpy(&p,reinterpret_cast<void*>(strings[i]),8);if(!p)new(reinterpret_cast<void*>(strings[i]))std::string;memcpy(&p,reinterpret_cast<void*>(strings[i]+8),8);if(!p)new(reinterpret_cast<void*>(strings[i]+8))std::wstring;}}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){num(11);num(id(p));num(absolute);return p->m_vPosition;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){num(12);num(id(p));num(type);if(p==s->self)return type==28?hash(4)%5==0:type==169?hash(5)%4==0:false;const unsigned choices[]={0,130,175,132,133,134,41,128,170,104};if(p==s->target)return unsigned(type)==choices[s->c.seed%10];if(p==s->item){unsigned mode=s->c.seed%9;return type==29?mode<3:type==30?mode<4:type==32?mode>=4:unsigned(type)==(mode==4?122:mode==5?157:mode==6?158:mode==7?159:0);}return false;}
bool player(CBaseUnit*p){num(13);num(id(p));return p==s->self?hash(6)%3==0:hash(7)&1;}
bool near(CCharacter*p){num(14);num(id(p));return hash(8+id(p))%17==0;}bool available(CCharacter*p){num(15);num(id(p));return hash(10)%13!=0;}bool friendOf(CCharacter*p,CCharacter*q){num(16);num(id(p));num(id(q));return hash(11)%11==0;}
void target(CCharacter*p,CCharacter*q){num(17);num(id(p));num(id(q));p->m_targetCharacter.setObject(q);}void targetItem(CCharacter*p,CItem*q){num(18);num(id(p));num(id(q));p->m_targetItem.setObject(q);}
void select(CCharacter*p,EATTACK_RANGE_TYPE type){num(19);num(type);p->m_attack=hash(12)%3?s->attack:NULL;}
bool range(CCharacter*,EATTACK_RANGE_TYPE type){num(20);num(type);return hash(13)%3!=0;}int skillRange(CCharacter*,long long guid,bool ignore){num(21);num(unsigned(guid));num(unsigned(guid>>32));num(ignore);return int(hash(14)%3)-1;}
bool sight(CCharacter*,CLevel&l,bool flag){num(22);num(id(&l));num(flag);return hash(15)%3!=0;}void turn(CCharacter*,const Ogre::Vector3&p,float elapsed){num(23);vec(p);fp(elapsed);}bool facing(CCharacter*){num(24);return hash(16)%3!=0;}
bool attack(CCharacter*){num(25);return hash(17)&1;}bool cast(CCharacter*,long long guid){num(26);num(unsigned(guid));num(unsigned(guid>>32));return hash(18)&1;}
void follow(CCharacter*p,CCharacter*q,CLevel&l){num(27);num(id(q));num(id(&l));p->m_isPathing=hash(19)%4!=0;p->m_targetPosition=q->m_vPosition;}
void destination(CCharacter*p,CLevel&l,float x,float z){num(28);num(id(&l));fp(x);fp(z);p->m_isPathing=hash(20)%4!=0;p->m_pathDestination=Ogre::Vector3(x,0,z);}
bool interaction(CCharacter*){num(29);return hash(21)%3!=0;}void getItem(CCharacter*,CItem*p,CLevel&l){num(30);num(id(p));num(id(&l));}
int targetType(CSkill*p){num(31);num(id(p));const int v[]={1,2,3,5,6,9,10,11,12};return v[hash(22)%9];}bool cancel(CSkill*p){num(32);num(id(p));return hash(23)&1;}
int known(CSkillManager*p,ESKILL_ACTIVATION_TYPE type){num(33);num(id(p));num(type);return hash(24)%7!=0;}CSkill*skillGuid(CSkillManager*p,long long guid){num(34);num(id(p));num(unsigned(guid));num(unsigned(guid>>32));return hash(25)%5==0?NULL:hash(26)&1?s->skill:s->alternate;}
bool check(CCharacter*,CBaseUnit*p,bool test,bool skip){num(35);num(id(p));num(test);num(skip);return hash(27)%4!=0;}
CQuestManager*questManager(){num(36);return s->quests;}CQuest*quest(CQuestManager*,CBaseUnit*p){num(37);num(id(p));return s->c.seed%11==0?s->quest:NULL;}bool cheat(CGameClient*p){num(38);num(p==s->client);return hash(28)&1;}
int mana(CCharacter*){num(39);return int(hash(29)%5)-2;}int cost(CSkill*p){num(40);num(id(p));return int(hash(30)%5)-2;}int costOT(CSkill*p){num(41);num(id(p));return int(hash(31)%5)-2;}bool chance(CSkill*p){num(42);num(id(p));return hash(32)%5!=0;}
bool cooling(CSkillManager*p,CSkill*q){num(43);num(id(p));num(id(q));return hash(33)%5==0;}bool execute(CSkillManager*p,CSkill*q,CBaseUnit*r,ESKILL_ACTIVATION_TYPE type,const Ogre::Vector3&v,CBaseUnit*t,bool flag){num(44);num(id(p));num(id(q));num(id(r));num(type);vec(v);num(id(t));num(flag);return hash(34)&1;}
EAlignment alignment(CCharacter*){num(45);return static_cast<EAlignment>(hash(35)%7);}bool valid(CSkill*p,CCharacter*q,CCharacter*r,const Ogre::Vector3*v,bool flag){num(46);num(id(p));num(id(q));num(id(r));vec(*v);num(flag);return hash(36)%3!=0;}
float skillDistance(CSkill*p){num(47);num(id(p));return scalar(37);}float angle(CSkill*p){num(48);num(id(p));return scalar(38);}
CCharacter*find(CLevel*p,const Ogre::Matrix4&m,EAlignment align,float minimum,float angle,float range,bool flag,CCharacter*exclude,CSkill*skill){num(49);num(id(p));for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j)fp(m[i][j]);num(align);fp(minimum);fp(angle);fp(range);num(flag);num(id(exclude));num(id(skill));return hash(39)%3?s->found:NULL;}
void tip(CGameUI*p,EContextTip value){num(50);num(p==s->ui);num(value);}void sound(CSoundBank*p,int index,float a,float b){num(51);num(p==s->sound);num(index);fp(a);fp(b);}
void side(void*raw,autotest::Capture&out,bool ours){State state;memset(&state,0,sizeof(state));s=&state;s->c=*static_cast<Case*>(raw);s->out=&out;autotest::g_arenaUsed=0;initStrings();s->self=new Character;s->target=new Character;s->master=new Character;s->found=new Character;s->item=new Item;s->skill=new CSkill(NULL,NULL);s->alternate=new CSkill(NULL,NULL);s->manager=new CSkillManager(NULL,s->self);s->attack=new CAttackDescription("attack",false,1,2,3,4,5,6);
 s->resources=new CResourceManager(NULL);s->level=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));s->client=static_cast<CGameClient*>(autotest::allocate(sizeof(CGameClient)));s->ui=static_cast<CGameUI*>(autotest::allocate(sizeof(CGameUI)));s->sound=static_cast<CSoundBank*>(autotest::allocate(sizeof(CSoundBank)));s->quests=static_cast<CQuestManager*>(autotest::allocate(sizeof(CQuestManager)));s->quest=static_cast<CQuest*>(autotest::allocate(sizeof(CQuest)));
 s->resources->m_pLevel=s->level;s->resources->m_GameClients.add(s->client);s->level->m_pGameClient=s->client;s->client->m_pGameUI=s->ui;s->self->m_pResourceManager=s->resources;
 CCharacter*p=s->self;unsigned targetMode=(s->c.seed/10)%5;p->m_targetCharacter.setObject(targetMode==0?NULL:s->target);p->m_targetItem.setObject(targetMode<2?s->item:NULL);if(s->c.op==0&&!p->m_targetCharacter.getObject()&&p->m_targetItem.getObject())s->item->m_vPosition=Ogre::Vector3(100,0,100);else s->item->m_vPosition=Ogre::Vector3(scalar(40),91,scalar(41));
 p->m_vPosition=Ogre::Vector3(1,77,2);s->target->m_vPosition=Ogre::Vector3(scalar(42),-71,scalar(43));s->master->m_vPosition=Ogre::Vector3(scalar(44),11,scalar(45));s->found->m_vPosition=Ogre::Vector3(3,4,5);
 p->m_targetPosition=Ogre::Vector3(scalar(46),0,scalar(47));p->m_targetDirection=Ogre::Vector3(0,0,1);p->m_vScale=Ogre::Vector3(1,1,scalar(48));p->m_attackRadius=scalar(49);p->m_attackRangeScale=scalar(50);p->m_isPathing=hash(51)&1;p->m_pathGraceTime=scalar(52);p->m_pathDestination=Ogre::Vector3(-9,-8,-7);p->m_returningToTown=hash(53)&1;p->m_followRange=scalar(54);p->m_nearWalkRadius=scalar(55);p->m_pMaster=hash(56)%3?s->master:NULL;p->m_moveInputHeld=hash(57)%7==0;p->m_attack=hash(58)%3?s->attack:NULL;p->m_activeSkill=hash(59)%9?s->skill:NULL;p->m_skillTime=scalar(60);p->m_skillLooping=hash(61)%5==0;p->m_skillInterrupted=hash(62)&1;p->m_attackTime=scalar(63);p->m_pSkillManager=hash(64)%11?s->manager:NULL;p->m_levelSound=hash(65)&1?s->sound:NULL;p->m_fBaseUnitValue194=scalar(66);s->skill->m_Guid=0x1234567800000000LL+s->c.seed;s->skill->m_iTargetAlignment=hash(67)%7;s->alternate->m_Guid=77;s->target->m_eAIState=static_cast<EAIState>(s->c.seed%17==0?5:s->c.seed%19==0?6:2);
 detour::Set patches;
#define PATCH(name,fn) TL_REDIRECT(patches,ai_##name,&fn)
 PATCH(position,position);PATCH(isa,isa);PATCH(player,player);PATCH(near,near);PATCH(available,available);PATCH(friend,friendOf);PATCH(target,target);PATCH(targetItem,targetItem);PATCH(select,select);PATCH(range,range);PATCH(skillRange,skillRange);PATCH(sight,sight);PATCH(turn,turn);PATCH(facing,facing);PATCH(attack,attack);PATCH(cast,cast);PATCH(follow,follow);PATCH(destination,destination);PATCH(interaction,interaction);PATCH(getItem,getItem);PATCH(targetType,targetType);PATCH(cancel,cancel);PATCH(known,known);PATCH(skillGuid,skillGuid);if(s->c.op!=6){PATCH(check,check);}PATCH(questManager,questManager);PATCH(quest,quest);PATCH(cheat,cheat);PATCH(mana,mana);PATCH(cost,cost);PATCH(costOT,costOT);PATCH(chance,chance);PATCH(cooling,cooling);PATCH(execute,execute);PATCH(alignment,alignment);PATCH(valid,valid);PATCH(skillDistance,skillDistance);PATCH(angle,angle);PATCH(find,find);PATCH(tip,tip);PATCH(sound,sound);
#undef PATCH
 if(patches.failed())_exit(43);s->armed=true;
 if(s->c.op<5){typedef void(*F)(CCharacter*,float,CLevel&);F old[]={oldApproach,oldAttack,oldSkill,oldHunt,oldItem},fresh[]={newApproach,newAttack,newSkill,newHunt,newItem};F fn=ours?fresh[s->c.op]:old[s->c.op];if(!autotest::beginInvocation(out,fn))return;fn(p,scalar(68),*s->level);out.callCompleted=1;}
 else if(s->c.op==5){typedef void(*F)(CCharacter*,float,CLevel&,long long);F fn=ours?newSkillApproach:oldSkillApproach;if(!autotest::beginInvocation(out,fn))return;fn(p,scalar(68),*s->level,hash(69)&1?-1:0x123456789abcdefLL);out.callCompleted=1;}
 else{typedef bool(*F)(CCharacter*,CBaseUnit*,bool,bool);F fn=ours?newCastCheck:oldCastCheck;CBaseUnit*t=hash(70)%3==0?NULL:hash(70)%3==1?static_cast<CBaseUnit*>(s->target):static_cast<CBaseUnit*>(s->item);if(!autotest::beginInvocation(out,fn))return;bool result=fn(p,t,hash(71)&1,hash(72)&1);num(ours&&s->c.control?!result:result);out.callCompleted=1;}
 if(ours&&s->c.control&&s->c.op!=6)p->m_eAIState=static_cast<EAIState>(unsigned(p->m_eAIState)^1);num(p->m_eAIState);num(id(p->m_targetCharacter.getObject()));num(id(p->m_targetItem.getObject()));num(id(p->m_activeSkill));num(p->m_attack==s->attack);num(p->m_isPathing);fp(p->m_pathGraceTime);vec(p->m_pathDestination);vec(p->m_targetPosition);num(p->m_returningToTown);num(id(s->target->m_targetCharacter.getObject()));num(s->target->m_isPathing);fp(s->target->m_pathGraceTime);vec(s->target->m_pathDestination);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void recovered(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*host,unsigned op,unsigned count){int failures=0;const uintptr_t addresses[]={(uintptr_t)&oldApproach,(uintptr_t)&oldAttack,(uintptr_t)&oldSkill,(uintptr_t)&oldHunt,(uintptr_t)&oldItem,(uintptr_t)&oldSkillApproach,(uintptr_t)&oldCastCheck};autotest::Coverage coverage("character_ai_runtime",addresses[op]);unsigned states[64]={0};for(unsigned i=0;i<count;++i){Case c={op,i,0};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int pair=coverage.observe(host,a,b);if(!pair&&a.capture.length>=80){unsigned state;memcpy(&state,a.capture.data+a.capture.length-80,4);if(state<64)++states[state];}TL_CHECK(failures,!pair);if(pair){host->log("    AI op%u seed%u status%d/%d issue%u/%u bytes%lu/%lu\n",op,i,a.status,b.status,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j<a.capture.length&&j<b.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first byte%u %02x/%02x\n",j,(unsigned char)a.capture.data[j],(unsigned char)b.capture.data[j]);break;}coverage.report(host);return failures;}}coverage.report(host);for(unsigned state=0;state<64;++state)if(states[state])host->log("    AI op%u endpoint state%u cases%u\n",op,state,states[state]);Case c={op,19,1};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);bool caught=a.capture.length!=b.capture.length||memcmp(a.capture.data,b.capture.data,a.capture.length)!=0;TL_CHECK(failures,caught&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b));host->log("    AI op%u negative detected %u\n",op,unsigned(caught));return failures;}
}
TL_TEST(character_ai_runtime){int failures=0;for(unsigned op=0;op<7;++op){failures+=run(host,op,1024);if(failures)return failures;}return failures;}
