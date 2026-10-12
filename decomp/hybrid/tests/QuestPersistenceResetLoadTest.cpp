// Independent d17200/d17b20 oracle, derived from the original ELF instructions.
// Genuine original resetGameSeed and dialog routines are always executed. The
// leaf-unit lane executes original UnitData reset/load; only resource selection
// is controlled there. The other lane isolates Quest's callback/framing contract.
// Objects are guarded ABI fixtures, not full gameplay or lifecycle coverage.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <new>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,qrlOldReset,(void*,bool,bool),"_ZN6CQuest17reinitializeQuestEbb")
extern "C" void qrlNewReset(void*,bool,bool) __asm__("_ZN6CQuest17reinitializeQuestEbb");
TL_ORIGINAL(void,qrlOldLoad,(void*,FILE*,void*,unsigned),"_ZN6CQuest4loadEP8_IO_FILEP16CResourceManagerj")
extern "C" void qrlNewLoad(void*,FILE*,void*,unsigned) __asm__("_ZN6CQuest4loadEP8_IO_FILEP16CResourceManagerj");
TL_FUNCTION(qrlReset,"_ZN6CQuest17reinitializeQuestEbb")
TL_FUNCTION(qrlSeed,"_ZN9UTILITIES7setSeedEi")
TL_FUNCTION(qrlRandom,"_ZN9UTILITIES20randomIntegerBetweenEii")
TL_FUNCTION(qrlClientSeed,"_ZN11CGameClient13resetGameSeedEi")
TL_FUNCTION(qrlSingleton,"_ZN15CDungeonManager12getSingletonEv")
TL_FUNCTION(qrlDungeon,"_ZN15CDungeonManager16getDungeonByNameESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qrlDepth,"_ZN7CPlayer11getMaxDepthESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qrlTemplate,"_ZN8CDungeon28getLevelTemplateDataForDepthEP11CGameClientj")
TL_FUNCTION(qrlGuid,"_ZN16CResourceManager17getUnitDataByGuidEx")
TL_FUNCTION(qrlUnitReset,"_ZN14CQuestUnitData12reinitializeEb")
TL_FUNCTION(qrlUnitLoad,"_ZN14CQuestUnitData4loadEP8_IO_FILEi")
TL_FUNCTION(qrlBaseGroup,"_ZN14CQuestUnitData20getBaseUnitDataGroupEv")
TL_FUNCTION(qrlDialogReset,"_ZN12CQuestDialog12reinitializeEv")
TL_FUNCTION(qrlDialogLoad,"_ZN12CQuestDialog4loadEP8_IO_FILE")
extern "C" char qrlNewArray[] __asm__("_Znam");
extern "C" char qrlDeleteArray[] __asm__("_ZdaPv");
namespace qrl {
typedef std::wstring Wide;
struct List {void** data;unsigned count,capacity,grow,pad;};
struct Flags {unsigned char* data;unsigned count,capacity,grow,pad;};
typedef char ABI[sizeof(List)==24&&sizeof(Wide)==8?1:-1];
template<class T>T& at(void* p,unsigned o){return *reinterpret_cast<T*>((char*)p+o);}
// kind: reset, isolated load (original reset on both sides), composed load.
// world: absent; first valid; first rejected; ten rejected; finite stop;
// bottomless bypass; quest-gate bypass; negative depth; no player; tenth valid.
// shape: empty, populated, aliases, capacity fallback, RNG count mutation with
// cached count, mutation with +27 reread; 6..8 outer-count mismatch by family;
// 9..11 inner-count mismatch; 12 dialog overcount; 13 dialog undercount;
// 14 nested smaller counts; 15 all saved counts zero; 16 EOF only at the
// final outer-count read, whose stack slot retains a preceding valid zero.
struct Case {unsigned kind,world,shape,flags,version,guid,real;};
struct Event {unsigned kind,a,b,c;};
struct Block {unsigned char* raw;void* p;unsigned bytes,freed,initial;};
static const Case* cs;static autotest::Capture* cap;static bool candidateSide,insideUnit,mutated;
static unsigned errors,firstError,eventCount,eventIndex,templateCalls,unitLoads,unitResets,dialogLoads,dialogResets,resetCalls;
static unsigned allocationCalls,freeCalls,blockCount,expectedAllocations,expectedFrees,expectedPosition,byteCount;
static unsigned char* owner;static void *storedResource,*passedResource,*manager,*client,*clientLevel,*player,*dungeonManager,*dungeon,*baseGroup,*guidGroup,*oldGuid,*oldTemplate,*templates[10];
static void* units[16];static void* dialogs[8];static List* groups[8];static List *selected[2],*sources[3];static Flags* flags[2];
static unsigned selectedIds[2][8],selectedCount[2],selectedCapacity[2];
static unsigned char ownerExpected[0x218],unitExpected[16][0xc8],dialogExpected[8][0xa8],flagExpected[2][8];
static unsigned char groupExpected[8][24],groupSlotsExpected[8][64],sourceSlotsExpected[3][64];
static unsigned char bytes[8192];static Event events[2048];static Block blocks[128];
static uint64_t expectedRng;static FILE* file;static int nameRefs;
static detour::Set *seedPatch,*randomPatch,*clientPatch,*unitResetPatch,*unitLoadPatch,*dialogResetPatch,*dialogLoadPatch,*questResetPatch;
static void number(unsigned x){cap->add(&x,4);}
static void check(bool yes,unsigned line){if(!yes){if(!errors)firstError=line;if(errors<5)std::fprintf(stderr,"    QRL %s kind=%u world=%u shape=%u flags=%u v=%u guid=%u real=%u line=%u event=%u/%u\n",candidateSide?"candidate":"original",cs->kind,cs->world,cs->shape,cs->flags,cs->version,cs->guid,cs->real,line,eventIndex,eventCount);++errors;}}
#define need(x) check((x),__LINE__)
static void* raw(unsigned n,unsigned char fill=0){unsigned char* p=(unsigned char*)autotest::allocate(n+32);if(!p)_exit(71);std::memset(p,0xad,n+32);std::memset(p+16,fill,n);return p+16;}
static void guard(void* p,unsigned n){for(unsigned i=0;i<16;++i)need(((unsigned char*)p)[-16+(int)i]==0xad&&((unsigned char*)p)[n+i]==0xad);}
static List& list(void* p,unsigned o){return at<List>(p,o);}
static void initList(List& l,unsigned n,unsigned capacity=4,unsigned grow=2){l.data=(void**)raw(8*8);l.count=n;l.capacity=capacity;l.grow=grow;l.pad=0x71727374u;}
static unsigned uid(void* p){for(unsigned i=0;i<16;++i)if(p==units[i])return i;need(false);return 0;}
static unsigned did(void* p){for(unsigned i=0;i<8;++i)if(p==dialogs[i])return i;need(false);return 0;}
static unsigned gid(void* p){for(unsigned i=0;i<8;++i)if(p==groups[i])return i;need(false);return 0;}
static void* item(const List& l,unsigned i){return l.data[i<l.capacity?i:0];}
static void expect(unsigned kind,unsigned a=0,unsigned b=0,unsigned c=0){if(eventCount>=2048)_exit(72);Event e={kind,a,b,c};events[eventCount++]=e;}
static void event(unsigned kind,unsigned a=0,unsigned b=0,unsigned c=0){Event e={kind,a,b,c};need(eventIndex<eventCount);if(eventIndex<eventCount)need(!std::memcmp(&e,&events[eventIndex],sizeof(e)));++eventIndex;cap->add(&e,sizeof(e));}
static int refs(const Wide& s){return *(const int*)((const char*)s.c_str()-8);}
static int modelRandom(int lo,int hi){if(hi<=lo)return lo;expectedRng=(expectedRng&0xffffffffULL)*0x29777b41ULL+(expectedRng>>32);unsigned value=(unsigned)expectedRng%(unsigned)(hi-lo+1);int result=lo+(int)value;return result>hi?hi:result;}
static void expectSeed(int seed){expect(1,(unsigned)seed);expectedRng=(unsigned)seed;}
static int expectRandom(int lo,int hi){int value=modelRandom(lo,hi);expect(2,(unsigned)lo,(unsigned)hi,(unsigned)value);return value;}
static void expectClientSeed(int depth){expect(3,(unsigned)depth);int used=depth==-1?7:depth;expectSeed(100+(cs->flags&1?9:0)+used);}
static int playerDepth(){return cs->world==7?-5:3;}
static bool present(){return cs->world!=0;}
static unsigned rejectionCount(){return cs->world==2?1:cs->world==3?10:cs->world==9?9:0;}
static void expectLookup(){expect(4);expect(5,present());}
static void modelUnitReset(unsigned id,bool resolve){
 expect(8,id,resolve);at<long long>(unitExpected[id],0x30)=-1;unitExpected[id][0x60]=unitExpected[id][0xb9]=0;
 if(cs->real&&resolve){expectSeed(at<int>(ownerExpected,0x1c));expect(9,id);at<void*>(unitExpected[id],0x20)=baseGroup;at<unsigned>(unitExpected[id],0x40)=22;at<unsigned>(unitExpected[id],0x38)=expectRandom(2,2);at<unsigned>(unitExpected[id],0x3c)=0;}
}
static void modelGroupReset(List* g,bool resolve){for(unsigned j=0;j<g->count;++j)modelUnitReset(uid(item(*g,j)),resolve);}
static void modelReset(bool resolve,bool skip){
 ownerExpected[0x24]=ownerExpected[0x26]=ownerExpected[0x209]=ownerExpected[0x210]=0;at<void*>(ownerExpected,0x1e8)=0;
 if(!skip){int seed=at<int>(ownerExpected,0x1c);if(seed!=-1)expectSeed(seed);at<void*>(ownerExpected,0x10)=0;expectLookup();
  if(present()){for(unsigned i=0;i<10;++i){int depth=cs->world==8?int(i+1):playerDepth()+int(i+1);if(cs->world!=8)expect(6,(unsigned)playerDepth());at<int>(ownerExpected,0x20)=depth;
    if(cs->world==4&&depth>=4){ownerExpected[0x210]=1;break;}
    if(depth<0)depth=0;at<int>(ownerExpected,0x20)=depth;expectClientSeed(depth);expect(7,(unsigned)depth,i);at<void*>(ownerExpected,0x10)=i<rejectionCount()?0:templates[i];if(i>=rejectionCount())break;
  }}
 }
 unsigned first=sources[0]->count;unsigned second=(unsigned)expectRandom(at<int>(ownerExpected,0x1a8),(int)sources[1]->count);
 if(cs->shape==4||cs->shape==5){at<unsigned>(ownerExpected,0x180)=1;if(cs->shape==5)first=1;}
 selectedCount[0]=first;selectedCount[1]=second;selectedCapacity[0]=selectedCapacity[1]=0;expectedFrees=2;
 for(unsigned i=0;i<sources[2]->count;++i)modelGroupReset((List*)item(*sources[2],i),resolve);
 for(unsigned f=0;f<2;++f){for(unsigned i=0;i<selectedCount[f];++i){unsigned id=gid(item(*sources[f],i));selectedIds[f][i]=id;if(i==selectedCapacity[f]){selectedCapacity[f]+=selected[f]->grow;++expectedAllocations;if(i)++expectedFrees;}modelGroupReset(groups[id],resolve);}}
 for(unsigned f=0;f<2;++f)for(unsigned i=0;i<flags[f]->count;++i)flagExpected[f][i<flags[f]->capacity?i:0]=0;
 for(unsigned f=0;f<4;++f){List& l=list(owner,0x60+f*24);for(unsigned i=0;i<l.count;++i){unsigned id=did(item(l,i));expect(10,id);dialogExpected[id][0x76]=dialogExpected[id][0x77]=0;}}
}
static void byte(unsigned x){if(byteCount>=sizeof(bytes))_exit(72);bytes[byteCount++]=(unsigned char)x;}
static void word(unsigned x){for(unsigned j=0;j<4;++j)byte(x>>(8*j));}
static void quad(uint64_t x){for(unsigned j=0;j<8;++j)byte(unsigned(x>>(8*j)));}
static void unitPayload(unsigned id,unsigned serial){
 expect(12,id,byteCount,cs->version);if(cs->real){modelUnitReset(id,true);byte(serial&1);byte(2);word(20+serial);word(30+serial);if((int)cs->version<=9)word(0xabcdef);word(40+serial);if((int)cs->version>19)quad(0x7788990000000000ULL+serial);word(0);
  unitExpected[id][0x60]=(serial&1)!=0;unitExpected[id][0xb9]=1;at<unsigned>(unitExpected[id],0x38)=20+serial;at<unsigned>(unitExpected[id],0x3c)=30+serial;at<unsigned>(unitExpected[id],0x10)=40+serial;if((int)cs->version>19)at<uint64_t>(unitExpected[id],0x30)=0x7788990000000000ULL+serial;
 }else{word(0x51000000u+serial);at<unsigned>(unitExpected[id],0x3c)=0x51000000u+serial;}
}
static void modelLoad(){
 uint64_t guid=cs->guid==0?~0ULL:cs->guid==1?0x123456789abcdef0ULL:0;
 quad(guid);if(guid!=~0ULL){expect(11,(unsigned)guid,(unsigned)(guid>>32));at<void*>(ownerExpected,0x1e8)=cs->guid==1?guidGroup:0;}
 word(17);at<int>(ownerExpected,0x1c)=17;int depth=cs->world==7?-1:4;word((unsigned)depth);at<int>(ownerExpected,0x20)=depth;
 if(cs->version>19){word(0x87654321u);at<unsigned>(ownerExpected,0x20c)=0x87654321u;}
 expectClientSeed(depth);expectLookup();if(present()){expect(7,(unsigned)depth,0);at<void*>(ownerExpected,0x10)=templates[0];}
 void* saved=at<void*>(ownerExpected,0x1e8);expect(13,1,1);modelReset(true,true);at<void*>(ownerExpected,0x1e8)=saved;
 unsigned serial=0;
 for(unsigned f=0;f<4;++f){List& l=list(owner,0x60+f*24);unsigned n=cs->shape>=15?0:cs->shape==12?l.count+2:cs->shape==13?(l.count?1:0):l.count;word(n);
  for(unsigned i=0;i<n&&i<l.count;++i){unsigned id=did(item(l,i));expect(14,id,byteCount);byte((serial&1)?0:3);byte((serial&2)?7:0);dialogExpected[id][0x76]=(serial&1)?0:1;dialogExpected[id][0x77]=(serial&2)?1:0;++serial;}}
 for(unsigned f=0;f<3;++f){unsigned live=f<2?selectedCount[f]:sources[2]->count;unsigned outer=cs->shape>=15?0:cs->shape==6+f?live+1:cs->shape==14?(live?1:0):live;if(!(cs->shape==16&&f==2))word(outer);
  for(unsigned i=0;i<outer;++i){List* g=0;if(outer<=live){unsigned id=f<2?selectedIds[f][i]:gid(item(*sources[2],i));g=groups[id];}
   unsigned inner=g?g->count:1;if(cs->shape==9+f)++inner;if(cs->shape==14&&inner)inner=1;word(inner);
   // Deliberately no bytes for skipped records. The next header/continuation
   // remains at the exact position where the original stops consuming.
   if(g&&inner<=g->count)for(unsigned j=0;j<inner;++j)unitPayload(uid(item(*g,j)),++serial);
  }}
 ownerExpected[0x26]=1;expectedPosition=byteCount;if(cs->shape!=16)word(0x6c5b4a39u);
}
static void* allocateBlock(unsigned n,unsigned initial){need(blockCount<128);Block& b=blocks[blockCount++];b.raw=(unsigned char*)std::malloc(n+32);if(!b.raw)throw std::bad_alloc();std::memset(b.raw,0xbd,n+32);b.p=b.raw+16;b.bytes=n;b.freed=0;b.initial=initial;return b.p;}
static void setup(){
 errors=firstError=eventCount=eventIndex=templateCalls=unitLoads=unitResets=dialogLoads=dialogResets=resetCalls=allocationCalls=freeCalls=blockCount=expectedAllocations=expectedFrees=expectedPosition=byteCount=0;insideUnit=mutated=false;file=0;autotest::g_arenaUsed=0;expectedRng=1234;*reinterpret_cast<uint64_t*>(0x14ecaf0)=1234;
 owner=(unsigned char*)raw(0x218,0x59);storedResource=raw(0x40);passedResource=raw(0x40);manager=raw(0x30);client=raw(0x3910);clientLevel=raw(0x60);player=raw(0x40);dungeonManager=raw(0x40);dungeon=raw(0x118);baseGroup=raw(0x40);guidGroup=raw(0x40);oldGuid=raw(0x40);oldTemplate=raw(0x778);
 at<int>(client,0x1090)=100;at<int>(client,0x1094)=7;at<void*>(client,0x38d8)=(cs->flags&1)?clientLevel:0;at<int>(clientLevel,0x58)=9;
 void** clients=(void**)raw(16);clients[0]=client;at<void*>(storedResource,0x28)=clients;at<unsigned>(storedResource,0x30)=1;at<void*>(passedResource,0x28)=clients;at<unsigned>(passedResource,0x30)=1;
 at<void*>(owner,0x1d8)=storedResource;at<void*>(owner,0x1d0)=manager;at<void*>(manager,0x10)=cs->world==8?0:player;at<void*>(owner,0x1e8)=oldGuid;at<void*>(owner,0x10)=oldTemplate;
 at<int>(owner,0x1c)=(cs->flags&4)?-1:29;at<int>(owner,0x20)=33;at<unsigned>(owner,0x20c)=0x11223344;owner[0x24]=owner[0x26]=owner[0x209]=owner[0x210]=1;owner[0x27]=cs->shape==5;owner[0x20b]=cs->world!=6;at<int>(dungeon,0x18)=cs->world==4||cs->world==5||cs->world==6?4:100;at<unsigned char>(dungeon,0x89)=cs->world==5;
 new(owner+0x30)Wide(L"Test dungeon \u03a9");nameRefs=refs(at<Wide>(owner,0x30));
 new(reinterpret_cast<void*>(0x14ff1a8))Wide();
 for(unsigned i=0;i<10;++i){templates[i]=raw(0x778,0x43);at<unsigned char>(templates[i],0x86)=i>=rejectionCount();at<unsigned char>(templates[i],0x87)=i<rejectionCount();}
 for(unsigned i=0;i<16;++i){units[i]=raw(0xc8,0x63);at<void*>(units[i],0x18)=owner;at<void*>(units[i],0x48)=0;at<unsigned>(units[i],0x50)=at<unsigned>(units[i],0x54)=0;at<int>(units[i],0xa8)=at<int>(units[i],0xac)=2;new((char*)units[i]+0x98)Wide();std::memcpy(unitExpected[i],units[i],0xc8);}
 for(unsigned i=0;i<8;++i){dialogs[i]=raw(0xa8,0x71);at<unsigned char>(dialogs[i],0x76)=at<unsigned char>(dialogs[i],0x77)=1;std::memcpy(dialogExpected[i],dialogs[i],0xa8);groups[i]=(List*)raw(sizeof(List));initList(*groups[i],cs->shape==0?0:2,cs->shape==3?1:4);groups[i]->data[0]=units[(i*2)%16];groups[i]->data[1]=units[(i*2+1)%16];}
 for(unsigned f=0;f<4;++f){List& l=list(owner,0x60+f*24);initList(l,cs->shape==0?0:2,cs->shape==3?1:4);l.data[0]=dialogs[f*2];l.data[1]=dialogs[f*2+1];}
 for(unsigned f=0;f<2;++f){flags[f]=&at<Flags>(owner,0xf8+f*24);Flags& l=*flags[f];l.data=(unsigned char*)raw(8,1);l.count=cs->shape==0?0:3;l.capacity=cs->shape==3?1:8;l.grow=7;l.pad=0x81828384;std::memcpy(flagExpected[f],l.data,8);
  selected[f]=&list(owner,0x130+f*24);selected[f]->data=(void**)allocateBlock(24,f+1);selected[f]->count=2;selected[f]->capacity=3;selected[f]->grow=f?1:2;selected[f]->pad=0x91929394;for(unsigned j=0;j<3;++j)selected[f]->data[j]=groups[7-j];}
 sources[0]=&list(owner,0x178);sources[1]=&list(owner,0x190);sources[2]=&list(owner,0x160);
 for(unsigned f=0;f<3;++f){initList(*sources[f],cs->shape==0?0:f<2?3:2,cs->shape==3?1:4);for(unsigned j=0;j<3;++j)sources[f]->data[j]=groups[f<2?3*f+j:6+j%2];}
 if(cs->shape==2){sources[0]->data[1]=groups[0];sources[1]->data[1]=groups[0];sources[2]->data[1]=groups[0];}
 for(unsigned i=0;i<8;++i){std::memcpy(groupExpected[i],groups[i],24);std::memcpy(groupSlotsExpected[i],groups[i]->data,64);}
 for(unsigned f=0;f<3;++f)std::memcpy(sourceSlotsExpected[f],sources[f]->data,64);
 at<int>(owner,0x1a8)=cs->shape==0?0:1;
 std::memcpy(ownerExpected,owner,0x218);if(cs->kind)modelLoad();else modelReset((cs->flags&1)!=0,(cs->flags&2)!=0);
 // Header count mutation belongs to the callback, so build the expected
 // source state without changing the initial fixture seen by the invocation.
 if(cs->kind){file=std::tmpfile();if(!file)_exit(71);if(std::fwrite(bytes,1,byteCount,file)!=byteCount)_exit(71);std::rewind(file);}
}
static void seed(int value){event(1,(unsigned)value);need(value!=0);seedPatch->restore();reinterpret_cast<void(*)(int)>(qrlSeed_original)(value);TL_REDIRECT(*seedPatch,qrlSeed,&seed);}
static int random(int lo,int hi){randomPatch->restore();int value=reinterpret_cast<int(*)(int,int)>(qrlRandom_original)(lo,hi);TL_REDIRECT(*randomPatch,qrlRandom,&random);event(2,(unsigned)lo,(unsigned)hi,(unsigned)value);if(!insideUnit&&!mutated&&(cs->shape==4||cs->shape==5)){sources[0]->count=1;mutated=true;}return value;}
static void clientSeed(void* self,int depth){need(self==client);event(3,(unsigned)depth);clientPatch->restore();reinterpret_cast<void(*)(void*,int)>(qrlClientSeed_original)(self,depth);TL_REDIRECT(*clientPatch,qrlClientSeed,&clientSeed);}
static void* singleton(){event(4);return dungeonManager;}
static void* lookup(void* self,Wide name){need(self==dungeonManager&&name==L"Test dungeon \u03a9");event(5,present());name=L"by-value mutation";return present()?dungeon:0;}
static int depth(void* self,Wide name){need(self==player&&name==L"Test dungeon \u03a9");event(6,(unsigned)playerDepth());name=L"by-value mutation";return playerDepth();}
static void* levelTemplate(void* self,void* c,unsigned depth){need(self==dungeon&&c==client&&templateCalls<10);event(7,depth,templateCalls);return templates[templateCalls++];}
static void* resourceGuid(void* self,long long guid){need(self==storedResource&&self!=passedResource);event(11,(unsigned)guid,(unsigned)(uint64_t(guid)>>32));return cs->guid==1?guidGroup:0;}
static void* getBase(void* self){event(9,uid(self));return baseGroup;}
static void unitReset(void* self,bool resolve){unsigned id=uid(self);event(8,id,resolve);++unitResets;
 if(cs->real){bool previous=insideUnit;insideUnit=true;unitResetPatch->restore();reinterpret_cast<void(*)(void*,bool)>(qrlUnitReset_original)(self,resolve);TL_REDIRECT(*unitResetPatch,qrlUnitReset,&unitReset);insideUnit=previous;}
 else{at<long long>(self,0x30)=-1;at<unsigned char>(self,0x60)=at<unsigned char>(self,0xb9)=0;}}
static void unitLoad(void* self,FILE* f,int version){unsigned id=uid(self);need(f==file&&(unsigned)version==cs->version);event(12,id,(unsigned)std::ftell(f),(unsigned)version);++unitLoads;
 if(cs->real){unitLoadPatch->restore();reinterpret_cast<void(*)(void*,FILE*,int)>(qrlUnitLoad_original)(self,f,version);TL_REDIRECT(*unitLoadPatch,qrlUnitLoad,&unitLoad);}
 else {unsigned value=0;need(std::fread(&value,4,1,f)==1);at<unsigned>(self,0x3c)=value;}}
static void dialogReset(void* self){event(10,did(self));++dialogResets;dialogResetPatch->restore();reinterpret_cast<void(*)(void*)>(qrlDialogReset_original)(self);TL_REDIRECT(*dialogResetPatch,qrlDialogReset,&dialogReset);}
static void dialogLoad(void* self,FILE* f){need(f==file);event(14,did(self),(unsigned)std::ftell(f));++dialogLoads;dialogLoadPatch->restore();reinterpret_cast<void(*)(void*,FILE*)>(qrlDialogLoad_original)(self,f);TL_REDIRECT(*dialogLoadPatch,qrlDialogLoad,&dialogLoad);}
static void reset(void* self,bool resolve,bool skip){need(self==owner);event(13,resolve,skip);++resetCalls;questResetPatch->restore();if(candidateSide&&cs->kind==2)qrlNewReset(self,resolve,skip);else qrlOldReset(self,resolve,skip);TL_REDIRECT(*questResetPatch,qrlReset,&reset);}
static void* arrayNew(size_t bytes){++allocationCalls;return allocateBlock((unsigned)bytes,0);}
static void arrayDelete(void* p){if(!p)return;++freeCalls;unsigned i=0;for(;i<blockCount;++i)if(blocks[i].p==p&&!blocks[i].freed)break;need(i<blockCount);if(i==blockCount)return;Block& b=blocks[i];if(b.initial){List& l=*selected[b.initial-1];need(l.data==p&&!l.count&&!l.capacity);if(b.initial==1)need(selected[1]->count==2&&selected[1]->capacity==3);else need(!selected[0]->data);}
 for(unsigned j=0;j<16;++j)need(b.raw[j]==0xbd&&b.raw[16+b.bytes+j]==0xbd);b.freed=1;std::free(b.raw);}
static void snapshot(){
 need(eventIndex==eventCount);need(allocationCalls==expectedAllocations&&freeCalls==expectedFrees);need(resetCalls==(cs->kind?1u:0u));need(*reinterpret_cast<uint64_t*>(0x14ecaf0)==expectedRng);cap->add(&expectedRng,8);
 unsigned char observed[0x218];std::memcpy(observed,owner,0x218);
 for(unsigned f=0;f<2;++f){List& l=*selected[f];need(l.count==selectedCount[f]&&l.capacity==selectedCapacity[f]);need(l.grow==(f?1u:2u)&&l.pad==0x91929394);need((l.data!=0)==(l.count!=0));
  for(unsigned i=0;i<l.count&&i<8;++i){need(l.data[i]==groups[selectedIds[f][i]]);number(gid(l.data[i]));}number(l.count);number(l.capacity);
  std::memset(observed+0x130+f*24,0,16);std::memset(ownerExpected+0x130+f*24,0,16);
  need(!std::memcmp(flags[f]->data,flagExpected[f],8));cap->add(flags[f]->data,8);guard(flags[f]->data,8);
 }
 need(!std::memcmp(observed,ownerExpected,0x218));need(at<Wide>(owner,0x30)==L"Test dungeon \u03a9"&&refs(at<Wide>(owner,0x30))==nameRefs);guard(owner,0x218);cap->add(observed,0x218);
 for(unsigned i=0;i<16;++i){need(!std::memcmp(units[i],unitExpected[i],0xc8));guard(units[i],0xc8);cap->add(units[i],0xc8);}
 for(unsigned i=0;i<8;++i){need(!std::memcmp(dialogs[i],dialogExpected[i],0xa8));guard(dialogs[i],0xa8);cap->add(dialogs[i],0xa8);guard(groups[i],sizeof(List));guard(groups[i]->data,64);need(!std::memcmp(groups[i],groupExpected[i],24));need(!std::memcmp(groups[i]->data,groupSlotsExpected[i],64));}
 for(unsigned f=0;f<3;++f)need(!std::memcmp(sources[f]->data,sourceSlotsExpected[f],64));
 if(file){need((unsigned)std::ftell(file)==expectedPosition&&!std::ferror(file));need((std::feof(file)!=0)==(cs->shape==16));if(cs->shape!=16){unsigned continuation=0;need(std::fread(&continuation,4,1,file)==1&&continuation==0x6c5b4a39u);}number(expectedPosition);}
 for(unsigned i=0;i<blockCount;++i)if(!blocks[i].freed){Block& b=blocks[i];for(unsigned j=0;j<16;++j)need(b.raw[j]==0xbd&&b.raw[16+b.bytes+j]==0xbd);}
 guard(client,0x3910);guard(storedResource,0x40);guard(passedResource,0x40);number(templateCalls);number(unitResets);number(unitLoads);number(dialogResets);number(dialogLoads);number(allocationCalls);number(freeCalls);number(firstError);number(0x7152ad10u);number(errors);
}
static void side(void* p,autotest::Capture& out,bool candidate){cs=(Case*)p;cap=&out;candidateSide=candidate;setup();
 {detour::Set boundaries,seeds,randoms,clients,unitResetsSet,unitLoadsSet,dialogResetsSet,dialogLoadsSet,resets,arrays;seedPatch=&seeds;randomPatch=&randoms;clientPatch=&clients;unitResetPatch=&unitResetsSet;unitLoadPatch=&unitLoadsSet;dialogResetPatch=&dialogResetsSet;dialogLoadPatch=&dialogLoadsSet;questResetPatch=&resets;
  TL_REDIRECT(seeds,qrlSeed,&seed);TL_REDIRECT(randoms,qrlRandom,&random);TL_REDIRECT(clients,qrlClientSeed,&clientSeed);TL_REDIRECT(boundaries,qrlSingleton,&singleton);TL_REDIRECT(boundaries,qrlDungeon,&lookup);TL_REDIRECT(boundaries,qrlDepth,&depth);TL_REDIRECT(boundaries,qrlTemplate,&levelTemplate);TL_REDIRECT(boundaries,qrlGuid,&resourceGuid);TL_REDIRECT(boundaries,qrlBaseGroup,&getBase);TL_REDIRECT(unitResetsSet,qrlUnitReset,&unitReset);TL_REDIRECT(unitLoadsSet,qrlUnitLoad,&unitLoad);TL_REDIRECT(dialogResetsSet,qrlDialogReset,&dialogReset);TL_REDIRECT(dialogLoadsSet,qrlDialogLoad,&dialogLoad);if(cs->kind)TL_REDIRECT(resets,qrlReset,&reset);arrays.redirect(qrlNewArray,qrlNewArray,&arrayNew);arrays.redirect(qrlDeleteArray,qrlDeleteArray,&arrayDelete);
  if(boundaries.failed()||seeds.failed()||randoms.failed()||clients.failed()||unitResetsSet.failed()||unitLoadsSet.failed()||dialogResetsSet.failed()||dialogLoadsSet.failed()||resets.failed()||arrays.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(cs->kind){typedef void(*Fn)(void*,FILE*,void*,unsigned);Fn fn=candidate?&qrlNewLoad:&qrlOldLoad;if(!autotest::beginInvocation(out,fn))return;fn(owner,file,passedResource,cs->version);}
  else {typedef void(*Fn)(void*,bool,bool);Fn fn=candidate?&qrlNewReset:&qrlOldReset;if(!autotest::beginInvocation(out,fn))return;fn(owner,(cs->flags&1)!=0,(cs->flags&2)!=0);}out.callCompleted=1;
 }
 snapshot();if(file)std::fclose(file);for(unsigned i=0;i<blockCount;++i)if(!blocks[i].freed)std::free(blocks[i].raw);at<Wide>(owner,0x30).~Wide();for(unsigned i=0;i<16;++i)at<Wide>(units[i],0x98).~Wide();
}
static void original(void* p,autotest::Capture& out){side(p,out,false);}static void candidate(void* p,autotest::Capture& out){side(p,out,true);}
static bool good(const autotest::Outcome& o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&o.capture.callCompleted&&tail[0]==0x7152ad10u&&!tail[1];}
static bool pair(const tlhybrid_host* host,autotest::Coverage& cv,Case c){autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);bool ok=good(a)&&good(b);if(cv.observe(host,a,b))ok=false;if(!ok)host->log("    quest reset/load kind=%u world=%u shape=%u flags=%u version=%u guid=%u real=%u status=%d/%d good=%u/%u issue=%u/%u\n",c.kind,c.world,c.shape,c.flags,c.version,c.guid,c.real,a.childStatus,b.childStatus,good(a),good(b),a.capture.issue,b.capture.issue);return ok;}
}
TL_TEST(quest_persistence_reset){using namespace qrl;autotest::Coverage cv("quest_persistence_reset",0xd17200);unsigned n=0;
 for(unsigned world=0;world<10;++world)for(unsigned flags=0;flags<8;++flags){Case c={0,world,1,flags,20,0,0};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 for(unsigned shape=0;shape<6;++shape)for(unsigned flags=0;flags<4;++flags)for(unsigned real=0;real<2;++real){Case c={0,2,shape,flags,20,0,real};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 cv.report(host);return cv.completed!=n||cv.different||cv.missing;}
TL_TEST(quest_persistence_load){using namespace qrl;autotest::Coverage cv("quest_persistence_load",0xd17b20);const unsigned versions[]={19,20,0xffffffffu};unsigned n=0;
 for(unsigned v=0;v<3;++v)for(unsigned guid=0;guid<3;++guid)for(unsigned world=0;world<3;++world){Case c={1,world,1,1,versions[v],guid,0};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 for(unsigned shape=0;shape<17;++shape){Case c={1,1,shape,0,20,1,0};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 cv.report(host);return cv.completed!=n||cv.different||cv.missing;}
TL_TEST(quest_persistence_reset_load_combined){using namespace qrl;autotest::Coverage cv("quest_persistence_reset_load_combined",0xd17b20);const unsigned versions[]={19,20,0xffffffffu};unsigned n=0;
 for(unsigned v=0;v<3;++v)for(unsigned real=0;real<2;++real)for(unsigned shape=0;shape<17;++shape){Case c={2,1,shape,1,versions[v],v,real};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 for(unsigned guid=0;guid<3;++guid){Case c={2,7,2,0,20,guid,1};if(!pair(host,cv,c)){cv.report(host);return 1;}++n;}
 cv.report(host);return cv.completed!=n||cv.different||cv.missing;}
