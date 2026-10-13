// Independent finite ASM oracle: populate d48ea0..d493c5 (1317 bytes).
// Original-bound helpers receive no new acceptance credit. D0 is an explicit
// retained-storage dispatch contract, never a destructor on arena ownership.
#include <cstdio>
#include <cstring>
#include <map>
#include <new>
#include <string>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#include "Quest.h"
#include "QuestManager.h"
#include "QuestUnitData.h"
#include "PropertyNode.h"
#include "Equipment.h"
#include "TRepository.h"
TL_ORIGINAL(void,qpOld,(CQuestUnitData*,CLevel*),"_ZN14CQuestUnitData8populateEP6CLevel")
extern "C" void qpNew(CQuestUnitData*,CLevel*) __asm__("_ZN14CQuestUnitData8populateEP6CLevel");
TL_ORIGINAL(void,qpRecordCtor,(void*,void*),"_ZN14CQuestUnitDataC1EP6CQuest")
TL_ORIGINAL(void,qpRecordDtor,(void*),"_ZN14CQuestUnitDataD1Ev")
TL_ORIGINAL(void,qpPropertyCtor,(void*,void*),"_ZN13CPropertyNodeC1EP16CResourceManager")
TL_ORIGINAL(void,qpBaseCtor,(void*,void*,int),"_ZN9CBaseUnitC1EP16CResourceManager14EBASEUNIT_TYPE")
TL_ORIGINAL(void,qpCharacterCtor,(void*,void*),"_ZN10CCharacterC1EP16CResourceManager")
TL_ORIGINAL(void,qpItemCtor,(void*,void*),"_ZN5CItemC1EP16CResourceManager")
TL_ORIGINAL(void,qpEquipmentCtor,(void*,void*),"_ZN10CEquipmentC1EP16CResourceManager")
TL_ORIGINAL(void,qpResourceCtor,(void*,void*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,qpResourceDtor,(void*),"_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void,qpGroupCtor,(void*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,qpGroupDtor,(void*),"_ZN10CDataGroupD1Ev")
#define QP_DEP(R,N,A,S) TL_ORIGINAL(R,qpOriginal##N,A,S) TL_FUNCTION(qpBoundary##N,S)
QP_DEP(CDataGroup*,Resolve,(CQuestUnitData*),"_ZN14CQuestUnitData20getBaseUnitDataGroupEv")
QP_DEP(char,Complete,(CQuestManager*,const std::wstring&),"_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE")
QP_DEP(CBaseUnit*,Lookup,(CLevel*,CDataGroup*),"_ZN6CLevel22getBaseUnitByDataGroupEP10CDataGroup")
QP_DEP(void,Remove,(CLevel*,CBaseUnit*,bool),"_ZN6CLevel10removeUnitEP9CBaseUnitb")
QP_DEP(CPositionableObject*,Create,(CQuestUnitData*,CLevel*),"_ZN14CQuestUnitData10createUnitEP6CLevel")
QP_DEP(void,Enumerate,(CLevel*,int,TArrayList<CBaseUnit*>&),"_ZN6CLevel18getUnitsByUnitTypeEN9UNITTYPES10EUNITTYPESER10TArrayListIP9CBaseUnitE")
QP_DEP(long long,NPC,(CQuestManager*,CCharacter*),"_ZN13CQuestManager16calculateNPCIconEP10CCharacter")
QP_DEP(void,Text,(CItem*),"_ZN5CItem15destroyItemTextEv")
QP_DEP(std::string,Narrow,(const wchar_t*),"_ZN7STRINGS21StringConvertToNarrowEPKw")
#undef QP_DEP
TL_FUNCTION(qpSpawnClass,"_ZN14CQuestUnitData31getSpawnClassUnitDataLookingForEv")
TL_FUNCTION(qpGroupGuid,"_ZN16CResourceManager22getUnitGuidByDataGroupEP10CDataGroupRKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qpByGuid,"_ZN16CResourceManager17getUnitDataByGuidEx")
TL_FUNCTION(qpInteger,"_ZN9UTILITIES20randomIntegerBetweenEii")
TL_FUNCTION(qpFloat,"_ZN9UTILITIES13randomBetweenEff")
TL_FUNCTION(qpResourceCreate,"_ZN16CResourceManager10createUnitEP10CDataGroupibb")
TL_FUNCTION(qpAdd,"_ZN6CLevel7addUnitEP9CBaseUnitRKN4Ogre7Vector3E")
TL_FUNCTION(qpRemoveCharacter,"_ZN6CLevel15removeCharacterEP10CCharacterb")
TL_FUNCTION(qpRemoveItem,"_ZN6CLevel10removeItemEP5CItemb")
TL_FUNCTION(qpDeleteCharacter,"_ZN10CCharacterD0Ev")
TL_FUNCTION(qpDeleteItem,"_ZN5CItemD0Ev")
TL_FUNCTION(qpDeleteEquipment,"_ZN10CEquipmentD0Ev")
TL_FUNCTION(qpDeleteBase,"_ZN9CBaseUnitD0Ev")
TL_FUNCTION(qpISA,"_ZN16CResourceManager3ISAEN9UNITTYPES10EUNITTYPESES1_")
TL_FUNCTION(qpScale,"_ZN13CPropertyNode12scaleUpdatedERKN4Ogre7Vector3E")
TL_FUNCTION(qpMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(qpGuid,"_ZN9UTILITIES16createUniqueGuidEv")
extern "C" char qpArrayDelete[] __asm__("_ZdaPv");
extern "C" char qpLogSingleton[] __asm__("_ZN4Ogre10LogManager12getSingletonEv");
extern "C" char qpLogMessage[] __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
namespace qp {
typedef std::wstring Wide;typedef std::map<Wide,bool> CompleteMap;
typedef TArrayList<CBaseUnit*> Units;typedef TArrayList<CPropertyNode*> Properties;
typedef TLinkedList<CCharacter*> Characters;typedef TLinkedList<CItem*> Items;
typedef TLinkedListNode<CCharacter*> CharacterNode;typedef TLinkedListNode<CItem*> ItemNode;
enum {UnitSize=0x778,LevelSize=0x2f0,MaxEvents=96,Null=100};
typedef char ABI[sizeof(Wide)==8&&sizeof(wchar_t)==4&&sizeof(CompleteMap)==48&&sizeof(CQuestUnitData)==0xc8&&sizeof(CQuest)==0x218&&sizeof(CPropertyNode)==0x158&&sizeof(CCharacter)==UnitSize&&sizeof(CItem)==0x230&&sizeof(CEquipment)==0x438&&sizeof(CResourceManager)==0x48?1:-1];
enum Code {Resolve=1,SpawnClass,GroupGuid,Complete,Lookup,Remove,Detach,Delete,Create,FloatRng,ResourceCreate,Add,Enumerate,IntegerRng,NPC,Text,Narrow,Singleton,Log,ByGuid};
enum Mode {Plain=0,QuestAfterResolve,TypesAfterResolve,NeverAfterResolve,AcceptAfterComplete,QuestAfterComplete,NeverAfterComplete,CacheAfterComplete,QuestAfterLookup,AcceptAfterRemove,AcceptAfterDelete,TrackAfterDelete,CountGrow,CountShrink,CountUnsigned,QuestAfterCreate,QuestAfterEnumerate,QuestAfterRng,CapacityAfterRng,CountAfterRng,SlotAfterRng,GuidAfterRng,ManagerAfterRng,QuestAfterNPC,ClearAfterText,QuestAfterNarrow};
struct Case {
 int base,relative,specific,depth,dungeonDepth,selection;
 unsigned questDungeon,levelDungeon,name,route,success,complete,world,matching,enumeration,sentinels,required,type,from,mode,fault,occurrence,createResult;
 bool create,accepted,completed,tracking,neverDestroy,nullLevel;
 Case():base(7),relative(0),specific(-1),depth(7),dungeonDepth(91),selection(0),questDungeon(1),levelDungeon(1),name(0),route(0),success(1),complete(0),world(7),matching(7),enumeration(7),sentinels(0),required(2),type(22),from(0),mode(Plain),fault(0),occurrence(1),createResult(1),create(true),accepted(true),completed(false),tracking(false),neverDestroy(false),nullLevel(false){}
};
struct Stop {unsigned code;explicit Stop(unsigned c):code(c){}};
struct State {
 unsigned quest,cache,create,completed,tracking,neverDestroy,type,from,required,accepted[2],manager[2],world,deleted;
 unsigned unitState[4],identified,orientation,tempCount,tempCapacity,tempSlots[10];
 unsigned long long baseGuid,unitGuid[4];bool tempLive;
};
struct Event {unsigned code,id,arg,extra;State state;std::string text;};
struct Block {unsigned char*p;unsigned size;};
struct MapNode {void*p;unsigned char bytes[48];};
static const Case*cs;static autotest::Capture*cap;static State model;static std::vector<Event>wanted;
static CQuestUnitData*record;static CQuest*quest[2];static CQuestManager*manager[2];static CResourceManager*resource[2];static CLevel*level[2];static CDataGroup*group[2];static CBaseUnit*unit[4];static CPropertyNode*property;
static Characters*characters;static Items*items;static CharacterNode*characterNode;static ItemNode*itemNode[2];static Units*temporary;
static Block blocks[32];static unsigned blockCount,errors,firstError,eventIndex,expectedFault,seenFault,faultHits,resolveCalls,createCalls,integerCalls,textCalls,actualWorld,actualDeleted,scaleCalls;
static unsigned expectedFrees,arrayFrees,arrayDoubleFree,narrowSource;static void*arrayPointer;static bool enumerated;static std::string narrowRetained,narrowAlias;
static unsigned char recordBefore[0xc8],questBefore[2][0x218],managerBefore[2][sizeof(CQuestManager)],resourceBefore[2][0x48],levelBefore[2][LevelSize],unitBefore[4][UnitSize],propertyBefore[0x158],boundsBefore[0xb8];
static Wide sourceDungeon[2],aliasDungeon[2],sourceName[2],aliasName[2],sourceLevel[2],aliasLevel[2],sourceRecord[8],aliasRecord[8],sourceUnit[5],aliasUnit[5];static MapNode mapNodes[8];static unsigned mapNodeCount;
static unsigned char groupBefore[2][sizeof(CDataGroup)];
static detour::Set *pResolve,*pComplete,*pLookup,*pRemove,*pCreate,*pEnumerate,*pNPC,*pText,*pNarrow,*pDelete;
template<class T>T&at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
static void check(bool x,unsigned line){if(!x){if(!errors)firstError=line;++errors;}}
#define NEED(x) check((x),__LINE__)
static void n(unsigned x){cap->add(&x,4);}static unsigned uid(const void*p){for(unsigned i=0;i<4;++i)if(p==unit[i])return i;return p?99:Null;}
static unsigned qid(const void*p){return p==quest[0]?0:p==quest[1]?1:99;}static unsigned mid(const void*p){return p==manager[0]?0:p==manager[1]?1:99;}
static unsigned rid(const void*p){return p==resource[0]?0:p==resource[1]?1:99;}static unsigned lid(const void*p){return p==level[0]?0:p==level[1]?1:99;}
static unsigned gid(const void*p){return p==group[0]?1:p==group[1]?2:p?99:0;}
static unsigned long long questGuid(unsigned q){return q?0x2468135724681357ULL:0x1357246813572468ULL;}
static unsigned long long resolvedGuid(){return 0x1234567800009876ULL;}
static Wide dungeon(unsigned id){return !id?Wide():id==1?Wide(L"vault"):id==2?Wide(L"vaulx"):Wide(L"longer dungeon");}
static Wide questName(unsigned payload,unsigned q){Wide x;if(payload==0)x=L"Quest ASCII";else if(payload==1)x=L"Quest \u03a9\u4e2d";else if(payload==2)x=Wide(L"Quest\0hidden",12);else if(payload==3)x=Wide(L"Q\u0100tail",6);else if(payload==4)x=Wide(180,L'Q');else x=Wide();if(q)x+=L" alternate";return x;}
static std::string converted(const Wide&w){std::string s;for(unsigned i=0;i<w.size()&&w[i];++i)s+=static_cast<char>(static_cast<unsigned>(w[i])&255u);return s;}
static std::string message(unsigned branch,unsigned q){std::string s=branch?"No units found for quest : \n":"Unable to spawn unit for quest ";s+=converted(questName(cs->name,q));return std::string(s.c_str());}
static Ogre::Vector3 position(){return Ogre::Vector3(3,-5,7);}
static Ogre::Matrix4 matrix(unsigned i){return i?Ogre::Matrix4(1,0,0,0,0,-1,0,0,0,0,-1,0,0,0,0,1):Ogre::Matrix4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);}
static void seedOrientation(void*p,unsigned i){Ogre::Matrix4 m=matrix(i);at<Ogre::Matrix4>(p,0xc0)=m;at<Ogre::Vector3>(p,0xa8)=Ogre::Vector3(m[0][0],m[1][0],m[2][0]);at<Ogre::Vector3>(p,0x9c)=Ogre::Vector3(m[0][1],m[1][1],m[2][1]);at<Ogre::Vector3>(p,0xb4)=Ogre::Vector3(m[0][2],m[1][2],m[2][2]);}
static unsigned lookupModel(unsigned cache,unsigned world){if(!cache)return Null;for(unsigned i=0;i<3;++i)if((world&(1u<<i))&&((cs->matching&(1u<<i))?1u:2u)==cache)return i;return Null;}
static unsigned sample(unsigned count,unsigned call){if(cs->selection<0||cs->selection>=3)return call==1?static_cast<unsigned>(cs->selection):0;return cs->selection==2?count-1:static_cast<unsigned>(cs->selection)%count;}
static void append(unsigned code,unsigned id=0,unsigned arg=0,unsigned extra=0,const std::string&text=std::string()){
 NEED(wanted.size()<MaxEvents);Event e;e.code=code;e.id=id;e.arg=arg;e.extra=extra;e.text=text;e.state=model;wanted.push_back(e);if(cs->fault==code&&++expectedFault==cs->occurrence)throw Stop(code);
}
static void mutate(State&s,unsigned boundary,unsigned call){
 if(boundary==Resolve&&call==1){if(cs->mode==QuestAfterResolve)s.quest=1;if(cs->mode==TypesAfterResolve){s.type=22;s.from=22;s.required=2;}if(cs->mode==NeverAfterResolve)s.neverDestroy=1;}
 if(boundary==Complete){if(cs->mode==AcceptAfterComplete)s.accepted[s.quest]=1;if(cs->mode==QuestAfterComplete){s.quest=1;s.accepted[1]=1;}if(cs->mode==NeverAfterComplete)s.neverDestroy=1;if(cs->mode==CacheAfterComplete)s.cache=2;}
 if(boundary==Lookup&&cs->mode==QuestAfterLookup){s.quest=1;s.accepted[1]=1;}
 if(boundary==Remove&&cs->mode==AcceptAfterRemove)s.accepted[s.quest]=1;
 if(boundary==Delete){if(cs->mode==AcceptAfterDelete)s.accepted[s.quest]=1;if(cs->mode==TrackAfterDelete){s.accepted[s.quest]=1;s.tracking=1;}}
 if(boundary==Create){if(cs->mode==CountGrow&&call==1)s.required=3;if(cs->mode==CountShrink&&call==1)s.required=1;if(cs->mode==CountUnsigned)s.required=call==1?0x80000000u:2u;if(cs->mode==QuestAfterCreate)s.quest=1;}
 if(boundary==Enumerate&&cs->mode==QuestAfterEnumerate)s.quest=1;
 if(boundary==IntegerRng&&call==1){if(cs->mode==QuestAfterRng)s.quest=1;if(cs->mode==CapacityAfterRng)s.tempCapacity=1;if(cs->mode==CountAfterRng)s.tempCount=2;if(cs->mode==SlotAfterRng)s.tempSlots[0]=2;if(cs->mode==GuidAfterRng)s.unitGuid[0]=99;if(cs->mode==ManagerAfterRng)s.manager[s.quest]=1;}
 if(boundary==NPC&&cs->mode==QuestAfterNPC)s.quest=1;
 if(boundary==Text&&call==1&&cs->mode==ClearAfterText)s.identified=0;
 if(boundary==Narrow&&cs->mode==QuestAfterNarrow)s.quest=1;
}
static void logModel(unsigned branch){unsigned q=model.quest;append(Narrow,q,0,0,converted(questName(cs->name,q)));mutate(model,Narrow,1);append(Singleton);append(Log,0,3,0,message(branch,q));}
static void simulate(){
 expectedFrees=0;if(cs->nullLevel)return;if(dungeon(cs->questDungeon).empty())model.create=0;
 unsigned wrapped=static_cast<unsigned>(cs->base)+static_cast<unsigned>(cs->relative);int active=cs->relative?(wrapped&0x80000000u?cs->base:static_cast<int>(wrapped)):(cs->specific==-1?cs->base:cs->specific);
 bool eligible=cs->depth==active&&dungeon(cs->levelDungeon)==dungeon(cs->questDungeon);
 if(!eligible)eligible=!model.create&&!cs->relative&&cs->specific<=0&&(dungeon(cs->questDungeon).empty()||dungeon(cs->levelDungeon)==dungeon(cs->questDungeon));
 if(!eligible)return;
 if(!model.cache){for(unsigned attempt=1;attempt<=5;++attempt){append(Resolve,0,attempt);unsigned result=0;
   if(cs->route==1){append(GroupGuid,model.quest,1);model.baseGuid=resolvedGuid();result=1;}
   else if(cs->route==3){append(ByGuid,model.quest);result=1;}
   else{append(SpawnClass,0,attempt);if(cs->success&&attempt>=cs->success){append(GroupGuid,model.quest,1);model.baseGuid=resolvedGuid();result=1;}else model.baseGuid=~0ULL;}
   mutate(model,Resolve,attempt);model.cache=result;if(result)break;
  }
  if(!model.cache){logModel(0);model.completed=model.tracking=1;return;}
 }
 if(!model.accepted[model.quest]){unsigned m=model.manager[model.quest];append(Complete,m,model.quest);mutate(model,Complete,1);
  if(cs->complete==2&&!model.neverDestroy){unsigned found=lookupModel(model.cache,model.world);append(Lookup,0,model.cache);mutate(model,Lookup,1);
   if(found!=Null){append(Remove,found,1);append(Detach,found,1);model.world&=~(1u<<found);mutate(model,Remove,1);append(Delete,found);model.deleted|=1u<<found;mutate(model,Delete,1);}
  }
 }
 if(model.completed||!model.accepted[model.quest]||model.tracking)return;model.tracking=1;if(model.type!=22)return;
 if(model.from==22){unsigned count=0;while(count<model.required){++count;NEED(count<=4);if(count>4)throw Stop(999);append(Create,0,count);
   if(model.create){append(FloatRng,0,1,1);if(model.cache&&!model.completed){append(ResourceCreate,model.quest,model.cache,cs->dungeonDepth+model.quest*12);if(cs->createResult){append(Add,model.quest,3);model.unitGuid[3]=questGuid(model.quest);model.unitState[3]=17;model.orientation=1;}}}
   mutate(model,Create,count);
  }return;}
 model.tempLive=true;model.tempCount=0;model.tempCapacity=0;for(unsigned i=0;i<10;++i)model.tempSlots[i]=i%3;
 for(unsigned i=0;i<3;++i)if((model.world&cs->enumeration)&(1u<<i))model.tempSlots[model.tempCount++]=i;
 if(model.tempCount){model.tempCapacity=10;expectedFrees=1;}
 append(Enumerate,0,model.from);mutate(model,Enumerate,1);
 if(!model.tempCount){logModel(1);model.tempLive=false;return;}
 unsigned calls=0;while(model.tempCount){unsigned count=model.tempCount;append(IntegerRng,0,count-1);mutate(model,IntegerRng,++calls);unsigned index=sample(model.tempCount,calls),slot=index<model.tempCapacity?index:0;NEED(slot<10);unsigned u=model.tempSlots[slot];
  if(index<model.tempCount){--model.tempCount;model.tempSlots[index]=model.tempSlots[model.tempCount];}
  if(model.unitGuid[u]==~0ULL)continue;
  model.unitGuid[u]=questGuid(model.quest);model.unitState[u]=17;
  if(u==0){append(NPC,model.manager[model.quest],u);mutate(model,NPC,1);}
  if(u==2){model.identified=1;append(Text,u,1);mutate(model,Text,1);append(Text,u,2);mutate(model,Text,2);}
  break;
 }
 model.tempLive=false;
}
static void*raw(unsigned size){if(blockCount==32){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}unsigned char*p=static_cast<unsigned char*>(autotest::allocate(size+32));if(!p){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}std::memset(p,0xa6,16);std::memset(p+16,0,size);std::memset(p+size+16,0x6a,16);blocks[blockCount].p=p+16;blocks[blockCount++].size=size;return p+16;}
static State readState(bool withArray){State s;s.quest=qid(record->m_pQuest);s.cache=gid(record->m_pBaseUnitDataGroup);s.create=record->m_createUnit;s.completed=record->m_completed;s.tracking=record->m_trackUnitEvents;s.neverDestroy=record->m_neverDestroy;s.type=record->m_unitType;s.from=record->m_spawnFromUnitType;s.required=static_cast<unsigned>(record->m_requiredUnitCount);s.baseGuid=record->m_baseUnitGuid;s.world=actualWorld;s.deleted=actualDeleted;
 for(unsigned i=0;i<2;++i){s.accepted[i]=at<bool>(quest[i],0x26);s.manager[i]=mid(at<void*>(quest[i],0x1d0));}
 for(unsigned i=0;i<4;++i){s.unitState[i]=at<unsigned>(unit[i],0x178);s.unitGuid[i]=at<unsigned long long>(unit[i],0x170);}
 s.identified=at<bool>(unit[2],0x348);s.orientation=0;s.tempLive=withArray;s.tempCount=s.tempCapacity=0;for(unsigned i=0;i<10;++i)s.tempSlots[i]=i%3;
 if(withArray){NEED(temporary!=0);if(temporary){s.tempCount=at<unsigned>(temporary,8);s.tempCapacity=at<unsigned>(temporary,12);CBaseUnit**data=at<CBaseUnit**>(temporary,0);if(data)for(unsigned i=0;i<10;++i)s.tempSlots[i]=uid(data[i]);}}
 return s;
}
static void applyMutation(unsigned boundary,unsigned call){State s=readState(temporary&&enumerated);mutate(s,boundary,call);
 if(s.quest<2)record->m_pQuest=quest[s.quest];if(s.cache<=2)record->m_pBaseUnitDataGroup=s.cache?group[s.cache-1]:0;
 record->m_createUnit=s.create;record->m_completed=s.completed;record->m_trackUnitEvents=s.tracking;record->m_neverDestroy=s.neverDestroy;record->m_unitType=s.type;record->m_spawnFromUnitType=s.from;record->m_requiredUnitCount=static_cast<int>(s.required);
 for(unsigned i=0;i<2;++i){at<bool>(quest[i],0x26)=s.accepted[i];if(s.manager[i]<2)at<void*>(quest[i],0x1d0)=manager[s.manager[i]];}
 for(unsigned i=0;i<4;++i)at<unsigned long long>(unit[i],0x170)=s.unitGuid[i];at<bool>(unit[2],0x348)=s.identified;
 if(s.tempLive&&temporary){at<unsigned>(temporary,8)=s.tempCount;at<unsigned>(temporary,12)=s.tempCapacity;CBaseUnit**data=at<CBaseUnit**>(temporary,0);if(data)for(unsigned i=0;i<10;++i)if(s.tempSlots[i]<4)data[i]=unit[s.tempSlots[i]];}
}
static void checkSources(){for(unsigned i=0;i<2;++i){NEED(sourceDungeon[i]==aliasDungeon[i]);NEED(sourceDungeon[i]==dungeon(i?2:cs->questDungeon));NEED(at<Wide>(quest[i],0x30)==sourceDungeon[i]);NEED(sourceName[i]==aliasName[i]);NEED(sourceName[i]==questName(cs->name,i));NEED(at<Wide>(quest[i],0x50)==sourceName[i]);NEED(sourceLevel[i]==aliasLevel[i]);NEED(sourceLevel[i]==dungeon(cs->levelDungeon));NEED(at<Wide>(level[i],0x280)==sourceLevel[i]);}}
static unsigned unitNameOwner(unsigned i){return i<2?i:2;}
static unsigned unitNameOffset(unsigned i){return i==0?0x4c0:i<=2?0x210:i==3?0x2d0:0x2d8;}
static Wide unitName(unsigned i){Wide x=L"Retained unit name ";x+=wchar_t(L'0'+i);return x;}
static void checkWorld(unsigned expected){
 NEED(actualWorld==expected);NEED(at<void*>(characters,0)==((expected&1)?characterNode:0));NEED(characterNode->m_Data==unit[0]);NEED(characterNode->m_pNext==0&&characterNode->m_pPrevious==0);
 ItemNode*first=(expected&2)?itemNode[0]:(expected&4)?itemNode[1]:0;NEED(at<void*>(items,0)==first);
 for(unsigned i=0;i<2;++i){NEED(itemNode[i]->m_Data==unit[i+1]);ItemNode*next=i==0&&(expected&2)&&(expected&4)?itemNode[1]:0;ItemNode*previous=i==1&&(expected&2)&&(expected&4)?itemNode[0]:0;NEED(itemNode[i]->m_pNext==next);NEED(itemNode[i]->m_pPrevious==previous);}
}
static void checkArray(const State&e){NEED(temporary!=0);if(!temporary)return;NEED(at<unsigned>(temporary,8)==e.tempCount);NEED(at<unsigned>(temporary,12)==e.tempCapacity);NEED(at<unsigned>(temporary,16)==10);CBaseUnit**data=at<CBaseUnit**>(temporary,0);NEED(data==arrayPointer);if(data)for(unsigned i=0;i<10;++i)NEED(uid(data[i])==e.tempSlots[i]);}
static void snapshot(const State*e,bool withArray){State s=readState(withArray);n(s.quest);n(s.cache);n(s.create);n(s.completed);n(s.tracking);n(s.neverDestroy);n(s.type);n(s.from);n(s.required);cap->add(&s.baseGuid,8);n(s.world);n(s.deleted);
 if(e){NEED(s.quest==e->quest&&s.cache==e->cache);NEED(s.create==e->create&&s.completed==e->completed&&s.tracking==e->tracking);NEED(s.neverDestroy==e->neverDestroy&&s.type==e->type&&s.from==e->from&&s.required==e->required);NEED(s.baseGuid==e->baseGuid);NEED(s.deleted==e->deleted);checkWorld(e->world);}
 for(unsigned i=0;i<2;++i){n(s.accepted[i]);n(s.manager[i]);if(e){NEED(s.accepted[i]==e->accepted[i]);NEED(s.manager[i]==e->manager[i]);}}
 for(unsigned i=0;i<4;++i){n(s.unitState[i]);cap->add(&s.unitGuid[i],8);if(e){NEED(s.unitState[i]==e->unitState[i]);NEED(s.unitGuid[i]==e->unitGuid[i]);}}
 n(s.identified);cap->add(&at<Ogre::Matrix4>(unit[3],0xc0),64);cap->add(&at<Ogre::Vector3>(unit[3],0x9c),36);
 if(e){NEED(s.identified==e->identified);Ogre::Matrix4 m=matrix(e->orientation);NEED(!std::memcmp(&m,&at<Ogre::Matrix4>(unit[3],0xc0),64));NEED(at<Ogre::Vector3>(unit[3],0xa8)==Ogre::Vector3(m[0][0],m[1][0],m[2][0]));NEED(at<Ogre::Vector3>(unit[3],0x9c)==Ogre::Vector3(m[0][1],m[1][1],m[2][1]));NEED(at<Ogre::Vector3>(unit[3],0xb4)==Ogre::Vector3(m[0][2],m[1][2],m[2][2]));}
 n(withArray);if(withArray){n(s.tempCount);n(s.tempCapacity);for(unsigned i=0;i<10;++i)n(s.tempSlots[i]);if(e)checkArray(*e);}
}
static void emit(unsigned code,unsigned id=0,unsigned arg=0,unsigned extra=0,const std::string&text=std::string()){
 n(code);n(id);n(arg);n(extra);cap->addText(text);NEED(eventIndex<wanted.size());
 if(eventIndex<wanted.size()){const Event&e=wanted[eventIndex];NEED(code==e.code&&id==e.id&&arg==e.arg&&extra==e.extra);NEED(text==e.text);snapshot(&e.state,e.state.tempLive);}else snapshot(0,temporary&&enumerated);
 ++eventIndex;if(cs->fault==code&&++seenFault==cs->occurrence){++faultHits;throw Stop(code);}
}
static void rebuildWorld(){at<void*>(characters,0)=(actualWorld&1)?characterNode:0;characterNode->m_pNext=characterNode->m_pPrevious=0;at<void*>(items,0)=(actualWorld&2)?itemNode[0]:(actualWorld&4)?itemNode[1]:0;itemNode[0]->m_pNext=(actualWorld&2)&&(actualWorld&4)?itemNode[1]:0;itemNode[0]->m_pPrevious=0;itemNode[1]->m_pNext=0;itemNode[1]->m_pPrevious=(actualWorld&2)&&(actualWorld&4)?itemNode[0]:0;}
static void*noMaster(){return 0;}static unsigned long long fixedGuid(){return 0x55443322ULL;}
static void setupScale(CPropertyNode*p,const Ogre::Vector3&v){++scaleCalls;NEED(p==property);NEED(&v==&at<Ogre::Vector3>(p,0x90));NEED(v==Ogre::Vector3(1,1,1));NEED(at<void*>(p,0x58)==0);NEED(at<void*>(p,0x148)!=0);if(at<void*>(p,0x148))NEED(at<void*>(at<void*>(p,0x148),0)==reinterpret_cast<void*>(0xfc9310));}
static CDataGroup*spawnClass(CQuestUnitData*p){NEED(p==record);emit(SpawnClass,0,resolveCalls);return cs->success&&resolveCalls>=cs->success?group[0]:0;}
static long long groupGuid(CResourceManager*p,CDataGroup*g,const Wide&key){NEED(key==L"UNIT_GUID");emit(GroupGuid,rid(p),gid(g));return static_cast<long long>(resolvedGuid());}
static CDataGroup*byGuid(CResourceManager*p,long long guid){NEED(static_cast<unsigned long long>(guid)==resolvedGuid());emit(ByGuid,rid(p));return group[0];}
static CDataGroup*callResolve(CQuestUnitData*p){++resolveCalls;NEED(p==record);emit(Resolve,0,resolveCalls);pResolve->restore();CDataGroup*r;
 try{r=qpOriginalResolve(p);}catch(...){TL_REDIRECT(*pResolve,qpBoundaryResolve,&callResolve);throw;}TL_REDIRECT(*pResolve,qpBoundaryResolve,&callResolve);applyMutation(Resolve,resolveCalls);return r;}
static char callComplete(CQuestManager*p,const Wide&name){unsigned q=&name==&at<Wide>(quest[0],0x50)?0:&name==&at<Wide>(quest[1],0x50)?1:99;NEED(q<2);if(q<2)NEED(name==sourceName[q]);emit(Complete,mid(p),q);pComplete->restore();char r;
 try{r=qpOriginalComplete(p,name);}catch(...){TL_REDIRECT(*pComplete,qpBoundaryComplete,&callComplete);throw;}TL_REDIRECT(*pComplete,qpBoundaryComplete,&callComplete);NEED(r==(cs->complete==2));applyMutation(Complete,1);return r;}
static CBaseUnit*callLookup(CLevel*p,CDataGroup*g){NEED(p==level[0]);unsigned expected=lookupModel(gid(g),actualWorld);emit(Lookup,0,gid(g));pLookup->restore();CBaseUnit*r;
 try{r=qpOriginalLookup(p,g);}catch(...){TL_REDIRECT(*pLookup,qpBoundaryLookup,&callLookup);throw;}TL_REDIRECT(*pLookup,qpBoundaryLookup,&callLookup);NEED(uid(r)==expected);applyMutation(Lookup,1);return r;}
static void detach(CLevel*p,CBaseUnit*u,bool flag){NEED(p==level[0]);unsigned id=uid(u);emit(Detach,id,flag);NEED(id<3);if(id<3){NEED(actualWorld&(1u<<id));actualWorld&=~(1u<<id);rebuildWorld();}}
static void removeCharacter(CLevel*p,CCharacter*u,bool flag){NEED(uid(u)==0);detach(p,u,flag);}
static bool removeItem(CLevel*p,CItem*u,bool flag){NEED(uid(u)==1||uid(u)==2);detach(p,u,flag);return true;}
static void callRemove(CLevel*p,CBaseUnit*u,bool flag){NEED(p==level[0]);emit(Remove,uid(u),flag);pRemove->restore();
 try{qpOriginalRemove(p,u,flag);}catch(...){TL_REDIRECT(*pRemove,qpBoundaryRemove,&callRemove);throw;}TL_REDIRECT(*pRemove,qpBoundaryRemove,&callRemove);applyMutation(Remove,1);}
static void deleting(CBaseUnit*u,unsigned exact){unsigned id=uid(u);NEED(id==exact);NEED(id<4);emit(Delete,id);if(id<4){NEED(!(actualWorld&(1u<<id)));NEED(!(actualDeleted&(1u<<id)));actualDeleted|=1u<<id;}applyMutation(Delete,1);}
static void deleteCharacter(CBaseUnit*u){deleting(u,0);}static void deleteItem(CBaseUnit*u){deleting(u,1);}static void deleteEquipment(CBaseUnit*u){deleting(u,2);}static void deleteBase(CBaseUnit*u){deleting(u,3);}
static float randomFloat(float lo,float hi){NEED(lo==1.f&&hi==1.f);emit(FloatRng,0,1,1);return 1.f;}
static CBaseUnit*resourceCreate(CResourceManager*p,CDataGroup*g,int depth,bool a,bool b){NEED(!a&&!b);emit(ResourceCreate,rid(p),gid(g),depth);return cs->createResult?unit[3]:0;}
static void add(CLevel*p,CBaseUnit*u,const Ogre::Vector3&v){NEED(v==position());emit(Add,lid(p),uid(u));}
static CPositionableObject*callCreate(CQuestUnitData*p,CLevel*l){++createCalls;NEED(p==record&&l==level[0]);emit(Create,0,createCalls);pCreate->restore();CPositionableObject*r;
 try{r=qpOriginalCreate(p,l);}catch(...){TL_REDIRECT(*pCreate,qpBoundaryCreate,&callCreate);throw;}TL_REDIRECT(*pCreate,qpBoundaryCreate,&callCreate);unsigned expected=record->m_createUnit&&record->m_pBaseUnitDataGroup&&!record->m_completed&&cs->createResult?3:Null;NEED(uid(r)==expected);applyMutation(Create,createCalls);return r;}
static bool lowerISA(CResourceManager*p,unsigned actual,unsigned requested){NEED(rid(p)<2);NEED(actual>=10&&actual<=12);NEED(requested==static_cast<unsigned>(record->m_spawnFromUnitType));return actual>=10&&actual<=12&&(cs->enumeration&(1u<<(actual-10)));}
static void callEnumerate(CLevel*p,int type,Units&out){NEED(p==level[0]);NEED(out.size()==0&&at<unsigned>(&out,12)==0&&at<unsigned>(&out,16)==10);temporary=&out;pEnumerate->restore();
 try{qpOriginalEnumerate(p,type,out);}catch(...){TL_REDIRECT(*pEnumerate,qpBoundaryEnumerate,&callEnumerate);throw;}TL_REDIRECT(*pEnumerate,qpBoundaryEnumerate,&callEnumerate);
 arrayPointer=at<void*>(&out,0);enumerated=true;NEED(out.size()<=3);NEED(at<unsigned>(&out,12)==(out.size()?10u:0u));CBaseUnit**data=at<CBaseUnit**>(&out,0);if(data)for(unsigned i=out.size();i<10;++i)data[i]=unit[i%3];emit(Enumerate,0,type);applyMutation(Enumerate,1);
}
static int randomInteger(int lo,int hi){++integerCalls;NEED(lo==0);emit(IntegerRng,0,static_cast<unsigned>(hi));applyMutation(IntegerRng,integerCalls);unsigned count=temporary?at<unsigned>(temporary,8):0;NEED(count>0);return static_cast<int>(sample(count?count:1,integerCalls));}
static long long callNPC(CQuestManager*p,CCharacter*u){NEED(uid(u)==0);emit(NPC,mid(p),uid(u));pNPC->restore();long long r;
 try{r=qpOriginalNPC(p,u);}catch(...){TL_REDIRECT(*pNPC,qpBoundaryNPC,&callNPC);throw;}TL_REDIRECT(*pNPC,qpBoundaryNPC,&callNPC);NEED(r==0);applyMutation(NPC,1);return r;}
static void callText(CItem*p){++textCalls;NEED(uid(p)==2);emit(Text,uid(p),textCalls);pText->restore();
 try{qpOriginalText(p);}catch(...){TL_REDIRECT(*pText,qpBoundaryText,&callText);throw;}TL_REDIRECT(*pText,qpBoundaryText,&callText);applyMutation(Text,textCalls);}
static std::string callNarrow(const wchar_t*p){unsigned q=p==at<Wide>(quest[0],0x50).c_str()?0:p==at<Wide>(quest[1],0x50).c_str()?1:99;NEED(q<2);std::string expected=q<2?converted(sourceName[q]):std::string();emit(Narrow,q,0,0,expected);pNarrow->restore();std::string r;
 try{r=qpOriginalNarrow(p);}catch(...){TL_REDIRECT(*pNarrow,qpBoundaryNarrow,&callNarrow);throw;}TL_REDIRECT(*pNarrow,qpBoundaryNarrow,&callNarrow);NEED(r==expected);narrowSource=q;narrowRetained=r;narrowAlias=r;applyMutation(Narrow,1);return r;}
static void*logger(){emit(Singleton);return static_cast<void*>(&arrayPointer);}
static void logMessage(void*p,const std::string&text,int priority,bool mask){NEED(p==static_cast<void*>(&arrayPointer));checkSources();NEED(narrowRetained==narrowAlias);NEED(narrowSource<2);if(narrowSource<2)NEED(narrowRetained==converted(questName(cs->name,narrowSource)));emit(Log,0,priority,mask,text);}
static void deleteArray(void*p){if(p&&p==arrayPointer){if(arrayFrees){++arrayDoubleFree;NEED(false);return;}checkArray(model);++arrayFrees;temporary=0;}
 pDelete->restore();typedef void(*Fn)(void*);reinterpret_cast<Fn>(qpArrayDelete)(p);pDelete->redirect(qpArrayDelete,qpArrayDelete,&deleteArray);
}
static void setup(){
 errors=firstError=blockCount=eventIndex=expectedFault=seenFault=faultHits=resolveCalls=createCalls=integerCalls=textCalls=scaleCalls=mapNodeCount=0;
 actualWorld=cs->world;actualDeleted=0;arrayFrees=arrayDoubleFree=0;narrowSource=Null;arrayPointer=0;temporary=0;enumerated=false;narrowRetained.clear();narrowAlias.clear();autotest::g_arenaUsed=0;
 ::new(reinterpret_cast<void*>(0x14ff1a8))Wide();::new(reinterpret_cast<void*>(0x147c348))Wide();::new(reinterpret_cast<void*>(0x147c340))std::string();::new(reinterpret_cast<void*>(0x1480a48))Wide();
 Ogre::Matrix4 identity=matrix(0);NEED(!std::memcmp(&identity,reinterpret_cast<void*>(0x1423fc0),64));NEED(*reinterpret_cast<Ogre::Vector3*>(0x14241ac)==Ogre::Vector3(0,0,0));
 for(unsigned i=0;i<2;++i){TRepository<Wide>*repository=new TRepository<Wide>(Wide());group[i]=static_cast<CDataGroup*>(raw(sizeof(CDataGroup)));qpGroupCtor(group[i],Wide(i?L"OTHER UNIT":L"POPULATE UNIT"),0,4,4,repository);}
 {detour::Set environment;TL_REDIRECT(environment,qpGuid,&fixedGuid);TL_REDIRECT(environment,qpMaster,&noMaster);TL_REDIRECT(environment,qpScale,&setupScale);if(environment.failed()){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}
  for(unsigned i=0;i<2;++i){resource[i]=static_cast<CResourceManager*>(raw(sizeof(CResourceManager)));qpResourceCtor(resource[i],0);}
  property=static_cast<CPropertyNode*>(raw(sizeof(CPropertyNode)));qpPropertyCtor(property,0);NEED(at<void*>(property,0)==reinterpret_cast<void*>(0xfd9ef0));NEED(at<void*>(property,0x100)==reinterpret_cast<void*>(0xfda0e0));at<Ogre::Vector3>(property,0x84)=position();seedOrientation(property,1);
  for(unsigned i=0;i<4;++i){unit[i]=static_cast<CBaseUnit*>(raw(UnitSize));if(i==0)qpCharacterCtor(unit[i],0);else if(i==1)qpItemCtor(unit[i],0);else if(i==2)qpEquipmentCtor(unit[i],0);else qpBaseCtor(unit[i],0,0);}
 }
 NEED(scaleCalls==1);
 for(unsigned i=0;i<2;++i){level[i]=static_cast<CLevel*>(raw(LevelSize));::new(&at<Wide>(level[i],0x280))Wide(dungeon(cs->levelDungeon));::new(&at<Properties>(level[i],0xf0))Properties(1);::new(&at<Properties>(level[i],0x108))Properties(1);at<Properties>(level[i],0xf0).add(property);at<Properties>(level[i],0x108).add(property);at<int>(level[i],0x1a4)=cs->depth;at<int>(level[i],0x1a8)=cs->dungeonDepth+12*i;at<void*>(resource[i],0x18)=level[i];
  sourceLevel[i]=at<Wide>(level[i],0x280);aliasLevel[i]=sourceLevel[i];
 }
 for(unsigned i=0;i<2;++i){manager[i]=static_cast<CQuestManager*>(raw(sizeof(CQuestManager)));at<void*>(manager[i],0x10)=0;::new(&at<CompleteMap>(manager[i],0x70))CompleteMap;
  quest[i]=static_cast<CQuest*>(raw(sizeof(CQuest)));::new(&at<Wide>(quest[i],0x30))Wide(dungeon(i?2:cs->questDungeon));::new(&at<Wide>(quest[i],0x50))Wide(questName(cs->name,i));at<int>(quest[i],0x20)=cs->base;at<bool>(quest[i],0x26)=i?true:cs->accepted;at<unsigned long long>(quest[i],0x1c8)=questGuid(i);at<void*>(quest[i],0x1d0)=manager[i];at<void*>(quest[i],0x1d8)=resource[i];
  sourceDungeon[i]=at<Wide>(quest[i],0x30);aliasDungeon[i]=sourceDungeon[i];sourceName[i]=at<Wide>(quest[i],0x50);aliasName[i]=sourceName[i];
  CompleteMap&m=at<CompleteMap>(manager[i],0x70);m.insert(CompleteMap::value_type(Wide(L"a map neighbor"),true));m.insert(CompleteMap::value_type(Wide(L"z map neighbor"),false));if(cs->complete)m.insert(CompleteMap::value_type(sourceName[i],cs->complete==2));
  for(CompleteMap::iterator n=m.begin();n!=m.end();++n){NEED(mapNodeCount<8);mapNodes[mapNodeCount].p=n._M_node;std::memcpy(mapNodes[mapNodeCount++].bytes,n._M_node,48);}
 }
 record=static_cast<CQuestUnitData*>(raw(sizeof(CQuestUnitData)));qpRecordCtor(record,quest[0]);record->m_questUnitDataId=17;record->m_pBaseUnitDataGroup=cs->route?0:group[0];record->m_pQuestDataGroup=cs->route==1?group[0]:0;record->m_baseUnitGuid=cs->route==3?static_cast<long long>(resolvedGuid()):cs->route?-1:0x8877665544332211ULL;
 record->m_requiredUnitCount=cs->required;record->m_currentUnitCount=9;record->m_spawnFromUnitType=cs->from;record->m_unitType=cs->type;record->m_completed=cs->completed;record->m_trackUnitEvents=cs->tracking;record->m_createUnit=cs->create;record->m_neverDestroy=cs->neverDestroy;record->m_makeChampion=false;record->m_unitSearchMode=0;record->m_relativeFloor=cs->relative;record->m_specificFloor=cs->specific;
 record->m_displayName=L"Display trap";record->m_uniqueUnitName=L"Unique trap";record->m_spawnClass=L"BOUNDED CLASS";record->m_itemName=L"Item trap";record->m_monsterName=L"Monster trap";record->m_unitTypeName=L"Type trap";record->m_spawnFromUnitTypeName=L"From trap";record->m_generatedChampionName=L"Champion trap";
 const unsigned stringOffset[]={0x68,0x70,0x78,0x80,0x88,0x90,0x98,0xc0};for(unsigned i=0;i<8;++i){sourceRecord[i]=at<Wide>(record,stringOffset[i]);aliasRecord[i]=sourceRecord[i];}
 for(unsigned i=0;i<4;++i){at<void*>(unit[i],0x68)=resource[0];at<unsigned>(unit[i],0x1ac)=10+i;at<void*>(unit[i],0x1b0)=group[(cs->matching&(1u<<i))?0:1];at<unsigned long long>(unit[i],0x170)=i<3&&(cs->sentinels&(1u<<i))?~0ULL:0x77000000ULL+i;at<unsigned>(unit[i],0x178)=900+i;seedOrientation(unit[i],0);NEED((dynamic_cast<CCharacter*>(unit[i])!=0)==(i==0));NEED((dynamic_cast<CItem*>(unit[i])!=0)==(i==1||i==2));NEED((dynamic_cast<CEquipment*>(unit[i])!=0)==(i==2));NEED(at<void*>(unit[i],0x58)==0);}
 at<bool>(unit[2],0x348)=false;NEED(at<void*>(unit[1],0x1e8)==0&&at<void*>(unit[2],0x1e8)==0);
 for(unsigned i=0;i<5;++i){at<Wide>(unit[unitNameOwner(i)],unitNameOffset(i))=unitName(i);sourceUnit[i]=at<Wide>(unit[unitNameOwner(i)],unitNameOffset(i));aliasUnit[i]=sourceUnit[i];}
 characters=::new(raw(sizeof(Characters)))Characters;items=::new(raw(sizeof(Items)))Items;characterNode=::new(raw(sizeof(CharacterNode)))CharacterNode;itemNode[0]=::new(raw(sizeof(ItemNode)))ItemNode;itemNode[1]=::new(raw(sizeof(ItemNode)))ItemNode;
 characterNode->m_Data=static_cast<CCharacter*>(unit[0]);itemNode[0]->m_Data=static_cast<CItem*>(unit[1]);itemNode[1]->m_Data=static_cast<CItem*>(unit[2]);rebuildWorld();for(unsigned i=0;i<2;++i){at<void*>(level[i],0x98)=characters;at<void*>(level[i],0xa0)=items;}
 std::memcpy(recordBefore,record,0xc8);std::memcpy(propertyBefore,property,0x158);std::memcpy(boundsBefore,at<void*>(property,0x148),0xb8);
 for(unsigned i=0;i<2;++i){std::memcpy(questBefore[i],quest[i],0x218);std::memcpy(managerBefore[i],manager[i],sizeof(CQuestManager));std::memcpy(resourceBefore[i],resource[i],0x48);std::memcpy(levelBefore[i],level[i],LevelSize);std::memcpy(groupBefore[i],group[i],sizeof(CDataGroup));}
 for(unsigned i=0;i<4;++i)std::memcpy(unitBefore[i],unit[i],UnitSize);
}
static void initializeModel(){std::memset(&model,0,sizeof(model));model.quest=0;model.cache=cs->route?0:1;model.create=cs->create;model.completed=cs->completed;model.tracking=cs->tracking;model.neverDestroy=cs->neverDestroy;model.required=cs->required;model.type=cs->type;model.from=cs->from;model.accepted[0]=cs->accepted;model.accepted[1]=1;model.manager[0]=0;model.manager[1]=1;model.world=cs->world;model.baseGuid=cs->route==3?resolvedGuid():cs->route?~0ULL:0x8877665544332211ULL;
 for(unsigned i=0;i<4;++i){model.unitGuid[i]=i<3&&(cs->sentinels&(1u<<i))?~0ULL:0x77000000ULL+i;model.unitState[i]=900+i;}for(unsigned i=0;i<10;++i)model.tempSlots[i]=i%3;
}
static void checkUntouched(){const unsigned char*p=reinterpret_cast<const unsigned char*>(record);for(unsigned j=0;j<0xc8;++j){bool mutableByte=(j>=0x18&&j<0x28)||(j>=0x30&&j<0x3c)||(j>=0x40&&j<0x48)||j==0x60||j==0x63||j==0xb8||j==0xb9;if(!mutableByte)NEED(p[j]==recordBefore[j]);}
 const unsigned stringOffset[]={0x68,0x70,0x78,0x80,0x88,0x90,0x98,0xc0};const wchar_t*values[]={L"Display trap",L"Unique trap",L"BOUNDED CLASS",L"Item trap",L"Monster trap",L"Type trap",L"From trap",L"Champion trap"};
 for(unsigned i=0;i<8;++i){NEED(at<Wide>(record,stringOffset[i])==sourceRecord[i]);NEED(sourceRecord[i]==aliasRecord[i]);NEED(sourceRecord[i]==values[i]);}
 checkSources();NEED(!std::memcmp(propertyBefore,property,0x158));NEED(!std::memcmp(boundsBefore,at<void*>(property,0x148),0xb8));
 for(unsigned i=0;i<2;++i){p=reinterpret_cast<const unsigned char*>(quest[i]);for(unsigned j=0;j<0x218;++j)if(j!=0x26&&!(j>=0x1d0&&j<0x1d8))NEED(p[j]==questBefore[i][j]);NEED(!std::memcmp(managerBefore[i],manager[i],sizeof(CQuestManager)));NEED(!std::memcmp(resourceBefore[i],resource[i],0x48));NEED(!std::memcmp(levelBefore[i],level[i],LevelSize));NEED(!std::memcmp(groupBefore[i],group[i],sizeof(CDataGroup)));NEED(at<Properties>(level[i],0xf0)[0]==property);NEED(at<Properties>(level[i],0x108)[0]==property);}
 for(unsigned i=0;i<mapNodeCount;++i)NEED(!std::memcmp(mapNodes[i].bytes,mapNodes[i].p,48));
 for(unsigned i=0;i<4;++i){p=reinterpret_cast<const unsigned char*>(unit[i]);for(unsigned j=0;j<UnitSize;++j){bool mutableByte=(j>=0x170&&j<0x17c)||(i==2&&j==0x348)||(i==3&&j>=0x9c&&j<0x100);if(!mutableByte)NEED(p[j]==unitBefore[i][j]);}}
 for(unsigned i=0;i<5;++i){NEED(at<Wide>(unit[unitNameOwner(i)],unitNameOffset(i))==unitName(i));NEED(sourceUnit[i]==unitName(i));NEED(sourceUnit[i]==aliasUnit[i]);}
 for(unsigned i=0;i<blockCount;++i)for(unsigned j=0;j<16;++j){NEED(blocks[i].p[int(j)-16]==0xa6);NEED(blocks[i].p[blocks[i].size+j]==0x6a);}
}
static void cleanup(){
 for(unsigned i=0;i<2;++i){at<Properties>(level[i],0xf0).~Properties();at<Properties>(level[i],0x108).~Properties();at<Wide>(level[i],0x280).~Wide();at<Wide>(quest[i],0x30).~Wide();at<Wide>(quest[i],0x50).~Wide();at<CompleteMap>(manager[i],0x70).~CompleteMap();}
 record->m_children.clear();qpRecordDtor(record);for(unsigned i=0;i<2;++i){qpGroupDtor(group[i]);at<void*>(resource[i],0x18)=0;qpResourceDtor(resource[i]);}
 // Genuine Character/Item/Equipment/BaseUnit, PropertyNode and CCullingBounds
 // stay alive until fork exit, including units observed through D0 dispatch.
}
static void side(void*context,autotest::Capture&out,bool candidate){cs=static_cast<Case*>(context);cap=&out;setup();initializeModel();wanted.clear();unsigned predicted=0;
 try{simulate();}catch(const Stop&s){predicted=s.code;}NEED(predicted==cs->fault);
 // Each event is <=360 bytes plus its bounded text; this exact inventory has
 // <96 events and <=210-byte texts. Reserve >190 KiB for control deviations.
 size_t budget=1024;for(unsigned i=0;i<wanted.size();++i)budget+=384+wanted[i].text.size();NEED(budget<65536);if(budget>=65536){out.issue=autotest::Capture::InvalidReport;return;}
 unsigned caught=0;
 {detour::Set resolve,complete,lookup,remove,create,enumerate,npc,text,narrow,contracts,arrays,logging;pResolve=&resolve;pComplete=&complete;pLookup=&lookup;pRemove=&remove;pCreate=&create;pEnumerate=&enumerate;pNPC=&npc;pText=&text;pNarrow=&narrow;pDelete=&arrays;
  TL_REDIRECT(resolve,qpBoundaryResolve,&callResolve);TL_REDIRECT(complete,qpBoundaryComplete,&callComplete);TL_REDIRECT(lookup,qpBoundaryLookup,&callLookup);TL_REDIRECT(remove,qpBoundaryRemove,&callRemove);TL_REDIRECT(create,qpBoundaryCreate,&callCreate);TL_REDIRECT(enumerate,qpBoundaryEnumerate,&callEnumerate);TL_REDIRECT(npc,qpBoundaryNPC,&callNPC);TL_REDIRECT(text,qpBoundaryText,&callText);TL_REDIRECT(narrow,qpBoundaryNarrow,&callNarrow);
  TL_REDIRECT(contracts,qpSpawnClass,&spawnClass);TL_REDIRECT(contracts,qpGroupGuid,&groupGuid);TL_REDIRECT(contracts,qpByGuid,&byGuid);TL_REDIRECT(contracts,qpInteger,&randomInteger);TL_REDIRECT(contracts,qpFloat,&randomFloat);TL_REDIRECT(contracts,qpResourceCreate,&resourceCreate);TL_REDIRECT(contracts,qpAdd,&add);TL_REDIRECT(contracts,qpRemoveCharacter,&removeCharacter);TL_REDIRECT(contracts,qpRemoveItem,&removeItem);TL_REDIRECT(contracts,qpDeleteCharacter,&deleteCharacter);TL_REDIRECT(contracts,qpDeleteItem,&deleteItem);TL_REDIRECT(contracts,qpDeleteEquipment,&deleteEquipment);TL_REDIRECT(contracts,qpDeleteBase,&deleteBase);TL_REDIRECT(contracts,qpISA,&lowerISA);
  arrays.redirect(qpArrayDelete,qpArrayDelete,&deleteArray);logging.redirect(qpLogSingleton,qpLogSingleton,&logger);logging.redirect(qpLogMessage,qpLogMessage,&logMessage);
  if(resolve.failed()||complete.failed()||lookup.failed()||remove.failed()||create.failed()||enumerate.failed()||npc.failed()||text.failed()||narrow.failed()||contracts.failed()||arrays.failed()||logging.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef void(*Fn)(CQuestUnitData*,CLevel*);Fn invoke=candidate?&qpNew:&qpOld;if(!autotest::beginInvocation(out,invoke))return;
  try{invoke(record,cs->nullLevel?0:level[0]);out.callCompleted=1;}catch(const Stop&s){caught=s.code;}catch(...){caught=999;NEED(false);}
  temporary=0;NEED(caught==predicted);NEED(faultHits==(cs->fault?1u:0u));NEED(eventIndex==wanted.size());n(caught);snapshot(&model,false);n(enumerated);n(arrayPointer!=0);n(arrayFrees);n(arrayDoubleFree);NEED(arrayFrees==expectedFrees);NEED(arrayDoubleFree==0);NEED((arrayPointer!=0)==(expectedFrees!=0));bool expectEnum=false;for(unsigned i=0;i<wanted.size();++i)if(wanted[i].code==Enumerate)expectEnum=true;NEED(enumerated==expectEnum);
  NEED(!resolve.failed()&&!complete.failed()&&!lookup.failed()&&!remove.failed()&&!create.failed()&&!enumerate.failed()&&!npc.failed()&&!text.failed()&&!narrow.failed()&&!contracts.failed()&&!arrays.failed()&&!logging.failed());
 }
 checkUntouched();for(unsigned i=0;i<2;++i){at<Wide>(quest[i],0x30)+=L" changed after call";at<Wide>(quest[i],0x50)+=L" changed after call";NEED(sourceDungeon[i]==dungeon(i?2:cs->questDungeon));NEED(sourceName[i]==questName(cs->name,i));NEED(sourceDungeon[i]==aliasDungeon[i]&&sourceName[i]==aliasName[i]);}
 for(unsigned i=0;i<5;++i){at<Wide>(unit[unitNameOwner(i)],unitNameOffset(i))+=L" changed after call";NEED(sourceUnit[i]==unitName(i));NEED(sourceUnit[i]==aliasUnit[i]);}NEED(narrowRetained==narrowAlias);if(narrowSource<2){NEED(narrowRetained==converted(questName(cs->name,narrowSource)));narrowRetained+=" changed after call";NEED(narrowAlias==converted(questName(cs->name,narrowSource)));}cleanup();n(firstError);n(0x51504f50u);n(errors);
}
static void oldSide(void*p,autotest::Capture&o){side(p,o,false);}static void newSide(void*p,autotest::Capture&o){side(p,o,true);}
static bool oracle(const autotest::Outcome&o){unsigned t[2]={0,1};if(o.capture.length>=8)std::memcpy(t,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&t[0]==0x51504f50u&&!t[1];}
static unsigned failureLine(const autotest::Outcome&o){unsigned n=0;if(o.capture.length>=12)std::memcpy(&n,o.capture.data+o.capture.length-12,4);return n;}
static bool pair(const tlhybrid_host*host,autotest::Coverage&coverage,Case&c,unsigned&completed,unsigned&unwinds,unsigned&originalFailures,unsigned&candidateFailures){autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);bool oa=oracle(a),ob=oracle(b);if(!oa)++originalFailures;if(!ob)++candidateFailures;bool ok;
 if(c.fault){++unwinds;ok=oa&&ob&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==0xd48ea0&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);}
 else{++completed;ok=coverage.observe(host,a,b)==0&&oa&&ob;}
 if(!ok){host->log("    populate pair=%u/%u mode=%u route=%u world=%u sentinel=%u from=%u fault=%u.%u status=%d/%d oracle=%u/%u line=%u/%u\n",completed,unwinds,c.mode,c.route,c.world,c.sentinels,c.from,c.fault,c.occurrence,a.childStatus,b.childStatus,oa,ob,failureLine(a),failureLine(b));coverage.report(host);}return ok;
}
#undef NEED
}
TL_TEST(quest_unit_populate_closure){using namespace qp;autotest::Coverage coverage("quest_unit_populate_closure",0xd48ea0);std::vector<Case>normal,faults;unsigned completed=0,unwinds=0,originalFailures=0,candidateFailures=0;
 // Every guard lane retains a fully valid latent graph for the chosen controls.
 for(unsigned accepted=0;accepted<2;++accepted){Case c;c.nullLevel=true;c.accepted=accepted;normal.push_back(c);}
 for(unsigned create=0;create<2;++create)for(unsigned q=0;q<3;++q)for(unsigned l=0;l<3;++l)for(unsigned d=0;d<3;++d)for(unsigned s=0;s<3;++s){Case c;c.create=create;c.questDungeon=q;c.levelDungeon=l;c.depth=6+d;c.specific=s==0?-1:s==1?0:1;c.type=21;normal.push_back(c);}
 const int floors[][3]={{7,2,9},{7,-2,5},{7,-8,7},{-3,2,-3},{2147483647,1,2147483647},{(-2147483647-1),-1,2147483647},{(-2147483647-1),(-2147483647-1),0},{2147483647,2147483647,2147483647}};
 for(unsigned i=0;i<8;++i)for(unsigned match=0;match<2;++match){Case c;c.base=floors[i][0];c.relative=floors[i][1];c.specific=11;c.depth=match?floors[i][2]:(floors[i][2]==2147483647?2147483646:floors[i][2]+1);c.type=21;normal.push_back(c);}
 for(unsigned route=1;route<=3;route+=2){Case c;c.route=route;c.type=21;normal.push_back(c);}
 for(unsigned success=0;success<=5;++success)for(unsigned accepted=0;accepted<2;++accepted){Case c;c.route=2;c.success=success;c.accepted=accepted;c.type=21;normal.push_back(c);}
 for(unsigned branch=0;branch<2;++branch)for(unsigned payload=0;payload<6;++payload){Case c;c.name=payload;if(branch)c.enumeration=0;else{c.route=2;c.success=0;}normal.push_back(c);}
 for(unsigned accepted=0;accepted<2;++accepted)for(unsigned complete=0;complete<3;++complete)for(unsigned never=0;never<2;++never)for(unsigned found=0;found<4;++found){Case c;c.accepted=accepted;c.complete=complete;c.neverDestroy=never;c.matching=found?1u<<(found-1):0;c.type=21;normal.push_back(c);}
 for(unsigned done=0;done<2;++done)for(unsigned tracked=0;tracked<2;++tracked)for(unsigned type=0;type<3;++type){Case c;c.completed=done;c.tracking=tracked;c.type=type==0?0:type==1?21:22;c.from=22;c.required=0;normal.push_back(c);}
 for(unsigned count=0;count<=3;++count)for(unsigned create=0;create<2;++create)for(unsigned result=0;result<2;++result){Case c;c.from=22;c.required=count;c.create=create;c.createResult=result;normal.push_back(c);}
 // Exhaustive finite three-object association lattice. Real list order is
 // Character, Item, Equipment; sentinels are skipped only after removal.
 for(unsigned world=1;world<8;++world)for(unsigned sentinel=0;sentinel<8;++sentinel)for(unsigned selection=0;selection<3;++selection){Case c;c.world=world;c.sentinels=sentinel;c.selection=selection;normal.push_back(c);}
 const unsigned fromTypes[]={0,1,2,21};for(unsigned type=0;type<4;++type)for(unsigned empty=0;empty<2;++empty){Case c;c.from=fromTypes[type];c.enumeration=empty?0:7;normal.push_back(c);}
 const int indices[]={-1,10,3,9};for(unsigned i=0;i<4;++i){Case c;c.selection=indices[i];normal.push_back(c);}
 for(unsigned mode=QuestAfterResolve;mode<=QuestAfterNarrow;++mode){Case c;c.mode=mode;
  if(mode<=NeverAfterResolve){c.route=2;c.success=mode==QuestAfterResolve?2:1;}
  if(mode==TypesAfterResolve)c.type=21;
  if(mode==NeverAfterResolve||(mode>=AcceptAfterComplete&&mode<=TrackAfterDelete)){c.accepted=false;c.complete=2;}
  if(mode>=CountGrow&&mode<=QuestAfterCreate){c.from=22;c.required=mode==CountShrink?3:1;}
  if(mode==CapacityAfterRng)c.selection=2;
  if(mode==GuidAfterRng)c.sentinels=1;
  if(mode==ClearAfterText)c.selection=2;
  if(mode==QuestAfterNarrow){c.route=2;c.success=0;c.name=3;}
  normal.push_back(c);
 }
 // Resolution and removal precede even an already-completed/tracking guard.
 for(unsigned gate=0;gate<2;++gate){Case c;c.accepted=false;c.complete=2;c.route=2;c.success=1;c.completed=gate==0;c.tracking=gate==1;normal.push_back(c);}
 // Before-boundary throws except enumeration, which throws only after genuine
 // fill and registration of its owned new[] storage. No D0 throw is introduced.
 const unsigned faultCodes[]={Resolve,SpawnClass,GroupGuid,Complete,Lookup,Remove,Detach,Create,FloatRng,ResourceCreate,Add,Enumerate,IntegerRng,NPC,Text,Narrow,Singleton,Log,ByGuid};
 for(unsigned i=0;i<sizeof(faultCodes)/sizeof(faultCodes[0]);++i){Case c;c.fault=faultCodes[i];
  if(c.fault==Resolve||c.fault==SpawnClass||c.fault==GroupGuid)c.route=2;
  if(c.fault==Complete||c.fault==Lookup||c.fault==Remove||c.fault==Detach){c.accepted=false;c.complete=2;}
  if(c.fault>=Create&&c.fault<=Add)c.from=22;
  if(c.fault==Text)c.selection=2;
  if(c.fault==Narrow||c.fault==Singleton||c.fault==Log){c.route=2;c.success=0;c.name=3;}
  if(c.fault==ByGuid)c.route=3;
  faults.push_back(c);
 }
 {Case c;c.fault=Text;c.occurrence=2;c.selection=2;faults.push_back(c);}
 {Case c;c.fault=IntegerRng;c.occurrence=3;c.sentinels=7;faults.push_back(c);}
 {Case c;c.fault=Resolve;c.occurrence=5;c.route=2;c.success=0;faults.push_back(c);}
 {Case c;c.fault=Create;c.occurrence=2;c.from=22;c.required=3;faults.push_back(c);}
 for(unsigned code=Narrow;code<=Log;++code){Case c;c.enumeration=0;c.name=3;c.fault=code;faults.push_back(c);}
 if(normal.size()!=489||faults.size()!=26){host->log("    populate inventory mismatch %u/%u\n",unsigned(normal.size()),unsigned(faults.size()));return 1;}
 for(unsigned i=0;i<normal.size();++i)if(!pair(host,coverage,normal[i],completed,unwinds,originalFailures,candidateFailures))return 1;
 for(unsigned i=0;i<faults.size();++i)if(!pair(host,coverage,faults[i],completed,unwinds,originalFailures,candidateFailures))return 1;
 coverage.report(host);host->log("    populate: %u completed finite pairs, %u excluded unwinds; oracle failures original=%u candidate=%u. Original helpers stay bound; retained D0 checks dispatch only. Only d48ea0 receives acceptance credit.\n",completed,unwinds,originalFailures,candidateFailures);
 return completed!=489||unwinds!=26||coverage.completed!=completed||coverage.different||coverage.missing||originalFailures||candidateFailures;
}
