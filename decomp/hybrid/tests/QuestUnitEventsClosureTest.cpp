// Draft comparative tests for original ELF 91b41ae9...174b. No runtime claim.
// Only unitInteracted and spawnChildrenUnits receive direct comparison credit.
// Genuine BaseUnit/ResourceManager/QUD construction; direct-original ISA,
// position, randomOpenPosition and spawnUnit forwarding. Bounded lower world
// contracts are explicit. No Character header, world engine or helper credit.
#include <cstdio>
#include <cstring>
#include <new>
#include <string>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#include "Quest.h"
#include "QuestUnitData.h"
#include "TRepository.h"

TL_ORIGINAL(bool,qeOldInteraction,(CQuestUnitData*,CBaseUnit*),"_ZN14CQuestUnitData14unitInteractedEP9CBaseUnit")
extern "C" bool qeNewInteraction(CQuestUnitData*,CBaseUnit*) __asm__("_ZN14CQuestUnitData14unitInteractedEP9CBaseUnit");
TL_FUNCTION(qeInteraction,"_ZN14CQuestUnitData14unitInteractedEP9CBaseUnit")
TL_ORIGINAL(void,qeOldChildren,(CQuestUnitData*,CResourceManager*,const Ogre::Vector3&),"_ZN14CQuestUnitData18spawnChildrenUnitsEP16CResourceManagerRKN4Ogre7Vector3E")
extern "C" void qeNewChildren(CQuestUnitData*,CResourceManager*,const Ogre::Vector3&) __asm__("_ZN14CQuestUnitData18spawnChildrenUnitsEP16CResourceManagerRKN4Ogre7Vector3E");
TL_FUNCTION(qeChildren,"_ZN14CQuestUnitData18spawnChildrenUnitsEP16CResourceManagerRKN4Ogre7Vector3E")
TL_ORIGINAL(void,qeRecordCtor,(void*,void*),"_ZN14CQuestUnitDataC1EP6CQuest")
TL_ORIGINAL(void,qeRecordDtor,(void*),"_ZN14CQuestUnitDataD1Ev")
TL_ORIGINAL(void,qeBaseCtor,(void*,void*,int),"_ZN9CBaseUnitC1EP16CResourceManager14EBASEUNIT_TYPE")
TL_ORIGINAL(void,qeResourceCtor,(void*,void*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,qeResourceDtor,(void*),"_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void,qeGroupCtor,(void*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,qeGroupDtor,(void*),"_ZN10CDataGroupD1Ev")
#define QE_DEP(R,N,A,S) TL_ORIGINAL(R,qeOriginal##N,A,S) TL_FUNCTION(qeBoundary##N,S)
QE_DEP(bool,ISA,(CBaseUnit*,int),"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
QE_DEP(Ogre::Vector3,Position,(CBaseUnit*,bool),"_ZN19CPositionableObject11getPositionEb")
QE_DEP(Ogre::Vector3,Random,(CLevel*,const Ogre::Vector3&,float,bool),"_ZN6CLevel18randomOpenPositionERKN4Ogre7Vector3Efb")
QE_DEP(CBaseUnit*,Spawn,(CQuestUnitData*,CResourceManager*,const Ogre::Vector3&),"_ZN14CQuestUnitData9spawnUnitEP16CResourceManagerRKN4Ogre7Vector3E")
#undef QE_DEP
TL_FUNCTION(qeLookup,"_ZN14CQuestUnitData20getBaseUnitDataGroupEv")
TL_FUNCTION(qeResourceISA,"_ZN16CResourceManager3ISAEN9UNITTYPES10EUNITTYPESES1_")
TL_FUNCTION(qeRange,"_ZN6CLevel23randomOpenPositionRangeERKN4Ogre7Vector3Effb")
TL_FUNCTION(qeCreate,"_ZN16CResourceManager10createUnitEP10CDataGroupibb")
TL_FUNCTION(qeAdd,"_ZN6CLevel7addUnitEP9CBaseUnitRKN4Ogre7Vector3E")
TL_FUNCTION(qeMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(qeGuid,"_ZN9UTILITIES16createUniqueGuidEv")

namespace qe {
typedef std::wstring Wide;
enum { MaxNodes=7, MaxChildren=6 };
typedef char ABI[sizeof(Wide)==8&&sizeof(wchar_t)==4&&sizeof(CBaseUnit)==0x1d8&&sizeof(CQuestUnitData)==0xc8&&sizeof(CResourceManager)==0x48?1:-1];
enum Code { Lookup=1,ISA,Position,Children,Random,Range,Spawn,Create,Add };
enum Mode { Plain=0,ReloadType,ReloadResource,ShrinkCount,GrowCount,ReloadCapacity,
            SlotBeforeSpawn,SlotAfterSpawn,CapacityAfterSecondSpawn,LevelAfterRange,InputAfterRange };
struct Node {
 unsigned cache,lookup,type,current,required,count,capacity,edge[MaxChildren];
 bool track,complete,quest,createNull,champion;
 Node():cache(1),lookup(1),type(22),current(0),required(2),count(0),capacity(0),track(false),complete(false),quest(true),createNull(false),champion(false){for(unsigned i=0;i<MaxChildren;++i)edge[i]=i+1;}
};
struct Case {
 Node node[MaxNodes];unsigned kind,total,resource,association,unitGroup,mode,repeats,fault,occurrence;
 bool nullUnit,matchISA,otherISA;
 Case():kind(0),total(1),resource(2),association(0),unitGroup(1),mode(Plain),repeats(1),fault(0),occurrence(1),nullUnit(false),matchISA(false),otherISA(false){}
};
struct Stop {unsigned code;explicit Stop(unsigned c):code(c){}};
struct Event {unsigned code,id,arg;float scalar;Ogre::Vector3 vector;Node state[MaxNodes];unsigned unitState[MaxNodes];unsigned long long unitGuid[MaxNodes];};
struct Block {unsigned char*p;unsigned size;};
static const Case* cs;static autotest::Capture* cap;
static CQuestUnitData* node[MaxNodes];static CBaseUnit* unit[MaxNodes];
static CDataGroup* group[2];static CResourceManager* resource[2];static CLevel* level[2];static CQuest* quest;
static Block blocks[24];static unsigned blockCount;
static unsigned char nodeBefore[MaxNodes][0xc8],unitBefore[MaxNodes][0x1d8],resourceBefore[2][0x48],levelBefore[2][0x2f0],questBefore[0x218];
static Node model[MaxNodes];static unsigned modelUnitState[MaxNodes];static unsigned long long modelUnitGuid[MaxNodes];
static std::vector<Event> wanted;static unsigned eventIndex,errors,firstError,seenFault,expectedFault,faultHits;
static unsigned isaCalls,modelISAs,randomCalls,spawnCalls,activeNode,modelResource,modelLevel;
static Ogre::Vector3 input,modelInput;
static detour::Set *pISA,*pPosition,*pRandom,*pSpawn;
template<class T>T& at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
static void check(bool ok,unsigned line){if(!ok){if(!errors)firstError=line;++errors;}}
#define NEED(x) check((x),__LINE__)
static void n(unsigned x){cap->add(&x,sizeof(x));}
static unsigned id(const void*p){for(unsigned i=0;i<cs->total;++i)if(p==node[i])return i;return 99;}
static unsigned uid(const void*p){for(unsigned i=0;i<cs->total;++i)if(p==unit[i])return i;return 99;}
static unsigned gid(const void*p){return p==group[0]?1:p==group[1]?2:p==0?0:99;}
static unsigned rid(const void*p){return p==resource[0]?1:p==resource[1]?2:p==0?0:99;}
static unsigned lid(const void*p){return p==level[0]?0:p==level[1]?1:99;}
static void* raw(unsigned size){
 if(blockCount>=24){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}
 unsigned char*p=static_cast<unsigned char*>(autotest::allocate(size+32));
 if(!p){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}
 std::memset(p,0xa6,16);std::memset(p+16,0,size);std::memset(p+16+size,0x6a,16);
 blocks[blockCount].p=p+16;blocks[blockCount++].size=size;return p+16;
}
static Ogre::Vector3 position(){return Ogre::Vector3(3.25f,-4.5f,7.75f);}
static Ogre::Vector3 changedInput(){return Ogre::Vector3(-8.0f,16.25f,32.5f);}
static Ogre::Vector3 randomResult(unsigned index){return Ogre::Vector3(10.25f+index,-20.5f-index,30.75f+2*index);}
static unsigned recordId(unsigned index){return cs->kind?17+index:17;}
static unsigned long long questGuid(){return 0x1357246813572468ULL;}
static bool membership(unsigned type){return type==31?cs->otherISA:cs->matchISA;}
static void append(unsigned code,unsigned index,unsigned arg=0,float scalar=0,const Ogre::Vector3& vector=Ogre::Vector3(0,0,0)){
 Event e;e.code=code;e.id=index;e.arg=arg;e.scalar=scalar;e.vector=vector;
 for(unsigned i=0;i<cs->total;++i){e.state[i]=model[i];e.unitState[i]=modelUnitState[i];e.unitGuid[i]=modelUnitGuid[i];}wanted.push_back(e);
 if(cs->fault==code&&++expectedFault==cs->occurrence)throw Stop(code);
}
static void modelListMutation(unsigned where,unsigned occurrence){
 if(cs->kind==0&&where==Lookup&&occurrence==1){
  if(cs->mode==ShrinkCount)model[0].count=1;
  if(cs->mode==GrowCount)model[0].count=3;
  if(cs->mode==ReloadCapacity)model[0].capacity=1;
 }
 if(cs->kind==1&&where==Range&&occurrence==1){
  if(cs->mode==SlotBeforeSpawn)model[0].edge[0]=2;
  if(cs->mode==LevelAfterRange)modelLevel=1;
  if(cs->mode==InputAfterRange)modelInput=changedInput();
 }
 if(cs->kind==1&&where==Spawn&&occurrence==1){
  if(cs->mode==SlotAfterSpawn)model[0].edge[0]=2;
  if(cs->mode==ShrinkCount)model[0].count=1;
  if(cs->mode==GrowCount)model[0].count=6;
  if(cs->mode==ReloadCapacity)model[0].capacity=1;
 }
 if(cs->kind==1&&where==Spawn&&occurrence==2&&cs->mode==CapacityAfterSecondSpawn)model[0].capacity=1;
}
static bool modelISA(unsigned index,unsigned type){append(ISA,index,type);++modelISAs;bool result=modelResource&&membership(type);if(cs->mode==ReloadType&&modelISAs==1)model[0].type=31;return result;}
static bool simulateInteraction(unsigned index,unsigned depth){
 NEED(index<cs->total&&depth<MaxNodes);if(index>=cs->total||depth>=MaxNodes)return false;
 if(cs->nullUnit||cs->resource<2)return false;Node& x=model[index];
 if(!x.cache){append(Lookup,index);if(index==1)modelListMutation(Lookup,1);x.cache=x.lookup;}
 bool primary=x.cache==cs->unitGroup;if(!primary)primary=modelISA(index,x.type);
 bool associated=x.type!=22&&modelISA(index,x.type);
 if(!associated){NEED(x.quest);associated=cs->association==1;}
 if(!x.complete&&primary){
  ++x.current;
  if(x.current>=x.required){append(Position,index,1,0,position());if(cs->mode==ReloadResource)modelResource=2;append(Children,index,modelResource,0,position());x.complete=true;return true;}
 }else if(x.complete&&!associated&&x.count){
  for(unsigned i=0;i<x.count&&i<MaxChildren;++i){unsigned child=x.edge[i<x.capacity?i:0];if(simulateInteraction(child,depth+1))return true;}
 }
 return false;
}
static void simulateChildren(){
 if(cs->resource<2||!model[0].count)return;
 for(unsigned i=0;i<model[0].count&&i<MaxChildren;++i){
  float radius=i<3?1.0f:float(i)*0.5f;
  append(Random,0,0,radius,modelInput);append(Range,0,0,radius,modelInput);modelListMutation(Range,i+1);
  Ogre::Vector3 v=randomResult(i);v.y+=1.5f;
  unsigned child=model[0].edge[i<model[0].capacity?i:0];Node& x=model[child];
  append(Spawn,child,1,0,v);
  if(x.cache&&!x.complete){append(Create,child,modelLevel,0,v);if(!x.createNull){append(Add,child,modelLevel,0,v);modelUnitState[child]=recordId(child);modelUnitGuid[child]=questGuid();}}
  modelListMutation(Spawn,i+1);child=model[0].edge[i<model[0].capacity?i:0];model[child].track=true;
 }
}
static void snapshot(const Event* e){
 for(unsigned i=0;i<cs->total;++i){
  Node a;a.cache=gid(node[i]->m_pBaseUnitDataGroup);a.type=at<unsigned>(node[i],0x44);a.current=at<unsigned>(node[i],0x3c);a.required=at<unsigned>(node[i],0x38);a.count=at<unsigned>(node[i],0x50);a.capacity=at<unsigned>(node[i],0x54);a.complete=node[i]->m_completed;a.track=node[i]->m_trackUnitEvents;
  n(a.cache);n(a.type);n(a.current);n(a.required);n(a.count);n(a.capacity);n(a.complete);n(a.track);
  const Node* z=e?&e->state[i]:0;
  if(z){NEED(a.cache==z->cache);NEED(a.type==z->type);NEED(a.current==z->current);NEED(a.required==z->required);NEED(a.count==z->count);NEED(a.capacity==z->capacity);NEED(a.complete==z->complete);NEED(a.track==z->track);}
  if(cs->node[i].capacity){CQuestUnitData**data=at<CQuestUnitData**>(node[i],0x48);for(unsigned j=0;j<MaxChildren;++j){unsigned selected=id(data[j]);n(selected);if(z)NEED(selected==z->edge[j]);}}
  unsigned state=at<unsigned>(unit[i],0x178);unsigned long long guid=at<unsigned long long>(unit[i],0x170);n(state);cap->add(&guid,sizeof(guid));
  if(e){NEED(state==e->unitState[i]);NEED(guid==e->unitGuid[i]);}
 }
}
static void finalSnapshot(){Event e;for(unsigned i=0;i<cs->total;++i){e.state[i]=model[i];e.unitState[i]=modelUnitState[i];e.unitGuid[i]=modelUnitGuid[i];}snapshot(&e);}
static unsigned expectedOwner(unsigned code){if(eventIndex<wanted.size()&&wanted[eventIndex].code==code)return wanted[eventIndex].id;NEED(false);return 0;}
static void emit(unsigned code,unsigned index,unsigned arg=0,float scalar=0,const Ogre::Vector3& vector=Ogre::Vector3(0,0,0)){
 n(code);n(index);n(arg);cap->add(&scalar,sizeof(scalar));cap->add(&vector,sizeof(vector));NEED(eventIndex<wanted.size());
 if(eventIndex<wanted.size()){const Event&e=wanted[eventIndex];NEED(e.code==code);NEED(e.id==index);NEED(e.arg==arg);NEED(e.scalar==scalar);NEED(e.vector==vector);snapshot(&e);}else snapshot(0);
 ++eventIndex;if(cs->fault==code&&++seenFault==cs->occurrence){++faultHits;throw Stop(code);}
}
static void* noMaster(){return 0;}static unsigned long long constantGuid(){return 0x54667788ULL;}
static bool lowerISA(void*p,unsigned type,unsigned parent){NEED(p==resource[0]||p==resource[1]);NEED(type==27);return membership(parent);}
static void actualListMutation(unsigned where,unsigned occurrence){
 if(cs->kind==0&&where==Lookup&&occurrence==1){if(cs->mode==ShrinkCount)at<unsigned>(node[0],0x50)=1;if(cs->mode==GrowCount)at<unsigned>(node[0],0x50)=3;if(cs->mode==ReloadCapacity)at<unsigned>(node[0],0x54)=1;}
 if(cs->kind==1&&where==Range&&occurrence==1){if(cs->mode==SlotBeforeSpawn)at<CQuestUnitData**>(node[0],0x48)[0]=node[2];if(cs->mode==LevelAfterRange)at<CLevel*>(resource[0],0x18)=level[1];if(cs->mode==InputAfterRange)input=changedInput();}
 if(cs->kind==1&&where==Spawn&&occurrence==1){if(cs->mode==SlotAfterSpawn)at<CQuestUnitData**>(node[0],0x48)[0]=node[2];if(cs->mode==ShrinkCount)at<unsigned>(node[0],0x50)=1;if(cs->mode==GrowCount)at<unsigned>(node[0],0x50)=6;if(cs->mode==ReloadCapacity)at<unsigned>(node[0],0x54)=1;}
 if(cs->kind==1&&where==Spawn&&occurrence==2&&cs->mode==CapacityAfterSecondSpawn)at<unsigned>(node[0],0x54)=1;
}
static CDataGroup* lookup(CQuestUnitData*p){unsigned index=id(p);emit(Lookup,index);if(index>=cs->total)return 0;if(index==1)actualListMutation(Lookup,1);unsigned g=cs->node[index].lookup;return g?group[g-1]:0;}
static bool callISA(CBaseUnit*p,int type){unsigned index=expectedOwner(ISA);emit(ISA,index,static_cast<unsigned>(type));NEED(p==unit[0]);if(p!=unit[0])return false;
 ++isaCalls;pISA->restore();bool result=false;try{result=qeOriginalISA(p,type);}catch(...){TL_REDIRECT(*pISA,qeBoundaryISA,&callISA);throw;}TL_REDIRECT(*pISA,qeBoundaryISA,&callISA);
 NEED(result==(at<void*>(p,0x68)!=0&&membership(type)));if(cs->mode==ReloadType&&isaCalls==1)node[0]->m_unitType=31;return result;
}
static Ogre::Vector3 callPosition(CBaseUnit*p,bool absolute){unsigned index=expectedOwner(Position);emit(Position,index,absolute,0,position());NEED(p==unit[0]);if(p!=unit[0])return Ogre::Vector3(0,0,0);
 pPosition->restore();Ogre::Vector3 v;try{v=qeOriginalPosition(p,absolute);}catch(...){TL_REDIRECT(*pPosition,qeBoundaryPosition,&callPosition);throw;}TL_REDIRECT(*pPosition,qeBoundaryPosition,&callPosition);NEED(v==position());cap->add(&v,sizeof(v));
 if(cs->mode==ReloadResource)at<void*>(p,0x68)=resource[1];return v;
}
static void observeChildren(CQuestUnitData*p,CResourceManager*r,const Ogre::Vector3& v){unsigned index=id(p);emit(Children,index,rid(r),0,v);NEED(index<cs->total);if(index<cs->total)NEED(!node[index]->m_completed);}
static Ogre::Vector3 lowerRange(CLevel*p,const Ogre::Vector3& v,float minimum,float maximum,bool flag){emit(Range,lid(p),flag,maximum,v);NEED(minimum==0.0f);NEED(&v==&input);unsigned which=randomCalls?randomCalls-1:0;actualListMutation(Range,randomCalls);return randomResult(which);}
static Ogre::Vector3 callRandom(CLevel*p,const Ogre::Vector3& v,float radius,bool flag){emit(Random,lid(p),flag,radius,v);NEED(&v==&input);++randomCalls;pRandom->restore();Ogre::Vector3 result;
 try{result=qeOriginalRandom(p,v,radius,flag);}catch(...){TL_REDIRECT(*pRandom,qeBoundaryRandom,&callRandom);throw;}TL_REDIRECT(*pRandom,qeBoundaryRandom,&callRandom);NEED(result==randomResult(randomCalls-1));cap->add(&result,sizeof(result));return result;
}
static CBaseUnit* lowerCreate(CResourceManager*p,CDataGroup*g,int depth,bool first,bool second){unsigned index=activeNode;unsigned lev=lid(at<void*>(p,0x18));Ogre::Vector3 v=randomResult(randomCalls?randomCalls-1:0);v.y+=1.5f;
 emit(Create,index,lev,0,v);NEED(p==resource[0]);NEED(g==node[index]->m_pBaseUnitDataGroup);NEED(depth==(lev?53:29));NEED(!first&&!second);return cs->node[index].createNull?0:unit[index];
}
static void lowerAdd(CLevel*p,CBaseUnit*u,const Ogre::Vector3& v){unsigned index=activeNode;emit(Add,index,lid(p),0,v);NEED(u==unit[index]);NEED(p==at<void*>(resource[0],0x18));}
static CBaseUnit* callSpawn(CQuestUnitData*p,CResourceManager*r,const Ogre::Vector3& v){unsigned index=id(p);emit(Spawn,index,rid(r),0,v);NEED(index<cs->total);if(index>=cs->total)return 0;activeNode=index;++spawnCalls;
 pSpawn->restore();CBaseUnit* result=0;try{result=qeOriginalSpawn(p,r,v);}catch(...){TL_REDIRECT(*pSpawn,qeBoundarySpawn,&callSpawn);throw;}TL_REDIRECT(*pSpawn,qeBoundarySpawn,&callSpawn);
 bool produces=p->m_pBaseUnitDataGroup&&!p->m_completed&&!cs->node[index].createNull&&r&&at<void*>(r,0x18);NEED(result==(produces?unit[index]:0));n(result?uid(result)+1:0);actualListMutation(Spawn,spawnCalls);return result;
}
static void setup(){
 errors=firstError=eventIndex=blockCount=seenFault=expectedFault=faultHits=isaCalls=randomCalls=spawnCalls=activeNode=0;autotest::g_arenaUsed=0;
 ::new(reinterpret_cast<void*>(0x14ff1a8))Wide();
 for(unsigned i=0;i<2;++i){TRepository<Wide>*repo=new TRepository<Wide>(Wide());group[i]=static_cast<CDataGroup*>(raw(sizeof(CDataGroup)));qeGroupCtor(group[i],Wide(i?L"OTHER":L"EVENT"),0,4,4,repo);}
 {
  detour::Set environment;TL_REDIRECT(environment,qeMaster,&noMaster);TL_REDIRECT(environment,qeGuid,&constantGuid);
  if(environment.failed()){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}
  for(unsigned i=0;i<2;++i){resource[i]=static_cast<CResourceManager*>(raw(sizeof(CResourceManager)));qeResourceCtor(resource[i],0);}
  for(unsigned i=0;i<cs->total;++i){unit[i]=static_cast<CBaseUnit*>(raw(sizeof(CBaseUnit)));qeBaseCtor(unit[i],0,0);}
 }
 // Only the scalar quest GUID is accessed. No Quest constructor/destructor,
 // Requirements member, unconstructed string or owner lifetime is invoked.
 quest=static_cast<CQuest*>(raw(sizeof(CQuest)));at<unsigned long long>(quest,0x1c8)=questGuid();
 // Levels are explicit field/identity scaffolds, not genuine Level objects.
 // Real randomOpenPosition forwards identity to Range without dereferencing it;
 // real spawnUnit reads only the initialized depth before bounded world calls.
 for(unsigned i=0;i<2;++i){level[i]=static_cast<CLevel*>(raw(0x2f0));at<int>(level[i],0x1a8)=i?53:29;at<void*>(resource[i],0x18)=cs->resource==2?level[0]:0;}
 input=position();
 for(unsigned i=0;i<cs->total;++i){
  at<void*>(unit[i],0x68)=cs->resource?resource[0]:0;at<unsigned>(unit[i],0x1ac)=27;at<void*>(unit[i],0x1b0)=cs->unitGroup?group[cs->unitGroup-1]:0;at<Ogre::Vector3>(unit[i],0x84)=position();
  unsigned state=cs->kind?900+i:cs->association==1?17:cs->association==2?99:41;
  unsigned long long guid=cs->kind||cs->association==0?0x778899ULL:questGuid();at<unsigned>(unit[i],0x178)=state;at<unsigned long long>(unit[i],0x170)=guid;modelUnitState[i]=state;modelUnitGuid[i]=guid;
  node[i]=static_cast<CQuestUnitData*>(raw(sizeof(CQuestUnitData)));qeRecordCtor(node[i],cs->node[i].quest?quest:0);
  const Node&x=cs->node[i];node[i]->m_questUnitDataId=recordId(i);node[i]->m_baseUnitGuid=0x1122334400000063LL;
  node[i]->m_pBaseUnitDataGroup=x.cache?group[x.cache-1]:0;node[i]->m_pQuestDataGroup=group[1];node[i]->m_unitType=x.type;node[i]->m_spawnFromUnitType=30;node[i]->m_createUnit=true;
  node[i]->m_completed=x.complete;node[i]->m_trackUnitEvents=x.track;node[i]->m_makeChampion=x.champion;at<unsigned>(node[i],0x38)=x.required;at<unsigned>(node[i],0x3c)=x.current;
  node[i]->m_displayName=L"display survives";node[i]->m_generatedChampionName=L"generated survives";
 }
 for(unsigned i=0;i<cs->total;++i)if(cs->node[i].capacity){node[i]->m_children.setGrowBy(MaxChildren);for(unsigned j=0;j<MaxChildren;++j){unsigned selected=cs->node[i].edge[j];NEED(selected<cs->total);node[i]->m_children.add(node[selected]);}at<unsigned>(node[i],0x50)=cs->node[i].count;at<unsigned>(node[i],0x54)=cs->node[i].capacity;}
 for(unsigned i=0;i<cs->total;++i){std::memcpy(nodeBefore[i],node[i],0xc8);std::memcpy(unitBefore[i],unit[i],0x1d8);}
 for(unsigned i=0;i<2;++i){std::memcpy(resourceBefore[i],resource[i],0x48);std::memcpy(levelBefore[i],level[i],0x2f0);}std::memcpy(questBefore,quest,0x218);
}
static void checkUntouched(){
 for(unsigned i=0;i<cs->total;++i){const unsigned char*p=reinterpret_cast<const unsigned char*>(node[i]);for(unsigned j=0;j<0xc8;++j){bool change=cs->kind?j==0xb9:(j>=0x20&&j<0x28)||(j>=0x3c&&j<0x40)||j==0x60;
   if(i==0&&cs->mode==ReloadType&&j>=0x44&&j<0x48)change=true;
   if(i==0&&(cs->mode==ShrinkCount||cs->mode==GrowCount||cs->mode==ReloadCapacity||cs->mode==CapacityAfterSecondSpawn)&&j>=0x50&&j<0x58)change=true;
   if(!change)NEED(p[j]==nodeBefore[i][j]);}
  NEED(node[i]->m_displayName==L"display survives");NEED(node[i]->m_generatedChampionName==L"generated survives");
  p=reinterpret_cast<const unsigned char*>(unit[i]);for(unsigned j=0;j<0x1d8;++j){bool change=cs->kind&&(j>=0x170&&j<0x17c);if(!cs->kind&&i==0&&cs->mode==ReloadResource&&j>=0x68&&j<0x70)change=true;if(!change)NEED(p[j]==unitBefore[i][j]);}
 }
 for(unsigned i=0;i<2;++i){const unsigned char*p=reinterpret_cast<const unsigned char*>(resource[i]);for(unsigned j=0;j<0x48;++j){bool change=i==0&&cs->mode==LevelAfterRange&&j>=0x18&&j<0x20;if(!change)NEED(p[j]==resourceBefore[i][j]);}NEED(!std::memcmp(level[i],levelBefore[i],0x2f0));}
 NEED(!std::memcmp(quest,questBefore,0x218));NEED(input==modelInput);
 for(unsigned i=0;i<blockCount;++i)for(unsigned j=0;j<16;++j){NEED(blocks[i].p[int(j)-16]==0xa6);NEED(blocks[i].p[blocks[i].size+j]==0x6a);}
}
static void cleanup(){
 for(unsigned i=0;i<cs->total;++i)node[i]->m_children.clear();
 for(unsigned i=0;i<cs->total;++i)qeRecordDtor(node[i]);
 for(unsigned i=0;i<2;++i){qeGroupDtor(group[i]);at<void*>(resource[i],0x18)=0;qeResourceDtor(resource[i]);}
 // Original-constructed BaseUnits and their owned allocations survive until
 // the isolated fork exits. No fake teardown or heap/lifecycle equivalence.
 for(unsigned i=0;i<blockCount;++i)for(unsigned j=0;j<16;++j){NEED(blocks[i].p[int(j)-16]==0xa6);NEED(blocks[i].p[blocks[i].size+j]==0x6a);}
}
static void side(void* context,autotest::Capture&out,bool candidate){
 cs=static_cast<Case*>(context);cap=&out;setup();wanted.clear();modelISAs=0;modelResource=cs->resource?1:0;modelLevel=0;modelInput=input;for(unsigned i=0;i<cs->total;++i)model[i]=cs->node[i];
 unsigned predictedCaught=0;bool result[2]={false,false};try{if(cs->kind)simulateChildren();else for(unsigned i=0;i<cs->repeats;++i)result[i]=simulateInteraction(0,0);}catch(const Stop&s){predictedCaught=s.code;}NEED(predictedCaught==cs->fault);
 {
  detour::Set isa,position,random,spawn,contracts,route;pISA=&isa;pPosition=&position;pRandom=&random;pSpawn=&spawn;
  if(cs->kind){TL_REDIRECT(random,qeBoundaryRandom,&callRandom);TL_REDIRECT(spawn,qeBoundarySpawn,&callSpawn);TL_REDIRECT(contracts,qeRange,&lowerRange);TL_REDIRECT(contracts,qeCreate,&lowerCreate);TL_REDIRECT(contracts,qeAdd,&lowerAdd);}
  else{TL_REDIRECT(isa,qeBoundaryISA,&callISA);TL_REDIRECT(position,qeBoundaryPosition,&callPosition);TL_REDIRECT(contracts,qeLookup,&lookup);TL_REDIRECT(contracts,qeResourceISA,&lowerISA);TL_REDIRECT(contracts,qeChildren,&observeChildren);if(candidate)route.redirect(qeInteraction_original,qeInteraction_original,&qeNewInteraction);}
  if(isa.failed()||position.failed()||random.failed()||spawn.failed()||contracts.failed()||route.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  unsigned caught=0;
  if(cs->kind){typedef void(*Fn)(CQuestUnitData*,CResourceManager*,const Ogre::Vector3&);Fn fn=candidate?&qeNewChildren:&qeOldChildren;if(!autotest::beginInvocation(out,fn))return;try{fn(node[0],cs->resource?resource[0]:0,input);}catch(const Stop&s){caught=s.code;}catch(...){caught=999;NEED(false);}}
  else{typedef bool(*Fn)(CQuestUnitData*,CBaseUnit*);Fn fn=candidate?&qeNewInteraction:&qeOldInteraction;if(!autotest::beginInvocation(out,fn))return;try{for(unsigned i=0;i<cs->repeats;++i){bool actual=fn(node[0],cs->nullUnit?0:unit[0]);n(actual);NEED(actual==result[i]);}}catch(const Stop&s){caught=s.code;}catch(...){caught=999;NEED(false);}}
  n(caught);NEED(caught==predictedCaught);NEED(faultHits==(cs->fault?1u:0u));NEED(eventIndex==wanted.size());finalSnapshot();if(!caught)out.callCompleted=1;
  NEED(!isa.failed()&&!position.failed()&&!random.failed()&&!spawn.failed()&&!contracts.failed()&&!route.failed());
 }
 checkUntouched();cleanup();n(firstError);n(0x51454556u);n(errors);
}
static void oldSide(void*p,autotest::Capture&o){side(p,o,false);}static void newSide(void*p,autotest::Capture&o){side(p,o,true);}
static bool oracle(const autotest::Outcome&o){unsigned t[2]={0,1};if(o.capture.length>=8)std::memcpy(t,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&t[0]==0x51454556u&&!t[1];}
static unsigned failureLine(const autotest::Outcome&o){unsigned line=0;if(o.capture.length>=12)std::memcpy(&line,o.capture.data+o.capture.length-12,4);return line;}
static bool pair(const tlhybrid_host*host,autotest::Coverage&coverage,Case&c,unsigned&completed,unsigned&unwinds,unsigned&originalFailures,unsigned&candidateFailures){
 autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);bool oa=oracle(a),ob=oracle(b);if(!oa)++originalFailures;if(!ob)++candidateFailures;bool ok;
 if(c.fault){++unwinds;ok=oa&&ob&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==(c.kind?0xd3e050u:0xd48d00u)&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);}
 else{++completed;ok=coverage.observe(host,a,b)==0&&oa&&ob;}
 if(!ok){host->log("    quest event kind=%u pair=%u/%u mode=%u fault=%u.%u nodes=%u status=%d/%d oracle=%u/%u line=%u/%u\n",c.kind,completed,unwinds,c.mode,c.fault,c.occurrence,c.total,a.childStatus,b.childStatus,oa,ob,failureLine(a),failureLine(b));coverage.report(host);}return ok;
}
static Case tree(unsigned shape){Case c;c.total=4;c.node[0].complete=true;c.node[0].cache=2;c.node[0].count=3;c.node[0].capacity=6;for(unsigned j=0;j<MaxChildren;++j)c.node[0].edge[j]=1+j%3;
 for(unsigned i=1;i<4;++i){c.node[i].cache=0;c.node[i].lookup=1;c.node[i].required=7;}if(shape==0)c.node[0].count=0;if(shape>=2&&shape<=4)c.node[shape-1].required=1;if(shape==5)for(unsigned i=1;i<4;++i)c.node[i].lookup=2;return c;
}
static Case spawnCase(unsigned count){Case c;c.kind=1;c.total=7;c.node[0].count=count;c.node[0].capacity=6;return c;}
static int run(const tlhybrid_host*host,std::vector<Case>&normal,std::vector<Case>&faults,const char*name,unsigned address){autotest::Coverage coverage(name,address);unsigned completed=0,unwinds=0,originalFailures=0,candidateFailures=0;
 for(unsigned i=0;i<normal.size();++i)if(!pair(host,coverage,normal[i],completed,unwinds,originalFailures,candidateFailures))return 1;
 for(unsigned i=0;i<faults.size();++i)if(!pair(host,coverage,faults[i],completed,unwinds,originalFailures,candidateFailures))return 1;
 coverage.report(host);host->log("    %s: %u completed finite pairs; %u excluded unwinds; oracle failures original=%u candidate=%u; direct target=%#x only.\n",name,completed,unwinds,originalFailures,candidateFailures,address);
 return completed!=normal.size()||unwinds!=faults.size()||coverage.completed!=completed||coverage.different||coverage.missing||originalFailures||candidateFailures;
}
#undef NEED
}

TL_TEST(quest_unit_interacted_closure){using namespace qe;std::vector<Case> normal,faults;
 // Child-only unsigned witnesses are first: a signed-completion control must
 // fail in this recursive candidate body, not borrow a root-arithmetic kill.
 for(unsigned boundary=0;boundary<2;++boundary){Case c=tree(1);c.node[0].count=1;c.node[1].required=boundary?1u:0x80000000u;c.node[1].current=boundary?0x7fffffffu:0u;normal.push_back(c);}
 for(unsigned r=0;r<3;++r){Case c;c.resource=r;c.nullUnit=r==2;c.node[0].cache=0;normal.push_back(c);}
 for(unsigned layout=0;layout<6;++layout)for(unsigned isa=0;isa<2;++isa)for(unsigned sentinel=0;sentinel<2;++sentinel){Case c;c.matchISA=isa;c.node[0].type=sentinel?22:30;c.node[0].cache=layout<2?layout+1:0;c.node[0].lookup=layout==2?1:layout==3?2:0;c.unitGroup=layout==4?0:1;c.repeats=2;normal.push_back(c);}
 for(unsigned a=0;a<4;++a)for(unsigned complete=0;complete<2;++complete)for(unsigned primary=0;primary<2;++primary)for(unsigned sentinel=0;sentinel<2;++sentinel){Case c=tree(2);c.association=a;c.node[0].complete=complete;c.node[0].cache=primary?1:2;c.node[0].type=sentinel?22:30;c.node[0].required=1;normal.push_back(c);}
 const unsigned edges[]={0,1,2,0x7ffffffeu,0x7fffffffu,0x80000000u,0xfffffffeu,0xffffffffu};
 for(unsigned i=0;i<8;++i)for(unsigned j=0;j<8;++j){Case c;c.node[0].current=edges[i];c.node[0].required=edges[j];normal.push_back(c);}
 for(unsigned shape=0;shape<6;++shape){Case c=tree(shape);normal.push_back(c);}
 {Case c=tree(2);c.node[0].cache=1;normal.push_back(c);} // Completed matching but unassociated still descends.
 {Case c=tree(2);c.node[0].complete=false;normal.push_back(c);} // Incomplete nonmatch does not descend.
 for(unsigned track=0;track<2;++track){Case c;c.node[0].track=track;c.node[0].required=1;normal.push_back(c);} // Interaction has no tracking gate.
 {Case c=tree(2);c.node[0].type=30;c.matchISA=true;normal.push_back(c);} // Second-ISA association suppresses descent.
 {Case c=tree(2);c.node[0].type=30;c.node[0].cache=2;c.otherISA=true;c.mode=ReloadType;normal.push_back(c);}
 {Case c;c.node[0].required=1;c.mode=ReloadResource;normal.push_back(c);}
 for(unsigned mode=ShrinkCount;mode<=ReloadCapacity;++mode){Case c=tree(1);c.mode=mode;if(mode==GrowCount)c.node[0].count=1;normal.push_back(c);}
 // Extra finite level of recursion: root -> completed child -> grandchild.
 {Case c=tree(1);c.node[0].count=1;c.node[1].complete=true;c.node[1].lookup=2;c.node[1].count=1;c.node[1].capacity=6;for(unsigned j=0;j<MaxChildren;++j)c.node[1].edge[j]=2;c.node[2].required=1;normal.push_back(c);}
 const unsigned codes[]={Lookup,ISA,Position,Children};for(unsigned i=0;i<4;++i){Case c;c.node[0].cache=0;c.node[0].lookup=2;c.matchISA=true;c.node[0].type=30;c.node[0].required=1;c.fault=codes[i];faults.push_back(c);}
 {Case c;c.node[0].cache=2;c.node[0].type=30;c.matchISA=true;c.fault=ISA;c.occurrence=2;faults.push_back(c);}
 return run(host,normal,faults,"quest_unit_interacted_closure",0xd48d00);
}

TL_TEST(quest_unit_spawn_children_closure){using namespace qe;std::vector<Case> normal,faults;
 for(unsigned r=0;r<2;++r){Case c=spawnCase(6);c.resource=r;normal.push_back(c);}
 for(unsigned count=0;count<=6;++count){Case c=spawnCase(count);normal.push_back(c);}
 for(unsigned mode=0;mode<4;++mode)for(unsigned track=0;track<2;++track){Case c=spawnCase(6);for(unsigned i=1;i<7;++i){c.node[i].track=track;if(mode==0)c.node[i].cache=0;if(mode==1)c.node[i].complete=true;if(mode==2)c.node[i].createNull=true;if(mode==3)c.node[i].champion=true;}normal.push_back(c);}
 {Case c=spawnCase(6);for(unsigned i=1;i<7;++i){c.node[i].cache=i%2?0:1;c.node[i].complete=i==4;c.node[i].createNull=i==6;c.node[i].track=i%2;}normal.push_back(c);}
 for(unsigned mode=ShrinkCount;mode<=InputAfterRange;++mode){Case c=spawnCase(6);c.mode=mode;if(mode==GrowCount)c.node[0].count=1;normal.push_back(c);}
 // Repeated child identities and bounded operator[] fallback, with all six
 // allocated backing entries live. Count > advertised capacity is deliberate.
 {Case c=spawnCase(6);for(unsigned j=0;j<6;++j)c.node[0].edge[j]=j%2+1;normal.push_back(c);}
 {Case c=spawnCase(6);c.node[0].capacity=1;normal.push_back(c);}
 const unsigned codes[]={Random,Range,Spawn,Create,Add};for(unsigned i=0;i<5;++i)for(unsigned occurrence=1;occurrence<=2;++occurrence){Case c=spawnCase(6);c.fault=codes[i];c.occurrence=occurrence;faults.push_back(c);}
 return run(host,normal,faults,"quest_unit_spawn_children_closure",0xd3e050);
}
