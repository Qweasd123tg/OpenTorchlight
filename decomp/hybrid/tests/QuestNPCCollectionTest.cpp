// Independent oracle for CQuest::getAllNPCUnitDataInvolvedInQuest, d15210.
// Original-derived fixture, GCC 4.4.7/C++98 and old COW ABI. No definition parser,
// save path, GUID loader, resource files, or imported code is used.
// Genuine lanes run original Quest/Dialog/DataGroup constructors/destructors.
// Bounded synthetic lanes are explicitly separated below. Allocation observers
// execute real new[]/delete[]; only new unused pointer slots receive a known
// poison value. Fault cases throw bad_alloc at the actual allocation boundary.
#include <cstdio>
#include <cstring>
#include <new>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "Quest.h"
#include "QuestDialog.h"
#include "DataGroup.h"
#include "TRepository.h"
TL_ORIGINAL(void,qncOld,(void*,TArrayList<CDataGroup*>&),"_ZN6CQuest32getAllNPCUnitDataInvolvedInQuestER10TArrayListIP10CDataGroupE")
extern "C" void qncNew(void*,TArrayList<CDataGroup*>&) __asm__("_ZN6CQuest32getAllNPCUnitDataInvolvedInQuestER10TArrayListIP10CDataGroupE");
TL_ORIGINAL(void,qncQuestCtor,(void*,void*,void*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void,qncQuestDtor,(void*),"_ZN6CQuestD1Ev")
TL_ORIGINAL(void,qncDialogCtor,(void*,void*),"_ZN12CQuestDialogC1EP6CQuest")
TL_ORIGINAL(void,qncDialogDtor,(void*),"_ZN12CQuestDialogD1Ev")
TL_ORIGINAL(void,qncResourceCtor,(void*,void*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,qncResourceDtor,(void*),"_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void,qncGroupCtor,(void*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,qncGroupDtor,(void*),"_ZN10CDataGroupD1Ev")
extern "C" char qncArrayNew[] __asm__("_Znam");
extern "C" char qncArrayDelete[] __asm__("_ZdaPv");
namespace quest_npc_collection_fixture {
typedef std::wstring Wide;
typedef TArrayList<CQuestDialog*> Dialogs;
typedef TArrayList<CDataGroup*> Output;
struct View {void** data;unsigned count,capacity,grow,pad;};
typedef char ABI[sizeof(Wide)==8&&sizeof(View)==24&&sizeof(Output)==24&&sizeof(CQuest)==0x218&&sizeof(CQuestDialog)==0xa8&&sizeof(CDataGroup)==0x60?1:-1];
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
struct Case {unsigned lane,shape,mode,repeat,fault;}; // lane 0 genuine, 1 synthetic, 2 bad_alloc
struct Guard {unsigned char* data;unsigned size;};
struct Block {void* pointer;unsigned id,size,freed;};
struct Event {unsigned kind,bytes,block,count,capacity,grow,storage;};
static const Case* cs;static autotest::Capture* cap;
static void* quest;static void* resource;static CQuestDialog* dialogs[40];static unsigned dialogCount;
static CDataGroup* groups[16];static Output* output;
static Guard guards[80];static unsigned guardCount;
static Block blocks[48];static unsigned blockCount;
static Event events[128],wantedEvents[128];static unsigned eventCount,wantedEventCount;
static unsigned errors,firstError,allocations,deletions,faultHits,mutationHits;
static unsigned encounter[48],encounterCount,wanted[64],wantedCount,wantedCapacity,wantedGrow,wantedStorage,wantedStorageBytes;
static unsigned expectedAllocations,expectedDeletions,expectedCaught;
static unsigned char questBefore[0x218],dialogBefore[40][0xa8],groupBefore[15][0x60];
static CQuestDialog* sourceBefore[4][16];static unsigned sourceBacking[4];
static detour::Set *newPatch,*deletePatch;
static const unsigned offsets[]={0x60,0x78,0x90,0xa8};
static void n(unsigned v){cap->add(&v,sizeof(v));}
static void check(bool yes,unsigned line){if(!yes){if(!errors)firstError=line;++errors;}}
#define need(x) check((x),__LINE__)
static void* memory(unsigned bytes){unsigned char* p=static_cast<unsigned char*>(autotest::allocate(bytes+32));if(!p)_exit(71);std::memset(p,0xce,bytes+32);std::memset(p+16,0xa5,bytes);need(guardCount<80);guards[guardCount].data=p;guards[guardCount++].size=bytes;return p+16;}
static View& view(void* list){return *static_cast<View*>(list);}
static View& destination(){return view(output);}
static Dialogs& source(unsigned family){return at<Dialogs>(quest,offsets[family]);}
static unsigned groupId(void* p){if(!p)return 0;for(unsigned i=1;i<16;++i)if(groups[i]==p)return i;need(false);return 0xffff;}
static Block* block(void* pointer){for(unsigned i=blockCount;i;--i)if(blocks[i-1].pointer==pointer&&!blocks[i-1].freed)return &blocks[i-1];return 0;}
static unsigned storageId(void* p){if(!p)return 0;Block* b=block(p);need(b!=0);return b?b->id:0xffff;}
static void remember(void* p,unsigned id,unsigned bytes){need(blockCount<48);if(blockCount<48){Block& b=blocks[blockCount++];b.pointer=p;b.id=id;b.size=bytes;b.freed=0;}}
static void event(unsigned kind,unsigned bytes,unsigned id){need(eventCount<128);if(eventCount<128){Event& e=events[eventCount++];e.kind=kind;e.bytes=bytes;e.block=id;e.count=destination().count;e.capacity=destination().capacity;e.grow=destination().grow;e.storage=storageId(destination().data);}}
static void expectedEvent(unsigned kind,unsigned bytes,unsigned id,unsigned count,unsigned capacity,unsigned storage){need(wantedEventCount<128);if(wantedEventCount<128){Event& e=wantedEvents[wantedEventCount++];e.kind=kind;e.bytes=bytes;e.block=id;e.count=count;e.capacity=capacity;e.grow=wantedGrow;e.storage=storage;}}
static void* allocate(size_t bytes){
 ++allocations;event(1,static_cast<unsigned>(bytes),allocations+1);
 // The source count can change at a callout. These two finite, fully backed
 // cases distinguish reload-after-call from a hoisted initial loop bound.
 if(cs->lane==1&&allocations==1&&(cs->shape==6||cs->shape==7)){
  at<unsigned>(&source(0),8)=cs->shape==6?3:0;++mutationHits;event(3,at<unsigned>(&source(0),8),0);
 }
 if(cs->fault&&allocations==cs->fault){++faultHits;throw std::bad_alloc();}
 need(bytes&&bytes%sizeof(void*)==0&&bytes<=64*sizeof(void*));
 newPatch->restore();void* p=reinterpret_cast<void*(*)(size_t)>(qncArrayNew)(bytes);
 newPatch->redirect(qncArrayNew,qncArrayNew,&allocate);need(!newPatch->failed());
 remember(p,allocations+1,static_cast<unsigned>(bytes));
 // Defined reads of copied and untouched capacity. This does not fabricate
 // successful allocation, suppress a free, or replace any source object.
 for(unsigned i=0;i<bytes/sizeof(void*);++i)static_cast<void**>(p)[i]=groups[15];
 return p;
}
static void release(void* p){
 Block* b=block(p);need(b!=0);event(2,b?b->size:0,b?b->id:0xffff);++deletions;if(b)++b->freed;
 deletePatch->restore();reinterpret_cast<void(*)(void*)>(qncArrayDelete)(p);deletePatch->redirect(qncArrayDelete,qncArrayDelete,&release);need(!deletePatch->failed());
}
static void statics(){
 const unsigned cells[]={0x14f9fe8,0x151d408,0x14fb488,0x14ff1a8,0x151c128,0x151ab48,0x14dd9c8,0x14dd9d8,0x14dda88};
 for(unsigned i=0;i<sizeof(cells)/sizeof(cells[0]);++i)new(reinterpret_cast<void*>(cells[i]))Wide();
 new(reinterpret_cast<void*>(0x14dd9c0))std::string();::new(reinterpret_cast<void*>(0x14dd9e0))TRepository<Wide>(Wide());
}
static CQuestDialog* dialog(unsigned group){
 need(dialogCount<40);CQuestDialog* d=static_cast<CQuestDialog*>(memory(sizeof(CQuestDialog)));dialogs[dialogCount++]=d;
 if(cs->lane!=1)qncDialogCtor(d,quest);else std::memset(d,0,sizeof(CQuestDialog));
 at<CDataGroup*>(d,0x68)=groups[group];return d;
}
static void add(unsigned family,unsigned group){source(family).add(dialog(group));}
static void truth(const unsigned* ids,unsigned count){need(count<=48);encounterCount=count;for(unsigned i=0;i<count;++i)encounter[i]=ids[i];}
static void setupSources(){
 const unsigned abc[]={1,2,3};
 if(cs->lane==1){
  if(cs->shape<4){unsigned f=cs->shape;add(f,1);add(f,2);add(f,3);at<unsigned>(&source(f),12)=cs->mode?0:1;const unsigned only[]={1};truth(only,1);return;}
  if(cs->shape==4){for(unsigned f=0;f<4;++f){add(f,1+3*f);add(f,2+3*f);add(f,3+3*f);at<unsigned>(&source(f),12)=cs->mode?0:2;}const unsigned six[]={1,2,4,5,7,8,10,11};const unsigned four[]={1,4,7,10};truth(cs->mode?four:six,cs->mode?4:8);return;}
  if(cs->shape==5){add(0,3);add(1,4);add(2,5);const unsigned special[]={3,4,5};truth(special,3);return;}
  add(0,1);add(0,2);add(0,3);at<unsigned>(&source(0),8)=cs->shape==6?1:3;truth(abc,cs->shape==6?3:1);return;
 }
 unsigned shape=cs->lane==2?9:cs->shape;
 if(shape==0){truth(abc,0);return;}
 if(shape<=4){unsigned f=shape-1;add(f,1);add(f,0);add(f,2);add(f,1);add(f,3);truth(abc,3);return;}
 if(shape==5){
  const unsigned ids[4][4]={{4,0,2,4},{7,2,1,0},{0,1,6,4},{5,7,3,5}};
  for(unsigned f=0;f<4;++f)for(unsigned i=0;i<4;++i)add(f,ids[f][i]);const unsigned answer[]={4,2,7,1,6,5,3};truth(answer,7);return;
 }
 if(shape==6){for(unsigned f=0;f<4;++f){add(f,0);add(f,0);}truth(abc,0);return;}
 if(shape==7){add(0,1);add(1,2);add(2,1);add(3,3);truth(abc,3);return;}
 if(shape==8){CQuestDialog* same=dialog(4);for(unsigned f=0;f<4;++f){source(f).add(same);source(f).add(same);}add(3,5);const unsigned answer[]={4,5};truth(answer,2);return;}
 if(shape==9){for(unsigned f=0;f<4;++f)for(unsigned i=0;i<3;++i)add(f,12-3*f-i);const unsigned answer[]={12,11,10,9,8,7,6,5,4,3,2,1};truth(answer,12);return;}
 if(shape==10){for(unsigned f=0;f<4;++f){add(f,2+3*f);add(f,1+3*f);add(f,3+3*f);add(f,2+3*f);add(f,0);add(f,1+3*f);}const unsigned answer[]={2,1,3,5,4,6,8,7,9,11,10,12};truth(answer,12);return;}
 need(false);
}
static void setupDestination(){
 unsigned mode=cs->lane==1?0:cs->mode;unsigned count=0,capacity=0,grow=1;const unsigned seedA[]={0,2,2,9};const unsigned seedB[]={3,0,3,1,12};const unsigned* seeds=seedA;
 if(mode==1)grow=3;if(mode==2){capacity=16;grow=5;}if(mode==3){count=capacity=4;grow=3;}if(mode==4){count=4;capacity=16;grow=2;}if(mode==5){count=capacity=5;grow=1;seeds=seedB;}
 unsigned backing=capacity;
 if(cs->lane==1&&cs->shape==5){count=4;capacity=2;backing=4;grow=5;}
 output=::new(memory(sizeof(Output)))Output(grow);
 if(backing){CDataGroup** p=new CDataGroup*[backing];for(unsigned i=0;i<backing;++i)p[i]=groups[15];for(unsigned i=0;i<count;++i)p[i]=groups[cs->lane==1?i+1:seeds[i]];at<void*>(output,0)=p;remember(p,1,backing*sizeof(void*));}
 destination().count=count;destination().capacity=capacity;destination().grow=grow;
 wantedCount=count;wantedCapacity=capacity;wantedGrow=grow;wantedStorage=backing?1:0;wantedStorageBytes=backing*sizeof(void*);
 for(unsigned i=0;i<64;++i)wanted[i]=15;for(unsigned i=0;i<count;++i)wanted[i]=groupId(destination().data[i]);
}
static void plan(){
 // Golden encounter order is supplied independently of the object lists.
 // A bit set expresses pointer membership; pre-existing duplicates/nulls stay.
 unsigned seen=0;for(unsigned i=0;i<wantedCount;++i)seen|=1u<<wanted[i];
 for(unsigned i=0;i<encounterCount;++i){unsigned id=encounter[i];if(!id||(seen&(1u<<id)))continue;
  if(wantedCount>=wantedCapacity){
   unsigned oldCapacity=wantedCapacity,newCapacity=wantedStorage?wantedCapacity+wantedGrow:wantedGrow;
   if(!wantedStorage)wantedCapacity=wantedGrow;
   ++expectedAllocations;expectedEvent(1,newCapacity*sizeof(void*),expectedAllocations+1,wantedCount,wantedCapacity,wantedStorage);
   if(cs->lane==1&&expectedAllocations==1&&(cs->shape==6||cs->shape==7))expectedEvent(3,cs->shape==6?3:0,0,wantedCount,wantedCapacity,wantedStorage);
   if(cs->fault==expectedAllocations){expectedCaught=1;return;}
   if(wantedStorage){expectedEvent(2,wantedStorageBytes,wantedStorage,wantedCount,wantedCapacity,wantedStorage);++expectedDeletions;}
   // For the explicitly malformed-but-backed synthetic destination, entries
   // between old capacity and old count are intentionally NOT copied by ELF.
   for(unsigned slot=oldCapacity;slot<newCapacity;++slot)wanted[slot]=15;
   wantedCapacity=newCapacity;wantedStorage=expectedAllocations+1;wantedStorageBytes=newCapacity*sizeof(void*);
  }
  need(wantedCount<wantedCapacity&&wantedCount<64);wanted[wantedCount++]=id;seen|=1u<<id;
 }
}
static void snapshots(){
 std::memcpy(questBefore,quest,sizeof(questBefore));
 for(unsigned i=0;i<dialogCount;++i)std::memcpy(dialogBefore[i],dialogs[i],sizeof(CQuestDialog));
 for(unsigned i=1;i<16;++i)std::memcpy(groupBefore[i-1],groups[i],sizeof(CDataGroup));
 for(unsigned f=0;f<4;++f){View& s=view(&source(f));
  // Every populated source started as a real add-created allocation of >=count
  // entries. Synthetic capacity changes do not shrink that physical backing.
  unsigned backing=sourceBacking[f];for(unsigned i=0;i<backing;++i)sourceBefore[f][i]=static_cast<CQuestDialog*>(s.data[i]);
 }
 if(cs->lane==1&&(cs->shape==6||cs->shape==7))at<unsigned>(questBefore,0x68)=cs->shape==6?3:0;
}
static void setup(){
 errors=firstError=guardCount=dialogCount=blockCount=eventCount=wantedEventCount=encounterCount=allocations=deletions=faultHits=mutationHits=expectedAllocations=expectedDeletions=expectedCaught=0;autotest::g_arenaUsed=0;
 resource=0;quest=memory(sizeof(CQuest));
 if(cs->lane!=1){statics();resource=memory(0x48);qncResourceCtor(resource,0);qncQuestCtor(quest,resource,0);}
 else {std::memset(quest,0,sizeof(CQuest));for(unsigned f=0;f<4;++f)::new(static_cast<char*>(quest)+offsets[f])Dialogs(10);}
 groups[0]=0;for(unsigned i=1;i<16;++i){groups[i]=static_cast<CDataGroup*>(memory(sizeof(CDataGroup)));if(cs->lane!=1)qncGroupCtor(groups[i],Wide(L"SAME NPC CONTENT"),0,10,10,reinterpret_cast<TRepository<Wide>*>(0x14dd9e0));else std::memset(groups[i],0x5a,sizeof(CDataGroup));}
 // Equal contents must never collapse two distinct group pointer identities.
 need(groups[1]!=groups[2]&&!std::memcmp(groups[1],groups[2],sizeof(CDataGroup)));
 setupSources();
 for(unsigned f=0;f<4;++f){View& s=view(&source(f));
  sourceBacking[f]=s.data?10:0;
  // Current fixtures stay within the original growBy=10 allocation.
  unsigned populated=cs->lane==1&&cs->shape==6&&f==0?3:s.count;
  need(populated<=10);for(unsigned i=populated;i<sourceBacking[f];++i)s.data[i]=dialogCount?dialogs[0]:0;
 }
 setupDestination();plan();snapshots();
}
static void verify(){
 need(destination().count==wantedCount&&destination().capacity==wantedCapacity&&destination().grow==wantedGrow);
 need(storageId(destination().data)==wantedStorage);need(allocations==expectedAllocations&&deletions==expectedDeletions);
 need(eventCount==wantedEventCount);for(unsigned i=0;i<eventCount;++i){Event& e=events[i];cap->add(&e,sizeof(e));if(i<wantedEventCount)need(!std::memcmp(&e,&wantedEvents[i],sizeof(e)));}
 unsigned limit=destination().capacity;if(!destination().data)limit=0;
 // A corrupt result must fail without an oracle reading beyond valid storage.
 Block* live=block(destination().data);if(live){need(limit<=live->size/sizeof(void*));if(limit>live->size/sizeof(void*))limit=live->size/sizeof(void*);}
 need(limit<=64);if(limit>64)limit=64;
 for(unsigned i=0;i<limit;++i){unsigned id=groupId(destination().data[i]);n(id);need(id==wanted[i]);}
 n(destination().count);n(destination().capacity);n(destination().grow);n(storageId(destination().data));
 unsigned alive=0;for(unsigned i=0;i<blockCount;++i)if(!blocks[i].freed)++alive;need(alive==(destination().data?1u:0u));
 need(!std::memcmp(quest,questBefore,sizeof(questBefore)));for(unsigned i=0;i<dialogCount;++i)need(!std::memcmp(dialogs[i],dialogBefore[i],sizeof(CQuestDialog)));for(unsigned i=1;i<16;++i)need(!std::memcmp(groups[i],groupBefore[i-1],sizeof(CDataGroup)));
 for(unsigned f=0;f<4;++f){View& s=view(&source(f));for(unsigned i=0;i<sourceBacking[f];++i)need(s.data[i]==sourceBefore[f][i]);}
 need(mutationHits==((cs->lane==1&&(cs->shape==6||cs->shape==7))?1u:0u));
 for(unsigned i=0;i<guardCount;++i)for(unsigned j=0;j<16;++j)need(guards[i].data[j]==0xce&&guards[i].data[16+guards[i].size+j]==0xce);
}
static void cleanup(){
 output->~Output();
 for(unsigned f=0;f<4;++f)source(f).clear();
 if(cs->lane!=1){for(unsigned i=0;i<dialogCount;++i)qncDialogDtor(dialogs[i]);for(unsigned i=1;i<16;++i)qncGroupDtor(groups[i]);qncQuestDtor(quest);qncResourceDtor(resource);}
 else for(unsigned f=0;f<4;++f)source(f).~Dialogs();
}
static void side(void* context,autotest::Capture& out,bool candidate){
 cs=static_cast<Case*>(context);cap=&out;setup();unsigned caught=0;
 {detour::Set news,deletes;newPatch=&news;deletePatch=&deletes;news.redirect(qncArrayNew,qncArrayNew,&allocate);deletes.redirect(qncArrayDelete,qncArrayDelete,&release);
  if(news.failed()||deletes.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef void(*Fn)(void*,Output&);Fn fn=candidate?&qncNew:&qncOld;if(!autotest::beginInvocation(out,fn))return;
  try{fn(quest,*output);if(cs->repeat)fn(quest,*output);out.callCompleted=1;}catch(const std::bad_alloc&){caught=1;}
 }
 need(caught==expectedCaught);need(faultHits==expectedCaught);need(out.callCompleted==!expectedCaught);verify();
 n(caught);n(faultHits);n(allocations);n(deletions);n(mutationHits);n(firstError);n(0x514e434cu);n(errors);
 // An initial-allocation failure leaves null data with nonzero capacity. Never
 // retry add on that partial state; destruction only sees its null data pointer.
 cleanup();
}
static void old(void* c,autotest::Capture& out){side(c,out,false);}static void fresh(void* c,autotest::Capture& out){side(c,out,true);}
static bool good(const autotest::Capture& out){unsigned tail[2]={0,1};if(out.length>=8)std::memcpy(tail,out.data+out.length-8,8);return tail[0]==0x514e434cu&&!tail[1];}
static unsigned line(const autotest::Capture& out){unsigned value=0;if(out.length>=12)std::memcpy(&value,out.data+out.length-12,4);return value;}
static bool completed(const tlhybrid_host* host,autotest::Coverage& coverage,Case& c,unsigned& count){
 autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(fresh,&c,b);++count;
 if(coverage.observe(host,a,b)||!good(a.capture)||!good(b.capture)){host->log("    NPC collection lane=%u shape=%u mode=%u repeat=%u status=%d/%d oracle=%u/%u firstError=%u/%u\n",c.lane,c.shape,c.mode,c.repeat,a.childStatus,b.childStatus,good(a.capture),good(b.capture),line(a.capture),line(b.capture));coverage.report(host);return false;}return true;
}
static bool unwound(const autotest::Outcome& o){return o.reportValid&&!o.childStatus&&!o.capture.issue&&o.capture.callStarted&&!o.capture.callCompleted&&good(o.capture);}
#undef need
}
// One named TL_TEST keeps the cycle's per-control FAIL binding unambiguous.
// Only completed semantic cases enter Coverage; caught bad_alloc cases have a
// separate count and must never supply completed-call acceptance credit.
TL_TEST(quest_npc_collection){using namespace quest_npc_collection_fixture;autotest::Coverage coverage("quest_npc_collection",0xd15210);unsigned count=0;
 for(unsigned shape=0;shape<11;++shape)for(unsigned mode=0;mode<6;++mode)for(unsigned repeat=0;repeat<2;++repeat){Case c={0,shape,mode,repeat,0};if(!completed(host,coverage,c,count))return 1;}
 host->log("    NPC collection: 132 genuine completed cases, original constructors and unchanged source/group objects\n");
 for(unsigned shape=0;shape<8;++shape)for(unsigned mode=0;mode<2;++mode){Case c={1,shape,mode,0,0};if(!completed(host,coverage,c,count))return 1;}
 coverage.report(host);if(coverage.completed!=count||count!=148||coverage.different||coverage.missing)return 1;
 unsigned exceptions=0;const unsigned modes[]={0,1,3};
 for(unsigned m=0;m<3;++m)for(unsigned fault=1;fault<=4;++fault){Case c={2,9,modes[m],0,fault};autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(fresh,&c,b);++exceptions;
  bool ok=unwound(a)&&unwound(b)&&a.capture.callTarget==0xd15210&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
  if(!ok){host->log("    NPC collection bad_alloc mode=%u ordinal=%u status=%d/%d oracle=%u/%u firstError=%u/%u\n",c.mode,fault,a.childStatus,b.childStatus,unwound(a),unwound(b),line(a.capture),line(b.capture));return 1;}}
 host->log("    NPC collection: 16 bounded synthetic completed cases and %u allocation-failure partial-state cases (no completed-call credit)\n",exceptions);return exceptions!=12;
}
