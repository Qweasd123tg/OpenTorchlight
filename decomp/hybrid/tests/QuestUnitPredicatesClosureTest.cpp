// Direct finite comparisons for CQuestUnitData isComplete/getIsRandom/save.
// Original ELF 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
// Draft only: no compiler or runtime was invoked while authoring.
// Construction/destruction and stdio are genuine. Save's isComplete dependency
// is explicitly original-bound; only the directly invoked helper receives credit.
#include <climits>
#include <cstdio>
#include <cstring>
#include <new>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "QuestUnitData.h"

#define QUPR_PAIR(R,N,A,S) TL_ORIGINAL(R,quprOld##N,A,S) extern "C" R quprNew##N A __asm__(S); TL_FUNCTION(quprTarget##N,S)
QUPR_PAIR(bool,Complete,(CQuestUnitData*,bool),"_ZN14CQuestUnitData10isCompleteEb")
QUPR_PAIR(bool,Random,(CQuestUnitData*),"_ZN14CQuestUnitData11getIsRandomEv")
QUPR_PAIR(void,Save,(CQuestUnitData*,FILE*),"_ZN14CQuestUnitData4saveEP8_IO_FILE")
#undef QUPR_PAIR
TL_ORIGINAL(void,quprCtor,(void*,void*),"_ZN14CQuestUnitDataC1EP6CQuest")
TL_ORIGINAL(void,quprDtor,(void*),"_ZN14CQuestUnitDataD1Ev")
extern "C" char quprWrite[] __asm__("fwrite");

