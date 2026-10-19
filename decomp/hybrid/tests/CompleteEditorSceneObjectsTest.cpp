#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "EditorScene.h"
#include "DescriptorManager.h"
#include "Descriptor.h"
#include "LogicGroupDescriptor.h"
#include "RandomGroupDescriptor.h"
#include "Layout.h"
#include "LayoutDescriptor.h"
#include "DataValue.h"
#include "TimerStatics.h"
#undef protected
#undef private
#include "Utilities.h"
#include "tests/NativeMenuClient.h"
#include "tests/NativeEditorControls.h"
#include "tests/CharacterEmptyGlobals.h"
#include "tests/SmallMassCompare.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,esCtor,(CEditorScene*,const wchar_t*),"_ZN12CEditorSceneC1EPKw")
TL_ORIGINAL(void,esDtor,(CEditorScene*),"_ZN12CEditorSceneD1Ev")
TL_ORIGINAL(void,esInit,(CEditorScene*,CResourceManager*,unsigned),"_ZN12CEditorScene9InitSceneEP16CResourceManagerj")
TL_ORIGINAL(CEditorBaseObject*,esCreateOld,(CEditorScene*,CDescriptor*,CEditorBaseObject*,CEditorBaseObject*,bool),"_ZN12CEditorScene24CreateObjectByDescriptorEP11CDescriptorP17CEditorBaseObjectS3_b")
TL_ORIGINAL(void,esDeleteOld,(CEditorScene*,CEditorBaseObject*),"_ZN12CEditorScene19DeleteObjectInSceneEP17CEditorBaseObject")
TL_ORIGINAL(void,esGetOld,(CEditorScene*,const std::wstring&,TArrayList<CEditorBaseObject*>*),"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEEP10TArrayListIP17CEditorBaseObjectE")
TL_ORIGINAL(void,esSaveOld,(CEditorScene*,CDataGroup*,unsigned),"_ZN12CEditorScene36SaveDescriptionOfSceneAndDescriptorsEP10CDataGroupj")
TL_ORIGINAL(void,esRollOld,(CRandomGroup*,TArrayList<CEditorBaseObject*>&,TArrayList<CRandomGroup*>&),"_Z9rollGroupP12CRandomGroupR10TArrayListIP17CEditorBaseObjectERS1_IS0_E")
TL_ORIGINAL(int,esLoadOld,(CEditorScene*,CDataGroup*,CDescriptorLoadConfiguration*),"_ZN12CEditorScene10loadObjectEP10CDataGroupP28CDescriptorLoadConfiguration")
extern "C" char esMicroseconds_linked[] __asm__("_ZN4Ogre5Timer15getMicrosecondsEv");
extern "C" CEditorBaseObject* esCreateNew(CEditorScene*,CDescriptor*,CEditorBaseObject*,CEditorBaseObject*,bool) __asm__("_ZN12CEditorScene24CreateObjectByDescriptorEP11CDescriptorP17CEditorBaseObjectS3_b");
extern "C" void esDeleteNew(CEditorScene*,CEditorBaseObject*) __asm__("_ZN12CEditorScene19DeleteObjectInSceneEP17CEditorBaseObject");
extern "C" void esGetNew(CEditorScene*,const std::wstring&,TArrayList<CEditorBaseObject*>*) __asm__("_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEEP10TArrayListIP17CEditorBaseObjectE");
extern "C" void esSaveNew(CEditorScene*,CDataGroup*,unsigned) __asm__("_ZN12CEditorScene36SaveDescriptionOfSceneAndDescriptorsEP10CDataGroupj");
extern "C" void esRollNew(CRandomGroup*,TArrayList<CEditorBaseObject*>&,TArrayList<CRandomGroup*>&) __asm__("_Z9rollGroupP12CRandomGroupR10TArrayListIP17CEditorBaseObjectERS1_IS0_E");
extern "C" int esLoadNew(CEditorScene*,CDataGroup*,CDescriptorLoadConfiguration*) __asm__("_ZN12CEditorScene10loadObjectEP10CDataGroupP28CDescriptorLoadConfiguration");
namespace {
nativegame::Services*services;
unsigned ticks;
unsigned long microseconds(Ogre::Timer*){return 1000ul*++ticks;}
struct Scene {
 CResourceManager resources;CEditorScene*scene;
 Scene(unsigned flags):resources(services->scene),scene(static_cast<CEditorScene*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEditorScene),0,0,0))){esCtor(scene,L"Fixture Scene");esInit(scene,&resources,flags);}
 ~Scene(){esDtor(scene);Ogre::NedAllocImpl::deallocBytes(scene);}
};
void number(autotest::Capture&out,unsigned x){out.add(&x,4);}
void snapshot(autotest::Capture&out,CEditorScene&scene){
 number(out,scene.m_Objects.size());number(out,scene.m_ObjectList0.size());
 CDescriptorManager*manager=scene.getDescriptorManager();number(out,manager->m_descriptors.size());
 for(unsigned i=0;i<manager->m_descriptors.size();++i){CDescriptor*d=manager->m_descriptors[i];out.addText(d->m_sName);number(out,d->getObjectCount());for(unsigned j=0;j<d->getObjectCount();++j){CEditorBaseObject*o=d->getObject(j);out.addText(o->getName());number(out,o->getDescriptor()==d);number(out,o->getSceneOwner()==&scene);}}
}
CDescriptor* addLogic(CEditorScene&scene,const wchar_t*name){CDescriptor*d=new CLogicGroupDescriptor(name,L"Fixture",L"Native descriptor");scene.AddDescriptor(d);return d;}
void side(smallmass::Case&c,bool ours,autotest::Capture&out){
 unsigned seed=c.index;Scene fixture(seed%8);CEditorScene&s=*fixture.scene;UTILITIES::setSeed(seed*73+19);UTILITIES::setSeedVolatile(seed*37+5);
 CDescriptor*first=addLogic(s,L"Fixture Logic");CDescriptor*second=addLogic(s,L"Other Logic");
 CEditorBaseObject*objects[12]={0};unsigned count=seed%9;
 for(unsigned i=0;i<count;++i){objects[i]=esCreateOld(&s,i%3?first:second,NULL,NULL,false);if(!objects[i])std::abort();objects[i]->SetName(i%2?L"First":L"Second");}
 if(c.op==0){
  CDataGroup root(L"ROOT",NULL,2,2,NULL);CDescriptorManager*saved=s.m_pDescriptorManager;if(seed/8%2)s.m_pDescriptorManager=NULL;
  autotest::invoke(out,ours?esSaveNew:esSaveOld,&s,&root,seed*0x13234567u);s.m_pDescriptorManager=saved;
  CDataGroup*data=root.GetDataGroupByName(L"SCENE",false);number(out,data!=NULL);if(data){out.addText(data->GetDataValue(L"NAME",L"missing"));number(out,data->GetDataValue(L"ID",0u));number(out,data->GetDataValue(L"SAVEENABLED",-77));number(out,data->m_DataValues.size());number(out,data->m_DataGroups.size());for(unsigned i=0;i<data->GetNumberOfDataValues();++i)number(out,data->GetDataValue(i)->GetValueType());}
 }else if(c.op==1){
  CEditorBaseObject*source=count&&seed/3%2?objects[0]:NULL;CEditorBaseObject*parent=count>1&&seed/5%2?objects[1]:NULL;CDescriptor*descriptor=seed%7==0?NULL:(source?source->getDescriptor():first);
  CEditorBaseObject*result=NULL;autotest::beginInvocation(out,ours?esCreateNew:esCreateOld);result=(ours?esCreateNew:esCreateOld)(&s,descriptor,source,parent,bool(seed%2));out.callCompleted=1;
  number(out,result!=NULL);if(result){number(out,result->getDescriptor()==descriptor);number(out,result->getSceneOwner()==&s);number(out,s.m_Objects.find(result->getGuid())!=s.m_Objects.end());out.addText(result->getName());}
 }else if(c.op==2){
  CEditorBaseObject*target=count?objects[seed%count]:NULL;CEditorBaseObject foreign;foreign.SetSceneOwner(seed/7%2?&s:NULL);if(seed%5==0)target=&foreign;
  if(count&&seed/4%2){objects[0]->getDescriptor()->m_iFlags|=0x20;for(unsigned i=1;i<count;++i)objects[i]->setParentGuid(objects[0]->getGuid());target=objects[0];}
  autotest::invoke(out,ours?esDeleteNew:esDeleteOld,&s,target);
 }else if(c.op==3){
  const wchar_t*links[]={L"Layout Link",L"Layout Link Particle",L"Layout Link Timeline"};
  for(unsigned k=0;k<seed%4;++k){CDescriptor*d=new CLayoutDescriptor(links[k],static_cast<ELAYOUT_TYPES>(1));s.AddDescriptor(d);for(unsigned j=0;j<1+seed/4%2;++j){CEditorScene*nested=dynamic_cast<CEditorScene*>(esCreateOld(&s,d,NULL,NULL,false));if(!nested)std::abort();CDescriptor*nd=addLogic(*nested,j%2?L"Other Logic":L"Fixture Logic");for(unsigned n=0;n<1+seed/8%3;++n){CEditorBaseObject*o=esCreateOld(nested,nd,NULL,NULL,false);if(!o)std::abort();std::wstring label(1,wchar_t(L'A'+k*6+j*3+n));o->SetName(label+L" nested");}if(seed/16%2){CDescriptor*sub=new CLayoutDescriptor(links[(k+1)%3],static_cast<ELAYOUT_TYPES>(1));nested->AddDescriptor(sub);CEditorScene*last=dynamic_cast<CEditorScene*>(esCreateOld(nested,sub,NULL,NULL,false));if(!last)std::abort();CDescriptor*ld=addLogic(*last,L"Fixture Logic");CEditorBaseObject*o=esCreateOld(last,ld,NULL,NULL,false);if(!o)std::abort();std::wstring label(1,wchar_t(L'a'+k*2+j));o->SetName(label+L" deep");}}}
  const std::wstring name=seed%3==0?L"Missing":seed%3==1?L"Fixture Logic":L"Other Logic";TArrayList<CEditorBaseObject*>result(1);if(count&&seed/3%2)result.add(objects[0]);
  autotest::beginInvocation(out,ours?esGetNew:esGetOld);(ours?esGetNew:esGetOld)(&s,name,&result);out.callCompleted=1;
  number(out,result.size());for(unsigned i=0;i<result.size();++i){unsigned at=0;while(at<count&&objects[at]!=result[i])++at;number(out,at);out.addText(result[i]->getName());}
 }else if(c.op==4){
  CRandomGroup parent(&fixture.resources);parent.setOriginalGuid(1234567);parent.m_iRandomType=seed%4;parent.SetNumberOfPicks(seed%5);parent.m_iMinimumChildren=seed%3;parent.m_iMaximumChildren=seed%3+2;
  TArrayList<CEditorBaseObject*>all(1);TArrayList<CRandomGroup*>rejected(1);std::vector<CRandomGroup*>owned;
  for(unsigned i=0;i<count;++i){CRandomGroup*g=new CRandomGroup(&fixture.resources);g->setParentGuid((seed+i)%3?1234567:7654321);g->SetRandomWeight((seed+i)%5);g->setOriginalGuid(100+i);all.add(g);owned.push_back(g);}
  if(seed/3%2)rejected.add(&parent);
  autotest::beginInvocation(out,ours?esRollNew:esRollOld);(ours?esRollNew:esRollOld)(&parent,all,rejected);out.callCompleted=1;
  number(out,rejected.size());number(out,rejected.m_nGrowBy);number(out,rejected.m_nCapacity);for(unsigned i=0;i<rejected.size();++i){number(out,rejected[i]==&parent);if(rejected[i]!=&parent)number(out,rejected[i]->getOriginalGuid());}
  for(unsigned i=0;i<owned.size();++i)delete owned[i];
 }else{
  CDescriptorLoadConfiguration configuration;configuration.m_createdObjects=NULL;configuration.m_timers=NULL;configuration.m_bFlag14=seed/3%2;configuration.m_iVersion=3;
  CDescriptorSaveConfiguration save;CDataGroup data(seed%9==1?L"WRONG":L"BASEOBJECT",NULL,2,2,NULL);
  if(seed%9!=2){for(unsigned i=0;i<count;++i)objects[i]->setOriginalGuid(10000+i);if(count)objects[0]->getDescriptor()->saveObject(objects[0],&data,&save);CDataGroup*properties=data.GetDataGroupByName(L"PROPERTIES",true);if(seed%9==3)properties->SetDataValue(L"DESCRIPTOR",std::wstring(L"Missing Descriptor"),false);else if(seed%9==4)properties->SetDataValue(L"DESCRIPTOR",std::wstring(),false);}
  if(count>1&&seed/4%2){CDataGroup*children=data.AddDataGroup(L"CHILDREN");for(unsigned i=1;i<count;++i){CDataGroup*child=children->AddDataGroup(L"BASEOBJECT");objects[i]->getDescriptor()->saveObject(objects[i],child,&save);}}
  if(configuration.m_bFlag14&&seed/17%2)for(unsigned i=0;i<count;++i)configuration.addRemap(10000+i,objects[i]->getGuid());
  TArrayList<CEditorBaseObject*>created(1);if(count&&seed/7%2)created.add(objects[0]);if(seed/5%2)configuration.m_createdObjects=&created;CTimerStatics timer;if(seed/11%2)configuration.m_timers=&timer;
  CDescriptorManager*saved=s.m_pDescriptorManager;if(seed%13==0)s.m_pDescriptorManager=NULL;
  detour::Set clock;clock.redirect(reinterpret_cast<char*>(0x555928),esMicroseconds_linked,&microseconds);if(clock.failed())std::abort();ticks=0;int result=0;
  autotest::beginInvocation(out,ours?esLoadNew:esLoadOld);result=(ours?esLoadNew:esLoadOld)(&s,seed%9==0?static_cast<CDataGroup*>(NULL):&data,seed%9==5?static_cast<CDescriptorLoadConfiguration*>(NULL):&configuration);out.callCompleted=1;clock.restore();s.m_pDescriptorManager=saved;
  number(out,result);number(out,created.size());for(unsigned i=0;i<created.size();++i){number(out,created[i]!=NULL);if(created[i])out.addText(created[i]->getName());}number(out,ticks);number(out,timer.m_times.size());number(out,timer.m_statistics.size());for(std::map<std::wstring,std::pair<unsigned,unsigned> >::iterator i=timer.m_statistics.begin();i!=timer.m_statistics.end();++i){out.addText(i->first);number(out,i->second.first);number(out,i->second.second);}
 }
 snapshot(out,s);
}
int worker(const tlhybrid_host*host){
 initEmptyGlobals();nativegame::Services native;services=&native;if(!native.ready())return 1;menugui::Audio audio(native.master);nativeeditor::Controls editor(native);
 const char*names[]={"editor_scene_save_native","editor_scene_create_native","editor_scene_delete_native","editor_scene_objects_native","editor_scene_roll_native","editor_scene_load_native"};const unsigned addresses[]={0x74e6f0,0x74c110,0x74c3b0,0x74bbf0,0x74b2c0,0x74f420};
 for(unsigned i=0;i<6;++i)if(smallmass::run(host,i,names[i],addresses[i],&side,64))return 1;return 0;
}
}
TL_TEST(complete_editor_scene_objects){return systems_fixture::isolated(&worker,host);}
