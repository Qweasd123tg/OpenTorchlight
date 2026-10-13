// Prepared 0xd24fb0 closure. Authored but NOT compiled/run yet.
// Original dependencies are forwarded; only modes 1..6 mutate callbacks.
// Quest is a synthetic non-null guard (target never dereferences it).
// Translation uses a bounded synthetic map, original lookup, no file loading.
// Expected exception pairs have no completed-coverage credit.
#include <climits>
#include <cstring>
#include <cwchar>
#include <map>
#include <new>
#include <string>
#include <vector>
#include "AutoTest.h"
#include "Detour.h"
#include "QuestDialog.h"
#include "QuestDialogItem.h"
#include "TRepository.h"
TL_ORIGINAL(bool,qdpOld,(void*,const std::wstring&,CDataGroup*),"_ZN12CQuestDialog14parseDialogTagERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup")
extern "C" bool qdpNew(void*,const std::wstring&,CDataGroup*) __asm__("_ZN12CQuestDialog14parseDialogTagERKSbIwSt11char_traitsIwESaIwEEP10CDataGroup");
TL_ORIGINAL(void,qdpDialogCtor,(void*,void*),"_ZN12CQuestDialogC1EP6CQuest")
TL_ORIGINAL(void,qdpDialogDtor,(void*),"_ZN12CQuestDialogD1Ev")
TL_ORIGINAL(void,qdpGroupCtor,(void*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,qdpGroupDtor,(void*),"_ZN10CDataGroupD1Ev")
TL_ORIGINAL(CDataGroup*,qdpAddGroup,(void*,const std::wstring&),"_ZN10CDataGroup12AddDataGroupERKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(CDataValue*,qdpAddText,(void*,const std::wstring&,const std::wstring&,bool),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES5_b")
TL_ORIGINAL(void*,qdpAddInt,(void*,const std::wstring&,int),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEi")
TL_ORIGINAL(void*,qdpAddBool,(void*,const std::wstring&,bool),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEb")
TL_ORIGINAL(void*,qdpAddFloat,(void*,const std::wstring&,float),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEf")
TL_ORIGINAL(void,qdpUnitsCtor,(void*),"_ZN17CUnitResourceListC1Ev")
TL_ORIGINAL(void,qdpUnitsDtor,(void*),"_ZN17CUnitResourceListD1Ev")
TL_ORIGINAL(void,qdpItemDelete,(void*),"_ZN16CQuestDialogItemD0Ev")
#define QDP_DEP(R,N,A,S) TL_ORIGINAL(R,qdpOriginal##N,A,S) TL_FUNCTION(qdpBoundary##N,S)
QDP_DEP(bool,Bool,(void*,const std::wstring&,bool),"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEb")
QDP_DEP(float,Float,(void*,const std::wstring&,float),"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEf")
QDP_DEP(const std::wstring&,Text,(void*,const std::wstring&,const std::wstring&),"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
QDP_DEP(std::wstring,Upper,(const std::wstring&),"_ZN7STRINGS11StringUpperERKSbIwSt11char_traitsIwESaIwEE")
QDP_DEP(const std::wstring&,GroupName,(void*),"_ZN10CDataGroup12GetGroupNameEv")
QDP_DEP(unsigned,Groups,(void*,const std::wstring&,std::vector<CDataGroup*>*),"_ZN10CDataGroup25GetDataGroupsMatchingNameERKSbIwSt11char_traitsIwESaIwEEPSt6vectorIPS_SaIS7_EE")
QDP_DEP(void,Ctor,(void*,void*),"_ZN16CQuestDialogItemC1EP12CQuestDialog")
QDP_DEP(void,Parse,(void*,CDataGroup*,bool),"_ZN16CQuestDialogItem20parseDialogItemGroupEP10CDataGroupb")
QDP_DEP(const std::wstring&,Name,(void*),"_ZN10CDataValue16GetDataValueNameEv")
QDP_DEP(const std::wstring&,Value,(void*,bool),"_ZN10CDataValue14GetValueStringEb")
QDP_DEP(std::wstring,Replace,(std::wstring,const std::wstring&,const std::wstring&),"_ZN7STRINGS14replaceWStringESbIwSt11char_traitsIwESaIwEERKS3_S5_")
QDP_DEP(CDataGroup*,Lookup,(void*,const std::wstring&,const std::wstring&),"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEES5_")
#undef QDP_DEP
extern "C" char qdpAlloc[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char qdpFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
extern "C" char qdpArray[] __asm__("_Znam");
extern "C" char qdpDelete[] __asm__("_ZdlPv");
namespace qdp {
typedef std::wstring Wide;typedef std::map<Wide,std::map<Wide,CDataGroup*> > UnitMap;typedef std::map<Wide,Wide> TranslationMap;
struct List {void** data;unsigned count,capacity,grow,pad;};
typedef char ABI[sizeof(Wide)==8&&sizeof(wchar_t)==4&&sizeof(CQuestDialog)==0xa8&&sizeof(CQuestDialogItem)==0x28&&sizeof(CDataGroup)==0x60&&sizeof(List)==24?1:-1];
template<class T>T& at(void* p,unsigned n){return *reinterpret_cast<T*>(static_cast<char*>(p)+n);}
enum Code {Bool=1,Float,Text,Upper,GroupName,Groups,Ctor,Parse,Name,Value,Replace,Lookup,Array};
struct Case {
 unsigned type,texts,items,mask,seed,profile,names,payload,repeats,mode,fault,occurrence,itemKind,floatBits;bool empty,nullInput,nullQuest,soundEmpty;
 Case():type(1),texts(1),items(0),mask(0),seed(0),profile(0),names(0),payload(0),repeats(1),mode(0),fault(0),occurrence(1),itemKind(0),floatBits(0),empty(false),nullInput(false),nullQuest(false),soundEmpty(false){}
};
struct Stop {unsigned site;explicit Stop(unsigned n):site(n){}};
struct Allocation {void* p;bool live,constructed;};struct Block {unsigned char* p;unsigned size;};
const wchar_t* types[]={L"ERROR",L"INTRO",L"RETURN",L"COMPLETE",L"PASSIVE",L"DETAILS",L"intro",L"UNKNOWN"};
const wchar_t* categories[]={L"ITEMS",L"MONSTERS",L"PLAYERS",L"PROPS"};
const wchar_t* boolKeys[]={L"ICONABOVEHEAD",L"FLOATYTEXT",L"MAKE_PET_ON_ACCEPT",L"LOOK_AT_PLAYER",L"REMOVE_AS_PET_ON_COMPLETE",L"DESTROY_PET"};
const unsigned boolOffsets[]={0x75,0x74,0x78,0x7b,0x79,0x7a};const bool boolDefaults[]={true,false,false,true,true,true};
static const Case* cs;static autotest::Capture* cap;static CQuestDialog* dialog;static CDataGroup *root,*replacementRoot,*extra,*defs[4];
static void* units[2];static CDataValue *replacement,*originalFirst;static void** originalValueData;static CDataValue** replacementValueData;static unsigned originalValueCapacity;static std::vector<CDataGroup*>* giveVector;
static unsigned depth,step,errors,firstError,sites[16],allocCount,freed,faultHits;static bool inCall,tracking;
static Allocation allocations[96];static Block blocks[16];static unsigned blockCount;
static Wide payload,expectedText,npc,fallback;static void* vectorData[2];static unsigned vectorFrees[8],vectorFreeCount;static const Wide* borrowedSound;static int soundRefs;static unsigned savedRootCount;static void *savedUnits,*savedTranslate,*translation;
static detour::Set *pBool,*pFloat,*pText,*pUpper,*pGroupName,*pGroups,*pCtor,*pParse,*pName,*pValue,*pReplace,*pLookup,*pAlloc,*pFree,*pArray,*pDelete;
static void check(bool v,unsigned line){if(!v){if(!errors)firstError=line;++errors;}}
#define NEED(x) check((x),__LINE__)
static void n(unsigned x){cap->add(&x,4);}
static void* raw(unsigned size){NEED(blockCount<16);if(blockCount>=16)_exit(71);unsigned char* p=static_cast<unsigned char*>(autotest::allocate(size+32));std::memset(p,0xb6,16);std::memset(p+16,0xa5,size);std::memset(p+16+size,0x6b,16);blocks[blockCount].p=p;blocks[blockCount++].size=size;return p+16;}
static unsigned aid(void* p){for(unsigned i=allocCount;i;--i)if(allocations[i-1].p==p&&allocations[i-1].live)return i;return 0;}
static void event(unsigned code,const Wide& a=L"",const Wide& b=L"",unsigned value=0){
 if(!inCall||depth)return;++sites[code];n(0x7100+code);n(value);cap->addText(a);cap->addText(b);
 if(cs->fault==code&&sites[code]==cs->occurrence){++faultHits;throw Stop(code);}
}
#define FORWARD(R,N,EXPR) p##N->restore();++depth;try{R v=EXPR;--depth;TL_REDIRECT(*p##N,qdpBoundary##N,&call##N);return v;}catch(...){--depth;TL_REDIRECT(*p##N,qdpBoundary##N,&call##N);throw;}
static bool callBool(void* p,const Wide& key,bool fallback){event(Bool,key,L"",fallback);FORWARD(bool,Bool,qdpOriginalBool(p,key,fallback))}
static float callFloat(void* p,const Wide& key,float fallback){unsigned bits;std::memcpy(&bits,&fallback,4);event(Float,key,L"",bits);FORWARD(float,Float,qdpOriginalFloat(p,key,fallback))}
static int cowRefs(const Wide& s){return *reinterpret_cast<const int*>(reinterpret_cast<const char*>(s.c_str())-8);}
static const Wide& callText(void* p,const Wide& key,const Wide& fallback){
 event(Text,key,fallback);bool active=inCall&&!depth;pText->restore();++depth;const Wide* value;
 try{value=&qdpOriginalText(p,key,fallback);--depth;TL_REDIRECT(*pText,qdpBoundaryText,&callText);}catch(...){--depth;TL_REDIRECT(*pText,qdpBoundaryText,&callText);throw;}
 if(active&&key==L"SOUND"&&!value->empty()){borrowedSound=value;soundRefs=cowRefs(*value);}return *value;
}
static Wide callUpper(const Wide& input){event(Upper,input);FORWARD(Wide,Upper,qdpOriginalUpper(input))}
static const Wide& callGroupName(void* p){
 event(GroupName);if(inCall&&!depth&&cs->mode==1){static Wide miss(L"no-match"),hit(L"RETURN");return sites[GroupName]==1?miss:hit;}
 FORWARD(const Wide&,GroupName,qdpOriginalGroupName(p))
}
static unsigned callGroups(void* p,const Wide& key,std::vector<CDataGroup*>* out){
 event(Groups,key);bool active=inCall&&!depth;pGroups->restore();++depth;unsigned result;
 try{result=qdpOriginalGroups(p,key,out);--depth;TL_REDIRECT(*pGroups,qdpBoundaryGroups,&callGroups);}catch(...){--depth;TL_REDIRECT(*pGroups,qdpBoundaryGroups,&callGroups);throw;}
 if(active){unsigned family=key==L"GIVEITEM"?0:1;vectorData[family]=out->empty()?0:&(*out)[0];if(!family)giveVector=out;}return result;
}
static void callCtor(void* p,void* owner){
 event(Ctor,L"",L"",owner==dialog);pCtor->restore();++depth;
 try{qdpOriginalCtor(p,owner);--depth;TL_REDIRECT(*pCtor,qdpBoundaryCtor,&callCtor);}catch(...){--depth;TL_REDIRECT(*pCtor,qdpBoundaryCtor,&callCtor);throw;}
 unsigned i=aid(p);if(i)allocations[i-1].constructed=true;
}
static void callParse(void* p,CDataGroup* group,bool give){
 event(Parse,L"",L"",give);bool active=inCall&&!depth;pParse->restore();++depth;
 try{qdpOriginalParse(p,group,give);--depth;TL_REDIRECT(*pParse,qdpBoundaryParse,&callParse);}catch(...){--depth;TL_REDIRECT(*pParse,qdpBoundaryParse,&callParse);throw;}
 if(active&&sites[Parse]==1){
  if(cs->mode==2){NEED(giveVector!=0);if(giveVector){giveVector->push_back(extra);vectorData[0]=&(*giveVector)[0];}}
  if(cs->mode==3){List& list=at<List>(dialog,0x30);NEED(list.capacity>=1&&list.count==1);list.count=0;}
 }
}
static const Wide& callName(void* p){
 event(Name);if(inCall&&!depth&&cs->mode==4&&sites[Name]==1){List& values=at<List>(root,0x20);NEED(values.count==2);originalValueData=values.data;originalValueCapacity=values.capacity;replacementValueData=new CDataValue*[2];replacementValueData[0]=replacement;replacementValueData[1]=root->m_DataValues[1];values.data=reinterpret_cast<void**>(replacementValueData);values.capacity=1;}
 FORWARD(const Wide&,Name,qdpOriginalName(p))
}
static const Wide& callValue(void* p,bool translate){
 event(Value,L"",L"",translate);if(inCall&&!depth&&cs->mode==5&&sites[Value]==1)at<List>(root,0x20).count=1;
 FORWARD(const Wide&,Value,qdpOriginalValue(p,translate))
}
static Wide callReplace(Wide text,const Wide& from,const Wide& to){event(Replace,from,to);FORWARD(Wide,Replace,qdpOriginalReplace(text,from,to))}
static CDataGroup* callLookup(void* p,const Wide& category,const Wide& name){
 event(Lookup,category,name,p==units[0]?1:p==units[1]?2:99);bool active=inCall&&!depth;pLookup->restore();++depth;CDataGroup* v;
 try{v=qdpOriginalLookup(p,category,name);--depth;TL_REDIRECT(*pLookup,qdpBoundaryLookup,&callLookup);}catch(...){--depth;TL_REDIRECT(*pLookup,qdpBoundaryLookup,&callLookup);throw;}
 if(active&&cs->mode==6&&sites[Lookup]==1){NEED(v==0);*reinterpret_cast<void**>(0x152f128)=units[1];}return v;
}
#undef FORWARD
static void* callAlloc(size_t size,const char* file,int line,const char* function){
 pAlloc->restore();void* p;try{p=reinterpret_cast<void*(*)(size_t,const char*,int,const char*)>(qdpAlloc)(size,file,line,function);pAlloc->redirect(qdpAlloc,qdpAlloc,&callAlloc);}catch(...){pAlloc->redirect(qdpAlloc,qdpAlloc,&callAlloc);throw;}
 if(inCall&&!depth){NEED(size==0x28&&allocCount<96);if(allocCount>=96)_exit(72);Allocation& a=allocations[allocCount++];a.p=p;a.live=true;a.constructed=false;n(0xa110);n(allocCount);n(size);}return p;
}
static void callFree(void* p){unsigned i=tracking?aid(p):0;if(i){allocations[i-1].live=false;++freed;n(0xa111);n(i);}pFree->restore();reinterpret_cast<void(*)(void*)>(qdpFree)(p);pFree->redirect(qdpFree,qdpFree,&callFree);}
static void* callArray(size_t size){event(Array,L"",L"",size);pArray->restore();void* p;try{p=reinterpret_cast<void*(*)(size_t)>(qdpArray)(size);pArray->redirect(qdpArray,qdpArray,&callArray);}catch(...){pArray->redirect(qdpArray,qdpArray,&callArray);throw;}return p;}
static void callDelete(void* p){
 if(inCall&&!depth)for(unsigned i=0;i<2;++i)if(p&&p==vectorData[i]){NEED(vectorFreeCount<8);if(vectorFreeCount<8)vectorFrees[vectorFreeCount++]=i+1;n(0xa112);n(i+1);if(borrowedSound&&soundRefs>=0)NEED(cowRefs(*borrowedSound)==soundRefs+1);vectorData[i]=0;}
 pDelete->restore();reinterpret_cast<void(*)(void*)>(qdpDelete)(p);pDelete->redirect(qdpDelete,qdpDelete,&callDelete);
}
static CDataGroup* group(const wchar_t* name){CDataGroup* p=static_cast<CDataGroup*>(raw(0x60));qdpGroupCtor(p,Wide(name),0,2,2,reinterpret_cast<TRepository<Wide>*>(0x14dd9e0));return p;}
static void put(void* p,const wchar_t* key,const Wide& text,bool translate=false){qdpAddText(p,Wide(key),text,translate);}
static void initialize(){
 const unsigned cells[]={0x14fb488,0x151c128,0x151c188,0x1490de8,0x14dd9c8,0x14dd9d8,0x14dda88};
 for(unsigned i=0;i<sizeof(cells)/sizeof(cells[0]);++i)::new(reinterpret_cast<void*>(cells[i]))Wide();
 ::new(reinterpret_cast<void*>(0x14dd9c0))std::string();::new(reinterpret_cast<void*>(0x14dd9e0))TRepository<Wide>(Wide());
 for(unsigned i=0;i<6;++i)::new(reinterpret_cast<void*>(0x14fb4c0+i*8))Wide(types[i]);
 ::new(reinterpret_cast<void*>(0x14fb4f0))Wide(L"GIVEITEM");::new(reinterpret_cast<void*>(0x14fb4f8))Wide(L"TAKEITEM");
 for(unsigned i=0;i<4;++i)::new(reinterpret_cast<void*>(0x14fb520+i*8))Wide(categories[i]);
}
static Wide makePayload(unsigned kind){
 switch(kind){case 1:return L"";case 2:return Wide(513,L'x')+L"\\n";case 3:{const wchar_t x[]={L'A',0,L'B',L'\\',L'n'};return Wide(x,5);}case 4:return L"Ω猫\\n\\n";case 5:return L"SOURCE";default:return L"a\\nb\\nc";}
}
static Wide replaceLF(Wide text){size_t p=0;while((p=text.find(L"\\n",p))!=Wide::npos){text.replace(p,2,1,L'\n');++p;}return text;}
static Wide inputText(unsigned i){Wide value=payload;if(cs->payload==0)value+=static_cast<wchar_t>(L'0'+i);return value;}
static float inputFloat(unsigned i){const float values[]={1.25f,-2.5f,17.0f};if(!cs->floatBits)return values[i];const unsigned bits[]={0x80000000u,0x7f7fffffu,0x7fc01234u};float f;std::memcpy(&f,&bits[i],4);return f;}
static bool suppliedFlag(unsigned i){if(cs->profile==0)return boolDefaults[i];if(cs->profile==1)return !boolDefaults[i];return i==cs->profile-2?!boolDefaults[i]:boolDefaults[i];}
static void setup(){
 errors=firstError=depth=step=allocCount=freed=faultHits=blockCount=0;inCall=tracking=false;giveVector=0;vectorData[0]=vectorData[1]=0;vectorFreeCount=0;borrowedSound=0;soundRefs=0;originalFirst=0;originalValueData=0;replacementValueData=0;originalValueCapacity=0;std::memset(sites,0,sizeof(sites));autotest::g_arenaUsed=0;
 savedUnits=*reinterpret_cast<void**>(0x152f128);savedTranslate=*reinterpret_cast<void**>(0x1521d00);initialize();*reinterpret_cast<void**>(0x152f128)=0;
 for(unsigned i=0;i<2;++i){units[i]=raw(0x120);qdpUnitsCtor(units[i]);}*reinterpret_cast<void**>(0x152f128)=units[0];
 translation=raw(0x50);::new(static_cast<char*>(translation)+0x10)TranslationMap;at<TranslationMap>(translation,0x10)[L"SOURCE"]=L"TRANSLATED\\nVALUE";at<unsigned char>(translation,0x48)=1;*reinterpret_cast<void**>(0x1521d00)=translation;
 for(unsigned i=0;i<4;++i)defs[i]=group(L"UNIT");root=group(types[cs->type]);replacementRoot=group(L"REPLACEMENT");extra=group(L"EXTRA");
 replacement=qdpAddText(replacementRoot,Wide(L"DIALOG"),Wide(L"REPLACED\\nTEXT"),false);put(extra,L"NAME",L"GOLD");qdpAddInt(extra,Wide(L"COUNT"),7);
 payload=makePayload(cs->payload);expectedText=replaceLF(cs->payload==5?Wide(L"TRANSLATED\\nVALUE"):Wide(payload.c_str()));npc=cs->names==0?L"MiXeD":cs->names==3?L"missing":L"";fallback=cs->names==2?L"":L"FaLlBaCk";
 if(!cs->empty){
  for(unsigned i=0;i<cs->texts;++i)put(root,L"DIALOG",inputText(i),cs->payload==5);
  if(cs->mode!=4&&cs->mode!=5){put(root,L"NOTDIALOG",L"ignored");qdpAddInt(root,Wide(L"DIALOG"),27);put(root,L"UNITNAME",npc);}
  if(cs->profile){for(unsigned i=0;i<6;++i)qdpAddBool(root,Wide(boolKeys[i]),suppliedFlag(i));put(root,L"SOUND",cs->soundEmpty?L"":L"MiXeD_Sound");put(root,L"THEMEOVERRIDE",L"ThEmE");qdpAddFloat(root,Wide(L"CAMERAMODX"),inputFloat(0));qdpAddFloat(root,Wide(L"CAMERAMODY"),inputFloat(1));qdpAddFloat(root,Wide(L"CAMERAMODZ"),inputFloat(2));}
 }
 for(unsigned i=0;i<cs->items;++i)for(unsigned family=0;family<2;++family){CDataGroup* g=qdpAddGroup(root,Wide(family?L"TAKEITEM":L"GIVEITEM"));qdpAddInt(g,Wide(L"COUNT"),i%3==0?0:i%3==1?-3:9);put(g,L"NAME",cs->itemKind==0?L"GOLD":cs->itemKind==1?L"MissingItem":L"UnitTarget");}
 Wide mapName=npc.empty()?fallback:npc;for(unsigned j=0;j<mapName.size();++j)if(mapName[j]>=L'a'&&mapName[j]<=L'z')mapName[j]-=L'a'-L'A';
 for(unsigned i=0;i<4;++i)if(cs->mask&(1u<<i))at<UnitMap>(units[0],0x18)[categories[i]][mapName]=defs[i];
 if(cs->itemKind==2)at<UnitMap>(units[0],0x18)[L"PROPS"][L"UNITTARGET"]=defs[2];
 if(cs->mode==6){at<UnitMap>(units[0],0x18).clear();at<UnitMap>(units[1],0x18)[L"ITEMS"][mapName]=defs[0];}
 dialog=static_cast<CQuestDialog*>(raw(0xa8));qdpDialogCtor(dialog,cs->nullQuest?0:reinterpret_cast<void*>(0x13579));
 dialog->m_sNPCName=L"old_name";dialog->m_sSoundName=L"old_sound";dialog->m_sThemeOverride=L"old_theme";dialog->m_pNPCDataGroup=defs[3];dialog->m_bDialogInitialized=true;dialog->m_bItemsGiven=true;
 if(cs->seed){dialog->m_dialogText.add(Wide(L"seed"));dialog->m_dialogItemsToGive.add(new CQuestDialogItem(dialog));dialog->m_dialogItemsToRemove.add(new CQuestDialogItem(dialog));}
 savedRootCount=root->m_DataValues.size();
}
static unsigned npcID(){for(unsigned i=0;i<4;++i)if(dialog->m_pNPCDataGroup==defs[i])return i+1;return dialog->m_pNPCDataGroup?99:0;}
static void snapshot(){
 for(unsigned i=0;i<8;++i)n(at<unsigned char>(dialog,0x74+i));n(dialog->m_iDialogType);
 cap->add(reinterpret_cast<char*>(dialog)+0x88,12);cap->addText(dialog->m_sNPCName);cap->addText(dialog->m_sThemeOverride);cap->addText(dialog->m_sSoundName);n(npcID());
 n(dialog->m_dialogText.size());for(unsigned i=0;i<dialog->m_dialogText.size();++i)cap->addText(dialog->m_dialogText[i]);
 for(unsigned family=0;family<2;++family){TArrayList<CQuestDialogItem*>& list=family?dialog->m_dialogItemsToRemove:dialog->m_dialogItemsToGive;n(list.size());for(unsigned i=0;i<list.size();++i){CQuestDialogItem* item=list[i];n(item->m_bGive);n(item->m_bGold);n(item->m_iCount);n(item->m_pQuestDialog==dialog);unsigned dataID=0;for(unsigned k=0;k<4;++k)if(item->m_pDataGroup==defs[k])dataID=k+1;n(item->m_pDataGroup&&!dataID?99:dataID);}}
}
static void assertCompleted(bool result,const unsigned char* before){
 if(cs->nullInput||cs->nullQuest){NEED(!result);NEED(!std::memcmp(before,dialog,0xa8));return;}
 unsigned type=cs->mode==1?2:cs->type>=1&&cs->type<=5?cs->type:0;
 NEED(dialog->m_iDialogType==static_cast<int>(type));
 for(unsigned i=0;i<6;++i)NEED(at<unsigned char>(dialog,boolOffsets[i])==(!cs->empty?suppliedFlag(i):boolDefaults[i]));
 NEED(dialog->m_bDialogInitialized&&dialog->m_bItemsGiven);
 NEED(dialog->m_sSoundName==(!cs->empty&&cs->profile&&!cs->soundEmpty?L"MIXED_SOUND":L"old_sound"));NEED(dialog->m_sThemeOverride==(!cs->empty&&cs->profile?L"THEME":L""));
 for(unsigned i=0;i<3;++i){float expected=!cs->empty&&cs->profile?inputFloat(i):0.0f;NEED(std::memcmp(reinterpret_cast<char*>(dialog)+0x88+i*4,&expected,4)==0);}
 unsigned textCount=!cs->empty&&type?(cs->mode==5?1:cs->texts):0;
 unsigned totalText=cs->seed+(step+1)*textCount;NEED(dialog->m_dialogText.size()==totalText);
 if(cs->seed&&dialog->m_dialogText.size())NEED(dialog->m_dialogText[0]==L"seed");
 for(unsigned i=cs->seed;i<dialog->m_dialogText.size();++i){Wide expected=cs->mode==4?L"REPLACED\nTEXT":cs->payload==0?replaceLF(inputText(textCount?(i-cs->seed)%textCount:i)):expectedText;NEED(dialog->m_dialogText[i]==expected);}
 bool expected=type&&!cs->empty&&totalText;NEED(result==expected);
 for(unsigned family=0;family<2;++family){
  TArrayList<CQuestDialogItem*>& list=family?dialog->m_dialogItemsToRemove:dialog->m_dialogItemsToGive;
  unsigned seeded=cs->mode==3&&!family?0:cs->seed;unsigned count=seeded+(step+1)*cs->items+(!family&&cs->mode==2?1:0);NEED(list.size()==count);
  for(unsigned i=0;i<list.size();++i){CQuestDialogItem* item=list[i];NEED(item->m_pQuestDialog==dialog);NEED(item->m_pDataGroup==(i>=seeded&&cs->itemKind==2?defs[2]:0));
   if(i<seeded){NEED(item->m_iCount==1&&!item->m_bGold);}
   else {unsigned span=cs->items+(cs->mode==2&&!family?1:0);NEED(span!=0);unsigned index=span?(i-seeded)%span:0;NEED(item->m_bGive==!family&&item->m_bGold==(cs->itemKind==0));int wanted=cs->mode==2&&!family&&index==cs->items?7:index%3==2?9:1;NEED(item->m_iCount==wanted);}
  }
 }
 if(expected){
  Wide wanted=(cs->mode==4||cs->mode==5||npc.empty())?fallback:npc;NEED(dialog->m_sNPCName==wanted);
  unsigned id=wanted.empty()?4:cs->mode==6?1:cs->mask&2?2:cs->mask&1?1:cs->mask&8?4:0;NEED(npcID()==id);
 }else{NEED(dialog->m_sNPCName==L"old_name"&&npcID()==4);}
}
static void side(void* context,autotest::Capture& out,bool candidate){
 cs=static_cast<Case*>(context);cap=&out;setup();tracking=true;
 typedef bool(*Fn)(void*,const Wide&,CDataGroup*);Fn invoke=candidate?&qdpNew:&qdpOld;void* displacedSeed=cs->mode==3?dialog->m_dialogItemsToGive[0]:0;
 {
 detour::Set b,f,t,u,g,gs,c,p,nm,v,r,l,a,fr,ar,dl;pBool=&b;pFloat=&f;pText=&t;pUpper=&u;pGroupName=&g;pGroups=&gs;pCtor=&c;pParse=&p;pName=&nm;pValue=&v;pReplace=&r;pLookup=&l;pAlloc=&a;pFree=&fr;pArray=&ar;pDelete=&dl;
 TL_REDIRECT(b,qdpBoundaryBool,&callBool);TL_REDIRECT(f,qdpBoundaryFloat,&callFloat);TL_REDIRECT(t,qdpBoundaryText,&callText);TL_REDIRECT(u,qdpBoundaryUpper,&callUpper);TL_REDIRECT(g,qdpBoundaryGroupName,&callGroupName);TL_REDIRECT(gs,qdpBoundaryGroups,&callGroups);TL_REDIRECT(c,qdpBoundaryCtor,&callCtor);TL_REDIRECT(p,qdpBoundaryParse,&callParse);TL_REDIRECT(nm,qdpBoundaryName,&callName);TL_REDIRECT(v,qdpBoundaryValue,&callValue);TL_REDIRECT(r,qdpBoundaryReplace,&callReplace);TL_REDIRECT(l,qdpBoundaryLookup,&callLookup);
 a.redirect(qdpAlloc,qdpAlloc,&callAlloc);fr.redirect(qdpFree,qdpFree,&callFree);ar.redirect(qdpArray,qdpArray,&callArray);dl.redirect(qdpDelete,qdpDelete,&callDelete);
 if(b.failed()||f.failed()||t.failed()||u.failed()||g.failed()||gs.failed()||c.failed()||p.failed()||nm.failed()||v.failed()||r.failed()||l.failed()||a.failed()||fr.failed()||ar.failed()||dl.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 for(step=0;step<cs->repeats;++step){
  unsigned char before[0xa8];std::memcpy(before,dialog,sizeof(before));unsigned caught=0;bool result=false;
  n(0xb100+step);if(step==0&&!autotest::beginInvocation(out,invoke))return;
  inCall=true;try{result=invoke(dialog,fallback,cs->nullInput?0:root);}catch(const Stop& stop){caught=stop.site;}catch(...){caught=999;NEED(false);}inCall=false;
  NEED(caught==cs->fault);n(caught);n(result);if(borrowedSound&&soundRefs>=0)NEED(cowRefs(*borrowedSound)==soundRefs);NEED(vectorData[0]==0&&vectorData[1]==0);if(vectorFreeCount>=2)NEED(vectorFrees[vectorFreeCount-2]==2&&vectorFrees[vectorFreeCount-1]==1);if(!caught)assertCompleted(result,before);snapshot();
  if(caught)break;
 }
 if(!cs->fault)out.callCompleted=1;else NEED(faultHits==1);
 if(!cs->fault&&!cs->nullInput&&!cs->nullQuest){
  unsigned type=cs->mode==1?2:cs->type>=1&&cs->type<=5?cs->type:0;
  NEED(sites[Bool]==6*cs->repeats&&sites[Float]==3*cs->repeats&&sites[Groups]==2*cs->repeats);
  NEED(sites[GroupName]==(type?type:5)*cs->repeats);
  NEED(sites[Parse]==2*cs->items*cs->repeats+(cs->mode==2?1:0));
  if(cs->mode==4)NEED(sites[Value]==cs->texts);if(cs->mode==5)NEED(sites[Value]==1);if(cs->mode==6)NEED(sites[Lookup]==2);
 }
 unsigned leaked=0;for(unsigned i=0;i<allocCount;++i)if(allocations[i].live){bool owned=false;for(unsigned family=0;family<2;++family){TArrayList<CQuestDialogItem*>& list=family?dialog->m_dialogItemsToRemove:dialog->m_dialogItemsToGive;for(unsigned j=0;j<list.size();++j)if(list[j]==allocations[i].p)owned=true;}if(!owned)++leaked;}
 n(leaked);bool itemLeak=cs->fault==Parse||(cs->fault==Array&&cs->occurrence<=2&&cs->items);NEED(leaked==(itemLeak?1u:0u));
 qdpDialogDtor(dialog);unsigned remaining=0;for(unsigned i=0;i<allocCount;++i)if(allocations[i].live)++remaining;n(allocCount);n(freed);n(remaining);NEED(remaining==leaked);
 tracking=false;for(unsigned i=0;i<allocCount;++i)if(allocations[i].live){NEED(allocations[i].constructed);qdpItemDelete(allocations[i].p);allocations[i].live=false;}
 }
 if(displacedSeed)qdpItemDelete(displacedSeed);
 if(originalValueData){at<List>(root,0x20).data=originalValueData;at<List>(root,0x20).capacity=originalValueCapacity;delete[] replacementValueData;}at<List>(root,0x20).count=savedRootCount;
 for(unsigned i=0;i<2;++i){at<UnitMap>(units[i],0x18).clear();qdpUnitsDtor(units[i]);}*reinterpret_cast<void**>(0x152f128)=savedUnits;
 at<TranslationMap>(translation,0x10).~TranslationMap();*reinterpret_cast<void**>(0x1521d00)=savedTranslate;
 qdpGroupDtor(root);qdpGroupDtor(replacementRoot);qdpGroupDtor(extra);for(unsigned i=0;i<4;++i)qdpGroupDtor(defs[i]);
 for(unsigned i=0;i<blockCount;++i)for(unsigned j=0;j<16;++j){NEED(blocks[i].p[j]==0xb6);NEED(blocks[i].p[16+blocks[i].size+j]==0x6b);}
 n(firstError);n(0x51445043);n(errors);
}
static void oldSide(void* c,autotest::Capture& out){side(c,out,false);}static void newSide(void* c,autotest::Capture& out){side(c,out,true);}
static bool oracle(const autotest::Outcome& x){unsigned tail[2]={0,1};if(x.capture.length>=8)std::memcpy(tail,x.capture.data+x.capture.length-8,8);return x.reportValid&&!x.childStatus&&!x.capture.issue&&tail[0]==0x51445043&&!tail[1];}
static bool pair(const tlhybrid_host* host,autotest::Coverage& coverage,Case& c,unsigned& completed,unsigned& unwinds){
 autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);bool ok;
 if(c.fault){++unwinds;ok=oracle(a)&&oracle(b)&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==0xd24fb0&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);}
 else {++completed;ok=coverage.observe(host,a,b)==0&&oracle(a)&&oracle(b);}
 if(!ok){unsigned fa=0,fb=0;if(a.capture.length>=12)std::memcpy(&fa,a.capture.data+a.capture.length-12,4);if(b.capture.length>=12)std::memcpy(&fb,b.capture.data+b.capture.length-12,4);host->log("    dialog type=%u texts=%u items=%u mask=%u seed=%u profile=%u names=%u payload=%u repeat=%u mode=%u fault=%u/%u empty=%u null=%u/%u status=%d/%d first=%u/%u\n",c.type,c.texts,c.items,c.mask,c.seed,c.profile,c.names,c.payload,c.repeats,c.mode,c.fault,c.occurrence,c.empty,c.nullInput,c.nullQuest,a.childStatus,b.childStatus,fa,fb);coverage.report(host);}return ok;
}
#undef NEED
}
TL_TEST(quest_dialog_parse_closure){
 using namespace qdp;autotest::Coverage coverage("quest_dialog_parse_closure",0xd24fb0);unsigned completed=0,unwinds=0;
 // Exhaust type gate, empty/non-dialog/text input, preexisting text, item work.
 for(unsigned type=0;type<8;++type)for(unsigned shape=0;shape<3;++shape)for(unsigned seed=0;seed<2;++seed){Case c;c.type=type;c.empty=shape==0;c.texts=shape==2?2:0;c.items=2;c.seed=seed;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 // Independent NPC precedence, both fallback forms, original nullable misses.
 for(unsigned mask=0;mask<16;++mask)for(unsigned names=0;names<3;++names){Case c;c.mask=mask;c.names=names;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 for(unsigned profile=0;profile<8;++profile){Case c;c.profile=profile;c.items=3;c.seed=1;c.repeats=2;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 for(unsigned payload=0;payload<6;++payload){Case c;c.payload=payload;c.texts=3;c.seed=1;c.repeats=2;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 const unsigned counts[]={0,1,2,3,7};for(unsigned i=0;i<5;++i){Case c;c.items=counts[i];c.seed=1;c.repeats=2;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 for(unsigned guard=0;guard<2;++guard)for(unsigned seed=0;seed<2;++seed){Case c;c.nullInput=guard==0;c.nullQuest=guard==1;c.items=3;c.seed=seed;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 for(unsigned kind=1;kind<=2;++kind){Case c;c.itemKind=kind;c.items=3;c.seed=1;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 {Case c;c.profile=1;c.soundEmpty=true;c.seed=1;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 {Case c;c.profile=1;c.floatBits=1;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 // Six completed callback probes; original forwarders remain active.
 for(unsigned mode=1;mode<=6;++mode){Case c;c.mode=mode;c.items=mode==2||mode==3?1:0;c.seed=mode==3;c.texts=mode==4||mode==5?2:1;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 // Distinct boundary failures, plus pointer/string array growth, no coverage credit.
 for(unsigned code=Bool;code<=Array;++code){unsigned count=code==Bool?6:code==Float?3:code==Text?3:code==Upper?2:code==GroupName?5:code==Groups?2:code==Ctor||code==Parse?2:code==Lookup?3:code==Array?3:1;
  for(unsigned occurrence=1;occurrence<=count;++occurrence){Case c;c.type=code==GroupName?7:1;c.items=1;c.profile=1;c.fault=code;c.occurrence=occurrence;if(!pair(host,coverage,c,completed,unwinds))return 1;}}
 coverage.report(host);host->log("    dialog parser: %u completed pairs (6 controlled); %u expected unwinds without acceptance credit; synthetic Quest guard and bounded translation map\n",completed,unwinds);
 return completed!=129||unwinds!=34||coverage.completed!=completed||coverage.different||coverage.missing;
}
