#include "ParentPairs.h"
#include "Detour.h"
#include "LogicGroup.h"
#include "LogicObject.h"
#include "DataGroup.h"
#include <fstream>
struct SmallmatchPass7Probe {static unsigned id(CLogicObject*o){return o->m_iID;}static long long objectID(CLogicObject*o){return o->m_iObjectID;}};
#define TARGET(ret,a,b,args,symbol) TL_ORIGINAL(ret,a,args,symbol) extern "C" ret b args __asm__(symbol);
TARGET(void,oldAdd,newAdd,(CLogicGroup*,CLogicObject*),"_ZN11CLogicGroup14AddLogicObjectEP12CLogicObject")
TARGET(bool,oldRemove,newRemove,(CLogicGroup*,long long),"_ZN11CLogicGroup32RemoveLogicObjectsRefingObjectIDEx")
TARGET(void,oldSave,newSave,(CLogicGroup*,CDataGroup*,std::ofstream*,CDescriptorSaveConfiguration*),"_ZN11CLogicGroup25saveLogicGroupToDataGroupEP10CDataGroupPSt14basic_ofstreamIcSt11char_traitsIcEEP28CDescriptorSaveConfiguration")
TL_FUNCTION(removeIndex,"_ZN11CLogicGroup24RemoveLogicObjectByIndexEj")
TL_FUNCTION(removeLinks,"_ZN12CLogicObject30RemoveLogicLinksRefingObjectIDEx")
TL_FUNCTION(getObject,"_ZN12CLogicObject9GetObjectEv")
TL_FUNCTION(canSave,"_ZN12CEditorScene16canObjectBeSavedEP16CResourceManagerP17CEditorBaseObject")
TL_FUNCTION(saveGroup,"_ZN12CLogicObject26saveLogicObjectToDataGroupEP10CDataGroup")
TL_FUNCTION(saveBinary,"_ZN12CLogicObject27saveLogicObjectToBinaryFileEPSt14basic_ofstreamIcSt11char_traitsIcEE")
TL_FUNCTION(saveLinks,"_ZN12CLogicObject32saveLogicObjectLinksToBinaryFileEPSt14basic_ofstreamIcSt11char_traitsIcEE")
namespace {
autotest::Capture*cap;CLogicGroup*receiver;CLogicObject*entries[32];CEditorBaseObject*objects;CEditorScene*scene;CResourceManager*manager;unsigned seed,calls;long long query;
void n(unsigned x){parentpairs::scalar(*cap,x);}unsigned id(CLogicObject*p){if(!p)return 98;for(unsigned i=0;i<32;++i)if(entries[i]==p)return i;return 99;}
void mutate(){if(calls++==0&&seed%8==1){unsigned i=31;entries[i]=new CLogicObject(NULL,query+1,i);receiver->m_logicObjects.add(entries[i]);}else if(calls==1&&seed%8==2&&receiver->m_logicObjects.size()>2)receiver->m_logicObjects.removeAt(1);}
bool remove(CLogicGroup*p,unsigned i){n(1);n(i);if(p!=receiver||i>=p->m_logicObjects.size()){cap->issue=autotest::Capture::InvalidReport;return false;}CLogicObject*object=p->m_logicObjects[i];n(id(object));p->m_logicObjects[i]=NULL;mutate();return (seed+i)%3!=0;}
bool links(CLogicObject*p,long long q){unsigned i=id(p);n(2);n(i);parentpairs::scalar(*cap,q);if(i==99||q!=query)cap->issue=autotest::Capture::InvalidReport;mutate();return (seed+i)%4!=0;}
CEditorBaseObject* get(CLogicObject*p){unsigned i=id(p);n(3);n(i);if(i>=12){cap->issue=autotest::Capture::InvalidReport;return NULL;}return seed%4==3&&(seed+i)%3==0?NULL:objects+i;}
bool eligible(CEditorScene*p,CResourceManager*m,CEditorBaseObject*object){unsigned i=unsigned(object-objects);n(4);n(i);n(p==scene);n(m==manager);if(p!=scene||m!=manager||i>=12)cap->issue=autotest::Capture::InvalidReport;return (seed+i)%3!=0;}
void save(CLogicObject*p,CDataGroup*group){unsigned i=id(p);n(5);n(i);cap->addText(group->GetGroupName());group->AddDataGroup(L"NODE")->AddDataValue(L"ID",i);}
void binary(CLogicObject*p,std::ofstream*stream){unsigned i=id(p);n(6);n(i);stream->write(reinterpret_cast<const char*>(&i),4);}
void binaryLinks(CLogicObject*p,std::ofstream*stream){unsigned i=id(p);n(7);n(i);unsigned marker=i+100;stream->write(reinterpret_cast<const char*>(&marker),4);}
void side(void*raw,autotest::Capture&out,bool ours,unsigned mode){seed=static_cast<parentpairs::Case*>(raw)->seed;cap=&out;calls=0;for(unsigned i=0;i<32;++i)entries[i]=NULL;CLogicGroup group(NULL);receiver=&group;unsigned count=seed%18;query=seed%9==0?-1:0x100000003LL;CEditorBaseObject base[12];objects=base;unsigned long long sceneStorage[64]={0},managerStorage[16]={0};scene=reinterpret_cast<CEditorScene*>(sceneStorage);manager=reinterpret_cast<CResourceManager*>(managerStorage);group.m_pResourceManager=manager;
 if(mode==2)count=seed%12;for(unsigned i=0;i<count;++i){if((i+seed)%5&&!(mode==2&&i==0)){entries[i]=new CLogicObject(NULL,(i+seed)%4?query+1:query,i+71);group.m_logicObjects.add(entries[i]);}else group.m_logicObjects.add(NULL);if(i<12)base[i].SetSceneOwner(scene);}detour::Set patches;
 if(mode==0){entries[30]=new CLogicObject(NULL,17,777);typedef void(*Fn)(CLogicGroup*,CLogicObject*);Fn fn=ours?newAdd:oldAdd;autotest::invoke(out,fn,&group,entries[30]);n(SmallmatchPass7Probe::id(entries[30]));
 }else if(mode==1){TL_REDIRECT(patches,removeIndex,&remove);TL_REDIRECT(patches,removeLinks,&links);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}typedef bool(*Fn)(CLogicGroup*,long long);Fn fn=ours?newRemove:oldRemove;if(!autotest::beginInvocation(out,fn))return;bool result=fn(&group,query);out.callCompleted=1;n(result);n(calls);
 }else{TL_REDIRECT(patches,getObject,&get);TL_REDIRECT(patches,canSave,&eligible);TL_REDIRECT(patches,saveGroup,&save);TL_REDIRECT(patches,saveBinary,&binary);TL_REDIRECT(patches,saveLinks,&binaryLinks);if(patches.failed()){out.issue=autotest::Capture::InvalidReport;return;}CDataGroup data(L"ROOT",NULL,2,2,NULL);char path[]="/tmp/otl-advance-graph-XXXXXX";int fd=mkstemp(path);if(fd<0){out.issue=autotest::Capture::InvalidReport;return;}close(fd);std::ofstream stream(path,std::ios::binary);typedef void(*Fn)(CLogicGroup*,CDataGroup*,std::ofstream*,CDescriptorSaveConfiguration*);Fn fn=ours?newSave:oldSave;autotest::invoke(out,fn,&group,seed%4<=1?&data:NULL,seed%4==3?NULL:&stream,reinterpret_cast<CDescriptorSaveConfiguration*>(seed&1?1:0));n(data.GetNumberOfDataGroups());if(data.GetNumberOfDataGroups()){CDataGroup*g=data.GetDataGroup(0);out.addText(g->GetGroupName());n(g->GetNumberOfDataGroups());for(unsigned i=0;i<g->GetNumberOfDataGroups();++i)n(g->GetDataGroup(i)->GetDataValue(L"ID",~0u));}stream.close();std::ifstream file(path,std::ios::binary);char bytes[256];file.read(bytes,sizeof(bytes));unsigned length=file.gcount();n(length);out.add(bytes,length);file.close();unlink(path);}
 n(group.m_logicObjects.size());for(unsigned i=0;i<group.m_logicObjects.size();++i)n(id(group.m_logicObjects[i]));group.m_logicObjects.clear();patches.restore();for(unsigned i=0;i<32;++i)if(entries[i])delete entries[i];}
void aa(void*p,autotest::Capture&c){side(p,c,false,0);}void ab(void*p,autotest::Capture&c){side(p,c,true,0);}void ra(void*p,autotest::Capture&c){side(p,c,false,1);}void rb(void*p,autotest::Capture&c){side(p,c,true,1);}void sa(void*p,autotest::Capture&c){side(p,c,false,2);}void sb(void*p,autotest::Capture&c){side(p,c,true,2);}
}
TL_TEST(advance_logic_group_add){return parentpairs::run(host,"advance_logic_group_add",(uintptr_t)oldAdd,54,aa,ab);}
TL_TEST(advance_logic_group_remove){return parentpairs::run(host,"advance_logic_group_remove",(uintptr_t)oldRemove,72,ra,rb);}
TL_TEST(advance_logic_group_save){return parentpairs::run(host,"advance_logic_group_save",(uintptr_t)oldSave,60,sa,sb);}
