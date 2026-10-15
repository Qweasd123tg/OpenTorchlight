#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "SteamStats.h"
#undef private
TL_ORIGINAL(void,oldModified,(CSteamStats*,ESTATS,UNIONDATA32BIT),"_ZN11CSteamStats12statModifiedE6ESTATS14UNIONDATA32BIT")
extern "C" void newModified(CSteamStats*,ESTATS,UNIONDATA32BIT) __asm__("_ZN11CSteamStats12statModifiedE6ESTATS14UNIONDATA32BIT");
extern "C" char arrayNew[] __asm__("_Znam");
extern "C" char arrayDelete[] __asm__("_ZdaPv");
namespace {struct Case{unsigned shape,key;};uint64_t allocated[16];autotest::Capture*output;void*initial;unsigned allocations,frees;
void invalid(){output->issue=autotest::Capture::InvalidReport;}void*allocate(unsigned long size){++allocations;output->add(&size,sizeof(size));if(size>sizeof(allocated))invalid();return allocated;}void release(void*p){++frees;unsigned id=p==initial?1:p==allocated?2:0;output->add(&id,4);if(!id)invalid();}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);output=&out;allocations=frees=0;uint64_t storage[(sizeof(CSteamStats)+7)/8];std::memset(storage,0xa5,sizeof(storage));std::memset(allocated,0x3c,sizeof(allocated));CSteamStats*self=reinterpret_cast<CSteamStats*>(storage);typedef CSteamStats::SStatChange Change;TArrayList<Change>*list=new(&self->m_pendingStatChanges)TArrayList<Change>(4);unsigned count=c.shape==0?0:c.shape==1?1:3,capacity=c.shape==0?0:c.shape==2?1:c.shape==3?3:4;Change*data=capacity?new Change[4]:0;for(unsigned i=0;i<4&&data;++i){data[i].stat=static_cast<ESTATS>(i*15);data[i].value.m_uValue=0x11223344u+i;}list->m_pData=data;list->m_nCount=count;list->m_nCapacity=capacity;initial=data;const int keys[]={-1,0,15,30,31,0x7fffffff};ESTATS key=static_cast<ESTATS>(keys[c.key]);UNIONDATA32BIT value;value.m_uValue=0xdeadbeef;
 detour::Set patches;patches.redirect(arrayNew,arrayNew,&allocate);patches.redirect(arrayDelete,arrayDelete,&release);if(patches.failed()){invalid();return;}typedef void(*Fn)(CSteamStats*,ESTATS,UNIONDATA32BIT);Fn fn=ours?newModified:oldModified;if(!autotest::beginInvocation(out,fn))return;fn(self,key,value);out.callCompleted=1;out.add(&allocations,4);out.add(&frees,4);out.add(&list->m_nCount,4);out.add(&list->m_nCapacity,4);unsigned id=list->m_pData==initial?1:list->m_pData==reinterpret_cast<Change*>(allocated)?2:0;if(!id)invalid();out.add(&id,4);if(list->m_nCapacity>16)invalid();else out.add(list->m_pData,list->m_nCapacity*sizeof(Change));out.add(allocated,sizeof(allocated));patches.restore();list->m_pData=0;list->~TArrayList<Change>();delete[] data;
}
void original(void*c,autotest::Capture&out){side(c,out,false);}void candidate(void*c,autotest::Capture&out){side(c,out,true);}}
TL_TEST(steam_stats_pending_changes){autotest::Coverage coverage("steam_stats_pending_changes",reinterpret_cast<uintptr_t>(&oldModified));for(unsigned shape=0;shape<5;++shape)for(unsigned key=0;key<6;++key){Case c={shape,key};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    stat pending shape %u key %u exits %d/%d issues %u/%u\n",shape,key,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);coverage.report(host);return 1;}}coverage.report(host);return 0;}
