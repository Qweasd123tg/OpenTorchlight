#include <cstring>
#include <vector>
#include <string>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "tests/NativeGameServices.h"
#include "tests/SystemsFixtureWorker.h"
#include "SpawnClassParser.h"
#include "SpawnClassData.h"
#include "SpawnClass.h"
#include "FileSystem.h"
#include "MasterResourceManager.h"
#include "UnitResourceList.h"
#include "StringUtilities.h"
#include <OgreUTFString.h>

TL_ORIGINAL(void, prCtor, (CSpawnClassParser*), "_ZN17CSpawnClassParserC1Ev")
TL_ORIGINAL(void, prDtor, (CSpawnClassParser*), "_ZN17CSpawnClassParserD1Ev")
TL_ORIGINAL(CSpawnClassData*, prTypeOld, (CSpawnClassParser*,const std::wstring&,CDataGroup*), "_ZN17CSpawnClassParser30createSpawnClassDataByUnitTypeERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup")
extern "C" CSpawnClassData* prTypeNew(CSpawnClassParser*,const std::wstring&,CDataGroup*) __asm__("_ZN17CSpawnClassParser30createSpawnClassDataByUnitTypeERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup");
TL_ORIGINAL(bool, prReloadOld, (CSpawnClassParser*,const wchar_t*), "_ZN17CSpawnClassParser19reloadFromDirectoryEPKw")
extern "C" bool prReloadNew(CSpawnClassParser*,const wchar_t*) __asm__("_ZN17CSpawnClassParser19reloadFromDirectoryEPKw");
TL_ORIGINAL(void, prDataCtor, (CSpawnClassData*,const std::wstring&), "_ZN15CSpawnClassDataC1ERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void, prClassCtor, (CSpawnClass*,const wchar_t*), "_ZN11CSpawnClassC1EPKw")
TL_ORIGINAL(void, prGroupCtor, (CDataGroup*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*), "_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void, prGroupDtor, (CDataGroup*), "_ZN10CDataGroupD1Ev")
TL_ORIGINAL(void, prEmptyOld, (CSpawnClassParser*,CDataGroup*), "_ZN17CSpawnClassParser21createEmptySpawnClassEP10CDataGroup")
TL_ORIGINAL(void, prFillOld, (CSpawnClassParser*,CDataGroup*), "_ZN17CSpawnClassParser19fillEmptySpawnClassEP10CDataGroup")
TL_FUNCTION(prReload, "_ZN17CSpawnClassParser19reloadFromDirectoryEPKw")
TL_FUNCTION(prHierarchy, "_ZN10CHierarchy15getTypeIDByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(prUnits, "_ZN17CUnitResourceList23getDataGroupsByUnitTypeEjR10TArrayListIP10CDataGroupE")
TL_FUNCTION(prFiles, "_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(prLoad, "_ZN10CDataGroup8LoadFileERKSbIwSt11char_traitsIwESaIwEEP13CTimerStatics")
TL_FUNCTION(prEmpty, "_ZN17CSpawnClassParser21createEmptySpawnClassEP10CDataGroup")
TL_FUNCTION(prFill, "_ZN17CSpawnClassParser19fillEmptySpawnClassEP10CDataGroup")
extern "C" CSpawnClassParser* prSingleton __asm__("_ZL19m_gSpawnClassParser");

namespace {
struct Case { unsigned seed, negative; };
autotest::Capture* capture;
CSpawnClassParser* parser;
CHierarchy* hierarchy;
CUnitResourceList* unitResources;
CFileSystem* files;
CDataGroup* units[6];
TSafePointer<CSpawnClassData>* previousData;
TSafePointer<CSpawnClass>* previousClass;
const Case* current;
std::wstring requestedDirectory;
unsigned hierarchyCalls, unitCalls, loadCalls, emptyCalls, fillCalls;
unsigned selectedType, selectedUnits, selectedFiles, ctorSkips;
bool invoking,typeCapture;
std::vector<TSafePointer<CDataGroup>*> loadedWitnesses;
detour::Set* emptyHook;
detour::Set* fillHook;

// The actual game catalog exceeds Capture's 256 KiB wire buffer. Feed every
// serialized byte to SHA-256; retain the full byte count and digest, never a
// bounded prefix. Known-answer checks and a final-entry mutation test guard it.
struct CatalogSHA256 {
    uint32_t h[8];unsigned char block[64];unsigned used;uint64_t total;
    CatalogSHA256():used(0),total(0){
        const uint32_t initial[]={0x6a09e667u,0xbb67ae85u,0x3c6ef372u,0xa54ff53au,0x510e527fu,0x9b05688cu,0x1f83d9abu,0x5be0cd19u};
        std::memcpy(h,initial,sizeof h);
    }
    static uint32_t rotate(uint32_t value,unsigned n){return value>>n|value<<(32-n);}
    void transform(){
        static const uint32_t k[]={
            0x428a2f98u,0x71374491u,0xb5c0fbcfu,0xe9b5dba5u,0x3956c25bu,0x59f111f1u,0x923f82a4u,0xab1c5ed5u,
            0xd807aa98u,0x12835b01u,0x243185beu,0x550c7dc3u,0x72be5d74u,0x80deb1feu,0x9bdc06a7u,0xc19bf174u,
            0xe49b69c1u,0xefbe4786u,0x0fc19dc6u,0x240ca1ccu,0x2de92c6fu,0x4a7484aau,0x5cb0a9dcu,0x76f988dau,
            0x983e5152u,0xa831c66du,0xb00327c8u,0xbf597fc7u,0xc6e00bf3u,0xd5a79147u,0x06ca6351u,0x14292967u,
            0x27b70a85u,0x2e1b2138u,0x4d2c6dfcu,0x53380d13u,0x650a7354u,0x766a0abbu,0x81c2c92eu,0x92722c85u,
            0xa2bfe8a1u,0xa81a664bu,0xc24b8b70u,0xc76c51a3u,0xd192e819u,0xd6990624u,0xf40e3585u,0x106aa070u,
            0x19a4c116u,0x1e376c08u,0x2748774cu,0x34b0bcb5u,0x391c0cb3u,0x4ed8aa4au,0x5b9cca4fu,0x682e6ff3u,
            0x748f82eeu,0x78a5636fu,0x84c87814u,0x8cc70208u,0x90befffau,0xa4506cebu,0xbef9a3f7u,0xc67178f2u};
        uint32_t w[64];
        for(unsigned i=0;i<16;++i)w[i]=uint32_t(block[i*4])<<24|uint32_t(block[i*4+1])<<16|uint32_t(block[i*4+2])<<8|uint32_t(block[i*4+3]);
        for(unsigned i=16;i<64;++i){uint32_t a=w[i-15],b=w[i-2];w[i]=w[i-16]+(rotate(a,7)^rotate(a,18)^(a>>3))+w[i-7]+(rotate(b,17)^rotate(b,19)^(b>>10));}
        uint32_t a=h[0],b=h[1],c=h[2],d=h[3],e=h[4],f=h[5],g=h[6],z=h[7];
        for(unsigned i=0;i<64;++i){uint32_t t1=z+(rotate(e,6)^rotate(e,11)^rotate(e,25))+((e&f)^(~e&g))+k[i]+w[i];uint32_t t2=(rotate(a,2)^rotate(a,13)^rotate(a,22))+((a&b)^(a&c)^(b&c));z=g;g=f;f=e;e=d+t1;d=c;c=b;b=a;a=t1+t2;}
        h[0]+=a;h[1]+=b;h[2]+=c;h[3]+=d;h[4]+=e;h[5]+=f;h[6]+=g;h[7]+=z;
    }
    void add(const void* raw,size_t n){
        const unsigned char* p=static_cast<const unsigned char*>(raw);total+=n;
        while(n){size_t take=64-used;if(take>n)take=n;std::memcpy(block+used,p,take);used+=take;p+=take;n-=take;if(used==64){transform();used=0;}}
    }
    void finish(unsigned char result[32])const{
        CatalogSHA256 copy=*this;uint64_t bits=total*8;unsigned char marker=0x80,zero=0;copy.add(&marker,1);
        while(copy.used!=56)copy.add(&zero,1);
        unsigned char size[8];for(unsigned i=0;i<8;++i)size[7-i]=static_cast<unsigned char>(bits>>(i*8));copy.add(size,8);
        for(unsigned i=0;i<8;++i)for(unsigned j=0;j<4;++j)result[i*4+j]=static_cast<unsigned char>(copy.h[i]>>(24-j*8));
    }
};
CatalogSHA256* catalogDigest;
void bytes(const void* p,size_t n){if(catalogDigest)catalogDigest->add(p,n);else capture->add(p,n);}
void text(const std::wstring& value){size_t n=value.size();bytes(&n,sizeof n);bytes(value.data(),n*sizeof(wchar_t));}
void number(unsigned value) { bytes(&value,sizeof(value)); }
void integer(int value) { bytes(&value,sizeof(value)); }
void valid(bool condition) { if(!condition)capture->issue=autotest::Capture::InvalidReport; }
void event(unsigned value) { if(invoking)number(value); }

bool digestKnownAnswers(){
    const unsigned char empty[]={0xe3,0xb0,0xc4,0x42,0x98,0xfc,0x1c,0x14,0x9a,0xfb,0xf4,0xc8,0x99,0x6f,0xb9,0x24,0x27,0xae,0x41,0xe4,0x64,0x9b,0x93,0x4c,0xa4,0x95,0x99,0x1b,0x78,0x52,0xb8,0x55};
    const unsigned char abc[]={0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};
    const unsigned char longer[]={0x24,0x8d,0x6a,0x61,0xd2,0x06,0x38,0xb8,0xe5,0xc0,0x26,0x93,0x0c,0x3e,0x60,0x39,0xa3,0x3c,0xe4,0x59,0x64,0xff,0x21,0x67,0xf6,0xec,0xed,0xd4,0x19,0xdb,0x06,0xc1};
    unsigned char result[32];CatalogSHA256 digest;digest.finish(result);if(std::memcmp(result,empty,32))return false;
    digest.add("a",1);digest.add("bc",2);digest.finish(result);if(std::memcmp(result,abc,32))return false;
    CatalogSHA256 second;const char* message="abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    for(unsigned i=0;i<56;++i)second.add(message+i,1);second.finish(result);return std::memcmp(result,longer,32)==0;
}

bool skipInitialReload(CSpawnClassParser* owner,const wchar_t* directory)
{
    if(owner!=parser||std::wstring(directory)!=L"media/SpawnClasses/")std::abort();
    ++ctorSkips;
    return false;
}

struct Owner {
    CSpawnClassParser* previous;
    TSafePointer<CSpawnClassParser> witness;
    Owner():previous(prSingleton) {
        parser=static_cast<CSpawnClassParser*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSpawnClassParser),0,0,0));
        ctorSkips=0;
        {detour::Set constructor;TL_REDIRECT(constructor,prReload,&skipInitialReload);
         if(constructor.failed())std::abort();prCtor(parser);}
        if(ctorSkips!=1||!parser->m_spawnClasses.empty()||!parser->m_spawnClassData.empty())std::abort();
        witness.setObject(parser);
    }
    ~Owner(){prDtor(parser);Ogre::NedAllocImpl::deallocBytes(parser);if(witness.getObject())std::abort();prSingleton=previous;}
private:Owner(const Owner&);Owner&operator=(const Owner&);
};

CDataGroup* group(const std::wstring& name)
{
    CDataGroup* p=static_cast<CDataGroup*>(Ogre::NedAllocImpl::allocBytes(sizeof(CDataGroup),0,0,0));
    prGroupCtor(p,name,NULL,10,10,NULL);
    return p;
}
void destroyGroup(CDataGroup* p){prGroupDtor(p);Ogre::NedAllocImpl::deallocBytes(p);}
CSpawnClassData* data(const std::wstring& name)
{
    CSpawnClassData* p=static_cast<CSpawnClassData*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSpawnClassData),0,0,0));
    prDataCtor(p,name);return p;
}
CSpawnClass* spawn(const wchar_t* name)
{
    CSpawnClass* p=static_cast<CSpawnClass*>(Ogre::NedAllocImpl::allocBytes(sizeof(CSpawnClass),0,0,0));
    prClassCtor(p,name);return p;
}

