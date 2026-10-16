#include <cstring>
#include <stdint.h>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,soundObjOld0,(void*),"_ZN12CSoundObject4playEv")
TL_ORIGINAL(void,soundObjOld1,(void*,float),"_ZN12CSoundObject12updateSoundsEf")
TL_ORIGINAL(void,soundObjOld2,(void*,void*),"_ZN12CSoundObjectC1EP16CResourceManager")
extern "C" void soundObjNew0(void*) __asm__("_ZN12CSoundObject4playEv");
extern "C" void soundObjNew1(void*,float) __asm__("_ZN12CSoundObject12updateSoundsEf");
extern "C" void soundObjNew2(void*,void*) __asm__("_ZN12CSoundObjectC1EP16CResourceManager");
TL_FUNCTION(soundObjVisibleTarget,"_ZN16CSceneNodeObject10setVisibleEb")
TL_FUNCTION(soundObjPauseTarget,"_ZN12CSoundObject5pauseEv")
TL_FUNCTION(soundObjStopTarget,"_ZN10CSoundBank4stopEv")
TL_FUNCTION(soundObjRadiusTarget,"_ZN10CSoundBank9setRadiusEf")
TL_FUNCTION(soundObjPlayTarget,"_ZN10CSoundBank10playSampleEiPN4Ogre9SceneNodeEffb")
TL_FUNCTION(soundObjUpdateTarget,"_ZN10CSoundBank6updateEfPN4Ogre9SceneNodeE")
TL_FUNCTION(soundObjMasterTarget,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(soundObjBaseCtorTarget,"_ZN19CPositionableObjectC2EP16CResourceManagerPN4Ogre12SceneManagerE")
TL_FUNCTION(soundObjBankCtorTarget,"_ZN10CSoundBankC1ER13CSoundManagerb")
namespace {
struct Case{unsigned operation,index;};struct State{autotest::Capture* out;uint64_t* object;uint64_t bank[26],manager[3][224],master[2][64],resources[3],node;unsigned index,calls,singletons;};State* active;
void add(unsigned x){active->out->add(&x,4);}void real(float x){active->out->add(&x,4);}void invalid(){active->out->issue=autotest::Capture::InvalidReport;}
void event(unsigned x){++active->calls;add(x);}unsigned char& byte(void* p,unsigned at){return reinterpret_cast<unsigned char*>(p)[at];}
void* pointer(void* p,unsigned at){void* v;std::memcpy(&v,reinterpret_cast<char*>(p)+at,8);return v;}void setPointer(void* p,unsigned at,void* v){std::memcpy(reinterpret_cast<char*>(p)+at,&v,8);}void setFloat(void* p,unsigned at,float f){std::memcpy(reinterpret_cast<char*>(p)+at,&f,4);}unsigned managerID(void* p){for(unsigned i=0;i<3;++i)if(p==active->manager[i])return i;invalid();return 99;}
void receiver(void* p){if(p!=active->object)invalid();}void bank(void* p){if(p!=pointer(active->object,0x118))invalid();}
void visible(void* p,bool b){receiver(p);event(1);add(b);byte(p,0x81)=b;}
bool enabled(void* p){receiver(p);event(2);return byte(p,0x82);}
void broadcast(void* p,unsigned value){receiver(p);event(3);add(value);}
void stop(void* p){bank(p);event(4);unsigned n=0;std::memcpy(reinterpret_cast<char*>(p)+0x20,&n,4);}
void radius(void* p,float value){bank(p);event(5);real(value);setFloat(p,0xb0,value);byte(p,0xa8)=1;}
int play(void* p,int sample,void* node,float volume,float pitch,bool force){bank(p);event(6);add(sample);add(node==&active->node);add(node!=0);real(volume);real(pitch);add(force);return active->index&64?-1:3;}
void pause(void* p){receiver(p);event(7);byte(p,0x122)=1;}
void update(void* p,float elapsed,void* node){bank(p);event(8);real(elapsed);add(node==&active->node);add(node!=0);unsigned n=active->index&64?1:0;std::memcpy(reinterpret_cast<char*>(p)+0x20,&n,4);}
void* master(){event(9);unsigned which=active->singletons++?1:0;return active->master[which];}
void baseCtor(void* p,void* resource,void* scene){receiver(p);event(10);unsigned id=resource==0?3:99;for(unsigned i=0;i<3;++i)if(resource==&active->resources[i])id=i;add(id);if(id==99||scene)invalid();std::memset(p,0,0x100);}
void bankCtor(void* p,void* manager,bool is3D){event(11);add(managerID(manager));add(is3D);std::memset(p,0,0xd0);setPointer(p,0x10,manager);setFloat(p,0xb0,10.0f);}
void side(Case& c,bool ours,autotest::Capture& out){
 uint64_t object[0x128/8]={0};State state;std::memset(state.bank,0,sizeof(state.bank));std::memset(state.manager,0,sizeof(state.manager));std::memset(state.master,0,sizeof(state.master));state.out=&out;state.object=object;state.index=c.index;state.calls=state.singletons=0;active=&state;
 void* table[64]={0};table[0x30/8]=reinterpret_cast<void*>(&broadcast);table[0x48/8]=reinterpret_cast<void*>(&enabled);*reinterpret_cast<void***>(object)=table;
 for(unsigned i=0;i<3;++i){byte(state.manager[i],0x6a8)=(c.index & 4)!=0;byte(state.manager[i],0x6a9)=(c.index & 8)!=0;}
 setPointer(object,0x118,c.index&2?state.bank:0);setPointer(object,0x58,&state.node);setPointer(state.bank,0x10,state.manager[0]);byte(object,0x81)=(c.index & 16)!=0;byte(object,0x82)=(c.index & 16)!=0;byte(object,0x121)=(c.index & 128)!=0;byte(object,0x122)=(c.index & 32)!=0;byte(object,0x123)=(c.index & 1)!=0;byte(state.bank,0xc8)=(c.index & 64)!=0;byte(state.bank,0xa8)=0;setFloat(state.bank,0xb0,17.0f);
 setPointer(state.master[0],0x98,c.index&1?state.manager[0]:0);setPointer(state.master[1],0x98,state.manager[(c.index/2)%3]);
 detour::Set d;TL_REDIRECT(d,soundObjVisibleTarget,&visible);TL_REDIRECT(d,soundObjPauseTarget,&pause);TL_REDIRECT(d,soundObjStopTarget,&stop);TL_REDIRECT(d,soundObjRadiusTarget,&radius);TL_REDIRECT(d,soundObjPlayTarget,&play);TL_REDIRECT(d,soundObjUpdateTarget,&update);TL_REDIRECT(d,soundObjMasterTarget,&master);TL_REDIRECT(d,soundObjBaseCtorTarget,&baseCtor);TL_REDIRECT(d,soundObjBankCtorTarget,&bankCtor);if(d.failed()){invalid();return;}
 if(c.operation==0){typedef void(*Fn)(void*);Fn fn=ours?soundObjNew0:soundObjOld0;if(!autotest::beginInvocation(out,fn))return;fn(object);}
 else if(c.operation==1){typedef void(*Fn)(void*,float);Fn fn=ours?soundObjNew1:soundObjOld1;if(!autotest::beginInvocation(out,fn))return;fn(object,c.index&1?0.25f:-1.0f);}
 else{typedef void(*Fn)(void*,void*);Fn fn=ours?soundObjNew2:soundObjOld2;if(!autotest::beginInvocation(out,fn))return;unsigned resource=(c.index/6)%4;fn(object,resource==3?0:&state.resources[resource]);}
 out.callCompleted=1;add(state.calls);add(state.singletons);add(byte(object,0x81));add(byte(object,0x121));add(byte(object,0x122));add(byte(object,0x123));void* finalBank=pointer(object,0x118);add(finalBank!=0);if(finalBank){add(byte(finalBank,0xa8));out.add(reinterpret_cast<char*>(finalBank)+0xb0,4);add(managerID(pointer(finalBank,0x10)));}if(c.operation==2){out.add(reinterpret_cast<char*>(object)+0x108,16);out.add(reinterpret_cast<char*>(object)+0x94,12);add(byte(object,0x120));}
}
void before(void* p,autotest::Capture& o){side(*static_cast<Case*>(p),false,o);}void after(void* p,autotest::Capture& o){side(*static_cast<Case*>(p),true,o);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){autotest::Coverage cov(name,address);unsigned count=operation==2?24:256;for(unsigned i=0;i<count;++i){Case c={operation,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log(" soundobject operation%u case%u exits%d/%d issues%u/%u\n",operation,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return cov.completed==count?0:1;}
}
TL_TEST(state_soundobject_a07f10){return run(host,0,"state_soundobject_a07f10",reinterpret_cast<uintptr_t>(&soundObjOld0));}
TL_TEST(state_soundobject_a08090){return run(host,1,"state_soundobject_a08090",reinterpret_cast<uintptr_t>(&soundObjOld1));}
TL_TEST(state_soundobject_a08300){return run(host,2,"state_soundobject_a08300",reinterpret_cast<uintptr_t>(&soundObjOld2));}