namespace qupr {
typedef std::wstring Wide;
enum { Nodes=6, MaxEvents=256, MaxBytes=2048 };
typedef char ABI[sizeof(Wide)==8 && sizeof(wchar_t)==4 && sizeof(CQuestUnitData)==0xc8 && sizeof(bool)==1 && sizeof(int)==4 ? 1 : -1];
template<class T>T& at(void*p,unsigned o){return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
enum Mode { Plain, CopyComplete, CopyTrack, CopyRequired, AliasCurrent,
    CopyID, AliasGuid, HeaderShrink, HeaderGrow, HeaderZeroGrow,
    ChildShrink, ChildGrow, ChildCapacity, RefreshTrack, RefreshRequired,
    RefreshID, RefreshGuid };
struct Node {
 bool complete,track;unsigned required,current,id,count,capacity,child[3];
 unsigned long long guid;int minimum,maximum;unsigned text;
 Node():complete(true),track(false),required(0),current(0),id(0),count(0),capacity(3),guid(0),minimum(1),maximum(1),text(0){child[0]=child[1]=child[2]=5;}
};
struct Case {
 unsigned entry,shape,mask,variant,selected,mode,shortAt,prefix,repeats;bool flag;
 Case():entry(0),shape(0),mask(63),variant(0),selected(0),mode(Plain),shortAt(0),prefix(0),repeats(1),flag(false){}
};
struct Event {unsigned node,field,width,taken;unsigned char bytes[8];};
static const Case* cs;static autotest::Capture* cap;
static CQuestUnitData* unit[Nodes];static unsigned char* blocks[Nodes];
static unsigned char before[Nodes][0xc8];static Node initial[Nodes],model[Nodes];
static Event expected[MaxEvents];static unsigned eventCount,eventIndex,errors,firstError,expectedLength,writeCalls;
static unsigned char expectedBytes[MaxBytes];static FILE* stream;static detour::Set* writer;
static void check(bool ok,unsigned line){if(!ok){if(!errors)firstError=line;++errors;}}
#define NEED(x) check((x),__LINE__)
static void n(unsigned value){cap->add(&value,sizeof(value));}
static void le(unsigned char* p,unsigned long long value,unsigned width){for(unsigned i=0;i<width;++i)p[i]=static_cast<unsigned char>(value>>(8*i));}
static Wide text(unsigned kind){
 if(!kind)return Wide();if(kind==1)return L"SPAWN";if(kind==2)return Wide(1,wchar_t(0));
 if(kind==3){const wchar_t p[]={L'A',0,L'B'};return Wide(p,3);}return Wide(257,L'Z');
}
static unsigned child(const Node& node,unsigned index){return node.child[index<node.capacity?index:0];}
static bool completion(const Node* nodes,unsigned index,bool flag,unsigned depth=0){
 if(depth>=Nodes){NEED(false);return false;}const Node& x=nodes[index];if(!x.complete)return false;if(flag)return true;
 for(unsigned i=0;i<x.count;++i){if(i>=3){NEED(false);return false;}if(!completion(nodes,child(x,i),false,depth+1))return false;}return true;
}
static bool random(const Node* nodes,unsigned index,unsigned depth=0){
 if(depth>=Nodes){NEED(false);return false;}const Node& x=nodes[index];if(x.minimum!=x.maximum||x.text)return true;
 for(unsigned i=0;i<x.count;++i){if(i>=3){NEED(false);return false;}if(random(nodes,child(x,i),depth+1))return true;}return false;
}
static void configure(){
 for(unsigned i=0;i<Nodes;++i){initial[i]=Node();Node& x=initial[i];x.complete=(cs->mask&(1u<<i))!=0;x.track=((i+cs->variant)&1)!=0;
  x.required=0x11223340u+i;x.current=0x8899aa10u+i;x.id=0xff000100u+i;x.guid=0x8192a3b4c5d6e700ULL+i;
 }
 initial[0].child[0]=1;initial[0].child[1]=2;initial[0].child[2]=3;
 for(unsigned i=1;i<4;++i){initial[i].child[0]=4;initial[i].child[1]=5;initial[i].child[2]=5;}
 initial[4].child[0]=5;
 if(cs->shape==1){initial[0].count=3;initial[1].count=2;}
 if(cs->shape==2){for(unsigned i=0;i<5;++i){initial[i].count=1;initial[i].child[0]=i+1;}}
 if(cs->shape==3){initial[0].count=3;initial[0].capacity=1;initial[1].count=2;}
 if(cs->shape==4){initial[0].count=3;initial[0].capacity=2;initial[2].count=2;}
 if(cs->shape==5){initial[0].count=1;initial[1].count=2;}
 if(cs->entry==1){Node& x=initial[cs->selected];
  if(cs->variant==1){x.minimum=INT_MIN;x.maximum=INT_MAX;}
  if(cs->variant==2){x.minimum=INT_MAX;x.maximum=INT_MIN;}
  if(cs->variant==3)x.minimum=x.maximum=INT_MIN;
  if(cs->variant>=4)x.text=cs->variant-3;
 }
 if(cs->mode>=HeaderShrink){initial[0].count=cs->mode==HeaderZeroGrow?0:cs->mode==HeaderGrow||cs->mode==ChildGrow?1:3;initial[1].count=0;}
}
static void setup(){
 errors=firstError=eventCount=eventIndex=expectedLength=writeCalls=0;autotest::g_arenaUsed=0;stream=0;
 // The only game TU static needed by the genuine original constructor.
 ::new(reinterpret_cast<void*>(0x14ff1a8))Wide();configure();
 for(unsigned i=0;i<Nodes;++i){
  blocks[i]=static_cast<unsigned char*>(autotest::allocate(0xc8+32));if(!blocks[i]){cap->issue=autotest::Capture::InvalidReport;return;}
  std::memset(blocks[i],0xa6,16);std::memset(blocks[i]+16+0xc8,0x6a,16);unit[i]=reinterpret_cast<CQuestUnitData*>(blocks[i]+16);quprCtor(unit[i],0);
 }
 for(unsigned i=0;i<Nodes;++i){const Node& x=initial[i];CQuestUnitData* u=unit[i];
  u->m_completed=x.complete;u->m_trackUnitEvents=x.track;at<unsigned>(u,0x38)=x.required;at<unsigned>(u,0x3c)=x.current;at<unsigned>(u,0x10)=x.id;at<unsigned long long>(u,0x30)=x.guid;
  u->m_minCount=x.minimum;u->m_maxCount=x.maximum;u->m_spawnClass=text(x.text);
  // Backing storage is genuinely TArrayList-owned; every possible child is live.
  for(unsigned j=0;j<3;++j)u->m_children.add(unit[x.child[j]]);
  at<unsigned>(u,0x50)=x.count;at<unsigned>(u,0x54)=x.capacity;
  std::memcpy(before[i],u,0xc8);model[i]=x;
 }
}
// A callback may mutate ordinary fields/list metadata while fwrite is executing.
// All backing arrays remain large enough; no null, dangling, or cyclic child is used.
static void mutate(Node* nodes,unsigned occurrence){
 Node& root=nodes[0];
 if(cs->mode==CopyComplete&&occurrence==1)root.complete=false;
 if(cs->mode==CopyTrack&&occurrence==2)root.track=!root.track;
 if(cs->mode==CopyRequired&&occurrence==3)root.required=0x76543210u;
 if(cs->mode==AliasCurrent&&occurrence==4)root.current=0xabcdef01u;
 if(cs->mode==CopyID&&occurrence==5)root.id=0x12345678u;
 if(cs->mode==AliasGuid&&occurrence==6)root.guid=0xfedcba9876543210ULL;
 if(cs->mode==HeaderShrink&&occurrence==7)root.count=0;
 if((cs->mode==HeaderGrow||cs->mode==HeaderZeroGrow)&&occurrence==7)root.count=3;
 if(cs->mode==ChildShrink&&occurrence==8)root.count=1;
 if(cs->mode==ChildGrow&&occurrence==8)root.count=3;
 if(cs->mode==ChildCapacity&&occurrence==8)root.capacity=1;
 if(cs->mode==RefreshTrack&&occurrence==1)root.track=!root.track;
 if(cs->mode==RefreshRequired&&occurrence==2)root.required=0x76543210u;
 if(cs->mode==RefreshID&&occurrence==4)root.id=0x12345678u;
 if(cs->mode==RefreshGuid&&occurrence==5)root.guid=0xfedcba9876543210ULL;
}
static void applyMutation(unsigned occurrence){
 Node changed[Nodes];for(unsigned i=0;i<Nodes;++i){changed[i]=initial[i];Node& x=changed[i];CQuestUnitData* u=unit[i];
  x.complete=u->m_completed;x.track=u->m_trackUnitEvents;x.required=at<unsigned>(u,0x38);x.current=at<unsigned>(u,0x3c);x.id=at<unsigned>(u,0x10);x.guid=at<unsigned long long>(u,0x30);x.count=at<unsigned>(u,0x50);x.capacity=at<unsigned>(u,0x54);
 }
 // Apply only this callback's changes to the actual current state. Never
 // overwrite an unexpected candidate change with oracle state.
 mutate(changed,occurrence);
 for(unsigned i=0;i<Nodes;++i){Node& x=changed[i];CQuestUnitData* u=unit[i];
  u->m_completed=x.complete;u->m_trackUnitEvents=x.track;at<unsigned>(u,0x38)=x.required;at<unsigned>(u,0x3c)=x.current;at<unsigned>(u,0x10)=x.id;at<unsigned long long>(u,0x30)=x.guid;
  at<unsigned>(u,0x50)=x.count;at<unsigned>(u,0x54)=x.capacity;
 }
}
static void expectWrite(unsigned index,unsigned field,unsigned width,unsigned long long copied,bool alias){
 if(eventCount>=MaxEvents){cap->issue=autotest::Capture::Overflow;return;}
 Event& e=expected[eventCount++];e.node=index;e.field=field;e.width=width;e.taken=cs->shortAt==eventCount?0:width;
 mutate(model,eventCount);unsigned long long value=alias?(field==4?model[index].current:model[index].guid):copied;le(e.bytes,value,width);
 if(expectedLength+e.taken>MaxBytes){cap->issue=autotest::Capture::Overflow;return;}
 std::memcpy(expectedBytes+expectedLength,e.bytes,e.taken);expectedLength+=e.taken;
}
static void saveModel(unsigned index,unsigned depth=0){
 if(depth>=Nodes){NEED(false);return;}Node& x=model[index];
 expectWrite(index,1,1,completion(model,index,false),false);
 expectWrite(index,2,1,x.track,false);expectWrite(index,3,4,x.required,false);
 expectWrite(index,4,4,x.current,true);expectWrite(index,5,4,x.id,false);expectWrite(index,6,8,x.guid,true);
 unsigned savedCount=x.count;expectWrite(index,7,4,savedCount,false);
 if(savedCount)for(unsigned i=0;i<x.count;++i){if(i>=3){NEED(false);return;}saveModel(child(x,i),depth+1);}
}
static size_t writeObserved(const void* data,size_t width,size_t count,FILE* f){
 ++writeCalls;NEED(f==stream);NEED(eventIndex<eventCount);NEED(count==1);NEED(width<=8);
 if(eventIndex>=eventCount||width>8){cap->issue=autotest::Capture::InvalidReport;return 0;}
 const Event& e=expected[eventIndex++];applyMutation(eventIndex);
 n(e.node);n(e.field);n(static_cast<unsigned>(width));n(static_cast<unsigned>(count));
 if(width<=8)cap->add(data,width);
 NEED(width==e.width);if(width==e.width)NEED(!std::memcmp(data,e.bytes,width));
 // Copied scalar vs direct-member pointer is independently checked. The
 // original uses direct aliases only for current count and the 64-bit GUID.
 const void* alias=e.field==4?static_cast<const void*>(&unit[e.node]->m_currentUnitCount):e.field==6?static_cast<const void*>(&unit[e.node]->m_baseUnitGuid):0;
 if(alias)NEED(data==alias);else for(unsigned i=0;i<Nodes;++i)NEED(!(reinterpret_cast<uintptr_t>(data)>=reinterpret_cast<uintptr_t>(unit[i])&&reinterpret_cast<uintptr_t>(data)<reinterpret_cast<uintptr_t>(unit[i])+0xc8));
 writer->restore();size_t result=0;
 if(e.taken)result=std::fwrite(data,width,count,f); // Genuine FILE operation.
 writer->redirect(quprWrite,quprWrite,&writeObserved);NEED(!writer->failed());
 NEED(result==(e.taken?1u:0u));n(static_cast<unsigned>(result));return result;
}
static void verifyObjects(bool save){
 for(unsigned i=0;i<Nodes;++i){unsigned char want[0xc8];std::memcpy(want,before[i],0xc8);const Node& x=save?model[i]:initial[i];
  if(save){at<bool>(want,0x60)=x.complete;at<bool>(want,0xb9)=x.track;at<unsigned>(want,0x38)=x.required;at<unsigned>(want,0x3c)=x.current;at<unsigned>(want,0x10)=x.id;at<unsigned long long>(want,0x30)=x.guid;at<unsigned>(want,0x50)=x.count;at<unsigned>(want,0x54)=x.capacity;}
  NEED(!std::memcmp(unit[i],want,0xc8));
  n(unit[i]->m_completed);n(unit[i]->m_trackUnitEvents);n(at<unsigned>(unit[i],0x38));n(at<unsigned>(unit[i],0x3c));n(at<unsigned>(unit[i],0x10));cap->add(&unit[i]->m_baseUnitGuid,8);n(at<unsigned>(unit[i],0x50));n(at<unsigned>(unit[i],0x54));
  cap->addText(unit[i]->m_spawnClass);NEED(unit[i]->m_spawnClass==text(initial[i].text));
  CQuestUnitData** values=at<CQuestUnitData**>(unit[i],0x48);for(unsigned j=0;j<3;++j)NEED(values[j]==unit[initial[i].child[j]]);
 }
}
static void cleanup(){
 for(unsigned i=0;i<Nodes;++i)unit[i]->m_children.clear();
 for(unsigned i=0;i<Nodes;++i){quprDtor(unit[i]);for(unsigned j=0;j<16;++j){NEED(blocks[i][j]==0xa6);NEED(blocks[i][16+0xc8+j]==0x6a);}}
}
static void side(void* p,autotest::Capture& out,bool candidate){
 cs=static_cast<Case*>(p);cap=&out;setup();if(out.issue)return;
 {
  detour::Set route,dependency,io;writer=&io;
  if(cs->entry==0){if(candidate)route.redirect(quprTargetComplete_original,quprTargetComplete_original,&quprNewComplete);
   typedef bool(*Fn)(CQuestUnitData*,bool);Fn fn=candidate?&quprNewComplete:&quprOldComplete;
   if(route.failed()||!autotest::beginInvocation(out,fn)){out.issue=autotest::Capture::InvalidReport;return;}
   bool want=completion(initial,0,cs->flag);for(unsigned i=0;i<cs->repeats;++i){bool value=fn(unit[0],cs->flag);n(value);NEED(value==want);}out.callCompleted=1;
  }else if(cs->entry==1){if(candidate)route.redirect(quprTargetRandom_original,quprTargetRandom_original,&quprNewRandom);
   typedef bool(*Fn)(CQuestUnitData*);Fn fn=candidate?&quprNewRandom:&quprOldRandom;
   if(route.failed()||!autotest::beginInvocation(out,fn)){out.issue=autotest::Capture::InvalidReport;return;}
   bool want=random(initial,0);for(unsigned i=0;i<cs->repeats;++i){bool value=fn(unit[0]);n(value);NEED(value==want);}out.callCompleted=1;
  }else{
   // Explicitly isolate the dependency so an isComplete mutant only fails its
   // own named test. Original entry and recursive original calls remain intact.
   if(quprTargetComplete_linked!=quprTargetComplete_original)dependency.redirect(quprTargetComplete_linked,quprTargetComplete_linked,&quprOldComplete);
   if(candidate)route.redirect(quprTargetSave_original,quprTargetSave_original,&quprNewSave);
   for(unsigned repeat=0;repeat<cs->repeats;++repeat)saveModel(0);
   stream=std::tmpfile();if(!stream){out.issue=autotest::Capture::InvalidReport;return;}
   unsigned char prefix[17];for(unsigned i=0;i<17;++i)prefix[i]=static_cast<unsigned char>(0xc0+i);
   if(cs->prefix)NEED(std::fwrite(prefix,1,17,stream)==17);
   io.redirect(quprWrite,quprWrite,&writeObserved);
   typedef void(*Fn)(CQuestUnitData*,FILE*);Fn fn=candidate?&quprNewSave:&quprOldSave;
   if(route.failed()||dependency.failed()||io.failed()||!autotest::beginInvocation(out,fn)){out.issue=autotest::Capture::InvalidReport;return;}
   for(unsigned repeat=0;repeat<cs->repeats;++repeat)fn(unit[0],stream);out.callCompleted=1;
   io.restore();NEED(eventIndex==eventCount);NEED(writeCalls==eventCount);NEED(std::fflush(stream)==0);
   long position=std::ftell(stream);NEED(position==static_cast<long>(expectedLength+(cs->prefix?17:0)));n(static_cast<unsigned>(position));NEED(!std::ferror(stream));
   NEED(std::fseek(stream,0,SEEK_SET)==0);unsigned char actual[MaxBytes+17];size_t length=std::fread(actual,1,sizeof(actual),stream);
   NEED(length==expectedLength+(cs->prefix?17:0));if(cs->prefix)NEED(!std::memcmp(actual,prefix,17));
   if(length==expectedLength+(cs->prefix?17:0))NEED(!std::memcmp(actual+(cs->prefix?17:0),expectedBytes,expectedLength));
   n(static_cast<unsigned>(length));cap->add(actual,length);NEED(std::feof(stream)!=0);NEED(!std::ferror(stream));NEED(std::fclose(stream)==0);stream=0;
  }
  NEED(!route.failed()&&!dependency.failed()&&!io.failed());
 }
 verifyObjects(cs->entry==2);cleanup();n(firstError);n(0x51555052u);n(errors);
}
static void oldSide(void* p,autotest::Capture& o){side(p,o,false);}static void newSide(void* p,autotest::Capture& o){side(p,o,true);}
static bool good(const autotest::Outcome& o){unsigned end[2]={0,1};if(o.capture.length>=8)std::memcpy(end,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&end[0]==0x51555052u&&!end[1];}
static unsigned line(const autotest::Outcome& o){unsigned value=0;if(o.capture.length>=12)std::memcpy(&value,o.capture.data+o.capture.length-12,4);return value;}
static bool pair(const tlhybrid_host* host,autotest::Coverage& coverage,Case& c,unsigned& completed){
 autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);++completed;
 bool equal=coverage.observe(host,a,b)==0;bool ok=equal&&good(a)&&good(b);
 if(!ok){host->log("    unit helper entry=%u shape=%u mask=%u variant=%u selected=%u mode=%u short=%u status=%d/%d oracle=%u/%u line=%u/%u\n",c.entry,c.shape,c.mask,c.variant,c.selected,c.mode,c.shortAt,a.childStatus,b.childStatus,good(a),good(b),line(a),line(b));coverage.report(host);}return ok;
}
#undef NEED
}
TL_TEST(quest_unit_complete_closure){using namespace qupr;autotest::Coverage coverage("quest_unit_complete_closure",0xd3dd20);unsigned completed=0;
 // A grandchild-only false result is first: recursion cannot borrow original code.
 Case deep;deep.shape=2;deep.mask=31;if(!pair(host,coverage,deep,completed))return 1;
 const unsigned masks[]={0,63,62,61,59,55,47,31,21};
 for(unsigned shape=0;shape<6;++shape)for(unsigned flag=0;flag<2;++flag)for(unsigned k=0;k<9;++k){Case c;c.shape=shape;c.flag=flag;c.mask=masks[k];c.repeats=2;if(!pair(host,coverage,c,completed))return 1;}
 coverage.report(host);return completed!=109||coverage.completed!=completed||coverage.different||coverage.missing;
}
TL_TEST(quest_unit_random_closure){using namespace qupr;autotest::Coverage coverage("quest_unit_random_closure",0xd45ac0);unsigned completed=0;
 Case deep;deep.entry=1;deep.shape=2;deep.selected=5;deep.variant=1;if(!pair(host,coverage,deep,completed))return 1;
 for(unsigned shape=0;shape<6;++shape)for(unsigned selected=0;selected<6;++selected)for(unsigned variant=0;variant<8;++variant){Case c;c.entry=1;c.shape=shape;c.selected=selected;c.variant=variant;c.repeats=2;if(!pair(host,coverage,c,completed))return 1;}
 coverage.report(host);return completed!=289||coverage.completed!=completed||coverage.different||coverage.missing;
}
TL_TEST(quest_unit_save_closure){using namespace qupr;autotest::Coverage coverage("quest_unit_save_closure",0xd3dda0);unsigned completed=0;
 Case deep;deep.entry=2;deep.shape=2;deep.mask=31;if(!pair(host,coverage,deep,completed))return 1;
 const unsigned masks[]={0,63,62,61,47,31};
 for(unsigned shape=0;shape<6;++shape)for(unsigned k=0;k<6;++k){Case c;c.entry=2;c.shape=shape;c.mask=masks[k];c.variant=k;c.prefix=k&1;c.repeats=2;if(!pair(host,coverage,c,completed))return 1;}
 for(unsigned mode=1;mode<=RefreshGuid;++mode){Case c;c.entry=2;c.shape=1;c.mode=mode;c.prefix=1;if(!pair(host,coverage,c,completed))return 1;}
 // Ignored short fwrite results still finish all remaining writes/descendants.
 for(unsigned at=1;at<=14;++at){Case c;c.entry=2;c.shape=1;c.shortAt=at;if(!pair(host,coverage,c,completed))return 1;}
 coverage.report(host);return completed!=67||coverage.completed!=completed||coverage.different||coverage.missing;
}
