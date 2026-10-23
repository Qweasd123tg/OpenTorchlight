#include "AutoTest.h"
#include <Ogre.h>
#define private public
#define protected public
#include "EditorScene.h"
#include "Descriptor.h"
#include "DescriptorManager.h"
#include "DescriptorLoadConfiguration.h"
#include "RandomGroupDescriptor.h"
#undef protected
#undef private
#include "Utilities.h"
#include "tests/CharacterEmptyGlobals.h"
#include "tests/NativeEditorControls.h"
#include "tests/SystemsFixtureWorker.h"

TL_ORIGINAL(void,randomGroupsOld,(CDescriptor*,TArrayList<CEditorBaseObject*>&,bool,CDescriptorLoadConfiguration&),"_Z16rollRandomGroupsP11CDescriptorR10TArrayListIP17CEditorBaseObjectEbR28CDescriptorLoadConfiguration")
extern "C" void randomGroupsNew(CDescriptor*,TArrayList<CEditorBaseObject*>&,bool,CDescriptorLoadConfiguration&) __asm__("_Z16rollRandomGroupsP11CDescriptorR10TArrayListIP17CEditorBaseObjectEbR28CDescriptorLoadConfiguration");
TL_ORIGINAL(void,groupsSceneCtor,(CEditorScene*,const wchar_t*),"_ZN12CEditorSceneC1EPKw")
TL_ORIGINAL(void,groupsSceneDtor,(CEditorScene*),"_ZN12CEditorSceneD1Ev")
TL_ORIGINAL(void,groupsSceneInit,(CEditorScene*,CResourceManager*,unsigned),"_ZN12CEditorScene9InitSceneEP16CResourceManagerj")
TL_ORIGINAL(CEditorBaseObject*,groupsCreateOld,(CEditorScene*,CDescriptor*,CEditorBaseObject*,CEditorBaseObject*,bool),"_ZN12CEditorScene24CreateObjectByDescriptorEP11CDescriptorP17CEditorBaseObjectS3_b")
TL_ORIGINAL(bool,groupsCanOld,(CRandomGroup*),"_ZN12CRandomGroup20getGroupCanBeCreatedEv")
TL_ORIGINAL(void,groupsRollOld,(CRandomGroup*,TArrayList<CEditorBaseObject*>&,TArrayList<CRandomGroup*>&),"_Z9rollGroupP12CRandomGroupR10TArrayListIP17CEditorBaseObjectERS1_IS0_E")
TL_ORIGINAL(bool,groupsChildOld,(CEditorBaseObject*,long long),"_ZN17CEditorBaseObject15isChildOfObjectEx")
TL_FUNCTION(groupsCanEntry,"_ZN12CRandomGroup20getGroupCanBeCreatedEv")
TL_FUNCTION(groupsRollEntry,"_Z9rollGroupP12CRandomGroupR10TArrayListIP17CEditorBaseObjectERS1_IS0_E")
TL_FUNCTION(groupsChildEntry,"_ZN17CEditorBaseObject15isChildOfObjectEx")
namespace {
struct Case{unsigned seed;bool observed,negative;};
nativegame::Services* services;nativeeditor::Controls* controls;
const Case* input;autotest::Capture* output;CDescriptor* owner;
unsigned canCalls,rollCalls,childCalls;detour::Set canHook,rollHook,childHook;
void number(long long value){output->add(&value,sizeof value);}
void identity(CEditorBaseObject* p){number(p?p->getOriginalGuid():-1);}
template<class T>void list(TArrayList<T*>& values){number(values.size());number(values.m_nCapacity);number(values.m_nGrowBy);for(unsigned i=0;i<values.size();++i)identity(values[i]);}
void checkHooks(){if(canHook.failed()||rollHook.failed()||childHook.failed())output->issue=autotest::Capture::InvalidReport;}
bool can(CRandomGroup* group){
 number(1);identity(group);++canCalls;canHook.restore();bool result=groupsCanOld(group);TL_REDIRECT(canHook,groupsCanEntry,&can);checkHooks();number(result);
 unsigned mode=input->seed/60%4;if(mode==1&&group->getOriginalGuid()%3==0)return false;if(mode==2)return false;return result;
}
void roll(CRandomGroup* group,TArrayList<CEditorBaseObject*>& objects,TArrayList<CRandomGroup*>& rejected){
 number(2);identity(group);list(objects);list(rejected);++rollCalls;
 rollHook.restore();groupsRollOld(group,objects,rejected);TL_REDIRECT(rollHook,groupsRollEntry,&roll);checkHooks();list(objects);list(rejected);
 // Reorder real live descriptor objects while the caller is iterating them.
 if(input->seed/60%4==3&&rollCalls==1&&owner->m_Objects.size()>1)std::swap(owner->m_Objects[0],owner->m_Objects[owner->m_Objects.size()-1]);
}
bool child(CEditorBaseObject* object,long long guid){
 number(3);identity(object);number(guid);++childCalls;childHook.restore();bool result=groupsChildOld(object,guid);TL_REDIRECT(childHook,groupsChildEntry,&child);checkHooks();number(result);return result;
}
struct Scene{
 CResourceManager resources;CEditorScene* scene;
 Scene():resources(services->scene),scene(static_cast<CEditorScene*>(Ogre::NedAllocImpl::allocBytes(sizeof(CEditorScene),0,0,0))){groupsSceneCtor(scene,L"Group Fixture");groupsSceneInit(scene,&resources,0);}
 ~Scene(){groupsSceneDtor(scene);Ogre::NedAllocImpl::deallocBytes(scene);}
};
void side(void*raw,autotest::Capture& out,bool ours){
 input=static_cast<Case*>(raw);output=&out;unsigned seed=input->seed;canCalls=rollCalls=childCalls=0;
 UTILITIES::setSeed(seed*73+19);UTILITIES::setSeedVolatile(seed*37+5);controls->editor->m_iFlags=2;
 int before=g_iTotalCountOfObjects;
 {
 Scene fixture;CEditorScene& scene=*fixture.scene;fixture.resources.m_bFlag3=seed/120%2;
 CDescriptor* groups=new CRandomGroupDescriptor;CDescriptor* children=new CRandomGroupDescriptor;scene.AddDescriptor(groups);scene.AddDescriptor(children);owner=groups;
 const unsigned counts[]={0,1,2,5,9,23};unsigned roots=counts[seed%6],extras=counts[(seed/12)%6];
 std::vector<CRandomGroup*> objects;
 for(unsigned i=0;i<roots+extras;++i){
  CRandomGroup* p=static_cast<CRandomGroup*>(groupsCreateOld(&scene,i<roots?groups:children,NULL,NULL,false));if(!p)std::abort();
  p->setGuid(1000+i);p->setOriginalGuid(1000+i);p->SetName(i&1?L"Группа Ω":L"");
  unsigned graph=seed/24%4;long long parent=-1;
  if(i&&graph==1)parent=1000+i-1;
  if(i&&graph==2)parent=1000+(i-1)/2;
  if(i>=roots&&roots&&graph==3)parent=1000+(i-roots)%roots;
  p->setParentGuid(parent);p->m_iRandomType=(seed/48+i)%3;p->m_iRandomWeight=(seed+i)%5?((seed+i)%101):0;p->m_iNumberOfPicks=int(seed/8%5)-1;
  if((seed/30+i)%7==0){if(fixture.resources.getGameClient()!=NULL)std::abort();p->m_sPlayerClassName=L"Missing fixture class";}
  objects.push_back(p);
 }
 scene.m_Objects.clear();for(unsigned i=0;i<objects.size();++i)scene.m_Objects[objects[i]->getGuid()]=objects[i];
 TArrayList<CEditorBaseObject*> result(seed%4+1);
 for(unsigned i=0;i<extras;++i)result.add(objects[roots+i]);
 if(!objects.empty()&&seed/96%2){result.add(objects[0]);result.add(objects[0]);}
 CDescriptorLoadConfiguration cfg;cfg.m_iVersion=37;cfg.m_iParentGuid=123456;cfg.m_Remaps[77]=99;
 std::vector<CEditorBaseObject*> originalOrder;for(unsigned i=0;i<groups->m_Objects.size();++i)originalOrder.push_back(groups->m_Objects[i]);
 if(input->observed){TL_REDIRECT(canHook,groupsCanEntry,&can);TL_REDIRECT(rollHook,groupsRollEntry,&roll);TL_REDIRECT(childHook,groupsChildEntry,&child);checkHooks();}
 typedef void(*Fn)(CDescriptor*,TArrayList<CEditorBaseObject*>&,bool,CDescriptorLoadConfiguration&);Fn fn=ours?randomGroupsNew:randomGroupsOld;
 if(autotest::beginInvocation(out,fn)){fn(seed%29==0?static_cast<CDescriptor*>(NULL):groups,result,bool(seed/6%2),cfg);out.callCompleted=1;}
 canHook.restore();rollHook.restore();childHook.restore();if(ours&&input->negative)result.setGrowBy(result.m_nGrowBy+1);
 list(result);number(canCalls);number(rollCalls);number(childCalls);number(cfg.m_iVersion);number(cfg.m_iParentGuid);number(cfg.m_Remaps.size());number(cfg.m_Remaps[77]);
 list(groups->m_Objects);list(children->m_Objects);number(scene.m_Objects.size());
 for(unsigned i=0;i<objects.size();++i){CRandomGroup* p=objects[i];identity(p);number(p->getGuid());number(p->getParentGuid());number(p->m_iRandomType);number(p->m_iRandomWeight);number(p->m_iNumberOfPicks);number(p->m_children.size());}
 for(unsigned i=0;i<originalOrder.size();++i)groups->m_Objects[i]=originalOrder[i];
 }
 number(g_iTotalCountOfObjects-before);
}
void oldSide(void*p,autotest::Capture&o){side(p,o,false);}void newSide(void*p,autotest::Capture&o){side(p,o,true);}
int run(const tlhybrid_host* host,bool observed){
 initEmptyGlobals();nativegame::Services native;if(!native.ready())return 1;services=&native;nativeeditor::Controls editor(native);controls=&editor;
 const char* label=observed?"random_groups_observed":"random_groups_native";autotest::Coverage coverage(label,0x74c900);
 for(unsigned seed=0;seed<480;++seed){Case c={seed,observed,false};autotest::Outcome a,b;autotest::runChild(oldSide,&c,a,8000,48000);autotest::runChild(newSide,&c,b,8000,48000);if(coverage.observe(host,a,b)){host->log("    random-groups seed%u status%d/%d issue%u/%u bytes%lu/%lu\n",seed,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}
 coverage.report(host);Case c={147,observed,true};autotest::Outcome a,b;autotest::runChild(oldSide,&c,a,8000,48000);autotest::runChild(newSide,&c,b,8000,48000);autotest::Coverage negative(label,0x74c900);int detected=negative.observe(host,a,b);host->log("    random-groups negative observed%u detected%u completed%u incomplete%u\n",unsigned(observed),unsigned(detected==1),negative.completed,negative.missing);return detected!=1||negative.completed!=1||negative.missing;
}
int nativeWorker(const tlhybrid_host*h){return run(h,false);}int observedWorker(const tlhybrid_host*h){return run(h,true);}
}
TL_TEST(random_groups_native){return systems_fixture::isolated(nativeWorker,host,300);}
TL_TEST(random_groups_observed){return systems_fixture::isolated(observedWorker,host,300);}
