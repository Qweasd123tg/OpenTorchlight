#include <Ogre.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <sys/stat.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/SystemsFixtureWorker.h"
#define private public
#define protected public
#include "SharedStash.h"
#include "Inventory.h"
#include "Equipment.h"
#include "ItemSaveState.h"
#include "Player.h"
#undef protected
#undef private
#include "tests/NativeGameServices.h"
#include "tests/ParticleNativeOwners.h"

TL_ORIGINAL(void, persistenceStashCtor, (CSharedStash*,const wchar_t*,const wchar_t*), "_ZN12CSharedStashC1EPKwS1_")
TL_ORIGINAL(void, persistenceStashDtor, (CSharedStash*), "_ZN12CSharedStashD1Ev")
TL_ORIGINAL(void, persistenceLoadOriginal, (CSharedStash*,CResourceManager*,CCharacter*), "_ZN12CSharedStash15loadSharedStashEP16CResourceManagerP10CCharacter")
extern "C" void persistenceLoadCandidate(CSharedStash*,CResourceManager*,CCharacter*) __asm__("_ZN12CSharedStash15loadSharedStashEP16CResourceManagerP10CCharacter");
TL_ORIGINAL(void, persistenceSaveOriginal, (CSharedStash*), "_ZN12CSharedStash15saveSharedStashEv")
extern "C" void persistenceSaveCandidate(CSharedStash*) __asm__("_ZN12CSharedStash15saveSharedStashEv");
TL_ORIGINAL(void, persistenceItemSave, (CItemSaveState*,FILE*), "_ZN14CItemSaveState4saveEP8_IO_FILE")
TL_FUNCTION(persistenceDirectory, "_ZN10FILESYSTEM15GetSaveDataPathEv")
TL_FUNCTION(persistenceFactory, "_ZN16CResourceManager10createUnitExibb")
TL_FUNCTION(persistencePickup, "_ZN10CInventory15pickupEquipmentEP10CEquipmentib")
extern "C" void* persistenceSingleton __asm__("_ZL14g_pSharedStash");

