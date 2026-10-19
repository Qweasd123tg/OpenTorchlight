#include <cstring>
#include <clocale>
#include <limits>
#include <execinfo.h>
#include <fcntl.h>
#include <ucontext.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#define private public
#define protected public
#include "Character.h"
#include "Equipment.h"
#include "Inventory.h"
#include "EquipmentRef.h"
#include "Effect.h"
#include "EffectManager.h"
#include "AttackDescription.h"
#include "Skill.h"
#include "SoundBank.h"
#include "Console.h"
#include "GameSpeed.h"
#undef private
#undef protected
#include "tests/MenuGuiFixture.h"
#include "tests/FinishLevelFixture.h"
namespace {
#include "CharacterEmptyGlobals.h"
}
TL_ORIGINAL(bool,rOld,(CCharacter*,CLevel&,CCharacter*,CEquipment*,unsigned,float,float,EDAMAGE_TYPES),"_ZN10CCharacter10rollAttackER6CLevelPS_P10CEquipmentjff13EDAMAGE_TYPES")
extern "C" bool rNew(CCharacter*,CLevel&,CCharacter*,CEquipment*,unsigned,float,float,EDAMAGE_TYPES) __asm__("_ZN10CCharacter10rollAttackER6CLevelPS_P10CEquipmentjff13EDAMAGE_TYPES");
#include "CharacterRollAttackSymbols.h"
namespace {
struct Case{unsigned seed,control;};unsigned seed,mode,variant,phase;bool armed,oursSide;autotest::Capture*out;
nativegame::Services*services;finishlevel::Fixture*world;menugui::Fixture*menu;CConsole*realConsole;CCharacter*self,*target,*master;CEquipment*weapons[3];CAttackDescription*attacks[4];
void fault(int signal,siginfo_t*info,void*context){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/character/character-roll-attack-signal.log",O_WRONLY|O_CREAT|O_APPEND,0600);if(fd>=0){char line[220];ucontext_t*uc=static_cast<ucontext_t*>(context);int n=std::snprintf(line,sizeof(line),"signal%d side%u seed%u phase%u rip%llx address%p\n",signal,unsigned(oursSide),seed,phase,(unsigned long long)uc->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,line,n);void*stack[40];int count=backtrace(stack,40);backtrace_symbols_fd(stack,count,fd);close(fd);}raise(signal);}
void num(unsigned n){if(armed)out->add(&n,4);}void fp(float f){if(armed)out->add(&f,4);}void wide(const std::wstring&s){num(s.size());if(armed)out->add(s.data(),s.size()*4);}void text(const std::string&s){num(s.size());if(armed)out->add(s.data(),s.size());}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}unsigned id(const void*p){if(!p)return 0;if(p==self)return 1;if(p==target)return 2;if(p==master)return 3;for(unsigned i=0;i<3;++i)if(p==weapons[i])return 10+i;for(unsigned i=0;i<4;++i)if(p==attacks[i])return 20+i;return 99;}
float value(CCharacter*p,EEFFECT_TYPE type,EDAMAGE_TYPES damage){num(101);num(id(p));num(type);num(damage);if(type==10)return mode==11?0:float((int(seed)+int(damage))%7-2);if(type==25)return float(int(variant%5)-2)*13.75f;if(type==15||type==16)return mode==20?-125.0f:float(variant%3)*25.0f;if(type==99||type==102||type==103||type==88)return float(int(type)-80);if(type==89)return mode==21?-200.0f:25.0f;if(type==56)return mode==12?-100.0f:mode==13?100.0f:0.0f;if(type==136)return mode==14?100.0f:0.0f;if(type==30||type==126||type==31){if(mode==15)return 200.0f;if(mode==16)return -200.0f;if(mode==17)return std::numeric_limits<float>::quiet_NaN();return variant&2?10.0f:0.0f;}if(type==49||type==125||type==50)return variant&4?-4.25f:variant&2?3.25f:0.0f;if(type==12)return mode==18?5.0f:0.0f;if(type==54)return mode==19?3.5f:0.0f;return 0;}
void effectState(CEffect*e){num(e->m_eType);num(e->m_activation);fp(e->m_fRemainingDuration);fp(e->m_fValueC4);fp(e->m_reflectionMinimum);fp(e->m_fValueC0);vec(e->m_direction);wide(e->m_sName);wide(e->m_name78);}
class Actor:public CCharacter{public:Actor():CCharacter(NULL){}virtual bool applyEffectOnUnit(CCharacter*s,CBaseUnit*t,CEffect*e){num(103);num(id(s));num(id(t));effectState(e);return true;}};
class Gear:public CEquipment{public:Gear():CEquipment(NULL){}virtual float getEffectValue(EEFFECT_ACTIVATION a,EEFFECT_TYPE t,float base,EDAMAGE_TYPES d){num(107);num(id(this));num(a);num(t);fp(base);num(d);return mode==18?float(id(this)-9):0.0f;}};
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){num(109);num(id(p));num(t);if(p==self)return t==167?mode==3:t==28?bool(variant&8):false;if(p==weapons[0]||p==weapons[1]||p==weapons[2]){if(t==35)return mode==4||mode==5||(variant&1);if(t==21)return mode==10;if(t==162)return variant%3==0;if(t==163)return variant%3==1;if(t==164)return variant%3==2;}return false;}
bool theme(CBaseUnit*p,const std::wstring&s){num(113);num(id(p));wide(s);return variant&1;}
CEquipment*left(CCharacter*p){num(127);num(id(p));return variant%3==0?weapons[0]:NULL;}CEquipment*right(CCharacter*p){num(131);num(id(p));return variant%3==1?weapons[1]:NULL;}
float reflect(CCharacter*p){num(137);num(id(p));return mode==4?30.0f:0.0f;}bool critical(CCharacter*p,CCharacter*t){num(139);num(id(p));num(id(t));return variant&1;}
int maximum(CCharacter*p,CAttackDescription*a,CCharacter*t){num(149);num(id(p));num(id(a));num(id(t));return mode==22?0:mode==23?1:31+variant;}
int attribute(CCharacter*p){num(151);num(id(p));return 17+variant;}
int setting(CDynamicPropertyFile*p,unsigned key){num(157);num(p==services->master->m_pSettings);num(key);return variant&1;}
int integer(int a,int b){num(163);num(a);num(b);return variant%3==0?a:variant%3==1?b:a+(b-a)/2;}
float random(float a,float b){num(167);fp(a);fp(b);return variant%3==0?a:variant%3==1?b:a+(b-a)*.5f;}
int modify(CCharacter*p,int damage,EDAMAGE_TYPES type,int maximum,float scale){num(173);num(id(p));num(damage);num(type);num(maximum);fp(scale);return mode==6?1:mode==7?0:mode==8?-2:damage-int(type)-int(variant%4);}
int hp(CCharacter*p){num(179);num(id(p));return mode==9?3:250;}int maxHP(CCharacter*p){num(181);num(id(p));return 400;}
void interrupt(CCharacter*p,bool flag){num(191);num(id(p));num(flag);p->m_skillInterrupted=true;}
bool blocked(CCharacter*p){num(193);num(id(p));return mode==24;}
void damageEffects(CCharacter*p,CCharacter*s,float amount,int(*damages)[2],unsigned count,bool critical){num(197);num(id(p));num(id(s));fp(amount);num(count);num(critical);for(unsigned i=0;i<count;++i){num(damages[i][0]);num(damages[i][1]);}}
void add(CBaseUnit*p,CEffect*e){num(199);num(id(p));effectState(e);delete e;}
void transfer(CEffectManager*p,CCharacter*t,EEFFECT_ACTIVATION a,EEFFECT_TYPE type){num(211);num(p==self->m_pEffectManager?1:2);num(id(t));num(a);num(type);}void inventory(CInventory*p,CCharacter*t,EEFFECT_ACTIVATION a,EEFFECT_TYPE type){num(223);num(p==self->m_pInventory);num(id(t));num(a);num(type);}
void sound(CSoundBank*p,int sample,Ogre::SceneNode*n,float a,float b,bool flag){num(227);num(p==self->m_levelSound);num(sample);num(n==self->m_pSceneNode?1:n==target->m_pSceneNode?2:0);fp(a);fp(b);num(flag);}
void event(CGameUI*p,const Ogre::Vector3&v,const std::string&s,float a,float b,CEGUI::colour first,CEGUI::colour second){num(229);num(p==menu->ui);vec(v);text(s);fp(a);fp(b);fp(first.getRed());fp(first.getGreen());fp(first.getBlue());fp(first.getAlpha());fp(second.getRed());fp(second.getGreen());fp(second.getBlue());fp(second.getAlpha());}
void console(CConsole*p,std::wstring s){num(233);num(p==realConsole);wide(s);}
void hpChange(CCharacter*p,float amount){num(239);num(id(p));fp(amount);p->m_fHPFloat+=amount;}void manaChange(CCharacter*p,float amount){num(241);num(id(p));fp(amount);p->m_fManaFloat+=amount;}
float calculate(CEffect*p,CEffect::ECALCULATETYPES type){num(251);num(type);fp(p->m_reflectionMinimum);p->m_fValueC0=p->m_reflectionMinimum;return p->m_fValueC0;}
void damage(CCharacter*p,CLevel&level,const Ogre::Vector3&position,float amount,const Ogre::Vector3&direction,float force,CCharacter*source,bool a,bool b,bool c,bool d,unsigned flags){num(257);num(id(p));num(&level==&world->level);vec(position);fp(amount);vec(direction);fp(force);num(id(source));num(a);num(b);num(c);num(d);num(flags);if(variant&8)p->m_eAIState=AISTATE_DYING;p->m_fHPFloat-=amount;}
void strike(CCharacter*p,const Ogre::Vector3&a,const Ogre::Vector3&b,float radius,bool critical,bool blocked){num(263);num(id(p));vec(a);vec(b);fp(radius);num(critical);num(blocked);}void speed(EGAMESPEED_TYPE type,float a,float b){num(269);num(type);fp(a);fp(b);}
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;mode=seed%32;variant=seed/32;phase=1;oursSide=ours;armed=false;out=&capture;struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_sigaction=&fault;action.sa_flags=SA_SIGINFO|SA_RESETHAND;sigemptyset(&action.sa_mask);sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);
 menu=new menugui::Fixture(*services->master->m_pSettings,services->scene);realConsole=new CConsole(NULL,NULL,NULL);menu->ui->m_console=realConsole;world->level.m_pGameClient=menu->nativeClient.client;menu->nativeClient.client->m_pGameUI=menu->ui;
 self=new Actor;target=new CCharacter(NULL);master=new CCharacter(NULL);self->m_pResourceManager=&world->resources;self->m_pSceneNode=services->scene->getRootSceneNode()->createChildSceneNode();target->m_pSceneNode=services->scene->getRootSceneNode()->createChildSceneNode();self->m_vPosition=Ogre::Vector3(1.25f+variant*.5f,-2.5f,3.75f);target->m_vPosition=Ogre::Vector3(-4.25f,3.5f,1.75f);self->m_fHPFloat=100;master->m_fHPFloat=200;self->m_fManaFloat=50;target->m_fManaFloat=20;target->m_fHPFloat=250;target->m_eAIState=mode==1?AISTATE_DYING:mode==2?AISTATE_DEAD:static_cast<EAIState>(2);target->m_fBaseUnitValue194=.75f;self->m_characterDisplayName=L"Combat Ж";target->m_skillInterrupted=variant&2;target->m_skillTime=variant%3?1.0f:0.0f;target->m_skillLooping=variant&4;target->m_skillCanInterrupt=variant&8;target->m_activeSkill=variant&2?new CSkill(NULL,NULL):NULL;
 for(unsigned i=0;i<4;++i){attacks[i]=new CAttackDescription("attack",false,2,3,1,2,3,.75f+i*.25f);for(unsigned j=0;j<7;++j)attacks[i]->m_DamageMaximums[j]=(j+variant)%4?3+j:0;attacks[i]->m_iUnknown78=variant%6;}self->m_attack=mode==25?NULL:attacks[3];self->m_attacks.push_back(attacks[3]);for(unsigned i=0;i<3;++i){weapons[i]=new Gear;weapons[i]->m_pAttackDescription=attacks[i];weapons[i]->m_pAttackDescriptionOverride=variant&2?attacks[(i+1)%4]:NULL;for(unsigned j=0;j<7;++j){weapons[i]->m_ElementalDamageTypes.push_back(static_cast<EDAMAGE_TYPES>(j));weapons[i]->m_ElementalDamageBonuses.push_back(mode==11?0:j+1);weapons[i]->m_InherentElementalDamage.push_back(mode==11?0:1);}}
 self->m_pInventory=new CInventory(self,21);if(variant&4){for(unsigned i=0;i<2;++i){CEquipmentRef*r=new CEquipmentRef;r->m_pEquipment=weapons[i];r->m_iSlot=1-i;self->m_pInventory->m_equipmentRefs.add(r);}}self->m_attackItem=mode==26?NULL:weapons[2];self->m_pMaster=variant&8?master:NULL;self->m_pEffectManager=mode==27?NULL:new CEffectManager(self);self->m_pInventory->m_pEffectManager=variant&4?new CEffectManager(self):NULL;self->m_levelSound=variant&2?new CSoundBank(*services->master->m_pSoundManager,false):NULL;if(mode==18){weapons[2]->m_SocketedEquipment.add(weapons[0]);weapons[2]->m_SocketedEquipment.add(weapons[1]);}
 detour::Set patches;
