#include <stdint.h>
#include <cstring>
#include <new>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "SafePointer.h"
#define private public
#include "SpawnClass.h"
#include "SpawnClassData.h"
#undef private
TL_ORIGINAL(void,oCtor,(CSpawnClass*,const wchar_t*),"_ZN11CSpawnClassC1EPKw")
TL_ORIGINAL(void,oDtor,(CSpawnClass*),"_ZN11CSpawnClassD1Ev")
extern "C" void nDtor(CSpawnClass*) __asm__("_ZN11CSpawnClassD1Ev");
TL_ORIGINAL(int,oCount,(CSpawnClass*,CCharacter*,int,int,int,int),"_ZN11CSpawnClass24calculateNumberOfChoicesEP10CCharacteriiii")
extern "C" int nCount(CSpawnClass*,CCharacter*,int,int,int,int) __asm__("_ZN11CSpawnClass24calculateNumberOfChoicesEP10CCharacteriiii");
TL_FUNCTION(choices,"_ZN15CSpawnClassData16calculateChoicesEP10CCharacteriiii")
namespace{
struct Case{unsigned mode,seed;};autotest::Capture*capture;unsigned destroyed,freed,calls;CSpawningData* objects[8];CSpawnClassData* data[8];CCharacter* character;
void number(unsigned value){capture->add(&value,4);}
unsigned identity(void* p){for(unsigned i=0;i<8;++i)if(objects[i]==p)return i;return 999;}
// Original CSpawningData D1 @a76830 only restores its vptr then calls CRunicCore D1.
struct LifetimeWitness:CSpawningData{virtual ~LifetimeWitness(){++destroyed;number(7);number(identity(this));}void operator delete(void*p){++freed;number(8);number(identity(p));CSpawningData::operator delete(p);}};
unsigned calculate(CSpawnClassData*self,CCharacter* who,int a,int b,int c,int d){unsigned id=999;for(unsigned i=0;i<8;++i)if(data[i]==self)id=i;number(id);number(who==character);capture->add(&a,4);capture->add(&b,4);capture->add(&c,4);capture->add(&d,4);++calls;return id*113+unsigned(a)^unsigned(b)^unsigned(c)^unsigned(d);}
void side(void* raw,autotest::Capture&out,bool ours){Case&c=*static_cast<Case*>(raw);capture=&out;destroyed=freed=calls=0;std::memset(objects,0,sizeof(objects));uint64_t memory[(sizeof(CSpawnClass)+7)/8],ds[8][(sizeof(CSpawnClassData)+7)/8],cs[(sizeof(CCharacter)+7)/8];CSpawnClass*self=reinterpret_cast<CSpawnClass*>(memory);character=reinterpret_cast<CCharacter*>(cs);std::memset(memory,0xa5,sizeof(memory));oCtor(self,c.seed%2?L"spawn/Ж":L"");for(unsigned i=0;i<8;++i)data[i]=reinterpret_cast<CSpawnClassData*>(ds[i]);TSafePointer<CSpawnClass> reference;reference.setObject(self);
 if(c.mode==0){SpawnClassEntry entries[8];for(unsigned i=0;i<c.seed%8;++i){entries[i].data=NULL;entries[i].spawnClassData=data[i];self->m_entries.add(&entries[i]);}if(c.seed&16&&self->m_entries.size())self->m_entries.m_nCapacity=(c.seed/8)%2;detour::Set d;TL_REDIRECT(d,choices,&calculate);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef int(*Fn)(CSpawnClass*,CCharacter*,int,int,int,int);Fn fn=ours?nCount:oCount;if(!autotest::beginInvocation(out,fn))return;int result=fn(self,c.seed&1?character:NULL,int(c.seed)-70,int(c.seed)*-3,17,-1);out.callCompleted=1;out.add(&result,4);number(calls);number(self->m_entries.size());capture->addText(self->m_name);number(self->m_iUnknown30);self->m_entries.clear();oDtor(self);}
 else{TSafePointer<CSpawningData> refs[8];unsigned expected=0;for(unsigned i=0;i<c.seed%8;++i){SpawnClassEntry* entry=new SpawnClassEntry;entry->data=NULL;entry->spawnClassData=data[i];if((i+c.seed)%3){entry->data=new LifetimeWitness;objects[i]=entry->data;refs[i].setObject(entry->data);++expected;}self->m_entries.add(entry);}typedef void(*Fn)(CSpawnClass*);Fn fn=ours?nDtor:oDtor;if(!autotest::beginInvocation(out,fn))return;fn(self);out.callCompleted=1;number(destroyed);number(freed);for(unsigned i=0;i<8;++i)number(refs[i].getObject()==NULL);if(destroyed!=expected||freed!=expected)out.issue=autotest::Capture::InvalidReport;}
 number(reference.getObject()==NULL);if(reference.getObject())out.issue=autotest::Capture::InvalidReport;
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host*h,unsigned mode,const char*n,uintptr_t a){autotest::Coverage coverage(n,a);for(unsigned seed=0;seed<96;++seed){Case c={mode,seed};autotest::Outcome x,y;autotest::runChild(original,&c,x);autotest::runChild(candidate,&c,y);if(coverage.observe(h,x,y)){h->log("    spawn mode %u seed %u issue %u/%u exits %d/%d\n",mode,seed,x.capture.issue,y.capture.issue,x.childStatus,y.childStatus);coverage.report(h);return 1;}}coverage.report(h);return 0;}
}
TL_TEST(bulk_spawn_class_count){return run(host,0,"bulk_spawn_class_count",(uintptr_t)&oCount);}
TL_TEST(bulk_spawn_class_lifetime){return run(host,1,"bulk_spawn_class_lifetime",(uintptr_t)&oDtor);}
