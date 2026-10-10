// Original/replacement comparisons for animation routing, resource reloads
// and property strings. Real original RTTI distinguishes model, character and
// unrelated objects. Collaborator callbacks exercise changes during traversal.
// Property counts stay inside the actual 4000-byte buffer, or take the original
// no-copy guard; the unsafe intermediate overflow range is never executed.
#include <cstring>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void* editorGlobal __asm__("gEditor");
extern "C" wchar_t editorString[1000] __asm__("sEditorString");
extern "C" unsigned char editorMemory[4000] __asm__("sEditorTmpMemory");
extern "C" void* modelTable[] __asm__("_ZTV13CGenericModel");
extern "C" void* characterTable[] __asm__("_ZTV10CCharacter");
extern "C" void* objectTable[] __asm__("_ZTV17CEditorBaseObject");
extern "C" void* monsterTable[] __asm__("_ZTV18CMonsterDescriptor");
extern "C" void* descriptorTable[] __asm__("_ZTV11CDescriptor");
TL_ORIGINAL(wchar_t*,original0,(long long,unsigned),"_Z29EditorGetObjectPropertyStringxj")
extern "C" wchar_t* candidate0(long long,unsigned) __asm__("_Z29EditorGetObjectPropertyStringxj");
TL_ORIGINAL(void,original1,(long long,bool),"_Z30EditorSetActiveAnimationPausedxb")
extern "C" void candidate1(long long,bool) __asm__("_Z30EditorSetActiveAnimationPausedxb");
TL_ORIGINAL(float,original2,(long long),"_Z36EditorGetActiveAnimationTimePositionx")
extern "C" float candidate2(long long) __asm__("_Z36EditorGetActiveAnimationTimePositionx");
TL_ORIGINAL(void,original3,(long long,float),"_Z36EditorSetActiveAnimationTimePositionxf")
extern "C" void candidate3(long long,float) __asm__("_Z36EditorSetActiveAnimationTimePositionxf");
TL_ORIGINAL(void,original4,(long long),"_Z27EditorReloadModelAnimationsx")
extern "C" void candidate4(long long) __asm__("_Z27EditorReloadModelAnimationsx");
TL_ORIGINAL(void,original5,(wchar_t*),"_Z16EditorReloadItemPw")
extern "C" void candidate5(wchar_t*) __asm__("_Z16EditorReloadItemPw");
TL_ORIGINAL(void,original6,(wchar_t*),"_Z16EditorReloadPropPw")
extern "C" void candidate6(wchar_t*) __asm__("_Z16EditorReloadPropPw");
TL_ORIGINAL(void,original7,(wchar_t*),"_Z18EditorReloadPlayerPw")
extern "C" void candidate7(wchar_t*) __asm__("_Z18EditorReloadPlayerPw");
TL_ORIGINAL(void,original8,(),"_Z20EditorReloadMonstersv")
extern "C" void candidate8() __asm__("_Z20EditorReloadMonstersv");
TL_FUNCTION(target_lookup,"_Z16GetObjectInScenex")
TL_FUNCTION(target_getModel,"_ZN10CCharacter12getUnitModelEv")
TL_FUNCTION(target_getTime,"_ZN13CGenericModel16getAnimationTimeEv")
TL_FUNCTION(target_setTime,"_ZN13CGenericModel16setAnimationTimeEf")
TL_FUNCTION(target_update,"_ZN13CGenericModel15updateAnimationEfb")
TL_FUNCTION(target_clear,"_ZN13CGenericModel15clearAnimationsEv")
TL_FUNCTION(target_reload,"_ZN13CGenericModel16reloadAnimationsEv")
TL_FUNCTION(target_bones,"_ZN10CCharacter8getBonesEv")
TL_FUNCTION(target_singleton,"_ZN17CUnitResourceList12getSingletonEv")
TL_FUNCTION(target_loadFile,"_ZN17CUnitResourceList8loadFileE16ERESOURCE_GROUPSSbIwSt11char_traitsIwESaIwEES4_bP10CDataGroup")
TL_FUNCTION(target_descriptor,"_ZN18CDescriptorManager13GetDescriptorEPKwb")
TL_FUNCTION(target_monsters,"_ZN18CMonsterDescriptor14ReloadMonstersEv")
TL_FUNCTION(target_property,"_ZN11CDescriptor16GetPropertyValueEP17CEditorBaseObjectjRj")

