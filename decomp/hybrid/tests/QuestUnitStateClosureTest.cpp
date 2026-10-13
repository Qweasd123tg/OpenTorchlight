// Independent ASM oracle for QUD reinitialize d493d0/250 and load d494d0/411.
// One registration, separate direct-address counters. No transitive helper credit.
#include <cstdio>
#include <cstring>
#include <map>
#include <new>
#include <string>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#include "Quest.h"
#include "QuestUnitData.h"
#include "Hierarchy.h"
#include "MasterResourceManager.h"
#include "TRepository.h"
TL_ORIGINAL(void,qsOldReset,(CQuestUnitData*,bool),"_ZN14CQuestUnitData12reinitializeEb")
TL_ORIGINAL(void,qsOldLoad,(CQuestUnitData*,FILE*,int),"_ZN14CQuestUnitData4loadEP8_IO_FILEi")
extern "C" void qsNewReset(CQuestUnitData*,bool) __asm__("_ZN14CQuestUnitData12reinitializeEb");
extern "C" void qsNewLoad(CQuestUnitData*,FILE*,int) __asm__("_ZN14CQuestUnitData4loadEP8_IO_FILEi");
TL_ORIGINAL(void,qsCtor,(void*,void*),"_ZN14CQuestUnitDataC1EP6CQuest")
TL_ORIGINAL(void,qsDtor,(void*),"_ZN14CQuestUnitDataD1Ev")
TL_ORIGINAL(void,qsResourceCtor,(void*,void*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,qsResourceDtor,(void*),"_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void,qsGroupCtor,(void*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,qsGroupDtor,(void*),"_ZN10CDataGroupD1Ev")
#define QS_DEP(R,N,A,S) TL_ORIGINAL(R,qsOriginal##N,A,S) TL_FUNCTION(qsBoundary##N,S)
QS_DEP(void,Seed,(int),"_ZN9UTILITIES7setSeedEi")
QS_DEP(int,Random,(int,int),"_ZN9UTILITIES20randomIntegerBetweenEii")
QS_DEP(CDataGroup*,Resolve,(CQuestUnitData*),"_ZN14CQuestUnitData20getBaseUnitDataGroupEv")
QS_DEP(unsigned,Type,(CHierarchy*,const std::wstring&),"_ZN10CHierarchy15getTypeIDByNameERKSbIwSt11char_traitsIwESaIwEE")
#undef QS_DEP
TL_FUNCTION(qsMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(qsGroupGuid,"_ZN16CResourceManager22getUnitGuidByDataGroupEP10CDataGroupRKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qsTick,"_Z12GetTickCountv")
extern "C" char qsFread[] __asm__("fread");
namespace qs {
typedef std::wstring Wide;typedef std::map<Wide,unsigned> TypeMap;typedef TArrayList<CQuestUnitData*> Children;
enum {Nodes=6,Null=100,Prefix=7,Reserve=64,MaxEvents=256};
typedef char ABI[sizeof(Wide)==8&&sizeof(wchar_t)==4&&sizeof(TypeMap)==48&&sizeof(CQuestUnitData)==0xc8&&sizeof(CQuest)==0x218&&sizeof(CResourceManager)==0x48?1:-1];
enum Code {Seed=1,Tick,Resolve,GroupGuid,Singleton,Type,Random,ReadBefore,ReadAfter};
enum Field {Flag1=1,Flag2,Required,Current,Legacy,Id,Guid,ChildCount};
enum Mode {Plain=0,SeedQuest,ResolveName,ResolveEmpty,ResolveRange,ResolveNull,ResolveQuest,SingletonHierarchy,SingletonName,TypeRange,RandomFields,RandomQuest,ResetGrow,ResetShrink,ResetCapacity,ResetSlot,ResetBacking,LoadGrow,LoadShrink,LoadCapacity,LoadSlot,LoadBacking,ReadCurrent,ReadRequired,ReadTracking,ReadQuest};
struct Case {unsigned target,tree,name,map,mode,fault,occurrence,saved,flags,range,capacity;int version,seed;bool resolve,nested,eof,nullQuest;
 Case():target(0),tree(0),name(1),map(1),mode(Plain),fault(0),occurrence(1),saved(0),flags(0),range(0),capacity(3),version(20),seed(17),resolve(true),nested(false),eof(false),nullQuest(false){}
};
struct Stop {unsigned code;explicit Stop(unsigned x):code(x){}};
struct Node {unsigned id,cache,quest,dataGroup,completed,tracking,required,current,from,minimum,maximum,count,capacity,bank,slots[3];unsigned long long guid;Wide name;};
struct State {Node n[Nodes];unsigned hierarchy,cursor,eof,error;unsigned long long rng;};
struct Event {unsigned code,id,a,b,c;unsigned long long value;State state;};
struct Block {unsigned char*p;unsigned size;};struct MapNode {void*p;unsigned char bytes[48];};
static const Case*cs;static autotest::Capture*cap;static bool candidateSide;static State model;static std::vector<Event>wanted;static std::vector<unsigned char>wire;
static CQuestUnitData*node[Nodes];static CQuest*quest[7];static CResourceManager*resource[2];static CDataGroup*group[2];static void*master;static CHierarchy*hierarchy[2];static Children alternate;static CQuestUnitData**backing[Nodes][2];static FILE*file;
static Block blocks[32];static unsigned blockCount,errors,firstError,eventIndex,expectedFault,seenFault,faultHits,active,loadOwner,eofReads;static bool modelFired,actualFired;static void*booleanLocal[Nodes];
static unsigned char nodeBefore[Nodes][0xc8],questBefore[7][0x218],resourceBefore[2][0x48],groupBefore[2][sizeof(CDataGroup)],hierarchyBefore[2][0x70],masterBefore[0x88];static MapNode mapNodes[12];static unsigned mapNodeCount;
static Wide sources[Nodes][8],aliases[Nodes][8];static unsigned initialSlots[Nodes][2][3];static detour::Set *pSeed,*pRandom,*pResolve,*pType,*pFread;
template<class T>T&at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
static void check(bool x,unsigned line){if(!x){if(!errors)firstError=line;++errors;}}
#define NEED(x) check((x),__LINE__)
static void n(unsigned x){cap->add(&x,4);}static int signed32(unsigned x){int y;std::memcpy(&y,&x,4);return y;}
static unsigned nid(const void*p){for(unsigned i=0;i<Nodes;++i)if(p==node[i])return i;return p?99:Null;}static unsigned qid(const void*p){for(unsigned i=0;i<7;++i)if(p==quest[i])return i;return p?99:Null;}
static unsigned gid(const void*p){return p==group[0]?1:p==group[1]?2:p?99:0;}static unsigned rid(const void*p){return p==resource[0]?0:p==resource[1]?1:99;}static unsigned hid(const void*p){return p==hierarchy[0]?0:p==hierarchy[1]?1:99;}
static unsigned seedFor(unsigned q){return static_cast<unsigned>(cs->seed)+(q==6?101u:q*17u);}
static unsigned long long resolvedGuid(unsigned r,unsigned g){return 0x1234567800000000ULL+(r+1)*0x1000+g*0x101;}
static Wide name(unsigned which){if(!which)return Wide();if(which==1)return L"iTeM";if(which==2)return L"ITEM";if(which==3)return L"ITEX";if(which==4)return Wide(L"item\0tail",9);if(which==5)return Wide(96,L'x');return L"monster";}
static Wide initialName(unsigned i){return name(i==0?cs->name:i==1?0:1);}
static Wide uppercase(Wide w){for(unsigned i=0;i<w.size();++i)if(w[i]>=L'a'&&w[i]<=L'z')w[i]-=L'a'-L'A';return w;}
static unsigned typeFor(unsigned h,const Wide&w){if(!cs->map)return ~0u;Wide u=uppercase(w);if(u==L"ITEM")return h?103:3;if(u==L"MONSTER")return h?107:7;if(u==Wide(L"ITEM\0TAIL",9))return h?0x80000002u:0x80000001u;return ~0u;}
static void interval(unsigned i,unsigned&a,unsigned&b){static const int bounds[][2]={{2,6},{5,5},{9,3},{-5,5},{-9,-2},{2147483645,2147483647},{(-2147483647-1),(-2147483647+1)}};a=static_cast<unsigned>(bounds[cs->range][0]);b=static_cast<unsigned>(bounds[cs->range][1]);if(i&&cs->range==0){a+=i;b+=i;}}
static unsigned randomValue(unsigned a,unsigned b,unsigned long long&state){if(signed32(b)<=signed32(a))return a;unsigned divisor=b-a+1;NEED(divisor!=0);state=(state&0xffffffffULL)*0x29777b41ULL+(state>>32);unsigned result=a+static_cast<unsigned>(state)%divisor;return signed32(result)>signed32(b)?b:result;}
static unsigned recordBytes(){return cs->version<=9?22:cs->version>19?26:18;}
static unsigned boolByte(unsigned serial,bool second){static const unsigned bytes[]={0,1,2,255};return bytes[(cs->flags+(second?1u:0u)+serial)%4];}
static void put(unsigned long long x,unsigned size){for(unsigned i=0;i<size;++i)wire.push_back(static_cast<unsigned char>(x>>(8*i)));}
static void makeWire(){wire.clear();for(unsigned i=0;i<Prefix;++i)wire.push_back(0xa0+i);if(cs->eof){wire.push_back(255);return;}for(unsigned s=0;s<Reserve;++s){put(boolByte(s,false),1);put(boolByte(s,true),1);put(0x80000010u+s,4);put(0x70000020u+s,4);if(cs->version<=9)put(0xdead0030u+s,4);put(0x60000040u+s,4);if(cs->version>19)put(0x9988776600000050ULL+s,8);put(s==0?cs->saved:cs->nested&&s==1?2:0,4);}}
static void append(unsigned code,unsigned id=0,unsigned a=0,unsigned b=0,unsigned c=0,unsigned long long value=0){NEED(wanted.size()<MaxEvents);Event e;e.code=code;e.id=id;e.a=a;e.b=b;e.c=c;e.value=value;e.state=model;wanted.push_back(e);if(cs->fault==code&&++expectedFault==cs->occurrence)throw Stop(code);}
static void mutate(State&s,unsigned boundary,unsigned id,unsigned field,bool&fired){Node&x=s.n[id];
 if(id==0){if(boundary==Seed&&cs->mode==SeedQuest)x.quest=6;
  if(boundary==Resolve){if(cs->mode==ResolveName)x.name=L"monster";if(cs->mode==ResolveEmpty)x.name.clear();if(cs->mode==ResolveRange){x.minimum=12;x.maximum=17;}if(cs->mode==ResolveQuest)x.quest=6;}
  if(boundary==Singleton){if(cs->mode==SingletonHierarchy)s.hierarchy=1;if(cs->mode==SingletonName)x.name=L"monster";}
  if(boundary==Type&&cs->mode==TypeRange){x.minimum=24;x.maximum=28;}
  if(boundary==Random){if(cs->mode==RandomFields){x.current=999;x.required=888;}if(cs->mode==RandomQuest)x.quest=6;}
  if(boundary==ReadAfter){if(field==ChildCount&&cs->mode==LoadGrow)x.count=3;if(field==Id&&cs->mode==ReadCurrent)x.current=0xabcdef01u;if(field==Current&&cs->mode==ReadRequired)x.required=0xabcddcbau;if(field==Flag2&&cs->mode==ReadTracking)x.tracking=1;if(field==Required&&cs->mode==ReadQuest)x.quest=6;}
 }
 if(!fired&&id==1&&boundary==Random&&cs->target==0){if(cs->mode>=ResetGrow&&cs->mode<=ResetBacking){Node&p=s.n[0];if(cs->mode==ResetGrow)p.count=3;if(cs->mode==ResetShrink)p.count=1;if(cs->mode==ResetCapacity)p.capacity=1;if(cs->mode==ResetSlot)p.slots[1]=3;if(cs->mode==ResetBacking){p.bank=1;p.slots[0]=3;p.slots[1]=2;p.slots[2]=1;}fired=true;}}
 if(!fired&&id==1&&boundary==ReadAfter&&field==ChildCount){if(cs->mode>=LoadShrink&&cs->mode<=LoadBacking){Node&p=s.n[0];if(cs->mode==LoadShrink)p.count=1;if(cs->mode==LoadCapacity)p.capacity=1;if(cs->mode==LoadSlot)p.slots[1]=3;if(cs->mode==LoadBacking){p.bank=1;p.slots[0]=3;p.slots[1]=3;p.slots[2]=2;}fired=true;}}
}
static unsigned selected(const Node&x,unsigned i){unsigned slot=i<x.capacity?i:0;NEED(slot<3);return x.slots[slot<3?slot:0];}
static void modelReset(unsigned id,bool resolve,unsigned depth){NEED(depth<8);if(depth>=8)throw Stop(999);Node&x=model.n[id];x.guid=~0ULL;x.tracking=x.completed=0;
 for(unsigned i=0;i<x.count;++i){NEED(i<4);if(i>=4)throw Stop(999);modelReset(selected(x,i),resolve,depth+1);}
 if(!resolve)return;unsigned seed=seedFor(x.quest);append(Seed,0,seed,1);if(!seed)append(Tick,0,0x76543210u);model.rng=seed?seed:0x76543210u;mutate(model,Seed,id,0,modelFired);
 append(Resolve,id);unsigned r=x.quest==6?1:x.quest%2,g=x.dataGroup;append(GroupGuid,id,r,g);x.guid=resolvedGuid(r,g);mutate(model,Resolve,id,0,modelFired);x.cache=cs->mode==ResolveNull&&id==0?0:g;
 if(x.name.empty())x.from=22;else{append(Singleton,id);mutate(model,Singleton,id,0,modelFired);append(Type,id,model.hierarchy,0,0,typeFor(model.hierarchy,x.name));unsigned result=typeFor(model.hierarchy,x.name);mutate(model,Type,id,0,modelFired);x.from=result;}
 append(Random,id,x.minimum,x.maximum);unsigned result=randomValue(x.minimum,x.maximum,model.rng);mutate(model,Random,id,0,modelFired);x.current=0;x.required=result;
}
static unsigned long long modelRead(unsigned id,unsigned field,unsigned size,unsigned long long retained=0){append(ReadBefore,id,field,size,1);unsigned start=model.cursor;unsigned count=start+size<=wire.size()?1:0;unsigned available=start<wire.size()?static_cast<unsigned>(wire.size())-start:0;unsigned bytes=available<size?available:size;unsigned long long value=retained;
 if(bytes){value=0;for(unsigned i=0;i<bytes;++i)value|=static_cast<unsigned long long>(wire[start+i])<<(8*i);}model.cursor+=bytes;if(bytes<size)model.eof=1;
 if(field==Current)model.n[id].current=static_cast<unsigned>(value);if(field==Guid)model.n[id].guid=value;
 append(ReadAfter,id,field,size,count,value);mutate(model,ReadAfter,id,field,modelFired);return value;
}
static void modelLoad(unsigned id,unsigned depth){NEED(depth<8);if(depth>=8)throw Stop(999);modelReset(id,true,0);unsigned first=modelRead(id,Flag1,1);unsigned tracking=modelRead(id,Flag2,1,first);model.n[id].tracking=tracking!=0;unsigned required=modelRead(id,Required,4);modelRead(id,Current,4);if(cs->version<=9)modelRead(id,Legacy,4);unsigned identity=modelRead(id,Id,4);if(cs->version>19)modelRead(id,Guid,8);model.n[id].completed=first!=0;model.n[id].required=required;model.n[id].id=identity;unsigned total=modelRead(id,ChildCount,4);NEED(total<=4);for(unsigned i=0;i<total;++i)if(model.n[id].count>=total)modelLoad(selected(model.n[id],i),depth+1);}
static void*raw(unsigned size){if(blockCount==32){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}unsigned char*p=static_cast<unsigned char*>(autotest::allocate(size+32));if(!p){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}std::memset(p,0xa6,16);std::memset(p+16,0,size);std::memset(p+size+16,0x6a,16);blocks[blockCount].p=p+16;blocks[blockCount++].size=size;return p+16;}
static State readState(){State s;s.rng=*reinterpret_cast<unsigned long long*>(0x14ecaf0);s.cursor=file?static_cast<unsigned>(std::ftell(file)):Prefix;s.eof=file&&std::feof(file)?1:0;s.error=file&&std::ferror(file)?1:0;s.hierarchy=hid(at<void*>(master,0x80));for(unsigned i=0;i<Nodes;++i){Node&x=s.n[i];CQuestUnitData*p=node[i];x.id=p->m_questUnitDataId;x.cache=gid(p->m_pBaseUnitDataGroup);x.quest=qid(p->m_pQuest);x.dataGroup=gid(p->m_pQuestDataGroup);x.guid=p->m_baseUnitGuid;x.completed=p->m_completed;x.tracking=p->m_trackUnitEvents;x.required=p->m_requiredUnitCount;x.current=p->m_currentUnitCount;x.from=p->m_spawnFromUnitType;x.minimum=p->m_minCount;x.maximum=p->m_maxCount;x.count=p->m_children.size();x.capacity=at<unsigned>(&p->m_children,12);CQuestUnitData**data=at<CQuestUnitData**>(&p->m_children,0);x.bank=data==backing[i][0]?0:data==backing[i][1]?1:99;for(unsigned j=0;j<3;++j)x.slots[j]=nid(data[j]);x.name=p->m_spawnFromUnitTypeName;}return s;}
static void applyMutation(unsigned boundary,unsigned id,unsigned field=0){if(id>=Nodes){NEED(false);return;}State s=readState();mutate(s,boundary,id,field,actualFired);if(s.hierarchy<2)at<void*>(master,0x80)=hierarchy[s.hierarchy];for(unsigned i=0;i<Nodes;++i){const Node&x=s.n[i];CQuestUnitData*p=node[i];if(x.quest<7)p->m_pQuest=quest[x.quest];p->m_minCount=signed32(x.minimum);p->m_maxCount=signed32(x.maximum);p->m_requiredUnitCount=signed32(x.required);p->m_currentUnitCount=signed32(x.current);p->m_trackUnitEvents=x.tracking;p->m_spawnFromUnitTypeName=x.name;at<unsigned>(&p->m_children,8)=x.count;at<unsigned>(&p->m_children,12)=x.capacity;if(x.bank<2)at<CQuestUnitData**>(&p->m_children,0)=backing[i][x.bank];CQuestUnitData**data=at<CQuestUnitData**>(&p->m_children,0);for(unsigned j=0;j<3;++j)if(x.slots[j]<Nodes)data[j]=node[x.slots[j]];}}
static void snapshot(const State*e){State s=readState();cap->add(&s.rng,8);n(s.cursor);n(s.hierarchy);n(s.eof);n(s.error);if(e){NEED(s.rng==e->rng);NEED(s.cursor==e->cursor);NEED(s.hierarchy==e->hierarchy);NEED(s.eof==e->eof&&s.error==e->error);}for(unsigned i=0;i<Nodes;++i){const Node&x=s.n[i];n(x.id);n(x.cache);n(x.quest);n(x.dataGroup);n(x.completed);n(x.tracking);n(x.required);n(x.current);n(x.from);n(x.minimum);n(x.maximum);n(x.count);n(x.capacity);n(x.bank);for(unsigned j=0;j<3;++j)n(x.slots[j]);cap->add(&x.guid,8);cap->addText(x.name);
 if(e){const Node&y=e->n[i];NEED(x.id==y.id&&x.cache==y.cache&&x.quest==y.quest&&x.dataGroup==y.dataGroup);NEED(x.completed==y.completed&&x.tracking==y.tracking);NEED(x.required==y.required&&x.current==y.current&&x.from==y.from);NEED(x.minimum==y.minimum&&x.maximum==y.maximum);NEED(x.count==y.count&&x.capacity==y.capacity&&x.bank==y.bank);for(unsigned j=0;j<3;++j)NEED(x.slots[j]==y.slots[j]);NEED(x.guid==y.guid&&x.name==y.name);}
 }}
static void emit(unsigned code,unsigned id=0,unsigned a=0,unsigned b=0,unsigned c=0,unsigned long long value=0){n(code);n(id);n(a);n(b);n(c);cap->add(&value,8);NEED(eventIndex<wanted.size());if(eventIndex<wanted.size()){const Event&e=wanted[eventIndex];NEED(code==e.code&&id==e.id&&a==e.a&&b==e.b&&c==e.c&&value==e.value);snapshot(&e.state);}else snapshot(0);++eventIndex;if(cs->fault==code&&++seenFault==cs->occurrence){++faultHits;throw Stop(code);}}
static void*noMaster(){return 0;}
static unsigned tick(){emit(Tick,0,0x76543210u);return 0x76543210u;}
static void __attribute__((noinline)) callSeed(int seed){void*returnPC=__builtin_return_address(0);unsigned long pc=reinterpret_cast<unsigned long>(returnPC);bool inside=pc>=0xd493d0UL&&pc<0xd494caUL;bool correct=inside!=candidateSide;NEED(correct);emit(Seed,0,static_cast<unsigned>(seed),correct);bool root=static_cast<unsigned>(seed)==seedFor(qid(node[0]->m_pQuest));pSeed->restore();
 try{qsOriginalSeed(seed);}catch(...){TL_REDIRECT(*pSeed,qsBoundarySeed,&callSeed);throw;}TL_REDIRECT(*pSeed,qsBoundarySeed,&callSeed);if(root)applyMutation(Seed,0);
}
static long long groupGuid(CResourceManager*r,CDataGroup*g,const Wide&key){NEED(key==L"UNIT_GUID");emit(GroupGuid,active,rid(r),gid(g));return static_cast<long long>(resolvedGuid(rid(r),gid(g)));}
static CDataGroup*callResolve(CQuestUnitData*p){active=nid(p);NEED(active<Nodes);emit(Resolve,active);pResolve->restore();CDataGroup*r;
 try{r=qsOriginalResolve(p);}catch(...){TL_REDIRECT(*pResolve,qsBoundaryResolve,&callResolve);throw;}TL_REDIRECT(*pResolve,qsBoundaryResolve,&callResolve);applyMutation(Resolve,active);return cs->mode==ResolveNull&&active==0?0:r;
}
static void*singleton(){emit(Singleton,active);applyMutation(Singleton,active);return master;}
static unsigned callType(CHierarchy*p,const Wide&w){unsigned id=Null;for(unsigned i=0;i<Nodes;++i)if(&w==&node[i]->m_spawnFromUnitTypeName)id=i;NEED(id<Nodes);NEED(id==active);unsigned expected=typeFor(hid(p),w);emit(Type,id,hid(p),0,0,expected);Wide retained=w,alias=w;pType->restore();unsigned result;
 try{result=qsOriginalType(p,w);}catch(...){TL_REDIRECT(*pType,qsBoundaryType,&callType);throw;}TL_REDIRECT(*pType,qsBoundaryType,&callType);NEED(result==expected);NEED(w==retained&&retained==alias);applyMutation(Type,id);return result;
}
static int callRandom(int a,int b){emit(Random,active,static_cast<unsigned>(a),static_cast<unsigned>(b));unsigned long long state=*reinterpret_cast<unsigned long long*>(0x14ecaf0);unsigned expected=randomValue(static_cast<unsigned>(a),static_cast<unsigned>(b),state);pRandom->restore();int result;
 try{result=qsOriginalRandom(a,b);}catch(...){TL_REDIRECT(*pRandom,qsBoundaryRandom,&callRandom);throw;}TL_REDIRECT(*pRandom,qsBoundaryRandom,&callRandom);NEED(static_cast<unsigned>(result)==expected);NEED(*reinterpret_cast<unsigned long long*>(0x14ecaf0)==state);applyMutation(Random,active);return result;
}
static unsigned fieldAt(unsigned pos){unsigned offset=(pos-Prefix)%recordBytes();if(offset==0)return Flag1;if(offset==1)return Flag2;if(offset==2)return Required;if(offset==6)return Current;offset-=10;if(cs->version<=9){if(!offset)return Legacy;offset-=4;}if(!offset)return Id;offset-=4;if(cs->version>19){if(!offset)return Guid;offset-=8;}return !offset?ChildCount:0;}
static void checkDestination(void*p,unsigned id,unsigned field){NEED(id<Nodes);if(id>=Nodes)return;if(field==Current){NEED(p==&node[id]->m_currentUnitCount);return;}if(field==Guid){NEED(p==&node[id]->m_baseUnitGuid);return;}for(unsigned i=0;i<Nodes;++i){unsigned long a=reinterpret_cast<unsigned long>(p),b=reinterpret_cast<unsigned long>(node[i]);NEED(a<b||a>=b+0xc8);}if(field==Flag1)booleanLocal[id]=p;if(field==Flag2)NEED(booleanLocal[id]==p);if(field==Legacy){unsigned x=1;std::memcpy(&x,p,4);NEED(x==0);}}
static size_t __attribute__((noinline)) read(void*destination,size_t size,size_t count,FILE*input){void*returnPC=__builtin_return_address(0);unsigned long pc=reinterpret_cast<unsigned long>(returnPC);bool inside=pc>=0xd494d0UL&&pc<0xd4966bUL;bool correct=inside!=candidateSide;NEED(correct);NEED(input==file);unsigned before=static_cast<unsigned>(std::ftell(input));unsigned field=cs->eof?++eofReads:fieldAt(before);if(field==Flag1)loadOwner=active;NEED(field>=Flag1&&field<=ChildCount);NEED(size==(field<=Flag2?1u:field==Guid?8u:4u)&&count==1);checkDestination(destination,loadOwner,field);emit(ReadBefore,loadOwner,field,size,correct);
 pFread->restore();typedef size_t(*Fn)(void*,size_t,size_t,FILE*);size_t result;
 try{result=reinterpret_cast<Fn>(qsFread)(destination,size,count,input);}catch(...){pFread->redirect(qsFread,qsFread,&read);throw;}pFread->redirect(qsFread,qsFread,&read);
 unsigned after=static_cast<unsigned>(std::ftell(input));unsigned long long value=0;NEED(size<=8);if(size<=8)std::memcpy(&value,destination,size);NEED(after>=before&&after-before<=size);emit(ReadAfter,loadOwner,field,size,result,value);applyMutation(ReadAfter,loadOwner,field);return result;
}
static void initialModel(){model.hierarchy=model.eof=model.error=0;model.cursor=Prefix;model.rng=0x1020304050607080ULL;for(unsigned i=0;i<Nodes;++i){Node&x=model.n[i];x.id=100+i;x.cache=(i%2)+1;x.quest=i;x.dataGroup=(i%2)+1;x.completed=x.tracking=1;x.required=80+i;x.current=90+i;x.from=12+i;interval(i,x.minimum,x.maximum);x.count=0;x.capacity=3;x.bank=0;for(unsigned j=0;j<3;++j)x.slots[j]=i==0?j+1:5;x.guid=0x7766554400000000ULL+i;x.name=initialName(i);}
 if(cs->tree==1)model.n[0].count=1;if(cs->tree==2||cs->tree==4||cs->tree==5)model.n[0].count=3;if(cs->tree==3){model.n[0].count=2;model.n[1].count=2;model.n[1].slots[0]=4;model.n[1].slots[1]=5;model.n[2].count=1;model.n[2].slots[0]=3;}if(cs->tree==4){model.n[0].slots[1]=1;model.n[0].slots[2]=1;}model.n[0].capacity=cs->capacity;
 if(cs->tree==5){model.n[0].guid=~0ULL;model.n[0].tracking=model.n[0].completed=0;}
 if(cs->nullQuest)for(unsigned i=0;i<Nodes;++i)model.n[i].quest=Null;
}
static void setup(){errors=firstError=blockCount=eventIndex=expectedFault=seenFault=faultHits=mapNodeCount=active=loadOwner=eofReads=0;actualFired=modelFired=false;file=0;std::memset(booleanLocal,0,sizeof(booleanLocal));autotest::g_arenaUsed=0;::new(reinterpret_cast<void*>(0x14ff1a8))Wide();
 for(unsigned i=0;i<2;++i){TRepository<Wide>*repository=new TRepository<Wide>(Wide());group[i]=static_cast<CDataGroup*>(raw(sizeof(CDataGroup)));qsGroupCtor(group[i],Wide(i?L"SECOND STATE UNIT":L"STATE UNIT"),0,4,4,repository);}
 {detour::Set environment;TL_REDIRECT(environment,qsMaster,&noMaster);if(environment.failed()){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}for(unsigned i=0;i<2;++i){resource[i]=static_cast<CResourceManager*>(raw(sizeof(CResourceManager)));qsResourceCtor(resource[i],0);}}
 for(unsigned i=0;i<7;++i){quest[i]=static_cast<CQuest*>(raw(sizeof(CQuest)));at<unsigned>(quest[i],0x1c)=seedFor(i);at<void*>(quest[i],0x1d8)=resource[i==6?1:i%2];}
 master=raw(0x88);for(unsigned i=0;i<2;++i){hierarchy[i]=static_cast<CHierarchy*>(raw(0x70));TypeMap&m=*::new(&at<TypeMap>(hierarchy[i],0x40))TypeMap;if(cs->map){m.insert(TypeMap::value_type(L"ITEM",i?103:3));m.insert(TypeMap::value_type(L"MONSTER",i?107:7));m.insert(TypeMap::value_type(Wide(L"ITEM\0TAIL",9),i?0x80000002u:0x80000001u));}for(TypeMap::iterator it=m.begin();it!=m.end();++it){mapNodes[mapNodeCount].p=it._M_node;std::memcpy(mapNodes[mapNodeCount++].bytes,it._M_node,48);}}
 at<void*>(master,0x80)=hierarchy[0];for(unsigned i=0;i<Nodes;++i){node[i]=static_cast<CQuestUnitData*>(raw(0xc8));qsCtor(node[i],quest[i]);}
 initialModel();::new(&alternate)Children(3);for(unsigned j=0;j<3;++j)alternate.add(node[3-j]);
 const unsigned offsets[]={0x68,0x70,0x78,0x80,0x88,0x90,0x98,0xc0};const wchar_t*texts[]={L"Display source",L"Unique source",L"Class source",L"Item source",L"Monster source",L"Type source",L"",L"Champion source"};
 for(unsigned i=0;i<Nodes;++i){CQuestUnitData*p=node[i];Node&x=model.n[i];p->m_pQuest=x.quest==Null?0:quest[x.quest];p->m_questUnitDataId=x.id;p->m_pBaseUnitDataGroup=group[x.cache-1];p->m_pQuestDataGroup=group[x.dataGroup-1];p->m_baseUnitGuid=x.guid;p->m_completed=x.completed;p->m_trackUnitEvents=x.tracking;p->m_requiredUnitCount=x.required;p->m_currentUnitCount=x.current;p->m_spawnFromUnitType=x.from;p->m_minCount=signed32(x.minimum);p->m_maxCount=signed32(x.maximum);p->m_makeChampion=false;
  for(unsigned j=0;j<3;++j)p->m_children.add(node[x.slots[j]]);at<unsigned>(&p->m_children,8)=x.count;at<unsigned>(&p->m_children,12)=x.capacity;backing[i][0]=at<CQuestUnitData**>(&p->m_children,0);backing[i][1]=i==0?at<CQuestUnitData**>(&alternate,0):backing[i][0];for(unsigned bank=0;bank<2;++bank)for(unsigned j=0;j<3;++j)initialSlots[i][bank][j]=nid(backing[i][bank][j]);
  for(unsigned j=0;j<8;++j){at<Wide>(p,offsets[j])=j==6?x.name:Wide(texts[j]);sources[i][j]=at<Wide>(p,offsets[j]);aliases[i][j]=sources[i][j];}std::memcpy(nodeBefore[i],p,0xc8);
 }
 for(unsigned i=0;i<7;++i)std::memcpy(questBefore[i],quest[i],0x218);for(unsigned i=0;i<2;++i){std::memcpy(resourceBefore[i],resource[i],0x48);std::memcpy(groupBefore[i],group[i],sizeof(CDataGroup));std::memcpy(hierarchyBefore[i],hierarchy[i],0x70);}std::memcpy(masterBefore,master,0x88);
 *reinterpret_cast<unsigned long long*>(0x14ecaf0)=model.rng;makeWire();if(cs->target){file=std::tmpfile();if(!file){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}NEED(std::fwrite(&wire[0],1,wire.size(),file)==wire.size());NEED(std::fseek(file,Prefix,SEEK_SET)==0);}
}
static void untouched(){const unsigned offsets[]={0x68,0x70,0x78,0x80,0x88,0x90,0x98,0xc0};const wchar_t*texts[]={L"Display source",L"Unique source",L"Class source",L"Item source",L"Monster source",L"Type source",L"",L"Champion source"};
 for(unsigned i=0;i<Nodes;++i){const unsigned char*p=reinterpret_cast<const unsigned char*>(node[i]);for(unsigned j=0;j<0xc8;++j){bool changed=(j>=0x10&&j<0x14)||(j>=0x18&&j<0x28)||(j>=0x30&&j<0x44)||(j>=0x48&&j<0x58)||j==0x60||(j>=0x98&&j<0xa0)||(j>=0xa8&&j<0xb0)||j==0xb9;if(!changed)NEED(p[j]==nodeBefore[i][j]);}
  for(unsigned j=0;j<8;++j){Wide expected=j==6?initialName(i):Wide(texts[j]);NEED(sources[i][j]==expected&&sources[i][j]==aliases[i][j]);NEED(at<Wide>(node[i],offsets[j])==(j==6?model.n[i].name:expected));}
  for(unsigned bank=0;bank<2;++bank)if(backing[i][bank]!=backing[i][model.n[i].bank])for(unsigned j=0;j<3;++j)NEED(nid(backing[i][bank][j])==initialSlots[i][bank][j]);
 }
 for(unsigned i=0;i<7;++i)NEED(!std::memcmp(questBefore[i],quest[i],0x218));for(unsigned i=0;i<2;++i){NEED(!std::memcmp(resourceBefore[i],resource[i],0x48));NEED(!std::memcmp(groupBefore[i],group[i],sizeof(CDataGroup)));NEED(!std::memcmp(hierarchyBefore[i],hierarchy[i],0x70));}
 NEED(!std::memcmp(masterBefore,master,0x80));for(unsigned i=0;i<mapNodeCount;++i)NEED(!std::memcmp(mapNodes[i].bytes,mapNodes[i].p,48));
 for(unsigned i=0;i<blockCount;++i)for(unsigned j=0;j<16;++j){NEED(blocks[i].p[int(j)-16]==0xa6);NEED(blocks[i].p[blocks[i].size+j]==0x6a);}
}
static void cleanup(){for(unsigned i=0;i<Nodes;++i){at<CQuestUnitData**>(&node[i]->m_children,0)=backing[i][0];node[i]->m_children.clear();qsDtor(node[i]);}alternate.clear();for(unsigned i=0;i<2;++i){at<TypeMap>(hierarchy[i],0x40).~TypeMap();qsGroupDtor(group[i]);qsResourceDtor(resource[i]);}if(file){NEED(std::fclose(file)==0);file=0;}}
static size_t snapshotBytes(const State&s){size_t n=24;for(unsigned i=0;i<Nodes;++i)n+=84+4*s.n[i].name.size();return n;}
static void side(void*context,autotest::Capture&out,bool candidate){cs=static_cast<Case*>(context);cap=&out;candidateSide=candidate;setup();wanted.clear();unsigned predicted=0;try{if(cs->target)modelLoad(0,0);else modelReset(0,cs->resolve,0);}catch(const Stop&s){predicted=s.code;}NEED(predicted==cs->fault);
 size_t budget=64+snapshotBytes(model);for(unsigned i=0;i<wanted.size();++i)budget+=28+snapshotBytes(wanted[i].state);if(budget>autotest::Capture::kSize-32768){out.issue=autotest::Capture::InvalidReport;return;}
 unsigned caught=0;
 {detour::Set seed,random,resolve,type,contracts,reads;pSeed=&seed;pRandom=&random;pResolve=&resolve;pType=&type;pFread=&reads;TL_REDIRECT(seed,qsBoundarySeed,&callSeed);TL_REDIRECT(random,qsBoundaryRandom,&callRandom);TL_REDIRECT(resolve,qsBoundaryResolve,&callResolve);TL_REDIRECT(type,qsBoundaryType,&callType);TL_REDIRECT(contracts,qsMaster,&singleton);TL_REDIRECT(contracts,qsGroupGuid,&groupGuid);TL_REDIRECT(contracts,qsTick,&tick);reads.redirect(qsFread,qsFread,&read);
  if(seed.failed()||random.failed()||resolve.failed()||type.failed()||contracts.failed()||reads.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(cs->target){typedef void(*Fn)(CQuestUnitData*,FILE*,int);Fn f=candidate?&qsNewLoad:&qsOldLoad;if(!autotest::beginInvocation(out,f))return;try{f(node[0],file,cs->version);out.callCompleted=1;}catch(const Stop&s){caught=s.code;}catch(...){caught=999;NEED(false);}}
  else{typedef void(*Fn)(CQuestUnitData*,bool);Fn f=candidate?&qsNewReset:&qsOldReset;if(!autotest::beginInvocation(out,f))return;try{f(node[0],cs->resolve);out.callCompleted=1;}catch(const Stop&s){caught=s.code;}catch(...){caught=999;NEED(false);}}
  NEED(caught==predicted);NEED(faultHits==(cs->fault?1u:0u));NEED(eventIndex==wanted.size());n(caught);snapshot(&model);NEED(!seed.failed()&&!random.failed()&&!resolve.failed()&&!type.failed()&&!contracts.failed()&&!reads.failed());
 }
 untouched();if(file){unsigned position=std::ftell(file);NEED(position==model.cursor);NEED(std::fseek(file,0,SEEK_SET)==0);std::vector<unsigned char>copy(wire.size());NEED(std::fread(&copy[0],1,copy.size(),file)==copy.size());NEED(copy==wire);NEED(std::fseek(file,position,SEEK_SET)==0);}
 for(unsigned i=0;i<Nodes;++i){Wide retained=node[i]->m_spawnFromUnitTypeName;node[i]->m_spawnFromUnitTypeName+=L" after invocation";NEED(retained==model.n[i].name);NEED(sources[i][6]==initialName(i));NEED(sources[i][6]==aliases[i][6]);}
 cleanup();n(firstError);n(0x51535441u);n(errors);
}
static void oldSide(void*p,autotest::Capture&o){side(p,o,false);}static void newSide(void*p,autotest::Capture&o){side(p,o,true);}
static bool oracle(const autotest::Outcome&o){unsigned t[2]={0,1};if(o.capture.length>=8)std::memcpy(t,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&t[0]==0x51535441u&&!t[1];}
static unsigned failureLine(const autotest::Outcome&o){unsigned n=0;if(o.capture.length>=12)std::memcpy(&n,o.capture.data+o.capture.length-12,4);return n;}
static bool pair(const tlhybrid_host*host,autotest::Coverage&coverage,Case&c,unsigned&completed,unsigned&unwinds,unsigned&originalFailures,unsigned&candidateFailures){autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);bool oa=oracle(a),ob=oracle(b);if(!oa)++originalFailures;if(!ob)++candidateFailures;bool ok;unsigned target=c.target?0xd494d0:0xd493d0;
 if(c.fault){++unwinds;ok=oa&&ob&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==target&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);}
 else{++completed;ok=coverage.observe(host,a,b)==0&&oa&&ob;}
 if(!ok){host->log("    state target=%u pair=%u/%u tree=%u mode=%u version=%d saved=%u fault=%u.%u status=%d/%d oracle=%u/%u line=%u/%u\n",c.target,completed,unwinds,c.tree,c.mode,c.version,c.saved,c.fault,c.occurrence,a.childStatus,b.childStatus,oa,ob,failureLine(a),failureLine(b));if(coverage.completed)coverage.report(host);}return ok;
}
#undef NEED
}
TL_TEST(quest_unit_state_closure){using namespace qs;autotest::Coverage resetCoverage("quest_unit_state_closure",0xd493d0),loadCoverage("quest_unit_state_closure",0xd494d0);std::vector<Case>resetCases,loadCases,resetFaults,loadFaults;unsigned resetCount=0,loadCount=0,resetUnwinds=0,loadUnwinds=0,originalFailures=0,candidateFailures=0;
 {Case c;c.tree=5;resetCases.push_back(c);}
 const unsigned capacities[]={0,1,3};for(unsigned tree=0;tree<6;++tree)for(unsigned resolve=0;resolve<2;++resolve)for(unsigned k=0;k<3;++k){Case c;c.tree=tree;c.resolve=resolve;c.capacity=capacities[k];resetCases.push_back(c);}
 for(unsigned name=0;name<7;++name)for(unsigned map=0;map<2;++map){Case c;c.name=name;c.map=map;resetCases.push_back(c);}
 const int seeds[]={0,1,-1,(-2147483647-1),2147483647};for(unsigned s=0;s<5;++s)for(unsigned range=0;range<7;++range){Case c;c.seed=seeds[s];c.range=range;resetCases.push_back(c);}
 for(unsigned mode=SeedQuest;mode<=ResetBacking;++mode){Case c;c.mode=mode;if(mode>=ResetGrow){c.tree=mode==ResetGrow?1:2;}resetCases.push_back(c);}
 for(unsigned tree=1;tree<=3;tree+=2){Case c;c.tree=tree;c.resolve=false;c.nullQuest=true;resetCases.push_back(c);}
 {Case c;c.target=1;c.tree=1;c.saved=1;loadCases.push_back(c);}
 const int versions[]={-1,0,9,10,19,20,(-2147483647-1),2147483647};for(unsigned v=0;v<8;++v)for(unsigned flags=0;flags<4;++flags)for(unsigned saved=0;saved<=4;++saved){Case c;c.target=1;c.version=versions[v];c.flags=flags;c.saved=saved;c.tree=2;loadCases.push_back(c);}
 for(unsigned tree=0;tree<6;++tree)for(unsigned saved=0;saved<=4;++saved){Case c;c.target=1;c.tree=tree;c.saved=saved;c.flags=2;loadCases.push_back(c);}
 for(unsigned capacity=0;capacity<4;++capacity)for(unsigned tree=2;tree<=4;tree+=2)for(unsigned saved=2;saved<=3;++saved){Case c;c.target=1;c.tree=tree;c.saved=saved;c.capacity=capacity;loadCases.push_back(c);}
 const int nestedVersions[]={-1,10,20};for(unsigned v=0;v<3;++v)for(unsigned k=0;k<2;++k){Case c;c.target=1;c.tree=3;c.saved=2;c.nested=true;c.version=nestedVersions[v];c.capacity=k?3:1;loadCases.push_back(c);}
 for(unsigned mode=LoadGrow;mode<=ReadQuest;++mode){Case c;c.target=1;c.mode=mode;if(mode<=LoadBacking){c.tree=mode==LoadGrow?1:2;c.saved=3;}if(mode==ReadTracking)c.flags=3;loadCases.push_back(c);}
 const unsigned cross[]={SeedQuest,ResolveRange,SingletonHierarchy};for(unsigned i=0;i<3;++i){Case c;c.target=1;c.mode=cross[i];c.tree=1;c.saved=1;loadCases.push_back(c);}
 for(unsigned code=Seed;code<=Random;++code){Case c;c.fault=code;if(code==Tick)c.seed=0;resetFaults.push_back(c);c.target=1;loadFaults.push_back(c);}
 const unsigned lateReset[]={Seed,Resolve,Random};for(unsigned i=0;i<3;++i){Case c;c.tree=2;c.fault=lateReset[i];c.occurrence=i==0?3:2;resetFaults.push_back(c);}
 for(unsigned code=ReadBefore;code<=ReadAfter;++code)for(unsigned occurrence=1;occurrence<=7;++occurrence){Case c;c.target=1;c.fault=code;c.occurrence=occurrence;loadFaults.push_back(c);}
 for(unsigned code=ReadBefore;code<=ReadAfter;++code){Case c;c.target=1;c.version=9;c.fault=code;c.occurrence=5;loadFaults.push_back(c);}
 {Case c;c.target=1;c.tree=1;c.saved=1;c.fault=ReadBefore;c.occurrence=8;loadFaults.push_back(c);}
 {Case c;c.target=1;c.tree=1;c.saved=1;c.fault=ReadAfter;c.occurrence=14;loadFaults.push_back(c);}
 {Case c;c.target=1;c.eof=true;c.fault=ReadBefore;c.occurrence=3;loadFaults.push_back(c);}
 if(resetCases.size()!=104||loadCases.size()!=225||resetFaults.size()!=10||loadFaults.size()!=26){host->log("    state inventory mismatch %u/%u/%u/%u\n",unsigned(resetCases.size()),unsigned(loadCases.size()),unsigned(resetFaults.size()),unsigned(loadFaults.size()));return 1;}
 for(unsigned i=0;i<resetCases.size();++i)if(!pair(host,resetCoverage,resetCases[i],resetCount,resetUnwinds,originalFailures,candidateFailures))return 1;
 for(unsigned i=0;i<loadCases.size();++i)if(!pair(host,loadCoverage,loadCases[i],loadCount,loadUnwinds,originalFailures,candidateFailures))return 1;
 for(unsigned i=0;i<resetFaults.size();++i)if(!pair(host,resetCoverage,resetFaults[i],resetCount,resetUnwinds,originalFailures,candidateFailures))return 1;
 for(unsigned i=0;i<loadFaults.size();++i)if(!pair(host,loadCoverage,loadFaults[i],loadCount,loadUnwinds,originalFailures,candidateFailures))return 1;
 if(resetCoverage.completed)resetCoverage.report(host);if(loadCoverage.completed)loadCoverage.report(host);host->log("    state: reset=%u load=%u direct completed pairs; excluded unwinds=%u/%u; original/candidate oracle failures=%u/%u. Recursive origin checks supplement direct counters.\n",resetCount,loadCount,resetUnwinds,loadUnwinds,originalFailures,candidateFailures);
 return resetCount!=104||loadCount!=225||resetUnwinds!=10||loadUnwinds!=26||resetCoverage.completed!=resetCount||loadCoverage.completed!=loadCount||resetCoverage.different||loadCoverage.different||resetCoverage.missing||loadCoverage.missing||originalFailures||candidateFailures;
}
