// Narrow expected-unwind probes for original Quest LSDA-covered by-value calls.
// These receive NO completed-call acceptance credit. Their purpose is exact
// partial writes plus COW/deep-copy release when lookup/getMaxDepth throws.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,qrluOldReset,(void*,bool,bool),"_ZN6CQuest17reinitializeQuestEbb")
extern "C" void qrluNewReset(void*,bool,bool) __asm__("_ZN6CQuest17reinitializeQuestEbb");
TL_ORIGINAL(void,qrluOldLoad,(void*,FILE*,void*,unsigned),"_ZN6CQuest4loadEP8_IO_FILEP16CResourceManagerj")
extern "C" void qrluNewLoad(void*,FILE*,void*,unsigned) __asm__("_ZN6CQuest4loadEP8_IO_FILEP16CResourceManagerj");
TL_FUNCTION(qrluSingleton,"_ZN15CDungeonManager12getSingletonEv")
TL_FUNCTION(qrluLookup,"_ZN15CDungeonManager16getDungeonByNameESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qrluDepth,"_ZN7CPlayer11getMaxDepthESbIwSt11char_traitsIwESaIwEE")
extern "C" char qrluDestroy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_");
extern "C" char qrluStringDtor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEED1Ev");
namespace qrlu {
typedef std::wstring Wide;
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>((char*)p+off);}
struct Case {unsigned kind,leaked;}; // reset lookup, reset depth, load lookup
struct Stop {unsigned point;explicit Stop(unsigned p):point(p){}};
struct Rep {void* p;unsigned freed;};
static const Case* cs;static autotest::Capture* cap;static unsigned errors,firstError,lookups,depths,reps,destructions;
static void *owner,*resource,*manager,*client,*dungeonManager,*dungeon,*player,*oldTemplate,*oldGuid;static FILE* file;
static Rep temporaries[2];static detour::Set *destroyPatch,*stringPatch;static void* forwardedRep;static int initialRefs;static unsigned char expected[0x218];
static void n(unsigned v){cap->add(&v,4);}
static void check(bool yes,unsigned line){if(!yes){if(!errors)firstError=line;++errors;}}
#define need(x) check((x),__LINE__)
static void* raw(unsigned size,unsigned char fill=0){unsigned char* p=(unsigned char*)autotest::allocate(size+32);if(!p)_exit(71);std::memset(p,0xce,size+32);std::memset(p+16,fill,size);return p+16;}
static int refs(const Wide& text){return *(const int*)((const char*)text.c_str()-8);}
static void* rep(const Wide& text){return (void*)((const char*)text.c_str()-24);}
static void watch(const Wide& name){need(name==L"Quest unwind dungeon \u03a9");need(reps<2);if(reps>=2)return;
 Wide& source=at<Wide>(owner,0x30);need(refs(source)==(cs->leaked?-1:initialRefs+1));need((rep(name)==rep(source))==(cs->leaked==0));need(refs(name)==(cs->leaked?0:initialRefs+1));temporaries[reps].p=rep(name);temporaries[reps++].freed=0;n(100+reps);
}
static void* singleton(){n(1);return dungeonManager;}
static void* lookup(void* self,Wide name){need(self==dungeonManager);++lookups;watch(name);n(2);if(cs->kind!=1)throw Stop(2);return dungeon;}
static int depth(void* self,Wide name){need(self==player);++depths;watch(name);n(3);throw Stop(3);}
static void released(void* p){if(!cs->leaked)return;unsigned i=0;for(;i<reps;++i)if(temporaries[i].p==p&&!temporaries[i].freed)break;need(i<reps);if(i<reps){++temporaries[i].freed;++destructions;n(200+i);}}
static void destroy(void* p,const void* allocator){bool observe=p!=forwardedRep;destroyPatch->restore();reinterpret_cast<void(*)(void*,const void*)>(qrluDestroy)(p,allocator);if(observe)released(p);destroyPatch->redirect(qrluDestroy,qrluDestroy,&destroy);}
static void stringDtor(Wide* text){void* p=rep(*text);void* previous=forwardedRep;forwardedRep=p;stringPatch->restore();reinterpret_cast<void(*)(Wide*)>(qrluStringDtor)(text);released(p);stringPatch->redirect(qrluStringDtor,qrluStringDtor,&stringDtor);forwardedRep=previous;}
static void side(void* context,autotest::Capture& out,bool candidate){
 cs=(Case*)context;cap=&out;errors=firstError=lookups=depths=reps=destructions=0;file=0;forwardedRep=0;autotest::g_arenaUsed=0;
 owner=raw(0x218,0x59);resource=raw(0x40);manager=raw(0x30);client=raw(0x3910);dungeonManager=raw(0x40);dungeon=raw(0x118);player=raw(0x40);oldTemplate=raw(0x778);oldGuid=raw(0x40);
 at<void*>(owner,0x1d8)=resource;at<void*>(owner,0x1d0)=manager;at<void*>(owner,0x10)=oldTemplate;at<void*>(owner,0x1e8)=oldGuid;at<void*>(manager,0x10)=player;
 void** clients=(void**)raw(8);clients[0]=client;at<void*>(resource,0x28)=clients;at<unsigned>(resource,0x30)=1;at<int>(client,0x1090)=100;at<int>(client,0x1094)=7;at<void*>(client,0x38d8)=0;
 at<int>(owner,0x1c)=29;at<int>(owner,0x20)=33;at<unsigned>(owner,0x20c)=0x11223344;at<unsigned char>(owner,0x24)=at<unsigned char>(owner,0x26)=at<unsigned char>(owner,0x209)=at<unsigned char>(owner,0x210)=1;
 new((char*)owner+0x30)Wide(L"Quest unwind dungeon \u03a9");if(cs->leaked)at<Wide>(owner,0x30)[0]=L'Q';initialRefs=refs(at<Wide>(owner,0x30));need(initialRefs==(cs->leaked?-1:0));
 std::memcpy(expected,owner,sizeof(expected));uint64_t wantedSeed=29;
 if(cs->kind==2){file=std::tmpfile();if(!file)_exit(71);const unsigned char bytes[]={255,255,255,255,255,255,255,255,17,0,0,0,4,0,0,0,0x21,0x43,0x65,0x87};need(std::fwrite(bytes,1,sizeof(bytes),file)==sizeof(bytes));std::rewind(file);at<unsigned>(expected,0x1c)=17;at<unsigned>(expected,0x20)=4;at<unsigned>(expected,0x20c)=0x87654321u;wantedSeed=104;}
 else {expected[0x24]=expected[0x26]=expected[0x209]=expected[0x210]=0;at<void*>(expected,0x1e8)=0;at<void*>(expected,0x10)=0;}
 unsigned caught=0;
 {detour::Set boundaries,destroys,strings;destroyPatch=&destroys;stringPatch=&strings;TL_REDIRECT(boundaries,qrluSingleton,&singleton);TL_REDIRECT(boundaries,qrluLookup,&lookup);TL_REDIRECT(boundaries,qrluDepth,&depth);destroys.redirect(qrluDestroy,qrluDestroy,&destroy);strings.redirect(qrluStringDtor,qrluStringDtor,&stringDtor);
  if(boundaries.failed()||destroys.failed()||strings.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(cs->kind==2){typedef void(*Fn)(void*,FILE*,void*,unsigned);Fn fn=candidate?&qrluNewLoad:&qrluOldLoad;if(!autotest::beginInvocation(out,fn))return;try{fn(owner,file,resource,20);out.callCompleted=1;}catch(const Stop& stop){caught=stop.point;}}
  else {typedef void(*Fn)(void*,bool,bool);Fn fn=candidate?&qrluNewReset:&qrluOldReset;if(!autotest::beginInvocation(out,fn))return;try{fn(owner,true,false);out.callCompleted=1;}catch(const Stop& stop){caught=stop.point;}}
 }
 need(caught==(cs->kind==1?3u:2u));need(lookups==1&&depths==(cs->kind==1?1u:0u));need(reps==1+depths);need(destructions==(cs->leaked?reps:0u));for(unsigned i=0;i<reps;++i)need(temporaries[i].freed==cs->leaked);
 need(!std::memcmp(owner,expected,sizeof(expected)));need(refs(at<Wide>(owner,0x30))==initialRefs);need(at<Wide>(owner,0x30)==L"Quest unwind dungeon \u03a9");need(*reinterpret_cast<uint64_t*>(0x14ecaf0)==wantedSeed);
 for(unsigned i=0;i<16;++i)need(((unsigned char*)owner)[-16+(int)i]==0xce&&((unsigned char*)owner)[0x218+i]==0xce);
 cap->add(owner,sizeof(expected));n(caught);n(lookups);n(depths);n(reps);n(destructions);if(file){need(std::ftell(file)==20&&!std::feof(file)&&!std::ferror(file));n((unsigned)std::ftell(file));std::fclose(file);}n(firstError);n(0x7152ee10u);n(errors);at<Wide>(owner,0x30).~Wide();
}
static void old(void* p,autotest::Capture& out){side(p,out,false);}static void fresh(void* p,autotest::Capture& out){side(p,out,true);}
static bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&o.capture.callStarted&&!o.capture.callCompleted&&tail[0]==0x7152ee10u&&!tail[1];}
}
TL_TEST(quest_persistence_reset_load_unwind){using namespace qrlu;for(unsigned kind=0;kind<3;++kind)for(unsigned leaked=0;leaked<2;++leaked){Case c={kind,leaked};autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(fresh,&c,b);uint64_t address=kind==2?0xd17b20:0xd17200;
 bool ok=good(a)&&good(b)&&a.capture.callTarget==address&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
 if(!ok){host->log("    Quest reset/load unwind kind=%u leaked=%u status=%d/%d good=%u/%u issue=%u/%u\n",kind,leaked,a.childStatus,b.childStatus,good(a),good(b),a.capture.issue,b.capture.issue);return 1;}}
 host->log("    Quest reset/load: 6 LSDA-covered expected lookup/depth unwinds, no completed-call credit\n");return 0;}
