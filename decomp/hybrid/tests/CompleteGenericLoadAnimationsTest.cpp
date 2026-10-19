#include "AutoTest.h"
#include <Ogre.h>
#include <deque>
#define private public
#define protected public
#include "GenericModel.h"
#include "ResourceManager.h"
#include "MasterResourceManager.h"
#undef protected
#undef private
#include "AnimationSet.h"
#include "Keyframe.h"
#include "DataGroup.h"
#include "FileSystem.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include <OgreSkeletonManager.h>
#include <OgreSkeletonInstance.h>
#include <OgreSubMesh.h>
TL_ORIGINAL(void,gaOld,(CGenericModel*,Ogre::Entity*,std::wstring,std::wstring,bool),"_ZN13CGenericModel14loadAnimationsEPN4Ogre6EntityESbIwSt11char_traitsIwESaIwEES6_b")
extern "C" void gaNew(CGenericModel*,Ogre::Entity*,std::wstring,std::wstring,bool) __asm__("_ZN13CGenericModel14loadAnimationsEPN4Ogre6EntityESbIwSt11char_traitsIwESaIwEES6_b");
TL_ORIGINAL(void,gaCtor,(CGenericModel*,CResourceManager*,Ogre::SceneManager*,OGRE_UTILITIES::EPRIMITIVES),"_ZN13CGenericModelC1EP16CResourceManagerPN4Ogre12SceneManagerEN14OGRE_UTILITIES11EPRIMITIVESE")
TL_ORIGINAL(void,gaDtor,(CGenericModel*),"_ZN13CGenericModelD1Ev")
TL_ORIGINAL(void,gaResourceCtor,(CResourceManager*,Ogre::SceneManager*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,gaResourceDtor,(CResourceManager*),"_ZN16CResourceManagerD1Ev")
TL_FUNCTION(gaFiles,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(gaLoad,"_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
extern "C" char gaLog[] __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
namespace {
nativegame::Services*services;Ogre::MeshPtr meshes[2];Ogre::SkeletonPtr sources[3],bases[2];autotest::Capture*output;unsigned current;
void number(unsigned n){output->add(&n,4);}void wide(const std::wstring&s){number(s.size());if(s.size())output->add(s.data(),s.size()*sizeof(wchar_t));}void narrow(const std::string&s){number(s.size());if(s.size())output->add(s.data(),s.size());}
void log(Ogre::LogManager*p,const std::string&s,Ogre::LogMessageLevel level,bool mask){if(p!=Ogre::LogManager::getSingletonPtr())std::abort();number(99);narrow(s);number(level);number(mask);}
void files(CFileSystem*p,const std::wstring&path,CFileInfo&info,bool a,bool b,bool c){if(p!=g_pFileSystem)std::abort();number(1);wide(path);number(a);number(b);number(c);unsigned mode=current%9;info.m_bExists=mode!=0;if(path.find(L"list.dat")==std::wstring::npos){info.m_bExists=mode!=2;if(path.find(L"hero.skeleton")!=std::wstring::npos)info.m_sResourceName=sources[1]->getName();else if(path.find(L"run.skeleton")!=std::wstring::npos)info.m_sResourceName=sources[2]->getName();else info.m_sResourceName=sources[0]->getName();}}
void load(CDataGroup*p,const std::wstring&path,CTimerStatics*timers){number(2);wide(p->GetGroupName());wide(path);number(timers==NULL);if(p->GetGroupName()!=L"ANIMATION")std::abort();unsigned mode=current%9;if(mode==1)return;unsigned groups=mode>=6?2:1;for(unsigned i=0;i<groups;++i){CDataGroup*group=p->AddDataGroup(L"ANIMATION");const wchar_t*file=mode==5?L"hero.skeleton":mode==7&&i==0?L"run.skeleton":mode==8&&i==1?L"run.skeleton":L"walk.skeleton";group->SetDataValue(L"FILE",file,false);for(unsigned k=0;k<current/18%4;++k){CDataGroup*key=group->AddDataGroup(L"KEY");key->SetDataValue(L"TYPE",L"SOUND",false);key->SetDataValue(L"NAME",L"fixture-key",false);key->SetDataValue(L"FRAME",static_cast<int>(k+1));}}}
void initialized(uintptr_t address,bool wide){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(address),8);if(!p){if(wide)new(reinterpret_cast<void*>(address))std::wstring;else new(reinterpret_cast<void*>(address))std::string;}}
void side(void*raw,autotest::Capture&out,bool ours){unsigned seed=*static_cast<unsigned*>(raw);current=seed;output=&out;CResourceManager*resources=static_cast<CResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CResourceManager),0,0,0));gaResourceCtor(resources,services->scene);CGenericModel*model=static_cast<CGenericModel*>(Ogre::NedAllocImpl::allocBytes(sizeof(CGenericModel),0,0,0));gaCtor(model,NULL,services->scene,OGRE_UTILITIES::PRIMITIVE_SPHERE);model->setResourceManager(resources);Ogre::Entity*entity=services->scene->createEntity("generic-animation-entity",meshes[seed/216%2]->getName());model->sceneNodeAttachEntity(entity);model->m_pSkeleton=entity->getSkeleton();model->m_sModelPath=L"folder/HERO.MESH";
 CAnimationSet*set=new CAnimationSet;set->m_nAnimationCount=7;set->m_nUnknown=1+seed/216%2;set->m_lUnknown28.push_back("BIND");set->m_lUnknown40.push_back(L"old-bind.skeleton");if(seed/216%2){set->m_lUnknown28.push_back("Walk");set->m_lUnknown40.push_back(L"old-walk.skeleton");}set->m_lAnimationGroups.resize(seed/72%3);services->master->m_animationSets.push_back(set);model->m_animationSet=set;
 detour::Set hooks;TL_REDIRECT(hooks,gaFiles,&files);TL_REDIRECT(hooks,gaLoad,&load);hooks.redirect(gaLog,gaLog,&log);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}void(*fn)(CGenericModel*,Ogre::Entity*,std::wstring,std::wstring,bool)=ours?gaNew:gaOld;if(autotest::beginInvocation(out,fn)){fn(model,entity,L"list.dat",seed/54%2?L"media/\x041b\x0435\x0441/":L"",seed/9%2);out.callCompleted=1;}number(set->m_nUnknown);number(set->m_lUnknown28.size());for(unsigned i=0;i<set->m_lUnknown28.size();++i)narrow(set->m_lUnknown28[i]);number(set->m_lUnknown40.size());for(unsigned i=0;i<set->m_lUnknown40.size();++i)wide(set->m_lUnknown40[i]);number(set->m_lAnimationGroups.size());for(unsigned i=0;i<set->m_lAnimationGroups.size();++i){number(set->m_lAnimationGroups[i].size());for(unsigned k=0;k<set->m_lAnimationGroups[i].size();++k){number(set->m_lAnimationGroups[i][k]->getAnimationIndex());number(set->m_lAnimationGroups[i][k]->getEventCode());}}
 number(model->m_pSkeleton->getNumAnimations());for(unsigned i=0;i<model->m_pSkeleton->getNumAnimations();++i){Ogre::Animation*a=model->m_pSkeleton->getAnimation(i);narrow(a->getName());float length=a->getLength();out.add(&length,4);}Ogre::AnimationStateIterator states=entity->getAllAnimationStates()->getAnimationStateIterator();while(states.hasMoreElements()){Ogre::AnimationState*state=states.getNext();narrow(state->getAnimationName());float length=state->getLength();out.add(&length,4);}number(777);hooks.restore();gaDtor(model);Ogre::NedAllocImpl::deallocBytes(model);std::vector<CAnimationSet*>&sets=services->master->m_animationSets;sets.erase(std::remove(sets.begin(),sets.end(),set),sets.end());delete set;gaResourceDtor(resources);Ogre::NedAllocImpl::deallocBytes(resources);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
