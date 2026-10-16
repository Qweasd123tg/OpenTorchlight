#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <stdint.h>
#include <limits>
#include <OgreVector3.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,bankOld0,(void*,float),"_ZN10CSoundBank9setRadiusEf")
extern "C" void bankNew0(void*,float) __asm__("_ZN10CSoundBank9setRadiusEf");
TL_ORIGINAL(bool,bankOld1,(void*,int),"_ZN10CSoundBank11bankPlayingEi")
extern "C" bool bankNew1(void*,int) __asm__("_ZN10CSoundBank11bankPlayingEi");
TL_ORIGINAL(void,bankOld2,(void*,int,float,float),"_ZN10CSoundBank17queueGlobalSampleEiff")
extern "C" void bankNew2(void*,int,float,float) __asm__("_ZN10CSoundBank17queueGlobalSampleEiff");
TL_ORIGINAL(void,bankOld3,(void*),"_ZN10CSoundBank5pauseEv")
extern "C" void bankNew3(void*) __asm__("_ZN10CSoundBank5pauseEv");
TL_ORIGINAL(void,bankOld4,(void*),"_ZN10CSoundBank6resumeEv")
extern "C" void bankNew4(void*) __asm__("_ZN10CSoundBank6resumeEv");
TL_ORIGINAL(void,bankOld5,(void*,int),"_ZN10CSoundBank4stopEi")
extern "C" void bankNew5(void*,int) __asm__("_ZN10CSoundBank4stopEi");
TL_ORIGINAL(float,bankOld6,(void*,float,const Ogre::Vector3&),"_ZN10CSoundBank20configureVolumeScaleEfRKN4Ogre7Vector3E")
extern "C" float bankNew6(void*,float,const Ogre::Vector3&) __asm__("_ZN10CSoundBank20configureVolumeScaleEfRKN4Ogre7Vector3E");
TL_ORIGINAL(void,bankOld7,(void*),"_ZN10CSoundBank4stopEv")
extern "C" void bankNew7(void*) __asm__("_ZN10CSoundBank4stopEv");
TL_ORIGINAL(void,bankOld8,(void*),"_ZN10CSoundBank5clearEv")
extern "C" void bankNew8(void*) __asm__("_ZN10CSoundBank5clearEv");

