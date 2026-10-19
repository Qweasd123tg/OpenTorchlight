#include "AutoTest.h"
#include <Ogre.h>
#include <limits>
#define private public
#define protected public
#include "Missile.h"
#include "Path.h"
#include "iMissile.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/FinishLevelFixture.h"
#include "tests/SmallMassCompare.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(bool,mhOldHit,(CMissile*,CBaseUnit*,Ogre::Vector3),"_ZN8CMissile20handleMissileHitUnitEP9CBaseUnitN4Ogre7Vector3E")
extern "C" bool mhNewHit(CMissile*,CBaseUnit*,Ogre::Vector3) __asm__("_ZN8CMissile20handleMissileHitUnitEP9CBaseUnitN4Ogre7Vector3E");
TL_ORIGINAL(bool,mhOldUpdate,(CMissile*,float),"_ZN8CMissile6updateEf")
extern "C" bool mhNewUpdate(CMissile*,float) __asm__("_ZN8CMissile6updateEf");
TL_ORIGINAL(void,mhCtor,(CMissile*,CResourceManager*),"_ZN8CMissileC1EP16CResourceManager")
TL_FUNCTION(mhISA,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(mhReflect,"_ZN10CCharacter26getDmgToReflectFromMissileEv")
TL_FUNCTION(mhDamage,"_ZN8CMissile19doDamageToCharacterEP10CCharacterRKN4Ogre7Vector3Eff")
TL_FUNCTION(mhAOE,"_ZN8CMissile11doAOEDamageEP9CBaseUnit")
TL_FUNCTION(mhKill,"_ZN8CMissile11killMissileEv")
TL_FUNCTION(mhDeath,"_ZN8CMissile20handleDeathOfMissileEf")
TL_FUNCTION(mhVelocity,"_ZN8CMissile24updatePositionByVelocityEf")
TL_FUNCTION(mhCollision,"_ZN8CMissile14checkCollisionEN4Ogre7Vector3ES1_RS1_S2_S2_PP9CBaseUnit")
TL_FUNCTION(mhEditor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(mhStart,"_ZN9CParticle5StartEv")
TL_FUNCTION(mhStop,"_ZN9CParticle4StopEb")
namespace {
nativegame::Services*services;autotest::Capture*output;bool armed;unsigned operation,seed,collisions;CMissile*missile;CCharacter*character;CItem*item;
void number(unsigned n){if(armed)output->add(&n,4);}void scalar(float n){if(armed)output->add(&n,4);}void vector(const Ogre::Vector3&v){scalar(v.x);scalar(v.y);scalar(v.z);}
unsigned id(CBaseUnit*p){return !p?0:p==character?1:p==item?2:99;}
float value(unsigned n){const float values[]={0,-0.0f,1e-10f,1,-2,3.25f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity()};return values[n%8];}
bool isa(CBaseUnit*p,UNITTYPES::EUNITTYPES t){number(1);number(id(p));number(t);return t==UNITTYPES::INTERACTABLE?(seed&8)!=0:p==item;}
float reflect(CCharacter*c){number(2);number(c==character);return value(seed/16);}
bool damage(CMissile*m,CCharacter*c,const Ogre::Vector3&direction,float scale,float soak){number(3);number(m==missile);number(id(c));vector(direction);scalar(scale);scalar(soak);return seed&32;}
void aoe(CMissile*m,CBaseUnit*excluded){number(4);number(m==missile);number(id(excluded));if(operation==1&&seed&512)m->m_bUnknown184=false;}
void kill(CMissile*m){number(5);number(m==missile);m->m_bUnknown184=true;}
bool death(CMissile*m,float elapsed){number(6);number(m==missile);scalar(elapsed);return seed&128;}
Ogre::Vector3 velocity(CMissile*m,float elapsed){number(7);number(m==missile);scalar(elapsed);vector(m->m_resetVector1A0);return m->getPosition(true)+Ogre::Vector3(.125f,-.25f,.5f);}
int collision(CMissile*m,Ogre::Vector3 start,Ogre::Vector3 end,Ogre::Vector3&position,Ogre::Vector3&normal,Ogre::Vector3&extra,CBaseUnit**unit){number(8);number(m==missile);vector(start);vector(end);number(&position==&end);number(*unit==NULL);number(++collisions);position=end+Ogre::Vector3(.25f,.5f,-.125f);normal=Ogre::Vector3(value(seed/3),value(seed/5),value(seed/7));extra=Ogre::Vector3(1,2,3);*unit=seed&256&&collisions<3?character:NULL;return seed&64;}
bool editor(CResourceManager*r){number(9);number(r==missile->m_pResourceManager);return seed&128;}
struct Particle:CParticle{unsigned id;Particle(CResourceManager*r,unsigned i):CParticle(NULL,L"fixture",r),id(i){}virtual void setOrientation(Ogre::Vector3&f,Ogre::Vector3&u){number(10);number(id);vector(f);vector(u);CParticle::setOrientation(f,u);vector(f);vector(u);}};
void start(CParticle*p){number(11);number(static_cast<Particle*>(p)->id);vector(p->getPosition(true));}
void stop(CParticle*p,bool immediate){number(12);number(static_cast<Particle*>(p)->id);number(immediate);}
struct Item:finishlevel::Item{explicit Item(CResourceManager*r):finishlevel::Item(r){}virtual bool interact(CCharacter*c){number(13);number(c==NULL);return seed&16;}};
struct Listener:iMissile{unsigned index;Listener(unsigned i):index(i){}virtual void missileBeingFired(CMissile*){}virtual void missileDieing(CMissile*){}virtual bool getCharacterCanBeHarmedByMissile(CMissile*m,CCharacter*c){number(14);number(index);number(m==missile);number(id(c));return !(seed&64)||index!=seed/128%3;}virtual bool missileApplyingEffects(CMissile*,CCharacter*,const Ogre::Vector3*,float,float){std::abort();return false;}virtual CPositionableObject*missileValidateTargetBeforeLaunch(CMissile*,CPositionableObject*p,Ogre::Vector3&){return p;}};
void side(smallmass::Case&c,bool ours,autotest::Capture&out){output=&out;armed=false;seed=c.index;collisions=0;finishlevel::Fixture f;f.resources.m_pSceneManager=services->scene;CMissile actual(&f.resources);missile=&actual;character=new CCharacter(NULL);item=new Item(NULL);actual.setPosition(Ogre::Vector3(1,2,3));actual.m_resetVector148=Ogre::Vector3(value(seed/3),value(seed/5),value(seed/7));actual.m_iUnknown1C4=7;actual.m_fUnknown1BC=seed%7;actual.m_fUnknown1C0=seed%5;actual.m_fUnknown290=.75f;actual.m_fSoakScale=seed*.125f;actual.m_target.setObject(character);actual.m_targetCharacter.setObject(character);actual.m_bUnknown294=false;
 Listener listeners[]={Listener(0),Listener(1),Listener(2)};if(operation==0)for(unsigned i=0;i<seed%4;++i)actual.m_Listeners.add(&listeners[i]);
 detour::Set hooks;if(operation==0){TL_REDIRECT(hooks,mhISA,&isa);TL_REDIRECT(hooks,mhReflect,&reflect);TL_REDIRECT(hooks,mhDamage,&damage);TL_REDIRECT(hooks,mhAOE,&aoe);}else{TL_REDIRECT(hooks,mhKill,&kill);TL_REDIRECT(hooks,mhDeath,&death);TL_REDIRECT(hooks,mhAOE,&aoe);TL_REDIRECT(hooks,mhVelocity,&velocity);TL_REDIRECT(hooks,mhCollision,&collision);TL_REDIRECT(hooks,mhEditor,&editor);TL_REDIRECT(hooks,mhStart,&start);TL_REDIRECT(hooks,mhStop,&stop);actual.m_bVisible=seed&1;actual.m_bEnabled=seed&512;actual.m_bUnknown185=seed&2;actual.m_bUnknown184=seed&4;actual.m_bTargetsPosition=seed&8;actual.m_bPiercing=seed&16;actual.m_fUnknown174=value(seed/8);actual.m_fUnknown16C=value(seed/11);actual.m_fUnknown198=value(seed/13);actual.m_fDistanceAllowedToTraveled=value(seed/17);actual.m_resetVector1A0=Ogre::Vector3(value(seed/3),value(seed/5),value(seed/7));if(seed&32)actual.m_particles[1]=new Particle(&f.resources,1);if(seed&64)actual.m_particles[2]=new Particle(&f.resources,2);}
 if(hooks.failed())std::abort();armed=true;
 if(!operation){CBaseUnit*unit=seed/4%3==0?NULL:seed/4%3==1?static_cast<CBaseUnit*>(character):item;typedef bool(*Fn)(CMissile*,CBaseUnit*,Ogre::Vector3);Fn fn=ours?mhNewHit:mhOldHit;if(!autotest::beginInvocation(out,fn))return;bool result=fn(missile,unit,Ogre::Vector3(value(seed/2),value(seed/3),value(seed/5)));out.callCompleted=1;number(result);}
 else{typedef bool(*Fn)(CMissile*,float);Fn fn=ours?mhNewUpdate:mhOldUpdate;if(!autotest::beginInvocation(out,fn))return;bool result=fn(missile,value(seed/7));out.callCompleted=1;number(result);}
 vector(actual.getPosition(true));vector(actual.m_resetVector148);vector(actual.m_resetVector1A0);scalar(actual.m_iUnknown1C4);scalar(actual.m_fUnknown1BC);scalar(actual.m_fUnknown1C0);scalar(actual.m_fUnknown174);scalar(actual.m_fUnknown290);number(actual.m_bUnknown294);number(actual.m_bUnknown184);number(actual.m_target.getObject()==character);number(actual.m_targetCharacter.getObject()==character);vector(actual.m_vForward);vector(actual.m_vRight);out.add(&actual.m_mOrientation,sizeof actual.m_mOrientation);for(unsigned i=1;i<3;++i)if(actual.m_particles[i]){vector(actual.m_particles[i]->getPosition(true));out.add(&actual.m_particles[i]->m_mOrientation,sizeof actual.m_mOrientation);}armed=false;hooks.restore();actual.m_Listeners.clear();actual.m_target.setObject(NULL);actual.m_targetCharacter.setObject(NULL);delete item;delete character;
}
int worker(const tlhybrid_host*host){finishlevel::initializeCharacterText();nativegame::Services native;if(!native.ready())return 1;services=&native;Ogre::SceneManager*old=native.master->m_pSceneManager;native.master->m_pSceneManager=native.scene;for(unsigned i=0;i<2;++i){void*p=NULL;void*a=reinterpret_cast<void*>(0x14a4320+8*i);std::memcpy(&p,a,8);if(!p){if(i)new(a)std::wstring;else new(a)std::string;}}int result=smallmass::run(host,operation,operation?"missile_update_native":"missile_hit_native",operation?0xd04120:0xd034c0,&side,1024);native.master->m_pSceneManager=old;return result;}
}
TL_TEST(missile_hit_native){operation=0;return systems_fixture::isolated(&worker,host);}
TL_TEST(missile_update_native){operation=1;return systems_fixture::isolated(&worker,host);}
