// Authored from original 0xd488f0..0xd48d00, ELF 91b41ae9...174b.
// Draft only: no compilation or execution performed while authoring.
// Acceptance is exclusively unitDefeated. Original constructors/ISA/position/
// tags/unsigned formatter/UI execute; explicitly bounded environment contracts
// replace group lookup, spawning, ResourceManager ISA/dungeon lookup and CEGUI.
// No world, dependency acceptance, global allocation balance or LSDA claim.
#include <climits>
#include <cstdio>
#include <cstring>
#include <new>
#include <string>
#include <vector>
#include <CEGUI.h>
#include "AutoTest.h"
#include "Detour.h"
#include "Quest.h"
#include "QuestUnitData.h"
#include "Character.h"
#include "GameUI.h"
#include "TRepository.h"

TL_ORIGINAL(bool,qdOld,(CQuestUnitData*,CBaseUnit*),"_ZN14CQuestUnitData12unitDefeatedEP9CBaseUnit")
extern "C" bool qdNew(CQuestUnitData*,CBaseUnit*) __asm__("_ZN14CQuestUnitData12unitDefeatedEP9CBaseUnit");
TL_FUNCTION(qdTarget,"_ZN14CQuestUnitData12unitDefeatedEP9CBaseUnit")
TL_ORIGINAL(void,qdUnitCtor,(void*,void*),"_ZN14CQuestUnitDataC1EP6CQuest")
TL_ORIGINAL(void,qdUnitDtor,(void*),"_ZN14CQuestUnitDataD1Ev")
TL_ORIGINAL(void,qdCharacterCtor,(void*,void*),"_ZN10CCharacterC1EP16CResourceManager")
TL_ORIGINAL(void,qdBaseCtor,(void*,void*,int),"_ZN9CBaseUnitC1EP16CResourceManager14EBASEUNIT_TYPE")
TL_ORIGINAL(void,qdResourceCtor,(void*,void*),"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_ORIGINAL(void,qdResourceDtor,(void*),"_ZN16CResourceManagerD1Ev")
TL_ORIGINAL(void,qdGroupCtor,(void*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,qdGroupDtor,(void*),"_ZN10CDataGroupD1Ev")
#define QD_DEP(R,N,A,S) TL_ORIGINAL(R,qdOriginal##N,A,S) TL_FUNCTION(qdBoundary##N,S)
QD_DEP(bool,ISA,(CBaseUnit*,int),"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
QD_DEP(Ogre::Vector3,Position,(CBaseUnit*,bool),"_ZN19CPositionableObject11getPositionEb")
QD_DEP(std::wstring,Tags,(CQuest*,const std::wstring&),"_ZN6CQuest17replaceStringTagsERKSbIwSt11char_traitsIwESaIwEE")
QD_DEP(std::wstring,Unsigned,(unsigned),"_ZN7STRINGS17GetValueAsWStringEj")
// Non-owning invisible-reference spies preserve the exact GCC 4.4 by-value
// parameter object. The TARGET call site destroys it, including on exception.
QD_DEP(void,Big,(CGameUI*,std::wstring&,float),"_ZN7CGameUI10setBigTextESbIwSt11char_traitsIwESaIwEEf")
QD_DEP(void,Small,(CGameUI*,std::wstring&,float),"_ZN7CGameUI12setSmallTextESbIwSt11char_traitsIwESaIwEEf")
#undef QD_DEP
TL_FUNCTION(qdGroup,"_ZN14CQuestUnitData20getBaseUnitDataGroupEv")
TL_FUNCTION(qdSpawn,"_ZN14CQuestUnitData18spawnChildrenUnitsEP16CResourceManagerRKN4Ogre7Vector3E")
TL_FUNCTION(qdResourceISA,"_ZN16CResourceManager3ISAEN9UNITTYPES10EUNITTYPESES1_")
TL_FUNCTION(qdDungeon,"_ZN16CResourceManager16getDungeonByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qdMaster,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(qdGuid,"_ZN9UTILITIES16createUniqueGuidEv")
extern "C" char qdVisible[] __asm__("_ZN5CEGUI6Window10setVisibleEb");
extern "C" char qdProperty[] __asm__("_ZN5CEGUI11PropertySet11setPropertyERKNS_6StringES3_");

namespace qd {
typedef std::wstring Wide;
enum { MaxNodes=4, UISize=0x1a08, BigOffset=0x1978, SmallOffset=0x1988 };
typedef char ABI[sizeof(Wide)==8&&sizeof(wchar_t)==4&&sizeof(CQuestUnitData)==0xc8&&sizeof(CQuest)==0x218&&sizeof(CCharacter)==0x778&&sizeof(CBaseUnit)==0x1d8?1:-1];
enum Code { Lookup=1,ISA,Tags,Big,Unsigned,Small,Position,Spawn,Visible,White,Black,Dungeon };
enum Mode { Plain=0,ReloadType,ReloadCountDown,ReloadCountUp,ReloadUIAfterTags,
    ReloadUIAfterFormat,ReloadResourceAfterPosition,ShrinkChildren,GrowChildren,
    ReloadCapacity,CopyParameter,ReloadRequired,ReloadName };
struct Node {
    unsigned cache,lookup,type,spawnType,count,required,children,capacity;
    bool track,complete,create,quest;
    Node():cache(1),lookup(1),type(22),spawnType(30),count(0),required(2),children(0),capacity(0),track(true),complete(false),create(false),quest(true){}
};
struct Case {
    Node node[MaxNodes];unsigned total,unitGroup,association,payload,name,resource,mode,fault,faultOccurrence,repeats;
    bool character,matchISA,otherISA,notifyISA,nullUnit;
    Case():total(1),unitGroup(1),association(0),payload(1),name(1),resource(0),mode(0),fault(0),faultOccurrence(1),repeats(1),character(true),matchISA(false),otherISA(false),notifyISA(false),nullUnit(false){}
};
struct Stop {unsigned code;explicit Stop(unsigned c):code(c){}};
struct Event {unsigned code,id,arg;Wide text;Node state[MaxNodes];};
struct Block {unsigned char*p;unsigned size;};
static const Case* cs;static autotest::Capture* cap;
static CQuestUnitData* node[MaxNodes];static CQuest* quest;static CBaseUnit* unit;
static CDataGroup* group[2];static void* resource[2];static void* level;static void* client;
static CGameUI* ui[2];static void* window[2][2];static TRepository<Wide>* repository[2];
static Block blocks[24];static unsigned blockCount;
static Node model[MaxNodes];static std::vector<Event> wanted;
static unsigned eventIndex,errors,firstError,faultHits,expectedFault,seenFault,tagDepth,uiKind,uiIndex,uiStep,modelUI,isaCalls,modelISAs,modelResource,modelFormats,formatCalls;
static unsigned activeNode;static bool modelResult;
static Wide sourceQuest,sourceName,sourceQuestAlias,sourceNameAlias,uiEntry;
static Wide modelName;static Wide expectedCache[2][2];static float expectedDuration[2][2],expectedFade[2][2];
static unsigned char uiBefore[2][UISize],nodeBefore[MaxNodes][0xc8],unitBefore[0x778];
static detour::Set *pISA,*pPosition,*pTags,*pUnsigned,*pBig,*pSmall;
template<class T>T& at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
static void check(bool ok,unsigned line){if(!ok){if(!errors)firstError=line;++errors;}}
#define NEED(x) check((x),__LINE__)
static void n(unsigned x){cap->add(&x,sizeof(x));}
static unsigned id(void*p){for(unsigned i=0;i<cs->total;++i)if(p==node[i])return i;return 99;}
static unsigned gid(void*p){return p==group[0]?1:p==group[1]?2:p==0?0:99;}
static unsigned rid(void*p){return p==resource[0]?1:p==resource[1]?2:p==0?0:99;}
static unsigned uid(void*p){return p==ui[0]?0:p==ui[1]?1:99;}
static void* raw(unsigned size){
 if(blockCount>=24){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}
 unsigned char*p=static_cast<unsigned char*>(autotest::allocate(size+32));
 if(!p){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}
 std::memset(p,0xa6,16);std::memset(p+16,0,size);std::memset(p+16+size,0x6a,16);
 blocks[blockCount].p=p+16;blocks[blockCount++].size=size;return p+16;
}
static Wide decimal(unsigned v){char s[32];std::snprintf(s,sizeof(s),"%u",v);Wide r;for(const char*p=s;*p;++p)r+=wchar_t(*p);return r;}
static Wide payload(unsigned which){
 if(!which)return Wide();
 if(which==1)return L"Depth [DEPTH]; defeat [DEFEATCOMPLETECOUNT]; acquire [ACQUIRECOMPLETECOUNT]";
 if(which==2)return Wide(L"\u03a9\0[DEPTH]\u4e2d",10);
 return Wide(300,L'Q')+L" [UNKNOWN]";
}
static Wide tagsExpected(){
 if(!cs->payload)return Wide();
 if(cs->payload==1)return L"Depth 5; defeat 0; acquire 0";
 if(cs->payload==2)return Wide(L"\u03a9\0",2)+L"5\u4e2d";
 return payload(cs->payload);
}
static Wide namePayload(unsigned which){
 if(!which)return Wide();if(which==1)return L"Enemy \u03a9";
 if(which==2)return Wide(L"A\0\u0416\u4e2d",4);return Wide(320,L'N');
}
static bool membership(unsigned type){if(type==25)return cs->notifyISA;if(type==31)return cs->otherISA;return cs->matchISA;}
static void append(unsigned code,unsigned index,unsigned arg=0,const Wide& text=Wide()){
 Event e;e.code=code;e.id=index;e.arg=arg;e.text=text;for(unsigned i=0;i<cs->total;++i)e.state[i]=model[i];wanted.push_back(e);
 if(cs->fault==code&&++expectedFault==cs->faultOccurrence)throw Stop(code);
}
static void modelUIEvents(unsigned kind,unsigned index,const Wide& text){
 if(text.empty())append(Visible,index,0);
 else{if(kind==0)append(Visible,index,1);append(White,index,kind);append(Black,index,kind);}
}
static bool modelISA(unsigned index,unsigned type){
 append(ISA,index,type);++modelISAs;
 bool value=modelResource!=0&&membership(type);
 if(cs->mode==ReloadType&&modelISAs==1)model[0].type=31;
 return value;
}
static bool simulate(unsigned index,unsigned depth){
 if(depth>MaxNodes){NEED(false);return false;}Node& x=model[index];if(!x.track)return false;
 if(!x.cache){append(Lookup,index);if(index==1){
   if(cs->mode==ShrinkChildren)model[0].children=1;
   if(cs->mode==GrowChildren)model[0].children=3;
   if(cs->mode==ReloadCapacity)model[0].capacity=1;
  }x.cache=x.lookup;}
 bool primary=x.cache==cs->unitGroup;
 if(!primary)primary=modelISA(index,x.type);
 bool associated=x.type!=22&&modelISA(index,x.type);
 if(!associated){NEED(x.quest);associated=cs->association==1;}
 if(x.spawnType==22&&x.create)primary=associated;
 if(!x.complete&&primary){
  ++x.count;
  if(modelResource&&cs->resource==2&&x.quest&&modelISA(index,25)&&cs->character){
   append(Tags,index,0,sourceQuest);append(Dungeon,index,0,L"fixture missing dungeon");
   if(cs->mode==ReloadUIAfterTags)modelUI=1;
   append(Big,modelUI,0,tagsExpected());modelUIEvents(0,modelUI,tagsExpected());
   if(cs->mode==ReloadName)modelName=L"Changed name after big text";
   unsigned required=x.required;
   append(Unsigned,index,required);++modelFormats;
   if(cs->mode==ReloadRequired&&modelFormats==1)x.required=9;
   if(cs->mode==ReloadUIAfterFormat&&modelFormats==1)modelUI=1;
   unsigned count=x.count;append(Unsigned,index,count);++modelFormats;
   Wide small=modelName+L" - "+decimal(count)+L"/"+decimal(required)+L" Defeated";
   append(Small,modelUI,0,small);modelUIEvents(1,modelUI,small);
   if(cs->mode==ReloadCountDown)x.count=0;
   if(cs->mode==ReloadCountUp)x.count=x.required;
  }
  if(x.count>=x.required){append(Position,index,1);if(cs->mode==ReloadResourceAfterPosition)modelResource=2;append(Spawn,index,modelResource);x.complete=true;return true;}
 }else if(x.complete&&!primary&&x.children){
  for(unsigned i=0;i<x.children&&i<3;++i){unsigned selected=i<x.capacity?i+1:1;if(simulate(selected,depth+1))return true;}
 }
 return false;
}
static void snapshot(const Node* expect){
 for(unsigned i=0;i<cs->total;++i){Node a;a.cache=gid(node[i]->m_pBaseUnitDataGroup);a.type=at<unsigned>(node[i],0x44);a.count=at<unsigned>(node[i],0x3c);a.required=at<unsigned>(node[i],0x38);a.complete=node[i]->m_completed;a.children=at<unsigned>(node[i],0x50);a.capacity=at<unsigned>(node[i],0x54);
  n(a.cache);n(a.type);n(a.count);n(a.required);n(a.complete);n(a.children);n(a.capacity);
  if(expect){const Node&e=expect[i];NEED(a.cache==e.cache);NEED(a.type==e.type);NEED(a.count==e.count);NEED(a.required==e.required);NEED(a.complete==e.complete);NEED(a.children==e.children);NEED(a.capacity==e.capacity);}
 }
}
static unsigned emit(unsigned code,unsigned actualID,unsigned arg=0,const Wide& text=Wide()){
 n(code);n(actualID);n(arg);cap->addText(text);unsigned owner=0;
 NEED(eventIndex<wanted.size());
 if(eventIndex<wanted.size()){const Event&e=wanted[eventIndex];NEED(e.code==code);NEED(e.id==actualID);NEED(e.arg==arg);NEED(e.text==text);owner=e.id;snapshot(e.state);}else snapshot(0);
 ++eventIndex;
 if(cs->fault==code&&++seenFault==cs->faultOccurrence){++faultHits;throw Stop(code);}
 return owner;
}
static unsigned expectedOwner(unsigned code){
 if(eventIndex<wanted.size()&&wanted[eventIndex].code==code)return wanted[eventIndex].id;
 NEED(false);return 0;
}
static void* noMaster(){return 0;}static unsigned long long constantGuid(){return 0x54667788ULL;}
static bool resourceISA(void*p,unsigned type,unsigned parent){NEED(p==resource[0]||p==resource[1]);NEED(type==27);return membership(parent);}
static void* dungeon(void*p,const Wide& name){NEED(p==resource[0]);NEED(name==L"fixture missing dungeon");emit(Dungeon,activeNode,0,name);return 0;}
static CDataGroup* lookup(CQuestUnitData*p){unsigned index=id(p);emit(Lookup,index);if(index>=cs->total)return 0;
 if(index==1){if(cs->mode==ShrinkChildren)at<unsigned>(node[0],0x50)=1;if(cs->mode==GrowChildren)at<unsigned>(node[0],0x50)=3;if(cs->mode==ReloadCapacity)at<unsigned>(node[0],0x54)=1;}
 unsigned g=cs->node[index].lookup;return g?group[g-1]:0;
}
static bool callISA(CBaseUnit*p,int type){unsigned index=expectedOwner(ISA);emit(ISA,index,static_cast<unsigned>(type));NEED(p==unit);if(p!=unit)return false;
 ++isaCalls;pISA->restore();bool result=false;
 try{result=qdOriginalISA(p,type);}catch(...){TL_REDIRECT(*pISA,qdBoundaryISA,&callISA);throw;}TL_REDIRECT(*pISA,qdBoundaryISA,&callISA);
 NEED(result==(at<void*>(unit,0x68)!=0&&membership(type)));
 if(cs->mode==ReloadType&&isaCalls==1)node[0]->m_unitType=31;return result;
}
static Ogre::Vector3 callPosition(CBaseUnit*p,bool absolute){unsigned index=expectedOwner(Position);emit(Position,index,absolute);NEED(p==unit);if(p!=unit)return Ogre::Vector3(0,0,0);
 pPosition->restore();Ogre::Vector3 v;
 try{v=qdOriginalPosition(p,absolute);}catch(...){TL_REDIRECT(*pPosition,qdBoundaryPosition,&callPosition);throw;}TL_REDIRECT(*pPosition,qdBoundaryPosition,&callPosition);
 NEED(v==Ogre::Vector3(3.25f,-4.5f,7.75f));cap->add(&v,sizeof(v));
 if(cs->mode==ReloadResourceAfterPosition)at<void*>(unit,0x68)=resource[1];return v;
}
static void spawn(CQuestUnitData*p,void*r,const Ogre::Vector3& pos){unsigned index=id(p);emit(Spawn,index,rid(r));NEED(index<cs->total);if(index<cs->total)NEED(!node[index]->m_completed);NEED(pos==Ogre::Vector3(3.25f,-4.5f,7.75f));cap->add(&pos,sizeof(pos));}
static Wide callTags(CQuest*p,const Wide& input){unsigned index=expectedOwner(Tags);activeNode=index;emit(Tags,index,0,input);NEED(p==quest);NEED(&input==&quest->m_sUnknown58);if(p!=quest)return Wide(L"invalid quest");
 pTags->restore();++tagDepth;
 try{Wide result=qdOriginalTags(p,input);--tagDepth;TL_REDIRECT(*pTags,qdBoundaryTags,&callTags);NEED(result==tagsExpected());if(cs->mode==ReloadUIAfterTags)at<void*>(client,0x78)=ui[1];return result;}
 catch(...){--tagDepth;TL_REDIRECT(*pTags,qdBoundaryTags,&callTags);throw;}
}
static Wide callUnsigned(unsigned value){
 bool direct=tagDepth==0;unsigned index=direct?expectedOwner(Unsigned):activeNode;if(direct){emit(Unsigned,index,value);++formatCalls;}
 pUnsigned->restore();try{Wide result=qdOriginalUnsigned(value);TL_REDIRECT(*pUnsigned,qdBoundaryUnsigned,&callUnsigned);NEED(result==decimal(value));
  if(direct&&cs->mode==ReloadRequired&&formatCalls==1)at<unsigned>(node[0],0x38)=9;
  if(direct&&cs->mode==ReloadUIAfterFormat&&formatCalls==1)at<void*>(client,0x78)=ui[1];return result;
 }catch(...){TL_REDIRECT(*pUnsigned,qdBoundaryUnsigned,&callUnsigned);throw;}
}
static Wide& cache(unsigned index,unsigned kind){return at<Wide>(ui[index],kind?SmallOffset:BigOffset);}
static void checkCache(unsigned index,unsigned kind){NEED(cache(index,kind)==expectedCache[index][kind]);NEED(at<float>(ui[index],kind?0x1990:0x1980)==expectedDuration[index][kind]);NEED(at<float>(ui[index],kind?0x1994:0x1984)==expectedFade[index][kind]);}
static void visible(void*p,bool value){emit(Visible,uiIndex,value);NEED(p==window[uiIndex][uiKind]);NEED(value==!uiEntry.empty());NEED(uiKind==0||!value);++uiStep;
 if(uiEntry.empty())expectedFade[uiIndex][uiKind]=0;checkCache(uiIndex,uiKind);
}
static void encoded(const CEGUI::String& s,const char* wantedText){
 unsigned length=std::strlen(wantedText);NEED(s.length()==length);unsigned bound=s.length()<128?s.length():128;n(s.length());for(unsigned i=0;i<bound;++i){NEED(i<length&&s[i]==static_cast<unsigned char>(wantedText[i]));n(s[i]);}
 NEED(!std::strcmp(s.c_str(),wantedText));
}
static void property(void*p,const CEGUI::String& key,const CEGUI::String& value){
 unsigned code=uiStep==(uiKind==0?1u:0u)?White:Black;emit(code,uiIndex,uiKind);NEED(p==window[uiIndex][uiKind]);encoded(key,code==White?"TextColour":"DropTextColour");encoded(value,code==White?"FFFFFFFF":"FF000000");++uiStep;
 expectedCache[uiIndex][uiKind]=uiEntry;expectedDuration[uiIndex][uiKind]=1.f;expectedFade[uiIndex][uiKind]=1.f;checkCache(uiIndex,uiKind);
}
static void callSmall(CGameUI*,Wide&,float);
static void callBig(CGameUI*p,Wide& text,float duration){
 unsigned index=uid(p);emit(Big,index,0,text);NEED(index<2);NEED(duration==1.f);cap->add(&duration,4);NEED(&text!=&quest->m_sUnknown58);NEED(&text!=&at<Wide>(unit,0x4c0));if(index>=2)return;
 uiKind=0;uiIndex=index;uiStep=0;uiEntry=text;pBig->restore();
 try{qdOriginalBig(p,text,duration);}catch(...){TL_REDIRECT(*pBig,qdBoundaryBig,&callBig);throw;}TL_REDIRECT(*pBig,qdBoundaryBig,&callBig);checkCache(index,0);
 NEED(uiStep==(text.empty()?1u:3u));if(cs->mode==CopyParameter){Wide kept=cache(index,0);text+=L" private parameter";NEED(cache(index,0)==kept);NEED(quest->m_sUnknown58==sourceQuest);}
 if(cs->mode==ReloadName)at<Wide>(unit,0x4c0)=L"Changed name after big text";
}
static void callSmall(CGameUI*p,Wide& text,float duration){
 unsigned index=uid(p);emit(Small,index,0,text);NEED(index<2);NEED(duration==1.f);cap->add(&duration,4);NEED(&text!=&quest->m_sUnknown58);NEED(&text!=&at<Wide>(unit,0x4c0));if(index>=2)return;
 uiKind=1;uiIndex=index;uiStep=0;uiEntry=text;pSmall->restore();
 try{qdOriginalSmall(p,text,duration);}catch(...){TL_REDIRECT(*pSmall,qdBoundarySmall,&callSmall);throw;}TL_REDIRECT(*pSmall,qdBoundarySmall,&callSmall);checkCache(index,1);NEED(uiStep==2);
 if(cs->mode==CopyParameter){Wide kept=cache(index,1);text+=L" private small parameter";NEED(cache(index,1)==kept);}
 if(cs->mode==ReloadCountDown)at<unsigned>(node[0],0x3c)=0;if(cs->mode==ReloadCountUp)at<unsigned>(node[0],0x3c)=at<unsigned>(node[0],0x38);
}
static void setup(){
 errors=firstError=blockCount=eventIndex=faultHits=seenFault=tagDepth=isaCalls=formatCalls=0;activeNode=0;autotest::g_arenaUsed=0;
 // Only constructor-referenced TU-local empty strings. No global repository
 // replacement and no sweep over unrelated global constructors.
 ::new(reinterpret_cast<void*>(0x14ff1a8))Wide();
 ::new(reinterpret_cast<void*>(0x147c348))Wide();
 ::new(reinterpret_cast<void*>(0x147c340))std::string();
 for(unsigned i=0;i<2;++i){repository[i]=new TRepository<Wide>(Wide());group[i]=static_cast<CDataGroup*>(raw(sizeof(CDataGroup)));qdGroupCtor(group[i],Wide(i?L"OTHER":L"DEFEATED"),0,4,4,repository[i]);}
 {
  detour::Set environment;TL_REDIRECT(environment,qdMaster,&noMaster);TL_REDIRECT(environment,qdGuid,&constantGuid);
  if(environment.failed()){cap->issue=autotest::Capture::InvalidReport;throw Stop(999);}
  for(unsigned i=0;i<2;++i){resource[i]=raw(sizeof(CResourceManager));qdResourceCtor(resource[i],0);}
  unit=static_cast<CBaseUnit*>(raw(0x778));
  if(cs->character)qdCharacterCtor(unit,0);else{qdBaseCtor(unit,0,0);::new(&at<Wide>(unit,0x4c0))Wide();}
 }
 // Accepted QuestStringTagsBoundaryTest scaffold, with explicit lifetimes for
 // the two empty outer arrays as well as both directly used wide strings.
 // This is not CQuest lifecycle coverage and never invokes CQuestD1.
 quest=static_cast<CQuest*>(raw(sizeof(CQuest)));
 ::new(&quest->m_pUnknown30)Wide(L"fixture missing dungeon");
 ::new(&quest->m_sUnknown58)Wide(payload(cs->payload));
 typedef TArrayList<TArrayList<CQuestUnitData*>*> Groups;
 ::new(&quest->m_Unknown130)Groups(1);::new(&quest->m_Unknown148)Groups(1);
 quest->m_iUnknown20=4;quest->m_iUnknown1C8=0x1357246813572468LL;
 quest->m_pResourceManager=static_cast<CResourceManager*>(resource[0]);
 sourceQuest=quest->m_sUnknown58;sourceQuestAlias=sourceQuest;
 at<Wide>(unit,0x4c0)=namePayload(cs->name);sourceName=at<Wide>(unit,0x4c0);sourceNameAlias=sourceName;
 NEED((dynamic_cast<CCharacter*>(unit)!=0)==cs->character);
 level=raw(0x240);client=raw(0x90);at<void*>(level,0x220)=client;
 for(unsigned i=0;i<2;++i){
  ui[i]=static_cast<CGameUI*>(raw(UISize));std::memset(ui[i],0x57,UISize);
  for(unsigned k=0;k<2;++k){
   ::new(&cache(i,k))Wide(k?L"retained small cache":L"retained BIG cache");expectedCache[i][k]=cache(i,k);
   expectedDuration[i][k]=k?7.5f:-3.25f;expectedFade[i][k]=k?.25f:.75f;
   at<float>(ui[i],k?0x1990:0x1980)=expectedDuration[i][k];at<float>(ui[i],k?0x1994:0x1984)=expectedFade[i][k];
   window[i][k]=raw(0x100);std::memset(window[i][k],0x33+i*2+k,0x100);at<void*>(ui[i],k?0x118:0x110)=window[i][k];
  }
  std::memcpy(uiBefore[i],ui[i],UISize);
 }
 at<void*>(client,0x78)=ui[0];
 for(unsigned i=0;i<2;++i)at<void*>(resource[i],0x18)=cs->resource==2?level:0;
 at<void*>(unit,0x68)=cs->resource?resource[0]:0;at<unsigned>(unit,0x1ac)=27;
 at<void*>(unit,0x1b0)=cs->unitGroup?group[cs->unitGroup-1]:0;
 at<long long>(unit,0x170)=cs->association==0?0x778899LL:quest->m_iUnknown1C8;
 at<unsigned>(unit,0x178)=cs->association==1?17:cs->association==2?99:41;
 at<Ogre::Vector3>(unit,0x84)=Ogre::Vector3(3.25f,-4.5f,7.75f);
 for(unsigned i=0;i<cs->total;++i){
  node[i]=static_cast<CQuestUnitData*>(raw(sizeof(CQuestUnitData)));qdUnitCtor(node[i],cs->node[i].quest?quest:0);
  const Node& x=cs->node[i];node[i]->m_questUnitDataId=17;node[i]->m_baseUnitGuid=0x1122334400000063LL;
  node[i]->m_pBaseUnitDataGroup=x.cache?group[x.cache-1]:0;node[i]->m_pQuestDataGroup=group[1];
  node[i]->m_unitType=x.type;node[i]->m_spawnFromUnitType=x.spawnType;node[i]->m_createUnit=x.create;
  node[i]->m_trackUnitEvents=x.track;node[i]->m_completed=x.complete;at<unsigned>(node[i],0x38)=x.required;at<unsigned>(node[i],0x3c)=x.count;
  node[i]->m_displayName=L"owner display remains alive";node[i]->m_generatedChampionName=L"owner generated remains alive";
 }
 if(cs->total>1){
  // All three backing pointers are live, including children revealed by the
  // count-growth probe. No active null child, cycle or invalid allocation.
  node[0]->m_children.setGrowBy(3);for(unsigned i=1;i<4;++i)node[0]->m_children.add(node[i]);
  at<unsigned>(node[0],0x50)=cs->node[0].children;at<unsigned>(node[0],0x54)=cs->node[0].capacity;
 }
 for(unsigned i=0;i<cs->total;++i)std::memcpy(nodeBefore[i],node[i],0xc8);
 std::memcpy(unitBefore,unit,0x778);
}
static void checkUntouched(){
 for(unsigned i=0;i<cs->total;++i){const unsigned char*p=reinterpret_cast<const unsigned char*>(node[i]);
  for(unsigned j=0;j<0xc8;++j){bool mutableByte=(j>=0x20&&j<0x28)||(j>=0x3c&&j<0x40)||j==0x60;
   if(cs->mode==ReloadType&&i==0&&j>=0x44&&j<0x48)mutableByte=true;
   if(cs->mode==ReloadRequired&&i==0&&j>=0x38&&j<0x3c)mutableByte=true;
   if((cs->mode==ShrinkChildren||cs->mode==GrowChildren||cs->mode==ReloadCapacity)&&i==0&&j>=0x50&&j<0x58)mutableByte=true;
   if(!mutableByte)NEED(p[j]==nodeBefore[i][j]);
  }
  NEED(node[i]->m_displayName==L"owner display remains alive");NEED(node[i]->m_generatedChampionName==L"owner generated remains alive");
 }
 const unsigned char*p=reinterpret_cast<const unsigned char*>(unit);
 for(unsigned j=0;j<0x778;++j){bool mutableByte=j>=0x4c0&&j<0x4c8;if(cs->mode==ReloadResourceAfterPosition&&j>=0x68&&j<0x70)mutableByte=true;if(!mutableByte)NEED(p[j]==unitBefore[j]);}
 NEED(quest->m_sUnknown58==sourceQuest);NEED(sourceQuest==sourceQuestAlias);NEED(sourceName==sourceNameAlias);
 NEED(at<Wide>(unit,0x4c0)==modelName);
 for(unsigned i=0;i<2;++i)for(unsigned k=0;k<2;++k){checkCache(i,k);cap->addText(cache(i,k));}
 for(unsigned i=0;i<2;++i){const unsigned char*p=reinterpret_cast<const unsigned char*>(ui[i]);
  for(unsigned j=0;j<UISize;++j)if(!(j>=0x1978&&j<0x1998))NEED(p[j]==uiBefore[i][j]);
  for(unsigned k=0;k<2;++k)for(unsigned j=0;j<0x100;++j)NEED(static_cast<unsigned char*>(window[i][k])[j]==0x33+i*2+k);
 }
 for(unsigned i=0;i<blockCount;++i)for(unsigned j=0;j<16;++j){NEED(blocks[i].p[int(j)-16]==0xa6);NEED(blocks[i].p[blocks[i].size+j]==0x6a);}
}
static void cleanup(){
 // Children are borrowed arena objects. Release the owning backing arrays
 // before original QuestUnitData destruction can delete those child objects.
 for(unsigned i=0;i<cs->total;++i)node[i]->m_children.clear();
 for(unsigned i=0;i<cs->total;++i)qdUnitDtor(node[i]);
 for(unsigned i=0;i<2;++i)qdGroupDtor(group[i]); // Each root owns its separate private repository.
 typedef TArrayList<TArrayList<CQuestUnitData*>*> Groups;
 quest->m_Unknown130.~Groups();quest->m_Unknown148.~Groups();
 quest->m_pUnknown30.~basic_string();quest->m_sUnknown58.~basic_string();
 for(unsigned i=0;i<2;++i){cache(i,0).~basic_string();cache(i,1).~basic_string();at<void*>(resource[i],0x18)=0;qdResourceDtor(resource[i]);}
 // Character/BaseUnit are genuinely original-constructed, retained until this
 // fork exits. Their nested original allocations are not transferred or freed
 // by a fake destructor; no whole-character lifecycle/heap-balance claim.
 for(unsigned i=0;i<blockCount;++i)for(unsigned j=0;j<16;++j){NEED(blocks[i].p[int(j)-16]==0xa6);NEED(blocks[i].p[blocks[i].size+j]==0x6a);}
}
static void side(void* context,autotest::Capture& out,bool candidate){
 cs=static_cast<Case*>(context);cap=&out;setup();wanted.clear();expectedFault=modelISAs=modelUI=modelFormats=0;modelResource=cs->resource?1:0;modelName=sourceName;
 for(unsigned i=0;i<cs->total;++i)model[i]=cs->node[i];
 bool results[2]={false,false};unsigned predictedCaught=0;
 try{for(unsigned r=0;r<cs->repeats;++r)results[r]=simulate(0,0);}catch(const Stop& s){predictedCaught=s.code;}
 NEED(predictedCaught==cs->fault);
 {
  detour::Set isa,position,tags,format,big,small,contracts,route;pISA=&isa;pPosition=&position;pTags=&tags;pUnsigned=&format;pBig=&big;pSmall=&small;
  TL_REDIRECT(isa,qdBoundaryISA,&callISA);TL_REDIRECT(position,qdBoundaryPosition,&callPosition);TL_REDIRECT(tags,qdBoundaryTags,&callTags);TL_REDIRECT(format,qdBoundaryUnsigned,&callUnsigned);
  TL_REDIRECT(big,qdBoundaryBig,&callBig);TL_REDIRECT(small,qdBoundarySmall,&callSmall);
  TL_REDIRECT(contracts,qdGroup,&lookup);TL_REDIRECT(contracts,qdSpawn,&spawn);TL_REDIRECT(contracts,qdResourceISA,&resourceISA);TL_REDIRECT(contracts,qdDungeon,&dungeon);
  contracts.redirect(qdVisible,qdVisible,&visible);contracts.redirect(qdProperty,qdProperty,&property);
  // Original child calls stay original in the oracle process. In the candidate
  // process BOTH linked self-calls and any original-address self-call reach
  // qdNew, so no candidate-parent/original-child hybrid can earn closure credit.
  if(candidate)route.redirect(qdTarget_original,qdTarget_original,&qdNew);
  if(isa.failed()||position.failed()||tags.failed()||format.failed()||big.failed()||small.failed()||contracts.failed()||route.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef bool(*Fn)(CQuestUnitData*,CBaseUnit*);Fn invoke=candidate?&qdNew:&qdOld;if(!autotest::beginInvocation(out,invoke))return;
  unsigned caught=0;try{for(unsigned r=0;r<cs->repeats;++r){bool result=invoke(node[0],cs->nullUnit?0:unit);n(result);NEED(result==results[r]);}}catch(const Stop& s){caught=s.code;}catch(...){caught=999;NEED(false);}
  n(caught);NEED(caught==predictedCaught);NEED(faultHits==(cs->fault?1u:0u));NEED(eventIndex==wanted.size());snapshot(model);
  if(!caught)out.callCompleted=1;
  NEED(!isa.failed()&&!position.failed()&&!tags.failed()&&!format.failed()&&!big.failed()&&!small.failed()&&!contracts.failed()&&!route.failed());
 }
 checkUntouched();
 // Surviving const sources and existing COW aliases stay independent after
 // genuine parameter/temporary destruction on both normal and unwind paths.
 quest->m_sUnknown58+=L" source after invocation";NEED(sourceQuest==sourceQuestAlias);
 at<Wide>(unit,0x4c0)+=L" name after invocation";NEED(sourceName==sourceNameAlias);
 for(unsigned i=0;i<2;++i)for(unsigned k=0;k<2;++k)checkCache(i,k);
 cleanup();n(firstError);n(0x51444654u);n(errors);
}
static void oldSide(void*p,autotest::Capture&o){side(p,o,false);}static void newSide(void*p,autotest::Capture&o){side(p,o,true);}
static bool oracle(const autotest::Outcome&o){unsigned t[2]={0,1};if(o.capture.length>=8)std::memcpy(t,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&t[0]==0x51444654u&&!t[1];}
static unsigned failureLine(const autotest::Outcome&o){unsigned n=0;if(o.capture.length>=12)std::memcpy(&n,o.capture.data+o.capture.length-12,4);return n;}
static bool pair(const tlhybrid_host*host,autotest::Coverage&coverage,Case&c,unsigned&completed,unsigned&unwinds,unsigned&originalFailures,unsigned&candidateFailures){
 autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);bool oa=oracle(a),ob=oracle(b);if(!oa)++originalFailures;if(!ob)++candidateFailures;bool ok;
 if(c.fault){++unwinds;ok=oa&&ob&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==0xd488f0&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);}
 else{++completed;ok=coverage.observe(host,a,b)==0&&oa&&ob;}
 if(!ok){host->log("    unitDefeated pair=%u/%u mode=%u fault=%u.%u counts=%u/%u nodes=%u status=%d/%d oracle=%u/%u line=%u/%u\n",completed,unwinds,c.mode,c.fault,c.faultOccurrence,c.node[0].count,c.node[0].required,c.total,a.childStatus,b.childStatus,oa,ob,failureLine(a),failureLine(b));coverage.report(host);}return ok;
}
static Case notifying(){Case c;c.resource=2;c.notifyISA=true;c.node[0].count=5;c.node[0].required=17;return c;}
static Case tree(unsigned shape){Case c;c.total=4;c.node[0].complete=true;c.node[0].cache=2;c.node[0].children=3;c.node[0].capacity=3;
 for(unsigned i=1;i<4;++i){c.node[i].cache=0;c.node[i].lookup=1;c.node[i].required=7;}
 if(shape==0)c.node[0].children=0;if(shape>=2&&shape<=4)c.node[shape-1].required=1;
 if(shape==5){c.node[1].lookup=2;c.node[2].track=false;c.node[3].lookup=2;}
 return c;
}
#undef NEED
}
TL_TEST(quest_unit_defeated_closure){using namespace qd;autotest::Coverage coverage("quest_unit_defeated_closure",0xd488f0);unsigned completed=0,unwinds=0,originalFailures=0,candidateFailures=0;std::vector<Case> normal,faults;
 // Recursive signed-comparison witnesses run FIRST. Only the child reaches
 // completion, so a signed-completion control must reject here rather than
 // borrowing an earlier root-count failure. One registered test also satisfies
 // the official control runner's exactly-one-failing-test contract.
 for(unsigned boundary=0;boundary<2;++boundary){Case c=tree(1);c.node[0].children=1;
  c.node[1].required=boundary?1u:0x80000000u;c.node[1].count=boundary?0x7fffffffu:0u;normal.push_back(c);
 }
 // Guarded null is used only with tracking disabled. Every active graph has
 // live units, children, quest association and safe potential spawn paths.
 for(unsigned nullUnit=0;nullUnit<2;++nullUnit){Case c;c.node[0].track=false;c.nullUnit=nullUnit;c.node[0].cache=0;normal.push_back(c);}
 for(unsigned layout=0;layout<6;++layout)for(unsigned isa=0;isa<2;++isa)for(unsigned sentinel=0;sentinel<2;++sentinel){Case c;c.resource=1;c.matchISA=isa;c.node[0].type=sentinel?22:30;
  c.node[0].cache=layout<2?layout+1:0;c.node[0].lookup=layout==2?1:layout==3?2:0;c.unitGroup=layout==4?0:1;c.repeats=2;normal.push_back(c);}
 // Same quest ID, wrong quest ID, matching base GUID low word and mismatch.
 for(unsigned a=0;a<4;++a)for(unsigned spawn=0;spawn<2;++spawn)for(unsigned create=0;create<2;++create)for(unsigned primary=0;primary<2;++primary){Case c;c.association=a;c.node[0].spawnType=spawn?22:30;c.node[0].create=create;c.node[0].cache=primary?1:2;c.node[0].required=1;normal.push_back(c);}
 const unsigned edges[]={0,1,2,0x7ffffffeu,0x7fffffffu,0x80000000u,0xfffffffeu,0xffffffffu};
 for(unsigned i=0;i<8;++i)for(unsigned j=0;j<8;++j){Case c;c.node[0].count=edges[i];c.node[0].required=edges[j];normal.push_back(c);}
 for(unsigned res=0;res<3;++res)for(unsigned isa=0;isa<2;++isa)for(unsigned character=0;character<2;++character){Case c;c.resource=res;c.notifyISA=isa;c.character=character;normal.push_back(c);}
 {Case c=notifying();c.node[0].type=30;c.matchISA=true;c.node[0].quest=false;normal.push_back(c);}
 for(unsigned text=0;text<4;++text)for(unsigned name=0;name<4;++name){Case c=notifying();c.payload=text;c.name=name;normal.push_back(c);}
 for(unsigned i=4;i<8;++i){Case c=notifying();c.node[0].count=edges[i];c.node[0].required=0xffffffffu;normal.push_back(c);}
 for(unsigned mode=ReloadType;mode<=ReloadName;++mode){Case c=notifying();c.mode=mode;
  if(mode==ReloadType){c.node[0].cache=2;c.node[0].type=30;c.otherISA=true;c.node[0].spawnType=22;c.node[0].create=true;}
  if(mode==ReloadCountDown){c.node[0].count=0;c.node[0].required=1;}
  if(mode==ReloadCountUp){c.node[0].count=0;c.node[0].required=9;}
  if(mode==ReloadResourceAfterPosition){c.node[0].count=0;c.node[0].required=1;}
  if(mode==ShrinkChildren||mode==GrowChildren||mode==ReloadCapacity){c=tree(1);c.mode=mode;if(mode==GrowChildren)c.node[0].children=1;}
  normal.push_back(c);
 }
 for(unsigned shape=0;shape<6;++shape){Case c=tree(shape);normal.push_back(c);}
 {Case c=tree(1);c.node[0].children=1;c.node[1].required=0x80000000u;c.node[1].count=0;normal.push_back(c);}
 {Case c=tree(1);c.node[0].children=1;c.node[1].required=1;c.node[1].count=0x7fffffffu;normal.push_back(c);}
 {Case c=tree(1);c.node[0].cache=1;normal.push_back(c);} // Completed matching parent must not descend.
 {Case c=tree(1);c.node[0].complete=false;normal.push_back(c);} // Incomplete nonmatch must not descend.
 // Controlled collaborator exceptions, never completed/accepted-pair credit.
 const unsigned faultCodes[]={Lookup,ISA,Tags,Big,Unsigned,Small,Position,Spawn,Dungeon};
 for(unsigned i=0;i<sizeof(faultCodes)/sizeof(faultCodes[0]);++i){Case c=notifying();c.node[0].cache=0;c.node[0].required=6;c.fault=faultCodes[i];faults.push_back(c);}
 {Case c=notifying();c.fault=Unsigned;c.faultOccurrence=2;faults.push_back(c);}
 for(unsigned i=0;i<normal.size();++i)if(!pair(host,coverage,normal[i],completed,unwinds,originalFailures,candidateFailures))return 1;
 for(unsigned i=0;i<faults.size();++i)if(!pair(host,coverage,faults[i],completed,unwinds,originalFailures,candidateFailures))return 1;
 coverage.report(host);host->log("    unitDefeated: %u completed finite pairs; %u supplementary unwinds; oracle failures original=%u candidate=%u. Only 0xd488f0 receives credit.\n",completed,unwinds,originalFailures,candidateFailures);
 return completed!=normal.size()||unwinds!=faults.size()||coverage.completed!=completed||coverage.different||coverage.missing||originalFailures||candidateFailures;
}
