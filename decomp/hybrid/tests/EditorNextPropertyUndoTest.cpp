#include <cstring>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
extern "C" void* editorGlobal __asm__("gEditor");
#define grouped (*reinterpret_cast<bool*>(0x1462770))
extern "C" void* groupUndo __asm__("g_pGroupedUndos");
TL_ORIGINAL(void,original0,(long long,int,int,void*),"_Z28EditorSetObjectPropertyArrayxiiP14UNIONDATA32BIT")
extern "C" void candidate0(long long,int,int,void*) __asm__("_Z28EditorSetObjectPropertyArrayxiiP14UNIONDATA32BIT");
TL_ORIGINAL(void,original1,(long long,unsigned,void*),"_Z23EditorSetObjectPropertyxjPv")
extern "C" void candidate1(long long,unsigned,void*) __asm__("_Z23EditorSetObjectPropertyxjPv");
TL_ORIGINAL(bool,original2,(long long),"_Z18EditorDeleteObjectx")
extern "C" bool candidate2(long long) __asm__("_Z18EditorDeleteObjectx");
TL_ORIGINAL(void*,original3,(unsigned,void*,void*),"_Z11cloneObjectjP17CEditorBaseObjectS0_")
extern "C" void* candidate3(unsigned,void*,void*) __asm__("_Z11cloneObjectjP17CEditorBaseObjectS0_");
TL_FUNCTION(target_lookup,"_Z16GetObjectInScenex")
TL_FUNCTION(target_getProperty,"_ZN11CDescriptor18GetPropertyByIndexEj")
TL_FUNCTION(target_variableType,"_ZN15CDescriptorProp15getVariableTypeEv")
TL_FUNCTION(target_undoProperty,"_ZN5CUndoC1EP17CEditorBaseObjectj")
TL_FUNCTION(target_undoEmpty,"_ZN5CUndoC1Ev")
TL_FUNCTION(target_addUndo,"_ZN7CEditor7addUndoEP5CUndob")
TL_FUNCTION(target_setProperty,"_ZN11CDescriptor11SetPropertyEP17CEditorBaseObjectjPKvj")
TL_FUNCTION(target_deleted,"_ZN5CUndo16AddObjectDeletedEP17CEditorBaseObject")
TL_FUNCTION(target_created,"_ZN12CEditorScene24CreateObjectByDescriptorEjP17CEditorBaseObjectS1_b")
TL_FUNCTION(target_objectCreated,"_ZN20CEditorObjectManager19EditorObjectCreatedEP17CEditorBaseObject")
TL_FUNCTION(target_objectSelected,"_ZN20CEditorObjectManager20EditorObjectSelectedEP17CEditorBaseObject")
TL_FUNCTION(target_newObject,"_ZN5CUndo12AddNewObjectEP17CEditorBaseObject")

