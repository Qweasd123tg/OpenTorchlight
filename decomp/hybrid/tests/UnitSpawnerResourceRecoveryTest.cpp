#include <Ogre.h>
#include <string>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "UnitSpawner.h"
#include "ResourceManager.h"
#include "Hierarchy.h"
#include "SpawnClassParser.h"
#include "SpawnClass.h"
#include "UnitResourceList.h"
#undef protected
#undef private
#include "UnitSpawnerDescriptor.h"
#include "MasterResourceManager.h"
#include "MissilePreloader.h"
#include "FileSystem.h"
#include "tests/NativeGameServices.h"

TL_ORIGINAL(std::wstring, urOld, (CEditorScene*,CEditorBaseObject*,unsigned,void*), "_ZN22CUnitSpawnerDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv")
extern "C" std::wstring urNew(CEditorScene*,CEditorBaseObject*,unsigned,void*) __asm__("_ZN22CUnitSpawnerDescriptor21GetResourceStringByIDEP12CEditorSceneP17CEditorBaseObjectjPv");
TL_ORIGINAL(void, urResourceCtor, (CResourceManager*,Ogre::SceneManager*), "_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void, urResourceDtor, (CResourceManager*), "_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void, urSpawnerCtor, (CUnitSpawner*,CResourceManager*), "_ZN12CUnitSpawnerC1EP16CResourceManager")
TL_ORIGINAL(void, urSpawnerDtor, (CUnitSpawner*), "_ZN12CUnitSpawnerD1Ev")
TL_ORIGINAL(void, urBaseCtor, (CEditorBaseObject*), "_ZN17CEditorBaseObjectC1Ev")
TL_ORIGINAL(void, urBaseDtor, (CEditorBaseObject*), "_ZN17CEditorBaseObjectD1Ev")
TL_ORIGINAL(void, urClassCtor, (CSpawnClass*,const wchar_t*), "_ZN11CSpawnClassC1EPKw")
TL_ORIGINAL(void, urClassDtor, (CSpawnClass*), "_ZN11CSpawnClassD1Ev")
TL_ORIGINAL(void, urGroupCtor, (CDataGroup*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*), "_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void, urGroupDtor, (CDataGroup*), "_ZN10CDataGroupD1Ev")
TL_FUNCTION(urMaster, "_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(urParser, "_ZN17CSpawnClassParser12getSingletonEv")
TL_FUNCTION(urTypeName, "_ZN10CHierarchy11getTypeNameEj")
TL_FUNCTION(urGroup, "_ZN17CUnitResourceList14getGroupByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(urMissiles, "_ZN17CMissilePreloader15getMissileNamesER10TArrayListISbIwSt11char_traitsIwESaIwEEE")
TL_FUNCTION(urFiles, "_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
extern "C" TArrayList<std::wstring> urParticleCache __asm__("_ZL14gParticleFiles");
extern "C" TArrayList<std::wstring> urMissileCache __asm__("_ZL13gMissileFiles");

namespace {
struct Case { unsigned category,count,index,cache,object,negative; };
const wchar_t* categories[]={L"Monsters",L"Items",L"Particle",L"Spawn Class",L"Missiles",L"Unit Type",L"Props",L"unknown-\u0416\u4e2d",L"monsters"};
const unsigned counts[]={0,1,3,12};
const unsigned indices[]={0,1,2,3,4,13,0xffffffffu};
const Case* current;
autotest::Capture* capture;
nativegame::Services* services;
CMasterResourceManager* master;
CSpawnClassParser* parser;
CHierarchy* hierarchy;
CUnitResourceList* resourcesList;
CMissilePreloader* missiles;
CFileSystem* filesystem;
std::map<long long,CDataGroup*> groups;
unsigned masterCalls,parserCalls,typeCalls,groupCalls,missileCalls,fileCalls;
unsigned diagnosticPhase;bool diagnosticOurs;

void number(unsigned n){capture->add(&n,sizeof n);}
void valid(bool yes){if(!yes){
    std::fprintf(stderr,"    UR_INVALID phase=%u ours=%u category=%u count=%u index=%u cache=%u object=%u totalObjects=%d\n",diagnosticPhase,unsigned(diagnosticOurs),current->category,current->count,current->index,current->cache,current->object,g_iTotalCountOfObjects);
    capture->issue=autotest::Capture::InvalidReport;
}}
template<class T> T* allocate(){return static_cast<T*>(Ogre::NedAllocImpl::allocBytes(sizeof(T),0,0,0));}
template<class T> void swapList(TArrayList<T>& a,TArrayList<T>& b){
    std::swap(a.m_pData,b.m_pData);std::swap(a.m_nCount,b.m_nCount);
    std::swap(a.m_nCapacity,b.m_nCapacity);std::swap(a.m_nGrowBy,b.m_nGrowBy);
}
template<class T> struct ScopedList {
    TArrayList<T>& target;TArrayList<T> previous;
    ScopedList(TArrayList<T>& list):target(list),previous(10){swapList(target,previous);}
    ~ScopedList(){target.clear();swapList(target,previous);}
};
std::wstring ordinal(unsigned i){char text[32];std::sprintf(text,"entry-%02u-",i);return std::wstring(text,text+std::strlen(text))+L"\u0416\u4e2d";}
std::wstring missileName(unsigned i){return L"missile/"+ordinal(i);}
std::wstring particleName(unsigned i){return L"media/particles/"+(i==0&&current->cache?std::wstring():ordinal(i));}
void dumpList(TArrayList<std::wstring>& list){
    number(list.size());number(list.m_nCapacity);number(list.m_nGrowBy);
    for(unsigned i=0;i<list.size();++i)capture->addText(list[i]);
}
void dumpCalls(){number(masterCalls);number(parserCalls);number(typeCalls);number(groupCalls);number(missileCalls);number(fileCalls);}

CMasterResourceManager* getMaster(){number(11);++masterCalls;return master;}
CSpawnClassParser* getParser(){number(13);++parserCalls;return parser;}
std::wstring getTypeName(CHierarchy* owner,unsigned type){
    valid(owner==hierarchy);number(17);number(type);++typeCalls;return ordinal(type);
}
std::map<long long,CDataGroup*>* getGroup(CUnitResourceList* owner,const std::wstring& name){
    valid(owner==resourcesList);number(19);capture->addText(name);++groupCalls;
    valid(name==(current->category==0?L"MONSTERS":current->category==1?L"ITEMS":L"PROPS"));
    return &groups;
}
void getMissiles(CMissilePreloader* owner,TArrayList<std::wstring>& result){
    valid(owner==missiles && &result==&urMissileCache);number(23);number(result.size());++missileCalls;
    for(unsigned i=0;i<current->count;++i)result.add(missileName(i));
}
unsigned getFiles(CFileSystem* owner,const std::wstring& directory,TArrayList<std::wstring>& result,std::wstring pattern,bool recursive,bool strip,bool modsOnly,bool skipMods){
    valid(owner==filesystem && &result==&urParticleCache);number(29);capture->addText(directory);capture->addText(pattern);
    number(recursive);number(strip);number(modsOnly);number(skipMods);number(result.size());++fileCalls;
    valid(directory==L"media/particles/"&&pattern==L"*.layout"&&recursive&&strip&&!modsOnly&&!skipMods);
    for(unsigned i=0;i<current->count;++i)result.add(particleName(i));return current->count+87;
}

void side(void* raw,autotest::Capture& out,bool ours){
    current=static_cast<Case*>(raw);capture=&out;diagnosticPhase=0;diagnosticOurs=ours;
    masterCalls=parserCalls=typeCalls=groupCalls=missileCalls=fileCalls=0;
    TSafePointer<CResourceManager> resourceWitness;
    TSafePointer<CUnitSpawner> spawnerWitness;
    TSafePointer<CEditorBaseObject> baseWitness;
    std::vector<TSafePointer<CSpawnClass>*> classWitnesses;
    std::vector<TSafePointer<CDataGroup>*> groupWitnesses;
    int objectCount=g_iTotalCountOfObjects;
    int setupCount=objectCount,afterCalls=objectCount;
    diagnosticPhase=1;CResourceManager* resources=allocate<CResourceManager>();urResourceCtor(resources,services->scene);resourceWitness.setObject(resources);
    diagnosticPhase=2;CUnitSpawner* spawner=allocate<CUnitSpawner>();urSpawnerCtor(spawner,resources);spawnerWitness.setObject(spawner);
    diagnosticPhase=3;CEditorBaseObject* base=allocate<CEditorBaseObject>();urBaseCtor(base);baseWitness.setObject(base);
    spawner->m_category=categories[current->category];spawner->m_resourceSpawn=L"unchanged-resource";
    CEditorBaseObject* supplied=current->object==0?NULL:current->object==1?base:spawner;
    if(current->object==2)spawner->m_pResourceManager=NULL;
    {ScopedList<std::wstring> particleScope(urParticleCache),missileScope(urMissileCache);
     ScopedList<unsigned> typesScope(hierarchy->m_types);
     std::map<std::wstring,CSpawnClass*> previousClasses;previousClasses.swap(parser->m_spawnClasses);
     groups.clear();
     for(unsigned i=0;i<current->count;++i){
         unsigned type=i%4==0?0:i%4==1?7:i%4==2?0xffffffffu:19;hierarchy->m_types.add(type);
         CSpawnClass* spawn=allocate<CSpawnClass>();std::wstring key=ordinal(current->count-i);urClassCtor(spawn,key.c_str());parser->m_spawnClasses[key]=spawn;
         TSafePointer<CSpawnClass>* cw=new TSafePointer<CSpawnClass>;cw->setObject(spawn);classWitnesses.push_back(cw);
         CDataGroup* group=allocate<CDataGroup>();urGroupCtor(group,ordinal(i),NULL,10,10,NULL);
         if(i%3)group->SetDataValue(L"NAME",ordinal(i),false);
         group->SetDataValue(L"GUID",static_cast<long long>(i));
         groups[i%2?-static_cast<long long>(i):100-static_cast<long long>(i)]=group;
         TSafePointer<CDataGroup>* gw=new TSafePointer<CDataGroup>;gw->setObject(group);groupWitnesses.push_back(gw);
         if(current->cache){urParticleCache.add(particleName(i));urMissileCache.add(missileName(i));}
     }
     diagnosticPhase=20;detour::Set hooks;TL_REDIRECT(hooks,urMaster,&getMaster);TL_REDIRECT(hooks,urParser,&getParser);
     TL_REDIRECT(hooks,urTypeName,&getTypeName);TL_REDIRECT(hooks,urGroup,&getGroup);
     TL_REDIRECT(hooks,urMissiles,&getMissiles);TL_REDIRECT(hooks,urFiles,&getFiles);
     if(hooks.failed()){std::fprintf(stderr,"    UR_HOOK_FAILURE reason=%u site=%p ours=%u\n",unsigned(hooks.failure()),hooks.failureSite(),unsigned(ours));out.issue=autotest::Capture::InvalidReport;return;}
     setupCount=g_iTotalCountOfObjects;
     valid(setupCount-objectCount>=3);
     typedef std::wstring(*Function)(CEditorScene*,CEditorBaseObject*,unsigned,void*);Function fn=ours?urNew:urOld;
     if(autotest::beginInvocation(out,fn)){
         diagnosticPhase=30;
         std::wstring first=fn(NULL,supplied,current->index,current->cache?resources:NULL);
         diagnosticPhase=31;
         capture->addText(first);dumpCalls();dumpList(urParticleCache);dumpList(urMissileCache);
         std::wstring second=fn(NULL,supplied,current->index,current->cache?NULL:resources);out.callCompleted=1;
         afterCalls=g_iTotalCountOfObjects;
         diagnosticPhase=32;
         if(ours&&current->negative)second+=L"!";
         capture->addText(second);dumpCalls();dumpList(urParticleCache);dumpList(urMissileCache);
     }
     diagnosticPhase=40;hooks.restore();capture->addText(spawner->m_category);capture->addText(spawner->m_resourceSpawn);
     valid(afterCalls==setupCount);
     number(hierarchy->m_types.size());for(unsigned i=0;i<hierarchy->m_types.size();++i)number(hierarchy->m_types[i]);
     number(parser->m_spawnClasses.size());
     for(std::map<std::wstring,CSpawnClass*>::iterator i=parser->m_spawnClasses.begin();i!=parser->m_spawnClasses.end();++i){capture->addText(i->first);urClassDtor(i->second);Ogre::NedAllocImpl::deallocBytes(i->second);}
     parser->m_spawnClasses.clear();previousClasses.swap(parser->m_spawnClasses);
     for(std::map<long long,CDataGroup*>::iterator i=groups.begin();i!=groups.end();++i){urGroupDtor(i->second);Ogre::NedAllocImpl::deallocBytes(i->second);}groups.clear();
    }
    spawner->m_pResourceManager=resources;
    diagnosticPhase=60;urSpawnerDtor(spawner);Ogre::NedAllocImpl::deallocBytes(spawner);
    diagnosticPhase=61;urBaseDtor(base);Ogre::NedAllocImpl::deallocBytes(base);
    diagnosticPhase=62;urResourceDtor(resources);Ogre::NedAllocImpl::deallocBytes(resources);
    diagnosticPhase=70;
    number(!spawnerWitness.getObject());number(!baseWitness.getObject());number(!resourceWitness.getObject());
    valid(!spawnerWitness.getObject()&&!baseWitness.getObject()&&!resourceWitness.getObject());
    for(unsigned i=0;i<classWitnesses.size();++i){number(!classWitnesses[i]->getObject());valid(!classWitnesses[i]->getObject());delete classWitnesses[i];}
    for(unsigned i=0;i<groupWitnesses.size();++i){number(!groupWitnesses[i]->getObject());valid(!groupWitnesses[i]->getObject());delete groupWitnesses[i];}
    // Native CRunicCore C1 increments this cumulative constructor count;
    // native D1 never decrements it. Weak witnesses above verify destruction.
    diagnosticPhase=71;int deltas[]={setupCount-objectCount,afterCalls-setupCount,g_iTotalCountOfObjects-afterCalls};
    capture->add(deltas,sizeof deltas);valid(deltas[1]==0&&deltas[2]==0);
}
void before(void* p,autotest::Capture& out){side(p,out,false);}
void after(void* p,autotest::Capture& out){side(p,out,true);}
bool guards;
int worker(const tlhybrid_host* host){
    nativegame::Services native;services=&native;if(!native.ready())return 1;
    master=CMasterResourceManager::getSingleton();parser=CSpawnClassParser::getSingleton();hierarchy=master->m_pHierarchy;
    resourcesList=CUnitResourceList::getSingleton();missiles=CMissilePreloader::getSinglelton();filesystem=CFileSystem::getSingleton();
    if(!parser||!hierarchy||!resourcesList||!missiles||!filesystem)return 1;
    const char* label=guards?"unit_spawner_resource_guards":"unit_spawner_resource_recovery";
    autotest::Coverage coverage(label,0x65e3e0);unsigned completed=guards?64:504;
    for(unsigned seed=0;seed<completed;++seed){
        const unsigned guardCategories[]={7,3,5,2};const unsigned guardIndices[]={0,1,2,0xffffffffu};
        Case c={guards?guardCategories[seed/16]:seed%9,guards?3:counts[seed/9%4],guards?guardIndices[seed/4%4]:indices[seed/36%7],guards?seed%2:seed/252,guards?seed%4:3,0};
        autotest::Outcome a,b;autotest::runChild(before,&c,a,16000,20000);autotest::runChild(after,&c,b,16000,20000);
        if(coverage.observe(host,a,b)){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;
            host->log("    resource seed%u guards%u valid%u/%u completed%u/%u status%d/%d issue%u/%u bytes%lu/%lu first%lu\n",seed,unsigned(guards),a.reportValid,b.reportValid,a.capture.callCompleted,b.capture.callCompleted,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at);coverage.report(host);return 1;}
    }
    coverage.report(host);Case control={guards?7u:4u,3,2,0,guards?1u:3u,1};autotest::Outcome a,b;
    autotest::runChild(before,&control,a,16000,20000);autotest::runChild(after,&control,b,16000,20000);
    bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    bool complete=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);
    host->log("    %s negative detected%u completed%u\n",label,unsigned(detected),unsigned(complete));
    return coverage.completed!=completed||coverage.missing||coverage.different||!detected||!complete;
}
}
TL_TEST(unit_spawner_resource_recovery){guards=false;return systems_fixture::isolated(worker,host,300);}
TL_TEST(unit_spawner_resource_guards){guards=true;return systems_fixture::isolated(worker,host,300);}