void dumpData(CSpawnClassData* p)
{
    number(p!=NULL);if(!p)return;
    text(p->m_sName);
    integer(p->m_iMinimumLevel);integer(p->m_iLevelOffset);integer(p->m_iRarityOverride);integer(p->m_iFlags);
    number(p->m_bIsInitialized);number(p->m_lUnitDataObjects.size());
    for(unsigned i=0;i<p->m_lUnitDataObjects.size();++i){
        CDataGroup* entry=p->m_lUnitDataObjects[i];
        if(typeCapture){unsigned identity=entry?0xfffffffeu:0xffffffffu;for(unsigned j=0;j<6;++j)if(entry==units[j])identity=j;valid(identity!=0xfffffffeu);number(identity);}
        else bytes(&entry,sizeof(entry));
    }
    number(p->m_pRandomizer!=NULL);number(p->m_pType1Randomizer!=NULL);number(p->m_pType2Randomizer!=NULL);
    number(p->m_pMinimumLevelGraph!=NULL);number(p->m_pMaximumLevelGraph!=NULL);
    number(p->m_pSpawnClass!=NULL);if(p->m_pSpawnClass)text(p->m_pSpawnClass->m_name);
    number(p->m_lPrimaryRandomizerIDs.size());
    for(unsigned i=0;i<p->m_lPrimaryRandomizerIDs.size();++i)integer(p->m_lPrimaryRandomizerIDs[i]);
}
void dumpParser()
{
    number(parser->m_spawnClasses.size());number(parser->m_spawnClassData.size());
    for(std::map<std::wstring,CSpawnClass*>::iterator i=parser->m_spawnClasses.begin();i!=parser->m_spawnClasses.end();++i){
        text(i->first);number(i->second!=NULL);if(!i->second)continue;
        CSpawnClass* p=i->second;text(p->m_name);integer(p->m_iUnknown30);number(p->m_entries.size());
        for(unsigned j=0;j<p->m_entries.size();++j){
            SpawnClassEntry* entry=p->m_entries[j];number(entry!=NULL);if(!entry)continue;
            number(entry->data!=NULL);if(entry->data)integer(entry->data->m_odds);
            number(entry->spawnClassData!=NULL);if(entry->spawnClassData)text(entry->spawnClassData->m_sName);
        }
    }
    for(std::map<std::wstring,CSpawnClassData*>::iterator i=parser->m_spawnClassData.begin();i!=parser->m_spawnClassData.end();++i){
        text(i->first);dumpData(i->second);
    }
}

