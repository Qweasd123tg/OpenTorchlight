// Independent bounded oracle for original createUnit d3e160..d3e608.
// Draft only. No compile/run claim. Only createUnit receives acceptance credit.
// Genuine PropertyNode C1 has one explicitly bounded setup-only scale callback.
// Original orientation, position, enumeration, random wrapper, spawn and NPC
// early branch execute; RNG, geometry, lower create/add and grounding are contracts.
#include <cstdio>
#include <cstring>
#include <new>
#include <string>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#include "Quest.h"
#include "QuestUnitData.h"
#include "QuestManager.h"
#include "PropertyNode.h"
#include "Equipment.h"
#include "TRepository.h"

TL_ORIGINAL(CPositionableObject*,qcOld,(CQuestUnitData*,CLevel*),"_ZN14CQuestUnitData10createUnitEP6CLevel")
extern "C" CPositionableObject* qcNew(CQuestUnitData*,CLevel*) __asm__("_ZN14CQuestUnitData10createUnitEP6CLevel");
TL_ORIGINAL(void,qcRecordCtor,(void*,void*),"_ZN14CQuestUnitDataC1EP6CQuest")
TL_ORIGINAL(void,qcRecordDtor,(void*),"_ZN14CQuestUnitDataD1Ev")
TL_ORIGINAL(void,qcPropertyCtor,(void*,void*),"_ZN13CPropertyNodeC1EP16CResourceManager")
TL_ORIGINAL(void,qcBaseCtor,(void*,void*,int),"_ZN9CBaseUnitC1EP16CResourceManager14EBASEUNIT_TYPE")
TL_ORIGINAL(void,qcCharacterCtor,(void*,void*),"_ZN10CCharacterC1EP16CResourceManager")
TL_ORIGINAL(void,qcItemCtor,(void*,void*),"_ZN5CItemC1EP16CResourceManager")
TL_ORIGINAL(void,qcEquipmentCtor,(void*,void*),"_ZN10CEquipmentC1EP16CResourceManager")
TL_ORIGINAL(void,qcResourceCtor,(void*,void*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,qcResourceDtor,(void*),"_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void,qcGroupCtor,(void*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,qcGroupDtor,(void*),"_ZN10CDataGroupD1Ev")
#define QC_DEP(R,N,A,S) TL_ORIGINAL(R,qcOriginal##N,A,S) TL_FUNCTION(qcBoundary##N,S)
QC_DEP(Ogre::Vector3,Position,(CPositionableObject*,bool),"_ZN19CPositionableObject11getPositionEb")
QC_DEP(Ogre::Quaternion,Orientation,(CPositionableObject*),"_ZN19CPositionableObject24getOrientationQuaternionEv")
QC_DEP(void,SetOrientation,(CPositionableObject*,const Ogre::Quaternion&),"_ZN19CPositionableObject14setOrientationERKN4Ogre10QuaternionE")
QC_DEP(CBaseUnit*,Spawn,(CQuestUnitData*,CResourceManager*,const Ogre::Vector3&),"_ZN14CQuestUnitData9spawnUnitEP16CResourceManagerRKN4Ogre7Vector3E")
QC_DEP(void,Enumerate,(CLevel*,int,TArrayList<CBaseUnit*>&),"_ZN6CLevel18getUnitsByUnitTypeEN9UNITTYPES10EUNITTYPESER10TArrayListIP9CBaseUnitE")
QC_DEP(Ogre::Vector3,Random,(CLevel*,const Ogre::Vector3&,float,bool),"_ZN6CLevel18randomOpenPositionERKN4Ogre7Vector3Efb")
QC_DEP(long long,NPC,(CQuestManager*,CCharacter*),"_ZN13CQuestManager16calculateNPCIconEP10CCharacter")
QC_DEP(void,Text,(CItem*),"_ZN5CItem15destroyItemTextEv")
#undef QC_DEP
TL_FUNCTION(qcFloat,"_ZN9UTILITIES13randomBetweenEff")
TL_FUNCTION(qcInteger,"_ZN9UTILITIES20randomIntegerBetweenEii")
TL_FUNCTION(qcRegion,"_ZN6CLevel17isInNoSpawnRegionERKN4Ogre7Vector3Ef")
TL_FUNCTION(qcRange,"_ZN6CLevel23randomOpenPositionRangeERKN4Ogre7Vector3Effb")
TL_FUNCTION(qcCreate,"_ZN16CResourceManager10createUnitEP10CDataGroupibb")
TL_FUNCTION(qcAdd,"_ZN6CLevel7addUnitEP9CBaseUnitRKN4Ogre7Vector3E")
TL_FUNCTION(qcDrop,"_ZN10CCharacter12dropToGroundER6CLevelfb")
TL_FUNCTION(qcSnap,"_ZN5CItem12snapToGroundEv")
TL_FUNCTION(qcISA,"_ZN16CResourceManager3ISAEN9UNITTYPES10EUNITTYPESES1_")
TL_FUNCTION(qcScale,"_ZN13CPropertyNode12scaleUpdatedERKN4Ogre7Vector3E")
TL_FUNCTION(qcMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(qcGuid,"_ZN9UTILITIES16createUniqueGuidEv")
extern "C" char qcDeleteArray[] __asm__("_ZdaPv");

namespace qc {
typedef std::wstring Wide;typedef TArrayList<CPropertyNode*> Properties;typedef TArrayList<CBaseUnit*> Units;
enum { UnitCount=4, PropertyCount=3, ResourceCount=3, LevelSize=0x2f0, UnitSize=0x778, MaxEvents=400 };
typedef char ABI[sizeof(Wide)==8&&sizeof(wchar_t)==4&&sizeof(Ogre::Vector3)==12&&sizeof(Ogre::Quaternion)==16&&sizeof(Ogre::Matrix4)==64&&sizeof(CQuestUnitData)==0xc8&&sizeof(CQuest)==0x218&&sizeof(CPropertyNode)==0x158&&sizeof(CCharacter)==UnitSize&&sizeof(CItem)==0x230&&sizeof(CEquipment)==0x438&&sizeof(CResourceManager)==0x48?1:-1];
enum Kind { Base=0,Character,Item,Equipment };
enum Code { FloatRng=1,Enumerate,IntegerRng,Position,Random,Range,Region,Spawn,Create,Add,Orientation,SetOrientation,NPC,Drop,Snap,Text };
enum Mode { Plain=0,QuestAfterPosition,QuestResourceAfterPosition,SlotAfterSpawn,CapacityAfterSpawn,
    DataAfterSpawn,CountAfterSpawn,CapacityAfterFloat,QuestAfterOrientation,NameAfterNPC,
    SourceAfterPosition,SourceAfterRange,SourceAfterRegion,LevelAfterRange,LevelAfterCreate,
    TempCountAfterRegion,TempCapacityAfterRng,TempSlotAfterRegion,MutateRangeInput,
    MutateRegionInput,MutateQuaternion,NameClearedAfterNPC,ManagerAfterOrientation };
struct Case {
 unsigned search,count,capacity,kind,name,blocked,spawnResult,mode,fault,occurrence,helperGuard;
 int selection;float floating;bool create,nullLevel,nullFirst;
 Case():search(0),count(3),capacity(3),kind(Base),name(1),blocked(0),spawnResult(1),mode(0),fault(0),occurrence(1),helperGuard(0),selection(0),floating(1.f),create(true),nullLevel(false),nullFirst(false){}
};
struct Stop {unsigned code;explicit Stop(unsigned c):code(c){}};
struct State {
 unsigned quest,questResource[2],manager[2],resourceLevel[3],unitResource[4],unitOrientation[4],unitState[4],identified[4];
 unsigned listCount[2],listCapacity[2],listBank[2],slots[2][3],tempCount,tempCapacity,tempSlot[3];
 unsigned long long guid[4];Wide unique,names[4];
};
struct Event {unsigned code,id,arg;float a,b;Ogre::Vector3 vector;Ogre::Quaternion quaternion;State state;};
struct Block {unsigned char*p;unsigned size;};
static const Case*cs;static autotest::Capture*cap;static State model;static std::vector<Event>wanted;
static CQuestUnitData*record;static CQuest*quest[2];static CQuestManager*manager[2];static CResourceManager*resource[3];static CLevel*level[3];
static CPropertyNode*property[3];static CBaseUnit*unit[4];static CDataGroup*group;static Properties alternate[2];
static CPropertyNode**listBacking[2][2];static void*enumerationWorld[5];static unsigned enumerationSize[5];static unsigned char enumerationBefore[5][24],boundsBefore[3][0xb8];
static Block blocks[40];static unsigned blockCount,errors,firstError,eventIndex,expectedFault,seenFault,faultHits;
static unsigned floatCalls,integerCalls,randomCalls,regionCalls,spawnCalls,modelIntegers,modelRegions,modelRandoms,activeSource,activeResource,activeLevel,setupScaleCalls;
static unsigned modelResult,actualResult,modelFrees,arrayFrees,arrayDoubleFree;static void*arrayPointer;static Units*temporary;static bool fallbackEntered,enumFilled;
static unsigned char recordBefore[0xc8],questBefore[2][0x218],levelBefore[3][LevelSize],resourceBefore[3][0x48],unitBefore[4][UnitSize],propertyBefore[3][0x158];
static Wide sourceUnique,sourceUniqueAlias,sourceDisplay,sourceDisplayAlias,sourceNames[4],sourceNameAliases[4];
static const Ogre::Vector3*randomInput;static const Ogre::Vector3*regionInput;static const Ogre::Vector3*spawnInput;static CPropertyNode*constructing;
static detour::Set *pPosition,*pOrientation,*pSetOrientation,*pSpawn,*pEnumerate,*pRandom,*pNPC,*pText,*pDelete;
template<class T>T&at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
static void check(bool ok,unsigned line){if(!ok){if(!errors)firstError=line;++errors;}}
#define NEED(x) check((x),__LINE__)
static void n(unsigned x){cap->add(&x,4);}static void f(float x){cap->add(&x,4);}
static unsigned uid(const void*p){for(unsigned i=0;i<4;++i)if(p==unit[i])return i;return p?99:100;}
static unsigned pid(const void*p){for(unsigned i=0;i<3;++i)if(p==property[i])return 10+i;return uid(p);}
static unsigned rid(const void*p){for(unsigned i=0;i<3;++i)if(p==resource[i])return i;return p?99:100;}
static unsigned lid(const void*p){for(unsigned i=0;i<3;++i)if(p==level[i])return i;return p?99:100;}
static unsigned qid(const void*p){return p==quest[0]?0:p==quest[1]?1:99;}
static unsigned mid(const void*p){return p==manager[0]?0:p==manager[1]?1:99;}
static unsigned kind(unsigned i){return i==0?Character:i==1?Item:i==2?Equipment:cs->kind;}
static unsigned long long questGuid(unsigned i){return i?0x2468135724681357ULL:0x1357246813572468ULL;}
static Properties&list(unsigned i){return at<Properties>(level[0],i?0x108:0xf0);}
static void*raw(unsigned size){if(blockCount>=40){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}unsigned char*p=static_cast<unsigned char*>(autotest::allocate(size+32));if(!p){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}std::memset(p,0xa6,16);std::memset(p+16,0,size);std::memset(p+16+size,0x6a,16);blocks[blockCount].p=p+16;blocks[blockCount++].size=size;return p+16;}
static Wide uniquePayload(unsigned i){if(!i)return Wide();if(i==1)return L"Unique quest name";if(i==2)return L"Unique \u03a9\u4e2d";if(i==3)return Wide(L"U\0\u0416",3);return Wide(220,L'U');}
static Ogre::Vector3 position(unsigned id){return id>=10?Ogre::Vector3(3.f+id,-5.f-id,7.f+2*id):Ogre::Vector3(101.f+id,-202.f-id,303.f+2*id);}
static Ogre::Vector3 generated(unsigned i){return Ogre::Vector3(500.f+i,-600.f-i,700.f+2*i);}
static Ogre::Vector3 changed(){return Ogre::Vector3(-71.f,82.f,-93.f);}
static Ogre::Quaternion rotation(unsigned i){return Ogre::Quaternion(i==0?1.f:0.f,i==1?1.f:0.f,i==2?1.f:0.f,i==3?1.f:0.f);}
static Ogre::Matrix4 matrix(unsigned i){float x=i==2||i==3?-1.f:1.f,y=i==1||i==3?-1.f:1.f,z=i==1||i==2?-1.f:1.f;return Ogre::Matrix4(x,0,0,0,0,y,0,0,0,0,z,0,0,0,0,1);}
static bool same(const Ogre::Quaternion&a,const Ogre::Quaternion&b){return a.w==b.w&&a.x==b.x&&a.y==b.y&&a.z==b.z;}
static void seedOrientation(void*p,unsigned i){Ogre::Matrix4 m=matrix(i);at<Ogre::Matrix4>(p,0xc0)=m;at<Ogre::Vector3>(p,0xa8)=Ogre::Vector3(m[0][0],m[1][0],m[2][0]);at<Ogre::Vector3>(p,0x9c)=Ogre::Vector3(m[0][1],m[1][1],m[2][1]);at<Ogre::Vector3>(p,0xb4)=Ogre::Vector3(m[0][2],m[1][2],m[2][2]);}
static void append(unsigned code,unsigned id=0,unsigned arg=0,float a=0,float b=0,const Ogre::Vector3&v=Ogre::Vector3(0,0,0),const Ogre::Quaternion&q=Ogre::Quaternion(1,0,0,0)){
 if(wanted.size()>=MaxEvents){NEED(false);throw Stop(999);}Event e;e.code=code;e.id=id;e.arg=arg;e.a=a;e.b=b;e.vector=v;e.quaternion=q;e.state=model;wanted.push_back(e);if(cs->fault==code&&++expectedFault==cs->occurrence)throw Stop(code);
}
static unsigned selectedProperty(unsigned which,unsigned index){unsigned slot=index<model.listCapacity[which]?index:0;NEED(slot<3);if(slot>=3)slot=0;return model.slots[which][slot];}
static int scriptedSelection(unsigned call,unsigned count){return cs->selection<0||cs->selection>=3?cs->selection:int((unsigned(cs->selection)+call-1)%count);}
static void modelPosition(unsigned id){append(Position,id,1,0,0,position(id));if(id>=10){if(cs->mode==QuestAfterPosition)model.quest=1;if(cs->mode==QuestResourceAfterPosition)model.questResource[model.quest]=1;}else if(cs->mode==SourceAfterPosition)model.unitResource[id]=(model.unitResource[id]+1)%3;}
static unsigned simulateSpawn(unsigned r,const Ogre::Vector3&v){
 append(Spawn,0,r,0,0,v);if(cs->helperGuard==1||cs->helperGuard==2||model.resourceLevel[r]==100)return 100;
 unsigned lev=model.resourceLevel[r];append(Create,r,lev,float(29+lev*12),0,v);
 if(cs->mode==LevelAfterCreate)model.resourceLevel[r]=(lev+1)%3;
 unsigned result=cs->spawnResult==0?100:cs->spawnResult==2?activeSource:3;
 if(result==100)return result;append(Add,lev,result,0,0,v);
 model.guid[result]=questGuid(model.quest);model.unitState[result]=17;
 if(kind(result)==Equipment){model.identified[result]=1;append(Text,result);append(Text,result);}
 return result;
}
static void simulate(){
 modelResult=100;modelFrees=0;modelIntegers=modelRegions=modelRandoms=0;
 if(!cs->create||cs->nullLevel)return;
 unsigned which=cs->search==1?1:0;
 if(cs->search<2&&model.listCount[which]){
  append(FloatRng,0,0,1.f,float(model.listCount[which]));
  if(cs->mode==CapacityAfterFloat)model.listCapacity[which]=1;
  unsigned index=static_cast<unsigned>(static_cast<long>(cs->floating-1.f));unsigned p=selectedProperty(which,index);
  modelPosition(10+p);activeSource=0;unsigned result=simulateSpawn(model.questResource[model.quest],position(10+p));modelResult=result;
  if(cs->mode==SlotAfterSpawn)model.slots[which][index<model.listCapacity[which]&&index<3?index:0]=2;
  if(cs->mode==CapacityAfterSpawn)model.listCapacity[which]=1;
  if(cs->mode==DataAfterSpawn){model.listBank[which]=1;for(unsigned i=0;i<3;++i)model.slots[which][i]=2-i;}
  if(cs->mode==CountAfterSpawn)model.listCount[which]=0;
  if(result==100)return;p=selectedProperty(which,index);
  append(Orientation,10+p,0,0,0,Ogre::Vector3(0,0,0),rotation(p));
  if(cs->mode==QuestAfterOrientation)model.quest=1;
  if(cs->mode==ManagerAfterOrientation)model.manager[model.quest]=1;
  append(SetOrientation,result,0,0,0,Ogre::Vector3(0,0,0),rotation(p));model.unitOrientation[result]=p;
  if(kind(result)==Character){append(NPC,model.manager[model.quest],result);
   if(cs->mode==NameAfterNPC)model.unique=L"Name changed by NPC callback";
   if(cs->mode==NameClearedAfterNPC)model.unique.clear();
   if(!model.unique.empty())model.names[result]=model.unique;append(Drop,result,0,4.f,0);
  }else if(kind(result)==Item||kind(result)==Equipment)append(Snap,result);
  return;
 }
 modelFrees=1;append(Enumerate,0,0);unsigned retry=0;float radius=10.f;
 for(;;){
  ++modelIntegers;append(IntegerRng,0,model.tempCount-1,0,float(model.tempCount-1));
  if(cs->mode==TempCapacityAfterRng&&modelIntegers==1)model.tempCapacity=1;
  unsigned index=static_cast<unsigned>(scriptedSelection(modelIntegers,model.tempCount));unsigned slot=index<model.tempCapacity?index:0;NEED(slot<3);if(slot>=3)slot=0;
  unsigned u=cs->nullFirst?100:model.tempSlot[slot];modelResult=u;if(u==100)return;activeSource=u;
  modelPosition(u);unsigned r=model.unitResource[u],lev=model.resourceLevel[r];
  append(Random,lev,0,radius,0,position(u));append(Range,lev,0,0,radius,position(u));
  ++modelRandoms;Ogre::Vector3 current=generated(modelRandoms);
  if(cs->mode==SourceAfterRange)model.unitResource[u]=(model.unitResource[u]+1)%3;
  if(cs->mode==LevelAfterRange)model.resourceLevel[r]=(lev+1)%3;
  r=model.unitResource[u];lev=model.resourceLevel[r];append(Region,lev,0,0,0,current);++modelRegions;
  if(cs->mode==SourceAfterRegion)model.unitResource[u]=(model.unitResource[u]+1)%3;
  if(cs->mode==MutateRegionInput)current=changed();
  if(cs->mode==TempCountAfterRegion&&modelRegions==1)model.tempCount=2;
  if(cs->mode==TempSlotAfterRegion&&modelRegions==1)model.tempSlot[0]=2;
  if(modelRegions>cs->blocked||retry==41){simulateSpawn(model.unitResource[u],current);return;}
  radius=10.f+.25f*retry;++retry;
 }
}

// Runtime collaborators and setup are below. All comparisons use the model
// built before invocation, never candidate-generated expected state.
static void snapshot(const State*e){
 unsigned q=qid(record->m_pQuest);n(q);if(e)NEED(q==e->quest);
 for(unsigned i=0;i<2;++i){unsigned r=rid(at<void*>(quest[i],0x1d8)),m=mid(at<void*>(quest[i],0x1d0));n(r);n(m);if(e){NEED(r==e->questResource[i]);NEED(m==e->manager[i]);}}
 for(unsigned i=0;i<3;++i){unsigned l=lid(at<void*>(resource[i],0x18));n(l);if(e)NEED(l==e->resourceLevel[i]);}
 for(unsigned i=0;i<4;++i){unsigned r=rid(at<void*>(unit[i],0x68)),s=at<unsigned>(unit[i],0x178);unsigned long long g=at<unsigned long long>(unit[i],0x170);n(r);n(s);cap->add(&g,8);
  cap->add(&at<Ogre::Matrix4>(unit[i],0xc0),64);cap->add(&at<Ogre::Vector3>(unit[i],0x9c),36);
  if(e){NEED(r==e->unitResource[i]);NEED(s==e->unitState[i]);NEED(g==e->guid[i]);Ogre::Matrix4 m=matrix(e->unitOrientation[i]);NEED(!std::memcmp(&m,&at<Ogre::Matrix4>(unit[i],0xc0),64));NEED(at<Ogre::Vector3>(unit[i],0xa8)==Ogre::Vector3(m[0][0],m[1][0],m[2][0]));NEED(at<Ogre::Vector3>(unit[i],0x9c)==Ogre::Vector3(m[0][1],m[1][1],m[2][1]));NEED(at<Ogre::Vector3>(unit[i],0xb4)==Ogre::Vector3(m[0][2],m[1][2],m[2][2]));}
  if(kind(i)==Character){const Wide&s=at<Wide>(unit[i],0x4c0);cap->addText(s);if(e)NEED(s==e->names[i]);}
  if(kind(i)==Equipment){unsigned b=at<bool>(unit[i],0x348);n(b);if(e)NEED(b==e->identified[i]);}
 }
 for(unsigned i=0;i<2;++i){unsigned c=at<unsigned>(&list(i),8),capacity=at<unsigned>(&list(i),12);n(c);n(capacity);if(e){NEED(c==e->listCount[i]);NEED(capacity==e->listCapacity[i]);}
  CPropertyNode**data=at<CPropertyNode**>(&list(i),0);unsigned bank=data==listBacking[i][0]?0:data==listBacking[i][1]?1:99;n(bank);if(e)NEED(bank==e->listBank[i]);for(unsigned j=0;j<3;++j){unsigned p=pid(data[j]);n(p);if(e)NEED(p==10+e->slots[i][j]);}
 }
 cap->addText(record->m_uniqueUnitName);if(e)NEED(record->m_uniqueUnitName==e->unique);
}
static void emit(unsigned code,unsigned id=0,unsigned arg=0,float a=0,float b=0,const Ogre::Vector3&v=Ogre::Vector3(0,0,0),const Ogre::Quaternion&q=Ogre::Quaternion(1,0,0,0)){
 n(code);n(id);n(arg);f(a);f(b);cap->add(&v,12);cap->add(&q,16);NEED(eventIndex<wanted.size());
 if(eventIndex<wanted.size()){const Event&e=wanted[eventIndex];NEED(code==e.code);NEED(id==e.id);NEED(arg==e.arg);NEED(a==e.a&&b==e.b);NEED(v==e.vector);NEED(same(q,e.quaternion));snapshot(&e.state);}else snapshot(0);
 ++eventIndex;if(cs->fault==code&&++seenFault==cs->occurrence){++faultHits;throw Stop(code);}
}
static void*noMaster(){return 0;}static unsigned long long fixedGuid(){return 0x55443322ULL;}
static void setupScale(CPropertyNode*p,const Ogre::Vector3&v){++setupScaleCalls;NEED(p==constructing);NEED(&v==&at<Ogre::Vector3>(p,0x90));NEED(v==Ogre::Vector3(1,1,1));NEED(at<void*>(p,0x58)==0);NEED(at<void*>(p,0x148)!=0);if(at<void*>(p,0x148))NEED(at<void*>(at<void*>(p,0x148),0)==reinterpret_cast<void*>(0xfc9310));}
static bool lowerISA(CResourceManager*p,unsigned actual,unsigned requested){NEED(rid(p)<3);NEED(actual>=10&&actual<=13);NEED(requested==0);return requested==0;}
static void deleteArray(void*p){
 if(p&&p==arrayPointer){if(arrayFrees){++arrayDoubleFree;NEED(false);return;}++arrayFrees;}
 pDelete->restore();typedef void(*Fn)(void*);reinterpret_cast<Fn>(qcDeleteArray)(p);pDelete->redirect(qcDeleteArray,qcDeleteArray,&deleteArray);
}
static float randomFloat(float lo,float hi){++floatCalls;emit(FloatRng,0,0,lo,hi);if(cs->mode==CapacityAfterFloat)at<unsigned>(&list(cs->search==1?1:0),12)=1;return cs->floating;}
static int randomInteger(int lo,int hi){++integerCalls;emit(IntegerRng,0,static_cast<unsigned>(hi),float(lo),float(hi));NEED(temporary!=0);if(temporary&&cs->mode==TempCapacityAfterRng&&integerCalls==1)at<unsigned>(temporary,12)=1;unsigned count=temporary?temporary->size():1;return scriptedSelection(integerCalls,count?count:1);}
static void callEnumerate(CLevel*p,int type,Units&out){
 fallbackEntered=true;temporary=&out;NEED(p==level[0]);NEED(type==0);NEED(out.size()==0&&at<unsigned>(&out,12)==0&&at<unsigned>(&out,16)==10);
 if(cs->nullFirst){out.add(static_cast<CBaseUnit*>(0));}
 else{pEnumerate->restore();try{qcOriginalEnumerate(p,type,out);}catch(...){TL_REDIRECT(*pEnumerate,qcBoundaryEnumerate,&callEnumerate);throw;}TL_REDIRECT(*pEnumerate,qcBoundaryEnumerate,&callEnumerate);}
 arrayPointer=at<void*>(&out,0);enumFilled=true;NEED(arrayPointer!=0);NEED(out.size()==(cs->nullFirst?1u:3u));NEED(at<unsigned>(&out,12)==10);
 if(!cs->nullFirst)for(unsigned i=0;i<3;++i)NEED(out[i]==unit[i]);else NEED(out[0]==0);
 emit(Enumerate,0,0);
}
static Ogre::Vector3 callPosition(CPositionableObject*p,bool absolute){unsigned id=pid(p);emit(Position,id,absolute,0,0,position(id));NEED(id<4||(id>=10&&id<13));pPosition->restore();Ogre::Vector3 v;
 try{v=qcOriginalPosition(p,absolute);}catch(...){TL_REDIRECT(*pPosition,qcBoundaryPosition,&callPosition);throw;}TL_REDIRECT(*pPosition,qcBoundaryPosition,&callPosition);NEED(v==position(id));
 if(id>=10){if(cs->mode==QuestAfterPosition)record->m_pQuest=quest[1];if(cs->mode==QuestResourceAfterPosition)at<void*>(record->m_pQuest,0x1d8)=resource[1];}
 else{activeSource=id;if(cs->mode==SourceAfterPosition)at<void*>(unit[id],0x68)=resource[(rid(at<void*>(unit[id],0x68))+1)%3];}
 return v;
}
static Ogre::Vector3 lowerRange(CLevel*p,const Ogre::Vector3&v,float lo,float hi,bool flag){emit(Range,lid(p),flag,lo,hi,v);NEED(&v==randomInput);NEED(lo==0.f);NEED(activeSource<3);if(cs->mode==MutateRangeInput)const_cast<Ogre::Vector3&>(v)=changed();return generated(randomCalls);}
static Ogre::Vector3 callRandom(CLevel*p,const Ogre::Vector3&v,float radius,bool flag){++randomCalls;randomInput=&v;emit(Random,lid(p),flag,radius,0,v);NEED(activeSource<3);if(activeSource<3)NEED(&v!=&at<Ogre::Vector3>(unit[activeSource],0x84));unsigned r=activeSource<3?rid(at<void*>(unit[activeSource],0x68)):0,lev=lid(p);pRandom->restore();Ogre::Vector3 result;
 try{result=qcOriginalRandom(p,v,radius,flag);}catch(...){TL_REDIRECT(*pRandom,qcBoundaryRandom,&callRandom);throw;}TL_REDIRECT(*pRandom,qcBoundaryRandom,&callRandom);NEED(result==generated(randomCalls));
 if(cs->mode==SourceAfterRange&&activeSource<3)at<void*>(unit[activeSource],0x68)=resource[(r+1)%3];
 if(cs->mode==LevelAfterRange&&r<3&&lev<3)at<void*>(resource[r],0x18)=level[(lev+1)%3];return result;
}
static bool noSpawn(CLevel*p,const Ogre::Vector3&v,float radius){++regionCalls;if(!regionInput)regionInput=&v;NEED(regionInput==&v);emit(Region,lid(p),0,radius,0,v);NEED(activeSource<3);if(activeSource<3)NEED(&v!=&at<Ogre::Vector3>(unit[activeSource],0x84));
 if(cs->mode==SourceAfterRegion&&activeSource<3)at<void*>(unit[activeSource],0x68)=resource[(rid(at<void*>(unit[activeSource],0x68))+1)%3];
 if(cs->mode==MutateRegionInput)const_cast<Ogre::Vector3&>(v)=changed();
 if(cs->mode==TempCountAfterRegion&&regionCalls==1&&temporary)at<unsigned>(temporary,8)=2;
 if(cs->mode==TempSlotAfterRegion&&regionCalls==1&&temporary)(*temporary)[0]=unit[2];
 return regionCalls<=cs->blocked;
}
static CBaseUnit*lowerCreate(CResourceManager*p,CDataGroup*g,int depth,bool first,bool second){activeResource=rid(p);activeLevel=activeResource<3?lid(at<void*>(p,0x18)):99;NEED(g==group);NEED(!first&&!second);NEED(activeResource<3&&activeLevel<3);
 NEED(spawnInput!=0);Ogre::Vector3 v=spawnInput?*spawnInput:Ogre::Vector3(0,0,0);emit(Create,activeResource,activeLevel,float(depth),0,v);
 if(cs->mode==LevelAfterCreate&&activeResource<3&&activeLevel<3)at<void*>(p,0x18)=level[(activeLevel+1)%3];
 return cs->spawnResult==0?0:cs->spawnResult==2?unit[activeSource<3?activeSource:0]:unit[3];
}
static void lowerAdd(CLevel*p,CBaseUnit*u,const Ogre::Vector3&v){emit(Add,lid(p),uid(u),0,0,v);NEED(&v==spawnInput);NEED(lid(p)==activeLevel);}
static void callText(CItem*p){emit(Text,uid(p));NEED(at<void*>(p,0x1e8)==0);pText->restore();try{qcOriginalText(p);}catch(...){TL_REDIRECT(*pText,qcBoundaryText,&callText);throw;}TL_REDIRECT(*pText,qcBoundaryText,&callText);NEED(at<void*>(p,0x1e8)==0);}
static CBaseUnit*callSpawn(CQuestUnitData*p,CResourceManager*r,const Ogre::Vector3&v){++spawnCalls;spawnInput=&v;emit(Spawn,0,rid(r),0,0,v);NEED(p==record);NEED(rid(r)<3);if(fallbackEntered){NEED(&v==regionInput);}else for(unsigned i=0;i<3;++i)NEED(&v!=&at<Ogre::Vector3>(property[i],0x84));
 pSpawn->restore();CBaseUnit*result=0;try{result=qcOriginalSpawn(p,r,v);}catch(...){TL_REDIRECT(*pSpawn,qcBoundarySpawn,&callSpawn);throw;}TL_REDIRECT(*pSpawn,qcBoundarySpawn,&callSpawn);
 if(!fallbackEntered){unsigned which=cs->search==1?1:0;unsigned index=static_cast<unsigned>(static_cast<long>(cs->floating-1.f));unsigned capacity=at<unsigned>(&list(which),12),slot=index<capacity&&index<3?index:0;
  if(cs->mode==SlotAfterSpawn)at<CPropertyNode**>(&list(which),0)[slot]=property[2];
  if(cs->mode==CapacityAfterSpawn)at<unsigned>(&list(which),12)=1;
  if(cs->mode==DataAfterSpawn){CPropertyNode**a=at<CPropertyNode**>(&list(which),0);at<CPropertyNode**>(&list(which),0)=at<CPropertyNode**>(&alternate[which],0);at<CPropertyNode**>(&alternate[which],0)=a;}
  if(cs->mode==CountAfterSpawn)at<unsigned>(&list(which),8)=0;
 }
 return result;
}
static Ogre::Quaternion callOrientation(CPositionableObject*p){unsigned id=pid(p);NEED(id>=10&&id<13);unsigned orientation=id>=10&&id<13?id-10:0;emit(Orientation,id,0,0,0,Ogre::Vector3(0,0,0),rotation(orientation));pOrientation->restore();Ogre::Quaternion q;
 try{q=qcOriginalOrientation(p);}catch(...){TL_REDIRECT(*pOrientation,qcBoundaryOrientation,&callOrientation);throw;}TL_REDIRECT(*pOrientation,qcBoundaryOrientation,&callOrientation);NEED(same(q,rotation(orientation)));
 if(cs->mode==QuestAfterOrientation)record->m_pQuest=quest[1];if(cs->mode==ManagerAfterOrientation)at<void*>(record->m_pQuest,0x1d0)=manager[1];return q;
}
static void callSetOrientation(CPositionableObject*p,const Ogre::Quaternion&q){emit(SetOrientation,uid(p),0,0,0,Ogre::Vector3(0,0,0),q);NEED(uid(p)<4);NEED(at<void*>(p,0x58)==0);for(unsigned i=0;i<3;++i)NEED(&q!=reinterpret_cast<Ogre::Quaternion*>(static_cast<char*>(static_cast<void*>(property[i]))+0xa8));pSetOrientation->restore();
 try{qcOriginalSetOrientation(p,q);}catch(...){TL_REDIRECT(*pSetOrientation,qcBoundarySetOrientation,&callSetOrientation);throw;}TL_REDIRECT(*pSetOrientation,qcBoundarySetOrientation,&callSetOrientation);if(cs->mode==MutateQuaternion)const_cast<Ogre::Quaternion&>(q)=Ogre::Quaternion(0,0,0,0);
}
static long long callNPC(CQuestManager*p,CCharacter*c){emit(NPC,mid(p),uid(c));NEED(mid(p)<2);NEED(at<void*>(p,0x10)==0);pNPC->restore();long long result;
 try{result=qcOriginalNPC(p,c);}catch(...){TL_REDIRECT(*pNPC,qcBoundaryNPC,&callNPC);throw;}TL_REDIRECT(*pNPC,qcBoundaryNPC,&callNPC);NEED(result==0);
 if(cs->mode==NameAfterNPC)record->m_uniqueUnitName=L"Name changed by NPC callback";if(cs->mode==NameClearedAfterNPC)record->m_uniqueUnitName.clear();return result;
}
static void drop(CCharacter*p,CLevel&l,float height,bool flag){emit(Drop,uid(p),lid(&l),height,float(flag));NEED(&l==level[0]);}
static void snap(CItem*p){emit(Snap,uid(p));}
static Wide destinationName(unsigned i){Wide s=L"Existing Character name ";s+=wchar_t(L'0'+i);return s;}
static void setup(){
 errors=firstError=blockCount=eventIndex=seenFault=expectedFault=faultHits=0;setupScaleCalls=0;autotest::g_arenaUsed=0;
 floatCalls=integerCalls=randomCalls=regionCalls=spawnCalls=activeSource=activeResource=activeLevel=0;
 arrayFrees=arrayDoubleFree=0;arrayPointer=0;temporary=0;fallbackEntered=enumFilled=false;randomInput=regionInput=spawnInput=0;
 ::new(reinterpret_cast<void*>(0x14ff1a8))Wide();::new(reinterpret_cast<void*>(0x147c348))Wide();::new(reinterpret_cast<void*>(0x147c340))std::string();::new(reinterpret_cast<void*>(0x1480a48))Wide();
 Ogre::Matrix4 identity=matrix(0);NEED(!std::memcmp(&identity,reinterpret_cast<void*>(0x1423fc0),64));NEED(*reinterpret_cast<Ogre::Vector3*>(0x14241ac)==Ogre::Vector3(0,0,0));
 TRepository<Wide>*repo=new TRepository<Wide>(Wide());group=static_cast<CDataGroup*>(raw(sizeof(CDataGroup)));qcGroupCtor(group,Wide(L"CREATE UNIT"),0,4,4,repo);
 {detour::Set environment;TL_REDIRECT(environment,qcGuid,&fixedGuid);TL_REDIRECT(environment,qcMaster,&noMaster);TL_REDIRECT(environment,qcScale,&setupScale);
  if(environment.failed()){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}
  for(unsigned i=0;i<3;++i){resource[i]=static_cast<CResourceManager*>(raw(sizeof(CResourceManager)));qcResourceCtor(resource[i],0);}
  for(unsigned i=0;i<3;++i){property[i]=static_cast<CPropertyNode*>(raw(sizeof(CPropertyNode)));constructing=property[i];qcPropertyCtor(property[i],0);NEED(at<void*>(property[i],0)==reinterpret_cast<void*>(0xfd9ef0));NEED(at<void*>(property[i],0x100)==reinterpret_cast<void*>(0xfda0e0));NEED(at<void*>(property[i],0x58)==0);at<Ogre::Vector3>(property[i],0x84)=position(10+i);seedOrientation(property[i],i);}
  for(unsigned i=0;i<4;++i){unit[i]=static_cast<CBaseUnit*>(raw(UnitSize));if(kind(i)==Character)qcCharacterCtor(unit[i],0);else if(kind(i)==Equipment)qcEquipmentCtor(unit[i],0);else if(kind(i)==Item)qcItemCtor(unit[i],0);else qcBaseCtor(unit[i],0,0);}
 }
 NEED(setupScaleCalls==3);
 for(unsigned i=0;i<3;++i){level[i]=static_cast<CLevel*>(raw(LevelSize));::new(&at<Properties>(level[i],0xf0))Properties(3);::new(&at<Properties>(level[i],0x108))Properties(3);at<int>(level[i],0x1a8)=29+i*12;}
 for(unsigned i=0;i<3;++i)at<void*>(resource[i],0x18)=level[(i+1)%3];
 if(cs->helperGuard==3)at<void*>(resource[0],0x18)=0;
 for(unsigned i=0;i<2;++i){manager[i]=static_cast<CQuestManager*>(raw(sizeof(CQuestManager)));at<void*>(manager[i],0x10)=0;quest[i]=static_cast<CQuest*>(raw(sizeof(CQuest)));at<unsigned long long>(quest[i],0x1c8)=questGuid(i);at<void*>(quest[i],0x1d0)=manager[i];at<void*>(quest[i],0x1d8)=resource[i];}
 record=static_cast<CQuestUnitData*>(raw(sizeof(CQuestUnitData)));qcRecordCtor(record,quest[0]);record->m_questUnitDataId=17;record->m_pBaseUnitDataGroup=cs->helperGuard==1?0:group;record->m_pQuestDataGroup=group;record->m_createUnit=cs->create;record->m_completed=cs->helperGuard==2;record->m_makeChampion=false;record->m_unitSearchMode=cs->search;
 record->m_displayName=L"Display name must never replace unique name";record->m_uniqueUnitName=uniquePayload(cs->name);record->m_generatedChampionName=L"Champion name remains untouched";
 sourceUnique=record->m_uniqueUnitName;sourceUniqueAlias=sourceUnique;sourceDisplay=record->m_displayName;sourceDisplayAlias=sourceDisplay;
 for(unsigned i=0;i<4;++i){unsigned r=i==1?2:i==3?0:1;at<void*>(unit[i],0x68)=resource[r];at<Ogre::Vector3>(unit[i],0x84)=position(i);at<unsigned>(unit[i],0x1ac)=10+i;at<unsigned>(unit[i],0x178)=900+i;at<unsigned long long>(unit[i],0x170)=0x77000000ULL+i;seedOrientation(unit[i],3);
  NEED((dynamic_cast<CCharacter*>(unit[i])!=0)==(kind(i)==Character));NEED((dynamic_cast<CItem*>(unit[i])!=0)==(kind(i)==Item||kind(i)==Equipment));NEED((dynamic_cast<CEquipment*>(unit[i])!=0)==(kind(i)==Equipment));NEED(at<void*>(unit[i],0x58)==0);
  if(kind(i)==Character){at<Wide>(unit[i],0x4c0)=destinationName(i);sourceNames[i]=at<Wide>(unit[i],0x4c0);sourceNameAliases[i]=sourceNames[i];}
  if(kind(i)==Equipment){at<bool>(unit[i],0x348)=false;NEED(at<void*>(unit[i],0x1e8)==0);}
 }
 // Genuine linked-list heads/nodes, borrowing real source units. Original
 // enumeration traverses Character first, then Item and Equipment.
 typedef TLinkedList<CCharacter*> Characters;typedef TLinkedList<CItem*> Items;
 Characters*characters=::new(raw(sizeof(Characters)))Characters;Items*items=::new(raw(sizeof(Items)))Items;
 TLinkedListNode<CCharacter*>*c=::new(raw(sizeof(TLinkedListNode<CCharacter*>)))TLinkedListNode<CCharacter*>;
 TLinkedListNode<CItem*>*a=::new(raw(sizeof(TLinkedListNode<CItem*>)))TLinkedListNode<CItem*>;TLinkedListNode<CItem*>*b=::new(raw(sizeof(TLinkedListNode<CItem*>)))TLinkedListNode<CItem*>;
 c->m_Data=static_cast<CCharacter*>(unit[0]);c->m_pNext=c->m_pPrevious=0;a->m_Data=static_cast<CItem*>(unit[1]);a->m_pPrevious=0;a->m_pNext=b;b->m_Data=static_cast<CItem*>(unit[2]);b->m_pPrevious=a;b->m_pNext=0;
 at<void*>(characters,0)=c;at<void*>(items,0)=a;at<void*>(level[0],0x98)=characters;at<void*>(level[0],0xa0)=items;
 enumerationWorld[0]=characters;enumerationWorld[1]=items;enumerationWorld[2]=c;enumerationWorld[3]=a;enumerationWorld[4]=b;for(unsigned i=0;i<5;++i){enumerationSize[i]=i<2?8:24;std::memcpy(enumerationBefore[i],enumerationWorld[i],enumerationSize[i]);}
 for(unsigned l=0;l<2;++l){::new(&alternate[l])Properties(3);for(unsigned j=0;j<3;++j){list(l).add(property[l?2-j:j]);alternate[l].add(property[2-j]);}at<unsigned>(&list(l),8)=cs->count;at<unsigned>(&list(l),12)=cs->capacity;listBacking[l][0]=at<CPropertyNode**>(&list(l),0);listBacking[l][1]=at<CPropertyNode**>(&alternate[l],0);}
 for(unsigned i=0;i<3;++i){std::memcpy(propertyBefore[i],property[i],0x158);std::memcpy(boundsBefore[i],at<void*>(property[i],0x148),0xb8);std::memcpy(levelBefore[i],level[i],LevelSize);std::memcpy(resourceBefore[i],resource[i],0x48);}
 for(unsigned i=0;i<4;++i)std::memcpy(unitBefore[i],unit[i],UnitSize);
 std::memcpy(recordBefore,record,0xc8);for(unsigned i=0;i<2;++i)std::memcpy(questBefore[i],quest[i],0x218);
}
static void initializeModel(){
 model.quest=0;model.unique=uniquePayload(cs->name);for(unsigned i=0;i<2;++i){model.questResource[i]=i;model.manager[i]=i;model.listCount[i]=cs->count;model.listCapacity[i]=cs->capacity;model.listBank[i]=0;for(unsigned j=0;j<3;++j)model.slots[i][j]=i?2-j:j;}
 for(unsigned i=0;i<3;++i){model.resourceLevel[i]=(i+1)%3;model.tempSlot[i]=i;}if(cs->helperGuard==3)model.resourceLevel[0]=100;
 for(unsigned i=0;i<4;++i){model.unitResource[i]=i==1?2:i==3?0:1;model.unitOrientation[i]=3;model.unitState[i]=900+i;model.guid[i]=0x77000000ULL+i;model.identified[i]=0;model.names[i]=kind(i)==Character?destinationName(i):Wide();}
 model.tempCount=cs->nullFirst?1:3;model.tempCapacity=10;
}
static void checkUntouched(){
 const unsigned char*p=reinterpret_cast<const unsigned char*>(record);for(unsigned j=0;j<0xc8;++j){bool mutableByte=j>=0x18&&j<0x20;if((cs->mode==NameAfterNPC||cs->mode==NameClearedAfterNPC)&&j>=0x70&&j<0x78)mutableByte=true;if(!mutableByte)NEED(p[j]==recordBefore[j]);}
 NEED(record->m_displayName==sourceDisplay);NEED(sourceDisplay==sourceDisplayAlias);NEED(sourceDisplay==L"Display name must never replace unique name");NEED(record->m_generatedChampionName==L"Champion name remains untouched");NEED(sourceUnique==sourceUniqueAlias);NEED(sourceUnique==uniquePayload(cs->name));
 for(unsigned i=0;i<4;++i){p=reinterpret_cast<const unsigned char*>(unit[i]);for(unsigned j=0;j<UnitSize;++j){bool mutableByte=(j>=0x68&&j<0x70)||(j>=0x9c&&j<0x100)||(j>=0x170&&j<0x17c)||(kind(i)==Character&&j>=0x4c0&&j<0x4c8)||(kind(i)==Equipment&&j==0x348);if(!mutableByte)NEED(p[j]==unitBefore[i][j]);}
  if(kind(i)==Character){NEED(sourceNames[i]==sourceNameAliases[i]);NEED(sourceNames[i]==destinationName(i));}
 }
 for(unsigned i=0;i<3;++i){NEED(!std::memcmp(propertyBefore[i],property[i],0x158));NEED(!std::memcmp(boundsBefore[i],at<void*>(property[i],0x148),0xb8));p=reinterpret_cast<const unsigned char*>(resource[i]);for(unsigned j=0;j<0x48;++j)if(!(j>=0x18&&j<0x20))NEED(p[j]==resourceBefore[i][j]);p=reinterpret_cast<const unsigned char*>(level[i]);for(unsigned j=0;j<LevelSize;++j)if(!(i==0&&((j>=0xf0&&j<0x100)||(j>=0x108&&j<0x118))))NEED(p[j]==levelBefore[i][j]);}
 for(unsigned i=0;i<5;++i)NEED(!std::memcmp(enumerationBefore[i],enumerationWorld[i],enumerationSize[i]));
 for(unsigned i=0;i<2;++i){p=reinterpret_cast<const unsigned char*>(quest[i]);for(unsigned j=0;j<0x218;++j)if(!(j>=0x1d0&&j<0x1e0))NEED(p[j]==questBefore[i][j]);NEED(at<void*>(manager[i],0x10)==0);}
 for(unsigned i=0;i<blockCount;++i)for(unsigned j=0;j<16;++j){NEED(blocks[i].p[int(j)-16]==0xa6);NEED(blocks[i].p[blocks[i].size+j]==0x6a);}
}
static void cleanup(){
 for(unsigned i=0;i<3;++i){at<Properties>(level[i],0xf0).~Properties();at<Properties>(level[i],0x108).~Properties();}for(unsigned i=0;i<2;++i)alternate[i].clear();
 record->m_children.clear();qcRecordDtor(record);qcGroupDtor(group);for(unsigned i=0;i<3;++i){at<void*>(resource[i],0x18)=0;qcResourceDtor(resource[i]);}
 // Original PropertyNodes, their genuine CCullingBounds, and original-derived
 // units/nested allocations remain alive to fork exit. Null-resource Property
 // D1 would itself need world state; no fake teardown or whole-heap claim.
}
static size_t snapshotBytes(const State&s){size_t bytes=4+16+12+4*(16+64+36)+2*24+8+4*s.unique.size();for(unsigned i=0;i<4;++i){if(kind(i)==Character)bytes+=8+4*s.names[i].size();if(kind(i)==Equipment)bytes+=4;}return bytes;}
static void side(void*context,autotest::Capture&out,bool candidate){
 cs=static_cast<Case*>(context);cap=&out;setup();initializeModel();wanted.clear();expectedFault=0;unsigned predictedCaught=0;
 try{simulate();}catch(const Stop&s){predictedCaught=s.code;}NEED(predictedCaught==cs->fault);
 // Exact planned serialization bound, including final snapshot/trailer and a
 // conservative returned-pointer word even on unwind. Reserve 16 KiB for
 // bounded semantic-control extra events. Long-name cases are property-only.
 size_t plannedBytes=36+snapshotBytes(model);for(unsigned i=0;i<wanted.size();++i)plannedBytes+=48+snapshotBytes(wanted[i].state);
 if(plannedBytes>autotest::Capture::kSize-16384){out.issue=autotest::Capture::InvalidReport;return;}
 activeSource=activeResource=activeLevel=0;unsigned caught=0;
 {detour::Set position,orientation,setOrientation,spawn,enumerate,random,npc,text,contracts,arrays;pPosition=&position;pOrientation=&orientation;pSetOrientation=&setOrientation;pSpawn=&spawn;pEnumerate=&enumerate;pRandom=&random;pNPC=&npc;pText=&text;pDelete=&arrays;
  TL_REDIRECT(position,qcBoundaryPosition,&callPosition);TL_REDIRECT(orientation,qcBoundaryOrientation,&callOrientation);TL_REDIRECT(setOrientation,qcBoundarySetOrientation,&callSetOrientation);TL_REDIRECT(spawn,qcBoundarySpawn,&callSpawn);TL_REDIRECT(enumerate,qcBoundaryEnumerate,&callEnumerate);TL_REDIRECT(random,qcBoundaryRandom,&callRandom);TL_REDIRECT(npc,qcBoundaryNPC,&callNPC);TL_REDIRECT(text,qcBoundaryText,&callText);
  TL_REDIRECT(contracts,qcFloat,&randomFloat);TL_REDIRECT(contracts,qcInteger,&randomInteger);TL_REDIRECT(contracts,qcRegion,&noSpawn);TL_REDIRECT(contracts,qcRange,&lowerRange);TL_REDIRECT(contracts,qcCreate,&lowerCreate);TL_REDIRECT(contracts,qcAdd,&lowerAdd);TL_REDIRECT(contracts,qcDrop,&drop);TL_REDIRECT(contracts,qcSnap,&snap);TL_REDIRECT(contracts,qcISA,&lowerISA);arrays.redirect(qcDeleteArray,qcDeleteArray,&deleteArray);
  if(position.failed()||orientation.failed()||setOrientation.failed()||spawn.failed()||enumerate.failed()||random.failed()||npc.failed()||text.failed()||contracts.failed()||arrays.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef CPositionableObject*(*Fn)(CQuestUnitData*,CLevel*);Fn invoke=candidate?&qcNew:&qcOld;if(!autotest::beginInvocation(out,invoke))return;
  try{CPositionableObject*result=invoke(record,cs->nullLevel?0:level[0]);actualResult=uid(result);n(actualResult);NEED(actualResult==modelResult);out.callCompleted=1;}catch(const Stop&s){caught=s.code;}catch(...){caught=999;NEED(false);}
  n(caught);NEED(caught==predictedCaught);NEED(faultHits==(cs->fault?1u:0u));NEED(eventIndex==wanted.size());snapshot(&model);
  // Do not touch the expired stack Units object. Only the recorded backing
  // pointer identity and its matching delete[] observations survive the call.
  n(enumFilled);n(arrayPointer!=0);n(arrayFrees);n(arrayDoubleFree);NEED(arrayDoubleFree==0);NEED(arrayFrees==modelFrees);NEED(enumFilled==(modelFrees!=0));NEED((arrayPointer!=0)==(modelFrees!=0));
  NEED(!position.failed()&&!orientation.failed()&&!setOrientation.failed()&&!spawn.failed()&&!enumerate.failed()&&!random.failed()&&!npc.failed()&&!text.failed()&&!contracts.failed()&&!arrays.failed());
 }
 checkUntouched();record->m_uniqueUnitName+=L" after invocation";NEED(sourceUnique==uniquePayload(cs->name));NEED(sourceUnique==sourceUniqueAlias);
 for(unsigned i=0;i<4;++i)if(kind(i)==Character){Wide retained=at<Wide>(unit[i],0x4c0);at<Wide>(unit[i],0x4c0)+=L" destination after invocation";NEED(sourceNames[i]==destinationName(i));NEED(sourceNames[i]==sourceNameAliases[i]);NEED(retained==model.names[i]);}
 cleanup();n(firstError);n(0x51435543u);n(errors);
}
static void oldSide(void*p,autotest::Capture&o){side(p,o,false);}static void newSide(void*p,autotest::Capture&o){side(p,o,true);}
static bool oracle(const autotest::Outcome&o){unsigned t[2]={0,1};if(o.capture.length>=8)std::memcpy(t,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&t[0]==0x51435543u&&!t[1];}
static unsigned failureLine(const autotest::Outcome&o){unsigned n=0;if(o.capture.length>=12)std::memcpy(&n,o.capture.data+o.capture.length-12,4);return n;}
static bool pair(const tlhybrid_host*host,autotest::Coverage&coverage,Case&c,unsigned&completed,unsigned&unwinds,unsigned&originalFailures,unsigned&candidateFailures){
 autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);bool oa=oracle(a),ob=oracle(b);if(!oa)++originalFailures;if(!ob)++candidateFailures;bool ok;
 if(c.fault){++unwinds;ok=oa&&ob&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==0xd3e160&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);}
 else{++completed;ok=coverage.observe(host,a,b)==0&&oa&&ob;}
 if(!ok){host->log("    createUnit pair=%u/%u mode=%u search=%u kind=%u blocked=%u fault=%u.%u status=%d/%d oracle=%u/%u line=%u/%u\n",completed,unwinds,c.mode,c.search,c.kind,c.blocked,c.fault,c.occurrence,a.childStatus,b.childStatus,oa,ob,failureLine(a),failureLine(b));coverage.report(host);}return ok;
}
#undef NEED
}
TL_TEST(quest_unit_create_closure){using namespace qc;autotest::Coverage coverage("quest_unit_create_closure",0xd3e160);std::vector<Case>normal,faults;unsigned completed=0,unwinds=0,originalFailures=0,candidateFailures=0;
 // All disabled-create cases retain a valid latent graph for a guard mutant.
 for(unsigned search=0;search<2;++search){Case c;c.create=false;c.search=search?2:0;normal.push_back(c);}
 for(unsigned create=0;create<2;++create){Case c;c.create=create;c.nullLevel=true;normal.push_back(c);}
 // Three valid backing slots always exist. count+1 is an explicitly controlled
 // finite RNG endpoint beyond the usual distribution, never an invalid load.
 for(unsigned search=0;search<2;++search)for(unsigned count=1;count<=3;++count)for(unsigned sample=0;sample<4;++sample)for(unsigned result=0;result<5;++result){Case c;c.search=search;c.count=count;c.floating=sample==0?1.f:sample==1?float(count):sample==2?float(count)-.25f:float(count)+1.f;c.spawnResult=result?1:0;c.kind=result?result-1:Base;normal.push_back(c);}
 for(unsigned search=0;search<2;++search)for(unsigned capacity=1;capacity<=2;++capacity)for(unsigned sample=0;sample<2;++sample)for(unsigned kind=Character;kind<=Item;++kind){Case c;c.search=search;c.capacity=capacity;c.floating=sample?3.f:2.5f;c.kind=kind;normal.push_back(c);}
 for(unsigned search=0;search<2;++search)for(unsigned name=0;name<5;++name){Case c;c.search=search;c.kind=Character;c.name=name;c.floating=2.f;normal.push_back(c);}
 for(unsigned search=0;search<2;++search)for(unsigned guard=1;guard<=3;++guard){Case c;c.search=search;c.helperGuard=guard;c.kind=Character;normal.push_back(c);}
 const unsigned blocked[]={0,1,2,40,41,42};
 for(unsigned path=0;path<3;++path)for(unsigned selection=0;selection<3;++selection)for(unsigned b=0;b<6;++b)for(unsigned result=0;result<3;++result){Case c;c.search=path;c.count=path<2?0:3;c.selection=selection;c.blocked=blocked[b];c.spawnResult=result;normal.push_back(c);}
 for(unsigned selection=0;selection<2;++selection)for(unsigned result=0;result<2;++result){Case c;c.search=2;c.selection=selection?-1:10;c.blocked=2;c.spawnResult=result;normal.push_back(c);}
 for(unsigned kind=Base;kind<=Equipment;++kind){Case c;c.search=2;c.kind=kind;c.blocked=2;normal.push_back(c);}
 {Case c;c.search=2;c.nullFirst=true;normal.push_back(c);}
 for(unsigned mode=QuestAfterPosition;mode<=ManagerAfterOrientation;++mode){Case c;c.mode=mode;c.kind=Character;c.floating=2.f;
  if((mode>=SourceAfterPosition&&mode<=LevelAfterRange)||(mode>=TempCountAfterRegion&&mode<=MutateRegionInput)){c.search=2;c.blocked=2;}
  if(mode==DataAfterSpawn)c.floating=3.f;
  if(mode==TempCapacityAfterRng)c.selection=2;
  if(mode==TempCountAfterRegion)c.selection=1;
  if(mode==TempSlotAfterRegion)c.selection=10;
  normal.push_back(c);
 }
 // One before-boundary exception per event, except Enumerate deliberately
 // throws after genuine filling so the target owns a real allocated array.
 for(unsigned fault=FloatRng;fault<=Text;++fault){Case c;c.fault=fault;c.kind=Character;
  if(fault==Enumerate||fault==IntegerRng||fault==Random||fault==Range||fault==Region)c.search=2;
  if(fault==Snap)c.kind=Item;if(fault==Text)c.kind=Equipment;faults.push_back(c);
 }
 const unsigned late[]={Position,Spawn,Create,Add};for(unsigned i=0;i<4;++i){Case c;c.search=2;c.blocked=2;c.fault=late[i];if(late[i]==Position)c.occurrence=2;faults.push_back(c);}
 for(unsigned occurrence=2;occurrence<=42;occurrence+=40){Case c;c.search=2;c.blocked=42;c.fault=Region;c.occurrence=occurrence;faults.push_back(c);}
 if(normal.size()!=349||faults.size()!=22){host->log("    createUnit fixture inventory mismatch %u/%u\n",unsigned(normal.size()),unsigned(faults.size()));return 1;}
 for(unsigned i=0;i<normal.size();++i)if(!pair(host,coverage,normal[i],completed,unwinds,originalFailures,candidateFailures))return 1;
 for(unsigned i=0;i<faults.size();++i)if(!pair(host,coverage,faults[i],completed,unwinds,originalFailures,candidateFailures))return 1;
 coverage.report(host);host->log("    createUnit: %u completed finite pairs; %u excluded unwinds; oracle failures original=%u candidate=%u; target-owned fallback arrays require one matching delete[]. Only d3e160 receives credit.\n",completed,unwinds,originalFailures,candidateFailures);
 return completed!=349||unwinds!=22||coverage.completed!=completed||coverage.different||coverage.missing||originalFailures||candidateFailures;
}
