#include "tests/FinishLevelFixture.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "Skill.h"
#undef protected
#undef private
#include <limits>
TL_ORIGINAL(CCharacter*,cvOld,(CLevel*,const Ogre::Matrix4&,EAlignment,float,float,float,bool,CCharacter*,CSkill*),"_ZN6CLevel23findCharacterWithinViewERKN4Ogre7Matrix4E10EAlignmentfffbP10CCharacterP6CSkill")
extern "C" CCharacter*cvNew(CLevel*,const Ogre::Matrix4&,EAlignment,float,float,float,bool,CCharacter*,CSkill*) __asm__("_ZN6CLevel23findCharacterWithinViewERKN4Ogre7Matrix4E10EAlignmentfffbP10CCharacterP6CSkill");
TL_FUNCTION(cvAlive,"_ZN10CCharacter5aliveEv")
TL_FUNCTION(cvAlignment,"_ZN10CCharacter9alignmentEv")
TL_FUNCTION(cvNear,"_ZN10CCharacter14isPetNearDeathEv")
TL_FUNCTION(cvISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(cvTheme,"_ZN9CBaseUnit12hasUnitThemeERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(cvMaster,"_ZN6CSkill23getMasterOwnerCharacterEv")
TL_FUNCTION(cvValid,"_ZN6CSkill16getTargetIsValidEP10CCharacterS1_PKN4Ogre7Vector3Eb")
TL_FUNCTION(cvPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(cvSight,"_ZN6CLevel17sightUnobstructedERKN4Ogre7Vector3ES3_b")
namespace {
autotest::Capture*output;Ogre::SceneManager*scene;CLevel*level;CCharacter*actors[5];CSkill*skill;unsigned seed,mode,sightCalls;
void word(unsigned n){output->add(&n,4);}void vec(const Ogre::Vector3&v){output->add(&v,sizeof v);}
unsigned identity(const void*p){if(!p)return 0;for(unsigned i=0;i<5;++i)if(actors[i]==p)return i+1;if(p==level)return 6;if(p==skill)return 7;return 99;}
unsigned mix(unsigned i,unsigned salt){unsigned x=seed*747796405u+i*2891336453u+salt*277803737u;x=(x^(x>>16))*2246822519u;return x^(x>>13);}
struct Actor:CCharacter {explicit Actor(CResourceManager*r):CCharacter(r){}virtual bool getEnabled(){word(1);word(identity(this));word(m_bEnabled);return m_bEnabled;}};
bool alive(CCharacter*p){unsigned id=identity(p);word(2);word(id);bool v=mode==0||mix(id,1)%5!=0;word(v);return v;}
EAlignment alignment(CCharacter*p){unsigned id=identity(p);word(3);word(id);unsigned v=mode==0?1:mix(id,2)%7;word(v);return static_cast<EAlignment>(v);}
bool near(CCharacter*p){unsigned id=identity(p);word(4);word(id);bool v=mode!=0&&mix(id,3)%7==0;word(v);return v;}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES type){word(5);unsigned id=identity(p);word(id);word(type);bool v=mode!=0&&mix(id,4)%4==0;word(v);return v;}
bool theme(CBaseUnit*p,const std::wstring&s){word(6);unsigned id=identity(p);word(id);word(s.size());if(!s.empty())output->add(s.data(),s.size()*4);bool v=mix(id,5)%3!=0;word(v);return v;}
CCharacter*master(CSkill*p){word(7);word(identity(p));CCharacter*v=seed%11==0?NULL:actors[4];word(identity(v));return v;}
bool valid(CSkill*p,CCharacter*a,CCharacter*b,const Ogre::Vector3*position,bool flag){word(8);word(identity(p));unsigned id=identity(a);word(id);word(identity(b));word(position!=NULL);if(position)vec(*position);word(flag);bool v=mode==0||mix(id,6)%4!=0;word(v);return v;}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){word(9);word(identity(p));word(absolute);return p->m_vPosition;}
bool sight(CLevel*p,const Ogre::Vector3&a,const Ogre::Vector3&b,bool flag){word(10);word(p==level);vec(a);vec(b);word(flag);bool v=(seed+sightCalls++)%5!=0;word(v);return v;}
void execute(void*raw,autotest::Capture&out,bool ours){
 output=&out;seed=*static_cast<unsigned*>(raw);mode=seed/1024;sightCalls=0;
 for(unsigned i=0;i<2;++i){void*p=NULL;void*a=reinterpret_cast<void*>(0x14ee340+8*i);std::memcpy(&p,a,8);if(!p){if(i)new(a)std::wstring;else new(a)std::string;}}
 finishlevel::Fixture f;level=&f.level;f.resources.m_pSceneManager=scene;CMasterResourceManager::getSingleton()->m_pSceneManager=scene;
 for(unsigned i=0;i<5;++i)actors[i]=new Actor(&f.resources);skill=new CSkill(&f.resources,NULL);skill->m_targetsDead=(seed/7)&1;
 Ogre::Matrix4 transform=Ogre::Matrix4::IDENTITY;float phase=float(seed%13)*.25f,c=::cosf(phase),s=::sinf(phase);float sx=float(seed%3+1)*.5f,sz=float(seed%4+1)*.25f;
 transform[0][0]=c*sx;transform[0][2]=s*sz;transform[2][0]=-s*sx;transform[2][2]=c*sz;transform[1][1]=.5f+float(seed%5);transform[0][3]=float(int(seed%7)-3);transform[1][3]=float(int(seed%11)-5)*.25f;transform[2][3]=float(int(seed%13)-6)*.5f;if(seed&64){transform[3][0]=.03125f;transform[3][2]=-.0625f;}
 float nan=std::numeric_limits<float>::quiet_NaN();const Ogre::Vector3 points[]={Ogre::Vector3(0,0,0),Ogre::Vector3(0,99,1),Ogre::Vector3(1,-99,0),Ogre::Vector3(-1,7,1),Ogre::Vector3(1,9,-1),Ogre::Vector3(.5f,-1,1.5f),Ogre::Vector3(.01f,0,1.99f),Ogre::Vector3(0,3,9999),Ogre::Vector3(0,0,10000),Ogre::Vector3(nan,0,1)};
 for(unsigned i=0;i<5;++i){CCharacter*a=actors[i];a->m_vPosition=transform*points[(seed/3+i)%10];a->m_bEnabled=mode==0||mix(i,7)%7!=0;a->m_bVisible=mode==0||mix(i,8)%7!=0;a->m_bInActiveRange=mode==0||mix(i,9)%7!=0;a->m_damageShapeEnabled=mode==0||mix(i,10)%7!=0;unsigned states[]={0,1,41,42,5};a->m_eAIState=static_cast<EAIState>(mode==0?0:states[mix(i,11)%5]);}
 for(unsigned i=0;i<seed%9;++i)finishlevel::prepend(level->m_activeCharacters,actors[(i+seed/9)%5]);for(unsigned i=0;i<(seed/9)%8;++i)finishlevel::prepend(level->m_pCharacters,actors[(i+1)%5]);
 float inf=std::numeric_limits<float>::infinity();const float radii[]={-1,0,.5f,1,2,10,inf,nan},angles[]={-10,0,15,30,60,180,360,nan},ranges[]={-1,0,1,2,10,100,10001,inf,nan};
 detour::Set hooks;TL_REDIRECT(hooks,cvAlive,&alive);TL_REDIRECT(hooks,cvAlignment,&alignment);TL_REDIRECT(hooks,cvNear,&near);TL_REDIRECT(hooks,cvISA,&isa);TL_REDIRECT(hooks,cvTheme,&theme);TL_REDIRECT(hooks,cvMaster,&master);TL_REDIRECT(hooks,cvValid,&valid);TL_REDIRECT(hooks,cvPosition,&position);TL_REDIRECT(hooks,cvSight,&sight);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef CCharacter*(*Fn)(CLevel*,const Ogre::Matrix4&,EAlignment,float,float,float,bool,CCharacter*,CSkill*);Fn fn=ours?cvNew:cvOld;if(!autotest::beginInvocation(out,fn))return;
 CCharacter*result=fn(level,transform,static_cast<EAlignment>(mode==0?3:seed%8),radii[seed%8],angles[seed/8%8],ranges[seed/64%9],seed&1,seed%3?NULL:actors[seed/3%5],seed%4?skill:NULL);out.callCompleted=1;word(identity(result));word(sightCalls);
 std::vector<CCharacter*>ids;for(unsigned i=0;i<5;++i)ids.push_back(actors[i]);finishlevel::listState(out,level->m_activeCharacters,ids);finishlevel::listState(out,level->m_pCharacters,ids);for(unsigned i=0;i<5;++i){word(actors[i]->m_bEnabled);word(actors[i]->m_bVisible);word(actors[i]->m_bInActiveRange);word(actors[i]->m_damageShapeEnabled);word(actors[i]->m_eAIState);vec(actors[i]->m_vPosition);}
 delete skill;for(unsigned i=0;i<5;++i)delete actors[i];
}
void original(void*p,autotest::Capture&o){execute(p,o,false);}void candidate(void*p,autotest::Capture&o){execute(p,o,true);}
int run(const tlhybrid_host*host){nativegame::Services services;if(!services.ready())return 1;scene=services.scene;autotest::Coverage coverage("level_character_view",(uintptr_t)&cvOld);for(unsigned i=0;i<3072;++i){autotest::Outcome a,b;autotest::runChild(original,&i,a);autotest::runChild(candidate,&i,b);if(coverage.observe(host,a,b)){host->log("    character view seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);if(a.capture.length==b.capture.length){for(unsigned j=0;j<a.capture.length;++j)if(a.capture.data[j]!=b.capture.data[j]){host->log("    first different byte%u native%u candidate%u\n",j,a.capture.data[j],b.capture.data[j]);break;}}coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(level_character_view){return systems_fixture::isolated(&run,host);}
