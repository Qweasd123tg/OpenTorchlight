// Independent branch/state oracle for original d300e0, using real GCC 4.4 maps.
#include <map>
#include <string>
#include <cstring>
#include <climits>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void*,oldSelect,(void*,void*),"_ZN13CQuestManager14getQuestForNPCEP9CBaseUnit")
extern "C" void* newSelect(void*,void*) __asm__("_ZN13CQuestManager14getQuestForNPCEP9CBaseUnit");
TL_FUNCTION(validFn,"_ZN6CQuest21getQuestIsValidForNPCEP9CBaseUnit")
TL_FUNCTION(initFn,"_ZN6CQuest22initializeQuestWithNPCEP9CBaseUnit")
TL_FUNCTION(randomFn,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(groupFn,"_ZN10CDataGroup18GetDataGroupByNameERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(valueFn,"_ZN10CDataValue14GetValueStringEb")
TL_FUNCTION(upperFn,"_ZN7STRINGS11StringUpperERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(depthFn,"_ZN7CPlayer11getMaxDepthESbIwSt11char_traitsIwESaIwEE")
extern "C" char qsArrayNew[] __asm__("_Znam");
extern "C" char qsArrayDelete[] __asm__("_ZdaPv");
namespace qs {
struct List {void** data;unsigned count,capacity,grow,padding;};
typedef std::map<void*,List*> NPCMap;typedef std::map<std::wstring,void*> Names;
struct Case {unsigned mode,variant,fault;};
struct Event {unsigned code,id;int value;};
const Case* c;autotest::Capture* cap;unsigned errors,used,wantUsed,validCalls;
Event events[128],wanted[128];void *owner,*npc,*player,*data,*changedData,*group,*quest[16],*values[16];
List *mapped,*replacement,*active,*valueList;NPCMap* mapping;Names* names;std::wstring texts[16];
unsigned char ownerExpected[0xd0],npcExpected[0x1c0],questExpected[16][0x220],groupExpected[0x60],valueExpected[16][0x38];
struct NodeSnapshot {void* p;unsigned char bytes[32];};
NodeSnapshot topology[12];unsigned nodes;
int questRefs[16],textRefs[16];
int refs(const std::wstring&s){return *reinterpret_cast<const int*>(reinterpret_cast<const char*>(s.data())-8);}
struct Allocation {unsigned char* p;unsigned n;bool freed;};
Allocation allocations[4];unsigned allocated,freed,allocAttempts;
unsigned qid(void*p){for(unsigned i=0;i<16;++i)if(p==quest[i])return i;return 99;}
unsigned vid(void*p){for(unsigned i=0;i<16;++i)if(p==values[i])return i;return 99;}
template<class T>T& at(void*p,unsigned o){return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
void need(bool x){if(!x)++errors;}
void num(unsigned n){cap->add(&n,4);}
void event(unsigned code,unsigned id=0,int value=0){if(used>=128){++errors;return;}Event e={code,id,value};events[used++]=e;if(c->fault==code)throw std::bad_alloc();}
void expect(unsigned code,unsigned id=0,int value=0){Event e={code,id,value};wanted[wantUsed++]=e;}
void* raw(unsigned n){return autotest::allocate(n);}
List* list(unsigned n=0){List*l=(List*)raw(sizeof(List));l->data=(void**)raw(16*8);l->count=n;l->capacity=16;l->grow=2;return l;}
void* expectedReturn;unsigned expectedRandom;
void* arrayNew(size_t n){++allocAttempts;if(c->fault==8||(c->fault==9&&allocAttempts==2))throw std::bad_alloc();need(allocated<4);Allocation&a=allocations[allocated++];a.p=(unsigned char*)raw(n+32);a.n=n;a.freed=false;std::memset(a.p,0xab,n+32);return a.p+16;}
void arrayDelete(void*p){if(!p)return;for(unsigned i=0;i<allocated;++i)if(allocations[i].p+16==p){need(!allocations[i].freed);allocations[i].freed=true;++freed;return;}++errors;}

void groupEvent(){expect(3,0,0);}
void valEvent(unsigned i){expect(4,i,1);expect(5,i,0);}
void selectEvent(unsigned n,unsigned q){expect(2,0,n-1);expect(6,q,0);expectedReturn=quest[q];}
unsigned recordValid(void*self,void*arg){unsigned i=qid(self);need(arg==npc);event(1,i);++validCalls;
 if(c->mode==11&&validCalls==1){(*mapping)[data]=replacement;}
 if(c->mode==12&&validCalls==1)mapped->count=1;
 if(c->mode==13&&validCalls==1)mapped->count=3;
 if(c->mode==14&&validCalls==1)mapped->capacity=1;
 if(c->mode==15&&validCalls==1)mapped->data[0]=0;
 if(c->mode==16&&validCalls==1){at<void*>(npc,0x1b0)=changedData;}
 if(c->mode==17&&validCalls==1){at<void*>(npc,0x1b0)=changedData;}
 if(c->mode==30&&validCalls==1)(*names)[L"QUEST0"]=quest[2];
 if(c->mode==4)return 0;
 if(c->mode==5)return i!=1;
 if(c->mode==17)return 0;
 if(c->mode==47)valueList->count=0;
 if(c->mode==25)return 0;
 return 1;
}
unsigned dirtyValid(void*self,void*arg){return recordValid(self,arg)|0x34567800u;}
int random(int lo,int hi){need(lo==0);event(2,0,hi);return expectedRandom;}
void initialize(void*self,void*arg){need(arg==npc);event(6,qid(self));if(c->mode==18){mapped->data[0]=quest[5];}}
void* getGroup(void*self,const std::wstring&s,bool create){need(self==data&&s==L"QUESTS"&&!create);event(3);return c->mode==19?0:group;}
const std::wstring& getValue(void*self,bool translate){unsigned i=vid(self);need(i<16&&translate);event(4,i,translate);if(c->mode==44)valueList->count=1;if(c->mode==45)valueList->count=3;if(c->mode==46)valueList->capacity=1;return texts[i<16?i:0];}
std::wstring upper(const std::wstring&s){unsigned i=0;for(;i<16;++i)if(&s==&texts[i])break;event(5,i);std::wstring r=s;for(unsigned k=0;k<r.size();++k)if(r[k]>=L'a'&&r[k]<=L'z')r[k]-=L'a'-L'A';return r;}
int depth(void*self,std::wstring dungeon){need(self==player&&dungeon==L"Dungeon mixed \u03a9");event(7);dungeon=L"MUTATED BY VALUE";if(c->mode==31||c->mode==32)(*names)[L"QUEST0"]=quest[3];
 if(c->mode==32)return 6;if(c->mode==27)return 4;if(c->mode==28)return 5;if(c->mode==29)return 6;if(c->mode==33)return -8;if(c->mode==34)return INT_MAX;return -1;
}
void setup(){autotest::g_arenaUsed=0;errors=used=wantUsed=validCalls=allocated=freed=allocAttempts=0;expectedReturn=0;expectedRandom=0;nodes=0;
 owner=raw(0xd0);npc=raw(0x1c0);player=raw(32);data=raw(32);changedData=raw(32);group=raw(0x60);at<void*>(owner,0x10)=player;at<void*>(npc,0x1b0)=data;
 names=new((char*)owner+0x40)Names;mapping=new((char*)owner+0xa0)NPCMap;
 active=(List*)((char*)owner+0x18);active->data=(void**)raw(16*8);active->capacity=16;active->grow=2;
 mapped=list();replacement=list(2);valueList=(List*)((char*)group+0x20);valueList->data=(void**)raw(16*8);valueList->capacity=16;valueList->grow=2;
 for(unsigned i=0;i<16;++i){quest[i]=raw(0x220);values[i]=raw(0x38);new((char*)quest[i]+0x30)std::wstring(L"Dungeon mixed \u03a9");at<void*>(quest[i],0x1e8)=changedData;at<int>(quest[i],0x20)=5;mapped->data[i]=quest[i];active->data[i]=quest[i];valueList->data[i]=values[i];at<unsigned>(values[i],0x30)=5;texts[i]=L"quest0";}
 for(unsigned i=0;i<16;++i)replacement->data[i]=quest[i+1<16?i+1:0];
 (*names)[L"QUEST0"]=quest[0];(*names)[L"QUEST1"]=quest[1];(*names)[L"QUEST2"]=quest[2];
 // Every pointer map has unrelated low/high keys, exercising both search directions.
 (*mapping)[(void*)1]=list();(*mapping)[(void*)(~(uintptr_t)0-16)]=list();
 unsigned m=c->mode;
 if(m==0){at<void*>(npc,0x1b0)=0;}
 else if(m==1){}
 else if(m==2){groupEvent();}
 else if(m>=3&&m<=18){(*mapping)[data]=mapped;mapped->count=1;
  if(m==3){expect(1,0);selectEvent(1,0);}
  if(m==4){expect(1,0);groupEvent();}
  if(m==5){mapped->count=3;expect(1,0);expect(1,1);expect(1,2);expectedRandom=1;selectEvent(2,2);}
  if(m==6||m==7){mapped->count=m==6?10:11;for(unsigned i=0;i<mapped->count;++i)expect(1,i);expectedRandom=c->variant?mapped->count-1:0;selectEvent(mapped->count,expectedRandom);}
  if(m==8){mapped->count=3;mapped->capacity=1;expect(1,0);expect(1,0);expect(1,0);expectedRandom=2;selectEvent(3,0);}
  if(m==9){expect(1,0);active->count=3;at<void*>(quest[2],0x1e8)=data;expectedReturn=quest[2];}
  if(m==10){expect(1,0);active->count=3;active->capacity=1;at<void*>(quest[2],0x1e8)=data;selectEvent(1,0);}
  if(m==11){expect(1,0);expect(1,2);expectedRandom=0;selectEvent(2,1);}
  if(m==12){mapped->count=3;expect(1,0);selectEvent(1,0);}
  if(m==13){expect(1,0);expect(1,1);expect(1,2);expectedRandom=2;selectEvent(3,2);}
  if(m==14){mapped->count=3;expect(1,0);expect(1,0);expect(1,0);expectedRandom=2;selectEvent(3,0);}
  if(m==15){expect(1,0);expect(2,0,0);}
  if(m==16){expect(1,0);active->count=1;expectedReturn=quest[0];}
  if(m==17){expect(1,0);groupEvent();}
  if(m==18){expect(1,0);selectEvent(1,0);}
 }
 else{groupEvent();if(m!=19&&m!=20){valueList->count=1;
  if(m==21){at<unsigned>(values[0],0x30)=3;}
  else{if(m==22)at<unsigned>(values[0],0x30)=8;
   if(m==23)texts[0]=L"missing";
   if(m==24)at<unsigned char>(quest[0],0x26)=1;
   if(m>=27&&m<=34)at<void*>(quest[0],0x1e8)=data;
   if(m==33)at<int>(quest[0],0x20)=-7;
   if(m==34)at<int>(quest[0],0x20)=INT_MIN;
   valEvent(0);
   if(m!=23&&m!=24){expect(1,0);
    if(m!=25){
     if(m>=27&&m<=34&&m!=30){expect(7);if(m==27||m==31||m==33){expectedReturn=m==31?quest[3]:quest[0];}else selectEvent(1,m==32?3:0);}
     else if(m==30)selectEvent(1,2);
     else if(m==35){valueList->count=3;valueList->capacity=1;valEvent(0);expect(1,0);valEvent(0);expect(1,0);expectedRandom=2;selectEvent(3,0);}
     else if(m==36){valueList->count=3;valEvent(1);expect(1,0);valEvent(2);expect(1,0);expectedRandom=2;selectEvent(3,0);}
     else selectEvent(1,0);
    }
   }
  }
 }}
 if(m>=37){wantUsed=0;expectedReturn=0;valueList->count=0;
  if(m==37||m==38){if(m==38)(*mapping)[data]=mapped;active->count=2;at<void*>(quest[1],0x1e8)=data;expectedReturn=quest[1];}
  if(m==39||m==40||m==48||m==49){(*mapping)[data]=mapped;mapped->count=m==40?3:1;if(m==40){mapped->data[1]=quest[0];mapped->data[2]=quest[0];}for(unsigned i=0;i<mapped->count;++i)expect(1,0);if(m==48){active->count=3;active->capacity=1;at<void*>(quest[0],0x1e8)=data;expectedReturn=quest[0];}else{expectedRandom=m==39?unsigned(-1):m==49?10:2;selectEvent(mapped->count,0);}}
  if((m>=41&&m<=47)||m==50){groupEvent();valueList->count=m==44||m==46?3:1;
   if(m==41){texts[0]=L"quest\u03a9";(*names)[L"QUEST\u03a9"]=quest[0];}
   if(m==42){const wchar_t x[]={L'q',0,L'z'};const wchar_t y[]={L'Q',0,L'Z'};texts[0]=std::wstring(x,3);(*names)[std::wstring(y,3)]=quest[0];}
   if(m==50)texts[0]=L"QuEsT2";
   valEvent(0);expect(1,m==50?2:0);
   if(m==43){at<void*>(quest[0],0x1e8)=data;at<int>(quest[0],0x20)=0;expect(7);expectedReturn=quest[0];}
   else if(m==45||m==46){valEvent(m==46?0:1);expect(1,0);valEvent(m==46?0:2);expect(1,0);expectedRandom=2;selectEvent(3,0);}
   else selectEvent(1,m==50?2:0);
  }
 }
 for(NPCMap::iterator i=mapping->begin();i!=mapping->end();++i){topology[nodes].p=i._M_node;std::memcpy(topology[nodes++].bytes,i._M_node,32);}
 for(Names::iterator i=names->begin();i!=names->end();++i){topology[nodes].p=i._M_node;std::memcpy(topology[nodes++].bytes,i._M_node,32);}
 std::memcpy(ownerExpected,owner,0xd0);std::memcpy(npcExpected,npc,0x1c0);std::memcpy(groupExpected,group,0x60);
 for(unsigned i=0;i<16;++i){std::memcpy(questExpected[i],quest[i],0x220);std::memcpy(valueExpected[i],values[i],0x38);questRefs[i]=refs(at<std::wstring>(quest[i],0x30));textRefs[i]=refs(texts[i]);}
}
void side(void*context,autotest::Capture&out,bool candidate){c=(Case*)context;cap=&out;setup();detour::Set d,arrays;
 TL_REDIRECT(d,validFn,&dirtyValid);TL_REDIRECT(d,initFn,&initialize);TL_REDIRECT(d,randomFn,&random);TL_REDIRECT(d,groupFn,&getGroup);TL_REDIRECT(d,valueFn,&getValue);TL_REDIRECT(d,upperFn,&upper);TL_REDIRECT(d,depthFn,&depth);
 arrays.redirect(qsArrayNew,qsArrayNew,&arrayNew);arrays.redirect(qsArrayDelete,qsArrayDelete,&arrayDelete);
 if(d.failed()||arrays.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void*(*Fn)(void*,void*);Fn f=candidate?&newSelect:&oldSelect;if(!autotest::beginInvocation(out,f))return;void*r=0;bool caught=false;try{r=f(owner,c->mode==1?0:npc);out.callCompleted=1;}catch(const std::bad_alloc&){caught=true;}need(caught==(c->fault!=0));if(!caught)need(r==expectedReturn);num(qid(r));if(!caught)need(used==wantUsed);else if(c->fault<8){unsigned stop=0;while(stop<wantUsed&&wanted[stop].code!=c->fault)++stop;need(stop<wantUsed&&used==stop+1);}
 for(unsigned i=0;i<used;++i){num(events[i].code);num(events[i].id);num(events[i].value);need(i<wantUsed&&!std::memcmp(&events[i],&wanted[i],sizeof(Event)));}
 if(c->mode==44)at<unsigned>(groupExpected,0x28)=1;if(c->mode==45)at<unsigned>(groupExpected,0x28)=3;if(c->mode==46)at<unsigned>(groupExpected,0x2c)=1;if(c->mode==47)at<unsigned>(groupExpected,0x28)=0;
 if(c->mode==16||c->mode==17)at<void*>(npcExpected,0x1b0)=changedData;
 need(!std::memcmp(npcExpected,npc,0x1c0));need(!std::memcmp(ownerExpected,owner,0xd0));need(!std::memcmp(groupExpected,group,0x60));
 for(unsigned i=0;i<16;++i){need(!std::memcmp(questExpected[i],quest[i],0x220));need(!std::memcmp(valueExpected[i],values[i],0x38));need(at<std::wstring>(quest[i],0x30)==L"Dungeon mixed \u03a9");need(refs(at<std::wstring>(quest[i],0x30))==questRefs[i]);need(refs(texts[i])==textRefs[i]);}
 for(NPCMap::iterator i=mapping->begin();i!=mapping->end();++i){num(i->first==(void*)1?0:i->first==data?1:2);num(i->second->count);num(i->second->capacity);for(unsigned k=0;k<16;++k)num(qid(i->second->data[k]));}
 for(Names::iterator i=names->begin();i!=names->end();++i){out.addText(i->first);num(qid(i->second));}
 for(unsigned i=0;i<nodes;++i)need(!std::memcmp(topology[i].p,topology[i].bytes,32));
 need(allocated==freed);for(unsigned i=0;i<allocated;++i){need(allocations[i].freed);need(allocations[i].n==(i?160:80));for(unsigned k=0;k<16;++k)need(allocations[i].p[k]==0xab&&allocations[i].p[16+allocations[i].n+k]==0xab);num(allocations[i].n);}
 if(!caught){unsigned expectedAlloc=(c->mode>=3&&c->mode<=18&&c->mode!=4&&c->mode!=17)||(c->mode>=22&&c->mode<=36&&c->mode!=23&&c->mode!=24&&c->mode!=25&&c->mode!=27&&c->mode!=31&&c->mode!=33)?1:0;if(c->mode==7)expectedAlloc=2;if(c->mode>=37)expectedAlloc=c->mode==37||c->mode==38||c->mode==43?0:1;need(allocated==expectedAlloc);}
 num(allocAttempts);num(freed);num(0x5153454c);num(errors);
}
void original(void*x,autotest::Capture&o){side(x,o,false);}void recovered(void*x,autotest::Capture&o){side(x,o,true);}
bool good(const autotest::Capture&o){unsigned n[2];if(o.length<8)return false;std::memcpy(n,o.data+o.length-8,8);return n[0]==0x5153454c&&!n[1];}
}

TL_TEST(questmanager_npc_selection){using namespace qs;autotest::Coverage cov("questmanager_npc_selection",0xd300e0);unsigned count=0;
 for(unsigned mode=0;mode<51;++mode)for(unsigned variant=0;variant<2;++variant){Case c={mode,variant,0};autotest::Outcome x,y;autotest::runChild(original,&c,x);autotest::runChild(recovered,&c,y);++count;if(cov.observe(host,x,y)||!good(x.capture)||!good(y.capture)){host->log("NPC selection mode=%u variant=%u oracle=%u/%u\n",mode,variant,good(x.capture),good(y.capture));cov.report(host);return 1;}}
 cov.report(host);if(cov.completed!=count||count<20||cov.different||cov.missing)return 1;
 const Case faults[]={{3,0,1},{3,0,2},{3,0,6},{26,0,3},{26,0,4},{26,0,5},{27,0,7},{3,0,8},{7,0,9}};
 for(unsigned i=0;i<sizeof(faults)/sizeof(faults[0]);++i){Case c=faults[i];autotest::Outcome x,y;autotest::runChild(original,&c,x);autotest::runChild(recovered,&c,y);bool ok=x.reportValid&&y.reportValid&&!x.childStatus&&!y.childStatus&&!x.capture.issue&&!y.capture.issue&&x.capture.callStarted&&y.capture.callStarted&&!x.capture.callCompleted&&!y.capture.callCompleted&&x.capture.callTarget==0xd300e0&&host->comparison_pair(x.capture.callTarget,y.capture.callTarget)&&good(x.capture)&&good(y.capture)&&x.capture.length==y.capture.length&&!std::memcmp(x.capture.data,y.capture.data,x.capture.length);if(!ok){host->log("NPC separate unwind mode=%u fault=%u oracle=%u/%u\n",c.mode,c.fault,good(x.capture),good(y.capture));return 1;}}
 host->log("NPC expected collaborator unwinds: 9, separate from completed coverage\n");return 0;}