#define P(name,fn) TL_REDIRECT(patches,r##name,&fn)
 P(ISA,isa);P(Theme,theme);P(Left,left);P(Right,right);P(Reflect,reflect);P(Critical,critical);P(Maximum,maximum);P(Strength,attribute);P(Dexterity,attribute);P(Magic,attribute);P(Value,value);P(Setting,setting);P(Integer,integer);P(Random,random);P(Modify,modify);P(HP,hp);P(MaxHP,maxHP);P(Interrupt,interrupt);P(Blocked,blocked);P(DamageEffects,damageEffects);P(Add,add);P(Transfer,transfer);P(Inventory,inventory);P(Sound,sound);P(Event,event);P(Console,console);P(HPChange,hpChange);P(ManaChange,manaChange);P(Calculate,calculate);P(Damage,damage);P(Strike,strike);P(Speed,speed);
#undef P
 if(patches.failed())_exit(43);unsigned flags=0;if(variant&1)flags|=1024;if(variant&2)flags|=8;if(mode==28)flags|=4096;if(mode==29)flags|=2048;phase=100;armed=true;typedef bool(*F)(CCharacter*,CLevel&,CCharacter*,CEquipment*,unsigned,float,float,EDAMAGE_TYPES);F fn=ours?rNew:rOld;if(!autotest::beginInvocation(capture,fn))return;CEquipment*weapon=mode==26?NULL:variant%4==0?NULL:weapons[variant%3];bool result=fn(self,world->level,mode==0?NULL:target,weapon,flags,variant%3==0?1.0f:variant%3==1?.5f:1.75f,variant&4?.5f:1.0f,static_cast<EDAMAGE_TYPES>(variant&4?2:7));capture.callCompleted=1;phase=101;if(ours&&c.control)result=!result;num(result);fp(self->m_fHPFloat);fp(master->m_fHPFloat);fp(target->m_fHPFloat);fp(self->m_fManaFloat);fp(target->m_fManaFloat);num(target->m_eAIState);num(target->m_skillInterrupted);armed=false;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(character_roll_attack_runtime){std::setlocale(LC_CTYPE,"C.UTF-8");initEmptyGlobals();const wchar_t*labels[]={L"Physical",L"Magical",L"Fire",L"Ice",L"Electric",L"Poison",L"All"};for(unsigned i=0;i<7;++i){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x147cb00+i*8),8);if(!p)new(reinterpret_cast<void*>(0x147cb00+i*8))std::wstring(labels[i]);}tlheadless::Environment env;env.loadGameSkin();nativegame::Services native;if(!native.ready())return 1;services=&native;menugui::Audio audio(native.master);CStringTranslate translate(L"");finishlevel::Fixture level;world=&level;world->resources.m_pLevel=&world->level;world->resources.m_pSceneManager=native.scene;int failures=0;autotest::Coverage coverage("character_roll_attack_runtime",(uintptr_t)&rOld);for(unsigned i=0;i<512;++i){Case c={i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    roll seed%u status%d/%d bytes%lu/%lu\n",i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j+3<a.capture.length&&j+3<b.capture.length;j+=4){unsigned x,y;std::memcpy(&x,a.capture.data+j,4);std::memcpy(&y,b.capture.data+j,4);if(x!=y){host->log("    word%u %08x/%08x\n",j/4,x,y);if(j>512)break;}}coverage.report(host);return failures;}}coverage.report(host);Case c={31,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    roll negative detected%u\n",unsigned(caught));return failures;}