int worker(const tlhybrid_host*host){nativegame::Services native;services=&native;if(!native.ready())return 1;uintptr_t strings[]={0x1482e00,0x14884c0,0x14b37c0,0x1528e40,0x14e6900};for(unsigned i=0;i<5;++i){initialized(strings[i],false);initialized(strings[i]+8,true);}CFileSystem*previous=g_pFileSystem;void*memory=Ogre::NedAllocImpl::allocBytes(sizeof(CFileSystem),0,0,0);g_pFileSystem=static_cast<CFileSystem*>(memory);CFileSystem*fs=new(memory)CFileSystem(false);
 Ogre::MaterialPtr material=Ogre::MaterialManager::getSingleton().create("generic-animation-material","General");material->removeAllTechniques();for(unsigned i=0;i<2;++i){bases[i]=Ogre::SkeletonManager::getSingleton().create("generic-animation-base"+Ogre::StringConverter::toString(i),"General",true);bases[i]->createBone(0);bases[i]->setBindingPose();bases[i]->createAnimation("BIND",2.f);if(i)bases[i]->createAnimation("Walk",3.f);bases[i]->load();meshes[i]=Ogre::MeshManager::getSingleton().createManual("generic-animation-mesh"+Ogre::StringConverter::toString(i),"General");meshes[i]->_setBounds(Ogre::AxisAlignedBox(-1,-1,-1,1,1,1),false);meshes[i]->createSubMesh()->setMaterialName(material->getName());meshes[i]->setSkeletonName(bases[i]->getName());}
 for(unsigned i=0;i<3;++i){sources[i]=Ogre::SkeletonManager::getSingleton().create("generic-animation-source"+Ogre::StringConverter::toString(i),"General",true);sources[i]->createBone(0);sources[i]->setBindingPose();sources[i]->createAnimation(i==2?"Run":"Walk",4.f+i);if(i==1)sources[i]->createAnimation("bind",1.f);sources[i]->load();}
 autotest::Coverage coverage("generic_load_animations",reinterpret_cast<uintptr_t>(gaOld));for(unsigned seed=0;seed<432;++seed){autotest::Outcome a,b;autotest::runChild(original,&seed,a);autotest::runChild(candidate,&seed,b);if(coverage.observe(host,a,b)){host->log("    animations seed%u issue%u/%u exit%d/%d bytes%lu/%lu\n",seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);coverage.report(host);return 1;}}coverage.report(host);for(unsigned i=0;i<2;++i){meshes[i].setNull();bases[i].setNull();}for(unsigned i=0;i<3;++i)sources[i].setNull();fs->~CFileSystem();Ogre::NedAllocImpl::deallocBytes(fs);g_pFileSystem=previous;return coverage.completed!=432||coverage.missing||coverage.different;
}
}
TL_TEST(complete_generic_load_animations){return systems_fixture::isolated(&worker,host);}
