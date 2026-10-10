// Original/replacement resource-list comparisons. The original has a 4000-byte
// shared buffer but much larger copy guards. Bounded outputs and the no-copy
// oversized branch are tested; overflowing original writes are not executed.
// Each base scenario compares all 4000 output bytes, pointer identity
// and collaborator calls; graph/spawn add an exact 999-character safe boundary.
// The local result enforces the publication minimum.
#include <cstring>
#include <new>
#include <map>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void* editorGlobal __asm__("gEditor");
extern "C" char outputBuffer[4000] __asm__("sEditorTmpMemory");
TL_ORIGINAL(wchar_t*,original0,(),"_Z15EditorGetQuestsv")
extern "C" wchar_t* candidate0() __asm__("_Z15EditorGetQuestsv");
TL_ORIGINAL(wchar_t*,original1,(),"_Z16EditorGetAffixesv")
extern "C" wchar_t* candidate1() __asm__("_Z16EditorGetAffixesv");
TL_ORIGINAL(wchar_t*,original2,(),"_Z17EditorGetMissilesv")
extern "C" wchar_t* candidate2() __asm__("_Z17EditorGetMissilesv");
TL_ORIGINAL(wchar_t*,original3,(),"_Z11GetModNamesv")
extern "C" wchar_t* candidate3() __asm__("_Z11GetModNamesv");
TL_ORIGINAL(wchar_t*,original4,(),"_Z13EditorGetSetsv")
extern "C" wchar_t* candidate4() __asm__("_Z13EditorGetSetsv");
TL_ORIGINAL(wchar_t*,original5,(),"_Z18GetEnabledModNamesv")
extern "C" wchar_t* candidate5() __asm__("_Z18GetEnabledModNamesv");
TL_ORIGINAL(wchar_t*,original6,(),"_Z15EditorGetSkillsv")
extern "C" wchar_t* candidate6() __asm__("_Z15EditorGetSkillsv");
TL_ORIGINAL(wchar_t*,original7,(),"_Z14EditorGetUnitsv")
extern "C" wchar_t* candidate7() __asm__("_Z14EditorGetUnitsv");
TL_ORIGINAL(wchar_t*,original8,(),"_Z19EditorGetSoundNamesv")
extern "C" wchar_t* candidate8() __asm__("_Z19EditorGetSoundNamesv");
TL_ORIGINAL(wchar_t*,original9,(wchar_t*),"_Z29EditorGetSoundNamesByCategoryPw")
extern "C" wchar_t* candidate9(wchar_t*) __asm__("_Z29EditorGetSoundNamesByCategoryPw");
TL_ORIGINAL(wchar_t*,original10,(),"_Z24EditorGetSoundCategoriesv")
extern "C" wchar_t* candidate10() __asm__("_Z24EditorGetSoundCategoriesv");
TL_ORIGINAL(wchar_t*,original11,(),"_Z18EditorGetUnitTypesv")
extern "C" wchar_t* candidate11() __asm__("_Z18EditorGetUnitTypesv");
TL_ORIGINAL(wchar_t*,original12,(),"_Z17EditorGetDungeonsv")
extern "C" wchar_t* candidate12() __asm__("_Z17EditorGetDungeonsv");
TL_ORIGINAL(wchar_t*,original13,(),"_Z19EditorGetGraphNamesv")
extern "C" wchar_t* candidate13() __asm__("_Z19EditorGetGraphNamesv");
TL_ORIGINAL(wchar_t*,original14,(),"_Z21EditorGetSpawnClassesv")
extern "C" wchar_t* candidate14() __asm__("_Z21EditorGetSpawnClassesv");
TL_ORIGINAL(wchar_t*,original15,(),"_Z19EditorGetUnitThemesv")
extern "C" wchar_t* candidate15() __asm__("_Z19EditorGetUnitThemesv");
TL_ORIGINAL(wchar_t*,original16,(),"_Z19EditorGetAlignmentsv")
extern "C" wchar_t* candidate16() __asm__("_Z19EditorGetAlignmentsv");
TL_ORIGINAL(wchar_t*,original17,(),"_Z16EditorGetAIFlagsv")
extern "C" wchar_t* candidate17() __asm__("_Z16EditorGetAIFlagsv");
TL_ORIGINAL(wchar_t*,original18,(),"_Z20EditorGetDamageTypesv")
extern "C" wchar_t* candidate18() __asm__("_Z20EditorGetDamageTypesv");
TL_ORIGINAL(wchar_t*,original19,(),"_Z26EditorGetAnimationKeyTypesv")
extern "C" wchar_t* candidate19() __asm__("_Z26EditorGetAnimationKeyTypesv");
TL_ORIGINAL(wchar_t*,original20,(),"_Z19EditorGetCinematicsv")
extern "C" wchar_t* candidate20() __asm__("_Z19EditorGetCinematicsv");
TL_FUNCTION(target_questSingleton,"_ZN13CQuestManager12getSingletonEv")
TL_FUNCTION(target_masterSingleton,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(target_missileSingleton,"_ZN17CMissilePreloader13getSingleltonEv")
TL_FUNCTION(target_fileSingleton,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(target_setsSingleton,"_ZN5CSets12getSingletonEv")
TL_FUNCTION(target_skillSingleton,"_ZN12CSkillParser12getSingletonEv")
TL_FUNCTION(target_spawnSingleton,"_ZN17CSpawnClassParser12getSingletonEv")
TL_FUNCTION(target_themesSingleton,"_ZN11CUnitThemes12getSingletonEv")
TL_FUNCTION(target_cinematicSingleton,"_ZN11CCinematics12getSingletonEv")
TL_FUNCTION(target_resourceList,"_ZN16CResourceManager21getMasterResourceListEv")
TL_FUNCTION(target_dungeonManager,"_ZN16CResourceManager17getDungeonManagerEv")
TL_FUNCTION(target_cinematic,"_ZN11CCinematics12getCinematicEj")
TL_FUNCTION(target_questNames,"_ZN13CQuestManager13getQuestNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(target_affixNames,"_ZN19CEffectGroupManager13getAffixNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(target_missileNames,"_ZN17CMissilePreloader15getMissileNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(target_modNames,"_ZN11CFileSystem11getModNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(target_setNames,"_ZN5CSets11getSetNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(target_enabledNames,"_ZN11CFileSystem18getEnabledModNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(target_skillNames,"_ZN12CSkillParser13getSkillNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(target_unitNames,"_ZN17CUnitResourceList12getUnitNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(target_soundNames,"_ZN25CSoundBankDataInformation13getSoundNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(target_categoryNames,"_ZN25CSoundBankDataInformation26getSoundNamesByCatgoryNameERKSbIwSt11char_traitsIwESaIwEEP10TArrayListIS3_E")
TL_FUNCTION(target_typeNames,"_ZN10CHierarchy12getTypeNamesEP10TArrayListISbIwSt11char_traitsIwESaIwEEE")

namespace {
struct Case{unsigned operation,scenario,width;};
struct List{std::wstring* data;unsigned count,capacity,grow;};
struct Pointers{void** data;unsigned count,capacity,grow;};
const Case* input;autotest::Capture* capture;std::wstring* names;unsigned count,capacity,cineCalls,dungeonCalls;
void* objects[16];void* editors[2];
void number(unsigned n){capture->add(&n,4);}
unsigned identity(void*p){if(!p)return 0;for(unsigned i=0;i<16;++i)if(objects[i]==p)return i+1;return 99;}
void event(unsigned code,void*p){number(code);number(identity(p));}
void pointerAt(void*p,unsigned at,void*v){std::memcpy(static_cast<char*>(p)+at,&v,8);}
void swapEditor(){if(input->scenario==12)editorGlobal=editors[1];}
void* questSingleton(){event(1,objects[1]);swapEditor();return objects[1];}
void* masterSingleton(){event(2,objects[0]);swapEditor();return objects[0];}
void* missileSingleton(){event(3,objects[2]);swapEditor();return objects[2];}
void* fileSingleton(){event(4,objects[3]);swapEditor();return objects[3];}
void* setsSingleton(){event(5,objects[4]);swapEditor();return objects[4];}
void* skillSingleton(){event(6,objects[5]);swapEditor();return objects[5];}
void* spawnSingleton(){event(7,objects[6]);swapEditor();return objects[6];}
void* themesSingleton(){event(8,objects[7]);swapEditor();return objects[7];}
void* cinematicSingleton(){void*p=objects[8+(cineCalls++%2)];event(9,p);swapEditor();return p;}
void* resourceList(void*p){event(10,p);swapEditor();return objects[10];}
void* dungeonManager(void*p){event(11,p);swapEditor();++dungeonCalls;return input->scenario==2?NULL:objects[11];}
void* cinematic(void*p,unsigned i){event(12,p);number(i);return input->scenario==5&&i%2?NULL:&names[i%32];}
void fill(unsigned code,void*p,List*list){event(code,p);number(list->count);number(list->capacity);number(list->grow);
 if(!count)return;unsigned allocated=capacity?capacity:1;list->data=new std::wstring[allocated];list->count=count;list->capacity=capacity;
 for(unsigned i=0;i<allocated;++i)list->data[i]=names[i];}
void questNames(void*p,List*l){fill(20,p,l);}
void affixNames(void*p,List*l){fill(21,p,l);}
void missileNames(void*p,List*l){fill(22,p,l);}
void modNames(void*p,List*l){fill(23,p,l);}
void setNames(void*p,List*l){fill(24,p,l);}
void enabledNames(void*p,List*l){fill(25,p,l);}
void skillNames(List*l){fill(26,NULL,l);}
void unitNames(void*p,List*l){fill(27,p,l);}
void soundNames(void*p,List*l){fill(28,p,l);}
void categoryNames(void*p,const std::wstring&s,List*l){capture->addText(s);fill(29,p,l);}
void typeNames(void*p,List*l){fill(30,p,l);}

void side(Case&c,bool ours,autotest::Capture&out){
 input=&c;capture=&out;cineCalls=dungeonCalls=0;
 unsigned long long objectBytes[16][64]={{0}},editorBytes[2][64]={{0}},namedObjects[32][20]={{0}};
 std::wstring dataset[32];names=dataset;void* elements[32];
 for(unsigned i=0;i<16;++i)objects[i]=objectBytes[i];
 for(unsigned i=0;i<2;++i){editors[i]=editorBytes[i];reinterpret_cast<char*>(editors[i])[0x49]=c.scenario==0;
  pointerAt(editors[i],0x58,c.scenario==1?NULL:objects[0]);pointerAt(editors[i],0x128,objects[14+i]);}
 editorGlobal=editors[0];count=c.scenario==3?0:c.scenario==4?1:5;capacity=c.scenario==6?2:count?count:1;
 if(c.scenario>=14&&c.scenario<28){
  const unsigned counts[]={2,2,7,31,32,5,7,3,6,10,1,4,16,30};
  const unsigned capacities[]={2,1,7,31,32,8,0,3,6,10,32,1,16,2};
  count=counts[c.scenario-14];capacity=capacities[c.scenario-14];
 }
 if(c.scenario==28)count=capacity=1;
 unsigned entries=c.operation==19?29:(c.operation>=16&&c.operation<=18)?7:count;
 for(unsigned i=0;i<32;++i){
  if(c.scenario==28)dataset[i]=i?L"":std::wstring(997,L'q');
  else if(c.scenario==9)dataset[i]=i?L"":std::wstring((c.width==2?1998:999)-entries,L'q');
  else if(c.scenario==10)dataset[i]=i?L"":std::wstring(4000000/c.width,L'r');
  else if(c.scenario==7)dataset[i]=std::wstring(L"ΩК").append(1,static_cast<wchar_t>(0x10000+i));
  else if(c.scenario==8)dataset[i]=std::wstring(L"a\0b",3);
  else if(c.scenario==13)dataset[i]=i%2?L"a,b":L"a,b,c";
  else if(c.scenario==14)dataset[i]=i?L"second":L"first";
  else if(c.scenario==15)dataset[i]=i?L"outside capacity":L"fallback";
  else if(c.scenario==16)dataset[i]=std::wstring(1,static_cast<wchar_t>(L'a'+i));
  else if(c.scenario==17||c.scenario==18)dataset[i]=std::wstring(L"unit_").append(1,static_cast<wchar_t>(L'A'+i));
  else if(c.scenario==19)dataset[i]=i<count?L"live":L"spare slot";
  else if(c.scenario==20)dataset[i]=i?L"not selected":L"zero capacity";
  else if(c.scenario==21)dataset[i]=L"same";
  else if(c.scenario==22)dataset[i]=std::wstring(L"e\u0301").append(1,static_cast<wchar_t>(0x1f642+i));
  else if(c.scenario==23)dataset[i]=i%2?L" a,\nb\t":L",, ";
  else if(c.scenario==24)dataset[i]=std::wstring(L"\0head",5);
  else if(c.scenario==25)dataset[i]=i?L"not selected":L"repeated first";
  else if(c.scenario==26)dataset[i]=L"";
  else if(c.scenario==27)dataset[i]=i%2?L"":L"end";
  else dataset[i]=i%3==0?L"":i%3==1?L"beta":L"alpha";
  elements[i]=namedObjects[i];
 }
 // The four local tables below belong specifically to EditorDLL.cpp in the
 // hash-pinned original; identical spellings exist in other translation units.
 const uintptr_t tableAddresses[]={0x1460c40,0x14625a0,0x1460cc0,0x14622a0};
 for(unsigned table=0;table<4;++table){std::wstring* values=reinterpret_cast<std::wstring*>(tableAddresses[table]);
  for(unsigned i=0;i<(table==3?29u:7u);++i)::new(&values[i])std::wstring(dataset[i]);}
 ::new(reinterpret_cast<void*>(0x1460598))std::wstring(c.scenario==11?L"seed:":L"");
 void* optional=c.scenario==2?NULL:objects[12];pointerAt(objects[0],0x100,optional);
 pointerAt(objects[0],0x58,objects[13]);pointerAt(objects[0],0x80,c.scenario==2?NULL:objects[13]);
 pointerAt(objects[0],0x48,c.scenario==2?NULL:objects[13]);
 List categories={names,count,capacity,10};std::memcpy(static_cast<char*>(objects[12])+0x10,&categories,sizeof(categories));
 Pointers pointers={elements,count,capacity,10};
 std::memcpy(static_cast<char*>(objects[7])+0x18,&pointers,sizeof(pointers));
 std::memcpy(static_cast<char*>(objects[11])+0x18,&pointers,sizeof(pointers));
 std::memcpy(static_cast<char*>(objects[8])+0x20,&count,4);
 unsigned changedCount=count+2;std::memcpy(static_cast<char*>(objects[9])+0x20,&changedCount,4);
 for(unsigned i=0;i<32;++i){::new(reinterpret_cast<char*>(namedObjects[i])+0x28)std::wstring(dataset[i]);::new(reinterpret_cast<char*>(namedObjects[i])+0x60)std::wstring(dataset[i]);
  if(c.operation==12&&c.scenario==5&&i%2)elements[i]=NULL;}
 typedef std::map<std::wstring,void*> Map;
 Map* graph=::new(static_cast<char*>(objects[13])+0x18)Map;
 Map* spawn=::new(static_cast<char*>(objects[6])+0x10)Map;
 for(unsigned i=0;i<count;++i){std::wstring key=dataset[i];if(c.scenario==9)key=L"bounded";key+=static_cast<wchar_t>(L'A'+(count-i));(*graph)[key]=elements[i];(*spawn)[key]=elements[i];}
 std::memset(outputBuffer,c.scenario>=14?0x80+c.scenario:0x5a,sizeof(outputBuffer));
 detour::Set patches;
 TL_REDIRECT(patches,target_questSingleton,&questSingleton);
 TL_REDIRECT(patches,target_masterSingleton,&masterSingleton);
 TL_REDIRECT(patches,target_missileSingleton,&missileSingleton);
 TL_REDIRECT(patches,target_fileSingleton,&fileSingleton);
 TL_REDIRECT(patches,target_setsSingleton,&setsSingleton);
 TL_REDIRECT(patches,target_skillSingleton,&skillSingleton);
 TL_REDIRECT(patches,target_spawnSingleton,&spawnSingleton);
 TL_REDIRECT(patches,target_themesSingleton,&themesSingleton);
 TL_REDIRECT(patches,target_cinematicSingleton,&cinematicSingleton);
 TL_REDIRECT(patches,target_resourceList,&resourceList);
 TL_REDIRECT(patches,target_dungeonManager,&dungeonManager);
 TL_REDIRECT(patches,target_cinematic,&cinematic);
 TL_REDIRECT(patches,target_questNames,&questNames);
 TL_REDIRECT(patches,target_affixNames,&affixNames);
 TL_REDIRECT(patches,target_missileNames,&missileNames);
 TL_REDIRECT(patches,target_modNames,&modNames);
 TL_REDIRECT(patches,target_setNames,&setNames);
 TL_REDIRECT(patches,target_enabledNames,&enabledNames);
 TL_REDIRECT(patches,target_skillNames,&skillNames);
 TL_REDIRECT(patches,target_unitNames,&unitNames);
 TL_REDIRECT(patches,target_soundNames,&soundNames);
 TL_REDIRECT(patches,target_categoryNames,&categoryNames);
 TL_REDIRECT(patches,target_typeNames,&typeNames);
 if(patches.failed())_exit(41);
 wchar_t* result=NULL;
 switch(c.operation){
 case 0:{wchar_t*(*fn)()=ours?&candidate0:&original0;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 1:{wchar_t*(*fn)()=ours?&candidate1:&original1;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 2:{wchar_t*(*fn)()=ours?&candidate2:&original2;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 3:{wchar_t*(*fn)()=ours?&candidate3:&original3;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 4:{wchar_t*(*fn)()=ours?&candidate4:&original4;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 5:{wchar_t*(*fn)()=ours?&candidate5:&original5;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 6:{wchar_t*(*fn)()=ours?&candidate6:&original6;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 7:{wchar_t*(*fn)()=ours?&candidate7:&original7;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 8:{wchar_t*(*fn)()=ours?&candidate8:&original8;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 9:{wchar_t*(*fn)(wchar_t*)=ours?&candidate9:&original9;if(!autotest::beginInvocation(out,fn))return;result=fn(const_cast<wchar_t*>(L"category Ω"));out.callCompleted=1;break;}
 case 10:{wchar_t*(*fn)()=ours?&candidate10:&original10;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 11:{wchar_t*(*fn)()=ours?&candidate11:&original11;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 12:{wchar_t*(*fn)()=ours?&candidate12:&original12;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 13:{wchar_t*(*fn)()=ours?&candidate13:&original13;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 14:{wchar_t*(*fn)()=ours?&candidate14:&original14;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 15:{wchar_t*(*fn)()=ours?&candidate15:&original15;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 16:{wchar_t*(*fn)()=ours?&candidate16:&original16;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 17:{wchar_t*(*fn)()=ours?&candidate17:&original17;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 18:{wchar_t*(*fn)()=ours?&candidate18:&original18;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 19:{wchar_t*(*fn)()=ours?&candidate19:&original19;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}
 case 20:{wchar_t*(*fn)()=ours?&candidate20:&original20;if(!autotest::beginInvocation(out,fn))return;result=fn();out.callCompleted=1;break;}

 }
 // The map appends B to a 997-character key, followed by the comma.
 // These witnesses fail closed even if both original and candidate skip work.
 if(c.scenario==28){
  if(reinterpret_cast<char*>(result)!=outputBuffer)_exit(42);
  for(unsigned i=0;i<997;++i)if(result[i]!=L'q')_exit(42);
  if(result[997]!=L'B'||result[998]!=L','||result[999]!=0)_exit(42);
 }
 number(!result?0:reinterpret_cast<char*>(result)==outputBuffer?1:99);
 out.add(outputBuffer,sizeof(outputBuffer));number(cineCalls);number(dungeonCalls);number(editorGlobal==editors[1]);
 patches.restore();graph->~Map();spawn->~Map();
}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(editor_mass_lists_differential){
 const uint64_t addresses[]={
(uint64_t)(uintptr_t)&original0,(uint64_t)(uintptr_t)&original1,(uint64_t)(uintptr_t)&original2,(uint64_t)(uintptr_t)&original3,(uint64_t)(uintptr_t)&original4,(uint64_t)(uintptr_t)&original5,(uint64_t)(uintptr_t)&original6,(uint64_t)(uintptr_t)&original7,(uint64_t)(uintptr_t)&original8,(uint64_t)(uintptr_t)&original9,(uint64_t)(uintptr_t)&original10,(uint64_t)(uintptr_t)&original11,(uint64_t)(uintptr_t)&original12,(uint64_t)(uintptr_t)&original13,(uint64_t)(uintptr_t)&original14,(uint64_t)(uintptr_t)&original15,(uint64_t)(uintptr_t)&original16,(uint64_t)(uintptr_t)&original17,(uint64_t)(uintptr_t)&original18,(uint64_t)(uintptr_t)&original19,(uint64_t)(uintptr_t)&original20};
 const unsigned widths[]={2,2,4,2,2,2,4,2,2,4,4,4,2,4,4,4,2,2,2,4,2};

 for(unsigned operation=0;operation<21;++operation){autotest::Coverage coverage("editor_mass_lists_differential",addresses[operation]);
  for(unsigned scenario=0;scenario<((operation==13||operation==14)?29u:28u);++scenario){Case c={operation,scenario,widths[operation]};
   autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int result=coverage.observe(host,a,b);
   if(result){host->log("    editor list operation %u scenario %u pair %d status %d/%d bytes %lu/%lu\n",operation,scenario,result,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}
  }coverage.report(host);if(coverage.completed<20)return 1;
 }return 0;
}
