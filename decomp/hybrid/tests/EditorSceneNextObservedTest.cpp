#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <new>
#include <unistd.h>
#include "AutoTest.h"
#include "Detour.h"
#include "TArrayList.h"
extern "C" void* nodeVtable[] __asm__("_ZTV16CSceneNodeObject");
extern "C" void* positionVtable[] __asm__("_ZTV19CPositionableObject");
extern "C" void* objectVtable[] __asm__("_ZTV17CEditorBaseObject");
TL_ORIGINAL(void,original0,(void*,void*,long long,long long),"_ZN12CEditorScene25EditorBaseObjectChangedIDEP17CEditorBaseObjectxx")
extern "C" void candidate0(void*,void*,long long,long long) __asm__("_ZN12CEditorScene25EditorBaseObjectChangedIDEP17CEditorBaseObjectxx");
TL_ORIGINAL(void,original1,(void*),"_ZN12CEditorScene25DeleteAllObjectsFromSceneEv")
extern "C" void candidate1(void*) __asm__("_ZN12CEditorScene25DeleteAllObjectsFromSceneEv");
TL_ORIGINAL(void,original2,(void*,void*),"_ZN12CEditorScene19RemoveObjectInSceneEP17CEditorBaseObject")
extern "C" void candidate2(void*,void*) __asm__("_ZN12CEditorScene19RemoveObjectInSceneEP17CEditorBaseObject");
TL_ORIGINAL(void,original3,(void*,long long,void*,void*),"_ZN12CEditorScene11getChildrenExR10TArrayListIP17CEditorBaseObjectEP11CDescriptor")
extern "C" void candidate3(void*,long long,void*,void*) __asm__("_ZN12CEditorScene11getChildrenExR10TArrayListIP17CEditorBaseObjectEP11CDescriptor");
TL_ORIGINAL(void,original4,(void*,std::ofstream&,void*,void*),"_Z17saveBinaryObjectsP12CEditorSceneRSt14basic_ofstreamIcSt11char_traitsIcEER10TArrayListIP17CEditorBaseObjectEP28CDescriptorSaveConfiguration")
extern "C" void candidate4(void*,std::ofstream&,void*,void*) __asm__("_Z17saveBinaryObjectsP12CEditorSceneRSt14basic_ofstreamIcSt11char_traitsIcEER10TArrayListIP17CEditorBaseObjectEP28CDescriptorSaveConfiguration");
TL_ORIGINAL(int,original5,(void*,void*,void*,void*),"_ZN12CEditorScene11loadObjectsEP17CEditorBaseObjectP10CDataGroupP28CDescriptorLoadConfiguration")
extern "C" int candidate5(void*,void*,void*,void*) __asm__("_ZN12CEditorScene11loadObjectsEP17CEditorBaseObjectP10CDataGroupP28CDescriptorLoadConfiguration");
TL_ORIGINAL(void,original6,(void*,void*,void*,void*,void*),"_ZN12CEditorScene22configureGroupsToParseEP17CEditorBaseObjectR10CDataGroupR10TArrayListIPS2_EP28CDescriptorLoadConfiguration")
extern "C" void candidate6(void*,void*,void*,void*,void*) __asm__("_ZN12CEditorScene22configureGroupsToParseEP17CEditorBaseObjectR10CDataGroupR10TArrayListIPS2_EP28CDescriptorLoadConfiguration");
TL_ORIGINAL(unsigned,original7,(void*,void*,void*,void*),"_ZN12CEditorScene21saveObjectAndChildrenEP17CEditorBaseObjectP10CDataGroupP28CDescriptorSaveConfiguration")
extern "C" unsigned candidate7(void*,void*,void*,void*) __asm__("_ZN12CEditorScene21saveObjectAndChildrenEP17CEditorBaseObjectP10CDataGroupP28CDescriptorSaveConfiguration");
TL_ORIGINAL(void,original8,(void*,const wchar_t*),"_ZN12CEditorSceneC1EPKw")
extern "C" void candidate8(void*,const wchar_t*) __asm__("_ZN12CEditorSceneC1EPKw");
TL_ORIGINAL(void,original9,(void*),"_ZN12CEditorSceneD1Ev")
extern "C" void candidate9(void*) __asm__("_ZN12CEditorSceneD1Ev");
TL_ORIGINAL(unsigned,original10,(void*,void*,void*,void*),"_ZN12CEditorScene5cloneEPS_P10TArrayListIP17CEditorBaseObjectEP13CTimerStatics")
extern "C" unsigned candidate10(void*,void*,void*,void*) __asm__("_ZN12CEditorScene5cloneEPS_P10TArrayListIP17CEditorBaseObjectEP13CTimerStatics");
TL_ORIGINAL(unsigned,original11,(void*,void*,void*,long long,void*),"_ZN12CEditorScene5mergeEPS_P10TArrayListIP17CEditorBaseObjectExP13CTimerStatics")
extern "C" unsigned candidate11(void*,void*,void*,long long,void*) __asm__("_ZN12CEditorScene5mergeEPS_P10TArrayListIP17CEditorBaseObjectExP13CTimerStatics");
TL_FUNCTION(target_nodeParent,"_ZN16CSceneNodeObject18sceneNodeSetParentEPN4Ogre9SceneNodeEb")
TL_FUNCTION(target_removing,"_ZN11CDescriptor25EditorSceneRemovingObjectEP17CEditorBaseObject")
TL_FUNCTION(target_clean,"_ZN11CDescriptor21cleanForQuickShutDownEv")
TL_FUNCTION(target_canSave,"_ZN12CEditorScene16canObjectBeSavedEP16CResourceManagerP17CEditorBaseObject")
TL_FUNCTION(target_configure,"_ZN12CEditorScene22configureGroupsToParseEP17CEditorBaseObjectR10CDataGroupR10TArrayListIPS2_EP28CDescriptorLoadConfiguration")
TL_FUNCTION(target_loadObject,"_ZN12CEditorScene10loadObjectEP10CDataGroupP28CDescriptorLoadConfiguration")
TL_FUNCTION(target_getGroup,"_ZN10CDataGroup18GetDataGroupByNameERKSbIwSt11char_traitsIwESaIwEEb")
TL_FUNCTION(target_addGroup,"_ZN10CDataGroup12AddDataGroupERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(target_flag,"_ZN17CEditorBaseObject17HasBaseObjectFlagE18EEDITOROBJECT_FLAG")
TL_FUNCTION(target_saveParent,"_ZN12CEditorScene23saveObjectsHavingParentExP10CDataGroupP28CDescriptorSaveConfiguration")
TL_FUNCTION(target_baseCtor,"_ZN19CPositionableObjectC1EP16CResourceManagerPN4Ogre12SceneManagerE")
TL_FUNCTION(target_baseDtor,"_ZN19CPositionableObjectD1Ev")
TL_FUNCTION(target_managerCtor,"_ZN18CDescriptorManagerC1EP12CEditorScene")
TL_FUNCTION(target_enabled,"_ZN12CEditorScene10setEnabledEb")
TL_FUNCTION(target_deleteAll,"_ZN12CEditorScene25DeleteAllObjectsFromSceneEv")
TL_FUNCTION(target_getDescriptor,"_ZN12CEditorScene26GetDescriptorInSceneByNameEPKwb")
TL_FUNCTION(target_cloneLayout,"_ZN12CEditorScene11cloneLayoutEPS_P10TArrayListIP17CEditorBaseObjectEP13CTimerStatics")
TL_FUNCTION(target_binary,"_ZN11CDescriptor22saveObjectInBinaryFileERSt14basic_ofstreamIcSt11char_traitsIcEEP17CEditorBaseObjectP28CDescriptorSaveConfiguration")
TL_FUNCTION(target_children,"_ZN12CEditorScene11getChildrenExR10TArrayListIP17CEditorBaseObjectEP11CDescriptor")

namespace {
typedef std::map<long long,void*> Map;typedef TArrayList<void*> List;typedef std::vector<void*> Vector;
struct ListView{void**data;unsigned count,capacity,grow,pad;};struct Case{unsigned op,seed,flags,mode;};Case*input;autotest::Capture*output;void*active;void*scenes[2];void*objects[8];void*descriptors[3];void*groups[10];void*managers[2];void*configuration;List*currentList;unsigned calls,addCalls;Map*activeMap;
const long long ids[]={-1,0,1,-9,33,0x100000003LL,(-9223372036854775807LL-1),9223372036854775807LL};
void num(unsigned x){output->add(&x,4);}void ptr(void*p){output->add(&p,8);}void event(unsigned n,void*p){num(n);ptr(p);}void put(void*p,unsigned o,void*v){std::memcpy(static_cast<char*>(p)+o,&v,8);}void word(void*p,unsigned o,unsigned v){std::memcpy(static_cast<char*>(p)+o,&v,4);}void id(void*p,unsigned o,long long v){std::memcpy(static_cast<char*>(p)+o,&v,8);}void*pointer(void*p,unsigned o){void*v;std::memcpy(&v,static_cast<char*>(p)+o,8);return v;}
void change(){++calls;if(input->mode==1){put(active,0x68,managers[calls%2]);put(active,0x100,managers[calls%2]);}if(input->mode==2){id(objects[0],0x10,ids[(calls+input->seed)%8]);id(objects[0],0x18,ids[(calls+2)%8]);}if(input->mode==3)put(objects[0],0x38,descriptors[calls%3]);if(input->mode==4&&currentList&&currentList->size()>1)reinterpret_cast<ListView*>(currentList)->count--;}
void nodeParent(void*p,void*parent,bool destroy){event(1,p);ptr(parent);num(destroy);change();}
void removing(void*p,void*object){event(2,p);ptr(object);change();}
void clean(void*p){event(3,p);change();}
bool canSave(void*p,void*resources,void*object){event(4,p);ptr(resources);ptr(object);change();return (calls+input->seed)%3!=0;}
void configure(void*p,void*parent,void*group,List*out,void*config){event(5,p);ptr(parent);ptr(group);ptr(config);num(reinterpret_cast<ListView*>(out)->grow);currentList=out;for(unsigned i=0;i<input->flags%7;++i)out->add(groups[i+1]);if(input->mode==6&&out->size())reinterpret_cast<ListView*>(out)->capacity=1;change();}
int loadObject(void*p,void*group,void*config){event(6,p);ptr(group);ptr(config);change();return static_cast<int>(input->seed*456789u+calls);}
void*getGroup(void*p,const std::wstring&name,bool create){event(7,p);output->addText(name);num(create);change();return input->flags&8?NULL:groups[1];}
void*addGroup(void*p,const std::wstring&name){event(8,p);output->addText(name);change();return groups[(++addCalls)%10];}
bool flag(void*p,int flag){event(9,p);num(flag);change();return input->flags&8;}
unsigned saveParent(void*p,long long parent,void*group,void*config){event(10,p);output->add(&parent,8);ptr(group);ptr(config);change();return input->seed*1234567u;}
void baseCtor(void*p,void*resources,void*scene){event(11,p);ptr(resources);ptr(scene);std::memset(p,(input->seed*31+7)&255,0x100);new(static_cast<char*>(p)+0x40)std::wstring(L"base name");}
void baseDtor(void*p){event(12,p);output->add(p,0x190);reinterpret_cast<std::wstring*>(static_cast<char*>(p)+0x40)->~basic_string();}
void managerCtor(void*p,void*scene){num(13);ptr(scene);std::memset(p,(input->seed*17+3)&255,0x60);}
void enabled(void*p,bool enable){event(14,p);num(enable);num(pointer(p,0x100)!=NULL);output->addText(*reinterpret_cast<std::wstring*>(static_cast<char*>(p)+0x40));static_cast<unsigned char*>(p)[0xd4]=enable;}
void deleteAll(void*p){event(15,p);change();if(input->mode==5){activeMap->clear();reinterpret_cast<List*>(static_cast<char*>(p)+0x138)->clear();}}
void*getDescriptor(void*p,const wchar_t*name,bool create){event(16,p);output->addText(std::wstring(name));num(create);change();return (input->flags%3==0||(input->flags%3==1&&std::wstring(name)==L"Timeline"))?NULL:descriptors[1];}
void cloneLayout(void*p,void*other,List*list,void*timers){event(17,p);ptr(other);ptr(list);ptr(timers);change();(*activeMap)[712]=objects[2];}
bool binary(void*p,std::ofstream&file,void*object,void*config){event(18,p);ptr(object);ptr(config);unsigned n=0;for(;n<8&&object!=objects[n];++n){}file.write(reinterpret_cast<const char*>(&n),4);change();return input->flags&1;}
void children(void*p,long long parent,List*list,void*exclude){event(19,p);output->add(&parent,8);ptr(exclude);num(reinterpret_cast<ListView*>(list)->grow);change();if(parent==ids[0]&&input->flags%3)list->add(objects[1]);if(parent==ids[1]&&input->flags%3==2)list->add(objects[2]);}
void deleteObject(void*p){event(20,p);change();if(input->mode==5){for(Map::iterator i=activeMap->begin();i!=activeMap->end();++i)if(i->second==p){activeMap->erase(i);break;}}}
void about(void*p){event(21,p);change();}
void deleted(void*p,void*object){event(22,p);ptr(object);change();}
bool descriptorDeleted(void*p,void*object){event(23,p);ptr(object);change();return input->flags&1;}
void setParent(void*p,long long parent){event(24,p);output->add(&parent,8);id(p,0x18,parent);change();}
void setScene(void*p,void*scene){event(25,p);ptr(scene);put(p,0x48,scene);change();}
void save(void*p,void*object,void*group,void*config){event(26,p);ptr(object);ptr(group);ptr(config);change();}
unsigned loadFile(void*p,std::wstring name,bool merge,void*list,long long guid,bool create,void*timers){event(27,p);output->addText(name);num(merge);ptr(list);output->add(&guid,8);num(create);ptr(timers);*reinterpret_cast<std::wstring*>(static_cast<char*>(p)+0x168)=L"changed by load";change();return input->seed*1234567u;}
unsigned loadData(void*p,std::wstring name,void*data,void*list,long long guid,void*timers){event(28,p);output->addText(name);ptr(data);ptr(list);output->add(&guid,8);ptr(timers);*reinterpret_cast<std::wstring*>(static_cast<char*>(p)+0x168)=L"changed by merge";change();return input->seed*1234567u;}
void deleteAux(void*p){event(29,p);change();}
void listState(List&list){ListView&v=*reinterpret_cast<ListView*>(&list);num(v.count);num(v.capacity);num(v.grow);for(unsigned i=0;i<v.count;++i)ptr(v.data[i]);}
void sceneState(void*p){Map&map=*reinterpret_cast<Map*>(static_cast<char*>(p)+0x108);num(map.size());for(Map::iterator i=map.begin();i!=map.end();++i){output->add(&i->first,8);ptr(i->second);}listState(*reinterpret_cast<List*>(static_cast<char*>(p)+0x138));listState(*reinterpret_cast<List*>(static_cast<char*>(p)+0x150));output->addText(*reinterpret_cast<std::wstring*>(static_cast<char*>(p)+0x168));unsigned char copy[0x190];std::memcpy(copy,p,0x190);std::memset(copy+0x108,0,48);std::memset(copy+0x138,0,8);std::memset(copy+0x150,0,8);std::memset(copy+0x168,0,8);output->add(copy,sizeof(copy));}
void side(Case&c,bool ours,autotest::Capture&out){input=&c;output=&out;calls=addCalls=0;currentList=NULL;
 unsigned long long scene[2][0x190/8],obj[8][0x200/8],desc[3][0x200/8],data[10][0x60/8],manager[2][0x60/8],config[0xa0/8];
 std::memset(scene,(c.seed*23+13)&255,sizeof(scene));std::memset(obj,0,sizeof(obj));std::memset(desc,0,sizeof(desc));std::memset(data,0,sizeof(data));std::memset(manager,0,sizeof(manager));std::memset(config,0,sizeof(config));void*self=scene[0];active=self;configuration=config;
 void*sceneTable[90]={0};sceneTable[0x240/8]=reinterpret_cast<void*>(&about);sceneTable[0x238/8]=reinterpret_cast<void*>(&deleted);sceneTable[0x1e8/8]=reinterpret_cast<void*>(&loadFile);sceneTable[0x1f0/8]=reinterpret_cast<void*>(&loadData);
 void*objectTable[80];std::memcpy(objectTable,nodeVtable,sizeof(objectTable));objectTable[3]=reinterpret_cast<void*>(&deleteObject);objectTable[2+3]=reinterpret_cast<void*>(&setParent);objectTable[2+5]=reinterpret_cast<void*>(&setScene);
 void*positionTable[80];std::memcpy(positionTable,positionVtable,sizeof(positionTable));positionTable[3]=reinterpret_cast<void*>(&deleteObject);positionTable[2+3]=reinterpret_cast<void*>(&setParent);positionTable[2+5]=reinterpret_cast<void*>(&setScene);
 void*baseTable[10];std::memcpy(baseTable,objectVtable,sizeof(baseTable));baseTable[3]=reinterpret_cast<void*>(&deleteObject);baseTable[2+3]=reinterpret_cast<void*>(&setParent);baseTable[2+5]=reinterpret_cast<void*>(&setScene);
 void*descTable[30]={0};descTable[0x60/8]=reinterpret_cast<void*>(&descriptorDeleted);descTable[0x88/8]=reinterpret_cast<void*>(&save);void*auxTable[2]={NULL,reinterpret_cast<void*>(&deleteAux)};
 for(unsigned i=0;i<3;++i){descriptors[i]=desc[i];put(descriptors[i],0,descTable);}for(unsigned i=0;i<10;++i){groups[i]=data[i];put(groups[i],0,auxTable);new(static_cast<char*>(groups[i])+0x38)List(3);}
 for(unsigned i=0;i<8;++i){objects[i]=obj[i];put(objects[i],0,(c.seed+i)%3==0?positionTable+2:(c.seed+i)%3==1?objectTable+2:baseTable+2);id(objects[i],0x10,ids[i]);id(objects[i],0x18,ids[(i+c.seed/8)%8]);put(objects[i],0x38,descriptors[i%3]);put(objects[i],0x48,self);}
 for(unsigned i=0;i<2;++i){scenes[i]=scene[i];managers[i]=manager[i];put(scenes[i],0,sceneTable);put(scenes[i],0x68,managers[i]);put(scenes[i],0x100,managers[i]);new(static_cast<char*>(scenes[i])+0x108)Map;new(static_cast<char*>(scenes[i])+0x138)List(3);new(static_cast<char*>(scenes[i])+0x150)List(3);new(static_cast<char*>(scenes[i])+0x168)std::wstring(i?L"source/Сцена.layout":L"old/scene.layout");put(scenes[i],0x180,c.flags&32?NULL:groups[0]);put(managers[i],0,auxTable);Vector*v=new(static_cast<char*>(managers[i])+0x40)Vector;for(unsigned j=0;j<c.flags%4;++j)v->push_back(descriptors[j%3]);}
 activeMap=reinterpret_cast<Map*>(static_cast<char*>(self)+0x108);for(unsigned i=0;i<c.flags%9;++i)(*activeMap)[ids[i]]=objects[i];
 List&list0=*reinterpret_cast<List*>(static_cast<char*>(self)+0x138);List&list1=*reinterpret_cast<List*>(static_cast<char*>(self)+0x150);for(unsigned i=0;i<c.flags%9;++i){list0.add(objects[(i+c.seed/8)%8]);list1.add(objects[i]);}
 if(c.op==2){if(c.flags&8)put(objects[0],0x48,scenes[1]);if(c.flags&16)put(objects[0],0x38,NULL);}
 if(c.op==7&&c.flags&4)put(objects[0],0x38,NULL);
 List&dataChildren=*reinterpret_cast<List*>(static_cast<char*>(groups[1])+0x38);for(unsigned i=0;i<c.flags%8;++i)dataChildren.add(groups[i+2]);if(c.mode==6&&dataChildren.size())reinterpret_cast<ListView*>(&dataChildren)->capacity=1;
 List resultList(2);if(c.op==3||c.op==6){if(c.flags&4)resultList.add(objects[7]);}if(c.op==4){resultList.add(objects[0]);if(c.flags&1)resultList.add(objects[3]);currentList=&resultList;}
 std::wstring label=c.flags&8?L"":c.flags&4?L"Scene Ω":L"editor scene";
 if(c.op==8){std::memset(self,(c.seed*37+19)&255,0x190);}
 if(c.op==9){new(static_cast<char*>(self)+0x40)std::wstring(L"base");}
 char path[]="/tmp/otl-scene-observed-XXXXXX";int fd=mkstemp(path);if(fd<0)_exit(42);close(fd);std::ofstream file;if(c.op==4){file.open(path,std::ios::binary);if(c.flags&8)file.setstate(std::ios::failbit);}
 detour::Set patches;
 if(true){TL_REDIRECT(patches,target_nodeParent,&nodeParent);}
 if(true){TL_REDIRECT(patches,target_removing,&removing);}
 if(true){TL_REDIRECT(patches,target_clean,&clean);}
 if(c.op!=0){TL_REDIRECT(patches,target_canSave,&canSave);}
 if(c.op!=6){TL_REDIRECT(patches,target_configure,&configure);}
 if(true){TL_REDIRECT(patches,target_loadObject,&loadObject);}
 if(true){TL_REDIRECT(patches,target_getGroup,&getGroup);}
 if(true){TL_REDIRECT(patches,target_addGroup,&addGroup);}
 if(true){TL_REDIRECT(patches,target_flag,&flag);}
 if(true){TL_REDIRECT(patches,target_saveParent,&saveParent);}
 if(true){TL_REDIRECT(patches,target_baseCtor,&baseCtor);}
 if(true){TL_REDIRECT(patches,target_baseDtor,&baseDtor);}
 if(true){TL_REDIRECT(patches,target_managerCtor,&managerCtor);}
 if(true){TL_REDIRECT(patches,target_enabled,&enabled);}
 if(c.op!=1){TL_REDIRECT(patches,target_deleteAll,&deleteAll);}
 if(true){TL_REDIRECT(patches,target_getDescriptor,&getDescriptor);}
 if(true){TL_REDIRECT(patches,target_cloneLayout,&cloneLayout);}
 if(true){TL_REDIRECT(patches,target_binary,&binary);}
 if(c.op!=3){TL_REDIRECT(patches,target_children,&children);}
 if(patches.failed())_exit(41);
 switch(c.op){
 case 0:autotest::invoke(out,ours?candidate0:original0,self,c.flags&32?NULL:objects[0],ids[(c.seed/8)%8],ids[(c.seed/64+1)%8]);break;
 case 1:autotest::invoke(out,ours?candidate1:original1,self);break;
 case 2:autotest::invoke(out,ours?candidate2:original2,self,c.flags&32?NULL:objects[0]);break;
 case 3:autotest::invoke(out,ours?candidate3:original3,self,ids[(c.seed/8)%8],&resultList,c.flags&16?NULL:descriptors[0]);break;
 case 4:{void(*fn)(void*,std::ofstream&,void*,void*)=ours?candidate4:original4;if(!autotest::beginInvocation(out,fn))return;fn(self,file,&resultList,c.flags&16?NULL:configuration);out.callCompleted=1;break;}
 case 5:autotest::invoke(out,ours?candidate5:original5,self,objects[0],c.flags&16?NULL:groups[0],c.flags&32?NULL:configuration);break;
 case 6:autotest::invoke(out,ours?candidate6:original6,self,objects[0],groups[0],&resultList,c.flags&32?NULL:configuration);break;
 case 7:autotest::invoke(out,ours?candidate7:original7,self,c.flags&16?NULL:objects[0],c.flags&32?NULL:groups[0],configuration);break;
 case 8:autotest::invoke(out,ours?candidate8:original8,self,c.flags&16?NULL:label.c_str());break;
 case 9:autotest::invoke(out,ours?candidate9:original9,self);break;
 case 10:autotest::invoke(out,ours?candidate10:original10,self,c.flags&16?NULL:scenes[1],&resultList,configuration);break;
 case 11:autotest::invoke(out,ours?candidate11:original11,self,c.flags&16?NULL:scenes[1],&resultList,ids[(c.seed/8)%8],configuration);break;

 }
 if(c.op==4){num(file.rdstate());file.close();std::ifstream saved(path,std::ios::binary);std::string bytes((std::istreambuf_iterator<char>(saved)),std::istreambuf_iterator<char>());num(bytes.size());out.add(bytes.data(),bytes.size());}unlink(path);
 num(calls);num(addCalls);listState(resultList);
 if(c.op==8){out.addText(*reinterpret_cast<std::wstring*>(static_cast<char*>(self)+0x40));void*newManager=pointer(self,0x100);num(newManager!=NULL);if(newManager)out.add(newManager,0x60);put(self,0x100,NULL);}
 if(c.op==9){out.add(self,0x190);}else{sceneState(self);}
 sceneState(scenes[1]);out.add(obj,sizeof(obj));out.add(desc,sizeof(desc));out.add(config,sizeof(config));for(unsigned i=0;i<10;++i)listState(*reinterpret_cast<List*>(static_cast<char*>(groups[i])+0x38));for(unsigned i=0;i<2;++i){Vector*v=reinterpret_cast<Vector*>(static_cast<char*>(managers[i])+0x40);num(v->size());for(unsigned j=0;j<v->size();++j)ptr((*v)[j]);}patches.restore();
}
void original(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),false,out);}void recovered(void*p,autotest::Capture&out){side(*static_cast<Case*>(p),true,out);}
int run(const tlhybrid_host*host,unsigned op,const char*name){const uint64_t addresses[]={(uint64_t)(uintptr_t)original0,(uint64_t)(uintptr_t)original1,(uint64_t)(uintptr_t)original2,(uint64_t)(uintptr_t)original3,(uint64_t)(uintptr_t)original4,(uint64_t)(uintptr_t)original5,(uint64_t)(uintptr_t)original6,(uint64_t)(uintptr_t)original7,(uint64_t)(uintptr_t)original8,(uint64_t)(uintptr_t)original9,(uint64_t)(uintptr_t)original10,(uint64_t)(uintptr_t)original11};autotest::Coverage coverage(name,addresses[op]);for(unsigned n=0;n<576;++n){Case c={op,n,n/8,n%8};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);if(coverage.observe(host,a,b)){host->log("    scene next %u/%u status %d/%d bytes %lu/%lu\n",op,n,a.status,b.status,(unsigned long)a.capture.length,(unsigned long)b.capture.length);for(unsigned i=0;i<a.capture.length&&i<b.capture.length;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    first byte %u %u/%u\n",i,(unsigned char)a.capture.data[i],(unsigned char)b.capture.data[i]);break;}coverage.report(host);return 1;}}coverage.report(host);return 0;}
}
TL_TEST(editor_scene_next_changed_id){return run(host,0,"editor_scene_next_changed_id");}
TL_TEST(editor_scene_next_delete_all){return run(host,1,"editor_scene_next_delete_all");}
TL_TEST(editor_scene_next_remove){return run(host,2,"editor_scene_next_remove");}
TL_TEST(editor_scene_next_children){return run(host,3,"editor_scene_next_children");}
TL_TEST(editor_scene_next_save_binary){return run(host,4,"editor_scene_next_save_binary");}
TL_TEST(editor_scene_next_load_objects){return run(host,5,"editor_scene_next_load_objects");}
TL_TEST(editor_scene_next_configure_groups){return run(host,6,"editor_scene_next_configure_groups");}
TL_TEST(editor_scene_next_save_children){return run(host,7,"editor_scene_next_save_children");}
TL_TEST(editor_scene_next_construct){return run(host,8,"editor_scene_next_construct");}
TL_TEST(editor_scene_next_destroy){return run(host,9,"editor_scene_next_destroy");}
TL_TEST(editor_scene_next_clone){return run(host,10,"editor_scene_next_clone");}
TL_TEST(editor_scene_next_merge){return run(host,11,"editor_scene_next_merge");}
