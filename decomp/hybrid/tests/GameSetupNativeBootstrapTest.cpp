#include <sys/stat.h>
#include "LinuxUtils.h"
#include <execinfo.h>
#include "AutoTest.h"
#include "tests/SystemsFixtureWorker.h"
#include "tests/SystemsNativeGame.h"
#include "tests/GameSetupCleanBootstrap.h"
#include "SteamStats.h"
#include "MasterResourceManager.h"
#include <ParticleUniverseSystemManager.h>
TL_ORIGINAL(void,setupPuCtor,(ParticleUniverse::ParticleSystemManager*,float,unsigned),"_ZN16ParticleUniverse21ParticleSystemManagerC1Efj")
TL_ORIGINAL(void,setupPuDtor,(ParticleUniverse::ParticleSystemManager*),"_ZN16ParticleUniverse21ParticleSystemManagerD1Ev")
TL_ORIGINAL(void,setupStatsCtor,(CSteamStats*),"_ZN11CSteamStatsC1Ev")
TL_ORIGINAL(void,setupStatsDtor,(CSteamStats*),"_ZN11CSteamStatsD1Ev")
TL_ORIGINAL(void,setupMasterCtor,(CMasterResourceManager*,CSettings*),"_ZN22CMasterResourceManagerC1EP9CSettings")
TL_ORIGINAL(void,setupMasterDtor,(CMasterResourceManager*),"_ZN22CMasterResourceManagerD1Ev")
namespace {
const tlhybrid_host*debugHost;void fault(int signal){void*frames[48];int count=backtrace(frames,48);debugHost->log("    bootstrap signal%u frames%u\n",signal,count);for(int i=0;i<count;++i)debugHost->log("    bootstrap frame%d %p\n",i,frames[i]);_exit(128+signal);}
int worker(const tlhybrid_host*host){debugHost=host;signal(SIGABRT,fault);signal(SIGSEGV,fault);
 if(!game_setup_fixture::finishInheritedOwners())return 1;
 char directory[]="/tmp/otl-setup-bootstrap-XXXXXX";if(!mkdtemp(directory))return 6;std::string base=std::string(directory)+"/";mkdir((base+".runicgames").c_str(),0700);mkdir((base+".runicgames/Torchlight").c_str(),0700);std::wstring previousHome=LinuxUtils::gameHomePath;LinuxUtils::gameHomePath=std::wstring(base.begin(),base.end());
 SystemsNativeGame native;
 host->log("    setup bootstrap actual Game/Settings/Root C1 completed\n");
 Ogre::Root*previous=native.root;native.root=NULL;native.ownsRoot=false;systemsGameRootDtor(previous);Ogre::NedAllocImpl::deallocBytes(previous);
 if(Ogre::Root::getSingletonPtr())return 2;
 host->log("    setup bootstrap previous Root D1 completed\n");
 Ogre::Root*root=static_cast<Ogre::Root*>(Ogre::NedAllocImpl::allocBytes(sizeof(Ogre::Root),0,0,0));std::string empty;systemsGameRootCtor(root,empty,empty,empty);
 host->log("    setup bootstrap new actual Root C1 completed\n");
 typedef ParticleUniverse::ParticleSystemManager PU;
 if(PU::getSingletonPtr())return 3;
 PU*pu=static_cast<PU*>(::operator new(sizeof(PU)));setupPuCtor(pu,150.f,2);
 host->log("    setup bootstrap actual PU C1 completed pool%u available%lu falloff%g\n",pu->m_maxParticles,(unsigned long)pu->m_availableParticles.size(),pu->m_particleFalloff);
 if(PU::getSingletonPtr()!=pu||pu->m_maxParticles!=2||pu->m_availableParticles.size()!=2)return 4;
 setupPuDtor(pu);::operator delete(pu);
 host->log("    setup bootstrap standalone PU D1 completed\n");
 CSteamStats*stats=static_cast<CSteamStats*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSteamStats),0,0,0));setupStatsCtor(stats);
 host->log("    setup bootstrap actual SteamStats C1 completed\n");
 setupStatsDtor(stats);Ogre::NedAllocImpl::deallocBytes(stats);
 CMasterResourceManager*master=static_cast<CMasterResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CMasterResourceManager),0,0,0));setupMasterCtor(master,native.settings);
 host->log("    setup bootstrap actual Master C1 completed pu%u missile%u\n",master->m_pParticleSystemManager==PU::getSingletonPtr(),master->m_missilePreloader!=NULL);
 if(master->m_pParticleSystemManager!=PU::getSingletonPtr()||!master->m_missilePreloader)return 5;
 setupMasterDtor(master);Ogre::NedAllocImpl::deallocBytes(master);
 host->log("    setup bootstrap native owners D1 completed\n");
 systemsGameRootDtor(root);Ogre::NedAllocImpl::deallocBytes(root);
 host->log("    setup bootstrap final Root D1 completed\n");LinuxUtils::gameHomePath=previousHome;unlink((base+".runicgames/Torchlight/resourceconfig.dat").c_str());rmdir((base+".runicgames/Torchlight").c_str());rmdir((base+".runicgames").c_str());rmdir(directory);return 0;
}
}
TL_TEST(native_game_setup_bootstrap){return systems_fixture::isolated(worker,host);}

#include "tests/NativeGameServices.h"
namespace { int dirtyParentWorker(const tlhybrid_host* h){
    new nativegame::Services; // real owners live until private worker exit
    return worker(h);
} }
TL_TEST(native_game_setup_bootstrap_dirty_parent){return systems_fixture::isolated(dirtyParentWorker,host);}