namespace {
struct Case {unsigned operation,mode,kind,seed,count;long long guid;float amount;bool flag;};
const Case* input;autotest::Capture* capture;
void* editors[2];void* objects[4];void* scenes[8];void* managers[8];void* descriptors[8];void* resource;
wchar_t* propertyData;unsigned lookupCalls,modelCalls,reloadCalls,descriptorCalls,propertyCalls;
void number(unsigned n){capture->add(&n,4);}
void pointerAt(void*p,unsigned at,void*v){std::memcpy(static_cast<char*>(p)+at,&v,8);}
void integerAt(void*p,unsigned at,unsigned v){std::memcpy(static_cast<char*>(p)+at,&v,4);}
unsigned identity(void*p){if(!p)return 0;for(unsigned i=0;i<2;++i)if(p==editors[i])return 1+i;
 for(unsigned i=0;i<4;++i)if(p==objects[i])return 10+i;
 for(unsigned i=0;i<8;++i){if(p==scenes[i])return 20+i;if(p==managers[i])return 30+i;if(p==descriptors[i])return 40+i;}
 return p==resource?50:999;}
void event(unsigned code,void*p){number(code);number(identity(p));}
void* chosenObject(){switch(input->kind){case 0:return NULL;case 1:return objects[0];case 2:case 4:case 5:return objects[1];case 3:return objects[2];default:return objects[3];}}
void* lookup(long long guid){number(1);capture->add(&guid,8);++lookupCalls;
 if(input->mode==5)editorGlobal=editors[1];return input->mode==3?NULL:chosenObject();}
void* getModel(void*p){event(2,p);++modelCalls;return input->kind==4?NULL:objects[input->kind==5?3:0];}
float getTime(void*p){event(3,p);return input->amount;}
void setTime(void*p,float time){event(4,p);capture->add(&time,4);std::memcpy(static_cast<char*>(p)+0x1f0,&time,4);}
void update(void*p,float elapsed,bool force){event(5,p);capture->add(&elapsed,4);number(force);}
void clear(void*p){event(6,p);if(input->mode==6)editorGlobal=editors[1];}
void reload(void*p){event(7,p);++reloadCalls;
 if(input->mode==10&&chosenObject())pointerAt(chosenObject(),0,characterTable+2);
 if(input->mode==11&&chosenObject())pointerAt(chosenObject(),0,objectTable+2);}
void bones(void*p){event(8,p);}
void* singleton(){event(9,resource);if(input->mode==5)editorGlobal=editors[1];return resource;}
void loadFile(void*p,int group,std::wstring label,std::wstring path,bool overwrite,void* parent){event(10,p);number(group);capture->addText(label);capture->addText(path);number(overwrite);number(identity(parent));}
void* descriptor(void*p,const wchar_t* name,bool create){event(11,p);capture->addText(std::wstring(name));number(create);++descriptorCalls;
 if(input->mode==7)return NULL;for(unsigned i=0;i<8;++i)if(p==managers[i])return descriptors[i];return NULL;}
void monsters(void*p){event(12,p);++reloadCalls;
 if(input->mode==9)integerAt(editors[0],0xc8,1);
 if(input->mode==10)editorGlobal=editors[1];
 if(input->mode==11)integerAt(editors[0],0xcc,0);}
void* property(void*p,void*object,unsigned index,unsigned* count){event(13,p);number(identity(object));number(index);number(*count);
 const unsigned lengths[]={0,1,5,999,998,1000000,0xffffffffu};++propertyCalls;*count=input->mode==12?0u:lengths[input->kind];return propertyData;}
void side(Case&c,bool ours,autotest::Capture&out){
 input=&c;capture=&out;lookupCalls=modelCalls=reloadCalls=descriptorCalls=propertyCalls=0;
 unsigned long long editorBytes[2][64]={{0}},objectBytes[4][128]={{0}},sceneBytes[8][64]={{0}},managerBytes[8][16]={{0}},descriptorBytes[8][64]={{0}},resourceBytes[32]={0};
 wchar_t propertyBuffer[1024];propertyData=propertyBuffer;
 for(unsigned i=0;i<1024;++i)propertyBuffer[i]=static_cast<wchar_t>(0x410+(i+c.seed)%32);
 if(c.flag)propertyBuffer[3]=0;
 resource=resourceBytes;
 for(unsigned i=0;i<2;++i){editors[i]=editorBytes[i];static_cast<unsigned char*>(editors[i])[0x49]=c.mode==1;
  pointerAt(editors[i],0x58,c.mode==2?NULL:resource);}
 for(unsigned i=0;i<4;++i){objects[i]=objectBytes[i];pointerAt(objects[i],0,(i==1?characterTable:i==2?objectTable:modelTable)+2);
  static_cast<unsigned char*>(objects[i])[0x1e8]=!c.flag;}
 void* scenePointers[8];
 for(unsigned i=0;i<8;++i){scenes[i]=sceneBytes[i];managers[i]=managerBytes[i];descriptors[i]=descriptorBytes[i];scenePointers[i]=scenes[i];
  pointerAt(scenes[i],0x100,c.mode==6&&i%2?NULL:managers[i]);pointerAt(descriptors[i],0,(c.mode==8||i%3==1?descriptorTable:monsterTable)+2);}
 for(unsigned i=0;i<4;++i)pointerAt(objects[i],0x38,c.mode==4?NULL:descriptors[0]);
 pointerAt(editors[0],0xc0,scenePointers);integerAt(editors[0],0xc8,c.count);integerAt(editors[0],0xcc,c.mode==4?2:8);
 pointerAt(editors[1],0xc0,scenePointers+6);integerAt(editors[1],0xc8,1);integerAt(editors[1],0xcc,1);
 editorGlobal=editors[0];std::memset(editorString,0x5a,sizeof(editorString));std::memset(editorMemory,0xa7,sizeof(editorMemory));
 std::wstring path;
 switch(c.kind){case 0:path=L"";break;case 1:path=L"media/units/item.dat";break;case 2:path=L"Персонажи/Ω.dat";break;
  case 3:path=std::wstring(L"a\0b",3);break;case 4:path=std::wstring(1024,L'x');break;case 5:path=L"../units/test.DAT";break;default:path=L"a/b/c.dat";break;}
 detour::Set patches;
 TL_REDIRECT(patches,target_lookup,&lookup);
 TL_REDIRECT(patches,target_getModel,&getModel);
 TL_REDIRECT(patches,target_getTime,&getTime);
 TL_REDIRECT(patches,target_setTime,&setTime);
 TL_REDIRECT(patches,target_update,&update);
 TL_REDIRECT(patches,target_clear,&clear);
 TL_REDIRECT(patches,target_reload,&reload);
 TL_REDIRECT(patches,target_bones,&bones);
 TL_REDIRECT(patches,target_singleton,&singleton);
 TL_REDIRECT(patches,target_loadFile,&loadFile);
 TL_REDIRECT(patches,target_descriptor,&descriptor);
 TL_REDIRECT(patches,target_monsters,&monsters);
 TL_REDIRECT(patches,target_property,&property);
 if(patches.failed())_exit(41);
 switch(c.operation){
 case 0:{wchar_t*(*fn)(long long,unsigned)=ours?&candidate0:&original0;if(!autotest::beginInvocation(out,fn))return;wchar_t* value=fn(c.guid,c.seed);out.callCompleted=1;if(c.mode==12&&(propertyCalls!=1||value!=editorString||editorString[0]!=0||*reinterpret_cast<wchar_t*>(editorMemory)!=0))out.issue=autotest::Capture::InvalidReport;number(!value?0:value==editorString?1:999);break;}
 case 1:autotest::invoke(out,ours?&candidate1:&original1,c.guid,c.flag);break;
 case 2:autotest::invoke(out,ours?&candidate2:&original2,c.guid);break;
 case 3:autotest::invoke(out,ours?&candidate3:&original3,c.guid,c.amount);break;
 case 4:autotest::invoke(out,ours?&candidate4:&original4,c.guid);break;
 case 5:autotest::invoke(out,ours?&candidate5:&original5,const_cast<wchar_t*>(path.c_str()));break;
 case 6:autotest::invoke(out,ours?&candidate6:&original6,const_cast<wchar_t*>(path.c_str()));break;
 case 7:autotest::invoke(out,ours?&candidate7:&original7,const_cast<wchar_t*>(path.c_str()));break;
 case 8:autotest::invoke(out,ours?&candidate8:&original8);break;

 }
 number(lookupCalls);number(modelCalls);number(reloadCalls);number(descriptorCalls);number(propertyCalls);number(identity(editorGlobal));
 out.add(editorString,sizeof(editorString));out.add(editorMemory,sizeof(editorMemory));out.add(editorBytes,sizeof(editorBytes));out.add(objectBytes,sizeof(objectBytes));
 patches.restore();
}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}
void recovered(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(editor_mass_animation_resources_differential){
 const uint64_t addresses[]={
(uint64_t)(uintptr_t)&original0,(uint64_t)(uintptr_t)&original1,(uint64_t)(uintptr_t)&original2,(uint64_t)(uintptr_t)&original3,(uint64_t)(uintptr_t)&original4,(uint64_t)(uintptr_t)&original5,(uint64_t)(uintptr_t)&original6,(uint64_t)(uintptr_t)&original7,(uint64_t)(uintptr_t)&original8};

 const unsigned bits[]={0,0x80000000u,0x3eaaaaabu,0xbf800000u,0x7f800000u,0xff800000u,0x7fc01234u};
 for(unsigned operation=0;operation<9;++operation){autotest::Coverage coverage("editor_mass_animation_resources_differential",addresses[operation]);
  for(unsigned n=0;n<504;++n){float amount;unsigned raw=bits[(n/7)%7];std::memcpy(&amount,&raw,4);
   Case c={operation,n%12,(n/12)%7,n/12,(n/12)%8,static_cast<long long>(n)*0x123456789LL,amount,((n/84)%2)!=0};
   autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int result=coverage.observe(host,a,b);
   if(result){host->log("    editor animation/resources operation %u case %u pair %d status %d/%d bytes %lu/%lu\n",operation,n,result,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}
  }
  if(operation==0){
   Case c={0,12,1,0,0,1,0.0f,false};
   autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
   if(coverage.observe(host,a,b)){host->log("    editor property valid-object zero-count witness failed\n");coverage.report(host);return 1;}
  }
  coverage.report(host);
  if(coverage.completed!=(operation==0?505u:504u)||coverage.different||coverage.missing)return 1;
 }return 0;
}
