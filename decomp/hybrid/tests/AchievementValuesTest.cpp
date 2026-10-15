#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "Achievement.h"
TL_ORIGINAL(void, old_set_float, (void*, float), "_ZN12CAchievement8setValueEf")
extern "C" void new_set_float(void*, float) __asm__("_ZN12CAchievement8setValueEf");
TL_ORIGINAL(void, old_set_int, (void*, int), "_ZN12CAchievement8setValueEi")
extern "C" void new_set_int(void*, int) __asm__("_ZN12CAchievement8setValueEi");
TL_ORIGINAL(void, old_cheat, (void*), "_ZN12CAchievement5cheatEv")
extern "C" void new_cheat(void*) __asm__("_ZN12CAchievement5cheatEv");
TL_ORIGINAL(void, old_force, (void*), "_ZN12CAchievement13forceCompleteEv")
extern "C" void new_force(void*) __asm__("_ZN12CAchievement13forceCompleteEv");
TL_ORIGINAL(void, old_add_float, (void*, float), "_ZN12CAchievement8addValueEf")
extern "C" void new_add_float(void*, float) __asm__("_ZN12CAchievement8addValueEf");
TL_ORIGINAL(void, old_add_int, (void*, int), "_ZN12CAchievement8addValueEi")
extern "C" void new_add_int(void*, int) __asm__("_ZN12CAchievement8addValueEi");
TL_ORIGINAL(void, old_increment, (void*), "_ZN12CAchievement9incrementEv")
extern "C" void new_increment(void*) __asm__("_ZN12CAchievement9incrementEv");
TL_FUNCTION(statsSingleton,"_ZN11CSteamStats12getSingletonEv")
TL_FUNCTION(getInt,"_ZN11CSteamStats10getStatIntE6ESTATS")
TL_FUNCTION(getFloat,"_ZN11CSteamStats12getStatFloatE6ESTATS")
TL_FUNCTION(setInt,"_ZN11CSteamStats10setStatIntE6ESTATSj")
TL_FUNCTION(incrementStat,"_ZN11CSteamStats13incrementStatE6ESTATSi")
TL_FUNCTION(check,"_ZN12CAchievement16checkForAchievedEv")
TL_FUNCTION(setFloatValue,"_ZN12CAchievement8setValueEf")
TL_FUNCTION(setIntValue,"_ZN12CAchievement8setValueEi")
TL_FUNCTION(achievementsSingleton,"_ZN13CAchievements12getSingletonEv")
TL_FUNCTION(complete,"_ZN13CAchievements22setAchievementCompleteEP12CAchievement")
namespace {
struct Case {unsigned operation,seed;};
autotest::Capture* output;CAchievement* achievement;unsigned calls,seed,op;uint64_t stats[8],achievements[4];
void number(unsigned n){output->add(&n,4);}void invalid(){output->issue=autotest::Capture::InvalidReport;}
void event(unsigned n){number(n);++calls;}
void* singleton(){event(1);return stats;}
void* achSingleton(){event(8);return achievements;}
int integer(void* p,int stat){event(2);number(stat);if(p!=stats)invalid();if(seed&32)achievement->m_eStatType=static_cast<ESTATS>(29);if(seed&64){unsigned bits=op==2||op==3?7:0x3fc00000;std::memcpy(&achievement->m_fRequiredValue,&bits,4);}return int(seed%9)-4;}
float floating(void* p,int stat){event(3);number(stat);if(p!=stats)invalid();if(seed&32)achievement->m_eStatType=static_cast<ESTATS>(29);if(seed&64)achievement->m_fRequiredValue=7.5f;unsigned bits=seed%8==0?0x7fc12345:seed%8==1?0x7f800000:seed%8==2?0xff800000:0;float value=float(int(seed%9)-4)+0.5f;if(bits)std::memcpy(&value,&bits,4);return value;}
void set(void* p,int stat,unsigned value){event(4);number(stat);number(value);if(p!=stats)invalid();stats[1]^=value;}
void increment(void* p,int stat,int value){event(5);number(stat);number(value);if(p!=stats||value!=1)invalid();stats[2]^=stat;}
void checked(void* p){event(6);if(p!=achievement)invalid();achievement->m_fCurrentValue=-3.75f;}
void valueInt(void* p,int value){event(7);number(value);if(p!=achievement)invalid();achievement->m_fCurrentValue=float(value);}
void valueFloat(void* p,float value){event(9);output->add(&value,4);if(p!=achievement)invalid();achievement->m_fCurrentValue=value;}
void completed(void* p,void* a){event(10);if(p!=achievements||a!=achievement)invalid();achievements[1]=0x123456;}
void side(void* raw,autotest::Capture& out,bool ours){
 const Case& c=*static_cast<Case*>(raw);seed=c.seed;op=c.operation;output=&out;calls=0;
 uint64_t object[(sizeof(CAchievement)+7)/8];std::memset(object,0xa5,sizeof(object));std::memset(stats,0x3c,sizeof(stats));std::memset(achievements,0x69,sizeof(achievements));achievement=reinterpret_cast<CAchievement*>(object);
 const int statValues[]={-1,0,1,15,29,30,31,0x7fffffff};int stat=op==2||op==3?int(seed%31):statValues[seed%8];achievement->m_eStatType=static_cast<ESTATS>(stat);achievement->m_bAchieved=op==3&&bool(seed&16);
 unsigned required[]={0,1,2,7,0xffffffff,0x3f800000,0x40e00000,0x7fc12345,0x7f800000,0xff800000};unsigned bits=required[(seed/4)%10];std::memcpy(&achievement->m_fRequiredValue,&bits,4);
 // Original local STT_OBJECT g_strStatDefines, Achievement.cpp; packet maps type to +4 of each 24-byte record.
 unsigned char* definitions=reinterpret_cast<unsigned char*>(0x1538e20);for(unsigned i=0;i<31;++i){int type=int((seed/8)%3);std::memcpy(definitions+i*24+4,&type,4);}
 detour::Set patches;TL_REDIRECT(patches,statsSingleton,&singleton);TL_REDIRECT(patches,getInt,&integer);TL_REDIRECT(patches,getFloat,&floating);TL_REDIRECT(patches,setInt,&set);TL_REDIRECT(patches,incrementStat,&increment);TL_REDIRECT(patches,check,&checked);TL_REDIRECT(patches,achievementsSingleton,&achSingleton);TL_REDIRECT(patches,complete,&completed);
 if(op==2||op==3){TL_REDIRECT(patches,setFloatValue,&valueFloat);TL_REDIRECT(patches,setIntValue,&valueInt);}
 if(patches.failed()){invalid();return;}
 unsigned inputBits[]={0,0x80000000,0x3fc00000,0xbfc00000,0x4f000000,0x7fc12345,0x7f800000,0xff800000};float input;bits=inputBits[(seed/8)%8];std::memcpy(&input,&bits,4);int ivalue=(seed&16)?-int(seed)-1:int(seed);
 if(op==0){typedef void(*Fn)(void*,float);Fn fn=ours?new_set_float:old_set_float;if(!autotest::beginInvocation(out,fn))return;fn(object,input);}
 if(op==1){typedef void(*Fn)(void*,int);Fn fn=ours?new_set_int:old_set_int;if(!autotest::beginInvocation(out,fn))return;fn(object,ivalue);}
 if(op==2){typedef void(*Fn)(void*);Fn fn=ours?new_cheat:old_cheat;if(!autotest::beginInvocation(out,fn))return;fn(object);}
 if(op==3){typedef void(*Fn)(void*);Fn fn=ours?new_force:old_force;if(!autotest::beginInvocation(out,fn))return;fn(object);}
 if(op==4){typedef void(*Fn)(void*,float);Fn fn=ours?new_add_float:old_add_float;if(!autotest::beginInvocation(out,fn))return;fn(object,input);}
 if(op==5){typedef void(*Fn)(void*,int);Fn fn=ours?new_add_int:old_add_int;if(!autotest::beginInvocation(out,fn))return;fn(object,ivalue);}
 if(op==6){typedef void(*Fn)(void*);Fn fn=ours?new_increment:old_increment;if(!autotest::beginInvocation(out,fn))return;fn(object);}
 out.callCompleted=1;number(calls);out.add(object,sizeof(object));out.add(stats,sizeof(stats));out.add(achievements,sizeof(achievements));out.add(definitions,744);
}
void original(void* c,autotest::Capture& out){side(c,out,false);}void candidate(void* c,autotest::Capture& out){side(c,out,true);}
int run(const tlhybrid_host* host,unsigned op,const char* name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned seed=0;seed<192;++seed){Case c={op,seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    achievement op %u seed %u exits %d/%d issues %u/%u\n",op,seed,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(achievement_set_float){return run(host,0,"achievement_set_float",reinterpret_cast<uintptr_t>(&old_set_float));}
TL_TEST(achievement_set_int){return run(host,1,"achievement_set_int",reinterpret_cast<uintptr_t>(&old_set_int));}
TL_TEST(achievement_cheat){return run(host,2,"achievement_cheat",reinterpret_cast<uintptr_t>(&old_cheat));}
TL_TEST(achievement_force){return run(host,3,"achievement_force",reinterpret_cast<uintptr_t>(&old_force));}
TL_TEST(achievement_add_float){return run(host,4,"achievement_add_float",reinterpret_cast<uintptr_t>(&old_add_float));}
TL_TEST(achievement_add_int){return run(host,5,"achievement_add_int",reinterpret_cast<uintptr_t>(&old_add_int));}
TL_TEST(achievement_increment){return run(host,6,"achievement_increment",reinterpret_cast<uintptr_t>(&old_increment));}
