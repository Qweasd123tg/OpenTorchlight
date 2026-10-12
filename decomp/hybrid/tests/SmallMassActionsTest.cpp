#include "SmallMassCompare.h"
#include "LinuxUtils.h"
#include <OgrePlane.h>
#include <OgreCamera.h>
TL_ORIGINAL(bool, original0, (void*,void*,void*), "_ZN10CCharacter12facingTargetEPS_P5CItem")
extern "C" bool candidate0(void*,void*,void*) __asm__("_ZN10CCharacter12facingTargetEPS_P5CItem");
TL_ORIGINAL(void, original1, (void*,float), "_ZN10CCharacter16teleportToMasterEf")
extern "C" void candidate1(void*,float) __asm__("_ZN10CCharacter16teleportToMasterEf");
TL_ORIGINAL(bool, original2, (void*,const Ogre::Vector3&,bool,bool), "_ZN10CCharacter14moveToPositionERKN4Ogre7Vector3Ebb")
extern "C" bool candidate2(void*,const Ogre::Vector3&,bool,bool) __asm__("_ZN10CCharacter14moveToPositionERKN4Ogre7Vector3Ebb");
TL_ORIGINAL(void, original3, (void*,void*), "_ZN10CCharacter9setTargetEPS_")
extern "C" void candidate3(void*,void*) __asm__("_ZN10CCharacter9setTargetEPS_");
TL_ORIGINAL(void, original4, (void*,const Ogre::Vector3&,const Ogre::Vector3&,float), "_ZN10CCharacter15playHitParticleERKN4Ogre7Vector3ES3_f")
extern "C" void candidate4(void*,const Ogre::Vector3&,const Ogre::Vector3&,float) __asm__("_ZN10CCharacter15playHitParticleERKN4Ogre7Vector3ES3_f");
TL_ORIGINAL(void, original5, (void*,void*,bool), "_ZN8CMonster8unitInitEP10CDataGroupb")
extern "C" void candidate5(void*,void*,bool) __asm__("_ZN8CMonster8unitInitEP10CDataGroupb");
TL_ORIGINAL(void, original6, (void*,float,void*), "_ZN8CMonster8fidgetAIEfR6CLevel")
extern "C" void candidate6(void*,float,void*) __asm__("_ZN8CMonster8fidgetAIEfR6CLevel");
TL_ORIGINAL(int, original7, (void*,int), "_ZN10CCharacter13damageDefenseE13EDAMAGE_TYPES")
extern "C" int candidate7(void*,int) __asm__("_ZN10CCharacter13damageDefenseE13EDAMAGE_TYPES");
TL_ORIGINAL(Ogre::Vector3, original8, (void*,POINT,Ogre::Plane), "_ZN16CObjectControl3D23getMousePlaneInstersectE5POINTN4Ogre5PlaneE")
extern "C" Ogre::Vector3 candidate8(void*,POINT,Ogre::Plane) __asm__("_ZN16CObjectControl3D23getMousePlaneInstersectE5POINTN4Ogre5PlaneE");
TL_ORIGINAL(Ogre::Vector3, original9, (void*,Ogre::Plane), "_ZN16CObjectControl3D23getCameraPlaneIntersectEN4Ogre5PlaneE")
extern "C" Ogre::Vector3 candidate9(void*,Ogre::Plane) __asm__("_ZN16CObjectControl3D23getCameraPlaneIntersectEN4Ogre5PlaneE");
TL_FUNCTION(dep_position, "_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(dep_setPosition, "_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(dep_randomOpen, "_ZN6CLevel18randomOpenPositionERKN4Ogre7Vector3Efb")
TL_FUNCTION(dep_passable, "_ZN6CLevel15passableBetweenEN4Ogre7Vector3ERKS1_b")
TL_FUNCTION(dep_ground, "_ZN10CCharacter12dropToGroundER6CLevelfb")
TL_FUNCTION(dep_aiFlag, "_ZN10CAIManager9hasAIFlagE13EAIFLAG_TYPES")
TL_FUNCTION(dep_addSafe, "_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(dep_removeSafe, "_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(dep_isPlayer, "_ZN9CBaseUnit8isPlayerEv")
TL_FUNCTION(dep_alert, "_ZN9CBaseUnit16broadcastAlertedEv")
TL_FUNCTION(dep_master, "_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(dep_getInt, "_ZN20CDynamicPropertyFile6GetIntEj")
TL_FUNCTION(dep_particleStart, "_ZN9CParticle5StartEv")
TL_FUNCTION(dep_unitInit, "_ZN10CCharacter8unitInitEP10CDataGroupb")
TL_FUNCTION(dep_getFloat, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEf")
TL_FUNCTION(dep_playing, "_ZNK13CGenericModel25animationPlayingSubstringERKSs")
TL_FUNCTION(dep_isa, "_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(dep_blend, "_ZN10CCharacter14blendAnimationERKSsbfff")
TL_FUNCTION(dep_effect, "_ZN10CInventory14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(dep_editor, "_ZN7CEditor12getSingletonEv")
TL_FUNCTION(dep_camera, "_ZN7CEditor9getCameraEv")
TL_FUNCTION(dep_mouse, "_ZN13CMouseHandler13MousePositionEv")
TL_FUNCTION(dep_screenRay, "_ZN4MATH16screenToWorldRayEPN4Ogre6CameraEffff")
extern "C" char dep_cameraPosition[] __asm__("_ZNK4Ogre6Camera11getPositionEv");

namespace {
using namespace smallmass;
void* self;void* other;void* masterObject;void* model;void* model2;void* level;void* settings;void* masterManager;void* editorObject;void* cameraObject;
unsigned positionCalls,passCalls,modelCalls,propertyCalls,cameraCalls;
Ogre::Vector3 cameraPositionValue,forwardValue;
Ogre::Vector3 initialPosition(void* p) {
 const float values[]={0,0.5f,7.999f,8,8.001f,16,-16};float x=values[(input->index/4)%7];
 if(p==self)return Ogre::Vector3(input->index%5==0?x:0,3,-2);
 return Ogre::Vector3(x,-9,input->index%5==0?-2:3);
}
Ogre::Vector3 position(void* p,bool absolute) { event(1,p);number(absolute);++positionCalls;Ogre::Vector3 v=initialPosition(p);if(input->index%11==0&&positionCalls==3)v.z+=2;return v; }
void setPosition(void* p,const Ogre::Vector3& v) { event(2,p);vector(v);field<Ogre::Vector3>(p,0x84)=v; }
void removeMap(void* p,void* map) { event(3,p);pointer(map);field<bool>(p,0x19b)=false; }
void addMap(void* p,void* map) { event(4,p);pointer(map);field<bool>(p,0x19b)=true; }
Ogre::Vector3 randomOpen(void* p,const Ogre::Vector3& v,float radius,bool flag) { event(5,p);vector(v);floating(radius);number(flag);return v+Ogre::Vector3(0.5f,1,-0.25f); }
bool passable(void* p,Ogre::Vector3 a,const Ogre::Vector3& b,bool flag) { event(6,p);vector(a);vector(b);number(flag);++passCalls;return input->index%3==0||input->index%3==1&&passCalls==2; }
void ground(void* p,void* map,float height,bool force) { event(7,p);pointer(map);floating(height);number(force);field<bool>(p,0x1f4)=force; }
const Ogre::Vector3& forward(void* p) { event(8,p);return forwardValue; }
bool aiFlag(void* p,int flag) { event(9,p);number(flag);return input->index&4; }
unsigned addSafe(void* p,void* reference) { event(10,p);pointer(reference);return input->index+91; }
void removeSafe(void* p,void* reference,unsigned index) { event(11,p);pointer(reference);number(index); }
bool isPlayer(void* p) { event(12,p);return input->index&8; }
void alert(void* p) { event(13,p); }
void* master() { number(14);return masterManager; }
int getInt(void* p,unsigned id) { event(15,p);number(id);++propertyCalls;return input->op==4?int(input->index%3):320+int(propertyCalls)*80; }
void particleStart(void* p) { event(16,p); }
void unitInit(void* p,void* data,bool flag) { event(17,p);pointer(data);number(flag);field<bool>(p,0x1d0)=flag; }
float getFloat(void* p,const std::wstring& name,float fallback) { event(18,p);text(name);floating(fallback);return float(int(input->index%17)-8)*0.125f; }
void* getModel(void* p) { event(19,p);++modelCalls;return input->index%3==0?NULL:modelCalls==1?model:model2; }
bool playing(void* p,const std::string& name) { event(20,p);text(name);return input->index&1; }
bool isa(void* p,int type) { event(21,p);number(type);return input->index&16; }
void blend(void* p,const std::string& name,bool loop,float fade,float speed,float end) { event(22,p);text(name);number(loop);floating(fade);floating(speed);floating(end); }
void state(void* p,int value) { event(23,p);number(value);field<int>(p,0x330)=value; }
float effect(void* p,int type,int damage) { event(24,p);number(type);number(damage);const float values[]={0,0.5f,-0.5f,2.1f,-2.1f,100,-150};return values[(input->index+type+damage)%7]; }
void* editor() { number(25);return editorObject; }
void* camera(void* p) { event(26,p);return input->index%5==0?NULL:cameraObject; }
POINT mouse(void* p) { event(27,p);POINT point={91,-17};return point; }
Ogre::Vector3 screenRay(void* p,float x,float y,float w,float h) { event(28,p);floating(x);floating(y);floating(w);floating(h);return Ogre::Vector3(input->index%3==0?0:0.25f,input->index%3==1?0:-1,0.125f); }
const Ogre::Vector3& cameraPosition(void* p) { event(29,p);++cameraCalls;cameraPositionValue=Ogre::Vector3(2,10+cameraCalls,3);return cameraPositionValue; }
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;positionCalls=passCalls=modelCalls=propertyCalls=cameraCalls=0;
 self=object(0x1000);other=object(0x778);masterObject=object(0x778);model=object(0x258);model2=object(0x258);level=object(16);
 settings=object(16);masterManager=object(0x190);field<void*>(masterManager,0x90)=settings;
 editorObject=object(0x198);field<void*>(editorObject,0x50)=settings;cameraObject=object(32);
 field<void*>(self,0x18)=object(32);field<void*>(self,0x68)=object(0x28);field<void*>(field<void*>(self,0x68),0x18)=level;
 field<void*>(self,0x200)=model;field<void*>(self,0x640)=c.index%7==0?NULL:masterObject;
 field<bool>(self,0x19b)=c.index&1;field<int>(self,0x330)=c.index%5==0?6:c.index%5==1?5:2;
 field<bool>(self,0x70c)=c.index%4==0;field<bool>(self,0x1d0)=c.index&2;
 field<void*>(self,0x340)=c.index%3==0?NULL:other;field<unsigned>(self,0x348)=27;
 field<void*>(self,0x350)=c.index%3==2?masterObject:NULL;field<unsigned>(self,0x358)=31;
 field<int>(other,0x330)=c.index%3==0?5:c.index%3==1?6:2;
 field<void*>(self,0x718)=c.index%5==0?NULL:object(16);
 field<void*>(self,0x490)=c.index%7==0?NULL:object(16);field<int>(self,0x430)=int(c.index%19)-3;
 for(unsigned i=0;i<8;++i)field<int>(self,0x620+i*4)=int((c.index*3+i*17)%200)-25;
 forwardValue=Ogre::Vector3(c.index%3==0?0:1,0,c.index%3==1?0:1);field<Ogre::Vector3>(self,0xb4)=forwardValue;
 field<float>(self,0x76c)=c.index%13==0?bits(0x7fc01234):float(c.index%8)*60;
 void** particles=static_cast<void**>(object(24));for(unsigned i=0;i<3;++i)particles[i]=(c.index+i)%4==0?NULL:object(0x168);list(self,0x4a8,particles,3,c.index%4==0?1:3);
 void** table=static_cast<void**>(object(0x420));table[0x130/8]=reinterpret_cast<void*>(&forward);table[0x1e0/8]=reinterpret_cast<void*>(&getModel);table[0x268/8]=reinterpret_cast<void*>(&removeMap);table[0x270/8]=reinterpret_cast<void*>(&addMap);table[0x348/8]=reinterpret_cast<void*>(&state);field<void*>(self,0)=table;
 detour::Set patches;
 TL_REDIRECT(patches,dep_position,&position);
 TL_REDIRECT(patches,dep_setPosition,&setPosition);
 TL_REDIRECT(patches,dep_randomOpen,&randomOpen);
 TL_REDIRECT(patches,dep_passable,&passable);
 TL_REDIRECT(patches,dep_ground,&ground);
 TL_REDIRECT(patches,dep_aiFlag,&aiFlag);
 TL_REDIRECT(patches,dep_addSafe,&addSafe);
 TL_REDIRECT(patches,dep_removeSafe,&removeSafe);
 TL_REDIRECT(patches,dep_isPlayer,&isPlayer);
 TL_REDIRECT(patches,dep_alert,&alert);
 TL_REDIRECT(patches,dep_master,&master);
 TL_REDIRECT(patches,dep_getInt,&getInt);
 TL_REDIRECT(patches,dep_particleStart,&particleStart);
 TL_REDIRECT(patches,dep_unitInit,&unitInit);
 TL_REDIRECT(patches,dep_getFloat,&getFloat);
 TL_REDIRECT(patches,dep_playing,&playing);
 TL_REDIRECT(patches,dep_isa,&isa);
 TL_REDIRECT(patches,dep_blend,&blend);
 TL_REDIRECT(patches,dep_effect,&effect);
 TL_REDIRECT(patches,dep_editor,&editor);
 TL_REDIRECT(patches,dep_camera,&camera);
 TL_REDIRECT(patches,dep_mouse,&mouse);
 TL_REDIRECT(patches,dep_screenRay,&screenRay);

 patches.redirect(dep_cameraPosition,dep_cameraPosition,&cameraPosition);if(patches.failed())_exit(41);
 Ogre::Vector3 from(c.index%2?0:2,15,-2),to(c.index%3?7:2,-3,c.index%5?9:-2);float distance=float(int(c.index%9)-2)*0.5f;
 switch(c.op) {
 case 0:autotest::invoke(out,ours?candidate0:original0,self,c.index%3==0?NULL:other,c.index%4==0?NULL:masterObject);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,distance);break;
 case 2:{bool(*fn)(void*,const Ogre::Vector3&,bool,bool)=ours?candidate2:original2;if(!autotest::beginInvocation(out,fn))return;number(fn(self,to,c.index&2,c.index&4));out.callCompleted=1;break;}
 case 3:autotest::invoke(out,ours?candidate3:original3,self,c.index%3==0?NULL:c.index%3==1?other:masterObject);break;
 case 4:{void(*fn)(void*,const Ogre::Vector3&,const Ogre::Vector3&,float)=ours?candidate4:original4;if(!autotest::beginInvocation(out,fn))return;fn(self,from,to,distance);out.callCompleted=1;break;}
 case 5:autotest::invoke(out,ours?candidate5:original5,self,other,bool(c.index&1));break;
 case 6:autotest::invoke(out,ours?candidate6:original6,self,0.125f,level);break;
 case 7:autotest::invoke(out,ours?candidate7:original7,self,int(c.index%6));break;
 case 8:{POINT point={long(c.index)*13-300,long(c.index)*7-600};Ogre::Plane plane(Ogre::Vector3(0,1,0),float(int(c.index%15)-7));Ogre::Vector3(*fn)(void*,POINT,Ogre::Plane)=ours?candidate8:original8;if(!autotest::beginInvocation(out,fn))return;vector(fn(self,point,plane));out.callCompleted=1;break;}
 case 9:{Ogre::Plane plane(Ogre::Vector3(0,1,0),float(int(c.index%15)-7));Ogre::Vector3(*fn)(void*,Ogre::Plane)=ours?candidate9:original9;if(!autotest::beginInvocation(out,fn))return;vector(fn(self,plane));out.callCompleted=1;break;}
 }
 number(positionCalls);number(passCalls);number(modelCalls);number(propertyCalls);number(cameraCalls);out.add(autotest::g_arena,autotest::g_arenaUsed);
}
}
TL_TEST(smallmass2_action_facing) { return smallmass::run(host,0,"smallmass2_action_facing",(uint64_t)(uintptr_t)original0,execute); }
TL_TEST(smallmass2_action_teleport) { return smallmass::run(host,1,"smallmass2_action_teleport",(uint64_t)(uintptr_t)original1,execute); }
TL_TEST(smallmass2_action_move) { return smallmass::run(host,2,"smallmass2_action_move",(uint64_t)(uintptr_t)original2,execute); }
TL_TEST(smallmass2_action_target) { return smallmass::run(host,3,"smallmass2_action_target",(uint64_t)(uintptr_t)original3,execute); }
TL_TEST(smallmass2_action_hit) { return smallmass::run(host,4,"smallmass2_action_hit",(uint64_t)(uintptr_t)original4,execute); }
TL_TEST(smallmass2_action_monster_init) { return smallmass::run(host,5,"smallmass2_action_monster_init",(uint64_t)(uintptr_t)original5,execute); }
TL_TEST(smallmass2_action_fidget) { return smallmass::run(host,6,"smallmass2_action_fidget",(uint64_t)(uintptr_t)original6,execute); }
TL_TEST(smallmass2_action_defense) { return smallmass::run(host,7,"smallmass2_action_defense",(uint64_t)(uintptr_t)original7,execute); }
TL_TEST(smallmass2_action_mouse_plane) { return smallmass::run(host,8,"smallmass2_action_mouse_plane",(uint64_t)(uintptr_t)original8,execute); }
TL_TEST(smallmass2_action_camera_plane) { return smallmass::run(host,9,"smallmass2_action_camera_plane",(uint64_t)(uintptr_t)original9,execute); }