UNITTYPES::EUNITTYPES typeID(CHierarchy* owner,const std::wstring& name)
{
    valid(owner==hierarchy);++hierarchyCalls;event(11);text(name);
    return static_cast<UNITTYPES::EUNITTYPES>(selectedType);
}
unsigned byType(CUnitResourceList* owner,unsigned type,TArrayList<CDataGroup*>& result)
{
    valid(owner==unitResources&&type==selectedType);++unitCalls;event(13);number(type);number(result.size());
    for(unsigned i=0;i<selectedUnits;++i)result.add((i+current->seed)%5==0?NULL:units[(i+current->seed)%6]);
    return selectedUnits+123;
}
void preparePrevious(TSafePointer<CSpawnClassData>& oldData,TSafePointer<CSpawnClass>& oldClass)
{
    CSpawnClassData* d=data(L"PREVIOUS-DATA");d->m_iFlags=int(current->seed)*37-41;
    CSpawnClass* c=spawn(L"PREVIOUS-CLASS");c->m_iUnknown30=-57;
    parser->m_spawnClassData[d->m_sName]=d;parser->m_spawnClasses[c->m_name]=c;
    oldData.setObject(d);oldClass.setObject(c);previousData=&oldData;previousClass=&oldClass;
}

void typeSide(void* raw,autotest::Capture& out,bool ours)
{
    current=static_cast<Case*>(raw);capture=&out;catalogDigest=NULL;invoking=false;typeCapture=true;hierarchyCalls=unitCalls=0;
    const wchar_t* names[]={L"WEAPON",L"weapon",L"monster",L"",L"unknown-type",L"\u0416\u4e2d",L"supplementary-\U0001f63a",L"a-type-name-long-enough-to-allocate-a-different-string-representation"};
    std::wstring name=names[current->seed%8];
    const unsigned ids[]={static_cast<unsigned>(-1),22,0,27};selectedType=ids[current->seed/8%4];
    const unsigned counts[]={0,1,3,9};selectedUnits=counts[current->seed/32%4];
    unsigned cacheMode=current->seed/128%3;
    for(unsigned i=0;i<6;++i)units[i]=group(L"native-unit-"+std::wstring(1,wchar_t(L'A'+i)));
    CDataGroup* options=group(L"options");
    TSafePointer<CSpawnClassData> oldData,cachedWitness;TSafePointer<CSpawnClass> oldClass;
    int objects=g_iTotalCountOfObjects;
    {Owner owner;preparePrevious(oldData,oldClass);
     std::wstring key=STRINGS::StringUpper(std::wstring(Ogre::UTFString("UNITTYPE:")+Ogre::UTFString(name)));
     if(cacheMode==1){CSpawnClassData* cached=data(key);cached->m_iLevelOffset=-113;cached->m_bIsInitialized=current->seed&1;parser->m_spawnClassData[key]=cached;cachedWitness.setObject(cached);}
     if(cacheMode==2)parser->m_spawnClassData[key]=NULL;
     bool nullOptions=(current->seed&4)&&((cacheMode==1)||selectedType==static_cast<unsigned>(-1)||(selectedType!=22&&selectedUnits==0));
     CDataGroup* supplied=nullOptions?NULL:options;
     detour::Set collaborators;TL_REDIRECT(collaborators,prHierarchy,&typeID);TL_REDIRECT(collaborators,prUnits,&byType);
     if(collaborators.failed()){out.issue=autotest::Capture::InvalidReport;return;}
     CSpawnClassData*(*fn)(CSpawnClassParser*,const std::wstring&,CDataGroup*)=ours?prTypeNew:prTypeOld;
     invoking=true;
     if(autotest::beginInvocation(out,fn)){
         CSpawnClassData* first=fn(parser,name,supplied);dumpData(first);number(hierarchyCalls);number(unitCalls);
         std::map<std::wstring,CSpawnClassData*>::iterator mapped=parser->m_spawnClassData.find(key);
         number(mapped!=parser->m_spawnClassData.end());number(mapped!=parser->m_spawnClassData.end()&&mapped->second==first);
         number(cacheMode!=1||first==cachedWitness.getObject());number(cacheMode!=1||cachedWitness.getObject()!=NULL);
         CSpawnClassData* second=fn(parser,name,supplied);out.callCompleted=1;
         number(first==second);dumpData(second);number(hierarchyCalls);number(unitCalls);
         mapped=parser->m_spawnClassData.find(key);number(mapped!=parser->m_spawnClassData.end());number(mapped!=parser->m_spawnClassData.end()&&mapped->second==second);
         number(cacheMode!=1||second==cachedWitness.getObject());
     }
     invoking=false;
     if(ours&&current->negative)oldData.getObject()->m_iFlags^=1;
     number(oldData.getObject()!=NULL);number(oldClass.getObject()!=NULL);dumpParser();collaborators.restore();}
    number(oldData.getObject()==NULL);number(oldClass.getObject()==NULL);number(cachedWitness.getObject()==NULL);integer(g_iTotalCountOfObjects-objects);
    destroyGroup(options);for(unsigned i=0;i<6;++i)destroyGroup(units[i]);
}
void typeBefore(void* p,autotest::Capture& out){typeSide(p,out,false);}
void typeAfter(void* p,autotest::Capture& out){typeSide(p,out,true);}

