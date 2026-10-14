// CQuest string tags: original-constructed object/dependency differential lane.
// Both addressed bodies and every numeric/string/unit/dungeon dependency run.
// The sole environment double is an empty filesystem listing during the real
// CDungeonManager constructor. Observers forward the complete ORIGINAL body.
// CDataGroup fixtures exercise GUID text parsing, never definition/GUID loading.
// Original ELF: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
#include <cstdio>
#include <cstring>
#include <new>
#include <string>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#include "Quest.h"
#include "Dungeon.h"
#include "DungeonManager.h"
#include "TRepository.h"

#define QST_PAIR(R,N,A,S) TL_ORIGINAL(R,qstOld##N,A,S) extern "C" R qstNew##N A __asm__(S);
QST_PAIR(std::wstring,Replace,(void*,const std::wstring&),"_ZN6CQuest17replaceStringTagsERKSbIwSt11char_traitsIwESaIwEE")
QST_PAIR(std::wstring,Acquire,(void*,std::wstring,unsigned,std::wstring&),"_Z14getAcquireTagsP14CQuestUnitDataSbIwSt11char_traitsIwESaIwEEjRS4_")
#undef QST_PAIR
TL_ORIGINAL(void,qstQuestCtor,(void*,void*,void*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void,qstQuestDtor,(void*),"_ZN6CQuestD1Ev")
TL_ORIGINAL(void,qstResourceCtor,(void*,void*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,qstResourceDtor,(void*),"_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void,qstUnitCtor,(void*,void*),"_ZN14CQuestUnitDataC1EP6CQuest")
TL_ORIGINAL(void,qstUnitDtor,(void*),"_ZN14CQuestUnitDataD1Ev")
TL_ORIGINAL(void,qstDungeonCtor,(void*),"_ZN8CDungeonC1Ev")
TL_ORIGINAL(void,qstDungeonDtor,(void*),"_ZN8CDungeonD1Ev")
TL_ORIGINAL(void,qstManagerCtor,(void*,std::wstring),"_ZN15CDungeonManagerC1ESbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,qstManagerDtor,(void*),"_ZN15CDungeonManagerD1Ev")
TL_ORIGINAL(void,qstGroupCtor,(void*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,qstGroupDtor,(void*),"_ZN10CDataGroupD1Ev")
TL_ORIGINAL(void*,qstAddWide,(void*,const std::wstring&,const std::wstring&,bool),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES5_b")
TL_ORIGINAL(std::wstring,qstStringReplace,(std::wstring,const std::wstring&,const std::wstring&),"_ZN7STRINGS14replaceWStringESbIwSt11char_traitsIwESaIwEERKS3_S5_")
TL_ORIGINAL(int,qstFloor,(void*),"_ZN14CQuestUnitData23getDungeonFloorActiveOnEv")
TL_ORIGINAL(bool,qstComplete,(void*,bool),"_ZN14CQuestUnitData10isCompleteEb")
TL_ORIGINAL(std::wstring,qstName,(void*),"_ZN14CQuestUnitData11getUnitNameEv")
TL_ORIGINAL(void*,qstLookup,(void*,const std::wstring&),"_ZN16CResourceManager16getDungeonByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qstStringBoundary,"_ZN7STRINGS14replaceWStringESbIwSt11char_traitsIwESaIwEERKS3_S5_")
TL_FUNCTION(qstFloorBoundary,"_ZN14CQuestUnitData23getDungeonFloorActiveOnEv")
TL_FUNCTION(qstCompleteBoundary,"_ZN14CQuestUnitData10isCompleteEb")
TL_FUNCTION(qstNameBoundary,"_ZN14CQuestUnitData11getUnitNameEv")
TL_FUNCTION(qstLookupBoundary,"_ZN16CResourceManager16getDungeonByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qstFilesBoundary,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
namespace quest_string_tags {
typedef std::wstring Wide;
typedef TArrayList<CQuestUnitData*> Units;
typedef TArrayList<Units*> Groups;
typedef char Layout[sizeof(Wide)==8 && sizeof(wchar_t)==4 && sizeof(CQuest)==0x218 && sizeof(CQuestUnitData)==0xc8 && sizeof(CDungeon)==0x118 && sizeof(CDungeonManager)==0x30?1:-1];
template<class T>T& at(void* p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
struct Case {unsigned entry,shape,text;};
static const Case* cs;static autotest::Capture* cap;
static CQuest* quest;static CDataGroup* staleGroup;static void* resource;static CDungeonManager* manager;static CDungeon* dungeon;
static CQuestUnitData* units[64];static CDataGroup* data[64];static Units* groups[32];
static unsigned unitCount,groupCount,errors,firstError,fileCalls,lookupCalls;
static bool observed[64],found;
static std::vector<Wide> events,wanted;
static detour::Set *stringsPatch,*floorPatch,*completePatch,*namePatch,*lookupPatch;
static void n(unsigned value){cap->add(&value,sizeof(value));}
static void check(bool yes,unsigned line){if(!yes){if(!errors)firstError=line;++errors;}}
#define need(x) check((x),__LINE__)
static void* storage(unsigned size){void* p=autotest::allocate(size);if(!p)_exit(71);std::memset(p,0xa5,size);return p;}
static Wide decimal(unsigned value){wchar_t s[32];std::swprintf(s,32,L"%u",value);return Wide(s);}
static Wide event(const wchar_t* label,unsigned id){return Wide(label)+decimal(id);}
static unsigned identity(void* self){for(unsigned i=0;i<unitCount;++i)if(units[i]==self)return i+1;need(false);return 0;}
static int refs(const Wide& text){return *reinterpret_cast<const int*>(reinterpret_cast<const char*>(text.c_str())-8);}
static unsigned emptyFiles(void*,const Wide& path,void* list,Wide pattern,bool a,bool b,bool c,bool d){
 ++fileCalls;need(path==L"QUEST_STRING_TAGS_ISOLATED/");need(pattern==L"*.dat");need(!at<void*>(list,0)&&!at<unsigned>(list,8));need(a&&b&&!c&&!d);return 0;
}
static Wide replaceObserved(Wide text,const Wide& from,const Wide& to){
 events.push_back(from);stringsPatch->restore();
 try{Wide result=qstStringReplace(text,from,to);TL_REDIRECT(*stringsPatch,qstStringBoundary,&replaceObserved);return result;}
 catch(...){TL_REDIRECT(*stringsPatch,qstStringBoundary,&replaceObserved);throw;}
}
static int floorObserved(void* self){events.push_back(event(L"$floor:",identity(self)));floorPatch->restore();int value=qstFloor(self);TL_REDIRECT(*floorPatch,qstFloorBoundary,&floorObserved);return value;}
static bool completeObserved(void* self,bool flag){events.push_back(event(flag?L"$complete-true:":L"$complete-false:",identity(self)));completePatch->restore();bool value=qstComplete(self,flag);TL_REDIRECT(*completePatch,qstCompleteBoundary,&completeObserved);return value;}
static Wide nameObserved(void* self){
 unsigned id=identity(self);events.push_back(event(L"$name:",id));if(id)observed[id-1]=true;namePatch->restore();
 try{Wide value=qstName(self);TL_REDIRECT(*namePatch,qstNameBoundary,&nameObserved);return value;}
 catch(...){TL_REDIRECT(*namePatch,qstNameBoundary,&nameObserved);throw;}
}
static void* lookupObserved(void* self,const Wide& name){
 ++lookupCalls;events.push_back(Wide(L"$lookup"));need(self==resource);need(name==quest->m_pUnknown30);
 need(*reinterpret_cast<void**>(0x151f650)==manager);lookupPatch->restore();void* result=qstLookup(self,name);TL_REDIRECT(*lookupPatch,qstLookupBoundary,&lookupObserved);need(result==(found?dungeon:0));return result;
}
static void initializeStatics(){
 const unsigned cells[]={0x14f9fe8,0x14fb488,0x14ff1a8,0x151d408,0x151ab48,0x151c128,0x1490de8,0x14dd9c8,0x14dd9d8,0x14dda88,0x1509e88};
 for(unsigned i=0;i<sizeof(cells)/sizeof(cells[0]);++i)new(reinterpret_cast<void*>(cells[i]))Wide();
 new(reinterpret_cast<void*>(0x14dd9c0))std::string();
 ::new(reinterpret_cast<void*>(0x14dd9e0))TRepository<Wide>(Wide());
 *reinterpret_cast<unsigned*>(0x1500730)=100;
}
static CQuestUnitData* unit(const Wide& name,unsigned required,unsigned current,bool completed,int floor,bool noQuest=false){
 need(unitCount<64);unsigned i=unitCount++;CQuestUnitData* u=static_cast<CQuestUnitData*>(storage(sizeof(CQuestUnitData)));units[i]=u;
 qstUnitCtor(u,noQuest?0:quest);need(!u->m_pBaseUnitDataGroup&&!u->m_pQuestDataGroup&&u->m_baseUnitGuid==-1);
 CDataGroup* g=static_cast<CDataGroup*>(storage(sizeof(CDataGroup)));data[i]=g;
 qstGroupCtor(g,Wide(L"UNIT"),0,10,10,reinterpret_cast<TRepository<Wide>*>(0x14dd9e0));
 qstAddWide(g,Wide(L"UNIT_GUID"),Wide(L"123456789"),false);
 qstAddWide(g,Wide(L"DISPLAYNAME"),name,false);
 qstAddWide(g,Wide(L"NAME"),Wide(L"Fallback group name"),false);
 u->m_pQuestDataGroup=noQuest?0:g;
 // A stale but genuine pointer must be replaced by the original getUnitName.
 u->m_pBaseUnitDataGroup=staleGroup;u->m_baseUnitGuid=-1;
 at<unsigned>(u,0x38)=required;at<unsigned>(u,0x3c)=current;u->m_completed=completed;
 u->m_specificFloor=floor;u->m_displayName=name;
 return u;
}
static Units* group(Groups& owner,CQuestUnitData* a,CQuestUnitData* b=0){
 need(groupCount<32);Units* g=::new(storage(sizeof(Units)))Units(2);groups[groupCount++]=g;g->add(a);if(b)g->add(b);owner.add(g);return g;
}
static void expectGlobals(){wanted.push_back(L"[DEPTH]");wanted.push_back(L"[DEFEATCOMPLETECOUNT]");wanted.push_back(L"[ACQUIRECOMPLETECOUNT]");}
static void expectUnit(const Wide& prefix,unsigned index,unsigned id,bool defeat){
 Wide tag=prefix+decimal(index+1);wanted.push_back(tag+L"COUNT]");wanted.push_back(event(L"$floor:",id));wanted.push_back(tag+L"DEPTH]");wanted.push_back(event(defeat?L"$complete-true:":L"$complete-false:",id));wanted.push_back(tag+L"COMPLETE]");wanted.push_back(event(L"$name:",id));wanted.push_back(tag+L"]");
}
static void expectDungeon(){wanted.push_back(L"$lookup");if(found)wanted.push_back(L"[DUNEGONNAME]");}
static void setupReplace(Wide& input,Wide& expected){
 quest->m_iUnknown20=4;quest->m_pUnknown30=found?L"isOlated":L"missing";
 expectGlobals();
 if(cs->shape==0||cs->shape==9){input=cs->shape==9?L"":L"plain [UNKNOWN] [DUNGEONNAME]";expected=input;expectDungeon();return;}
 if(cs->shape==1){input=L"[DEPTH]/[ACQUIRECOMPLETECOUNT]/[DEFEATCOMPLETECOUNT]/[DUNEGONNAME]/[DUNGEONNAME]";expected=found?L"5/0/0/Cavern/[DUNGEONNAME]":L"5/0/0/[DUNEGONNAME]/[DUNGEONNAME]";expectDungeon();return;}
 if(cs->shape==2 || cs->shape==7){
  CQuestUnitData* a=unit(L"Acquired {HIDDEN}Gem",7,3,true,-1);a->m_relativeFloor=2;
  CQuestUnitData* ignoredA=unit(L"Ignored acquisition",99,5,false,1);
  CQuestUnitData* d=unit(L"unused group display",17,11,true,8);d->m_unitType=1;d->m_displayName=L"Defeated";
  CQuestUnitData* ignoredD=unit(L"Ignored defeat",99,13,false,1);
  CQuestUnitData* c=unit(L"unused child display",19,2,true,-1);c->m_relativeFloor=-7;c->m_generatedChampionName=L"Champion child";
  CQuestUnitData* e=unit(L"Second child",23,6,false,-3);
  CQuestUnitData* grand=unit(L"Never expanded",29,4,false,12);
  a->m_children.add(grand);c->m_children.add(grand);d->m_children.add(c);d->m_children.add(e);
  group(quest->m_Unknown130,a,ignoredA);group(quest->m_Unknown148,d,ignoredD);
  input=L"[DEPTH]|[ACQUIRECOMPLETECOUNT]|[DEFEATCOMPLETECOUNT]|[ACQUIRE1COUNT]|[ACQUIRE1DEPTH]|[ACQUIRE1COMPLETE]|[ACQUIRE1]|[DUNEGONNAME]|[DEFEAT1COUNT]|[DEFEAT1DEPTH]|[DEFEAT1COMPLETE]|[DEFEAT1]|[DEFEAT1ACQUIRE1COUNT]|[DEFEAT1ACQUIRE1DEPTH]|[DEFEAT1ACQUIRE1COMPLETE]|[DEFEAT1ACQUIRE1]|[DEFEAT1ACQUIRE2COUNT]|[DEFEAT1ACQUIRE2DEPTH]|[DEFEAT1ACQUIRE2COMPLETE]|[DEFEAT1ACQUIRE2]|[DEFEAT1ACQUIRE1ACQUIRE1]|[ACQUIRE1]|[ACQUIRE2]";
  expected=Wide(L"5|8|24|7|7|Incomplete|Acquired Gem|")+(found?L"Cavern":L"[DUNEGONNAME]")+L"|17|9|Complete|Defeated|19|5|Incomplete|Champion child|23|-2|Incomplete|Second child|[DEFEAT1ACQUIRE1ACQUIRE1]|Acquired Gem|[ACQUIRE2]";
  if(cs->shape==7){input=L"no recognized tags";expected=input;}
  expectUnit(L"[ACQUIRE",0,1,false);expectDungeon();expectUnit(L"[DEFEAT",0,3,true);expectUnit(L"[DEFEAT1ACQUIRE",0,5,false);expectUnit(L"[DEFEAT1ACQUIRE",1,6,false);return;
 }
 if(cs->shape==3){
  CQuestUnitData* a=unit(L"[DEPTH]/[DEFEATCOMPLETECOUNT]/[ACQUIRECOMPLETECOUNT]/[DUNEGONNAME]/[DEFEAT1COUNT]/[ACQUIRE1COUNT]/[ACQUIRE2]",7,3,false,0);
  CQuestUnitData* a2=unit(L"Later",8,4,false,0);
  CQuestUnitData* d=unit(L"[DEFEAT1COUNT]/[DEFEAT1ACQUIRE1]",17,11,true,0);
  CQuestUnitData* child=unit(L"Child[DEFEAT1ACQUIRE1COUNT]/[DEFEAT2COUNT]",19,2,false,0);
  CQuestUnitData* d2=unit(L"Second",23,5,false,0);
  d->m_children.add(child);group(quest->m_Unknown130,a);group(quest->m_Unknown130,a2);group(quest->m_Unknown148,d);group(quest->m_Unknown148,d2);
  dungeon->m_sDisplayName=L"R[ACQUIRE1]/[DEFEAT1COUNT]";
  input=L"[ACQUIRE1]|[DUNEGONNAME]|[DEFEAT1]|[DEFEAT1ACQUIRE1]";
  expected=found?L"[DEPTH]/[DEFEATCOMPLETECOUNT]/[ACQUIRECOMPLETECOUNT]/R[ACQUIRE1]/17/17/[ACQUIRE1COUNT]/Later|R[ACQUIRE1]/17|[DEFEAT1COUNT]/Child[DEFEAT1ACQUIRE1COUNT]/23|Child[DEFEAT1ACQUIRE1COUNT]/23":L"[DEPTH]/[DEFEATCOMPLETECOUNT]/[ACQUIRECOMPLETECOUNT]/[DUNEGONNAME]/17/[ACQUIRE1COUNT]/Later|[DUNEGONNAME]|[DEFEAT1COUNT]/Child[DEFEAT1ACQUIRE1COUNT]/23|Child[DEFEAT1ACQUIRE1COUNT]/23";
  expectUnit(L"[ACQUIRE",0,1,false);expectUnit(L"[ACQUIRE",1,2,false);expectDungeon();expectUnit(L"[DEFEAT",0,3,true);expectUnit(L"[DEFEAT1ACQUIRE",0,4,false);expectUnit(L"[DEFEAT",1,5,true);return;
 }
 if(cs->shape==4){
  for(unsigned i=0;i<10;++i)group(quest->m_Unknown130,unit(Wide(L"A")+decimal(i+1),i+10,i+1,false,0));
  for(unsigned i=0;i<10;++i)group(quest->m_Unknown148,unit(Wide(L"D")+decimal(i+1),i+30,i+11,true,0));
  input=L"[ACQUIRE9]|[ACQUIRE10]|[ACQUIRE10COUNT]|[DEFEAT9]|[DEFEAT10]|[DEFEAT10COUNT]|[ACQUIRECOMPLETECOUNT]|[DEFEATCOMPLETECOUNT]|[ACQUIRE0]|[DEFEAT11]";
  expected=L"A9|A10|19|D9|D10|39|55|155|[ACQUIRE0]|[DEFEAT11]";
  for(unsigned i=0;i<10;++i)expectUnit(L"[ACQUIRE",i,i+1,false);expectDungeon();for(unsigned i=0;i<10;++i)expectUnit(L"[DEFEAT",i,i+11,true);return;
 }
 if(cs->shape==5||cs->shape==8){
  const wchar_t nm[]={L'\u03a9',0,L'\u732b',static_cast<wchar_t>(0x1f642)};
  Wide name(nm,4);CQuestUnitData* a=unit(name,7,3,false,0);group(quest->m_Unknown130,a);
  // Original AddDataValue(wstring,wstring,bool) passes c_str to
  // SetValueString(wchar_t const*) at c5fb84/c5fb8f: definition text
  // truncates at NUL. The direct display-name branch preserves its length.
  if(cs->shape==8)a->m_unitType=1;
  input=Wide(L"[DEPTH]")+Wide(1,0)+L"[ACQUIRE1]/[DEPTH]";
  expected=Wide(L"5")+Wide(1,0)+(cs->shape==8?name:Wide(L"\u03a9"))+L"/5";
  expectUnit(L"[ACQUIRE",0,1,false);expectDungeon();return;
 }
 if(cs->shape==6){
  quest->m_iUnknown20=(-2147483647-1);
  group(quest->m_Unknown130,unit(L"A",~0u,~0u,false,-2),unit(L"ignored A",1,2,false,0));
  group(quest->m_Unknown148,unit(L"D",0x80000000u,0x7fffffffu,true,-2),unit(L"ignored D",1,2,false,0));
  // C++98 does not specify argument evaluation order: list identity is detected
  // below rather than inferred from the construction order of these arguments.
  CQuestUnitData* a=quest->m_Unknown130[0]->operator[](0);CQuestUnitData* d=quest->m_Unknown148[0]->operator[](0);
  input=L"[DEPTH]|[ACQUIRECOMPLETECOUNT]|[DEFEATCOMPLETECOUNT]|[ACQUIRE1COUNT]|[DEFEAT1COUNT]|[ACQUIRE1DEPTH]|[DEFEAT1DEPTH]";
  expected=L"-2147483647|1|2147483649|4294967295|2147483648|-1|-1";
  expectUnit(L"[ACQUIRE",0,identity(a),false);expectDungeon();expectUnit(L"[DEFEAT",0,identity(d),true);return;
 }
 need(false);
}
static void setupHelper(Wide& input,Wide& expected,Wide& prefix,unsigned& index,void*& selected){
 prefix=L"[ACQUIRE";index=cs->shape==2?8:cs->shape==3?9:cs->shape==4?~0u:0;
 selected=0;
 if(cs->shape==0){input=L"[ACQUIRE1] untouched";expected=input;return;}
 CQuestUnitData* a=unit(L"Helper {secret}name",7,99,true,-3,cs->shape==8);selected=a;
 if(cs->shape==8){a->m_displayName=L"No definition";a->m_generatedChampionName=L"";}
 if(cs->shape==6){CQuestUnitData* child=unit(L"Unexpanded child",3,1,false,0);a->m_children.add(child);}
 if(cs->shape==7){a->m_generatedChampionName=L"Champion";}
 if(cs->shape==9){
  prefix=Wide(L"[\u03a9")+Wide(1,0)+L"\u732b";
  const wchar_t name[]={L'N',0,static_cast<wchar_t>(0x1f642)};a->m_generatedChampionName=Wide(name,3);
 }
 if(cs->shape==5)at<unsigned>(a,0x38)=~0u;
 Wide tag=prefix+decimal(index+1);
 input=tag+L"COUNT]|"+tag+L"DEPTH]|"+tag+L"COMPLETE]|"+tag+L"]|"+tag+L"]|[UNKNOWN]|"+tag+L"ACQUIRE1]";
 Wide name=cs->shape==7?Wide(L"Champion"):cs->shape==8?Wide(L"No definition"):Wide(L"Helper name");
 if(cs->shape==9)name=a->m_generatedChampionName;
 expected=Wide(cs->shape==5?L"4294967295|-2|":L"7|-2|")+(cs->shape==6?L"Incomplete|":L"Complete|")+name+L"|"+name+L"|[UNKNOWN]|"+tag+L"ACQUIRE1]";
 expectUnit(prefix,index,1,false);
}
static unsigned failureLine(const autotest::Capture& out){unsigned line=0;if(out.length>=12)std::memcpy(&line,out.data+out.length-12,4);return line;}
static void codepoints(const char* label,const Wide& value){std::fprintf(stderr,"    %s length=%lu:",label,static_cast<unsigned long>(value.size()));for(unsigned i=0;i<value.size()&&i<160;++i)std::fprintf(stderr," %08x",static_cast<unsigned>(value[i]));std::fprintf(stderr,"\n");}
static bool good(const autotest::Capture& out){unsigned tail[2]={0,1};if(out.length>=8)std::memcpy(tail,out.data+out.length-8,8);return tail[0]==0x71534754u&&!tail[1];}
static void side(void* context,autotest::Capture& out,bool candidate){
 cs=static_cast<Case*>(context);cap=&out;errors=firstError=unitCount=groupCount=fileCalls=lookupCalls=0;events.clear();wanted.clear();std::memset(observed,0,sizeof(observed));autotest::g_arenaUsed=0;initializeStatics();
 resource=storage(0x48);qstResourceCtor(resource,0);
 quest=static_cast<CQuest*>(storage(sizeof(CQuest)));qstQuestCtor(quest,resource,0);
 staleGroup=static_cast<CDataGroup*>(storage(sizeof(CDataGroup)));qstGroupCtor(staleGroup,Wide(L"STALE"),0,10,10,reinterpret_cast<TRepository<Wide>*>(0x14dd9e0));
 manager=static_cast<CDungeonManager*>(storage(sizeof(CDungeonManager)));void* savedManager=*reinterpret_cast<void**>(0x151f650);
 detour::Set environment;TL_REDIRECT(environment,qstFilesBoundary,&emptyFiles);if(environment.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 qstManagerCtor(manager,Wide(L"quest_string_tags_isolated/"));need(fileCalls==1&&manager->m_lDungeons.size()==0);
 dungeon=static_cast<CDungeon*>(storage(sizeof(CDungeon)));qstDungeonCtor(dungeon);dungeon->m_sName=L"ISOLATED";dungeon->m_sDisplayName=L"Cavern";
 found=(cs->text&1)!=0;if(found)manager->m_lDungeons.add(dungeon);
 Wide input,expected,prefix;unsigned index=0;void* selected=0;
 if(cs->entry)setupHelper(input,expected,prefix,index,selected);else setupReplace(input,expected);
 // Both real COW sharing and the mutable-c_str (leaked rep) state are covered.
 Wide snapshot(input),untouched(input.c_str(),input.size()),prefixSnapshot(prefix),untouchedPrefix(prefix.c_str(),prefix.size());if(cs->text&2){if(!input.empty())input[0]=input.c_str()[0];if(!prefix.empty())prefix[0]=prefix.c_str()[0];}
 int inputRefs=refs(input),prefixRefs=refs(prefix);Wide output;
 {detour::Set strings,floors,completes,names,lookups;stringsPatch=&strings;floorPatch=&floors;completePatch=&completes;namePatch=&names;lookupPatch=&lookups;
  TL_REDIRECT(strings,qstStringBoundary,&replaceObserved);TL_REDIRECT(floors,qstFloorBoundary,&floorObserved);TL_REDIRECT(completes,qstCompleteBoundary,&completeObserved);TL_REDIRECT(names,qstNameBoundary,&nameObserved);TL_REDIRECT(lookups,qstLookupBoundary,&lookupObserved);
  if(strings.failed()||floors.failed()||completes.failed()||names.failed()||lookups.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(cs->entry){typedef Wide(*Fn)(void*,Wide,unsigned,Wide&);Fn fn=candidate?&qstNewAcquire:&qstOldAcquire;if(!autotest::beginInvocation(out,fn))return;output=fn(selected,prefix,index,input);}
  else{typedef Wide(*Fn)(void*,const Wide&);Fn fn=candidate?&qstNewReplace:&qstOldReplace;if(!autotest::beginInvocation(out,fn))return;output=fn(quest,input);}
  out.callCompleted=1;
 }
 if(output!=expected){std::fprintf(stderr,"    Quest tag oracle entry=%u shape=%u text=%u side=%s\n",cs->entry,cs->shape,cs->text,candidate?"candidate":"original");codepoints("actual",output);codepoints("expected",expected);}
 need(events==wanted);need(output==expected);need(snapshot==untouched);need(prefix==prefixSnapshot&&prefixSnapshot==untouchedPrefix);need(refs(prefix)==prefixRefs);need(lookupCalls==(cs->entry?0u:1u));
 if(cs->entry)need(input==expected);else{need(input==snapshot);if(input!=output)need(refs(input)==inputRefs);}
 for(unsigned i=0;i<unitCount;++i){
  if(observed[i]){need(units[i]->m_pBaseUnitDataGroup==(units[i]->m_pQuest?data[i]:0));need(units[i]->m_baseUnitGuid==(units[i]->m_pQuest?123456789LL:-1LL));}
  else{need(units[i]->m_pBaseUnitDataGroup==staleGroup);need(units[i]->m_baseUnitGuid==-1);}
  n(observed[i]);n(units[i]->m_pBaseUnitDataGroup==data[i]);n(units[i]->m_pBaseUnitDataGroup==0);cap->add(&units[i]->m_baseUnitGuid,sizeof(long long));
 }
 cap->addText(output);cap->addText(input);cap->addText(prefix);for(unsigned i=0;i<events.size();++i)cap->addText(events[i]);
 // Return, mutable reference, const input and pre-existing COW aliases have
 // independent object identity and must survive mutation of the other copy.
 Wide outputKeeper(output),inputKeeper(input);output.append(L" changed return");need(input==inputKeeper&&outputKeeper==expected);
 input.append(L" changed argument");need(outputKeeper==expected&&snapshot==untouched);
 if(cs->entry)need(inputKeeper==expected);prefix.append(L" changed prefix");need(prefixSnapshot==untouchedPrefix);
 // Detach arena-backed objects before original deleting ownership paths.
 for(unsigned i=0;i<unitCount;++i)units[i]->m_children.clear();
 quest->m_Unknown130.clear();quest->m_Unknown148.clear();
 for(unsigned i=0;i<groupCount;++i)groups[i]->~Units();
 for(unsigned i=0;i<unitCount;++i)qstUnitDtor(units[i]);
 for(unsigned i=0;i<unitCount;++i)qstGroupDtor(data[i]);qstGroupDtor(staleGroup);
 manager->m_lDungeons.clear();qstDungeonDtor(dungeon);qstManagerDtor(manager);*reinterpret_cast<void**>(0x151f650)=savedManager;
 qstQuestDtor(quest);qstResourceDtor(resource);
 n(firstError);n(0x71534754u);n(errors);
}
static void old(void* c,autotest::Capture& out){side(c,out,false);}static void fresh(void* c,autotest::Capture& out){side(c,out,true);}
#undef need
}
TL_TEST(quest_string_tags_original_dependencies){using namespace quest_string_tags;autotest::Coverage coverage("quest_string_tags_original_dependencies",0xd181a0);unsigned count=0;
 for(unsigned shape=0;shape<10;++shape)for(unsigned text=0;text<4;++text){Case c={0,shape,text};autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(fresh,&c,b);++count;
  if(coverage.observe(host,a,b)||!good(a.capture)||!good(b.capture)){host->log("    Quest tags original-dependency shape=%u text=%u status=%d/%d oracle=%u/%u firstError=%u/%u\n",shape,text,a.childStatus,b.childStatus,good(a.capture),good(b.capture),failureLine(a.capture),failureLine(b.capture));coverage.report(host);return 1;}}
 coverage.report(host);host->log("    actual original Quest/unit/data-group/dungeon constructors and getters; only empty filesystem boundary; no world or definition-loader claim\n");return coverage.completed!=count||coverage.different||coverage.missing;
}
TL_TEST(quest_acquire_tags_original_dependencies){using namespace quest_string_tags;autotest::Coverage coverage("quest_acquire_tags_original_dependencies",0xd1d480);unsigned count=0;
 for(unsigned shape=0;shape<10;++shape)for(unsigned text=0;text<4;++text){Case c={1,shape,text};autotest::Outcome a,b;autotest::runChild(old,&c,a);autotest::runChild(fresh,&c,b);++count;
  if(coverage.observe(host,a,b)||!good(a.capture)||!good(b.capture)){host->log("    Acquire tags original-dependency shape=%u text=%u status=%d/%d oracle=%u/%u firstError=%u/%u\n",shape,text,a.childStatus,b.childStatus,good(a.capture),good(b.capture),failureLine(a.capture),failureLine(b.capture));coverage.report(host);return 1;}}
 coverage.report(host);return coverage.completed!=count||coverage.different||coverage.missing;
}