namespace {
struct Case { unsigned seed; bool save,negative; };
ParticleNativeOwners owners; CPlayer* players[2]; CCharacter* character;
std::string base,directory; std::wstring wideDirectory;
autotest::Capture* output; const Case* current; bool recording;
unsigned directoryCalls,createdCount,stateCount;
TSafePointer<CRunicCore> created[64],states[64];
void number(long long value) { output->add(&value,sizeof(value)); }
void event(unsigned tag) { if(recording)number(tag); }
std::wstring saveDirectory() { ++directoryCalls;event(1);return wideDirectory; }

void fill(CItemSaveState& state,unsigned seed,int slot,bool flag,bool children)
{
    std::memset(reinterpret_cast<char*>(&state)+0x28,0,0xb8);
    state.m_sItemName=seed%3==0?L"":seed%3==1?L"saved-item":L"saved-Ж中";
    state.m_sStateString18=seed%2?L"prefix":L"";state.m_sStateString20=seed%2?L"":L"suffix";
    state.m_iStateValue28=seed*13;state.m_iOriginalGuid=0x1234567800000000LL+seed;
    state.m_iStateValue38=-17;state.m_iParentHierarchyHash=0x1122334400000000LL+seed;
    state.m_iSpawnerGuid=0xffffffffLL;state.m_iIndex=slot;state.m_bSaveFlag5C=flag;
    state.m_bEnabled=seed%2;state.m_bBlocksPath=seed%3==0;
    state.m_iUnitValue60=seed%4==0?-1:1000+seed;state.m_iStackSize=1+seed%7;
    state.m_iStateValue6C=-11;state.m_iBaseDamage=13+seed;state.m_iBaseArmor=-1;state.m_iRoomIndex=0;
    state.m_bIdentified=seed%2;state.m_StateByte74=seed%5;
    state.m_vLocalPosition=Ogre::Vector3(float(seed),-0.5f,2.25f);
    state.m_vWorldPosition=Ogre::Vector3(-float(seed),7.5f,-1.25f);state.m_mOrientation=Ogre::Matrix4::IDENTITY;
    state.m_iQuestGuid=0x9876543210000000ULL+seed;state.m_iQuestState=seed%3;state.m_bItemFlag17C=seed%2;
    if(children&&seed%3==1){
        CItemSaveState* child=new CItemSaveState;fill(*child,seed+7,-1,false,false);
        state.m_SocketedItems.push_back(child);state.m_iSocketCount=1;
    }
    if(seed%2){state.m_DamageTypes.push_back(static_cast<EDAMAGE_TYPES>(0));state.m_DamageBonuses.push_back(17);}
}
void stateView(const CItemSaveState& state)
{
    output->addText(state.m_sItemName);output->addText(state.m_sStateString18);output->addText(state.m_sStateString20);
    number(state.m_iUnitValue60);number(state.m_iIndex);number(state.m_iStackSize);number(state.m_bSaveFlag5C);
    number(state.m_iOriginalGuid);number(state.m_iParentHierarchyHash);number(state.m_SocketedItems.size());
    number(state.m_DamageTypes.size());number(state.m_DamageBonuses.size());
}
class Equipment:public CEquipment {
public:
    unsigned identity;
    Equipment(unsigned id):CEquipment(owners.resources),identity(id){}
    virtual ~Equipment(){if(recording){event(6);number(identity);}}
    virtual void fillSaveState(CItemSaveState& state,int slot,bool flag){
        event(3);number(identity);number(slot);number(flag);
        if(stateCount>=64){output->issue=autotest::Capture::InvalidReport;return;}
        states[stateCount++].setObject(&state);
        fill(state,identity,slot,flag,true);
    }
    virtual void applySaveState(CItemSaveState& state){
        event(4);number(identity);stateView(state);
        if(stateCount>=64){output->issue=autotest::Capture::InvalidReport;return;}
        states[stateCount++].setObject(&state);
        m_sItemName=state.m_sItemName;m_iUnknown238=state.m_iStackSize;m_iUnitValue1A0=state.m_iUnitValue60;
        // The stash must retain the slot captured before this virtual call.
        if(current->seed%3==1)state.m_iIndex+=71;
    }
};
CBaseUnit* factory(CResourceManager* resources,long long guid,int level,bool first,bool second)
{
    event(2);number(guid);number(level);number(first);number(second);
    if(resources!=owners.resources||level!=1||!first||second||guid<1000)output->issue=autotest::Capture::InvalidReport;
    unsigned identity=static_cast<unsigned>(guid-1000);
    if((identity+current->seed)%5==2)return NULL;
    Equipment* equipment=new Equipment(identity);
    if(createdCount>=64){output->issue=autotest::Capture::InvalidReport;return equipment;}
    created[createdCount++].setObject(equipment);return equipment;
}
CEquipment* pickup(CInventory* inventory,CEquipment* equipment,int slot,bool flag)
{
    Equipment* item=dynamic_cast<Equipment*>(equipment);
    event(5);number(item?item->identity:999);number(slot);number(flag);
    if(!item||!flag){output->issue=autotest::Capture::InvalidReport;return NULL;}
    if((item->identity+current->seed)%3==0)return NULL;
    CEquipmentRef* reference=new CEquipmentRef;
    reference->m_pEquipment=equipment;reference->m_iSlot=slot;reference->m_originalSlot=-1;
    reference->m_flag20=false;reference->m_effectsEnabled=false;
    inventory->m_equipmentRefs.add(reference);return equipment;
}
void cleanupFiles()
{
    unlink((directory+"stash-normal.bin").c_str());unlink((directory+"stash-alt.bin").c_str());
    rmdir((directory+"missing").c_str());rmdir(directory.c_str());
}
void fileView(const char* name)
{
    FILE* file=fopen((directory+name).c_str(),"rb");number(file!=NULL);if(!file)return;
    unsigned char bytes[8192];size_t count=fread(bytes,1,sizeof(bytes),file);
    if(!feof(file))output->issue=autotest::Capture::Overflow;
    number(count);output->add(bytes,count);fclose(file);
}
void side(void* raw,autotest::Capture& out,bool ours)
{
    Case c=*static_cast<Case*>(raw);current=&c;output=&out;recording=false;directoryCalls=createdCount=stateCount=0;
    for(unsigned i=0;i<64;++i){created[i].setObject(NULL);states[i].setObject(NULL);}
    cleanupFiles();bool directoryBefore=c.seed%3!=0;
    if(directoryBefore&&mkdir(directory.c_str(),0700)&&errno!=EEXIST)_exit(41);
    const wchar_t* normal=c.seed%11==3?L"missing/normal.bin":L"stash-normal.bin";
    const wchar_t* alternate=c.seed%13==4?L"missing/alt.bin":L"stash-alt.bin";
    union Storage{long double align;char bytes[sizeof(CSharedStash)];} storage;
    CSharedStash* stash=reinterpret_cast<CSharedStash*>(storage.bytes);persistenceSingleton=NULL;
    persistenceStashCtor(stash,normal,alternate);stash->m_bUseAlternateStash=bool(c.seed&1);
    players[0]->m_saveOnDeath=players[1]->m_saveOnDeath=stash->m_bUseAlternateStash;
    CCharacter* actors[]={NULL,players[0],players[1],character};
    CCharacter* argument=actors[c.seed%4];CInventory* initial=stash->m_pInventory;
    initial->m_pPositionableObject=actors[(c.seed/4)%4];
    TSafePointer<CRunicCore> initialLife;initialLife.setObject(initial);
    unsigned existing=c.save?c.seed/4%7:(c.seed%7==0?1:0);
    for(unsigned i=0;i<existing;++i){
        Equipment* equipment=new Equipment(c.seed+i+1);created[createdCount++].setObject(equipment);
        CEquipmentRef* reference=new CEquipmentRef;reference->m_pEquipment=equipment;
        reference->m_iSlot=int(i*3)-2;reference->m_originalSlot=77+i;reference->m_flag20=bool((c.seed+i)&1);reference->m_effectsEnabled=false;
        initial->m_equipmentRefs.add(reference);
    }
    if(c.seed%9==1){delete stash->m_pInventory;stash->m_pInventory=NULL;}
    if(!c.save&&c.seed%5!=0){
        if(!directoryBefore&&mkdir(directory.c_str(),0700)&&errno!=EEXIST)_exit(42);
        const char* name=stash->m_bUseAlternateStash?"stash-alt.bin":"stash-normal.bin";
        FILE* file=fopen((directory+name).c_str(),"wb");if(!file)_exit(43);
        unsigned version=c.seed%17==0?0:23,count=c.seed%17==0?0:c.seed/7%7;
        fwrite(&version,4,1,file);
        if(c.seed%19!=0)fwrite(&count,4,1,file);
        if(c.seed%19!=0)for(unsigned i=0;i<count;++i){CItemSaveState state;fill(state,c.seed+i,int(i*5)-3,bool(i&1),true);persistenceItemSave(&state,file);}
        fclose(file);
    }
    detour::Set hooks;TL_REDIRECT(hooks,persistenceDirectory,&saveDirectory);
    TL_REDIRECT(hooks,persistenceFactory,&factory);TL_REDIRECT(hooks,persistencePickup,&pickup);
    if(hooks.failed()){out.issue=autotest::Capture::InvalidReport;return;}
    int before=g_iTotalCountOfObjects;recording=true;
    if(c.save){autotest::invoke(out,ours?persistenceSaveCandidate:persistenceSaveOriginal,stash);}
    else{autotest::invoke(out,ours?persistenceLoadCandidate:persistenceLoadOriginal,stash,owners.resources,argument);}
    if(ours&&c.negative)stash->m_bUseAlternateStash=!stash->m_bUseAlternateStash;
    number(directoryCalls);number(stash->m_bUseAlternateStash);out.addText(stash->m_stashFileName);out.addText(stash->m_alternateStashFileName);
    number(initialLife.getObject()!=NULL);number(stash->m_pInventory!=NULL);number(g_iTotalCountOfObjects-before);
    if(stash->m_pInventory){
        CInventory* inventory=stash->m_pInventory;unsigned owner=9;
        for(unsigned i=0;i<4;++i)if(inventory->m_pPositionableObject==actors[i])owner=i;
        number(owner);number(inventory->m_equipmentRefs.size());
        for(unsigned i=0;i<inventory->m_equipmentRefs.size();++i){
            CEquipmentRef* reference=inventory->m_equipmentRefs[i];Equipment* equipment=dynamic_cast<Equipment*>(reference->m_pEquipment);
            number(equipment?equipment->identity:999);number(reference->m_iSlot);number(reference->m_flag20);
            if(equipment){out.addText(equipment->m_sItemName);number(equipment->m_iUnknown238);number(equipment->getParentGuid());number(equipment->getResourceManager()==owners.resources);}
        }
    }
    for(unsigned i=0;i<stateCount;++i)number(states[i].getObject()==NULL);
    for(unsigned i=0;i<createdCount;++i)number(created[i].getObject()!=NULL);
    struct stat info;number(stat(directory.c_str(),&info)==0);
    fileView("stash-normal.bin");fileView("stash-alt.bin");
    persistenceStashDtor(stash);
    for(unsigned i=0;i<createdCount;++i)number(created[i].getObject()==NULL);
    recording=false;cleanupFiles();
}
void original(void* p,autotest::Capture& out){side(p,out,false);}
void candidate(void* p,autotest::Capture& out){side(p,out,true);}
int worker(const tlhybrid_host* host,bool save)
{
    owners=particleNativeOwners(0);players[0]=nativegame::createPlayer(owners.resources);players[1]=nativegame::createPlayer(owners.resources);
    players[0]->setGuid(1234567);players[1]->setGuid(9876543);character=new CCharacter(owners.resources);
    char temporary[]="/tmp/otl-stash-recovery-XXXXXX";if(!mkdtemp(temporary))return 1;
    base=temporary;directory=base+"/case/";wideDirectory=std::wstring(directory.begin(),directory.end());
    LinuxUtils::gameHomePath=std::wstring(base.begin(),base.end())+L"/";
    const char* label=save?"shared_stash_save_recovery":"shared_stash_load_recovery";
    autotest::Coverage coverage(label,save?0xe16990:0xe16430);
    unsigned count=save?128:192;
    for(unsigned i=0;i<count;++i){
        Case c={i,save,false};autotest::Outcome a,b;
        autotest::runChild(original,&c,a,2000,10000);autotest::runChild(candidate,&c,b,2000,10000);
        if(coverage.observe(host,a,b)){
            size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;
            host->log("    stash persistence save%u seed%u status%d/%d issue%u/%u bytes%lu/%lu first%lu\n",save,i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at);
            coverage.report(host);return 1;
        }
    }
    coverage.report(host);Case c={37,save,true};autotest::Outcome a,b;
    autotest::runChild(original,&c,a,2000,10000);autotest::runChild(candidate,&c,b,2000,10000);
    bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);
    host->log("    stash persistence negative save%u detected%u\n",save,detected?1:0);
    cleanupFiles();rmdir(base.c_str());
    return !detected||!a.reportValid||!b.reportValid||a.childStatus||b.childStatus||autotest::incomplete(a)||autotest::incomplete(b);
}
int loadWorker(const tlhybrid_host* host){return worker(host,false);}
int saveWorker(const tlhybrid_host* host){return worker(host,true);}
}
TL_TEST(shared_stash_load_recovery){return systems_fixture::isolated(loadWorker,host);}
TL_TEST(shared_stash_save_recovery){return systems_fixture::isolated(saveWorker,host);}