std::wstring fileName(unsigned index)
{
    const wchar_t* names[]={L"first.dat",L"forward-\u0416.dat",L"third.dat",L"duplicate.dat",L"empty.dat",L"last.dat"};
    return requestedDirectory+names[index%6]+std::wstring(1,wchar_t(L'0'+index/6));
}
unsigned fileList(CFileSystem* owner,const std::wstring& directory,TArrayList<std::wstring>& list,std::wstring pattern,bool recursive,bool strip,bool modsOnly,bool skipMods)
{
    valid(owner==files&&directory==requestedDirectory&&pattern==L"*.dat"&&recursive&&strip&&!modsOnly&&!skipMods);
    event(21);text(directory);text(pattern);number(recursive);number(strip);number(modsOnly);number(skipMods);
    number(previousData->getObject()==NULL);number(previousClass->getObject()==NULL);number(list.size());
    for(unsigned i=0;i<selectedFiles;++i)list.add(fileName(i));
    return selectedFiles+77;
}
void loadGroup(CDataGroup* owner,const std::wstring& name,CTimerStatics* timers)
{
    valid(owner&&timers==NULL&&owner->GetGroupName()==name&&loadCalls<selectedFiles);
    event(23);text(name);number(owner->GetNumberOfDataValues());number(owner->GetNumberOfDataGroups());
    TSafePointer<CDataGroup>* witness=new TSafePointer<CDataGroup>;witness->setObject(owner);loadedWitnesses.push_back(witness);
    unsigned index=loadCalls++;
    unsigned mode=current->seed/5%5;
    std::wstring className=index%3==0?L"FIRST":index%3==1?L"FORWARD":L"THIRD";
    if(mode==1&&index==0)className=L"";
    owner->SetDataValue(L"NAME",className,false);
    owner->SetDataValue(L"LEVEL_BONUS",int(index)*11-int(current->seed));
    owner->SetDataValue(L"DONOTSPAWN",mode==2&&index==1);
    if(mode==3)return;
    CDataGroup* child=owner->AddDataGroup(L"choice");
    child->SetDataValue(L"SPAWNCLASS",index%3==0?L"FORWARD":index%3==1?L"THIRD":L"FIRST",false);
    child->SetDataValue(L"WEIGHT",int(index)+3);
    if(mode==4){CDataGroup* missing=owner->AddDataGroup(L"missing");missing->SetDataValue(L"SPAWNCLASS",L"NOT-PRESENT",false);}
}
void emptyObserved(CSpawnClassParser* owner,CDataGroup* value)
{
    valid(owner==parser&&loadCalls==selectedFiles&&fillCalls==0);++emptyCalls;event(25);
    text(value->GetGroupName());number(parser->m_spawnClasses.size());
    emptyHook->restore();prEmptyOld(owner,value);TL_REDIRECT(*emptyHook,prEmpty,&emptyObserved);
    valid(!emptyHook->failed());
}
void fillObserved(CSpawnClassParser* owner,CDataGroup* value)
{
    valid(owner==parser&&loadCalls==selectedFiles&&emptyCalls==selectedFiles);++fillCalls;event(27);
    text(value->GetGroupName());number(parser->m_spawnClasses.size());
    fillHook->restore();prFillOld(owner,value);TL_REDIRECT(*fillHook,prFill,&fillObserved);
    valid(!fillHook->failed());
}
void reloadSide(void* raw,autotest::Capture& out,bool ours,bool observed)
{
    current=static_cast<Case*>(raw);capture=&out;catalogDigest=NULL;invoking=false;typeCapture=false;loadCalls=emptyCalls=fillCalls=0;loadedWitnesses.clear();
    const unsigned counts[]={0,1,2,3,12};selectedFiles=counts[current->seed%5];
    const wchar_t* observedDirectories[]={L"spawn-proof/",L"\u0416\u4e2d/",L"",L"a-long-resource-folder-name-for-string-storage/"};
    requestedDirectory=observed?observedDirectories[current->seed/25%4]:(current->seed%3==0?L"media/no-such-parser-recovery-directory/":current->seed%3==1?L"media/SpawnClasses/":L"media/spawnclasses/");
    TSafePointer<CSpawnClassData> oldData;TSafePointer<CSpawnClass> oldClass;int objects=g_iTotalCountOfObjects;
    {Owner owner;preparePrevious(oldData,oldClass);
     detour::Set boundary,empty,fill;emptyHook=&empty;fillHook=&fill;
     if(observed){TL_REDIRECT(boundary,prFiles,&fileList);TL_REDIRECT(boundary,prLoad,&loadGroup);TL_REDIRECT(empty,prEmpty,&emptyObserved);TL_REDIRECT(fill,prFill,&fillObserved);}
     if(boundary.failed()||empty.failed()||fill.failed()){out.issue=autotest::Capture::InvalidReport;return;}
     bool(*fn)(CSpawnClassParser*,const wchar_t*)=ours?prReloadNew:prReloadOld;invoking=true;
     if(autotest::beginInvocation(out,fn)){bool result=fn(parser,requestedDirectory.c_str());out.callCompleted=1;
         if(!observed)valid(current->seed%3==0?parser->m_spawnClassData.empty():!parser->m_spawnClassData.empty());
         if(ours&&current->negative==1)result=!result;number(result);}
     invoking=false;number(oldData.getObject()==NULL);number(oldClass.getObject()==NULL);
     number(loadCalls);number(emptyCalls);number(fillCalls);for(unsigned i=0;i<loadedWitnesses.size();++i)number(loadedWitnesses[i]->getObject()==NULL);
     if(ours&&current->negative==2){
         valid(!parser->m_spawnClassData.empty());
         if(!parser->m_spawnClassData.empty()){
             CSpawnClassData* last=parser->m_spawnClassData.rbegin()->second;valid(last!=NULL);
             if(last)last->m_iFlags^=1;
         }
     }
     if(observed)dumpParser();
     else{
         // Explicit catalog cardinalities precede a digest of every byte that
         // dumpParser emitted in V1, including exact borrowed unit identities.
         number(parser->m_spawnClasses.size());number(parser->m_spawnClassData.size());
         CatalogSHA256 digest;catalogDigest=&digest;dumpParser();catalogDigest=NULL;
         unsigned char result[32];digest.finish(result);capture->add(&digest.total,sizeof digest.total);capture->add(result,sizeof result);
     }
     boundary.restore();empty.restore();fill.restore();}
    number(oldData.getObject()==NULL);number(oldClass.getObject()==NULL);integer(g_iTotalCountOfObjects-objects);
    for(unsigned i=0;i<loadedWitnesses.size();++i)delete loadedWitnesses[i];loadedWitnesses.clear();
}
void reloadBefore(void* p,autotest::Capture& out){reloadSide(p,out,false,true);}
void reloadAfter(void* p,autotest::Capture& out){reloadSide(p,out,true,true);}
void nativeBefore(void* p,autotest::Capture& out){reloadSide(p,out,false,false);}
void nativeAfter(void* p,autotest::Capture& out){reloadSide(p,out,true,false);}

