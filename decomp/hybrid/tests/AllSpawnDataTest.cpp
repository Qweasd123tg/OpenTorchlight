#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <sys/stat.h>
#include <dlfcn.h>
#include <OgreHardwareBufferManager.h>
#include <OgreMaterialManager.h>
#include <OgreRoot.h>
#include "tests/FinishLevelFixture.h"
#define private public
#define protected public
#include "SpawnClassData.h"
#include "GameGlobals.h"
#include "GraphManager.h"
#include "Hierarchy.h"
#include "DataGroup.h"
#include "Settings.h"
#include "LinuxUtils.h"
#undef protected
#undef private

TL_ORIGINAL(void, spawnSettingsCtor, (CSettings*,std::wstring,std::wstring,std::wstring,std::wstring), "_ZN9CSettingsC1ESbIwSt11char_traitsIwESaIwEES3_S3_S3_")
TL_ORIGINAL(void, spawnMasterCtor, (CMasterResourceManager*,CSettings*), "_ZN22CMasterResourceManagerC1EP9CSettings")
TL_ORIGINAL(void, spawnMasterDtor, (CMasterResourceManager*), "_ZN22CMasterResourceManagerD1Ev")
TL_ORIGINAL(void, spawnSettingsDtor, (CSettings*), "_ZN9CSettingsD1Ev")
TL_ORIGINAL(void, spawnPlayerCtor, (CPlayer*,CResourceManager*), "_ZN7CPlayerC1EP16CResourceManager")
TL_ORIGINAL(void, spawnPlayerDtor, (CPlayer*), "_ZN7CPlayerD1Ev")
TL_ORIGINAL(void, spawnDataCtor, (CSpawnClassData*,const std::wstring&), "_ZN15CSpawnClassDataC1ERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void, spawnFillOld, (CSpawnClassData*,CCharacter*,int,int,int,int), "_ZN15CSpawnClassData14fillRandomizerEP10CCharacteriiii")
extern "C" void spawnFillNew(CSpawnClassData*,CCharacter*,int,int,int,int) __asm__("_ZN15CSpawnClassData14fillRandomizerEP10CCharacteriiii");
TL_ORIGINAL(void, spawnRollOld, (CSpawnClassData*,TArrayList<CDataGroup*>&,TArrayList<bool>*,CCharacter*,CCharacter*,int,int,int,int,int), "_ZN15CSpawnClassData18rollSpawnClassDataER10TArrayListIP10CDataGroupEPS0_IbEP10CCharacterS8_iiiii")
extern "C" void spawnRollNew(CSpawnClassData*,TArrayList<CDataGroup*>&,TArrayList<bool>*,CCharacter*,CCharacter*,int,int,int,int,int) __asm__("_ZN15CSpawnClassData18rollSpawnClassDataER10TArrayListIP10CDataGroupEPS0_IbEP10CCharacterS8_iiiii");
TL_FUNCTION(spawnLevelPlayer,"_ZN6CLevel9getPlayerEv")
TL_FUNCTION(spawnEffect,"_ZN10CCharacter14getEffectValueE12EEFFECT_TYPE13EDAMAGE_TYPES")
TL_FUNCTION(spawnRandom,"_ZN11CRandomizer9getRandomEv")
TL_FUNCTION(spawnDelegate,"_ZN11CSpawnClass14rollSpawnClassER10TArrayListIP10CDataGroupEPS0_IbEP10CCharacterS8_ijiiii")
TL_ORIGINAL(int,spawnRandomOriginal,(CRandomizer*),"_ZN11CRandomizer9getRandomEv")
extern "C" void spawnRootCtor(void*,const std::string&,const std::string&,const std::string&) __asm__("_ZN4Ogre4RootC1ERKSsS2_S2_");
extern "C" void spawnRootDtor(void*) __asm__("_ZN4Ogre4RootD1Ev");
extern "C" char spawnSetMaterial[] __asm__("_ZN4Ogre16SimpleRenderable11setMaterialERKSs");

namespace {
Ogre::SceneManager*activeScene;
void number(autotest::Capture&out,unsigned n){out.add(&n,4);}
struct NativeServices {
    void*root;
    CSettings*settings;
    CMasterResourceManager*master;
    std::string base;
    std::wstring previousHome;
    void*buffers;
    void(*bufferDtor)(void*);
    Ogre::SceneManager*scene;
    NativeServices():root(NULL),settings(NULL),master(NULL),previousHome(LinuxUtils::gameHomePath),buffers(NULL),bufferDtor(NULL),scene(NULL) {
        char path[]="/tmp/otl-spawn-XXXXXX";if(!mkdtemp(path))std::abort();
        base=std::string(path)+"/";mkdir((base+".runicgames").c_str(),0700);mkdir((base+".runicgames/Torchlight").c_str(),0700);
        LinuxUtils::gameHomePath=std::wstring(base.begin(),base.end());
        if (!Ogre::Root::getSingletonPtr()) {
            root=Ogre::NedAllocImpl::allocBytes(0x398,0,0,0);std::string empty;
            spawnRootCtor(root,empty,empty,empty);
        }
        if(!CMasterResourceManager::getSingleton()) {
            settings=static_cast<CSettings*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSettings),0,0,0));
            spawnSettingsCtor(settings,L"",L"",L"",L"");
            master=static_cast<CMasterResourceManager*>(Ogre::NedAllocImpl::allocBytes(sizeof(CMasterResourceManager),0,0,0));
            spawnMasterCtor(master,settings);
        }
        if(!Ogre::HardwareBufferManager::getSingletonPtr()){
            void*lib=dlopen("libOgreMain-1.6.5.so",RTLD_NOW|RTLD_NOLOAD);if(!lib)std::abort();
            void(*ctor)(void*)=reinterpret_cast<void(*)(void*)>(dlsym(lib,"_ZN4Ogre28DefaultHardwareBufferManagerC1Ev"));
            bufferDtor=reinterpret_cast<void(*)(void*)>(dlsym(lib,"_ZN4Ogre28DefaultHardwareBufferManagerD1Ev"));if(!ctor||!bufferDtor)std::abort();
            buffers=Ogre::NedAllocImpl::allocBytes(0x130,0,0,0);ctor(buffers);dlclose(lib);
        }
        scene=Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC);
        activeScene=scene;
        if(Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting").isNull())
            Ogre::MaterialManager::getSingleton().initialise();
        void*p=NULL;std::memcpy(&p,reinterpret_cast<void*>(0x148a300),sizeof p);if(!p)new(reinterpret_cast<void*>(0x148a300))std::string;
        std::memcpy(&p,reinterpret_cast<void*>(0x148a308),sizeof p);if(!p)new(reinterpret_cast<void*>(0x148a308))std::wstring;
    }
    ~NativeServices() {
        if(scene)Ogre::Root::getSingleton().destroySceneManager(scene);
        if(master){spawnMasterDtor(master);Ogre::NedAllocImpl::deallocBytes(master);spawnSettingsDtor(settings);Ogre::NedAllocImpl::deallocBytes(settings);}
        if(root){spawnRootDtor(root);Ogre::NedAllocImpl::deallocBytes(root);}
        if(buffers){bufferDtor(buffers);Ogre::NedAllocImpl::deallocBytes(buffers);}
        LinuxUtils::gameHomePath=previousHome;
        unlink((base+".runicgames/Torchlight/resourceconfig.dat").c_str());rmdir((base+".runicgames/Torchlight").c_str());rmdir((base+".runicgames").c_str());rmdir(base.c_str());
    }
    bool ready(){CMasterResourceManager*p=CMasterResourceManager::getSingleton();return p&&p->m_pHierarchy&&CGraphManager::getSingleton()&&CGameGlobals::getSingleton();}
};
struct Case{unsigned mode,seed;};
autotest::Capture*capture;
unsigned seed;
unsigned fishingMaterialCalls;
void fishingMaterial(Ogre::SimpleRenderable*,const std::string& name){
    // Only the constructor's GPU upload is replaced; the real player and line
    // keep their native owning lifecycle. This hook is gone before invocation.
    if(name!="FishingLine")std::abort();++fishingMaterialCalls;
}
CPlayer*player;
CCharacter*characters[3];
CRandomizer*randomizers[3];
detour::Set*randomHook;
CCharacter*getPlayer(CLevel*){number(*capture,71);return seed%3?player:NULL;}
float effect(CCharacter*who,EEFFECT_TYPE type,EDAMAGE_TYPES damage){
    unsigned id=99;for(unsigned i=0;i<3;++i)if(characters[i]==who)id=i;
    number(*capture,81);number(*capture,id);number(*capture,type);number(*capture,damage);
    const float values[]={0.0f,0.9f,1.9f,17.5f,-1.0f,-13.5f,100.0f,500.0f};
    return values[(seed+id*3)%8];
}
void randomState(CRandomizer*randomizer){
    number(*capture,randomizer!=NULL);if(!randomizer)return;
    number(*capture,randomizer->m_Choices.size());number(*capture,randomizer->m_Choices.m_nCapacity);
    for(unsigned i=0;i<randomizer->m_Choices.size();++i){number(*capture,randomizer->m_Choices[i]);capture->add(&randomizer->m_Odds[i],4);}
}
int randomValue(CRandomizer*self){
    unsigned id=3;for(unsigned i=0;i<3;++i)if(randomizers[i]==self)id=i;
    number(*capture,91);number(*capture,id);randomState(self);
    if(seed%5==0)return id==3?int((seed/5)%7)-2:int((seed/7)%11)-2;
    randomHook->restore();int value=spawnRandomOriginal(self);TL_REDIRECT(*randomHook,spawnRandom,&randomValue);
    if(randomHook->failed())std::abort();return value;
}
int delegate(CSpawnClass*,TArrayList<CDataGroup*>&groups,TArrayList<bool>*primary,
             CCharacter*who,CCharacter*rolling,int minimum,unsigned choices,int offset,int bonus,int rarity,int flags){
    number(*capture,101);number(*capture,groups.size());number(*capture,primary!=NULL);
    number(*capture,who==characters[0]);number(*capture,rolling==characters[1]);number(*capture,minimum);
    number(*capture,choices);number(*capture,offset);number(*capture,bonus);number(*capture,rarity);number(*capture,flags);
    return int(seed);
}
void execute(void*raw,autotest::Capture&out,bool ours){
    Case c=*static_cast<Case*>(raw);seed=c.seed;capture=&out;std::srand(seed+117);
    finishlevel::Fixture fixture;
    fixture.resources.m_pSceneManager=activeScene;
    CCharacter a(NULL),b(NULL),d(NULL);characters[0]=&a;characters[1]=&b;characters[2]=&d;
    CGraph minimum(GRAPH_LINEAR,L"spawn min",1),maximum(GRAPH_LINEAR,L"spawn max",1);
    minimum.addValue(0,0,0);minimum.addValue(20,10,0);minimum.processPoints();
    maximum.addValue(0,5,0);maximum.addValue(20,30,0);maximum.processPoints();
    void*memory=Ogre::NedAllocImpl::allocBytes(sizeof(CSpawnClassData),0,0,0);
    CSpawnClassData*self=static_cast<CSpawnClassData*>(memory);spawnDataCtor(self,std::wstring(L"spawn fixture"));
    self->m_pMinimumLevelGraph=&minimum;self->m_pMaximumLevelGraph=&maximum;
    CHierarchy*hierarchy=CMasterResourceManager::getSingleton()->m_pHierarchy;
    const unsigned parents[]={0x36,0x37,8,0xd,0x11,0xa0,0x18,0xfe};
    CDataGroup*groups[12];
    for(unsigned i=0;i<12;++i){
        groups[i]=new CDataGroup(L"unit",NULL,4,2,NULL);
        if((seed+i)%3)groups[i]->SetDataValue(L"RARITY",int((seed+i)%7)-2);
        groups[i]->SetDataValue(L"RARITY_HARDCORE",int((seed+i*2)%9)-3);
        if((seed+i)%4)groups[i]->SetDataValue(L"CREATEAS",L"EQUIPMENT",false);
        if((seed+i)%3)groups[i]->SetDataValue(L"NAME",i%2?L"sample":L"",false);
        groups[i]->SetDataValue(L"LEVEL",int((seed+i)%24)-2);
        if((seed+i)%4)groups[i]->SetDataValue(L"MINLEVEL",int((seed+i)%16)-3);
        if((seed+i)%5)groups[i]->SetDataValue(L"MAXLEVEL",int((seed+i*3)%21)-4);
        std::wstring type(1,wchar_t(L'A'+i));groups[i]->SetDataValue(L"UNITTYPE",type,false);
        unsigned id=500+i;hierarchy->m_typeIDs[type]=id;hierarchy->m_parentTypes[id].clear();
        hierarchy->m_parentTypes[id].push_back(id);hierarchy->m_parentTypes[id].push_back(parents[(seed+i)%8]);
        if(i<seed%13)self->m_lUnitDataObjects.add(groups[i]);
    }
    if(c.mode==0&&seed>=512){
        self->m_lUnitDataObjects.clear();
        for(unsigned i=0;i<12;++i){
            groups[i]->SetDataValue(L"CREATEAS",L"EQUIPMENT",false);
            groups[i]->SetDataValue(L"RARITY",int(1+i%3));
            groups[i]->SetDataValue(L"RARITY_HARDCORE",int(2+i%4));
            groups[i]->SetDataValue(L"LEVEL",7);
            groups[i]->SetDataValue(L"MINLEVEL",0);
            groups[i]->SetDataValue(L"MAXLEVEL",i%2?100:0);
            hierarchy->m_parentTypes[500+i].clear();
            hierarchy->m_parentTypes[500+i].push_back(parents[i%8]);
            self->m_lUnitDataObjects.add(groups[i]);
        }
    }
    int minimumLevel=int(seed%9)-2,offset=int((seed/3)%7)-3;
    int rarity=seed%5==0?int((seed/5)%7)-3:-1,flags=(seed/2)%32;
    if(c.mode==0&&seed>=512){minimumLevel=8;offset=0;rarity=-1;flags=seed%32;}
    a.m_eUnitType=static_cast<UNITTYPES::EUNITTYPES>(seed%2?0x29:8);
    a.m_pResourceManager=seed%4?&fixture.resources:NULL;fixture.level.m_dungeonDepth=int(seed%7)-2;
    detour::Set hooks;
    if(c.mode==0){
        player=static_cast<CPlayer*>(Ogre::NedAllocImpl::allocBytes(sizeof(CPlayer),0,0,0));
        {
            detour::Set graphics;fishingMaterialCalls=0;
            graphics.redirect(spawnSetMaterial,spawnSetMaterial,&fishingMaterial);
            if(graphics.failed()){out.issue=autotest::Capture::InvalidReport;return;}
            spawnPlayerCtor(player,&fixture.resources);
            if(fishingMaterialCalls!=1){out.issue=autotest::Capture::InvalidReport;return;}
        }
        player->m_saveOnDeath=seed%2;
        TL_REDIRECT(hooks,spawnLevelPlayer,&getPlayer);if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
        if(seed%3){self->m_pRandomizer=new CRandomizer(RANDOMIZER_NORMAL);self->m_pType1Randomizer=new CRandomizer(RANDOMIZER_NORMAL);self->m_pType2Randomizer=new CRandomizer(RANDOMIZER_NORMAL);self->m_pRandomizer->addChoice(17,3);}
        typedef void(*Fn)(CSpawnClassData*,CCharacter*,int,int,int,int);Fn fn=ours?spawnFillNew:spawnFillOld;
        if(!autotest::beginInvocation(out,fn))return;fn(self,seed%7?&a:NULL,minimumLevel,offset,rarity,flags);out.callCompleted=1;
    }else{
        self->m_pRandomizer=new CRandomizer(RANDOMIZER_NORMAL);self->m_pType1Randomizer=new CRandomizer(RANDOMIZER_NORMAL);self->m_pType2Randomizer=new CRandomizer(RANDOMIZER_NORMAL);
        randomizers[0]=self->m_pRandomizer;randomizers[1]=self->m_pType1Randomizer;randomizers[2]=self->m_pType2Randomizer;
        for(unsigned category=0;category<3;++category)for(unsigned j=0;j<(seed/(category+1))%5;++j)randomizers[category]->addChoice((j+category)%12,1+int(j));
        for(unsigned i=0;i<seed%4;++i)self->m_lPrimaryRandomizerIDs.add(i);
        self->m_iMinimumLevel=minimumLevel;self->m_iLevelOffset=offset;self->m_iRarityOverride=rarity;self->m_iFlags=flags;
        CGameGlobals*globals=CGameGlobals::getSingleton();globals->m_normalItemWeight=int(seed%13)-2;globals->m_magicItemWeight=int(seed%11)-1;globals->m_uniqueItemWeight=int(seed%7);
        globals->m_magicFindMagicInfluence=float(seed%5)*0.375f;globals->m_magicFindUniqueInfluence=float(seed%7)*0.25f;
        b.m_pMaster=seed%3?&a:NULL;a.m_pMaster=seed%2?&d:NULL;d.m_pMaster=NULL;
        TArrayList<CDataGroup*>result(2);TArrayList<bool>primary(2);result.add(groups[11]);primary.add(true);
        TL_REDIRECT(hooks,spawnEffect,&effect);detour::Set rng;randomHook=&rng;TL_REDIRECT(rng,spawnRandom,&randomValue);
        if(seed%17==0){self->m_pSpawnClass=new CSpawnClass(L"delegate");TL_REDIRECT(hooks,spawnDelegate,&delegate);}
        if(hooks.failed()||rng.failed()){out.issue=autotest::Capture::InvalidReport;return;}
        typedef void(*Fn)(CSpawnClassData*,TArrayList<CDataGroup*>&,TArrayList<bool>*,CCharacter*,CCharacter*,int,int,int,int,int);Fn fn=ours?spawnRollNew:spawnRollOld;
        if(!autotest::beginInvocation(out,fn))return;fn(self,result,seed%3?&primary:NULL,&a,seed%7?&b:NULL,minimumLevel,offset,int(seed%31)-5,rarity,flags);out.callCompleted=1;
        number(out,result.size());for(unsigned i=0;i<result.size();++i){unsigned id=99;for(unsigned j=0;j<12;++j)if(result[i]==groups[j])id=j;number(out,id);}
        number(out,primary.size());for(unsigned i=0;i<primary.size();++i)number(out,primary[i]);
    }
    number(out,self->m_iMinimumLevel);number(out,self->m_iLevelOffset);number(out,self->m_iRarityOverride);number(out,self->m_iFlags);
    randomState(self->m_pRandomizer);randomState(self->m_pType1Randomizer);randomState(self->m_pType2Randomizer);
    number(out,self->m_lPrimaryRandomizerIDs.size());for(unsigned i=0;i<self->m_lPrimaryRandomizerIDs.size();++i)number(out,self->m_lPrimaryRandomizerIDs[i]);
    delete self->m_pSpawnClass;self->m_pSpawnClass=NULL;self->~CSpawnClassData();Ogre::NedAllocImpl::deallocBytes(self);
    for(unsigned i=0;i<12;++i)delete groups[i];
    if(c.mode==0){spawnPlayerDtor(player);Ogre::NedAllocImpl::deallocBytes(player);player=NULL;}
}
void original(void*p,autotest::Capture&o){execute(p,o,false);}void candidate(void*p,autotest::Capture&o){execute(p,o,true);}
int run(const tlhybrid_host*host,unsigned mode,const char*name,uintptr_t address){
    NativeServices services;if(!services.ready()){host->log("native bootstrap missing owning services\n");return 1;}
    autotest::Coverage coverage(name,address);
    for(unsigned seed=0;seed<(mode==0?1024u:512u);++seed){Case c={mode,seed};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        if(coverage.observe(host,a,b)){host->log("    spawn mode%u seed%u issues%u/%u exits%d/%d lengths%lu/%lu\n",mode,seed,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,(unsigned long)a.capture.length,(unsigned long)b.capture.length);
            for(size_t i=0;i<a.capture.length&&i<b.capture.length;++i)if(a.capture.data[i]!=b.capture.data[i]){host->log("    first different byte%lu: %u/%u\n",(unsigned long)i,(unsigned char)a.capture.data[i],(unsigned char)b.capture.data[i]);break;}
            if(a.capture.length<1024&&b.capture.length<1024){for(size_t i=0;i<a.capture.length/4;++i){unsigned x,y;std::memcpy(&x,a.capture.data+4*i,4);std::memcpy(&y,b.capture.data+4*i,4);host->log("    word%lu %u/%u\n",(unsigned long)i,x,y);}}
            coverage.report(host);return 1;}}
    coverage.report(host);return 0;
}
}
TL_TEST(all_spawn_data_fill){return run(host,0,"all_spawn_data_fill",(uintptr_t)&spawnFillOld);}
TL_TEST(all_spawn_data_roll){return run(host,1,"all_spawn_data_roll",(uintptr_t)&spawnRollOld);}
