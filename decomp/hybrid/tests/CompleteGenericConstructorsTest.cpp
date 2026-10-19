#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "GenericModel.h"
#include "ResourceManager.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,gcOldPrimitive,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_ORIGINAL(void,gcOldString,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,std::wstring,std::wstring,bool),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEES8_b")
TL_ORIGINAL(void,gcDtor,(CGenericModel*),"_ZN13CGenericModelD1Ev")
TL_ORIGINAL(void,gcResourceCtor,(CResourceManager*,Ogre::SceneManager*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,gcResourceDtor,(CResourceManager*),"_ZN16CResourceManagerD1Ev")
TL_FUNCTION(gcPrefab,"_ZN13CGenericModel14loadPrefabTypeEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_FUNCTION(gcLoad,"_ZN13CGenericModel9loadModelESbIwSt11char_traitsIwESaIwEES3_bbb")
extern "C" void gcNewPrimitive(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES) __asm__("_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE");
extern "C" void gcNewString(CGenericModel*,CResourceManager*,Ogre::SceneManager*,std::wstring,std::wstring,bool) __asm__("_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEES8_b");
namespace {
nativegame::Services*services;autotest::Capture*output;CGenericModel*expected;
struct Case{unsigned op,seed;};void number(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){number(s.size());if(s.size())output->add(s.data(),s.size()*sizeof(wchar_t));}void narrow(const std::string&s){number(s.size());if(s.size())output->add(s.data(),s.size());}
void prefab(CGenericModel*p,OGRE_UTILITIES::EPRIMITIVES primitive){if(p!=expected)std::abort();number(1);number(primitive);number(p->m_bEnabled);number(p->m_queryMask);number(p->m_modelSceneManager==services->scene);wide(p->m_sModelPath);wide(p->m_modelGroup);}
void load(CGenericModel*p,std::wstring path,std::wstring group,bool a,bool b,bool c){if(p!=expected)std::abort();number(2);wide(path);wide(group);number(a);number(b);number(c);number(p->m_bEnabled);number(p->m_queryMask);number(p->m_modelSceneManager==services->scene);wide(p->m_sModelPath);wide(p->m_modelGroup);}
void side(void*raw,autotest::Capture&out,bool ours){Case c=*static_cast<Case*>(raw);output=&out;unsigned seed=c.seed;CResourceManager*resources=static_cast<CResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CResourceManager),0,0,0));gcResourceCtor(resources,services->scene);CResourceManager*argument=seed%2?resources:NULL;Ogre::SceneManager*scene=seed/2%2?services->scene:NULL;void*memory=Ogre::NedAllocImpl::allocBytes(sizeof(CGenericModel),0,0,0);std::memset(memory,seed/4%3==0?0:seed/4%3==1?0x5a:0xc3,sizeof(CGenericModel));CGenericModel*model=static_cast<CGenericModel*>(memory);expected=model;
 const wchar_t*paths[]={L"",L"models/actor.mesh",L"\x041b\x0435\x0441.mesh",L"space path/box.mesh",L"/",L"a\\b"};std::wstring path=paths[seed/12%6],group=paths[seed/72%6];detour::Set hooks;TL_REDIRECT(hooks,gcPrefab,&prefab);TL_REDIRECT(hooks,gcLoad,&load);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op==0){typedef void(*Fn)(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES);Fn fn=ours?gcNewPrimitive:gcOldPrimitive;if(autotest::beginInvocation(out,fn)){fn(model,argument,scene,static_cast<OGRE_UTILITIES::EPRIMITIVES>(seed/12%6));out.callCompleted=1;}}
 else{typedef void(*Fn)(CGenericModel*,CResourceManager*,Ogre::SceneManager*,std::wstring,std::wstring,bool);Fn fn=ours?gcNewString:gcOldString;if(autotest::beginInvocation(out,fn)){fn(model,argument,scene,path,group,seed/6%2);out.callCompleted=1;}}
 wide(model->m_sModelPath);wide(model->m_modelGroup);narrow(model->m_name);narrow(model->m_string128);number(model->getResourceManager()==argument);number(model->getSceneNode()!=NULL);number(model->m_pSceneManager==services->scene);number(model->m_modelSceneManager==services->scene);number(model->m_bEnabled);number(model->m_bVisible);number(model->m_pSkeleton==NULL);out.add(model->m_gap138,sizeof(model->m_gap138));number(model->m_animationStates.size());number(model->m_animationStates.m_nGrowBy);number(model->m_activeAnimations.size());number(model->m_AnimationEvents.size());number(model->m_valueIndexes.size());number(model->m_animationSet==NULL);number(model->m_animationPaused);number(model->m_flag1e9);out.add(&model->m_boundsMinimum,sizeof(Ogre::Vector3));out.add(&model->m_boundsMaximum,sizeof(Ogre::Vector3));number(model->m_queryMask);number(model->m_renderableStates.size());number(model->m_randomWeight);number(model->m_uniqueMaterials);out.add(&model->m_opacity,4);number(model->m_entity230==NULL);number(model->m_flag238);number(model->m_renderToLightMap);out.add(&model->m_renderFlag23A,1);number(model->m_gap23B);number(model->m_animationLoop);out.add(&model->m_animationSpeed,4);number(model->m_animationPlaying);out.add(model->m_ModelData248,sizeof(model->m_ModelData248));out.add(&model->m_animationStep,4);
 hooks.restore();gcDtor(model);Ogre::NedAllocImpl::deallocBytes(memory);gcResourceDtor(resources);Ogre::NedAllocImpl::deallocBytes(resources);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;for(unsigned i=0;i<2;++i){void*p=NULL;uintptr_t address=i?0x1482e08:0x1482e00;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p){if(i)new(reinterpret_cast<void*>(address))std::wstring;else new(reinterpret_cast<void*>(address))std::string;}}
 const char*names[]={"generic_primitive_ctor","generic_string_ctor"};for(unsigned op=0;op<2;++op){autotest::Coverage coverage(names[op],reinterpret_cast<uintptr_t>(op?reinterpret_cast<void*>(gcOldString):reinterpret_cast<void*>(gcOldPrimitive)));for(unsigned seed=0;seed<432;++seed){Case c={op,seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);if(coverage.observe(host,a,b)){host->log("    generic ctor op%u seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",op,seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);}return 0;}
}
TL_TEST(complete_generic_constructors){return systems_fixture::isolated(&worker,host);}
