#ifndef COMPLETE_SYSTEMS_NATIVE_MASTER_H
#define COMPLETE_SYSTEMS_NATIVE_MASTER_H
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <OgreRoot.h>
#include "Settings.h"
#include "MasterResourceManager.h"
#include "LinuxUtils.h"
#include "AutoTest.h"
TL_ORIGINAL(void, systemsNativeSettingsCtor, (CSettings*,std::wstring,std::wstring,std::wstring,std::wstring), "_ZN9CSettingsC1ESbIwSt11char_traitsIwESaIwEES3_S3_S3_")
TL_ORIGINAL(void, systemsNativeSettingsDtor, (CSettings*), "_ZN9CSettingsD1Ev")
TL_ORIGINAL(void, systemsNativeMasterCtor, (CMasterResourceManager*,CSettings*), "_ZN22CMasterResourceManagerC1EP9CSettings")
TL_ORIGINAL(void, systemsNativeMasterDtor, (CMasterResourceManager*), "_ZN22CMasterResourceManagerD1Ev")
extern "C" void systemsNativeRootCtor(void*,const std::string&,const std::string&,const std::string&) __asm__("_ZN4Ogre4RootC1ERKSsS2_S2_");
extern "C" void systemsNativeRootDtor(void*) __asm__("_ZN4Ogre4RootD1Ev");
class SystemsNativeMaster {
    std::string base;
    std::wstring previousHome;
    bool ownsRoot;
public:
    Ogre::Root* root;
    CSettings* settings;
    CMasterResourceManager* master;
    SystemsNativeMaster():previousHome(LinuxUtils::gameHomePath),ownsRoot(false),root(NULL),settings(NULL),master(NULL) {
        char home[]="/tmp/otl-native-master-XXXXXX";
        if(!mkdtemp(home))_exit(70);
        base=std::string(home)+"/";LinuxUtils::gameHomePath=std::wstring(base.begin(),base.end());
        if(mkdir((base+".runicgames").c_str(),0700)||mkdir((base+".runicgames/Torchlight").c_str(),0700))_exit(71);
        root=Ogre::Root::getSingletonPtr();
        if (!root) {
            root=static_cast<Ogre::Root*>(Ogre::NedAllocImpl::allocBytes(0x398,0,0,0));
            std::string empty;systemsNativeRootCtor(root,empty,empty,empty);
            ownsRoot=true;
        }
        settings=static_cast<CSettings*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSettings),0,0,0));
        systemsNativeSettingsCtor(settings,L"",L"",L"",L"");
        master=static_cast<CMasterResourceManager*>(Ogre::NedAllocImpl::allocBytes(0x190,0,0,0));
        systemsNativeMasterCtor(master,settings);
    }
    ~SystemsNativeMaster(){
        systemsNativeMasterDtor(master);Ogre::NedAllocImpl::deallocBytes(master);
        systemsNativeSettingsDtor(settings);Ogre::NedAllocImpl::deallocBytes(settings);
        if (ownsRoot) {systemsNativeRootDtor(root);Ogre::NedAllocImpl::deallocBytes(root);}
        LinuxUtils::gameHomePath=previousHome;
        unlink((base+".runicgames/Torchlight/resourceconfig.dat").c_str());
        rmdir((base+".runicgames/Torchlight").c_str());rmdir((base+".runicgames").c_str());
        rmdir(base.substr(0,base.size()-1).c_str());
    }
};
#endif
