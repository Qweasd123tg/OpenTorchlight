// Independent bounded composition oracle: original d0cc10/d0ce90 with accepted
// d0cbe0 setter, d2f470 manager event and d2dca0 map lookup. UnitData leaves
// execute original d3dd20/d48140. No UnitData acceptance is claimed.
// A completion notification queries its already-complete owner and completes
// up to two dependent quests recursively through genuine manager dispatch.
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(long long,qrrOldComplete,(void*,bool),"_ZN6CQuest10isCompleteEb")
extern "C" long long qrrNewComplete(void*,bool) __asm__("_ZN6CQuest10isCompleteEb");
TL_ORIGINAL(void,qrrOldEvent,(void*,unsigned,void*,void*),"_ZN6CQuest16questEventUpdateE13EQUEST_EVENTSP9CBaseUnitS2_")
extern "C" void qrrNewEvent(void*,unsigned,void*,void*) __asm__("_ZN6CQuest16questEventUpdateE13EQUEST_EVENTSP9CBaseUnitS2_");
TL_FUNCTION(qrrComplete,"_ZN6CQuest10isCompleteEb")
TL_FUNCTION(qrrEvent,"_ZN6CQuest16questEventUpdateE13EQUEST_EVENTSP9CBaseUnitS2_")
TL_FUNCTION(qrrSetter,"_ZN6CQuest13setIsCompleteEb")
TL_FUNCTION(qrrNotify,"_ZN13CQuestManager16questEventUpdateE13EQUEST_EVENTSP10CCharacterP9CBaseUnit")
TL_FUNCTION(qrrDone,"_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qrrUnitComplete,"_ZN14CQuestUnitData10isCompleteEb")
TL_FUNCTION(qrrPickup,"_ZN14CQuestUnitData12unitPickedUpEP9CBaseUnit")
TL_FUNCTION(qrrUI,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(qrrRefresh,"_ZN7CGameUI16refreshQuestMenuEv")
extern "C" void qrrAcceptedSetter(void*,bool) __asm__("_ZN6CQuest13setIsCompleteEb");
extern "C" void qrrAcceptedNotify(void*,unsigned,void*,void*) __asm__("_ZN13CQuestManager16questEventUpdateE13EQUEST_EVENTSP10CCharacterP9CBaseUnit");
extern "C" char qrrAcceptedDone(void*,const std::wstring&) __asm__("_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE");
namespace qrr {
typedef std::wstring Wide;typedef std::map<Wide,bool> Map;
struct List {void** data;unsigned count,capacity,grow,pad;};
struct Flags {unsigned char* data;unsigned count,capacity,grow,pad;};
struct Names {Wide* data;unsigned count,capacity,grow,pad;};
typedef char ABI[sizeof(List)==24&&sizeof(Wide)==8&&sizeof(Map)==48?1:-1];
struct Case {unsigned kind,dependents,force,preloaded;};
enum Code {CompleteIn=1,CompleteOut,EventIn,EventOut,SetterIn,SetterOut,NotifyIn,NotifyOut,Lookup,UnitComplete,Pickup,UnexpectedUI};
struct Event {unsigned code,id,arg,depth,complete,flags,unitDone,unitCount;};
struct NodeBefore {void* p;unsigned char bytes[48];};
static const Case* cs;static autotest::Capture* cap;static bool candidateSide;
static unsigned errors,firstError,wanted,observed,modelDepth,actualDepth,arenaSize;
static Event events[512];static unsigned char expected[16384];
static void *quests[3],*manager,*player,*target,*unit,*marker,*ui;static List* group;static Map* completed;static NodeBefore nodes[2];static unsigned nodeCount;
static detour::Set *cp,*ep,*sp,*np,*dp,*up,*pp;
template<class T>T& at(void* p,unsigned offset){return *reinterpret_cast<T*>((char*)p+offset);}
static void check(bool b,unsigned line){if(!b){if(!errors)firstError=line;if(errors<4)std::fprintf(stderr,"    QRR %s kind=%u deps=%u force=%u preloaded=%u line=%u event=%u/%u depth=%u\n",candidateSide?"candidate":"original",cs->kind,cs->dependents,cs->force,cs->preloaded,line,observed,wanted,actualDepth);++errors;}}
#define need(x) check((x),__LINE__)
static void number(unsigned n){cap->add(&n,4);}
static void* raw(unsigned size,unsigned char fill=0){unsigned char* p=(unsigned char*)autotest::allocate(size+32);if(!p)_exit(71);std::memset(p,0xa9,size+32);std::memset(p+16,fill,size);return p+16;}
static void* mem(void* p,bool model){return model?expected+((char*)p-autotest::g_arena):p;}
template<class T>T& field(void* p,unsigned offset,bool model){return at<T>(mem(p,model),offset);}
static unsigned id(void* p){for(unsigned i=0;i<3;++i)if(quests[i]==p)return i;need(false);return 0;}
static unsigned char& flag(unsigned q,bool model){Flags& f=field<Flags>(quests[q],0x110,model);return *(unsigned char*)mem(f.data,model);}
static void trace(bool model,unsigned code,unsigned q=99,unsigned arg=0){unsigned bits=0,flags=0;for(unsigned i=0;i<3;++i){if(field<unsigned char>(quests[i],0x24,model))bits|=1u<<i;if(i&&flag(i,model))flags|=1u<<i;}Event e={code,q,arg,model?modelDepth:actualDepth,bits,flags,field<unsigned char>(unit,0x60,model),field<unsigned>(unit,0x3c,model)};
 if(model){if(wanted>=512)_exit(72);events[wanted++]=e;}else{need(observed<wanted);if(observed<wanted)need(!std::memcmp(&e,&events[observed],sizeof(e)));++observed;cap->add(&e,sizeof(e));}}
static bool modelComplete(unsigned,bool);static void modelEvent(unsigned,unsigned);static void modelNotify();
static void modelSetter(unsigned q){trace(true,SetterIn,q,1);bool change=!field<unsigned char>(quests[q],0x24,true);field<unsigned char>(quests[q],0x24,true)=1;if(change)modelNotify();trace(true,SetterOut,q,1);}
static bool modelComplete(unsigned q,bool force){trace(true,CompleteIn,q,force);bool result=false;
 if(!force&&field<unsigned char>(quests[q],0x24,true))result=true;
 else {bool ready;if(!q){trace(true,UnitComplete,0,0);ready=field<unsigned char>(unit,0x60,true)!=0;}else ready=flag(q,true)!=0;if(ready){modelSetter(q);result=true;}}
 trace(true,CompleteOut,q,result);return result;
}
static void modelEvent(unsigned q,unsigned e){trace(true,EventIn,q,e);if(e==0){trace(true,Pickup,0,1);unsigned& count=field<unsigned>(unit,0x3c,true);++count;if(count>=2)field<unsigned char>(unit,0x60,true)=1;if(count>2)count=2;modelComplete(q,false);}else{if(!flag(q,true)){trace(true,Lookup,q,1);flag(q,true)=1;}modelComplete(q,false);}trace(true,EventOut,q,e);}
static void modelNotify(){++modelDepth;trace(true,NotifyIn,99,4);
 for(unsigned q=0;q<=cs->dependents;++q){bool before=modelComplete(q,false);if(before)continue;modelEvent(q,4);bool after=modelComplete(q,false);need(after);bool last=modelComplete(q,false);need(last&&!before);}
 trace(true,NotifyOut,99,4);--modelDepth;
}
static void initList(List& l,unsigned count){l.data=(void**)raw(24);l.count=count;l.capacity=3;l.grow=2;l.pad=0x76543210;}
static void setup(){errors=firstError=wanted=observed=modelDepth=actualDepth=nodeCount=0;autotest::g_arenaUsed=0;
 for(unsigned q=0;q<3;++q)quests[q]=raw(0x218,0x57);manager=raw(0xd0,0x61);player=raw(0x300);target=raw(0x1c0);unit=raw(0xc8,0x63);marker=raw(0x40);ui=raw(0x40);group=(List*)raw(24);initList(*group,1);group->data[0]=unit;
 at<void*>(manager,0x10)=player;initList(at<List>(manager,0x18),cs->dependents+1);for(unsigned q=0;q<3;++q)at<List>(manager,0x18).data[q]=quests[q];completed=new((char*)manager+0x70)Map;
 const wchar_t* keys[]={L"Owner",L"Ready first",L"Ready \u0416\u732b"};
 for(unsigned q=0;q<3;++q){at<unsigned char>(quests[q],0x24)=0;at<unsigned char>(quests[q],0x2a)=0;at<unsigned char>(quests[q],0x209)=1;at<void*>(quests[q],0x1d0)=manager;at<long long>(quests[q],0x1c8)=0x123456789abcdefLL;new((char*)quests[q]+0x50)Wide(keys[q]);
  initList(at<List>(quests[q],0x60),0);for(unsigned f=0;f<2;++f){initList(at<List>(quests[q],0x130+24*f),q==0&&f==0?1:0);at<List>(quests[q],0x130+24*f).data[0]=group;Flags& flags=at<Flags>(quests[q],0xf8+24*f);flags.data=(unsigned char*)raw(4,0x75);flags.data[0]=q&&cs->preloaded?1:0;flags.count=q&&f==1?1:0;flags.capacity=4;flags.grow=2;flags.pad=0x22446688;Names& names=at<Names>(quests[q],0xc8+24*f);names.data=(Wide*)raw(8);new(names.data)Wide(keys[q]);names.count=q&&f==1?1:0;names.capacity=1;names.grow=2;names.pad=0x11335577;}
  if(q)completed->insert(Map::value_type(Wide(keys[q]),true));}
 at<void*>(unit,0x18)=quests[0];at<void*>(unit,0x20)=marker;at<unsigned>(unit,0x10)=42;at<unsigned>(unit,0x38)=2;at<unsigned>(unit,0x3c)=cs->kind?1:2;at<unsigned>(unit,0x40)=1;at<unsigned>(unit,0x44)=22;at<void*>(unit,0x48)=0;at<unsigned>(unit,0x50)=at<unsigned>(unit,0x54)=0;at<unsigned char>(unit,0x60)=cs->kind?0:1;at<unsigned char>(unit,0x63)=0;at<unsigned>(unit,0xb4)=1;at<unsigned char>(unit,0xb9)=1;
 at<void*>(target,0x58)=0;at<void*>(target,0x68)=0;at<void*>(target,0x1b0)=marker;at<long long>(target,0x170)=at<long long>(quests[0],0x1c8);at<unsigned>(target,0x178)=42;
 for(Map::iterator i=completed->begin();i!=completed->end();++i){nodes[nodeCount].p=i._M_node;std::memcpy(nodes[nodeCount++].bytes,i._M_node,48);}arenaSize=(unsigned)autotest::g_arenaUsed;need(arenaSize<sizeof(expected));std::memcpy(expected,autotest::g_arena,arenaSize);
 for(unsigned i=0;i<2;++i)if(cs->kind)modelEvent(0,0);else need(modelComplete(0,cs->force!=0));
}
static long long complete(void*,bool);static void event(void*,unsigned,void*,void*);static void setter(void*,bool);static void notify(void*,unsigned,void*,void*);
// Each selected body executes with its own observer restored. A collaborating
// entry rearms all dispatch observers before allowing nested manager calls.
// Thus accepted manager code cannot silently select the replacement on the
// original lane, and the original lane remains genuine at every recursion.
static void arm(){TL_REDIRECT(*cp,qrrComplete,&complete);TL_REDIRECT(*ep,qrrEvent,&event);TL_REDIRECT(*sp,qrrSetter,&setter);TL_REDIRECT(*np,qrrNotify,&notify);}
static long long complete(void* self,bool force){arm();unsigned q=id(self);trace(false,CompleteIn,q,force);cp->restore();long long value=candidateSide?qrrNewComplete(self,force):qrrOldComplete(self,force);arm();trace(false,CompleteOut,q,(unsigned)value);return value;}
static void event(void* self,unsigned e,void* actor,void* t){arm();unsigned q=id(self);need(e==(q?4u:0u)&&actor==(q?0:player)&&t==(q?0:target));trace(false,EventIn,q,e);ep->restore();if(candidateSide)qrrNewEvent(self,e,actor,t);else qrrOldEvent(self,e,actor,t);arm();trace(false,EventOut,q,e);}
static void setter(void* self,bool value){arm();unsigned q=id(self);need(value);trace(false,SetterIn,q,value);sp->restore();qrrAcceptedSetter(self,value);arm();trace(false,SetterOut,q,value);}
static void notify(void* self,unsigned e,void* actor,void* t){arm();need(self==manager&&e==4&&!actor&&!t);++actualDepth;need(actualDepth<=3);if(actualDepth>6){--actualDepth;return;}trace(false,NotifyIn,99,e);np->restore();qrrAcceptedNotify(self,e,actor,t);arm();trace(false,NotifyOut,99,e);--actualDepth;}
static char done(void* self,const Wide& key){need(self==manager);unsigned q=1;for(;q<3;++q)if(&key==at<Names>(quests[q],0xe0).data)break;need(q<3);trace(false,Lookup,q,1);dp->restore();char result=qrrAcceptedDone(self,key);TL_REDIRECT(*dp,qrrDone,&done);need(result==1);return result;}
static bool unitComplete(void* self,bool force){need(self==unit&&!force);trace(false,UnitComplete,0,force);up->restore();bool result=reinterpret_cast<bool(*)(void*,bool)>(qrrUnitComplete_original)(self,force);TL_REDIRECT(*up,qrrUnitComplete,&unitComplete);return result;}
static unsigned long pickup(void* self,void* t){need(self==unit&&t==target);trace(false,Pickup,0,t?1:0);pp->restore();bool result=reinterpret_cast<bool(*)(void*,void*)>(qrrPickup_original)(self,t);TL_REDIRECT(*pp,qrrPickup,&pickup);return 0x100UL|(result?1UL:0UL);}
static void* getUI(){trace(false,UnexpectedUI);need(false);return ui;}static void refresh(void* self){need(self==ui);trace(false,UnexpectedUI,99,1);need(false);}
static void side(void* context,autotest::Capture& out,bool candidate){cs=(Case*)context;cap=&out;candidateSide=candidate;setup();
 {detour::Set completeSet,eventSet,setterSet,notifySet,doneSet,unitSet,pickupSet,uiSet;cp=&completeSet;ep=&eventSet;sp=&setterSet;np=&notifySet;dp=&doneSet;up=&unitSet;pp=&pickupSet;arm();TL_REDIRECT(doneSet,qrrDone,&done);TL_REDIRECT(unitSet,qrrUnitComplete,&unitComplete);TL_REDIRECT(pickupSet,qrrPickup,&pickup);TL_REDIRECT(uiSet,qrrUI,&getUI);TL_REDIRECT(uiSet,qrrRefresh,&refresh);
  if(completeSet.failed()||eventSet.failed()||setterSet.failed()||notifySet.failed()||doneSet.failed()||unitSet.failed()||pickupSet.failed()||uiSet.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(cs->kind){typedef void(*Fn)(void*,unsigned,void*,void*);Fn fn=candidate?&qrrNewEvent:&qrrOldEvent;if(!autotest::beginInvocation(out,fn))return;for(unsigned i=0;i<2;++i)fn(quests[0],0,player,target);}
  else {typedef long long(*Fn)(void*,bool);Fn fn=candidate?&qrrNewComplete:&qrrOldComplete;if(!autotest::beginInvocation(out,fn))return;for(unsigned i=0;i<2;++i){long long result=fn(quests[0],cs->force!=0);need(result==1);number((unsigned)result);}}out.callCompleted=1;
 }
 need(wanted==observed&&!actualDepth);if(std::memcmp(expected,autotest::g_arena,arenaSize)){for(unsigned i=0;i<arenaSize;++i)if(expected[i]!=(unsigned char)autotest::g_arena[i]){if(errors<4)std::fprintf(stderr,"    QRR byte mismatch arena+%x expected=%02x actual=%02x\n",i,expected[i],(unsigned char)autotest::g_arena[i]);need(false);break;}}
 cap->add(autotest::g_arena,arenaSize);for(unsigned i=0;i<nodeCount;++i)need(!std::memcmp(nodes[i].bytes,nodes[i].p,48));number(wanted);number(firstError);number(0x7152e711u);number(errors);
 for(unsigned q=0;q<3;++q){at<Wide>(quests[q],0x50).~Wide();for(unsigned f=0;f<2;++f)at<Names>(quests[q],0xc8+24*f).data->~Wide();}completed->~Map();
}
static void original(void* c,autotest::Capture& out){side(c,out,false);}static void candidate(void* c,autotest::Capture& out){side(c,out,true);}
static bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&o.capture.callCompleted&&tail[0]==0x7152e711u&&!tail[1];}
static int run(const tlhybrid_host* host,unsigned kind){autotest::Coverage cv(kind?"quest_runtime_reentrant_events":"quest_runtime_reentrant_completion",kind?0xd0ce90:0xd0cc10);unsigned n=0;
 for(unsigned deps=0;deps<3;++deps)for(unsigned force=0;force<(kind?1u:2u);++force)for(unsigned preloaded=0;preloaded<2;++preloaded){Case c={kind,deps,force,preloaded};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);++n;bool ok=good(a)&&good(b);if(cv.observe(host,a,b))ok=false;if(!ok){host->log("    quest runtime reentrant kind=%u deps=%u force=%u preloaded=%u status=%d/%d good=%u/%u issue=%u/%u\n",kind,deps,force,preloaded,a.childStatus,b.childStatus,good(a),good(b),a.capture.issue,b.capture.issue);cv.report(host);return 1;}}
 cv.report(host);return cv.completed!=n||cv.different||cv.missing;}
}
TL_TEST(quest_runtime_reentrant_completion){return qrr::run(host,0);}
TL_TEST(quest_runtime_reentrant_events){return qrr::run(host,1);}