int run(const tlhybrid_host* host,unsigned mode)
{
    if(!digestKnownAnswers()){host->log("    parser catalog SHA-256 known-answer failure\n");return 1;}
    nativegame::Services services;if(!services.ready())return 1;
    hierarchy=CMasterResourceManager::getSingleton()->m_pHierarchy;unitResources=CUnitResourceList::getSingleton();files=CFileSystem::getSingleton();
    if(!hierarchy||!unitResources||!files)return 1;
    const char* labels[]={"spawn_parser_type_recovery","spawn_parser_reload_observed_recovery","spawn_parser_reload_native_recovery"};
    const unsigned counts[]={384,100,24};
    void(*before)(void*,autotest::Capture&)=mode==0?typeBefore:mode==1?reloadBefore:nativeBefore;
    void(*after)(void*,autotest::Capture&)=mode==0?typeAfter:mode==1?reloadAfter:nativeAfter;
    autotest::Coverage coverage(labels[mode],mode==0?0xa7f410:0xa816c0);
    for(unsigned i=0;i<counts[mode];++i){Case c={i,0};autotest::Outcome a,b;autotest::runChild(before,&c,a,10000,20000);autotest::runChild(after,&c,b,10000,20000);
        if(coverage.observe(host,a,b)){size_t at=0;while(at<a.capture.length&&at<b.capture.length&&a.capture.data[at]==b.capture.data[at])++at;
            host->log("    parser mode%u seed%u valid%u/%u issue%u/%u exit%d/%d completed%u/%u bytes%lu/%lu first%lu\n",mode,i,a.reportValid,b.reportValid,a.capture.issue,b.capture.issue,a.childStatus,b.childStatus,a.capture.callCompleted,b.capture.callCompleted,(unsigned long)a.capture.length,(unsigned long)b.capture.length,(unsigned long)at);coverage.report(host);return 1;}}
    coverage.report(host);bool controls=true;
    for(unsigned mutation=1;mutation<=(mode==2?2u:1u);++mutation){
        Case control={mode==0?270u:mode==1?13u:1u,mutation};autotest::Outcome a,b;autotest::runChild(before,&control,a,10000,20000);autotest::runChild(after,&control,b,10000,20000);
        bool detected=a.capture.length!=b.capture.length||std::memcmp(a.capture.data,b.capture.data,a.capture.length);
        bool completed=a.reportValid&&b.reportValid&&!a.childStatus&&!b.childStatus&&!autotest::incomplete(a)&&!autotest::incomplete(b);
        host->log("    parser mode%u negative%u detected%u completed%u\n",mode,mutation,unsigned(detected),unsigned(completed));controls=controls&&detected&&completed;
    }
    return coverage.completed!=counts[mode]||coverage.missing||coverage.different||!controls;
}
int typeWorker(const tlhybrid_host* host){return run(host,0);}
int reloadWorker(const tlhybrid_host* host){return run(host,1);}
int nativeWorker(const tlhybrid_host* host){return run(host,2);}
}
TL_TEST(spawn_parser_type_recovery){return systems_fixture::isolated(typeWorker,host,180);}
TL_TEST(spawn_parser_reload_observed_recovery){return systems_fixture::isolated(reloadWorker,host,180);}
TL_TEST(spawn_parser_reload_native_recovery){return systems_fixture::isolated(nativeWorker,host,180);}
