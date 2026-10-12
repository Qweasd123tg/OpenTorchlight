// Synthetic caller-boundary and expected-unwind probes, separate from the
// genuine constructor/dependency lane in QuestStringTagsGenuineTest.cpp.
// Unit getters and dungeon lookup are explicit doubles. Numeric conversion and
// STRINGS::replaceWString execute their complete original bodies. No fake object
// below is described as a genuine game object or passed to a game destructor.
// Raw System V calls additionally check the hidden result address returned in
// rax and the caller-owned by-value prefix's lifetime. UTF-32, old COW ABI only.
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <new>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void*,qsbOldReplace,(void*,void*,const std::wstring&),"_ZN6CQuest17replaceStringTagsERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void* qsbNewReplace(void*,void*,const std::wstring&) __asm__("_ZN6CQuest17replaceStringTagsERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void*,qsbOldAcquire,(void*,void*,std::wstring*,unsigned,std::wstring&),"_Z14getAcquireTagsP14CQuestUnitDataSbIwSt11char_traitsIwESaIwEEjRS4_")
extern "C" void* qsbNewAcquire(void*,void*,std::wstring*,unsigned,std::wstring&) __asm__("_Z14getAcquireTagsP14CQuestUnitDataSbIwSt11char_traitsIwESaIwEEjRS4_");
TL_ORIGINAL(std::wstring,qsbStringReplace,(std::wstring,const std::wstring&,const std::wstring&),"_ZN7STRINGS14replaceWStringESbIwSt11char_traitsIwESaIwEERKS3_S5_")
TL_FUNCTION(qsbStringBoundary,"_ZN7STRINGS14replaceWStringESbIwSt11char_traitsIwESaIwEERKS3_S5_")
TL_FUNCTION(qsbFloorBoundary,"_ZN14CQuestUnitData23getDungeonFloorActiveOnEv")
TL_FUNCTION(qsbCompleteBoundary,"_ZN14CQuestUnitData10isCompleteEb")
TL_FUNCTION(qsbNameBoundary,"_ZN14CQuestUnitData11getUnitNameEv")
TL_FUNCTION(qsbLookupBoundary,"_ZN16CResourceManager16getDungeonByNameERKSbIwSt11char_traitsIwESaIwEE")
namespace quest_string_boundaries {
typedef std::wstring Wide;
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
struct Case {unsigned entry,shape,leaked,fault;};
struct Stop {unsigned site;explicit Stop(unsigned value):site(value){}};
struct List {void** data;unsigned count,capacity,grow,pad;};
typedef char ABI[sizeof(Wide)==8&&sizeof(wchar_t)==4&&sizeof(List)==24?1:-1];
static const Case* cs;static autotest::Capture* cap;static void *quest,*resource,*dungeon,*units[8];
static List *aGroups[3],*dGroups[2];static Wide* names[8];static int floors[8];
static unsigned errors,firstError,replacements,floorCalls,completeCalls,nameCalls,lookupCalls,faultHits;
static detour::Set* stringPatch;static Wide* retained[192];static unsigned retainedCount;
static void n(unsigned value){cap->add(&value,sizeof(value));}
static void check(bool value,unsigned line){if(!value){if(!errors)firstError=line;++errors;}}
#define need(x) check((x),__LINE__)
static void* raw(unsigned size){void* p=autotest::allocate(size);if(!p)_exit(71);std::memset(p,0,size);return p;}
static List& list(void* p,unsigned off){return at<List>(p,off);}
static Wide decimal(unsigned x){wchar_t s[32];std::swprintf(s,32,L"%u",x);return Wide(s);}
static int refs(const Wide& text){return *reinterpret_cast<const int*>(reinterpret_cast<const char*>(text.c_str())-8);}
static void** pointers(void* a,void* b=0,void* c=0){void** p=static_cast<void**>(raw(3*sizeof(void*)));p[0]=a;p[1]=b;p[2]=c;return p;}
static void set(List& value,void** data,unsigned count,unsigned capacity){value.data=data;value.count=count;value.capacity=capacity;value.grow=2;value.pad=0;}
static List* make(void* a,void* b=0,void* c=0,unsigned count=1,unsigned capacity=1){List* l=static_cast<List*>(raw(sizeof(List)));set(*l,pointers(a,b,c),count,capacity);return l;}
static unsigned id(void* p){for(unsigned i=0;i<8;++i)if(p==units[i])return i;need(false);return 0;}
static void fault(unsigned site){if(cs->fault==site){++faultHits;throw Stop(site);}}
static void retain(const Wide& value){if(!cs->fault||value.empty())return;need(retainedCount<192);if(retainedCount<192)retained[retainedCount++]=new Wide(value);}
static Wide replace(Wide text,const Wide& from,const Wide& to){
 ++replacements;n(1000+replacements);cap->addText(text);cap->addText(from);cap->addText(to);retain(text);retain(from);retain(to);
 if(replacements==1)fault(1);if(replacements==2)fault(2);if(replacements==4)fault(7);if(replacements==5)fault(8);if(replacements==9)fault(9);if(replacements==14)fault(10);
 stringPatch->restore();try{Wide answer=qsbStringReplace(text,from,to);TL_REDIRECT(*stringPatch,qsbStringBoundary,&replace);return answer;}
 catch(...){TL_REDIRECT(*stringPatch,qsbStringBoundary,&replace);throw;}
}
static int floor(void* self){unsigned i=id(self);++floorCalls;n(2000+i);fault(3);return floors[i];}
static bool complete(void* self,bool flag){unsigned i=id(self);++completeCalls;n(3000+2*i+flag);fault(4);return flag;}
static Wide name(void* self){unsigned i=id(self);++nameCalls;n(4000+i);fault(5);if(i==4)fault(11);
 if(!cs->entry&&cs->shape==3){if(i==0)list(quest,0x130).count=2;if(i==2)list(quest,0x148).count=2;if(i==4)list(units[2],0x48).count=2;}
 return *names[i];
}
static void* lookup(void* self,const Wide& value){++lookupCalls;n(5000);need(self==resource);need(value==at<Wide>(quest,0x30));cap->addText(value);fault(6);return dungeon;}
static void init(){
 errors=firstError=replacements=floorCalls=completeCalls=nameCalls=lookupCalls=faultHits=retainedCount=0;autotest::g_arenaUsed=0;
 quest=raw(0x218);resource=raw(8);dungeon=raw(0x118);at<void*>(quest,0x1d8)=resource;at<int>(quest,0x20)=4;
 new(static_cast<char*>(quest)+0x30)Wide(L"Synthetic dungeon");new(static_cast<char*>(dungeon)+0x68)Wide(L"Cavern");
 const wchar_t* labels[]={L"A",L"B",L"D",L"E",L"C",L"F",L"G",L"H"};
 const unsigned required[]={7,9,11,12,13,17,19,23};const unsigned current[]={2,3,5,7,11,13,17,19};
 for(unsigned i=0;i<8;++i){units[i]=raw(0xc8);at<unsigned>(units[i],0x38)=required[i];at<unsigned>(units[i],0x3c)=current[i];names[i]=new(raw(sizeof(Wide)))Wide(labels[i]);floors[i]=2;}
 aGroups[0]=make(units[0]);aGroups[1]=make(units[1]);aGroups[2]=make(units[6]);dGroups[0]=make(units[2]);dGroups[1]=make(units[3]);
}
static void configure(Wide& input,Wide& expected,Wide& prefix,unsigned& index,void*& selected){
 prefix=L"[ACQUIRE";index=0;selected=units[0];
 if(cs->entry){
  if(cs->shape==1)index=~0u;
  if(cs->shape==2)prefix=Wide(L"[\u03a9")+Wide(1,0)+L"\u732b";
  Wide tag=prefix+decimal(index+1);input=tag+L"COUNT]|"+tag+L"DEPTH]|"+tag+L"COMPLETE]|"+tag+L"]";
  expected=L"7|3|Incomplete|A";
  if(cs->shape==3){input=L"";expected=L"";}
  if(cs->shape==4){selected=0;expected=input;}
  return;
 }
 if(cs->fault){
  set(list(units[2],0x48),pointers(units[4]),1,1);
  set(list(quest,0x130),pointers(aGroups[0]),1,1);set(list(quest,0x148),pointers(dGroups[0]),1,1);
  input=L"[DEPTH]|[DEFEATCOMPLETECOUNT]|[ACQUIRECOMPLETECOUNT]|[ACQUIRE1COUNT]|[ACQUIRE1DEPTH]|[ACQUIRE1COMPLETE]|[ACQUIRE1]|[DUNEGONNAME]|[DEFEAT1COUNT]|[DEFEAT1]|[DEFEAT1ACQUIRE1COUNT]|[DEFEAT1ACQUIRE1DEPTH]|[DEFEAT1ACQUIRE1COMPLETE]|[DEFEAT1ACQUIRE1]";
  expected=L"5|5|2|7|3|Incomplete|A|Cavern|11|D|13|3|Incomplete|C";return;
 }
 if(cs->shape==0){
  // Storage remains valid even beyond the deliberately smaller capacity. The
  // distinct spare entries make first-element fallback observably necessary.
  set(*aGroups[0],pointers(units[0],units[1],units[6]),3,cs->leaked?0:1);set(*dGroups[0],pointers(units[2],units[3]),2,cs->leaked?0:1);
  set(list(units[2],0x48),pointers(units[4],units[5],units[6]),3,cs->leaked?0:1);
  set(list(quest,0x130),pointers(aGroups[0],aGroups[1],aGroups[2]),3,cs->leaked?0:1);set(list(quest,0x148),pointers(dGroups[0],dGroups[1]),2,cs->leaked?0:1);
  input=L"[ACQUIRECOMPLETECOUNT]|[DEFEATCOMPLETECOUNT]|[ACQUIRE1COUNT]|[ACQUIRE2COUNT]|[ACQUIRE3COUNT]|[DEFEAT1COUNT]|[DEFEAT2COUNT]|[ACQUIRE1]|[ACQUIRE3]|[DEFEAT1]|[DEFEAT2]|[DUNEGONNAME]|[DEFEAT1ACQUIRE1]|[DEFEAT1ACQUIRE2]|[DEFEAT2ACQUIRE3]";
  expected=L"18|20|7|7|7|11|11|A|A|D|D|Cavern|C|C|C";return;
 }
 if(cs->shape==1){
  // Zero counted units avoids the unguarded sum dereference; the allocated
  // first slot is still read for representative selection and contains null.
  List* an=make(0);an->count=0;List* dn=make(0);dn->count=0;
  set(list(quest,0x130),pointers(an,aGroups[0]),2,2);set(list(quest,0x148),pointers(dn,dGroups[0]),2,2);
  input=L"[ACQUIRECOMPLETECOUNT]|[DEFEATCOMPLETECOUNT]|[ACQUIRE1]|[ACQUIRE2]|[DEFEAT1]|[DEFEAT2]|[ACQUIRE1COUNT]|[DEFEAT1COMPLETE]";
  expected=L"2|5|[ACQUIRE1]|A|[DEFEAT1]|D|[ACQUIRE1COUNT]|[DEFEAT1COMPLETE]";return;
 }
 if(cs->shape==2){
  set(list(quest,0x148),pointers(dGroups[0]),1,1);set(list(units[2],0x48),pointers(0,units[4],units[5]),3,3);set(list(units[4],0x48),pointers(units[6]),1,1);
  input=L"[DEFEAT1COMPLETE]|[DEFEAT1ACQUIRE1]|[DEFEAT1ACQUIRE2]|[DEFEAT1ACQUIRE2COUNT]|[DEFEAT1ACQUIRE2COMPLETE]|[DEFEAT1ACQUIRE3]|[DEFEAT1ACQUIRE2ACQUIRE1]";
  expected=L"Complete|[DEFEAT1ACQUIRE1]|C|13|Incomplete|F|[DEFEAT1ACQUIRE2ACQUIRE1]";return;
 }
 if(cs->shape==3){
  set(list(quest,0x130),pointers(aGroups[0],aGroups[1]),1,2);set(list(quest,0x148),pointers(dGroups[0],dGroups[1]),1,2);set(list(units[2],0x48),pointers(units[4],units[5]),1,2);
  input=L"[ACQUIRECOMPLETECOUNT]|[DEFEATCOMPLETECOUNT]|[ACQUIRE1]|[ACQUIRE2]|[DEFEAT1]|[DEFEAT2]|[DEFEAT1ACQUIRE1]|[DEFEAT1ACQUIRE2]";
  expected=L"2|5|A|B|D|E|C|F";return;
 }
 if(cs->shape==4){set(list(quest,0x130),pointers(aGroups[0]),1,1);set(list(quest,0x148),pointers(dGroups[0]),1,1);input=L"no tags";expected=input;return;}
 if(cs->shape==5){
  at<int>(quest,0x20)=2147483647;at<unsigned>(units[0],0x38)=~0u;at<unsigned>(units[0],0x3c)=~0u;at<unsigned>(units[1],0x3c)=2;floors[0]=2147483647;
  set(*aGroups[0],pointers(units[0],units[1]),2,2);set(list(quest,0x130),pointers(aGroups[0]),1,1);
  input=L"[DEPTH]|[ACQUIRE1DEPTH]|[ACQUIRECOMPLETECOUNT]|[ACQUIRE1COUNT]";expected=L"-2147483648|-2147483648|1|4294967295";return;
 }
 if(cs->shape==6){at<Wide>(quest,0x30)=L"[DEPTH]/[DUNEGONNAME]";input=at<Wide>(quest,0x30);expected=L"5/Cavern";return;}
 need(false);
}
static void witnesses(Wide** roots,unsigned rootCount){
 // Every retained string is a real COW copy. Once the target unwinds, its
 // references must disappear: the only remaining owners are these keepers and
 // the enumerated external objects. This catches leaked references to observed
 // replacement arguments/results and sret/external-prefix roots. Detached
 // intermediate prefix+index stem allocations are NOT lifetime-instrumented.
 // These probes do not throw
 // from any destructor or allocator or mistaking an equal crash for evidence.
 for(unsigned i=0;i<retainedCount;++i){unsigned owners=0;const wchar_t* p=retained[i]->c_str();
  for(unsigned j=0;j<retainedCount;++j)if(retained[j]->c_str()==p)++owners;
  for(unsigned j=0;j<rootCount;++j){bool duplicate=false;for(unsigned k=0;k<j;++k)if(roots[k]==roots[j])duplicate=true;if(!duplicate&&roots[j]->c_str()==p)++owners;}
  need(refs(*retained[i])==static_cast<int>(owners)-1);
 }
 for(unsigned i=0;i<retainedCount;++i)delete retained[i];retainedCount=0;
}
static Wide helperPartial(const Wide& original){
 if(cs->fault==1)return original;
 if(cs->fault==2||cs->fault==3)return Wide(L"7|[ACQUIRE1DEPTH]|[ACQUIRE1COMPLETE]|[ACQUIRE1]");
 if(cs->fault==4)return Wide(L"7|3|[ACQUIRE1COMPLETE]|[ACQUIRE1]");
 return Wide(L"7|3|Incomplete|[ACQUIRE1]");
}
static bool footer(const autotest::Capture& out){unsigned tail[2]={0,1};if(out.length>=8)std::memcpy(tail,out.data+out.length-8,8);return tail[0]==0x71534254u&&!tail[1];}
static void side(void* context,autotest::Capture& out,bool candidate){
 cs=static_cast<Case*>(context);cap=&out;init();Wide ownInput,expected,prefix;unsigned index=0;void* selected=0;configure(ownInput,expected,prefix,index,selected);
 Wide& input=(!cs->entry&&!cs->fault&&cs->shape==6)?at<Wide>(quest,0x30):ownInput;
 Wide snapshot(input),untouched(input.c_str(),input.size()),prefixSnapshot(prefix),untouchedPrefix(prefix.c_str(),prefix.size());
 if(cs->leaked){if(!input.empty())input[0]=input.c_str()[0];if(!prefix.empty())prefix[0]=prefix.c_str()[0];}
 int inputRefs=refs(input),prefixRefs=refs(prefix);
 // This local is exactly the caller-created by-value prefix object, including
 // its deep-copy behavior when the caller's source COW rep is marked leaked.
 Wide incoming(prefix);int incomingRefs=refs(incoming);void* resultStorage=raw(sizeof(Wide));void* returned=0;unsigned caught=0;
 {detour::Set callbacks,strings;stringPatch=&strings;TL_REDIRECT(strings,qsbStringBoundary,&replace);TL_REDIRECT(callbacks,qsbFloorBoundary,&floor);TL_REDIRECT(callbacks,qsbCompleteBoundary,&complete);TL_REDIRECT(callbacks,qsbNameBoundary,&name);TL_REDIRECT(callbacks,qsbLookupBoundary,&lookup);
  if(callbacks.failed()||strings.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(cs->entry){typedef void*(*Fn)(void*,void*,Wide*,unsigned,Wide&);Fn fn=candidate?&qsbNewAcquire:&qsbOldAcquire;if(!autotest::beginInvocation(out,fn))return;try{returned=fn(resultStorage,selected,&incoming,index,input);out.callCompleted=1;}catch(const Stop& stop){caught=stop.site;}}
  else{typedef void*(*Fn)(void*,void*,const Wide&);Fn fn=candidate?&qsbNewReplace:&qsbOldReplace;if(!autotest::beginInvocation(out,fn))return;try{returned=fn(resultStorage,quest,input);out.callCompleted=1;}catch(const Stop& stop){caught=stop.site;}}
 }
 need(snapshot==untouched&&prefixSnapshot==untouchedPrefix&&prefix==untouchedPrefix&&incoming==untouchedPrefix);
 if(cs->fault){
  need(caught==cs->fault&&faultHits==1&&!out.callCompleted);need(!returned);
  if(cs->entry)need(input==helperPartial(untouched));else need(input==untouched);
  Wide* roots[24];unsigned count=0;roots[count++]=&input;roots[count++]=&ownInput;roots[count++]=&snapshot;roots[count++]=&prefix;roots[count++]=&prefixSnapshot;roots[count++]=&incoming;roots[count++]=&at<Wide>(quest,0x30);roots[count++]=&at<Wide>(dungeon,0x68);roots[count++]=&expected;roots[count++]=&untouched;roots[count++]=&untouchedPrefix;
  for(unsigned i=0;i<8;++i)roots[count++]=names[i];witnesses(roots,count);
  if(!cs->entry)need(refs(input)==inputRefs);
  need(refs(prefix)==prefixRefs+(cs->leaked?0:1));need(refs(incoming)==incomingRefs);
 }else{
  need(!caught&&returned==resultStorage&&out.callCompleted);need(refs(incoming)==incomingRefs);Wide& result=*static_cast<Wide*>(resultStorage);need(result==expected);if(cs->entry)need(input==expected);else need(input==untouched);
  need(lookupCalls==(cs->entry?0u:1u));
  unsigned expectedNames=cs->entry?(selected?1u:0u):cs->shape==0?11:cs->shape==1?2:cs->shape==2?3:cs->shape==3?6:cs->shape==4?2:cs->shape==5?1:0;
  need(nameCalls==expectedNames&&floorCalls==expectedNames&&completeCalls==expectedNames);
  if(!cs->entry&&cs->shape==3)need(list(quest,0x130).count==2&&list(quest,0x148).count==2&&list(units[2],0x48).count==2);
  cap->addText(result);Wide keeper(result),inputKeeper(input);result.append(L" changed result");need(keeper==expected&&input==inputKeeper);input.append(L" changed input");need(keeper==expected&&snapshot==untouched);result.~Wide();
 }
 cap->addText(input);cap->addText(snapshot);cap->addText(prefix);n(caught);n(faultHits);n(replacements);n(floorCalls);n(completeCalls);n(nameCalls);n(lookupCalls);n(firstError);
 for(unsigned i=0;i<8;++i)names[i]->~Wide();at<Wide>(quest,0x30).~Wide();at<Wide>(dungeon,0x68).~Wide();
 n(0x71534254u);n(errors);
}
static void old(void* c,autotest::Capture& out){side(c,out,false);}static void fresh(void* c,autotest::Capture& out){side(c,out,true);}
static bool unwindGood(const autotest::Outcome& o){return o.reportValid&&!o.childStatus&&!o.capture.issue&&o.capture.callStarted&&!o.capture.callCompleted&&footer(o.capture);}
#undef need
}
TL_TEST(quest_string_tags_synthetic_boundaries){using namespace quest_string_boundaries;autotest::Coverage coverage("quest_string_tags_synthetic_boundaries",0xd181a0);unsigned count=0;
 for(unsigned shape=0;shape<7;++shape)for(unsigned leaked=0;leaked<2;++leaked){Case c={0,shape,leaked,0};autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(fresh,&c,b);++count;if(coverage.observe(host,a,b)||!footer(a.capture)||!footer(b.capture)){host->log("    Quest tag synthetic shape=%u leaked=%u status=%d/%d oracle=%u/%u\n",shape,leaked,a.childStatus,b.childStatus,footer(a.capture),footer(b.capture));coverage.report(host);return 1;}}
 coverage.report(host);return coverage.completed!=count||coverage.different||coverage.missing;
}
TL_TEST(quest_acquire_tags_synthetic_boundaries){using namespace quest_string_boundaries;autotest::Coverage coverage("quest_acquire_tags_synthetic_boundaries",0xd1d480);unsigned count=0;
 for(unsigned shape=0;shape<5;++shape)for(unsigned leaked=0;leaked<2;++leaked){Case c={1,shape,leaked,0};autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(fresh,&c,b);++count;if(coverage.observe(host,a,b)||!footer(a.capture)||!footer(b.capture)){host->log("    Acquire tag synthetic shape=%u leaked=%u status=%d/%d oracle=%u/%u\n",shape,leaked,a.childStatus,b.childStatus,footer(a.capture),footer(b.capture));coverage.report(host);return 1;}}
 coverage.report(host);return coverage.completed!=count||coverage.different||coverage.missing;
}
TL_TEST(quest_string_tags_expected_unwind){using namespace quest_string_boundaries;unsigned count=0;
 for(unsigned entry=0;entry<2;++entry)for(unsigned leaked=0;leaked<2;++leaked)for(unsigned fault=1;fault<=11;++fault){if(entry&&(fault==6||fault>=8))continue;Case c={entry,0,leaked,fault};autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(fresh,&c,b);++count;uint64_t address=entry?0xd1d480:0xd181a0;
  bool ok=unwindGood(a)&&unwindGood(b)&&a.capture.callTarget==address&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
  if(!ok){host->log("    Quest tag expected-unwind entry=%u fault=%u leaked=%u status=%d/%d oracle=%u/%u issue=%u/%u\n",entry,fault,leaked,a.childStatus,b.childStatus,unwindGood(a),unwindGood(b),a.capture.issue,b.capture.issue);return 1;}}
 host->log("    %u expected Quest/helper unwinds: mutable-reference partial state, unchanged const input and COW temporary releases; no completed-call credit\n",count);return count!=34;
}