namespace {
struct Case{unsigned op,seed,mode;};Case*input;autotest::Capture*output;void*editors[2];void*objs[4];void*props[2];void*scene;void*desc;void*data;unsigned propertyCalls,allocs;void*undos[8];
void num(unsigned x){output->add(&x,4);}void ptr(void*p){output->add(&p,8);}void event(unsigned n,void*p){num(n);ptr(p);}void put(void*p,unsigned o,void*v){std::memcpy(static_cast<char*>(p)+o,&v,8);}
void swap(){if(input->mode==6)editorGlobal=editors[1];if(input->mode==7)static_cast<char*>(editorGlobal)[0x49]=1;}
void*lookup(long long id){num(1);output->add(&id,8);swap();return input->mode==3?NULL:objs[0];}
void*getProperty(void*p,unsigned index){event(2,p);num(index);++propertyCalls;swap();return input->mode==5&&propertyCalls==1?NULL:props[propertyCalls%2];}
int variableType(void*p){event(3,p);return input->seed/12%3==0?5:input->seed/12%3==1?0:9;}
void undoProperty(void*p,void*object,unsigned index){event(4,p);ptr(object);num(index);std::memset(p,0x34,40);undos[allocs++]=p;swap();}
void undoEmpty(void*p){event(5,p);std::memset(p,0x56,40);undos[allocs++]=p;swap();}
void addUndo(void*p,void*undo,bool clear){event(6,p);ptr(undo);num(clear);output->add(undo,40);swap();}
void setProperty(void*p,void*object,unsigned index,const void*value,unsigned count){event(7,p);ptr(object);num(index);num(count);num(value==data);if(value!=data){output->addText(std::wstring(static_cast<const wchar_t*>(value),count));}else{output->add(data,64);}swap();}
void deleted(void*p,void*object){event(8,p);ptr(object);static_cast<char*>(p)[0x18]=0x27;swap();}
void*created(void*p,unsigned descriptor,void*object,void*owner,bool load){event(9,p);num(descriptor);ptr(object);ptr(owner);num(load);swap();return input->mode==5?NULL:objs[2];}
void objectCreated(void*p,void*object){event(10,p);ptr(object);if(input->mode==8)grouped=!grouped;swap();}
void objectSelected(void*p,void*object){event(11,p);ptr(object);if(input->mode==9)grouped=!grouped;swap();}
void newObject(void*p,void*object){event(12,p);ptr(object);static_cast<char*>(p)[0x1c]=0x62;swap();}
void side(Case&c,bool ours,autotest::Capture&out){input=&c;output=&out;propertyCalls=allocs=0;unsigned long long ed[2][64]={{0}},objects[4][32]={{0}},man[2][32]={{0}},descriptor[32]={0},properties[2][16]={{0}},sceneBytes[64]={0},undoGroup[5]={0};
 wchar_t text[64];for(unsigned i=0;i<64;++i)text[i]=static_cast<wchar_t>(0x410+(c.seed+i)%32);text[(c.seed/12)%15]=0;data=text;desc=descriptor;scene=sceneBytes;props[0]=properties[0];props[1]=properties[1];
 for(unsigned i=0;i<4;++i)objs[i]=objects[i];for(unsigned i=0;i<2;++i){editors[i]=ed[i];put(editors[i],0x120,man[i]);put(editors[i],0x58,c.mode==2?NULL:scene);static_cast<char*>(editors[i])[0x49]=c.mode==1;}
 put(objs[0],0x38,c.mode==4?NULL:desc);put(objs[0],0x48,c.mode==4?NULL:scene);editorGlobal=editors[0];grouped=(c.seed/12)&1;groupUndo=undoGroup;
 detour::Set patches;
 TL_REDIRECT(patches,target_lookup,&lookup);
 TL_REDIRECT(patches,target_getProperty,&getProperty);
 TL_REDIRECT(patches,target_variableType,&variableType);
 TL_REDIRECT(patches,target_undoProperty,&undoProperty);
 TL_REDIRECT(patches,target_undoEmpty,&undoEmpty);
 TL_REDIRECT(patches,target_addUndo,&addUndo);
 TL_REDIRECT(patches,target_setProperty,&setProperty);
 TL_REDIRECT(patches,target_deleted,&deleted);
 TL_REDIRECT(patches,target_created,&created);
 TL_REDIRECT(patches,target_objectCreated,&objectCreated);
 TL_REDIRECT(patches,target_objectSelected,&objectSelected);
 TL_REDIRECT(patches,target_newObject,&newObject);

 if(patches.failed())_exit(41);long long guid=static_cast<long long>(c.seed)*0x123456789LL;int lengths[]={0,1,3,16,-1};
 switch(c.op){case 0:autotest::invoke(out,ours?candidate0:original0,guid,int(c.seed*131),lengths[(c.seed/12)%5],data);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,guid,c.seed*131,data);break;
 case 2:autotest::invoke(out,ours?candidate2:original2,guid);break;
 case 3:{void*(*fn)(unsigned,void*,void*)=ours?candidate3:original3;if(!autotest::beginInvocation(out,fn))return;void*result=fn(c.seed*131,c.mode==3?NULL:objs[0],c.seed&1?NULL:objs[1]);out.callCompleted=1;ptr(result);break;}}
 num(propertyCalls);num(allocs);for(unsigned i=0;i<allocs;++i)out.add(undos[i],40);ptr(editorGlobal);num(grouped);ptr(groupUndo);out.add(ed,sizeof(ed));out.add(objects,sizeof(objects));out.add(man,sizeof(man));out.add(descriptor,sizeof(descriptor));out.add(properties,sizeof(properties));out.add(sceneBytes,sizeof(sceneBytes));out.add(undoGroup,sizeof(undoGroup));out.add(text,sizeof(text));patches.restore();
}
void original(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),false,c);}void recovered(void*p,autotest::Capture&c){side(*static_cast<Case*>(p),true,c);}
}
TL_TEST(editor_next_property_undo){const uint64_t addresses[]={(uint64_t)(uintptr_t)original0,(uint64_t)(uintptr_t)original1,(uint64_t)(uintptr_t)original2,(uint64_t)(uintptr_t)original3};
 for(unsigned op=0;op<4;++op){autotest::Coverage coverage("editor_next_property_undo",addresses[op]);for(unsigned n=0;n<360;++n){Case c={op,n,n%12};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    property/undo %u/%u status %d/%d bytes %lu/%lu\n",op,n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);}return 0;}
