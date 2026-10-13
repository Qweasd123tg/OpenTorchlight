#include "SmallMassCompare.h"
TL_ORIGINAL(void, original0, (void*,void*), "_ZN10CCharacter9removePetEPS_")
extern "C" void candidate0(void*,void*) __asm__("_ZN10CCharacter9removePetEPS_");
TL_ORIGINAL(void, original1, (void*,bool), "_ZN10CCharacter13stopParticlesEb")
extern "C" void candidate1(void*,bool) __asm__("_ZN10CCharacter13stopParticlesEb");
TL_ORIGINAL(void, original2, (void*,int), "_ZN10CCharacter10setAIStateE8EAIState")
extern "C" void candidate2(void*,int) __asm__("_ZN10CCharacter10setAIStateE8EAIState");
TL_ORIGINAL(void, original3, (void*,void*), "_ZN10CCharacter17addToAvoidanceMapER6CLevel")
extern "C" void candidate3(void*,void*) __asm__("_ZN10CCharacter17addToAvoidanceMapER6CLevel");
TL_ORIGINAL(bool, original4, (void*,void*), "_ZN10CCharacter18inDamageReactRangeEPS_")
extern "C" bool candidate4(void*,void*) __asm__("_ZN10CCharacter18inDamageReactRangeEPS_");
TL_ORIGINAL(bool, original5, (void*), "_ZN10CCharacter18inInteractionRangeEv")
extern "C" bool candidate5(void*) __asm__("_ZN10CCharacter18inInteractionRangeEv");
TL_ORIGINAL(void, original6, (void*,void*), "_ZN10CCharacter13setTargetItemEP5CItem")
extern "C" void candidate6(void*,void*) __asm__("_ZN10CCharacter13setTargetItemEP5CItem");
TL_ORIGINAL(void, original7, (void*,float,bool), "_ZN10CCharacter8updateAIEfb")
extern "C" void candidate7(void*,float,bool) __asm__("_ZN10CCharacter8updateAIEfb");
TL_ORIGINAL(void, original8, (void*,void*), "_ZN10CCharacter9setMasterEPS_")
extern "C" void candidate8(void*,void*) __asm__("_ZN10CCharacter9setMasterEPS_");
TL_ORIGINAL(void, original9, (void*,const Ogre::Vector3&,const Ogre::Vector3&,float,bool,bool), "_ZN10CCharacter18playStrikeParticleERKN4Ogre7Vector3ES3_fbb")
extern "C" void candidate9(void*,const Ogre::Vector3&,const Ogre::Vector3&,float,bool,bool) __asm__("_ZN10CCharacter18playStrikeParticleERKN4Ogre7Vector3ES3_fbb");
TL_ORIGINAL(void, original10, (void*,void*), "_ZN10CCharacter12updateAttackER6CLevel")
extern "C" void candidate10(void*,void*) __asm__("_ZN10CCharacter12updateAttackER6CLevel");
TL_FUNCTION(dep_stop, "_ZN9CParticle4StopEb")
TL_FUNCTION(dep_start, "_ZN9CParticle5StartEv")
TL_FUNCTION(dep_baseMap, "_ZN9CBaseUnit17addToAvoidanceMapER6CLevel")
TL_FUNCTION(dep_position, "_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(dep_setPosition, "_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
TL_FUNCTION(dep_isa, "_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(dep_addSafe, "_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(dep_removeSafe, "_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(dep_target, "_ZN10CCharacter9setTargetEPS_")
TL_FUNCTION(dep_selectAttack, "_ZN10CCharacter12selectAttackE18EATTACK_RANGE_TYPE")
TL_FUNCTION(dep_animationAI, "_ZN10CCharacter15animationPlayAIEf")
TL_FUNCTION(dep_attack, "_ZN10CCharacter13performAttackEP10CEquipmentjff13EDAMAGE_TYPES")
extern "C" void* originalCharacterTable[] __asm__("_ZTV10CCharacter");
extern "C" void* originalMonsterTable[] __asm__("_ZTV8CMonster");
namespace {
using namespace smallmass;
void* self;void* other;void* path;void* model;void* level;unsigned calls;
void stop(void* p,bool immediate) { event(1,p);number(immediate);field<bool>(p,0x81)=false; }
void start(void* p) { event(2,p);field<bool>(p,0x81)=true; }
void baseMap(void* p,void* map) { event(3,p);pointer(map);field<bool>(p,0x19b)=true; }
void petMap(void* p,void* map) { event(4,p);pointer(map);field<bool>(p,0x19b)=true; }
bool enabled(void* p) { event(5,p);return input->index&4; }
void broadcast(void* p,unsigned id) { event(6,p);number(id); }
void follow(void* p,void* value) { event(7,p);pointer(value);field<void*>(p,0x750)=value; }
Ogre::Vector3 position(void* p,bool absolute) { event(8,p);number(absolute);return field<Ogre::Vector3>(p,0x84); }
void setPosition(void* p,const Ogre::Vector3& v) { event(9,p);vector(v);field<Ogre::Vector3>(p,0x84)=v; }
bool isa(void* p,int type) { event(10,p);number(type);return input->index&1; }
unsigned addSafe(void* p,void* reference) { event(11,p);pointer(reference);return 51+input->index; }
void removeSafe(void* p,void* reference,unsigned index) { event(12,p);pointer(reference);number(index); }
void target(void* p,void* value) { event(13,p);pointer(value);field<void*>(p,0x340)=value; }
void selectAttack(void* p,int type) { event(14,p);number(type); }
void state(void* p,int value) { event(15,p);number(value);field<int>(p,0x330)=value; }
void animationAI(void* p,float elapsed) { event(16,p);floating(elapsed); }
void attack(void* p,void* equipment,unsigned index,float damage,float effects,int type) { event(17,p);pointer(equipment);number(index);floating(damage);floating(effects);number(type);++calls;if(input->index%7==0)field<void*>(model,0x1b8)=field<void*>(model,0x1b0); }
void dispatch0(void* p,float elapsed,void* map) { event(30,p);floating(elapsed);pointer(map); }
void dispatch1(void* p,float elapsed,void* map) { event(31,p);floating(elapsed);pointer(map); }
void dispatch2(void* p,float elapsed) { event(32,p);floating(elapsed); }
void dispatch3(void* p,float elapsed,void* map) { event(33,p);floating(elapsed);pointer(map); }
void dispatch4(void* p,float elapsed) { event(34,p);floating(elapsed); }
void dispatch5(void* p,float elapsed,void* map) { event(35,p);floating(elapsed);pointer(map); }
void dispatch6(void* p,float elapsed,void* map) { event(36,p);floating(elapsed);pointer(map); }
void dispatch7(void* p,float elapsed) { event(37,p);floating(elapsed); }
void dispatch8(void* p,float elapsed,void* map) { event(38,p);floating(elapsed);pointer(map); }
void dispatch9(void* p,float elapsed,void* map) { event(39,p);floating(elapsed);pointer(map); }
void dispatch10(void* p,float elapsed,void* map) { event(40,p);floating(elapsed);pointer(map); }
void dispatch11(void* p,float elapsed,void* map,long long guid) { event(41,p);floating(elapsed);pointer(map);output->add(&guid,sizeof(guid)); }
void dispatch12(void* p,float elapsed,void* map) { event(42,p);floating(elapsed);pointer(map); }
void dispatch13(void* p,float elapsed,void* map) { event(43,p);floating(elapsed);pointer(map); }
void dispatch14(void* p,float elapsed,void* map) { event(44,p);floating(elapsed);pointer(map); }
void dispatch15(void* p,float elapsed,void* map) { event(45,p);floating(elapsed);pointer(map); }
void execute(Case& c,bool ours,autotest::Capture& out) {
 input=&c;output=&out;autotest::g_arenaUsed=0;calls=0;
 self=object(0x7f8);other=object(0x778);path=object(0x198);model=object(0x258);level=object(32);
 void** storage=static_cast<void**>(object(0x450));
 // Keep the real offset-to-top and RTTI so setAIState executes the original dynamic_cast.
 storage[0]=0;storage[1]=(c.index&1?originalMonsterTable:originalCharacterTable)[1];void** table=storage+2;
 table[0x48/8]=reinterpret_cast<void*>(&enabled);table[0x30/8]=reinterpret_cast<void*>(&broadcast);
 table[0x310/8]=reinterpret_cast<void*>(&follow);table[0x348/8]=reinterpret_cast<void*>(&state);table[0x270/8]=reinterpret_cast<void*>(&petMap);
 table[0x360/8]=reinterpret_cast<void*>(&dispatch0);
 table[0x368/8]=reinterpret_cast<void*>(&dispatch1);
 table[0x370/8]=reinterpret_cast<void*>(&dispatch2);
 table[0x378/8]=reinterpret_cast<void*>(&dispatch3);
 table[0x388/8]=reinterpret_cast<void*>(&dispatch4);
 table[0x390/8]=reinterpret_cast<void*>(&dispatch5);
 table[0x398/8]=reinterpret_cast<void*>(&dispatch6);
 table[0x3a0/8]=reinterpret_cast<void*>(&dispatch7);
 table[0x3a8/8]=reinterpret_cast<void*>(&dispatch8);
 table[0x3b0/8]=reinterpret_cast<void*>(&dispatch9);
 table[0x3b8/8]=reinterpret_cast<void*>(&dispatch10);
 table[0x3c0/8]=reinterpret_cast<void*>(&dispatch11);
 table[0x3c8/8]=reinterpret_cast<void*>(&dispatch12);
 table[0x3d0/8]=reinterpret_cast<void*>(&dispatch13);
 table[0x3d8/8]=reinterpret_cast<void*>(&dispatch14);
 table[0x3e0/8]=reinterpret_cast<void*>(&dispatch15);
 field<void*>(self,0)=table;field<void*>(other,0)=table;field<void*>(path,0)=table;
 field<void*>(self,0x750)=c.index%5==0?NULL:path;field<bool>(path,0x135)=c.index&2;field<bool>(path,0x136)=c.index&4;field<bool>(self,0x771)=c.index&8;
 const unsigned counts[]={0,1,2,7,63,64,65,66};unsigned count=(c.op==0||c.op==3)?counts[(c.index/4)%8]:4;
 void** followers=static_cast<void**>(object(70*8));
 for(unsigned i=0;i<70;++i){followers[i]=object((c.op==0||c.op==3)?0x778:16);field<void*>(followers[i],0)=table;}
 field<void*>(self,0x648)=followers;field<void*>(self,0x650)=followers+count;field<void*>(self,0x658)=followers+70;
 unsigned long* flags=static_cast<unsigned long*>(object(16));flags[0]=0xa5a5a5a5a5a5a5a5UL^(c.index*0x102010201020102UL);flags[1]=~flags[0];
 field<void*>(self,0x538)=flags;field<unsigned>(self,0x540)=0;field<void*>(self,0x548)=flags+count/64;field<unsigned>(self,0x550)=count%64;field<void*>(self,0x558)=flags+2;
 void* resources=object(0x60);field<void*>(resources,0x18)=c.index%7==0?NULL:level;field<void*>(self,0x68)=c.index%11==0?NULL:resources;
 field<bool>(self,0x81)=c.index&1;field<bool>(self,0x19b)=c.index&2;
 const int states[]={0,3,4,5,6,7,9,10,12,13,14,15,29,32,33,34,35,40,41,42,44,45,-1};int oldState=states[(c.index/3)%23];
 field<int>(self,0x330)=c.op==7?states[c.index%23]:oldState;
 field<int>(other,0x330)=c.index%3==0?5:c.index%3==1?6:0;field<bool>(other,0x199)=c.index&8;
 void* oldItem=object(0x230);field<void*>(self,0x340)=c.index%3?other:NULL;field<unsigned>(self,0x348)=17;
 field<void*>(self,0x350)=c.index%3==0?NULL:c.index%3==1?other:oldItem;field<unsigned>(self,0x358)=19;
 field<void*>(self,0x640)=c.index&1?other:NULL;field<bool>(self,0x52e)=c.index&2;field<float>(self,0x414)=0;
 field<int>(other,0x338)=(c.index/5)%5;field<int>(self,0x338)=3;
 const float ranges[]={0,0.5f,1.75f,2.95f,3.45f,7,15,30};float x=ranges[(c.index/2)%8];
 field<Ogre::Vector3>(self,0x84)=Ogre::Vector3(0,3,0);field<Ogre::Vector3>(other,0x84)=Ogre::Vector3(x,-8,c.index%5?0:2);
 if(c.index%19==0)field<float>(other,0x84)=bits(0x7fc01234);
 field<float>(self,0x194)=float(c.index%3)*0.25f;field<float>(other,0x194)=float(c.index%5)*0.25f;field<float>(self,0x374)=ranges[(c.index/7)%8];field<bool>(self,0x264)=c.index&16;
 void** triggerData=static_cast<void**>(object(4*8));void** particles=static_cast<void**>(object(8*8));
 for(unsigned i=0;i<8;++i){particles[i]=object(0x168);}
 if(c.index%13==0)particles[0]=NULL;list(self,0x4a8,particles,8,c.index%3==0?1:8);
 for(unsigned i=0;i<4;++i){triggerData[i]=object(0x60);field<bool>(triggerData[i],0x59)=(c.index+i)&1;field<bool>(triggerData[i],0x5a)=(c.index/3+i)&1;field<void*>(triggerData[i],0x18)=(c.index+i)%3==0?NULL:particles[i+1];}
 list(self,0x738,triggerData,c.index%5,c.index%3==0?1:4);
 void** keyData=static_cast<void**>(object(4*8));for(unsigned i=0;i<4;++i){keyData[i]=object(0x60);field<int>(keyData[i],0x58)=(c.index/3+i)%3;}
 field<void*>(model,0x1b0)=keyData;field<void*>(model,0x1b8)=keyData+c.index%5;field<void*>(model,0x1c0)=keyData+4;field<void*>(self,0x200)=model;
 field<void*>(self,0x390)=c.index%5==0?NULL:object(0x80);field<float>(self,0x378)=c.index%4==0?0:c.index%4==1?-1:c.index%4==2?1:bits(0x7fc01234);
 detour::Set patches;
 TL_REDIRECT(patches,dep_stop,&stop);
 TL_REDIRECT(patches,dep_start,&start);
 TL_REDIRECT(patches,dep_baseMap,&baseMap);
 TL_REDIRECT(patches,dep_position,&position);
 TL_REDIRECT(patches,dep_setPosition,&setPosition);
 TL_REDIRECT(patches,dep_isa,&isa);
 TL_REDIRECT(patches,dep_addSafe,&addSafe);
 TL_REDIRECT(patches,dep_removeSafe,&removeSafe);
 TL_REDIRECT(patches,dep_target,&target);
 TL_REDIRECT(patches,dep_selectAttack,&selectAttack);
 TL_REDIRECT(patches,dep_animationAI,&animationAI);
 TL_REDIRECT(patches,dep_attack,&attack);
 if(patches.failed())_exit(41);
 Ogre::Vector3 from(c.index%3?0:3,15,-2),to(c.index%5?7:3,-8,c.index%7?5:-2);
 switch(c.op) {
 case 0:autotest::invoke(out,ours?candidate0:original0,self,c.index%4==0?other:c.index%4==1?followers[0]:c.index%4==2?followers[count?count/2:0]:followers[count?count-1:0]);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self,bool(c.index&2));break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,int(c.index%7));break;
 case 3:autotest::invoke(out,ours?candidate3:original3,self,level);break;
 case 4:autotest::invoke(out,ours?candidate4:original4,self,other);break;
 case 5:autotest::invoke(out,ours?candidate5:original5,self);break;
 case 6:autotest::invoke(out,ours?candidate6:original6,self,c.index%3==0?NULL:c.index%3==1?other:oldItem);break;
 case 7:autotest::invoke(out,ours?candidate7:original7,self,0.125f,bool(c.index&1));break;
 case 8:autotest::invoke(out,ours?candidate8:original8,self,c.index%3==0?NULL:other);break;
 case 9:{void(*fn)(void*,const Ogre::Vector3&,const Ogre::Vector3&,float,bool,bool)=ours?candidate9:original9;if(!autotest::beginInvocation(out,fn))return;fn(self,from,to,float(int(c.index%9)-3)*0.5f,c.index&1,c.index&2);out.callCompleted=1;break;}
 case 10:autotest::invoke(out,ours?candidate10:original10,self,level);break;
 }
 number(calls);out.add(autotest::g_arena,autotest::g_arenaUsed);
}
}
TL_TEST(restore69_80ec70) { return smallmass::run(host,0,"restore69_80ec70",(uint64_t)(uintptr_t)original0,execute,128); }
TL_TEST(restore69_80f2e0) { return smallmass::run(host,1,"restore69_80f2e0",(uint64_t)(uintptr_t)original1,execute,96); }
TL_TEST(restore69_80f710) { return smallmass::run(host,2,"restore69_80f710",(uint64_t)(uintptr_t)original2,execute,128); }
TL_TEST(restore69_822ce0) { return smallmass::run(host,3,"restore69_822ce0",(uint64_t)(uintptr_t)original3,execute,128); }
TL_TEST(restore69_823ee0) { return smallmass::run(host,4,"restore69_823ee0",(uint64_t)(uintptr_t)original4,execute,128); }
TL_TEST(restore69_8244a0) { return smallmass::run(host,5,"restore69_8244a0",(uint64_t)(uintptr_t)original5,execute,128); }
TL_TEST(restore69_824920) { return smallmass::run(host,6,"restore69_824920",(uint64_t)(uintptr_t)original6,execute,128); }
TL_TEST(restore69_825d40) { return smallmass::run(host,7,"restore69_825d40",(uint64_t)(uintptr_t)original7,execute,184); }
TL_TEST(restore69_825fa0) { return smallmass::run(host,8,"restore69_825fa0",(uint64_t)(uintptr_t)original8,execute,128); }
TL_TEST(restore69_827720) { return smallmass::run(host,9,"restore69_827720",(uint64_t)(uintptr_t)original9,execute,128); }
TL_TEST(restore69_848790) { return smallmass::run(host,10,"restore69_848790",(uint64_t)(uintptr_t)original10,execute,128); }
