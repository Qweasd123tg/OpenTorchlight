#include "SmallMassCompare.h"
#include "SpawnClassParser.h"
#include "SpawnClassData.h"
#include "SpawnClass.h"
#include "GraphManager.h"
#include "StringUtilities.h"
#include "UnitResourceList.h"
#include "EmptyStrings.h"
TL_ORIGINAL(void, spawnCtor,(CSpawnClassData*,const std::wstring&),"_ZN15CSpawnClassDataC1ERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void spawnCtorNew(CSpawnClassData*,const std::wstring&) __asm__("_ZN15CSpawnClassDataC1ERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void, parserEmpty,(CSpawnClassParser*,CDataGroup*),"_ZN17CSpawnClassParser21createEmptySpawnClassEP10CDataGroup")
extern "C" void parserEmptyNew(CSpawnClassParser*,CDataGroup*) __asm__("_ZN17CSpawnClassParser21createEmptySpawnClassEP10CDataGroup");
TL_ORIGINAL(CSpawnClassData*, parserRef,(CSpawnClassParser*,const std::wstring&,CDataGroup*),"_ZN17CSpawnClassParser33createSpawnClassDataRefSpawnClassERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup")
extern "C" CSpawnClassData* parserRefNew(CSpawnClassParser*,const std::wstring&,CDataGroup*) __asm__("_ZN17CSpawnClassParser33createSpawnClassDataRefSpawnClassERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup");
TL_ORIGINAL(CSpawnClassData*, parserUnit,(CSpawnClassParser*,const std::wstring&,CDataGroup*),"_ZN17CSpawnClassParser28createSpawnClassDataWithUnitERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup")
extern "C" CSpawnClassData* parserUnitNew(CSpawnClassParser*,const std::wstring&,CDataGroup*) __asm__("_ZN17CSpawnClassParser28createSpawnClassDataWithUnitERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup");
TL_ORIGINAL(CSpawnClassData*, parserData,(CSpawnClassParser*,CDataGroup*),"_ZN17CSpawnClassParser20createSpawnClassDataEP10CDataGroup")
extern "C" CSpawnClassData* parserDataNew(CSpawnClassParser*,CDataGroup*) __asm__("_ZN17CSpawnClassParser20createSpawnClassDataEP10CDataGroup");
TL_ORIGINAL(void, parserFill,(CSpawnClassParser*,CDataGroup*),"_ZN17CSpawnClassParser19fillEmptySpawnClassEP10CDataGroup")
extern "C" void parserFillNew(CSpawnClassParser*,CDataGroup*) __asm__("_ZN17CSpawnClassParser19fillEmptySpawnClassEP10CDataGroup");
TL_FUNCTION(spawnGraphManager,"_ZN13CGraphManager12getSingletonEv")
TL_FUNCTION(spawnGraph,"_ZN13CGraphManager8getGraphERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(spawnByType,"_ZN17CSpawnClassParser30createSpawnClassDataByUnitTypeERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup")
TL_FUNCTION(spawnWithUnit,"_ZN17CSpawnClassParser28createSpawnClassDataWithUnitERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup")
TL_FUNCTION(spawnByRef,"_ZN17CSpawnClassParser33createSpawnClassDataRefSpawnClassERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup")
TL_FUNCTION(spawnCreate,"_ZN17CSpawnClassParser20createSpawnClassDataEP10CDataGroup")
TL_FUNCTION(spawnAdd,"_ZN11CSpawnClass17addSpawnClassDataEP10CDataGroupP15CSpawnClassData")
namespace deepen_spawn {
using namespace smallmass;
struct ParserStorage : CRunicCore {
 std::map<std::wstring,CSpawnClass*> classes;
 std::map<std::wstring,CSpawnClassData*> data;
};
struct GraphFailure {unsigned step;};
bool throwGraph;unsigned throwStep;CSpawnClassData* constructing;TSafePointer<CSpawnClassData>* observer;
CGraphManager* manager;CGraph* graphs[2];CSpawnClassParser* parser;CSpawnClass* selected;CDataGroup* rootGroup;CSpawnClassData* markers[3];unsigned graphCalls,addCalls;
CGraphManager* graphManager(){number(1);return manager;}
CGraph* graph(CGraphManager* self,const std::wstring& name){number(2);number(self==manager);text(name);unsigned n=graphCalls++;
 if(throwGraph&&n==0){observer->setObject(constructing);constructing->m_lUnitDataObjects.add(reinterpret_cast<CDataGroup*>(markers[0]));constructing->m_lUnitDataObjects.add(reinterpret_cast<CDataGroup*>(markers[1]));constructing->m_lUnitDataObjects.add(reinterpret_cast<CDataGroup*>(markers[2]));for(int i=0;i<13;++i)constructing->m_lPrimaryRandomizerIDs.add(i);}
 if(throwGraph&&n==throwStep){GraphFailure failure={n};throw failure;}
 return input->index&(1<<(n&1))?graphs[n&1]:0;}
CDataGroup* group(const wchar_t* name){return new CDataGroup(name,0,4,3,0);}
CSpawnClassData* route(CSpawnClassParser* self,const std::wstring& name,CDataGroup* data,unsigned kind){number(10+kind);number(self==parser);number(data==rootGroup);text(name);return input->index&32?0:markers[kind];}
CSpawnClassData* byType(CSpawnClassParser* s,const std::wstring& n,CDataGroup* g){return route(s,n,g,0);}
CSpawnClassData* withUnit(CSpawnClassParser* s,const std::wstring& n,CDataGroup* g){return route(s,n,g,1);}
CSpawnClassData* byRef(CSpawnClassParser* s,const std::wstring& n,CDataGroup* g){return route(s,n,g,2);}
CSpawnClassData* create(CSpawnClassParser* self,CDataGroup* child){number(20);number(self==parser);int id=child->GetDataValue(L"INDEX",-1);number(id);return (unsigned(id)+input->index)%3?markers[unsigned(id)%3]:0;}
void add(CSpawnClass* self,CDataGroup* child,CSpawnClassData* data){number(21);number(self==selected);number(child->GetDataValue(L"INDEX",-1));number(data==markers[0]?0:data==markers[1]?1:2);++addCalls;}
void emit(CSpawnClassParser* self,CDataGroup* unit){
 number(self->m_spawnClasses.size());for(std::map<std::wstring,CSpawnClass*>::iterator it=self->m_spawnClasses.begin();it!=self->m_spawnClasses.end();++it){text(it->first);number(it->second!=0);if(it->second){text(it->second->m_name);number(it->second->m_iUnknown30);number(it->second->m_entries.size());}}
 number(self->m_spawnClassData.size());for(std::map<std::wstring,CSpawnClassData*>::iterator it=self->m_spawnClassData.begin();it!=self->m_spawnClassData.end();++it){text(it->first);CSpawnClassData* d=it->second;number(d!=0);if(!d)continue;text(d->m_sName);number(d->m_lUnitDataObjects.size());for(unsigned n=0;n<d->m_lUnitDataObjects.size();++n)number(d->m_lUnitDataObjects[n]==unit);number(d->m_pSpawnClass==selected);number(d->m_iMinimumLevel);number(d->m_iLevelOffset);number(d->m_iRarityOverride);number(d->m_iFlags);number(d->m_pMinimumLevelGraph==graphs[0]);number(d->m_pMaximumLevelGraph==graphs[1]);}
}
void execute(Case& c,bool ours,autotest::Capture& out){
 input=&c;output=&out;autotest::g_arenaUsed=0;manager=(CGraphManager*)object(8);graphs[0]=(CGraph*)object(8);graphs[1]=(CGraph*)object(8);for(unsigned i=0;i<3;++i)markers[i]=(CSpawnClassData*)object(8);graphCalls=addCalls=0;throwGraph=c.op==6;throwStep=c.index&1;constructing=0;observer=0;
 detour::Set redirects;TL_REDIRECT(redirects,spawnGraphManager,&graphManager);TL_REDIRECT(redirects,spawnGraph,&graph);if(redirects.failed())_exit(42);
 if(c.op==0||c.op==6){
  CSpawnClassData* self=(CSpawnClassData*)object(sizeof(CSpawnClassData));std::memset(self,0xa5,sizeof(*self));std::wstring name=c.index%4==0?L"":c.index%4==1?L"Mixed spawn":c.index%4==2?L"Данные \x1f4a1":std::wstring(128,L'X');
  int before=g_iTotalCountOfObjects;typedef void(*Fn)(CSpawnClassData*,const std::wstring&);Fn fn=ours?spawnCtorNew:spawnCtor;
  if(c.op==6){
   TSafePointer<CSpawnClassData> weak;constructing=self;observer=&weak;out.addHeapInUse();
   if(!autotest::beginInvocation(out,fn))return;
   try{fn(self,name);_exit(48);}catch(const GraphFailure& failure){number(failure.step);}
   out.addHeapInUse();number(weak.getObject()==0);number(g_iTotalCountOfObjects-before);number(graphCalls);return;
  }
  if(!autotest::beginInvocation(out,fn))return;fn(self,name);out.callCompleted=1;
  text(self->m_sName);number(self->m_lUnitDataObjects.size());number(field<unsigned>(&self->m_lUnitDataObjects,0xc));number(field<unsigned>(&self->m_lUnitDataObjects,0x10));number(self->m_iMinimumLevel);number(self->m_iLevelOffset);number(self->m_iRarityOverride);number(self->m_iFlags);number(self->m_pRandomizer==0);number(self->m_pType1Randomizer==0);number(self->m_pType2Randomizer==0);number(self->m_pSpawnClass==0);number(self->m_bIsInitialized);number(self->m_lPrimaryRandomizerIDs.size());number(field<unsigned>(&self->m_lPrimaryRandomizerIDs,0x10));number(self->m_pMinimumLevelGraph==graphs[0]);number(self->m_pMaximumLevelGraph==graphs[1]);number(graphCalls);number(g_iTotalCountOfObjects-before);self->~CSpawnClassData();number(g_iTotalCountOfObjects-before);return;
 }
 ParserStorage* storage=::new(object(sizeof(ParserStorage)))ParserStorage;
 parser=reinterpret_cast<CSpawnClassParser*>(storage);
 if(sizeof(ParserStorage)!=sizeof(CSpawnClassParser)||reinterpret_cast<char*>(&storage->classes)-reinterpret_cast<char*>(storage)!=reinterpret_cast<char*>(&parser->m_spawnClasses)-reinterpret_cast<char*>(parser)||reinterpret_cast<char*>(&storage->data)-reinterpret_cast<char*>(storage)!=reinterpret_cast<char*>(&parser->m_spawnClassData)-reinterpret_cast<char*>(parser))_exit(47);
 CDataGroup* data=group(L"ROOT");rootGroup=data;
 CUnitResourceList* previous=m_pGlobalUnitResourceList;m_pGlobalUnitResourceList=0;CUnitResourceList* resources=::new(object(sizeof(CUnitResourceList)))CUnitResourceList;
 std::wstring name=c.index%4==0?L"Mixed Name":c.index%4==1?L"ДАННЫЕ":c.index%4==2?L"":L"Type \x1f4a1";std::wstring upper=STRINGS::StringUpper(name);
 selected=new CSpawnClass(upper.c_str());selected->m_iUnknown30=17;
 if(c.op==1){
  parser->m_spawnClasses[L"EXISTING"]=selected;
  std::wstring query=c.index%4==0?L"existing":c.index%4==1?L"New Name":c.index%4==2?L"":L"Тест";
  if(c.index&8)data->SetDataValue(L"NAME",query,false);
  data->SetDataValue(L"DONOTSPAWN",bool(c.index&16));data->SetDataValue(L"LEVEL_BONUS",int(c.index%7)-3);
  autotest::invoke(out,ours?parserEmptyNew:parserEmpty,parser,c.index%9==0?static_cast<CDataGroup*>(0):data);emit(parser,0);
 }else if(c.op==2||c.op==3){
  CDataGroup* unit=group(L"UNIT");resources->m_loadedDataGroups.add(unit);
  bool found=c.index&4,cached=c.index&8;
  if(c.op==2){if(found)parser->m_spawnClasses[upper]=selected;else parser->m_spawnClasses[L"OTHER"]=selected;}
  else{parser->m_spawnClasses[L"OTHER"]=selected;if(found)resources->m_dataGroupsByResourceGroupAndName[L"units"][upper]=unit;}
  CSpawnClassData* cache=0;
  if(cached){std::wstring key=(c.op==2?L"SPAWNCLASS:":L"UNIT:")+upper;cache=new CSpawnClassData(key);parser->m_spawnClassData[key]=cache;}
  CDataGroup* argument=(!found||cached)&&(c.index&16)?0:data;
  typedef CSpawnClassData*(*Fn)(CSpawnClassParser*,const std::wstring&,CDataGroup*);Fn fn=c.op==2?(ours?parserRefNew:parserRef):(ours?parserUnitNew:parserUnit);
  if(!autotest::beginInvocation(out,fn))return;CSpawnClassData* result=fn(parser,name,argument);out.callCompleted=1;number(result!=0);number(result&&result==cache);emit(parser,unit);
 }else if(c.op==4){
  parser->m_spawnClasses[L"OTHER"]=selected;
  if(c.index&1)data->SetDataValue(L"UNITTYPE",L"Monster type",false);if(c.index&2)data->SetDataValue(L"UNIT",L"Specific unit",false);if(c.index&4)data->SetDataValue(L"SPAWNCLASS",L"Class name",false);
  TL_REDIRECT(redirects,spawnByType,&byType);TL_REDIRECT(redirects,spawnWithUnit,&withUnit);TL_REDIRECT(redirects,spawnByRef,&byRef);if(redirects.failed())_exit(42);
  typedef CSpawnClassData*(*Fn)(CSpawnClassParser*,CDataGroup*);Fn fn=ours?parserDataNew:parserData;if(!autotest::beginInvocation(out,fn))return;CSpawnClassData* result=fn(parser,c.index&8?data:0);out.callCompleted=1;number(result==0?0:result==markers[0]?1:result==markers[1]?2:3);
 }else{
  parser->m_spawnClasses[c.index&4?upper:L"OTHER"]=selected;data->SetDataValue(L"NAME",name,false);
  for(unsigned n=0;n<c.index%5;++n){CDataGroup* child=data->AddDataGroup(L"ENTRY");child->SetDataValue(L"INDEX",int(n));}
  TL_REDIRECT(redirects,spawnCreate,&create);TL_REDIRECT(redirects,spawnAdd,&add);if(redirects.failed())_exit(42);
  unsigned capacity=field<unsigned>(&data->m_DataGroups,0xc);if(c.index&16&&data->GetNumberOfDataGroups())field<unsigned>(&data->m_DataGroups,0xc)=0;
  autotest::invoke(out,ours?parserFillNew:parserFill,parser,c.index&8?data:static_cast<CDataGroup*>(0));number(addCalls);field<unsigned>(&data->m_DataGroups,0xc)=capacity;
 }
 parser->clear();storage->~ParserStorage();resources->~CUnitResourceList();m_pGlobalUnitResourceList=previous;delete data;
}
}
TL_TEST(deepen_spawn_data_constructor){return smallmass::run(host,0,"deepen_spawn_data_constructor",(uint64_t)(uintptr_t)spawnCtor,&deepen_spawn::execute,48);}
TL_TEST(deepen_spawn_parser_empty){return smallmass::run(host,1,"deepen_spawn_parser_empty",(uint64_t)(uintptr_t)parserEmpty,&deepen_spawn::execute,72);}
TL_TEST(deepen_spawn_parser_reference){return smallmass::run(host,2,"deepen_spawn_parser_reference",(uint64_t)(uintptr_t)parserRef,&deepen_spawn::execute,80);}
TL_TEST(deepen_spawn_parser_unit){return smallmass::run(host,3,"deepen_spawn_parser_unit",(uint64_t)(uintptr_t)parserUnit,&deepen_spawn::execute,80);}
TL_TEST(deepen_spawn_parser_dispatch){return smallmass::run(host,4,"deepen_spawn_parser_dispatch",(uint64_t)(uintptr_t)parserData,&deepen_spawn::execute,96);}
TL_TEST(deepen_spawn_parser_fill){return smallmass::run(host,5,"deepen_spawn_parser_fill",(uint64_t)(uintptr_t)parserFill,&deepen_spawn::execute,96);}

TL_TEST(deepen_spawn_data_constructor_unwind){
 smallmass::side=&deepen_spawn::execute;
 for(unsigned i=0;i<32;++i){smallmass::Case c={6,i};autotest::Outcome& a=autotest::g_outcomes[0];autotest::Outcome& b=autotest::g_outcomes[1];autotest::runChild(smallmass::original,&c,a);autotest::runChild(smallmass::recovered,&c,b);
  if(!a.reportValid||!b.reportValid||a.childStatus||b.childStatus||a.capture.issue||b.capture.issue||!a.capture.callStarted||!b.capture.callStarted||a.capture.callCompleted||b.capture.callCompleted||a.capture.callTarget!=(uint64_t)(uintptr_t)spawnCtor||!host->comparison_pair(a.capture.callTarget,b.capture.callTarget)||a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length)){host->log("    spawn constructor unwind case %u: status %d/%d bytes %lu/%lu\n",i,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);return 1;}
 }
 host->log("    spawn constructor: 32 expected exception pairs, both real arrays and safe pointers cleaned\n");return 0;
}
