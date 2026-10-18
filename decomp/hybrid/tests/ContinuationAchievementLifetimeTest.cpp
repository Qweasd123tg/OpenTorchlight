#include <string>
#include <cstring>
#include <stdint.h>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#include "Achievement.h"
TL_ORIGINAL(void,caCtor,(CAchievement*,std::string,ESTATS,int,int),"_ZN12CAchievementC1ESs6ESTATSii")
TL_ORIGINAL(void,caOldDestroy,(CAchievement*),"_ZN12CAchievementD1Ev")
extern "C" void caNewDestroy(CAchievement*) __asm__("_ZN12CAchievementD1Ev");
TL_FUNCTION(caStats,"_ZN11CSteamStats12getSingletonEv")
TL_FUNCTION(caListener,"_ZN11CSteamStats15addStatListenerE6ESTATSP13iStatListener")
namespace {
struct Case{unsigned seed;};autotest::Capture* out;void* instance;void* stats;unsigned callbacks;
void* singleton(){return stats;}void listener(void*p,ESTATS type,iStatListener* value){++callbacks;if(p!=stats||value!=static_cast<iStatListener*>(static_cast<CAchievement*>(instance)))out->issue=autotest::Capture::InvalidReport;}
void side(void*raw,autotest::Capture& capture,bool ours){unsigned seed=static_cast<Case*>(raw)->seed;out=&capture;callbacks=0;uint64_t memory[(sizeof(CAchievement)+7)/8]={0},statMem[32]={0};CAchievement* self=reinterpret_cast<CAchievement*>(memory);instance=self;stats=statMem;int before=g_iTotalCountOfObjects;detour::Set d;TL_REDIRECT(d,caStats,&singleton);TL_REDIRECT(d,caListener,&listener);if(d.failed()){capture.issue=autotest::Capture::InvalidReport;return;}std::string name=seed%3==0?std::string():seed%3==1?std::string("achievement"):std::string(1024,'X');caCtor(self,name,static_cast<ESTATS>(seed%31),int(seed)-13,int(seed)*11);TSafePointer<CAchievement> weak[5];for(unsigned i=0;i<seed%6;++i)weak[i].setObject(self);if(seed&2)weak[0].setObject(NULL);int constructed=g_iTotalCountOfObjects;typedef void(*Fn)(CAchievement*);Fn fn=ours?caNewDestroy:caOldDestroy;if(!autotest::beginInvocation(capture,fn))return;fn(self);capture.callCompleted=1;capture.add(&callbacks,4);int delta=constructed-before;capture.add(&delta,4);delta=g_iTotalCountOfObjects-before;capture.add(&delta,4);for(unsigned i=0;i<5;++i){bool empty=weak[i].getObject()==NULL;capture.add(&empty,1);if(!empty)capture.issue=autotest::Capture::InvalidReport;}capture.addHeapInUse();if(callbacks!=1||constructed!=before+1||g_iTotalCountOfObjects!=constructed)capture.issue=autotest::Capture::InvalidReport;}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(continuation_achievement_lifetime){autotest::Coverage coverage("continuation_achievement_lifetime",(uintptr_t)&caOldDestroy);for(unsigned i=0;i<32;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    achievement lifetime seed%u issue%u/%u status%d/%d\n",i,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus);coverage.report(host);return 1;}}coverage.report(host);return 0;}
