#include "AutoTest.h"
#include <Ogre.h>
#include <limits>
#define private public
#define protected public
#include "Missile.h"
#include "Path.h"
#include "Graph.h"
#include "iMissile.h"
#undef protected
#undef private
#include "tests/NativeMenuClient.h"
#include "tests/FinishLevelFixture.h"
#include "tests/SystemsFixtureWorker.h"
#define DECL(N,A,S) TL_ORIGINAL(void,mdOld##N,A,S) extern "C" void mdNew##N A __asm__(S);
DECL(AOE,(CMissile*,CBaseUnit*),"_ZN8CMissile11doAOEDamageEP9CBaseUnit")
DECL(Launch,(CMissile*,const Ogre::Vector3&,const Ogre::Vector3&),"_ZN8CMissile26calculateLaunchOrientationERKN4Ogre7Vector3ES3_")
#undef DECL
TL_ORIGINAL(bool,mdOldDamage,(CMissile*,CCharacter*,const Ogre::Vector3&,float,float),"_ZN8CMissile19doDamageToCharacterEP10CCharacterRKN4Ogre7Vector3Eff")
extern "C" bool mdNewDamage(CMissile*,CCharacter*,const Ogre::Vector3&,float,float) __asm__("_ZN8CMissile19doDamageToCharacterEP10CCharacterRKN4Ogre7Vector3Eff");
TL_ORIGINAL(void,mdCtor,(CMissile*,CResourceManager*),"_ZN8CMissileC1EP16CResourceManager")
TL_ORIGINAL(void,mdDtor,(CMissile*),"_ZN8CMissileD1Ev")
TL_FUNCTION(mdQuery,"_ZN6CLevel24getActiveUnitsAtPositionERKN4Ogre7Vector3EfR10TArrayListIP10CCharacterERS4_IP5CItemE")
TL_FUNCTION(mdRay,"_ZN6CLevel12rayCollisionERKN4Ogre7Vector3ES3_RS1_S4_RjS4_b")
TL_FUNCTION(mdGraph,"_ZN16CResourceManager14getGraphDamageEv")
TL_FUNCTION(mdRandom,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(mdApply,"_ZN10CCharacter11applyDamageER6CLevelRKN4Ogre7Vector3EfS5_fPS_bbbbj")
namespace {
nativegame::Services*services;CGameClient*client;CGraph*graph;autotest::Capture*output;bool armed;unsigned operation,seed;CMissile*missile;CLevel*level;CCharacter*characters[3];CItem*items[3];
void number(unsigned n){if(armed)output->add(&n,4);}
void scalar(float n){if(armed)output->add(&n,4);}
void vector(const Ogre::Vector3&v){scalar(v.x);scalar(v.y);scalar(v.z);}
unsigned id(CBaseUnit*p){if(!p)return 0;for(unsigned i=0;i<3;++i){if(p==characters[i])return i+1;if(p==items[i])return i+4;}return 99;}
struct Item:finishlevel::Item {unsigned index;Item(CResourceManager*r,unsigned i):finishlevel::Item(r),index(i){}virtual bool interact(CCharacter*c){number(5);number(index);number(c==NULL);if(seed&64)missile->m_owner.setObject(characters[0]);return index&1;}};
void query(CLevel*p,const Ogre::Vector3&position,float radius,TArrayList<CCharacter*>&cs,TArrayList<CItem*>&is){number(1);number(p==level);vector(position);scalar(radius);number(cs.size());number(is.size());unsigned count=seed/8%5;for(unsigned i=0;i<count;++i){cs.add(characters[(i+seed/32)%3]);is.add(items[(i+seed/16)%3]);}}
bool aoeDamage(CMissile*m,CCharacter*c,const Ogre::Vector3&direction,float damage,float soak){number(2);number(m==missile);number(id(c));vector(direction);scalar(damage);scalar(soak);if(seed&128){m->m_fAOEDamageScale+=.5f;m->m_fSoakScale-=.25f;m->m_owner.setObject(items[1]);}return false;}
bool ray(CLevel*p,const Ogre::Vector3&top,const Ogre::Vector3&bottom,Ogre::Vector3&hit,Ogre::Vector3&normal,unsigned&type,Ogre::Vector3&extra,bool flag){number(3);number(p==level);vector(top);vector(bottom);vector(hit);number(flag);if(seed&16)hit=Ogre::Vector3(seed*.125f,-3.25f,7.75f);normal=Ogre::Vector3::UNIT_Y;type=seed;extra=Ogre::Vector3::ZERO;return seed&32;}
CGraph*getGraph(CResourceManager*r){number(6);number(r==missile->m_pResourceManager);return graph;}
float random(float low,float high){number(7);scalar(low);scalar(high);return (low+high)*.375f;}
void apply(CCharacter*c,CLevel&l,const Ogre::Vector3&position,float damage,const Ogre::Vector3&direction,float force,CCharacter*source,bool a,bool b,bool d,bool e,unsigned flags){number(8);number(id(c));number(&l==level);vector(position);scalar(damage);vector(direction);scalar(force);number(id(source));number(a);number(b);number(d);number(e);number(flags);}
struct Listener:iMissile {
 unsigned index;Listener(unsigned i):index(i){}virtual void missileBeingFired(CMissile*){}virtual void missileDieing(CMissile*){}
 virtual bool getCharacterCanBeHarmedByMissile(CMissile*m,CCharacter*c){number(9);number(index);number(m==missile);number(id(c));if((seed&128)&&index==0)m->m_fUnknown290+=.25f;return !(seed&8)||index!=(seed/16%3);}
 virtual bool missileApplyingEffects(CMissile*m,CCharacter*c,const Ogre::Vector3*v,float damage,float effect){number(10);number(index);number(m==missile);number(id(c));vector(*v);scalar(damage);scalar(effect);if(seed&64){m->m_fUnknown290+=.25f;if(c)c->m_iUnitLevel+=2;}return (seed&16)&&index==(seed/32%3);}
 virtual CPositionableObject*missileValidateTargetBeforeLaunch(CMissile*,CPositionableObject*p,Ogre::Vector3&){return p;}
};
float value(unsigned n){const float v[]={0,-0.0f,1e-10f,1,-2,3.25f,1e8f,-1e8f};return v[n%8];}
struct Missile:CMissile {explicit Missile(CResourceManager*r):CMissile(r){}virtual void setOrientation(Ogre::Vector3&forward,Ogre::Vector3&up){number(4);vector(forward);vector(up);CPositionableObject::setOrientation(forward,up);vector(forward);vector(up);}};
void caseSide(smallmass::Case&c,bool ours,autotest::Capture&out){
 output=&out;armed=false;seed=c.index;finishlevel::Fixture f;level=&f.level;f.resources.m_pSceneManager=services->scene;
 if(operation==1&&seed&1)f.resources.m_GameClients.add(client);
 Missile actual(&f.resources);missile=&actual;
 for(unsigned i=0;i<3;++i){characters[i]=new CCharacter(NULL);characters[i]->setPosition(Ogre::Vector3(i*.5f,seed%3,i-1.25f));items[i]=new Item(NULL,i);characters[i]->m_iUnitLevel=i*5+seed%17;}
 actual.setPosition(Ogre::Vector3(value(seed),value(seed/3),value(seed/5)));actual.m_pSceneNode->setPosition(Ogre::Vector3(1.25f,-3,7));
 actual.m_fAOEDamageScale=seed*.25f;actual.m_fSoakScale=seed*.125f;actual.m_fUnknown290=seed%7*.3f;actual.m_fInherentMinDMGPercent=seed*.01f;actual.m_fInherentMaxDMGPercent=seed*.05f;actual.m_fInherentKnockback=seed*.125f;
 Listener listeners[]={Listener(0),Listener(1),Listener(2)};if(operation==2)for(unsigned i=0;i<seed%4;++i)actual.m_Listeners.add(&listeners[i]);
 detour::Set hooks;
 if(operation==0){TL_REDIRECT(hooks,mdQuery,&query);hooks.redirect(reinterpret_cast<char*>(mdOldDamage),reinterpret_cast<char*>(mdNewDamage),&aoeDamage);actual.m_fAOERadius=seed%8==0?0:seed%8==1?-1:seed%8==2?std::numeric_limits<float>::quiet_NaN():float(seed%9);if(seed&1)actual.m_owner.setObject(seed&2?static_cast<CBaseUnit*>(characters[0]):items[0]);}
 if(operation==1){TL_REDIRECT(hooks,mdRay,&ray);actual.m_fMissileArchHeight=seed%8==0?0:seed%8==1?-2:seed%8==2?std::numeric_limits<float>::quiet_NaN():float(seed%11);actual.m_fUnknown218=123;if(seed&2){actual.m_pPath=new CPath("prior",false,Ogre::Vector3(1,2,3));actual.m_pPath->AddPoint(Ogre::Vector3(4,5,6),1,2);}}
 if(operation==2){TL_REDIRECT(hooks,mdGraph,&getGraph);TL_REDIRECT(hooks,mdRandom,&random);TL_REDIRECT(hooks,mdApply,&apply);}
 if(hooks.failed())std::abort();armed=true;
 if(operation==0){typedef void(*Fn)(CMissile*,CBaseUnit*);Fn fn=ours?mdNewAOE:mdOldAOE;CBaseUnit*excluded=seed&4?(seed&2?static_cast<CBaseUnit*>(characters[1]):items[1]):NULL;if(!autotest::beginInvocation(out,fn))return;fn(missile,excluded);fn(missile,excluded);out.callCompleted=1;scalar(actual.m_fAOEDamageScale);scalar(actual.m_fSoakScale);number(id(actual.m_owner.getObject()));}
 if(operation==1){Ogre::Vector3 from(value(seed/2),value(seed/5),value(seed/7)),to(value(seed/3),value(seed/11),value(seed/13));const Ogre::Vector3&start=seed&64?actual.m_targetPosition:from;const Ogre::Vector3&end=seed&128?actual.m_targetPosition:to;actual.m_targetPosition=Ogre::Vector3(-.5f,6.25f,3.75f);typedef void(*Fn)(CMissile*,const Ogre::Vector3&,const Ogre::Vector3&);Fn fn=ours?mdNewLaunch:mdOldLaunch;if(!autotest::beginInvocation(out,fn))return;fn(missile,start,end);out.callCompleted=1;vector(actual.m_targetPosition);scalar(actual.m_fUnknown198);scalar(actual.m_fUnknown218);out.add(&actual.m_mOrientation,sizeof actual.m_mOrientation);number(actual.m_pPath!=NULL);if(actual.m_pPath){CPath&p=*actual.m_pPath;number(p.m_lPoints.size());for(unsigned i=0;i<p.m_lPoints.size();++i){vector(p.m_lPoints[i]);scalar(p.m_lRadiusLeft[i]);scalar(p.m_lRadiusRight[i]);}number(p.m_lPointDistance.size());for(unsigned i=0;i<p.m_lPointDistance.size();++i)scalar(p.m_lPointDistance[i]);number(p.m_lSegmentAngle.size());for(unsigned i=0;i<p.m_lSegmentAngle.size();++i)scalar(p.m_lSegmentAngle[i]);scalar(p.m_fPathLength);}}
 if(operation==2){CCharacter*target=characters[seed/4%3];Ogre::Vector3 direction(value(seed/5),value(seed/7),value(seed/11));typedef bool(*Fn)(CMissile*,CCharacter*,const Ogre::Vector3&,float,float);Fn fn=ours?mdNewDamage:mdOldDamage;if(!autotest::beginInvocation(out,fn))return;bool result=fn(missile,target,direction,seed*.375f,seed*.625f);out.callCompleted=1;number(result);scalar(actual.m_fUnknown290);number(target->m_iUnitLevel);}
 armed=false;hooks.restore();actual.m_Listeners.clear();actual.m_owner.setObject(NULL);for(unsigned i=0;i<3;++i){delete items[i];delete characters[i];}
}
int worker(const tlhybrid_host*host){finishlevel::initializeCharacterText();nativegame::Services native;if(!native.ready())return 1;services=&native;Ogre::SceneManager*previous=native.master->m_pSceneManager;native.master->m_pSceneManager=native.scene;for(unsigned i=0;i<2;++i){void*p=NULL;void*a=reinterpret_cast<void*>(0x14a4320+8*i);std::memcpy(&p,a,8);if(!p){if(i)new(a)std::wstring;else new(a)std::string;}}
 int result;
 if(operation==1){menugui::Audio audio(native.master);menugui::Client actualClient(*native.settings,native.master,*native.master->m_pSoundManager);client=actualClient.client;result=smallmass::run(host,operation,"missile_launch_native",0xd01090,&caseSide,512);}
 else if(operation==2){graph=new CGraph(GRAPH_LINEAR,L"missile-fixture",1);graph->addValue(0,1,0);graph->addValue(100,201,0);graph->processPoints();result=smallmass::run(host,operation,"missile_damage_native",0xcf9620,&caseSide,512);delete graph;}
 else result=smallmass::run(host,operation,"missile_aoe_native",0xd00c20,&caseSide,512);
 native.master->m_pSceneManager=previous;return result;}
}
TL_TEST(missile_aoe_native){operation=0;return systems_fixture::isolated(&worker,host);}
TL_TEST(missile_launch_native){operation=1;return systems_fixture::isolated(&worker,host);}
TL_TEST(missile_damage_native){operation=2;return systems_fixture::isolated(&worker,host);}
