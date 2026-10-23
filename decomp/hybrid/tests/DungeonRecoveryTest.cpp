#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <fenv.h>
#include <unistd.h>
#define private public
#include "Dungeon.h"
#include "LevelTemplateData.h"
#include "DataGroup.h"
#undef private
#include "StringUtilities.h"
#include "GameVariables.h"
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"

TL_ORIGINAL(void, drCtor, (CDungeon*), "_ZN8CDungeonC1Ev")
TL_ORIGINAL(void, drDtor, (CDungeon*), "_ZN8CDungeonD1Ev")
TL_ORIGINAL(void, drTemplateCtor, (CLevelTemplateData*, const wchar_t*), "_ZN18CLevelTemplateDataC1EPKw")
TL_ORIGINAL(void, drTemplateDtor, (CLevelTemplateData*), "_ZN18CLevelTemplateDataD1Ev")
TL_ORIGINAL(CLevelTemplateData*, drGetOld, (CDungeon*, unsigned), "_ZN8CDungeon17getStrataTemplateEj")
extern "C" CLevelTemplateData* drGetNew(CDungeon*, unsigned) __asm__("_ZN8CDungeon17getStrataTemplateEj");
TL_ORIGINAL(bool, drLoadOld, (CDungeon*, const wchar_t*), "_ZN8CDungeon11loadDungeonEPKw")
extern "C" bool drLoadNew(CDungeon*, const wchar_t*) __asm__("_ZN8CDungeon11loadDungeonEPKw");
TL_FUNCTION(drTemplateLoad, "_ZN18CLevelTemplateData4loadEPKw")
TL_FUNCTION(drGroupLoad, "_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
TL_FUNCTION(drFloat, "_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEf")

namespace dungeon_recovery {
struct Case { unsigned seed; bool nativeData, negative; };
static const Case* current;
static autotest::Capture* output;
static CDungeon* dungeon;
static unsigned errors, levelLoads, groupLoads, floatLoads;
static bool armed, observeFloats;
static detour::Set* floatPatch;
static std::vector<CLevelTemplateData*> created;
static std::vector<TSafePointer<CRunicCore>*> witnesses;
static CLevelTemplateData* alternate;
static std::string temporary;
static void number(unsigned value) { output->add(&value, sizeof value); }
static void real(float value) { output->add(&value, sizeof value); }
static void text(const std::wstring& value) { output->addText(value); }
static void valid(bool condition, unsigned code) { if (!condition) { ++errors; number(0xd7000000u + code); } }
static void watch(CRunicCore* p) { TSafePointer<CRunicCore>* w = new TSafePointer<CRunicCore>; w->setObject(p); witnesses.push_back(w); }
static void nativeStrings() {
    const uintptr_t empty[] = {0x1490de8, 0x1495cc8};
    for (unsigned i=0; i<2; ++i) { void* p=NULL; std::memcpy(&p,reinterpret_cast<void*>(empty[i]),sizeof p); if(!p)new(reinterpret_cast<void*>(empty[i]))std::wstring; }
    const uintptr_t bases[]={0x1490e00,0x1490e60,0x1490ec0,0x1490f80};
    const std::wstring* values[]={g_LEVELLAYOUT_CREATION_NAMES,g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES,g_LEVELLAYOUT_CREATION_PATHNODES,g_LEVELLAYOUT_CREATION_COUNTS};
    const unsigned count[]={11,11,22,22};
    for(unsigned a=0;a<4;++a)for(unsigned i=0;i<count[a];++i){void* p=NULL;std::memcpy(&p,reinterpret_cast<void*>(bases[a]+i*8),8);if(!p)new(reinterpret_cast<void*>(bases[a]+i*8))std::wstring(values[a][i]);}
}
template<class T> static void shape(const TArrayList<T>& list) { number(list.size());number(list.m_nCapacity);number(list.m_nGrowBy);number(list.m_pData!=NULL); }
static void randomizer(CRandomizer& r) {
    shape(r.m_Choices);for(unsigned i=0;i<r.m_Choices.size();++i)number(r.m_Choices[i]);
    shape(r.m_Odds);for(unsigned i=0;i<r.m_Odds.size();++i)real(r.m_Odds[i]);
    shape(r.m_ComputedOdds);for(unsigned i=0;i<r.m_ComputedOdds.size();++i)real(r.m_ComputedOdds[i]);
    number(r.m_eType);real(r.m_fDecay);number(r.m_bOddsDirty);
}
static int levelID(CLevelTemplateData* p) { if(!p)return -1;for(unsigned i=0;i<created.size();++i)if(created[i]==p)return i;return -2; }
static void baseLevel(CLevelTemplateData* p,unsigned serial) {
    p->m_levelName=L"loaded name \u03a9";p->m_string60=L"loaded fallback";p->m_cinematic=L"loaded cinema";
    p->m_monsterLevelMin=70+serial;p->m_monsterLevelMax=90+serial;
    p->m_questSelectionExcluded=(current->seed/2)%2;p->m_dontStore=(current->seed/3)%2;
    p->m_permitsPortal=false;p->m_permitsPetDeparture=false;p->m_isTown=true;
    for(unsigned i=0;i<11;++i){p->m_unitSpawnerNames[i]=L"base/"+STRINGS::GetValueAsWString(i);p->m_selectedUnitSpawners[i]=L"chosen";p->m_useSpawnClass[i]=(current->seed+i)%2;
        p->m_densityRanges[i].minimum=float(i)+0.125f;p->m_densityRanges[i].maximum=float(i)+0.75f;
        p->m_countRanges[i].minimum=float(20+i);p->m_countRanges[i].maximum=float(40+i);}
}
static CLevelTemplateData* nativeLevel() {
    CLevelTemplateData* p=static_cast<CLevelTemplateData*>(Ogre::NedAllocImpl::allocBytes(sizeof(CLevelTemplateData),0,0,0));drTemplateCtor(p,NULL);baseLevel(p,created.size());created.push_back(p);watch(p);return p;
}
static void levelLoad(CLevelTemplateData* p,const wchar_t* file) {
    if(!armed)return;
    ++levelLoads;number(10);number(file!=NULL);if(file)text(file);
    number(dungeon->m_levelTemplateData.size());
    // The owner is a native C1 object; only its synchronous file dependency is supplied.
    baseLevel(p,created.size());created.push_back(p);watch(p);
}
static float floatValue(CDataGroup* group,const std::wstring& name,float fallback) {
    number(20);text(name);real(fallback);++floatLoads;
    for(unsigned i=0;i<dungeon->m_levelTemplateData.size();++i)number(levelID(dungeon->m_levelTemplateData[i]));
    floatPatch->restore();
    float result=reinterpret_cast<float(*)(CDataGroup*,const std::wstring&,float)>(drFloat_original)(group,name,fallback);
    if(observeFloats&&floatLoads==1&&current->seed%7==0){
        unsigned depth=(current->seed/4)%3;
        if(depth<dungeon->m_levelTemplateData.size())dungeon->m_levelTemplateData[depth]=alternate;
    }
    TL_REDIRECT(*floatPatch,drFloat,&floatValue);valid(!floatPatch->failed(),1);return result;
}
static void fillStrata(CDataGroup& data,unsigned seed) {
    if(seed%3!=0)data.AddDataValue(L"RULESET",seed%3==1?L"":L"synthetic/rules \u03a9.dat",false);
    if(seed%4!=0)data.AddDataValue(L"ALLOW_PORTALS",(seed/4)%2!=0);
    if(seed%5!=0)data.AddDataValue(L"ALLOW_PET_RETURN",(seed/5)%2!=0);
    if(seed%6!=0)data.AddDataValue(L"IS_TOWN",(seed/6)%2!=0);
    if(seed%3!=0)data.AddDataValue(L"DUNGEON",seed%2?L"other dungeon":L"",false);
    const int bounds[]={-5,0,1,27};
    if(seed%5!=0)data.AddDataValue(L"MONSTER_LVL_MIN",bounds[(seed/2)%4]);
    if(seed%7!=0)data.AddDataValue(L"MONSTER_LVL_MAX",bounds[(seed/8)%4]);
    if(seed%4!=0)data.AddDataValue(L"NO_RANDOM_QUESTS",(seed/3)%2!=0);
    if(seed%4!=0)data.AddDataValue(L"DONTSTORE",(seed/7)%2!=0);
    if(seed%3!=0)data.AddDataValue(L"CINEMATIC",seed%2?L"cinema \u0416":L"",false);
    if(seed%5!=0)data.AddDataValue(L"NAME_OVERRIDE",seed%2?L"override name":L"",false);
    const unsigned floats[]={0x00000000,0x80000000,0x3f400000,0xc1200000,0x7f800000,0xff800000,0x7fc12345};
    for(unsigned i=0;i<11;++i){
        if((seed+i)%3!=0)data.AddDataValue(g_LEVELLAYOUT_CREATION_NAMES[i],i%2?L"spawner/\u03a9":L"",false);
        if((seed+i)%4!=0)data.AddDataValue(g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES[i],(seed+i)%2!=0);
        for(unsigned j=0;j<2;++j){float v;unsigned bits=floats[(seed+i+j)%7];std::memcpy(&v,&bits,4);
            if((seed+i+j)%3!=0)data.SetDataValue(g_LEVELLAYOUT_CREATION_PATHNODES[2*i+j],v);
            if((seed+i+j)%4!=0)data.SetDataValue(g_LEVELLAYOUT_CREATION_COUNTS[2*i+j],v);}
    }
}
static void snapshotLevel(CLevelTemplateData& p) {
    text(p.m_levelName);text(p.m_string60);text(p.m_cinematic);number(p.m_monsterLevelMin);number(p.m_monsterLevelMax);
    number(p.m_questSelectionExcluded);number(p.m_dontStore);number(p.m_permitsPortal);number(p.m_permitsPetDeparture);number(p.m_isTown);
    for(unsigned i=0;i<11;++i){text(p.m_unitSpawnerNames[i]);text(p.m_selectedUnitSpawners[i]);number(p.m_useSpawnClass[i]);real(p.m_densityRanges[i].minimum);real(p.m_densityRanges[i].maximum);real(p.m_countRanges[i].minimum);real(p.m_countRanges[i].maximum);}
}
static CDungeon* nativeDungeon() {
    nativeStrings();CDungeon* p=static_cast<CDungeon*>(Ogre::NedAllocImpl::allocBytes(sizeof(CDungeon),0,0,0));drCtor(p);watch(p);return p;
}
static void clearState(const Case& c,autotest::Capture& out) {
    current=&c;output=&out;errors=levelLoads=groupLoads=floatLoads=0;armed=false;observeFloats=false;alternate=NULL;created.clear();witnesses.clear();
}
static void cleanup() {
    // The callback may replace a cache slot. Track and destroy the displaced real owner.
    for(unsigned i=0;i<created.size();++i)if(dungeon->m_levelTemplateData.find(created[i])<0){drTemplateDtor(created[i]);Ogre::NedAllocImpl::deallocBytes(created[i]);}
    drDtor(dungeon);Ogre::NedAllocImpl::deallocBytes(dungeon);
    for(unsigned i=0;i<witnesses.size();++i){number(witnesses[i]->getObject()==NULL);valid(witnesses[i]->getObject()==NULL,2);delete witnesses[i];}
    witnesses.clear();number(0x44554e47);number(errors);
}
static void getSide(void* raw,autotest::Capture& out,bool ours) {
    const Case& c=*static_cast<Case*>(raw);clearState(c,out);dungeon=nativeDungeon();
    detour::Set loads;TL_REDIRECT(loads,drTemplateLoad,&levelLoad);valid(!loads.failed(),3);
    dungeon->m_pDungeonData=new CDataGroup(L"DUNGEON",NULL,20,10,NULL);watch(dungeon->m_pDungeonData);
    unsigned count=c.seed%4;
    for(unsigned i=0;i<count;++i){CDataGroup* data=dungeon->m_pDungeonData->AddDataGroup(L"STRATA"+STRINGS::GetValueAsWString(i));fillStrata(*data,c.seed+i);watch(data);dungeon->m_strataData.add(data);dungeon->m_levelTemplateData.add(NULL);}
    unsigned depth=(c.seed/4)%6;if(depth==5)depth=UINT_MAX;
    if(count&&c.seed%5==0)dungeon->m_levelTemplateData[depth<count?depth:0]=nativeLevel();
    alternate=nativeLevel();
    detour::Set floats;floatPatch=&floats;observeFloats=c.nativeData;
    if(observeFloats)TL_REDIRECT(floats,drFloat,&floatValue);valid(!floats.failed(),4);
    typedef CLevelTemplateData*(*Function)(CDungeon*,unsigned);Function fn=ours?drGetNew:drGetOld;
    armed=true;feclearexcept(FE_ALL_EXCEPT);
    CLevelTemplateData* result=NULL;
    if(autotest::beginInvocation(out,fn)){result=fn(dungeon,depth);out.callCompleted=1;}
    int exceptions=fetestexcept(FE_ALL_EXCEPT);armed=false;
    if(ours&&c.negative)result=alternate;
    number(levelID(result));number(levelLoads);number(floatLoads);number(exceptions);shape(dungeon->m_levelTemplateData);shape(dungeon->m_strataData);
    for(unsigned i=0;i<dungeon->m_levelTemplateData.size();++i)number(levelID(dungeon->m_levelTemplateData[i]));
    for(unsigned i=0;i<created.size();++i)snapshotLevel(*created[i]);
    if(!c.negative){valid(depth<count?result!=NULL:result==NULL,5);valid(levelLoads<=1,6);if(observeFloats&&levelLoads)valid(floatLoads==44,7);}
    floats.restore();loads.restore();cleanup();
}
static void getOld(void* p,autotest::Capture& o){getSide(p,o,false);}static void getNew(void* p,autotest::Capture& o){getSide(p,o,true);}

static void fillDungeon(CDataGroup& data,unsigned seed) {
    data.SetGroupName(seed%19==0?L"":L"DUNGEON");
    if(seed%3!=0)data.AddDataValue(L"NAME",L"mixed \u03a9 dungeon",false);
    if(seed%4!=0)data.AddDataValue(L"DISPLAYNAME",L"display \u0416",false);
    if(seed%5!=0)data.AddDataValue(L"PARENT_DUNGEON",seed%2?L"parent":L"",false);
    if(seed%3!=0)data.AddDataValue(L"VOLATILE",(seed/3)%2!=0);
    if(seed%4!=0)data.AddDataValue(L"MONSTER_LVL_MULT",float(int(seed%9)-4)*0.25f);
    if(seed%5!=0)data.AddDataValue(L"PLAYER_LVL_MATCH_MIN",int(seed%7)-3);
    if(seed%6!=0)data.AddDataValue(L"PLAYER_LVL_MATCH_MAX",int(seed%11)-2);
    if(seed%7!=0)data.AddDataValue(L"PLAYER_LVL_MATCH_OFFSET",int(seed%13)-6);
    if(seed%4!=0)data.AddDataValue(L"BOTTOMLESS",(seed/2)%2!=0);
    unsigned strata=seed%5;
    for(unsigned i=0;i<strata;++i){unsigned id=(seed%13==0&&i==1)?3:i;CDataGroup* s=data.AddDataGroup(L"STRATA"+STRINGS::GetValueAsWString(id));
        const int floors[]={-3,0,1,2,13};if((seed+i)%4)s->AddDataValue(L"FLOORS",floors[(seed/5+i)%5]);
        const int weights[]={-5,0,1,77};if((seed+i)%3)s->AddDataValue(L"WEIGHT",weights[(seed/7+i)%4]);
        for(unsigned k=0;k<2;++k){if((seed+i+k)%3==0)continue;CDataGroup* req=s->AddDataGroup(k?L"MUST_BE_COMPLETED_OR_ACTIVE":L"MUST_BE_COMPLETED");
            unsigned count=(seed/3+i+k)%5;for(unsigned j=0;j<count;++j){std::wstring key=L"ENTRY"+STRINGS::GetValueAsWString(j);
                if(j%3==0)req->AddDataValue(key,L"required \u03a9",false);
                else if(j%3==1)req->AddDataValue(key,L"translated requirement",true);
                else req->AddDataValue(key,int(j*17));}}
    }
}
static void groupLoad(CDataGroup* data,const std::wstring& file,CTimerStatics* timers) {
    ++groupLoads;number(30);text(file);number(timers!=NULL);text(data->GetGroupName());shape(data->m_DataValues);shape(data->m_DataGroups);
    valid(data==dungeon->m_pDungeonData&&!timers&&data->GetGroupName().empty(),8);fillDungeon(*data,current->seed);
}
static void stringLists(const TArrayList<TArrayList<std::wstring>*>& lists) {
    shape(lists);for(unsigned i=0;i<lists.size();++i){number(lists[i]!=NULL);if(lists[i]){shape(*lists[i]);for(unsigned j=0;j<lists[i]->size();++j)text((*lists[i])[j]);}}
}
static void snapshotDungeon(const std::vector<CDataGroup*>& old) {
    text(dungeon->m_sName);text(dungeon->m_sDisplayName);text(dungeon->m_sParentDungeon);real(dungeon->m_fMonsterLevelMultiplier);
    number(dungeon->m_iPlayerLevelMatchMin);number(dungeon->m_iPlayerLevelMatchMax);number(dungeon->m_iPlayerLevelMatchOffset);number(dungeon->m_iDungeonIndex);number(dungeon->m_bVolatile);number(dungeon->m_bBottomless);
    shape(dungeon->m_levelTemplateData);for(unsigned i=0;i<dungeon->m_levelTemplateData.size();++i)number(levelID(dungeon->m_levelTemplateData[i]));
    shape(dungeon->m_strataData);for(unsigned i=0;i<dungeon->m_strataData.size();++i){CDataGroup* p=dungeon->m_strataData[i];int id=-1;for(unsigned j=0;j<old.size();++j)if(old[j]==p)id=1000+j;
        for(unsigned j=0;j<dungeon->m_pDungeonData->m_DataGroups.size();++j)if(dungeon->m_pDungeonData->m_DataGroups[j]==p)id=j;number(id);}
    stringLists(dungeon->m_mustBeCompleted);stringLists(dungeon->m_mustBeCompletedOrActive);randomizer(dungeon->m_randomizer);
    text(dungeon->m_pDungeonData->GetGroupName());number(dungeon->m_pDungeonData->GetNumberOfDataGroups());number(dungeon->m_pDungeonData->getRepository()!=CDataGroup::stringRepository());
}
static void loadSide(void* raw,autotest::Capture& out,bool ours) {
    const Case& c=*static_cast<Case*>(raw);clearState(c,out);dungeon=nativeDungeon();
    dungeon->m_sName=L"old name";dungeon->m_sDisplayName=L"old display";dungeon->m_sParentDungeon=L"old parent";
    dungeon->m_fMonsterLevelMultiplier=-3.25f;dungeon->m_iPlayerLevelMatchMin=11;dungeon->m_iPlayerLevelMatchMax=22;dungeon->m_iPlayerLevelMatchOffset=-7;dungeon->m_bVolatile=false;dungeon->m_bBottomless=true;
    std::vector<CDataGroup*> old;
    TSafePointer<CDataGroup> previous;
    if(c.seed%2){dungeon->m_pDungeonData=new CDataGroup(L"PREVIOUS",NULL,20,10,NULL);previous.setObject(dungeon->m_pDungeonData);
        CDataGroup* s=dungeon->m_pDungeonData->AddDataGroup(L"PREVIOUSSTRATA");old.push_back(s);dungeon->m_strataData.add(s);dungeon->m_levelTemplateData.add(nativeLevel());
        TArrayList<std::wstring>* req=new TArrayList<std::wstring>(1);req->add(L"old completion");dungeon->m_mustBeCompleted.add(req);dungeon->m_mustBeCompletedOrActive.add(NULL);dungeon->m_randomizer.addChoice(123,17);}
    std::string path=temporary+"/dungeon.dat";std::wstring file(path.begin(),path.end());
    bool missing=c.seed%17==0;
    if(c.nativeData&&!missing){CDataGroup source(L"DUNGEON",NULL,20,10,NULL);fillDungeon(source,c.seed);valid(source.SaveToFile(file)!=0,9);}
    detour::Set io;if(!c.nativeData)TL_REDIRECT(io,drGroupLoad,&groupLoad);valid(!io.failed(),10);
    typedef bool(*Function)(CDungeon*,const wchar_t*);Function fn=ours?drLoadNew:drLoadOld;
    bool result=false;armed=true;
    if(autotest::beginInvocation(out,fn)){result=fn(dungeon,file.c_str());out.callCompleted=1;}armed=false;
    if(ours&&c.negative)result=!result;
    number(result);number(groupLoads);number(previous.getObject()==NULL);valid(previous.getObject()==NULL,11);snapshotDungeon(old);
    watch(dungeon->m_pDungeonData);for(unsigned i=0;i<dungeon->m_pDungeonData->m_DataGroups.size();++i)watch(dungeon->m_pDungeonData->m_DataGroups[i]);
    io.restore();cleanup();if(c.nativeData){unlink(path.c_str());unlink((temporary+"/dungeon.adm").c_str());unlink((temporary+"/dungeon.cmp").c_str());}
}
static void loadOld(void* p,autotest::Capture& o){loadSide(p,o,false);}static void loadNew(void* p,autotest::Capture& o){loadSide(p,o,true);}
static bool complete(const autotest::Outcome& o) { return o.reportValid&&!o.childStatus&&!o.capture.issue&&!autotest::incomplete(o); }
static bool good(const autotest::Outcome& o) { unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return complete(o)&&tail[0]==0x44554e47&&!tail[1]; }
static unsigned selection;
static int worker(const tlhybrid_host* host) {
    nativegame::Services services;if(!services.ready())return 1;char path[]="/tmp/otl-dungeon-proof-XXXXXX";if(!mkdtemp(path))return 1;temporary=path;
    bool get=selection<2;bool native=selection%2;const char* labels[]={"dungeon_strata_native_data","dungeon_strata_callbacks","dungeon_load_observed","dungeon_load_native_files"};
    unsigned count=get?256:native?192:128;autotest::Coverage coverage(labels[selection],get?0x9337f0:0x934720);
    for(unsigned seed=0;seed<count;++seed){Case c={seed,native,false};autotest::Outcome a,b;autotest::runChild(get?getOld:loadOld,&c,a,10000,20000);autotest::runChild(get?getNew:loadNew,&c,b,10000,20000);
        bool different=coverage.observe(host,a,b)!=0;if(different||!good(a)||!good(b)){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;
            host->log("    dungeon %s seed%u valid%u/%u status%d/%d issue%u/%u completed%u/%u bytes%lu/%lu first%lu\n",labels[selection],seed,a.reportValid,b.reportValid,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at);
            for(unsigned side=0;side<2;++side){const autotest::Capture& z=side?b.capture:a.capture;for(size_t i=0;i+4<=z.length;i+=4){unsigned value;std::memcpy(&value,z.data+i,4);if((value&0xffff0000u)==0xd7000000u)host->log("    dungeon side%u error%u at%lu\n",side,value-0xd7000000u,(unsigned long)i);}}
            coverage.report(host);return 1;}}
    coverage.report(host);Case negative={get?2u:23u,native,true};autotest::Outcome a,b;autotest::runChild(get?getOld:loadOld,&negative,a,10000,20000);autotest::runChild(get?getNew:loadNew,&negative,b,10000,20000);
    bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);bool completed=good(a)&&good(b);
    host->log("    %s negative detected%u completed%u\n",labels[selection],unsigned(detected),unsigned(completed));rmdir(temporary.c_str());return coverage.completed!=count||!detected||!completed;
}
}
TL_TEST(dungeon_strata_native_data){dungeon_recovery::selection=0;return systems_fixture::isolated(dungeon_recovery::worker,host,300);}
TL_TEST(dungeon_strata_callbacks){dungeon_recovery::selection=1;return systems_fixture::isolated(dungeon_recovery::worker,host,300);}
TL_TEST(dungeon_load_observed){dungeon_recovery::selection=2;return systems_fixture::isolated(dungeon_recovery::worker,host,300);}
TL_TEST(dungeon_load_native_files){dungeon_recovery::selection=3;return systems_fixture::isolated(dungeon_recovery::worker,host,300);}
