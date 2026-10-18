#include <string>
#include <vector>
#include <map>
#include <new>
#include <OgreSceneManager.h>
#define private public
#define protected public
#include "Character.h"
#include "BaseUnit.h"
#include "AstarPathfinder.h"
#include "Level.h"
#include "SpawnClass.h"
#include "Path.h"
#include "WeaponTrail.h"
#undef protected
#undef private
#include "AutoTest.h"
#include "tests/Detour.h"
TL_ORIGINAL(void,oldCharacterDisplayPath,(CCharacter*),"_ZN10CCharacter11displayPathEv")
extern "C" void newCharacterDisplayPath(CCharacter*) __asm__("_ZN10CCharacter11displayPathEv");
TL_ORIGINAL(void,oldCharacterPathfinder,(CCharacter*,CLevel&),"_ZN10CCharacter16createPathfinderER6CLevel")
extern "C" void newCharacterPathfinder(CCharacter*,CLevel&) __asm__("_ZN10CCharacter16createPathfinderER6CLevel");
TL_FUNCTION(cpaths_trailCtor,"_ZN12CWeaponTrailC1EPN4Ogre12SceneManagerERKSsif")
TL_FUNCTION(cpaths_trailActive,"_ZN12CWeaponTrail9setActiveEb")
TL_FUNCTION(cpaths_trailMaterial,"_ZN12CWeaponTrail15setMaterialNameERKSs")
TL_FUNCTION(cpaths_trailUpdate,"_ZN12CWeaponTrail6updateEfPN4Ogre7Vector3ES2_bP16CSceneNodeObject")
TL_FUNCTION(cpaths_unique,"_ZN7STRINGS10uniqueNameERKSs")
TL_FUNCTION(cpaths_position,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(cpaths_point,"_ZN5CPath8GetPointEj")
TL_FUNCTION(cpaths_leftX,"_ZN6CLevel8topLeftXEv")
TL_FUNCTION(cpaths_leftY,"_ZN6CLevel8topLeftYEv")
TL_FUNCTION(cpaths_roll,"_ZN11CSpawnClass14rollSpawnClassER10TArrayListIP10CDataGroupEPS0_IbEP10CCharacterS8_ijiiii")
TL_FUNCTION(cpaths_unit,"_ZN16CResourceManager10createUnitEP10CDataGroupibb")
TL_FUNCTION(cpaths_rng,"_ZN9UTILITIES21randomBetweenVolatileEff")
TL_FUNCTION(cpaths_spawnPosition,"_ZN6CLevel23randomOpenPositionRangeERKN4Ogre7Vector3Effb")
TL_FUNCTION(cpaths_addCharacter,"_ZN6CLevel12addCharacterEP10CCharacterRKN4Ogre7Vector3Eb")
TL_FUNCTION(cpaths_addPet,"_ZN10CCharacter6addPetEPS_")
namespace {
struct Case{unsigned mode,index;};struct State{Case c;autotest::Capture*out;CCharacter*self;CLevel*level;CResourceManager*resources;Ogre::SceneManager*scene;CBaseUnit*units[4];CDataGroup*data[4];CWeaponTrail*trail;unsigned created;};State*active;
unsigned hash(unsigned n){unsigned v=active->c.index*2654435761u+n*2246822519u;v^=v>>16;v*=3266489917u;return v^(v>>13);}void num(unsigned v){active->out->add(&v,4);}void fp(float v){active->out->add(&v,4);}void vec(const Ogre::Vector3&v){fp(v.x);fp(v.y);fp(v.z);}void text(const std::string&v){num(v.size());active->out->add(v.data(),v.size());}unsigned id(const void*p){if(!p)return 0;if(p==active->self)return 1;for(unsigned i=0;i<4;++i){if(p==active->units[i])return 10+i;if(p==active->data[i])return 20+i;}return 99;}
void trailCtor(CWeaponTrail*p,Ogre::SceneManager*s,const std::string&name,int count,float duration){num(1);num(s==active->scene);text(name);num(count);fp(duration);active->trail=p;}
void trailActive(CWeaponTrail*,bool v){num(2);num(v);}void trailMaterial(CWeaponTrail*,const std::string&v){num(3);text(v);}
void trailUpdate(CWeaponTrail*,float dt,Ogre::Vector3*p,Ogre::Vector3*down,bool flag,CSceneNodeObject*owner){num(4);fp(dt);vec(*p);vec(*down);num(flag);num(id(owner));}
std::string unique(const std::string&prefix){num(5);text(prefix);return prefix+"17";}
Ogre::Vector3 position(CPositionableObject*p,bool absolute){num(6);num(id(p));num(absolute);return p->m_vPosition;}
Ogre::Vector3 point(CPath*p,unsigned i){num(7);num(i);return p->m_lPoints[i];}
float leftX(CLevel*p){num(8);return p->m_topLeftX;}float leftY(CLevel*p){num(9);return p->m_topLeftY;}
int roll(CSpawnClass*,TArrayList<CDataGroup*>&list,TArrayList<bool>*flags,CCharacter*a,CCharacter*b,int level,unsigned unique,int x,int y,int z,int q){num(10);num(flags!=NULL);num(id(a));num(id(b));num(level);num(unique);num(x);num(y);num(z);num(q);for(unsigned i=0;i<hash(10)%5;++i)list.add(active->data[i]);return 0;}
CBaseUnit*unit(CResourceManager*r,CDataGroup*d,int depth,bool a,bool b){num(11);num(r==active->resources);num(id(d));num(depth);num(a);num(b);return active->units[active->created++];}
float rng(float lo,float hi){num(12);fp(lo);fp(hi);return float(hash(12+active->created)%9)*45;}
void direction(CPositionableObject*p,Ogre::Vector3 v){num(13);num(id(p));vec(v);p->m_vForward=v;}
Ogre::Vector3 spawnPosition(CLevel*,const Ogre::Vector3&p,float low,float high,bool flag){num(14);vec(p);fp(low);fp(high);num(flag);return p+Ogre::Vector3(1,2,3);}
void addCharacter(CLevel*,CCharacter*p,const Ogre::Vector3&v,bool flag){num(15);num(id(p));vec(v);num(flag);}
void addPet(CCharacter*,CCharacter*p){num(16);num(id(p));}
void side(Case&c,bool ours,autotest::Capture&out){autotest::g_arenaUsed=0;State s;active=&s;s.c=c;s.out=&out;s.created=0;s.trail=NULL;
 s.self=static_cast<CCharacter*>(autotest::allocate(sizeof(CCharacter)));s.resources=static_cast<CResourceManager*>(autotest::allocate(sizeof(CResourceManager)));s.scene=static_cast<Ogre::SceneManager*>(autotest::allocate(sizeof(Ogre::SceneManager)));s.resources->m_pSceneManager=s.scene;s.self->m_pResourceManager=c.mode==0&&hash(1)%4==0?NULL:s.resources;s.self->m_vPosition=Ogre::Vector3(3,4.5f,-7);
 if(c.mode==0){CPath*path=static_cast<CPath*>(autotest::allocate(sizeof(CPath)));new(&path->m_lPoints)std::vector<Ogre::Vector3>;for(unsigned i=0;i<c.index%17;++i)path->m_lPoints.push_back(Ogre::Vector3(float(i),-9,-float(i)*.5f));s.self->m_movementPath=path;CWeaponTrail*initial=hash(2)%2?static_cast<CWeaponTrail*>(autotest::allocate(sizeof(CWeaponTrail))):NULL;s.self->m_weaponTrails[3]=initial;autotest::invoke(out,ours?newCharacterDisplayPath:oldCharacterDisplayPath,s.self);num(s.self->m_weaponTrails[3]==(initial?initial:s.trail));num(path->m_lPoints.size());for(unsigned i=0;i<path->m_lPoints.size();++i)vec(path->m_lPoints[i]);path->m_lPoints.~vector();if(s.trail)Ogre::NedAllocImpl::deallocBytes(s.trail);}
 else {s.level=static_cast<CLevel*>(autotest::allocate(sizeof(CLevel)));s.level->m_topLeftX=-12.5f;s.level->m_topLeftY=7.25f;s.level->m_passWidth=2+hash(3)%8;s.level->m_passHeight=3+hash(4)%8;s.level->m_dungeonDepth=int(hash(5)%7)-3;s.level->m_mapPassability=NULL;s.level->m_objectPassability=NULL;
 s.self->m_pathfinder=hash(6)%2?new CAstarPathfinder(1,2,3,4,NULL,NULL,.2f):NULL;s.self->m_isPathing=c.index&1;s.self->m_pathGraceTime=.5f;s.self->m_savedPathIterations=-13;s.self->m_pendingPetSpawn=hash(7)%3?static_cast<CSpawnClass*>(autotest::allocate(sizeof(CSpawnClass))):NULL;
 for(unsigned i=0;i<4;++i){s.data[i]=static_cast<CDataGroup*>(autotest::allocate(sizeof(CDataGroup)));bool character=(hash(8+i)&1)!=0;s.units[i]=static_cast<CBaseUnit*>(autotest::allocate(character?sizeof(CCharacter):sizeof(CBaseUnit)));void**table=static_cast<void**>(autotest::allocate(0x510));std::memcpy(table,reinterpret_cast<void*>(character?0xfcdd60:0xfc8fc0),0x510);table[2+0x120/8]=reinterpret_cast<void*>(&direction);*reinterpret_cast<void***>(s.units[i])=table+2;}
 typedef void(*F)(CCharacter*,CLevel&);F f=ours?newCharacterPathfinder:oldCharacterPathfinder;if(!autotest::beginInvocation(out,f))return;f(s.self,*s.level);out.callCompleted=1;
 CAstarPathfinder*p=s.self->m_pathfinder;fp(p->m_fOriginX);fp(p->m_fOriginY);num(p->m_iWidth);num(p->m_iHeight);fp(p->m_fTileSize);num(p->m_iTileCount);num(p->m_pTiles==NULL);num(p->m_pOccupiedTiles==NULL);num(p->m_iMaxIterations);num(s.self->m_savedPathIterations);num(s.self->m_isPathing);fp(s.self->m_pathGraceTime);vec(s.self->m_pathDestination);num(s.self->m_pendingPetSpawn!=NULL);num(s.created);delete p;
 }
}
void before(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void after(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t address){detour::Set hooks;TL_REDIRECT(hooks,cpaths_trailCtor,&trailCtor);TL_REDIRECT(hooks,cpaths_trailActive,&trailActive);TL_REDIRECT(hooks,cpaths_trailMaterial,&trailMaterial);TL_REDIRECT(hooks,cpaths_trailUpdate,&trailUpdate);TL_REDIRECT(hooks,cpaths_unique,&unique);TL_REDIRECT(hooks,cpaths_position,&position);TL_REDIRECT(hooks,cpaths_point,&point);TL_REDIRECT(hooks,cpaths_leftX,&leftX);TL_REDIRECT(hooks,cpaths_leftY,&leftY);TL_REDIRECT(hooks,cpaths_roll,&roll);TL_REDIRECT(hooks,cpaths_unit,&unit);TL_REDIRECT(hooks,cpaths_rng,&rng);TL_REDIRECT(hooks,cpaths_spawnPosition,&spawnPosition);TL_REDIRECT(hooks,cpaths_addCharacter,&addCharacter);TL_REDIRECT(hooks,cpaths_addPet,&addPet);if(hooks.failed())return 1;autotest::Coverage coverage(name,address);for(unsigned i=0;i<1024;++i){Case c={mode,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(coverage.observe(host,a,b)){host->log("    character path mode%u seed%u exits%d/%d bytes%lu/%lu\n",mode,i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);unsigned k=0;while(k*4<a.capture.length&&k*4<b.capture.length){unsigned x,y;std::memcpy(&x,a.capture.data+k*4,4);std::memcpy(&y,b.capture.data+k*4,4);if(x!=y){host->log("    first word%u %08x/%08x\n",k,x,y);break;}++k;}coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=1024||coverage.different||coverage.missing;}
}
TL_TEST(all_character_display_path){return run(host,0,"all_character_display_path",0x82a940);}
TL_TEST(all_character_create_pathfinder){return run(host,1,"all_character_create_pathfinder",0x832260);}
