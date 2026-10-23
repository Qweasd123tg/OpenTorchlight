#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/CharacterEmptyGlobals.h"
#include "tests/CharacterLibraryBoundary.h"
#define private public
#include "MasterResourceManager.h"
#include "TRepository.h"
#include "FileSystem.h"
#undef private
#include "Settings.h"
#include "FileSystem.h"
#include "FileUtilities.h"
#include "LinuxUtils.h"
#include "Hierarchy.h"
#include "ResourceSettings.h"
#include "UnitResourceList.h"
#include "DungeonManager.h"
#include "ParticlePreloader.h"
#include "AnimationSet.h"
#include "BatchModelRef.h"
#include "CollisionModelRef.h"
#include "Achievement.h"
#include "Achievements.h"
#include "SteamStats.h"
#include "GameVariables.h"
#include "StringUtilities.h"
#include "DataGroup.h"
#include <OgreRoot.h>
#include <OgrePlugin.h>
#include <OgreResourceGroupManager.h>
#include <OgreMemoryAllocatorConfig.h>
#include <fstream>
#include <iterator>
#include <dirent.h>
#include <sys/stat.h>
#include <ucontext.h>
#include <execinfo.h>
TL_ORIGINAL(void,mrCtorOld,(CMasterResourceManager*,CSettings*),"_ZN22CMasterResourceManagerC1EP9CSettings")
extern "C" void mrCtorNew(CMasterResourceManager*,CSettings*) __asm__("_ZN22CMasterResourceManagerC1EP9CSettings");
TL_ORIGINAL(void,mrDtorOld,(CMasterResourceManager*),"_ZN22CMasterResourceManagerD1Ev")
extern "C" void mrDtorNew(CMasterResourceManager*) __asm__("_ZN22CMasterResourceManagerD1Ev");
TL_ORIGINAL(void,mrDeleteOld,(CMasterResourceManager*),"_ZN22CMasterResourceManagerD0Ev")
extern "C" void mrDeleteNew(CMasterResourceManager*) __asm__("_ZN22CMasterResourceManagerD0Ev");
TL_ORIGINAL(void,mrSettingsCtor,(CSettings*,std::wstring,std::wstring,std::wstring,std::wstring),"_ZN9CSettingsC1ESbIwSt11char_traitsIwESaIwEES3_S3_S3_")
TL_ORIGINAL(void,mrSettingsDtor,(CSettings*),"_ZN9CSettingsD1Ev")
TL_ORIGINAL(void,mrFsCtor,(CFileSystem*,bool),"_ZN11CFileSystemC1Eb")
TL_ORIGINAL(void,mrFsDtor,(CFileSystem*),"_ZN11CFileSystemD1Ev")
extern "C" void mrRootCtor(void*,const std::string&,const std::string&,const std::string&) __asm__("_ZN4Ogre4RootC1ERKSsS2_S2_");
extern "C" void mrRootDtor(void*) __asm__("_ZN4Ogre4RootD1Ev");
extern "C" char mrFreeLinked[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
TL_FUNCTION(mrFsCtorEntry,"_ZN11CFileSystemC1Eb")
TL_FUNCTION(mrModCount,"_ZN11CFileSystem15getNumberOfModsEv")
namespace {
struct Case{unsigned seed,op,negative;};const Case*input;autotest::Capture*output;const tlhybrid_host*diagHost;volatile sig_atomic_t stage,candidate;std::string directory,profile;void*root;CMasterResourceManager*owner;detour::Set*freeHooks;unsigned masterFrees,countCalls;void*objects[64];unsigned objectFreed[64];unsigned objectCount;
void fault(int s,siginfo_t*,void*raw){ucontext_t*m=static_cast<ucontext_t*>(raw);diagHost->log("    master signal%d candidate%d stage%d rip%p\n",s,int(candidate),int(stage),reinterpret_cast<void*>(m->uc_mcontext.gregs[REG_RIP]));void*f[32];int n=backtrace(f,32);for(int i=0;i<n;++i)diagHost->log("    master frame%d %p\n",i,f[i]);_exit(128+s);}
void diagnostics(bool ours){stage=0;candidate=ours;struct sigaction a;std::memset(&a,0,sizeof a);a.sa_sigaction=&fault;a.sa_flags=SA_SIGINFO;sigemptyset(&a.sa_mask);sigaction(SIGABRT,&a,NULL);sigaction(SIGSEGV,&a,NULL);sigaction(SIGBUS,&a,NULL);}
void word(unsigned n){output->add(&n,4);}
const unsigned offsets[]={0x188,0x180,0x178,0x60,0xf8,0x80,0x88,0x68,0xe8,0x100,0x78,0x48,0x70,0x58,0xa8,0x20,0x28,0x38,0x30,0x40,0x10,0x18,0xb8};
void*pointerAt(void*p,unsigned offset){void*v=NULL;std::memcpy(&v,static_cast<char*>(p)+offset,sizeof v);return v;}
void rawState(CMasterResourceManager*p){for(unsigned i=0;i<sizeof offsets/sizeof offsets[0];++i)word(pointerAt(p,offsets[i])!=NULL);word(m_pMasterResourceManager==p);word(m_pMasterResourceManager==NULL);}
void freeObserved(void*p){if(p==owner){word(901);word(++masterFrees);rawState(owner);}else for(unsigned i=0;i<objectCount;++i)if(p==objects[i]){word(900);word(i);word(++objectFreed[i]);rawState(owner);break;}freeHooks->restore();Ogre::NedAllocImpl::deallocBytes(p);freeHooks->redirect(reinterpret_cast<char*>(0x555268),mrFreeLinked,&freeObserved);if(freeHooks->failed())std::abort();}
detour::Set*fsCtorHooks;CFileSystem*fixtureFs;
void fsCtorObserved(CFileSystem*p,bool force){word(700);word(force);word(m_pMasterResourceManager==owner);word(p!=fixtureFs);word(owner->m_fileSystem==NULL);word(owner->m_flagC1);fsCtorHooks->restore();mrFsCtor(p,force);TL_REDIRECT(*fsCtorHooks,mrFsCtorEntry,&fsCtorObserved);if(fsCtorHooks->failed())std::abort();word(p->m_bInitialized);word(p->m_pSettings==NULL);word(p->m_ResourceGroups.m_nGrowBy);}
unsigned mods(CFileSystem*p){word(800);word(++countCalls);word(p==m_pMasterResourceManager->m_fileSystem);const unsigned counts[]={0,1,4,5,9,10,11};if(input->seed&8)return countCalls==1?1:countCalls==2?0:11;return counts[input->seed%7];}
void utf16(const std::string&path,const std::wstring&text){FILE*f=std::fopen(path.c_str(),"wb");if(!f)std::abort();unsigned short bom=0xfeff;std::fwrite(&bom,2,1,f);for(unsigned i=0;i<text.size();++i){unsigned short x=text[i];std::fwrite(&x,2,1,f);}std::fclose(f);}
void clearTree(const std::string&path){DIR*d=opendir(path.c_str());if(!d)return;for(dirent*e=readdir(d);e;e=readdir(d)){if(!std::strcmp(e->d_name,".")||!std::strcmp(e->d_name,".."))continue;std::string p=path+"/"+e->d_name;struct stat st;if(lstat(p.c_str(),&st))std::abort();if(S_ISDIR(st.st_mode)){clearTree(p);if(rmdir(p.c_str()))std::abort();}else if(unlink(p.c_str()))std::abort();}closedir(d);}
void files(unsigned seed){clearTree(directory+"/work");clearTree(profile);mkdir((directory+"/work/media").c_str(),0700);mkdir((directory+"/work/GRAPHS").c_str(),0700);mkdir((directory+"/work/AFFIXES").c_str(),0700);mkdir((directory+"/work/translations").c_str(),0700);if(seed&1){utf16(profile+"resourceconfig.dat",L"Graphs path :GRAPHS/\nAffix Folder :AFFIXES/\nTranslate File :translations/translation.dat\nMaster Resource File :media/resources.dat\n");utf16(directory+"/work/media/resources.dat",L"[ROOT]\n[/ROOT]\n");utf16(directory+"/work/media/globals.dat",L"[GLOBALS]\n<INTEGER>RETIREMENT_AGE:33\n[/GLOBALS]\n");utf16(directory+"/work/media/unittypes.hie",L"[UNITTYPES]\n[UNITTYPE]\n<STRING>NAME:MONSTER\n[/UNITTYPE]\n[/UNITTYPES]\n");utf16(directory+"/work/GRAPHS/EXPERIENCE.DAT",L"[GRAPH]\n<STRING>NAME:EXPERIENCEGATE\n[/GRAPH]\n");utf16(directory+"/work/GRAPHS/FAME.DAT",L"[GRAPH]\n<STRING>NAME:FAMEGATE\n[/GRAPH]\n");}}
void bytes(const std::string&path){std::ifstream f(path.c_str(),std::ios::binary);word(f.is_open());std::string s((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());word(s.size());output->add(s.data(),s.size());}
void dump(CMasterResourceManager*p,CSettings*settings,CFileSystem*fs){rawState(p);word(p->m_pSettings==settings);word(CFileSystem::getSingleton()==fs);word(p->m_loadingResources);word(p->m_flagC1);word(p->m_pDefaultSceneManager==NULL);word(p->m_pSoundManager==NULL);word(p->m_console==NULL);word(p->m_pParticleSystemManager!=NULL);const unsigned untouched[]={0xb0,0xd0,0xd8,0xe0};for(unsigned i=0;i<4;++i)output->add(static_cast<char*>(static_cast<void*>(p))+untouched[i],8);output->add(reinterpret_cast<char*>(p)+0xc2,6);word(p->m_collisionModels.size());word(p->m_batchModels.size());word(p->m_animationSets.size());word(p->m_resourceLocations.size());word(p->m_pHierarchy->m_typeIDs.size());for(std::map<std::wstring,unsigned>::iterator i=p->m_pHierarchy->m_typeIDs.begin();i!=p->m_pHierarchy->m_typeIDs.end();++i){output->addText(i->first);word(i->second);}word(p->m_unitResourceList->m_pHierarchy==p->m_pHierarchy);word(p->m_unitResourceList->m_pResourceSettings==p->m_resourceSettings);CDataGroup*g=p->m_unitResourceList->m_pMasterDataGroup;word(g!=NULL);if(g){output->addText(g->GetGroupName());word(g->m_pRepository!=NULL);word(g->m_DataGroups.size());}word(p->m_experienceGraph!=NULL);word(p->m_fameGraph!=NULL);output->addText(p->m_resourceSettings->GetString(KRESOURCESETTING_S_GRAPH_MANAGER));output->addText(p->m_resourceSettings->GetString(KRESOURCESETTING_S_TRANSLATE_FILE));for(unsigned i=26;i<=28;++i){CAchievement*a=p->m_achievements->getAchievement(static_cast<EACHIEVEMENTS>(i));word(a!=NULL);if(a){word(a->m_bAchieved);output->addText(a->m_strName);}}const Ogre::Root::PluginInstanceList&plugins=Ogre::Root::getSingleton().getInstalledPlugins();word(plugins.size());for(Ogre::Root::PluginInstanceList::const_iterator i=plugins.begin();i!=plugins.end();++i)output->addText((*i)->getName());}
void populate(CMasterResourceManager*p,unsigned seed){for(unsigned i=0;i<seed%5;++i){CollisionModelRef*c=i%3?new CollisionModelRef:NULL;BatchModelRef*b=i%2?new BatchModelRef:NULL;CAnimationSet*a=i%3==1?NULL:new CAnimationSet;p->m_collisionModels.push_back(c);p->m_batchModels.push_back(b);p->m_animationSets.push_back(a);if(c)c->m_sUnknown20=L"owned collision Ж";if(b)b->m_sBatchModelName=L"owned batch Ω";if(a)a->m_wsName=L"owned animation";}if(seed&2)p->m_pParticlePreloader=new CParticlePreloader(p->m_resourceSettings);for(unsigned i=0;i<seed%4;++i)p->m_resourceLocations.push_back(i&1?"Resource Ω":"location");}
void side(void*raw,autotest::Capture&out,bool ours){const Case&c=*static_cast<Case*>(raw);input=&c;output=&out;diagnostics(ours);masterFrees=countCalls=objectCount=0;std::memset(objectFreed,0,sizeof objectFreed);files(c.seed);stage=1;char cwd[4096];if(!getcwd(cwd,sizeof cwd)||chdir((directory+"/work").c_str()))std::abort();CSettings*settings=static_cast<CSettings*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSettings),0,0,0));mrSettingsCtor(settings,L"",L"",L"",L"");if(c.seed%3==1)settings->m_pCmdLineParser->m_params[L"COMPRESS"].push_back(L"archive");else if(c.seed%3==2)settings->m_pCmdLineParser->m_params[L"COMPRESS"].push_back(L"");stage=2;CFileSystem*previousFs=g_pFileSystem;CFileSystem*fs=static_cast<CFileSystem*>(Ogre::NedAllocImpl::allocBytes(sizeof(CFileSystem),0,0,0));g_pFileSystem=fs;mrFsCtor(fs,false);fixtureFs=fs;CMasterResourceManager*previousMaster=m_pMasterResourceManager;owner=static_cast<CMasterResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CMasterResourceManager),0,0,0));std::memset(owner,0x40+c.seed%50,sizeof(CMasterResourceManager));stage=3;detour::Set fsTrace;fsCtorHooks=&fsTrace;if(c.op==3)TL_REDIRECT(fsTrace,mrFsCtorEntry,&fsCtorObserved);detour::Set collaborators;if(c.op==3)TL_REDIRECT(collaborators,mrModCount,&mods);if(collaborators.failed())std::abort();
 if(c.op==0||c.op==3){typedef void(*Fn)(CMasterResourceManager*,CSettings*);Fn fn=ours?mrCtorNew:mrCtorOld;if(autotest::beginInvocation(out,fn)){fn(owner,settings);out.callCompleted=1;}}
 else mrCtorOld(owner,settings);stage=4;collaborators.restore();fsTrace.restore();word(countCalls);if(ours&&c.negative&&(c.op==0||c.op==3))owner->m_flagC1=!owner->m_flagC1;dump(owner,settings,fs);if(c.seed==1&&owner->m_resourceSettings->GetString(KRESOURCESETTING_S_GRAPH_MANAGER)!=L"GRAPHS/")out.issue=autotest::Capture::InvalidReport;CDungeonManager*dungeon=owner->m_dungeons;Ogre::Root::PluginInstanceList plugins=Ogre::Root::getSingleton().getInstalledPlugins();CRunicCore*detached=NULL;
 if(c.op==1||c.op==2){populate(owner,c.seed);unsigned index=c.seed%(sizeof offsets/sizeof offsets[0]);if(index!=19){unsigned offset=offsets[index];detached=static_cast<CRunicCore*>(pointerAt(owner,offset));void*zero=NULL;std::memcpy(reinterpret_cast<char*>(owner)+offset,&zero,sizeof zero);}for(unsigned i=0;i<sizeof offsets/sizeof offsets[0];++i){void*p=pointerAt(owner,offsets[i]);if(p)objects[objectCount++]=p;}for(unsigned i=0;i<owner->m_collisionModels.size();++i)if(owner->m_collisionModels[i])objects[objectCount++]=owner->m_collisionModels[i];for(unsigned i=0;i<owner->m_batchModels.size();++i)if(owner->m_batchModels[i])objects[objectCount++]=owner->m_batchModels[i];for(unsigned i=0;i<owner->m_animationSets.size();++i)if(owner->m_animationSets[i])objects[objectCount++]=owner->m_animationSets[i];if(objectCount>64)std::abort();detour::Set dealloc;freeHooks=&dealloc;dealloc.redirect(reinterpret_cast<char*>(0x555268),mrFreeLinked,&freeObserved);if(dealloc.failed())std::abort();stage=5;typedef void(*Fn)(CMasterResourceManager*);Fn fn=c.op==2?(ours?mrDeleteNew:mrDeleteOld):(ours?mrDtorNew:mrDtorOld);if(autotest::beginInvocation(out,fn)){fn(owner);out.callCompleted=1;}stage=6;dealloc.restore();for(unsigned i=0;i<objectCount;++i){word(objectFreed[i]);if(objectFreed[i]!=1)out.issue=autotest::Capture::InvalidReport;}if(ours&&c.negative)word(0xfeed1234);word(masterFrees);if(c.op==1){rawState(owner);Ogre::NedAllocImpl::deallocBytes(owner);}}
 else{mrDtorOld(owner);Ogre::NedAllocImpl::deallocBytes(owner);}stage=7;word(m_pMasterResourceManager==NULL);bytes(profile+"resourceconfig.dat");if(detached)delete detached;delete dungeon;stage=8;mrFsDtor(fs);Ogre::NedAllocImpl::deallocBytes(fs);g_pFileSystem=previousFs;m_pMasterResourceManager=previousMaster;mrSettingsDtor(settings);Ogre::NedAllocImpl::deallocBytes(settings);stage=9;mrRootDtor(root);Ogre::NedAllocImpl::deallocBytes(root);for(Ogre::Root::PluginInstanceList::iterator i=plugins.begin();i!=plugins.end();++i)delete *i;if(chdir(cwd))std::abort();stage=10;
}
void oldSide(void*p,autotest::Capture&o){side(p,o,false);}void newSide(void*p,autotest::Capture&o){side(p,o,true);}unsigned operation;
int worker(const tlhybrid_host*host){diagHost=host;initEmptyGlobals();const uintptr_t strings[]={0x14b3af0};for(unsigned i=0;i<sizeof strings/sizeof strings[0];++i){void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(strings[i]),8);if(!p)new(reinterpret_cast<void*>(strings[i]))std::wstring;}char temp[]="/tmp/otl-master-recovery-XXXXXX";char*p=mkdtemp(temp);if(!p)return 1;directory=p;mkdir((directory+"/work").c_str(),0700);mkdir((directory+"/.runicgames").c_str(),0700);profile=directory+"/.runicgames/Torchlight/";mkdir(profile.c_str(),0700);std::wstring priorHome=LinuxUtils::gameHomePath,priorData=LinuxUtils::gameDataPath;LinuxUtils::gameHomePath=STRINGS::StringConvertToWide(directory+"/");LinuxUtils::gameDataPath=STRINGS::StringConvertToWide(directory+"/work/");root=Ogre::NedAllocImpl::allocBytes(0x398,0,0,0);std::string empty;mrRootCtor(root,empty,empty,empty);const char*names[]={"master_ctor_native","master_dtor_native","master_delete_native","master_ctor_mods_observed"};uintptr_t address=operation==1?(uintptr_t)mrDtorOld:operation==2?(uintptr_t)mrDeleteOld:(uintptr_t)mrCtorOld;autotest::Coverage coverage(names[operation],address);const unsigned total=24;int bad=0;for(unsigned seed=0;seed<total;++seed){Case c={seed,operation,0};autotest::Outcome a,b;autotest::runChild(oldSide,&c,a,8000,24000);autotest::runChild(newSide,&c,b,8000,24000);if(coverage.observe(host,a,b)){unsigned at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;host->log("    master op%u seed%u valid%u/%u exits%d/%d issue%u/%u first%u bytes%lu/%lu\n",operation,seed,a.reportValid,b.reportValid,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,at,(unsigned long)a.capture.length,(unsigned long)b.capture.length);bad=1;break;}}coverage.report(host);Case c={7,operation,1};autotest::Outcome a,b;autotest::runChild(oldSide,&c,a,8000,24000);autotest::runChild(newSide,&c,b,8000,24000);bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);bool complete=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);host->log("    %s negative detected%u completed%u\n",names[operation],unsigned(detected),unsigned(complete));mrRootDtor(root);Ogre::NedAllocImpl::deallocBytes(root);LinuxUtils::gameHomePath=priorHome;LinuxUtils::gameDataPath=priorData;clearTree(directory);rmdir(directory.c_str());return bad||coverage.completed!=total||!detected||!complete;}
}
TL_TEST(master_ctor_native){operation=0;return systems_fixture::isolated(worker,host,180);}
TL_TEST(master_dtor_native){operation=1;return systems_fixture::isolated(worker,host,180);}
TL_TEST(master_delete_native){operation=2;return systems_fixture::isolated(worker,host,180);}
TL_TEST(master_ctor_mods_observed){operation=3;return systems_fixture::isolated(worker,host,180);}