#include "TArrayList.h"
TL_FUNCTION(bankStopTarget,"_ZN13CSoundManager9stopSoundEi")
TL_FUNCTION(bankPauseTarget,"_ZN13CSoundManager13setPauseSoundEib")
TL_FUNCTION(bankQueueTarget,"_ZN13CSoundManager10queueSoundEiP14CSoundInstanceff")
TL_FUNCTION(bankReleaseTarget,"_ZN13CSoundManager12releaseSoundEP14CSoundInstance")
TL_FUNCTION(bankRandomTarget,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
namespace {
struct Bank {
 uint64_t table,safe;void* manager;
 TArrayList<int> channels,ids;
 std::vector<std::vector<void*> > samples;
 std::vector<float> radii,volumes;std::vector<int> probabilities;
 bool dirty;float scale,radius;bool is3D;Ogre::Vector3 lastPosition;float lastVolume;bool loop;
};
struct Case{unsigned operation,index;};
struct State{autotest::Capture* out;void* manager;void* sounds[6];unsigned seed,calls;};State* active;
void scalar(unsigned v){active->out->add(&v,sizeof(v));}
void real(float v){active->out->add(&v,sizeof(v));}
void invalid(){active->out->issue=autotest::Capture::InvalidReport;}
unsigned sound(void* p){for(unsigned i=0;i<6;++i)if(p==active->sounds[i])return i;invalid();return 99;}
void event(void* manager,unsigned tag,int id){if(manager!=active->manager)invalid();++active->calls;scalar(tag);scalar(id);}
void stop(void* p,int id){event(p,1,id);}
void pause(void* p,int id,bool value){event(p,2,id);scalar(value);}
void queue(void* p,int id,void* instance,float volume,float pitch){event(p,3,id);scalar(sound(instance));real(volume);real(pitch);}
void release(void* p,void* instance){event(p,4,sound(instance));}
int random(int low,int high){++active->calls;scalar(5);scalar(low);scalar(high);if(high<low){invalid();return low;}int result=low+active->seed%static_cast<unsigned>(high-low+1);scalar(result);return result;}
void list(const TArrayList<int>& values){scalar(values.size());for(unsigned i=0;i<values.size();++i)scalar(values[i]);const unsigned* words=reinterpret_cast<const unsigned*>(reinterpret_cast<const char*>(&values)+8);scalar(words[1]);scalar(words[2]);}
void side(Case& c,bool ours,autotest::Capture& out){
 uint64_t manager[224]={0},nodes[6][16]={{0}};Bank b;State state;state.out=&out;state.manager=manager;state.seed=c.index%3==0?0:c.index%3==1?98:99;state.calls=0;active=&state;
 for(unsigned i=0;i<6;++i)state.sounds[i]=nodes[i];
 b.table=b.safe=0;b.manager=manager;b.dirty=c.index&1;b.scale=(c.index&2)?0.25f:-2.0f;b.radius=13.0f;b.is3D=c.index&4;b.lastPosition=Ogre::Vector3(3,7,-9);b.lastVolume=-17.0f;b.loop=c.index&8;
 reinterpret_cast<unsigned char*>(manager)[0x6a8]=(c.index&16)==0;reinterpret_cast<unsigned char*>(manager)[0x6a9]=(c.index&32)==0;
 float x=3.0f,z=-4.0f;std::memcpy(reinterpret_cast<char*>(manager)+0x20,&x,4);std::memcpy(reinterpret_cast<char*>(manager)+0x28,&z,4);
 unsigned count=c.index%4;for(unsigned i=0;i<count;++i){b.samples.push_back(std::vector<void*>());unsigned n=(c.index/4+i)%4;for(unsigned j=0;j<n;++j)b.samples.back().push_back(nodes[(i+j)%6]);b.radii.push_back(2.0f+i);b.volumes.push_back(0.125f*(i+1));b.probabilities.push_back(c.index%3==0?-1:c.index%3==1?50:100);}
 for(unsigned i=0;i<(c.index/3)%5;++i){b.channels.add(i==1?-1:static_cast<int>(i+10));b.ids.add(i%3);}
 detour::Set d;TL_REDIRECT(d,bankStopTarget,&stop);TL_REDIRECT(d,bankPauseTarget,&pause);TL_REDIRECT(d,bankQueueTarget,&queue);TL_REDIRECT(d,bankReleaseTarget,&release);TL_REDIRECT(d,bankRandomTarget,&random);if(d.failed()){invalid();return;}
 const int samples[]={-1,0,1,2,3,9};int sample=samples[(c.index/4)%6];float values[]={0.0f,1.0f,-2.0f,10.0f,20.0f,std::numeric_limits<float>::quiet_NaN()};float value=values[(c.index/6)%6];Ogre::Vector3 position((c.index&1)?3.0f:8.0f,1000.0f,(c.index&2)?-4.0f:9.0f);
 if(c.operation==6) {
  const float exceptional[]={std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity()};
  unsigned axisCase=c.index%9;
  if(axisCase==1)position.x=exceptional[c.index/9%3];
  if(axisCase==2)position.z=exceptional[c.index/9%3];
  if(axisCase==3){x=exceptional[c.index/9%3];std::memcpy(reinterpret_cast<char*>(manager)+0x20,&x,4);}
  if(axisCase==4){z=exceptional[c.index/9%3];std::memcpy(reinterpret_cast<char*>(manager)+0x28,&z,4);}
 }
 switch(c.operation){
 case 0:{typedef void(*Fn)(void*,float);Fn fn=ours?bankNew0:bankOld0;if(!autotest::beginInvocation(out,fn))return;fn(&b,value);break;}
 case 1:{typedef bool(*Fn)(void*,int);Fn fn=ours?bankNew1:bankOld1;if(!autotest::beginInvocation(out,fn))return;scalar(fn(&b,sample));break;}
 case 2:{typedef void(*Fn)(void*,int,float,float);Fn fn=ours?bankNew2:bankOld2;if(!autotest::beginInvocation(out,fn))return;fn(&b,sample,value,0.75f);break;}
 case 3:{typedef void(*Fn)(void*);Fn fn=ours?bankNew3:bankOld3;if(!autotest::beginInvocation(out,fn))return;fn(&b);break;}
 case 4:{typedef void(*Fn)(void*);Fn fn=ours?bankNew4:bankOld4;if(!autotest::beginInvocation(out,fn))return;fn(&b);break;}
 case 5:{typedef void(*Fn)(void*,int);Fn fn=ours?bankNew5:bankOld5;if(!autotest::beginInvocation(out,fn))return;fn(&b,sample);break;}
 case 6:{typedef float(*Fn)(void*,float,const Ogre::Vector3&);Fn fn=ours?bankNew6:bankOld6;if(!autotest::beginInvocation(out,fn))return;real(fn(&b,value,position));break;}
 case 7:{typedef void(*Fn)(void*);Fn fn=ours?bankNew7:bankOld7;if(!autotest::beginInvocation(out,fn))return;fn(&b);break;}
 default:{typedef void(*Fn)(void*);Fn fn=ours?bankNew8:bankOld8;if(!autotest::beginInvocation(out,fn))return;fn(&b);break;}
 }
 out.callCompleted=1;scalar(b.dirty);real(b.radius);real(b.lastVolume);scalar(state.calls);list(b.channels);list(b.ids);scalar(b.samples.size());for(unsigned i=0;i<b.samples.size();++i){scalar(b.samples[i].size());for(unsigned j=0;j<b.samples[i].size();++j)scalar(sound(b.samples[i][j]));}for(unsigned i=0;i<b.radii.size();++i)real(b.radii[i]);
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host* host,unsigned operation,const char* name,uintptr_t address){autotest::Coverage cov(name,address);for(unsigned i=0;i<72;++i){Case c={operation,i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log(" bank operation%u case%u exits%d/%d issues%u/%u\n",operation,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return cov.completed==72?0:1;}
}
TL_TEST(state_bank_a687d0){return run(host,0,"state_bank_a687d0",reinterpret_cast<uintptr_t>(&bankOld0));}
TL_TEST(state_bank_a68830){return run(host,1,"state_bank_a68830",reinterpret_cast<uintptr_t>(&bankOld1));}
TL_TEST(state_bank_a688a0){return run(host,2,"state_bank_a688a0",reinterpret_cast<uintptr_t>(&bankOld2));}
TL_TEST(state_bank_a68a20){return run(host,3,"state_bank_a68a20",reinterpret_cast<uintptr_t>(&bankOld3));}
TL_TEST(state_bank_a68a80){return run(host,4,"state_bank_a68a80",reinterpret_cast<uintptr_t>(&bankOld4));}
TL_TEST(state_bank_a68ae0){return run(host,5,"state_bank_a68ae0",reinterpret_cast<uintptr_t>(&bankOld5));}
TL_TEST(state_bank_a68b80){return run(host,6,"state_bank_a68b80",reinterpret_cast<uintptr_t>(&bankOld6));}
TL_TEST(state_bank_a68fd0){return run(host,7,"state_bank_a68fd0",reinterpret_cast<uintptr_t>(&bankOld7));}
TL_TEST(state_bank_a69070){return run(host,8,"state_bank_a69070",reinterpret_cast<uintptr_t>(&bankOld8));}
