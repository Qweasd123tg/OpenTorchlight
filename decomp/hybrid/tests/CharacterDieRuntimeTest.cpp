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
#include "Particle.h"
#include "Path.h"
#include "SkillManager.h"
#include "EffectManager.h"
#include "Affix.h"
#include "SoundBank.h"
#include "CameraControl.h"
#include "CameraShake.h"
#include "SteamStats.h"
#include "SpawnClass.h"
#undef protected
#undef private
#include "tests/NativeMenuServices.h"
#include "tests/FinishLevelFixture.h"
namespace {
#include "CharacterEmptyGlobals.h"
}
TL_ORIGINAL(void,dOld,(CCharacter*,CCharacter*,const Ogre::Vector3*,float,bool),"_ZN10CCharacter3dieEPS_PKN4Ogre7Vector3Efb")
extern "C" void dNew(CCharacter*,CCharacter*,const Ogre::Vector3*,float,bool) __asm__("_ZN10CCharacter3dieEPS_PKN4Ogre7Vector3Efb");
#include "CharacterDieSymbols.h"
namespace {
struct Case { unsigned seed,control; };
unsigned seed,mode,variant,rays,phase; bool armed,oursSide; autotest::Capture*out;
nativegame::Services*services; finishlevel::Fixture*world; CCharacter*self,*killer,*master;
CParticle*particles[11]; CAffix*frozen; CCameraControl*camera; CSteamStats*stats; CSpawnClass*spawn;
void fault(int signal,siginfo_t*info,void*context){int fd=open("/home/qweasd123tg/Code/левые проекты/OpenTorchlight/build-decomp/all-functions-20261018/character/character-die-signal.log",O_WRONLY|O_CREAT|O_APPEND,0600);if(fd>=0){char line[220];ucontext_t*uc=static_cast<ucontext_t*>(context);int n=std::snprintf(line,sizeof(line),"signal%d side%u seed%u phase%u rays%u rip%llx address%p\n",signal,unsigned(oursSide),seed,phase,rays,(unsigned long long)uc->uc_mcontext.gregs[REG_RIP],info->si_addr);write(fd,line,n);void*stack[40];int count=backtrace(stack,40);backtrace_symbols_fd(stack,count,fd);close(fd);}raise(signal);}
void num(unsigned x){if(armed)out->add(&x,4);} void fp(float x){if(armed)out->add(&x,4);} void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);} void wide(const std::wstring&s){num(s.size());if(armed)out->add(s.data(),s.size()*sizeof(wchar_t));}void text(const std::string&s){num(s.size());if(armed)out->add(s.data(),s.size());}
unsigned id(const void*p){if(!p)return 0;if(p==self)return 1;if(p==killer)return 2;if(p==master)return 3;if(p==camera)return 4;if(p==stats)return 5;if(p==spawn)return 6;for(unsigned i=0;i<11;++i)if(p==particles[i])return 100+i;return 99;}
class Actor:public CCharacter{public:Actor():CCharacter(NULL){}virtual void setAIState(EAIState state){num(101);num(state);m_eAIState=state;}};
bool theme(CBaseUnit*p,const std::wstring&name){num(103);num(id(p));wide(name);return variant&1;}
void untheme(CBaseUnit*p,const std::wstring&name){num(107);num(id(p));wide(name);}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){num(109);num(id(p));num(type);return mode==7;}
bool player(CBaseUnit*p){num(113);num(id(p));return variant&1;}
int hp(CCharacter*p){num(127);num(id(p));return static_cast<int>(p->m_fHPFloat);}
void modify(CCharacter*p,float change){num(131);num(id(p));fp(change);p->m_fHPFloat+=change;}
void journal(CCharacter*p,EJournalStatistic type,int count){num(137);num(id(p));num(type);num(count);}
void procs(CCharacter*p,EEFFECT_TYPE type,CBaseUnit*target){num(139);num(id(p));num(type);num(id(target));}
void target(CCharacter*p,CCharacter*t){num(149);num(id(p));num(id(t));p->m_targetCharacter.setObject(t);}
void mesh(CCharacter*p,bool a,bool b){num(151);num(id(p));num(a);num(b);}
void visible(CCharacter*p,bool a,bool b){num(157);num(id(p));num(a);num(b);p->m_bVisible=a;}
EAlignment align(CCharacter*p){num(163);num(id(p));return static_cast<EAlignment>(variant%3);}
void state(CBaseUnit*p,EUNIT_STATES type){num(167);num(id(p));num(type);}
void killed(CBaseUnit*p){num(173);num(id(p));}
void quest(CBaseUnit*p,EQUEST_EVENTS type,CCharacter*k,CBaseUnit*t){num(179);num(id(p));num(type);num(id(k));num(id(t));}
void start(CParticle*p){num(181);num(id(p));vec(p->getPosition(false));}
void stop(CParticle*p,bool instant){num(191);num(id(p));num(instant);}
void sound(CSoundBank*p,int sample,Ogre::SceneNode*node,float a,float b,bool flag){num(193);num(p==self->m_levelSound);num(sample);num(node==self->m_pSceneNode);fp(a);fp(b);num(flag);}
bool effect(CEffectManager*p,EEFFECT_TYPE type){num(197);num(p==self->m_pEffectManager);num(type);return variant&2;}
CAffix*affix(CEffectManager*p,const std::wstring&name){num(199);num(p==self->m_pEffectManager);wide(name);return mode==3||mode==4?frozen:NULL;}
void skillsStop(CSkillManager*p,bool a,bool b,bool c){num(211);num(p==self->m_pSkillManager);num(a);num(b);num(c);if(mode==21)self->m_pSkillManager=NULL;}
void skillsFire(CSkillManager*p,CBaseUnit*unit,ESKILL_ACTIVATION_TYPE type,const Ogre::Vector3&position,const Ogre::Quaternion&q,const Ogre::Vector3&to,CCharacter*t){num(223);num(p==self->m_pSkillManager);num(id(unit));num(type);vec(position);fp(q.w);fp(q.x);fp(q.y);fp(q.z);vec(to);num(id(t));}
bool exists(const CGenericModel*p,const std::string&name){num(227);num(p==self->m_pUnitModel);text(name);return mode!=11;}
bool substring(const CGenericModel*p,const std::string&name){num(229);num(p==self->m_pUnitModel);text(name);return variant&1;}
int find(CGenericModel*p,const std::string&name){num(233);num(p==self->m_pUnitModel);text(name);return 7+variant;}
float length(const CGenericModel*p,const std::string&name){num(239);num(p==self->m_pUnitModel);text(name);return .75f+variant*.125f;}
void clear(CGenericModel*p){num(241);num(p==self->m_pUnitModel);}
CCameraControl*getCamera(CResourceManager*p){num(251);num(p==&world->resources);return camera;}
void shake(CCameraControl*p,CCameraShake*s,bool owning){num(257);num(id(p));wide(s->m_strCameraShakeName);fp(s->m_fDuration);fp(s->m_fMagnitudeMultiplier);fp(s->m_fDirectionX);fp(s->m_fDirectionY);fp(s->m_fDirectionZ);fp(s->m_fCameraPositionX);fp(s->m_fCameraPositionY);fp(s->m_fCameraPositionZ);num(s->m_bCameraShakeActive);num(s->m_bCameraFallsOffWithDistance);num(owning);}
void stat(CSteamStats*p,ESTATS type,int count){num(263);num(id(p));num(type);num(count);}
void sort(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b){num(269);num(p==&world->level);vec(a);vec(b);}
bool sphere(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,float radius,Ogre::Vector3&hit,Ogre::Vector3&normal,Ogre::Vector3&third,unsigned&type,Ogre::Vector3&extra,CBaseUnit**unit,bool flag){num(271);num(p==&world->level);vec(a);vec(b);fp(radius);num(flag);num(*unit==NULL);hit=Ogre::Vector3(b.x-.5f,b.y-1,b.z+.25f);normal=Ogre::Vector3::UNIT_Y;third=Ogre::Vector3::UNIT_Z;extra=Ogre::Vector3::ZERO;type=31;return variant&2;}
bool ray(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,Ogre::Vector3&hit,Ogre::Vector3&normal,unsigned&type,Ogre::Vector3&extra,bool flag){num(277);num(p==&world->level);vec(a);vec(b);num(flag);unsigned index=rays++;num(index);float height=self->m_vPosition.y-1.0f+float(index)*.25f;if(mode==15)height=self->m_vPosition.y-8;if(mode==17&&index==5)height=self->m_vPosition.y-4;hit=Ogre::Vector3(a.x,height,a.z);normal=Ogre::Vector3::UNIT_Y;extra=Ogre::Vector3::ZERO;type=17;return !(mode==13&&index==0)&&!(mode==14&&index==2)&&!(mode==16&&index==5);}
void treasure(CLevel*p,CCharacter*k,CCharacter*u,const Ogre::Vector3&position){num(281);num(p==&world->level);num(id(k));num(id(u));vec(position);}
void money(CLevel*p,CCharacter*k,CCharacter*u,const Ogre::Vector3&position,bool flag){num(283);num(p==&world->level);num(id(k));num(id(u));vec(position);num(flag);}
void spawnUnits(CResourceManager*p,CSpawnClass*s,unsigned count,const Ogre::Vector3&position,CLevel*l,CCharacter*owner,CCharacter*source,int level){num(293);num(p==&world->resources);num(id(s));num(count);vec(position);num(l==&world->level);num(id(owner));num(id(source));num(level);}
void blendName(CCharacter*p,const std::string&name,bool loop,float blend,float speed,float length){num(307);num(id(p));text(name);num(loop);fp(blend);fp(speed);fp(length);}
void blendIndex(CCharacter*p,int animation,bool loop,float blend,float speed,float length){num(311);num(id(p));num(animation);num(loop);fp(blend);fp(speed);fp(length);}
void queue(CCharacter*p,const std::string&name,bool loop,float blend,float speed){num(313);num(id(p));text(name);num(loop);fp(blend);fp(speed);}
float random(float a,float b){num(317);fp(a);fp(b);return variant%3==0?a:variant%3==1?b:a+(b-a)*.5f;}
unsigned randInt(int a,int b){num(331);num(a);num(b);return (a+b)/2;}
int setting(CDynamicPropertyFile*p,unsigned key){num(337);num(p==static_cast<CDynamicPropertyFile*>(services->master->m_pSettings));num(key);return mode==6?0:variant&1;}
void path(CPath*p){num(p!=NULL);if(!p)return;num(p->m_lPoints.size());fp(p->m_fPathLength);for(unsigned i=0;i<p->m_lPoints.size();++i){vec(p->m_lPoints[i]);fp(p->m_lRadiusLeft[i]);fp(p->m_lRadiusRight[i]);}}
void side(void*raw,autotest::Capture&capture,bool ours){Case c=*static_cast<Case*>(raw);seed=c.seed;mode=seed%32;variant=seed/32;rays=0;phase=1;oursSide=ours;armed=false;out=&capture;struct sigaction action;std::memset(&action,0,sizeof(action));action.sa_sigaction=&fault;action.sa_flags=SA_SIGINFO|SA_RESETHAND;sigemptyset(&action.sa_mask);sigaction(SIGSEGV,&action,NULL);sigaction(SIGABRT,&action,NULL);
 self=new Actor;killer=new CCharacter(NULL);master=new CCharacter(NULL);self->m_pResourceManager=&world->resources;self->m_pSceneNode=services->scene->getRootSceneNode()->createChildSceneNode();self->m_vPosition=Ogre::Vector3(1.25f+variant*.5f,2.5f,3.75f);self->m_vRight=Ogre::Vector3::UNIT_X;self->m_vUp=Ogre::Vector3::UNIT_Y;self->m_vForward=Ogre::Vector3::UNIT_Z;self->m_iUnitLevel=mode==0?0:7;self->m_eAIState=mode==1?AISTATE_DYING:mode==2?AISTATE_DEAD:static_cast<EAIState>(2);self->m_fHPFloat=variant%3==0?-3:variant%3==1?0:11;self->m_isPathing=variant&1;self->m_pathGraceTime=-3;self->m_pathDestination=Ogre::Vector3(-1,-2,-3);self->m_bBlocksPath=variant&2;self->m_bPathingFlag19C=true;self->m_attackTime=3;self->m_skillTime=4;self->m_skillLooping=true;self->m_champion=mode==8;self->m_spawnFlag704=variant&4;self->m_forcedHidden=false;self->m_bVisible=true;self->m_bInActiveRange=false;self->m_bInFadeRange=false;self->m_deathPathActive=variant&4;self->m_deathPathSilent=variant&8;self->m_deathPathDistance=17;self->m_deathPathSpeed=-2;self->m_fBaseUnitValue194=variant%2?.3f:.5f;self->m_targetCharacter.setObject(killer);
 if(variant&8){self->m_pMaster=master;master->m_Followers.push_back(self);master->m_followerFlags.push_back(true);}self->m_pUnitModel=new CGenericModel(NULL,services->scene,static_cast<OGRE_UTILITIES::EPRIMITIVES>(0));if(variant%3)self->m_deathPath=new CPath("existing",false,Ogre::Vector3::ZERO);if(self->m_deathPath)self->m_deathPath->AddPoint(Ogre::Vector3(-4,-5,-6),-1,1);if(variant%3)self->m_pSkillManager=new CSkillManager(NULL,self);if(mode!=22)self->m_pEffectManager=new CEffectManager(self);frozen=new CAffix(L"fixture");camera=new CCameraControl(NULL,NULL,NULL,NULL,NULL);stats=new CSteamStats;spawn=new CSpawnClass(L"fixture");self->m_merchantSpawnClass=variant&8?spawn:NULL;self->m_merchantMinimum=2;self->m_merchantMaximum=5;self->m_levelSound=variant&2?new CSoundBank(*services->master->m_pSoundManager,false):NULL;
 Ogre::Vector3 last(-7,-8,-9);std::memcpy(self->m_Padding210,&last,12);for(unsigned i=0;i<11;++i){particles[i]=new CParticle(NULL,L"fixture",&world->resources);particles[i]->m_bVisible=(i+variant)%2;self->m_equipmentParticles[i]=i==10&&mode==6?NULL:particles[i];}for(unsigned i=0;i<variant%4;++i){CCharacter::CParticleAnimationTrigger*t=new CCharacter::CParticleAnimationTrigger;t->m_particle=i%2?NULL:particles[i];t->m_stopOnDeath=(i+variant)%3!=0;t->m_resources=&world->resources;t->m_node=NULL;t->m_nodeOwner=NULL;self->m_particleTriggers.add(t);}
 detour::Set patches;
#define P(name,fn) TL_REDIRECT(patches,d##name,&fn)
 P(Theme,theme);P(Untheme,untheme);P(ISA,isa);P(IsPlayer,player);P(HP,hp);P(Modify,modify);P(Journal,journal);P(Procs,procs);P(Target,target);P(Mesh,mesh);P(Visible,visible);P(Align,align);P(State,state);P(Killed,killed);P(Quest,quest);P(Start,start);P(Stop,stop);P(Sound,sound);P(Effect,effect);P(Affix,affix);P(SkillsStop,skillsStop);P(SkillsFire,skillsFire);P(Exists,exists);P(Substring,substring);P(Find,find);P(Length,length);P(Clear,clear);P(Camera,getCamera);P(Shake,shake);P(Stat,stat);P(Sort,sort);P(Sphere,sphere);P(Ray,ray);P(Treasure,treasure);P(Money,money);P(Spawn,spawnUnits);P(BlendName,blendName);P(BlendIndex,blendIndex);P(Queue,queue);P(Random,random);P(RandInt,randInt);P(Setting,setting);
#undef P
 if(patches.failed())_exit(43);phase=100;armed=true;typedef void(*F)(CCharacter*,CCharacter*,const Ogre::Vector3*,float,bool);F fn=ours?dNew:dOld;if(!autotest::beginInvocation(capture,fn))return;Ogre::Vector3 direction(variant%2?.25f:0.0f,.125f,-.5f);fn(self,variant%4?killer:NULL,mode==9?NULL:&direction,mode==10?0:3.25f,mode==5||mode==6);capture.callCompleted=1;phase=101;if(ours&&c.control)self->m_pathGraceTime+=1;num(self->m_eAIState);num(self->m_bInActiveRange);num(self->m_bInFadeRange);num(self->m_isPathing);fp(self->m_pathGraceTime);vec(self->m_pathDestination);num(self->m_bPathingFlag19C);fp(self->m_attackTime);fp(self->m_skillTime);num(self->m_skillLooping);fp(self->m_fHPFloat);num(self->m_forcedHidden);num(self->m_bVisible);num(id(self->m_targetCharacter.getObject()));num(master->m_Followers.size());num(self->m_deathPathActive);num(self->m_deathPathSilent);fp(self->m_deathPathDistance);fp(self->m_deathPathSpeed);path(self->m_deathPath);armed=false;
}
void before(void*p,autotest::Capture&o){side(p,o,false);}void after(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(character_die_runtime){std::setlocale(LC_CTYPE,"C.UTF-8");initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;services=&native;menugui::Audio audio(native.master);finishlevel::Fixture level;world=&level;world->resources.m_pLevel=&world->level;world->resources.m_pSceneManager=native.scene;int failures=0;autotest::Coverage coverage("character_die_runtime",(uintptr_t)&dOld);for(unsigned i=0;i<1024;++i){Case c={i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);int pair=coverage.observe(host,a,b);TL_CHECK(failures,!pair);if(pair){host->log("    die seed%u status%d/%d bytes%lu/%lu\n",i,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned j=0;j+3<a.capture.length&&j+3<b.capture.length;j+=4){unsigned x,y;std::memcpy(&x,a.capture.data+j,4);std::memcpy(&y,b.capture.data+j,4);if(x!=y)host->log("    word%u %u/%u\n",j/4,x,y);}coverage.report(host);return failures;}}coverage.report(host);Case c={31,1};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);bool caught=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);TL_CHECK(failures,caught&&!autotest::incomplete(a)&&!autotest::incomplete(b)&&a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus);host->log("    die negative detected%u\n",unsigned(caught));return failures;}
