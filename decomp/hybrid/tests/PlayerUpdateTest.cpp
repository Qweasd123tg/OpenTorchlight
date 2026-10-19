#include <string>
#include <vector>
#include <map>
#include <new>
#include <limits>
#define private public
#define protected public
#include "Player.h"
#include "GameClient.h"
#include "GameUI.h"
#include "GenericModel.h"
#include "QuestManager.h"
#include "PathController.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldPlayerUpdate,(CPlayer*,Ogre::Camera*,const Ogre::Vector3&,float),"_ZN7CPlayer6updateEPN4Ogre6CameraERKNS0_7Vector3Ef")
extern "C" void newPlayerUpdate(CPlayer*,Ogre::Camera*,const Ogre::Vector3&,float) __asm__("_ZN7CPlayer6updateEPN4Ogre6CameraERKNS0_7Vector3Ef");
TL_FUNCTION(pup_base,"_ZN10CCharacter6updateEPN4Ogre6CameraERKNS0_7Vector3Ef")
TL_FUNCTION(pup_quest,"_ZN13CQuestManager6updateEf")
TL_FUNCTION(pup_path,"_ZN10CCharacter19updatePathFollowingEb")
TL_FUNCTION(pup_skill,"_ZN10CCharacter15performingSkillEv")
TL_FUNCTION(pup_attack,"_ZN10CCharacter16performingAttackEv")
TL_FUNCTION(pup_rng,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(pup_playing,"_ZNK10CCharacter16animationPlayingERKSs")
TL_FUNCTION(pup_exists,"_ZNK13CGenericModel24animationExistsSubstringERKSs")
TL_FUNCTION(pup_randomAnimation,"_ZN13CGenericModel19findRandomAnimationERKSs")
TL_FUNCTION(pup_blend,"_ZN13CGenericModel14blendAnimationEjbfff")
TL_FUNCTION(pup_queue,"_ZN10CCharacter19queueBlendAnimationERKSsbff")
TL_FUNCTION(pup_ui,"_ZN16CResourceManager9getGameUIEv")
TL_FUNCTION(pup_hp,"_ZN10CCharacter2HPEv")
TL_FUNCTION(pup_maxHP,"_ZN10CCharacter5maxHPEv")
TL_FUNCTION(pup_mana,"_ZN10CCharacter4manaEv")
TL_FUNCTION(pup_maxMana,"_ZN10CCharacter7maxManaEv")
TL_FUNCTION(pup_tip,"_ZN7CGameUI8queueTipE11EContextTip")
TL_FUNCTION(pup_petNearDeath,"_ZN10CCharacter14isPetNearDeathEv")
TL_FUNCTION(pup_death,"_ZN7CGameUI11toggleDeathEv")
TL_FUNCTION(pup_opacity,"_ZN10CCharacter13updateOpacityEfb")
namespace {
struct Case{unsigned index;};struct State{Case c;autotest::Capture*out;CPlayer*self;CCharacter*pet;CResourceManager*resources;CQuestManager*quests;CGameUI*ui;CPathController*path;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned v){active->out->add(&v,4);}void fp(float v){active->out->add(&v,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void text(const std::string&s){num(s.size());active->out->add(s.data(),s.size());}
void base(CCharacter*p,Ogre::Camera*camera,const Ogre::Vector3&v,float dt){num(1);num(p==active->self);num(camera==NULL);vec(v);fp(dt);if(hash(1)%7==0)p->m_isPathing=!p->m_isPathing;}
void quest(CQuestManager*p,float dt){num(2);num(p==active->quests);fp(dt);}
void path(CCharacter*p,bool flag){num(3);num(flag);p->m_isPathing=hash(3)&1;}
bool skill(CCharacter*){num(4);return(hash(4)&3)==0;}bool attack(CCharacter*){num(5);return(hash(5)&3)==0;}
int rng(int lo,int hi){num(6);num(lo);num(hi);const int values[]={0,1,2,3,1000};return values[hash(6)%5];}
bool playing(const CCharacter*,const std::string&name){num(7);text(name);return(hash(7)&1)!=0;}
bool exists(const CGenericModel*,const std::string&name){num(8);text(name);return(hash(8)&1)!=0;}
unsigned animation(CGenericModel*,const std::string&name){num(9);text(name);return 17;}
void blend(CGenericModel*,unsigned n,bool loop,float a,float b,float c){num(10);num(n);num(loop);fp(a);fp(b);fp(c);}
void queue(CCharacter*,const std::string&name,bool loop,float a,float b){num(11);text(name);num(loop);fp(a);fp(b);}
CGameUI*ui(CResourceManager*){num(12);return hash(12)%5?active->ui:NULL;}
int hp(CCharacter*){num(13);const int values[]={-1,0,1,34,35,36,100};return values[hash(13)%7];}int maxhp(CCharacter*){num(14);return hash(14)&1?100:10;}int mana(CCharacter*){num(15);return int(hash(15)%5)*10;}int maxmana(CCharacter*){num(16);return hash(16)&1?100:50;}
void tip(CGameUI*,EContextTip n){num(17);num(n);}bool pet(CCharacter*p){num(18);num(p==active->pet);return(hash(18)&1)!=0;}
void death(CGameUI*){num(19);}void opacity(CCharacter*,float dt,bool force){num(20);fp(dt);num(force);}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;active=&s;s.c=c;s.out=&out;s.self=static_cast<CPlayer*>(autotest::allocate(sizeof(CPlayer)));s.pet=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.resources=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));s.quests=static_cast<CQuestManager*>(autotest::allocate(sizeof(CQuestManager)));s.ui=static_cast<CGameUI*>(autotest::allocate(sizeof(CGameUI)));s.path=static_cast<CPathController*>(autotest::allocate(sizeof(CPathController)));new(s.path)CRunicCore;
 CGameClient*client=static_cast<CGameClient*>(autotest::allocate(sizeof(CGameClient)));client->m_gameState=static_cast<EGameState>(hash(21)%3);new(&s.resources->m_GameClients)TArrayList<CGameClient*>;s.resources->m_GameClients.add(client);s.self->m_pResourceManager=s.resources;s.self->m_questManager=hash(22)%3?s.quests:NULL;s.self->m_isPathing=hash(23)&1;s.self->m_eAIState=static_cast<EAIState>(hash(24)%4);s.self->m_returningToTown=hash(25)&1;
 const float times[]={0,9.99f,10,10.01f,20,std::numeric_limits<float>::quiet_NaN()};s.self->m_fidgetTime=times[hash(26)%6];s.self->m_pUnitModel=static_cast<CGenericModel*>(autotest::allocate(sizeof(CGenericModel)));new(&s.self->m_Followers)std::vector<CCharacter*>;if(hash(27)%3)s.self->m_Followers.push_back(s.pet);new(&s.self->m_pathToFollow)TSafePointer<CPathController>;if(hash(28)%3)s.self->m_pathToFollow.setObject(s.path);
 const float delays[]={-1,0,.125f,.25f,5,std::numeric_limits<float>::quiet_NaN()};s.self->m_deathDelay=delays[hash(29)%6];s.self->m_currentOpacity=.75f;s.self->m_playerTranslucent=hash(30)&1;float elapsed=float(hash(31)%5)*.125f;Ogre::Vector3 viewer(6,3,-2);typedef void(*F)(CPlayer*,Ogre::Camera*,const Ogre::Vector3&,float);F f=ours?newPlayerUpdate:oldPlayerUpdate;if(!autotest::beginInvocation(out,f))return;f(s.self,NULL,viewer,elapsed);out.callCompleted=1;
 num(s.self->m_returningToTown);num(s.self->m_isPathing);fp(s.self->m_fidgetTime);fp(s.self->m_deathDelay);fp(s.self->m_currentOpacity);s.self->m_pathToFollow.~TSafePointer();s.path->CRunicCore::~CRunicCore();s.self->m_Followers.~vector();s.resources->m_GameClients.~TArrayList();
}
void before(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void after(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(all_player_update){detour::Set h;TL_REDIRECT(h,pup_base,&base);TL_REDIRECT(h,pup_quest,&quest);TL_REDIRECT(h,pup_path,&path);TL_REDIRECT(h,pup_skill,&skill);TL_REDIRECT(h,pup_attack,&attack);TL_REDIRECT(h,pup_rng,&rng);TL_REDIRECT(h,pup_playing,&playing);TL_REDIRECT(h,pup_exists,&exists);TL_REDIRECT(h,pup_randomAnimation,&animation);TL_REDIRECT(h,pup_blend,&blend);TL_REDIRECT(h,pup_queue,&queue);TL_REDIRECT(h,pup_ui,&ui);TL_REDIRECT(h,pup_hp,&hp);TL_REDIRECT(h,pup_maxHP,&maxhp);TL_REDIRECT(h,pup_mana,&mana);TL_REDIRECT(h,pup_maxMana,&maxmana);TL_REDIRECT(h,pup_tip,&tip);TL_REDIRECT(h,pup_petNearDeath,&pet);TL_REDIRECT(h,pup_death,&death);TL_REDIRECT(h,pup_opacity,&opacity);if(h.failed())return 1;autotest::Coverage coverage("all_player_update",0x8e48a0);for(unsigned i=0;i<4096;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    player update seed%u status%d/%d bytes%lu/%lu\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned k=0;k*4<a.capture.length&&k*4<b.capture.length;++k){unsigned x,y;std::memcpy(&x,a.capture.data+k*4,4);std::memcpy(&y,b.capture.data+k*4,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=4096||coverage.different||coverage.missing;}
