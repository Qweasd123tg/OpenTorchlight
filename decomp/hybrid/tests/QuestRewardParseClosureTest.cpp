// Original-ELF closure for CQuestRewards::parseRewardTag, 0xd3c0c0.
// Prepared packet: tu-9xmmn_78, SHA256 59bdfb786c351526c4aa2a8dfa0b037be208941de8fea92924bbd44c094eb86a.
// Genuine lane: original Quest/Requirements/Rewards/Resource/DataGroup/Spawn
// constructors and getters, plus original UnitResourceList construction/lookup.
// SpawnClassParser has a bounded, explicitly synthetic map; its directory-
// loading constructor is NEVER called. Controlled callbacks and expected
// exception unwinds are separate. Unwinds receive no acceptance credit.
// Only this target is submitted to Coverage. No world/item creation claim.
#include <climits>
#include <cstring>
#include <cwchar>
#include <map>
#include <new>
#include <string>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#include "QuestRewards.h"
#include "TRepository.h"

TL_ORIGINAL(long long, qrpOld, (void*,CDataGroup*), "_ZN13CQuestRewards14parseRewardTagEP10CDataGroup")
extern "C" long long qrpNew(void*,CDataGroup*) __asm__("_ZN13CQuestRewards14parseRewardTagEP10CDataGroup");
TL_ORIGINAL(void, qrpQuestCtor, (void*,void*,void*), "_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void, qrpQuestDtor, (void*), "_ZN6CQuestD1Ev")
TL_ORIGINAL(void, qrpRewardCtor, (void*,void*), "_ZN13CQuestRewardsC1EP6CQuest")
TL_ORIGINAL(void, qrpRewardDtor, (void*), "_ZN13CQuestRewardsD1Ev")
TL_ORIGINAL(void, qrpResourceCtor, (void*,void*), "_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void, qrpResourceDtor, (void*), "_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void, qrpUnitsCtor, (void*), "_ZN17CUnitResourceListC1Ev")
TL_ORIGINAL(void, qrpUnitsDtor, (void*), "_ZN17CUnitResourceListD1Ev")
TL_ORIGINAL(void, qrpSpawnCtor, (void*,const wchar_t*), "_ZN11CSpawnClassC1EPKw")
TL_ORIGINAL(void, qrpSpawnDtor, (void*), "_ZN11CSpawnClassD1Ev")
TL_ORIGINAL(void, qrpGroupCtor, (void*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*), "_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void, qrpGroupDtor, (void*), "_ZN10CDataGroupD1Ev")
TL_ORIGINAL(CDataGroup*, qrpAddGroup, (void*,const std::wstring&), "_ZN10CDataGroup12AddDataGroupERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void*, qrpAddInt, (void*,const std::wstring&,int), "_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEi")
TL_ORIGINAL(void*, qrpAddBool, (void*,const std::wstring&,bool), "_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEb")
TL_ORIGINAL(void*, qrpAddText, (void*,const std::wstring&,const std::wstring&,bool), "_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES5_b")
#define QRP_DEP(R,N,A,S) TL_ORIGINAL(R,qrpOriginal##N,A,S) TL_FUNCTION(qrpBoundary##N,S)
QRP_DEP(int,Int,(void*,const std::wstring&,int),"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEi")
QRP_DEP(bool,Bool,(void*,const std::wstring&,bool),"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEb")
QRP_DEP(const std::wstring&,Text,(void*,const std::wstring&,const std::wstring&),"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
QRP_DEP(unsigned,Groups,(void*,const std::wstring&,std::vector<CDataGroup*>*),"_ZN10CDataGroup25GetDataGroupsMatchingNameERKSbIwSt11char_traitsIwESaIwEEPSt6vectorIPS_SaIS7_EE")
QRP_DEP(void*,Spawn,(void*,const std::wstring&),"_ZN17CSpawnClassParser13getSpawnClassERKSbIwSt11char_traitsIwESaIwEE")
QRP_DEP(void*,Master,(void*),"_ZN16CResourceManager21getMasterResourceListEv")
QRP_DEP(CDataGroup*,Lookup,(void*,const std::wstring&,const std::wstring&),"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEES5_")
QRP_DEP(void,Core,(void*),"_ZN10CRunicCoreC1Ev")
#undef QRP_DEP
TL_ORIGINAL(void, qrpRefDelete, (void*), "_ZN13CQuestRewards14CUnitCreateRefD0Ev")
extern "C" char qrpAlloc[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char qrpFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
extern "C" char qrpArrayNew[] __asm__("_Znam");
extern "C" char qrpArrayDelete[] __asm__("_ZdaPv");
extern "C" char qrpLiteral[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1EPKwRKS1_");

namespace qrp {
typedef std::wstring Wide;
typedef std::map<Wide,void*> SpawnMap;
typedef std::map<Wide,std::map<Wide,CDataGroup*> > UnitMap;
struct List { void** data; unsigned count,capacity,grow,pad; };
typedef char ABI[sizeof(Wide)==8 && sizeof(wchar_t)==4 && sizeof(List)==24 && sizeof(CQuestRewards)==0x78 && sizeof(CQuestRewards::CUnitCreateRef)==0x20 && sizeof(CDataGroup)==0x60 && sizeof(SpawnMap)==48?1:-1];
template<class T> T& at(void* p,unsigned o){return *reinterpret_cast<T*>(static_cast<char*>(p)+o);}
enum Code { Int=1,Text,Spawn,Groups,Master,Lookup,Bool,Array,Core,Literal,Probe };
struct Case {
 unsigned n,mask,seed,profile,text,spawn,mode,fault,line,repeated;
 bool nullInput,wrongCategory;
 Case():n(0),mask(0),seed(0),profile(0),text(0),spawn(0),mode(0),fault(0),line(1),repeated(0),nullInput(false),wrongCategory(false){}
};
struct Stop { unsigned site; explicit Stop(unsigned s):site(s){} };
struct Event {unsigned code,id,value;Wide a,b;};
struct Allocation {void* p;bool live,constructed,seed;};
struct Block {unsigned char* p;unsigned size;};
const wchar_t* categories[]={L"ITEMS",L"MONSTERS",L"PLAYERS",L"PROPS"};
const wchar_t* keys[]={L"GOLDMINPCT",L"GOLDMAXPCT",L"XPMINPCT",L"XPMAXPCT",L"FAMEMINPCT",L"FAMEMAXPCT"};
const unsigned offsets[]={0x50,0x54,0x48,0x4c,0x58,0x5c};
const int defaults[]={0,0,500,800,0,0};
static const Case* cs;static autotest::Capture* cap;
static void *owner,*quest[2],*resource[2],*units[2],*spawn[2],*parser;
static CDataGroup *root,*empty,*seedRoot,*definitions[4],*children[4],*active;
static SpawnMap* spawnMap;
static Wide names[4],treasure;
static int integers[6];static unsigned wantedData[4];static bool wantedIdentify[4];
static std::vector<Event> wanted;
static unsigned seen,errors,firstError,sites[16],faultHits,probeCalls,step,refCount,arrayCalls,freed;
static Allocation refs[64];static bool inCall,track;static void** orphanArray;static void* probeFirst;
static Block blocks[24];static unsigned blockCount;
static const Wide* borrowed[8];static int borrowedRefs[8];static unsigned borrowedCount;
static void *savedMaster,*savedParser,*savedUnits;
typedef long long(*Fn)(void*,CDataGroup*);static Fn invokeTarget;
static detour::Set *pInt,*pText,*pSpawn,*pGroups,*pMaster,*pLookup,*pBool,*pCore,*pAlloc,*pFree,*pArray,*pArrayFree,*pLiteral;
static void n(unsigned v){cap->add(&v,4);}
static void check(bool ok,unsigned line){if(!ok){if(!errors)firstError=line;++errors;}}
#define NEED(x) check((x),__LINE__)
static void* raw(unsigned size){
 NEED(blockCount<24);if(blockCount>=24)_exit(71);
 unsigned char* p=static_cast<unsigned char*>(autotest::allocate(size+32));if(!p)_exit(71);
 std::memset(p,0xb6,16);std::memset(p+16,0xa5,size);std::memset(p+16+size,0x6b,16);
 blocks[blockCount].p=p;blocks[blockCount++].size=size;return p+16;
}
static int cowRefs(const Wide& s){return *reinterpret_cast<const int*>(reinterpret_cast<const char*>(s.c_str())-8);}
static Wide decimal(unsigned value){wchar_t text[24];std::swprintf(text,24,L"%u",value);return Wide(text);}
static Wide upperASCII(Wide value){for(unsigned i=0;i<value.size();++i)if(value[i]>=L'a'&&value[i]<=L'z')value[i]-=L'a'-L'A';return value;}
static unsigned groupId(void* p){if(!p)return 0;if(p==root)return 1;if(p==empty)return 2;if(p==seedRoot)return 3;for(unsigned i=0;i<4;++i){if(p==children[i])return 10+i;if(p==definitions[i])return 20+i;}return 99;}
static unsigned pointerId(void* p,void* a,void* b){return p==a?1:p==b?2:p?99:0;}
static unsigned refId(void* p){for(unsigned i=refCount;i;--i)if(refs[i-1].p==p&&refs[i-1].live)return i;return 0;}
static unsigned addRef(void* p,bool seeded){NEED(refCount<64);if(refCount>=64)_exit(72);Allocation& r=refs[refCount++];r.p=p;r.live=true;r.constructed=seeded;r.seed=seeded;return refCount;}
static void want(unsigned code,unsigned id=0,unsigned value=0,const Wide& a=L"",const Wide& b=L""){Event e;e.code=code;e.id=id;e.value=value;e.a=a;e.b=b;wanted.push_back(e);}
static void fault(unsigned code){if(code<16)++sites[code];if(cs->fault==code&&sites[code]==cs->line){++faultHits;throw Stop(code);}}
static void emit(unsigned code,unsigned id=0,unsigned value=0,const Wide& a=L"",const Wide& b=L""){
 n(code);n(id);n(value);cap->addText(a);cap->addText(b);NEED(seen<wanted.size());
 if(seen<wanted.size()){const Event& e=wanted[seen];NEED(e.code==code&&e.id==id&&e.value==value&&e.a==a&&e.b==b);}++seen;fault(code);
}
static void rememberBorrowed(const Wide& text){for(unsigned i=0;i<borrowedCount;++i)if(borrowed[i]==&text)return;NEED(borrowedCount<8);if(borrowedCount<8){borrowed[borrowedCount]=&text;borrowedRefs[borrowedCount++]=cowRefs(text);}}

static int integer(void* self,const Wide& key,int fallback){
 emit(Int,groupId(self),static_cast<unsigned>(fallback),key);pInt->restore();
 try{int v=qrpOriginalInt(self,key,fallback);TL_REDIRECT(*pInt,qrpBoundaryInt,&integer);return v;}catch(...){TL_REDIRECT(*pInt,qrpBoundaryInt,&integer);throw;}
}
static const Wide& text(void* self,const Wide& key,const Wide& fallback){
 emit(Text,groupId(self),0,key,fallback);pText->restore();
 try{const Wide& v=qrpOriginalText(self,key,fallback);TL_REDIRECT(*pText,qrpBoundaryText,&text);rememberBorrowed(v);return v;}catch(...){TL_REDIRECT(*pText,qrpBoundaryText,&text);throw;}
}
static void* lookupSpawn(void* self,const Wide& name){
 NEED(self==parser);emit(Spawn,1,0,name);pSpawn->restore();
 try{void* v=qrpOriginalSpawn(self,name);TL_REDIRECT(*pSpawn,qrpBoundarySpawn,&lookupSpawn);return v;}catch(...){TL_REDIRECT(*pSpawn,qrpBoundarySpawn,&lookupSpawn);throw;}
}
static unsigned groups(void* self,const Wide& name,std::vector<CDataGroup*>* result){
 NEED(result&&result->empty());pGroups->restore();unsigned v;
 try{v=qrpOriginalGroups(self,name,result);TL_REDIRECT(*pGroups,qrpBoundaryGroups,&groups);}catch(...){TL_REDIRECT(*pGroups,qrpBoundaryGroups,&groups);throw;}
 emit(Groups,groupId(self),0,name);NEED(result->size()==(self==root?cs->n:0));return v;
}
static void* master(void* self){
 emit(Master,pointerId(self,resource[0],resource[1]));pMaster->restore();
 try{void* v=qrpOriginalMaster(self);TL_REDIRECT(*pMaster,qrpBoundaryMaster,&master);return v;}catch(...){TL_REDIRECT(*pMaster,qrpBoundaryMaster,&master);throw;}
}
static CDataGroup* lookup(void* self,const Wide& category,const Wide& name){
 // The target uses a wchar_t* constructor, not a COW copy of the table cell.
 if(cs->mode==4)NEED(category.c_str()!=at<Wide>(reinterpret_cast<void*>(0x14fdf20),0).c_str());
 emit(Lookup,pointerId(self,units[0],units[1]),0,category,name);pLookup->restore();CDataGroup* v;
 try{v=qrpOriginalLookup(self,category,name);TL_REDIRECT(*pLookup,qrpBoundaryLookup,&lookup);}catch(...){TL_REDIRECT(*pLookup,qrpBoundaryLookup,&lookup);throw;}
 if(cs->mode==4&&sites[Lookup]==1){
  NEED(v==0);at<Wide>(reinterpret_cast<void*>(0x14fdf20),0)=L"PROPS";
  at<void*>(owner,0x10)=quest[1];*reinterpret_cast<void**>(0x152f128)=units[1];
 }
 return v;
}
static bool identify(void* self,const Wide& key,bool fallback){
 emit(Bool,groupId(self),fallback?1:0,key);pBool->restore();
 try{bool v=qrpOriginalBool(self,key,fallback);TL_REDIRECT(*pBool,qrpBoundaryBool,&identify);return v;}catch(...){TL_REDIRECT(*pBool,qrpBoundaryBool,&identify);throw;}
}
static void core(void* self){
 unsigned id=refId(self);NEED(id!=0);fault(Core);pCore->restore();
 try{qrpOriginalCore(self);TL_REDIRECT(*pCore,qrpBoundaryCore,&core);}catch(...){TL_REDIRECT(*pCore,qrpBoundaryCore,&core);throw;}
 if(id)refs[id-1].constructed=true;
}
static void* allocate(size_t size,const char* file,int line,const char* function){
 pAlloc->restore();void* p;
 try{p=reinterpret_cast<void*(*)(size_t,const char*,int,const char*)>(qrpAlloc)(size,file,line,function);pAlloc->redirect(qrpAlloc,qrpAlloc,&allocate);}catch(...){pAlloc->redirect(qrpAlloc,qrpAlloc,&allocate);throw;}
 if(inCall){NEED(size==32);unsigned id=addRef(p,false);n(0xa110);n(id);n(static_cast<unsigned>(size));}return p;
}
static void release(void* p){
 unsigned id=track?refId(p):0;
 if(id){NEED(refs[id-1].live);refs[id-1].live=false;++freed;n(0xa111);n(id);if(inCall&&refs[id-1].seed)NEED(probeCalls==(cs->mode==1||cs->mode==2?2u:cs->mode==3?1u:0u));}
 pFree->restore();reinterpret_cast<void(*)(void*)>(qrpFree)(p);pFree->redirect(qrpFree,qrpFree,&release);
}
static void* arrayNew(size_t size){
 if(inCall){++arrayCalls;n(0xa112);n(static_cast<unsigned>(size));fault(Array);}
 pArray->restore();void* p;
 try{p=reinterpret_cast<void*(*)(size_t)>(qrpArrayNew)(size);pArray->redirect(qrpArrayNew,qrpArrayNew,&arrayNew);}catch(...){pArray->redirect(qrpArrayNew,qrpArrayNew,&arrayNew);throw;}return p;
}
static void arrayDelete(void* p){
 if(inCall){n(0xa113);n(p!=0);}
 pArrayFree->restore();reinterpret_cast<void(*)(void*)>(qrpArrayDelete)(p);pArrayFree->redirect(qrpArrayDelete,qrpArrayDelete,&arrayDelete);
}
static void literal(Wide* self,const wchar_t* value,const void* allocator){
 if(inCall&&std::wcscmp(value,L"IDENTIFY")==0)fault(Literal);
 pLiteral->restore();
 try{reinterpret_cast<void(*)(Wide*,const wchar_t*,const void*)>(qrpLiteral)(self,value,allocator);pLiteral->redirect(qrpLiteral,qrpLiteral,&literal);}catch(...){pLiteral->redirect(qrpLiteral,qrpLiteral,&literal);throw;}
}
static void probeDelete(void* self){
 unsigned id=at<unsigned>(self,8);++probeCalls;emit(Probe,id);
 if(id==1&&cs->mode==1){unsigned char before[0x78];std::memcpy(before,owner,sizeof(before));long long r=invokeTarget(owner,0);NEED(r==0&&!std::memcmp(before,owner,sizeof(before)));}
 if(id==1&&cs->mode==2){List& list=at<List>(owner,0x60);void** replacement=static_cast<void**>(at<void*>(self,16));orphanArray=list.data;list.data=replacement;}
 if(id==1&&cs->mode==3)at<List>(owner,0x60).count=1;
}

static void initializeStatics(){
 const unsigned cells[]={0x14f9fe8,0x14fb488,0x14ff1a8,0x151d408,0x151ab48,0x151c128,0x1490de8,0x14dd9c8,0x14dd9d8,0x14dda88,0x1509e88,0x14fdea8};
 for(unsigned i=0;i<sizeof(cells)/sizeof(cells[0]);++i)::new(reinterpret_cast<void*>(cells[i]))Wide();
 ::new(reinterpret_cast<void*>(0x14dd9c0))std::string();
 ::new(reinterpret_cast<void*>(0x14dd9e0))TRepository<Wide>(Wide());
 for(unsigned i=0;i<4;++i)::new(reinterpret_cast<void*>(0x14fdf20+i*8))Wide(categories[i]);
 *reinterpret_cast<unsigned*>(0x1500730)=100;
}
static CDataGroup* group(const wchar_t* name){CDataGroup* p=static_cast<CDataGroup*>(raw(sizeof(CDataGroup)));qrpGroupCtor(p,Wide(name),0,4,4,reinterpret_cast<TRepository<Wide>*>(0x14dd9e0));return p;}
static void put(void* p,const wchar_t* key,const Wide& value){qrpAddText(p,Wide(key),value,false);}
static Wide inputName(unsigned i){
 if(cs->text==1)return L"Shared";
 if(cs->text==2)return Wide(L"\u03a9\u732b")+decimal(i);
 if(cs->text==3)return Wide(257+i*31,L'x')+decimal(i);
 if(cs->text==4){const wchar_t x[]={L'U',L'n',L'i',L't',0,L'x'};return Wide(x,6);}
 if(cs->text==5||cs->text==6)return L"";
 return Wide(L"MiXeD")+decimal(i);
}
static void setup(){
 errors=firstError=seen=faultHits=probeCalls=refCount=arrayCalls=freed=borrowedCount=blockCount=step=0;
 inCall=track=false;orphanArray=0;probeFirst=0;std::memset(sites,0,sizeof(sites));std::memset(children,0,sizeof(children));autotest::g_arenaUsed=0;wanted.clear();
 savedMaster=*reinterpret_cast<void**>(0x14b3ae0);savedParser=*reinterpret_cast<void**>(0x14b7cf0);savedUnits=*reinterpret_cast<void**>(0x152f128);
 initializeStatics();*reinterpret_cast<void**>(0x14b3ae0)=0;*reinterpret_cast<void**>(0x152f128)=0;
 for(unsigned i=0;i<2;++i){resource[i]=raw(0x48);qrpResourceCtor(resource[i],0);quest[i]=raw(0x218);qrpQuestCtor(quest[i],resource[i],0);units[i]=raw(0x120);qrpUnitsCtor(units[i]);spawn[i]=raw(0x38);qrpSpawnCtor(spawn[i],i?L"OLD":L"TREASURE");}
 owner=raw(0x78);qrpRewardCtor(owner,quest[0]);
 parser=raw(0x40);spawnMap=::new(static_cast<char*>(parser)+0x10)SpawnMap;(*spawnMap)[L"TREASURE"]=spawn[0];*reinterpret_cast<void**>(0x14b7cf0)=parser;
 root=group(L"REWARD");empty=group(L"EMPTY");seedRoot=group(L"SEED");
 for(unsigned i=0;i<4;++i)definitions[i]=group(L"UNIT");
 int profileValues[6]={-7,103,501,809,-11,17};
 const int boundaries[]={INT_MIN,INT_MAX,-16777217,-1,0,1,16777217};
 for(unsigned i=0;i<6;++i){
  bool present=cs->profile!=0&&(cs->profile!=2||i%2==0);
  integers[i]=present?(cs->profile>=3?boundaries[(cs->profile-3+i)%7]:profileValues[i]):defaults[i];
  if(present)qrpAddInt(root,Wide(keys[i]),integers[i]);
 }
 treasure=cs->spawn==0?L"tReAsUrE":cs->spawn==1?L"MISSING":L"";if(cs->spawn!=2)put(root,L"TREASURECLASS",treasure);
 UnitMap& map=at<UnitMap>(units[0],0x18);UnitMap& alternate=at<UnitMap>(units[1],0x18);
 for(unsigned i=0;i<4;++i){
  Wide seedName=Wide(L"SEED")+decimal(i);CDataGroup* child=qrpAddGroup(seedRoot,Wide(L"UNITREWARD"));put(child,L"UNITNAME",seedName);map[categories[i]][seedName]=definitions[i];
 }
 qrpAddGroup(root,Wide(L"IGNORED"));
 for(unsigned i=0;i<cs->n;++i){
  children[i]=qrpAddGroup(root,Wide(L"UNITREWARD"));Wide supplied=inputName(i);names[i]=Wide(supplied.c_str());
  if(cs->text!=5)put(children[i],L"UNITNAME",supplied);
  if(i%3!=0)qrpAddBool(children[i],Wide(L"IDENTIFY"),i%3==2);
  wantedIdentify[i]=i%3!=1;wantedData[i]=cs->text==1?0:i;
  if(cs->mask&(1u<<i))map[categories[i]][upperASCII(names[i])]=definitions[wantedData[i]];
  else if(cs->wrongCategory)map[categories[(i+1)%4]][upperASCII(names[i])]=definitions[i];
  qrpAddGroup(root,Wide(L"UNRELATED"));
 }
 if(cs->mode==4)alternate[L"PROPS"][upperASCII(names[0])]=definitions[0];
 if(cs->seed){NEED(qrpOld(owner,seedRoot)==1);List& l=at<List>(owner,0x30);NEED(l.count==4);for(unsigned i=0;i<l.count&&i<4;++i)addRef(l.data[i],true);}
 at<float>(owner,0x18)=12.25f;at<float>(owner,0x1c)=-19.5f;at<float>(owner,0x20)=27.75f;at<void*>(owner,0x28)=spawn[1];
 for(unsigned i=0;i<6;++i)at<float>(owner,offsets[i])=static_cast<float>(91+i);
 if(cs->mode>=1&&cs->mode<=3){
  void** table=static_cast<void**>(raw(16));table[0]=reinterpret_cast<void*>(&probeDelete);table[1]=reinterpret_cast<void*>(&probeDelete);
  void* a=raw(24);void* b=raw(24);probeFirst=a;at<void*>(a,0)=table;at<void*>(b,0)=table;at<unsigned>(a,8)=1;at<unsigned>(b,8)=2;
  List& items=at<List>(owner,0x60);items.data=new void*[3];items.data[0]=a;items.data[1]=0;items.data[2]=b;items.count=items.capacity=3;
  if(cs->mode==2){void** replacement=new void*[3];replacement[0]=a;replacement[1]=0;replacement[2]=b;at<void*>(a,16)=replacement;}
 }
}

static unsigned hitCount(){if(active!=root)return 0;if(cs->mode==4)return 1;unsigned count=0;for(unsigned i=0;i<cs->n;++i)if(cs->mask&(1u<<i))++count;return count;}
static void expected(){
 wanted.clear();seen=borrowedCount=0;std::memset(sites,0,sizeof(sites));
 if(!active)return;
 if(step==0&&cs->mode>=1&&cs->mode<=3){want(Probe,1);if(cs->mode!=3)want(Probe,2);}
 for(unsigned i=0;i<6;++i)want(Int,groupId(active),static_cast<unsigned>(defaults[i]),keys[i]);
 want(Text,groupId(active),0,L"TREASURECLASS",L"");want(Spawn,1,0,active==root?treasure:Wide());want(Groups,groupId(active),0,L"UNITREWARD");
 if(active!=root)return;
 for(unsigned i=0;i<cs->n;++i){
  want(Text,10+i,0,L"UNITNAME",L"");bool found=(cs->mask&(1u<<i))!=0;
  unsigned attempts=cs->mode==4?2:found?1:4;
  for(unsigned j=0;j<attempts;++j){unsigned identity=cs->mode==4&&j?2:1;want(Master,identity);want(Lookup,identity,0,cs->mode==4&&j?Wide(L"PROPS"):Wide(categories[i]),names[i]);}
  if(found||cs->mode==4)want(Bool,10+i,1,L"IDENTIFY");
 }
}
static void captureState(){
 for(unsigned i=0;i<6;++i)cap->add(static_cast<char*>(owner)+offsets[i],4);
 cap->add(static_cast<char*>(owner)+0x18,12);n(pointerId(at<void*>(owner,0x10),quest[0],quest[1]));n(pointerId(at<void*>(owner,0x28),spawn[0],spawn[1]));
 for(unsigned off=0x30;off<=0x60;off+=0x30){List& l=at<List>(owner,off);n(l.data!=0);n(l.count);n(l.capacity);n(l.grow);NEED(l.count<=8);if(off==0x30)for(unsigned i=0;i<l.count&&i<8;++i){unsigned id=refId(l.data[i]);n(id);NEED(id!=0);if(id){n(groupId(at<void*>(l.data[i],0x10)));n(at<unsigned char>(l.data[i],0x18));NEED(at<void*>(l.data[i],8)==0);}}}
}
static void checkResult(unsigned caught,const unsigned char* before,unsigned refsBefore,unsigned arraysBefore){
 if(!active){NEED(!caught&&!std::memcmp(before,owner,0x78)&&seen==0);return;}
 for(unsigned i=0;i<6;++i){bool written=!(cs->fault==Int&&i>=cs->line-1);float value=written?static_cast<float>(active==root?integers[i]:defaults[i]):*reinterpret_cast<const float*>(before+offsets[i]);NEED(!std::memcmp(static_cast<char*>(owner)+offsets[i],&value,4));}
 NEED(!std::memcmp(static_cast<char*>(owner)+0x18,before+0x18,12));
 bool hasSpawn=!(caught&&(cs->fault==Int||(cs->fault==Text&&cs->line==1)||cs->fault==Spawn));
 if(hasSpawn)NEED(at<void*>(owner,0x28)==(active==root&&cs->spawn==0?spawn[0]:0));else NEED(at<void*>(owner,0x28)==*reinterpret_cast<void*const*>(before+0x28));
 unsigned expectedCount=hitCount(),leak=0,allocations=expectedCount;
 if(caught){
  if(cs->fault==Bool||cs->fault==Array||cs->fault==Core||cs->fault==Literal){expectedCount=cs->line-1;allocations=cs->line;leak=cs->fault==Core?0:1;}
  else expectedCount=allocations=0;
 }
 List& list=at<List>(owner,0x30);NEED(list.count==expectedCount);NEED(list.grow==1);
 unsigned capacity=(caught&&cs->fault==Array&&cs->line==1)?1:expectedCount;NEED(list.capacity==capacity);NEED((list.data!=0)==(expectedCount!=0));
 unsigned selected=0;
 for(unsigned i=0;i<cs->n&&selected<expectedCount&&selected<list.count&&list.data;++i)if((cs->mask&(1u<<i))||cs->mode==4){
  void* ref=list.data[selected++];NEED(at<void*>(ref,0x10)==definitions[wantedData[i]]);NEED(at<unsigned char>(ref,0x18)==static_cast<unsigned char>(wantedIdentify[i]));
  for(unsigned j=0;j+1<selected;++j)NEED(list.data[j]!=ref);
 }
 NEED(refCount-refsBefore==allocations);
 if(!caught)NEED(arrayCalls-arraysBefore==expectedCount);
 unsigned live=0;for(unsigned i=0;i<refCount;++i)if(refs[i].live)++live;NEED(live==expectedCount+leak);
 List& items=at<List>(owner,0x60);NEED(!items.data&&!items.count&&!items.capacity&&items.grow==1);
 if(cs->mode==2){NEED(orphanArray&&orphanArray[0]==probeFirst);n(orphanArray&&orphanArray[0]==probeFirst);}
 for(unsigned i=0;i<borrowedCount;++i)NEED(cowRefs(*borrowed[i])==borrowedRefs[i]);
 if(!caught)NEED(seen==wanted.size());else NEED(faultHits==1);
}

static void side(void* context,autotest::Capture& out,bool candidate){
 cs=static_cast<Case*>(context);cap=&out;invokeTarget=candidate?&qrpNew:&qrpOld;setup();track=true;
 {detour::Set di,dt,ds,dg,dm,dl,db,dc,da,df,dn,dd,dw;
 pInt=&di;pText=&dt;pSpawn=&ds;pGroups=&dg;pMaster=&dm;pLookup=&dl;pBool=&db;pCore=&dc;pAlloc=&da;pFree=&df;pArray=&dn;pArrayFree=&dd;pLiteral=&dw;
 TL_REDIRECT(di,qrpBoundaryInt,&integer);TL_REDIRECT(dt,qrpBoundaryText,&text);TL_REDIRECT(ds,qrpBoundarySpawn,&lookupSpawn);TL_REDIRECT(dg,qrpBoundaryGroups,&groups);TL_REDIRECT(dm,qrpBoundaryMaster,&master);TL_REDIRECT(dl,qrpBoundaryLookup,&lookup);TL_REDIRECT(db,qrpBoundaryBool,&identify);TL_REDIRECT(dc,qrpBoundaryCore,&core);
 da.redirect(qrpAlloc,qrpAlloc,&allocate);df.redirect(qrpFree,qrpFree,&release);dn.redirect(qrpArrayNew,qrpArrayNew,&arrayNew);dd.redirect(qrpArrayDelete,qrpArrayDelete,&arrayDelete);dw.redirect(qrpLiteral,qrpLiteral,&literal);
 if(di.failed()||dt.failed()||ds.failed()||dg.failed()||dm.failed()||dl.failed()||db.failed()||dc.failed()||da.failed()||df.failed()||dn.failed()||dd.failed()||dw.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 unsigned repetitions=cs->repeated?4:1;
 for(step=0;step<repetitions;++step){
  active=cs->nullInput?0:(step==2?empty:step==3?0:root);expected();
  unsigned char before[0x78];std::memcpy(before,owner,sizeof(before));unsigned refsBefore=refCount,arraysBefore=arrayCalls,caught=0;long long result=-9;
  n(0xb100+step);if(step==0&&!autotest::beginInvocation(out,invokeTarget))return;
  inCall=true;try{result=invokeTarget(owner,active);}catch(const Stop& stop){caught=stop.site;}catch(...){NEED(false);caught=999;}inCall=false;
  NEED(caught==cs->fault);if(!caught)NEED(result==(active?1:0));n(caught);cap->add(&result,sizeof(result));checkResult(caught,before,refsBefore,arraysBefore);captureState();
  if(caught)break;
 }
 if(!cs->fault)out.callCompleted=1;
 // Preserve the post-call leak observation before ordinary genuine teardown.
 unsigned leaked=0;for(unsigned i=0;i<refCount;++i)if(refs[i].live){bool owned=false;List& l=at<List>(owner,0x30);for(unsigned j=0;j<l.count;++j)if(l.data[j]==refs[i].p)owned=true;if(!owned)++leaked;}
 n(leaked);NEED(leaked==((cs->fault==Bool||cs->fault==Array||cs->fault==Literal)?1u:0u));
 qrpRewardDtor(owner);
 unsigned liveAfter=0;for(unsigned i=0;i<refCount;++i)if(refs[i].live)++liveAfter;n(refCount);n(freed);n(liveAfter);NEED(liveAfter==leaked);
 // Fault-path residual references are released only AFTER their original leak
 // is captured. This fixture cleanup is not attributed to target behavior.
 track=false;for(unsigned i=0;i<refCount;++i)if(refs[i].live){NEED(refs[i].constructed);qrpRefDelete(refs[i].p);refs[i].live=false;}
 }
 if(orphanArray)delete[] orphanArray;
 for(unsigned i=0;i<2;++i){qrpQuestDtor(quest[i]);qrpResourceDtor(resource[i]);qrpUnitsDtor(units[i]);}
 *reinterpret_cast<void**>(0x152f128)=savedUnits;spawnMap->clear();spawnMap->~SpawnMap();*reinterpret_cast<void**>(0x14b7cf0)=savedParser;
 for(unsigned i=0;i<2;++i)qrpSpawnDtor(spawn[i]);qrpGroupDtor(root);qrpGroupDtor(empty);qrpGroupDtor(seedRoot);for(unsigned i=0;i<4;++i)qrpGroupDtor(definitions[i]);
 *reinterpret_cast<void**>(0x14b3ae0)=savedMaster;
 for(unsigned i=0;i<blockCount;++i)for(unsigned j=0;j<16;++j){NEED(blocks[i].p[j]==0xb6);NEED(blocks[i].p[16+blocks[i].size+j]==0x6b);}
 n(firstError);n(0x71525043u);n(errors);
}
static void oldSide(void* c,autotest::Capture& out){side(c,out,false);}static void newSide(void* c,autotest::Capture& out){side(c,out,true);}
static bool oracle(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&o.childStatus==0&&!o.capture.issue&&tail[0]==0x71525043u&&!tail[1];}
static bool pair(const tlhybrid_host* host,autotest::Coverage& coverage,Case& c,unsigned& completed){
 autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);bool ok;
 if(c.fault)ok=oracle(a)&&oracle(b)&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==0xd3c0c0&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
 else{++completed;ok=coverage.observe(host,a,b)==0&&oracle(a)&&oracle(b);}
 if(!ok){unsigned fa=0,fb=0;if(a.capture.length>=12)std::memcpy(&fa,a.capture.data+a.capture.length-12,4);if(b.capture.length>=12)std::memcpy(&fb,b.capture.data+b.capture.length-12,4);host->log("    reward parser n=%u mask=%u seed=%u profile=%u text=%u spawn=%u mode=%u fault=%u line=%u repeated=%u null=%u wrongCategory=%u status=%d/%d completed=%u/%u first=%u/%u\n",c.n,c.mask,c.seed,c.profile,c.text,c.spawn,c.mode,c.fault,c.line,c.repeated,c.nullInput,c.wrongCategory,a.childStatus,b.childStatus,a.capture.callCompleted,b.capture.callCompleted,fa,fb);coverage.report(host);}return ok;
}
#undef NEED
}

TL_TEST(quest_reward_parse_closure){
 using namespace qrp;autotest::Coverage coverage("quest_reward_parse_closure",0xd3c0c0);unsigned completed=0,unwinds=0;
 // Every success/miss combination across the four valid outer categories,
 // both fresh and genuinely prepopulated Rewards objects: 62 pairs.
 for(unsigned count=0;count<=4;++count)for(unsigned mask=0;mask<(1u<<count);++mask)for(unsigned seed=0;seed<2;++seed){Case c;c.n=count;c.mask=mask;c.seed=seed;c.profile=mask%3;c.spawn=mask%3;if(!pair(host,coverage,c,completed))return 1;}
 for(unsigned profile=3;profile<10;++profile){Case c;c.profile=profile;c.spawn=2;if(!pair(host,coverage,c,completed))return 1;}
 for(unsigned text=1;text<=6;++text){Case c;c.n=4;c.mask=15;c.seed=1;c.profile=1;c.text=text;if(!pair(host,coverage,c,completed))return 1;}
 for(unsigned seed=0;seed<2;++seed){Case c;c.seed=seed;c.nullInput=true;if(!pair(host,coverage,c,completed))return 1;}
 {Case c;c.n=4;c.seed=1;c.wrongCategory=true;if(!pair(host,coverage,c,completed))return 1;}
 const unsigned repeatedMasks[]={0,5,15};for(unsigned i=0;i<3;++i){Case c;c.n=4;c.mask=repeatedMasks[i];c.seed=1;c.profile=1;c.repeated=1;if(!pair(host,coverage,c,completed))return 1;}
 // Four controlled completed cases: virtual-deletion order/null reentry,
 // backing-store reload, live-count shrink, and category/Quest/singleton reload.
 for(unsigned mode=1;mode<=4;++mode){Case c;c.mode=mode;c.seed=1;c.profile=1;c.n=mode==4?1:4;c.mask=mode==4?0:15;if(!pair(host,coverage,c,completed))return 1;}
 // 28 bounded expected unwinds, excluded from Coverage: six scalar reads,
 // treasure/name reads, spawn/groups/master/lookup, and four success positions
 // for IDENTIFY, list allocation, base construction, IDENTIFY-key construction.
 for(unsigned site=Int;site<=Literal;++site){unsigned lines=site==Int?6:site==Text?2:(site==Bool||site==Array||site==Core||site==Literal)?4:1;for(unsigned line=1;line<=lines;++line){Case c;c.n=4;c.mask=15;c.seed=1;c.profile=1;c.fault=site;c.line=line;if(!pair(host,coverage,c,completed))return 1;++unwinds;}}
 coverage.report(host);host->log("    reward parser: %u completed target-only pairs (81 genuine, 4 controlled); %u expected unwinds, no unwind acceptance credit; bounded spawn map, no directory/world loading\n",completed,unwinds);
 return completed!=85||unwinds!=28||coverage.completed!=completed||coverage.different||coverage.missing;
}
