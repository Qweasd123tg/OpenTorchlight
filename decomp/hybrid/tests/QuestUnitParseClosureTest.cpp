// Prepared 0xd46b70 closure draft. Not compiled or executed.
// Real original ctor/DataGroup/typed getters/StringUpper; bounded callback probes.
// Expected unwinds are supplementary and excluded from accepted coverage.
#include <climits>
#include <cstddef>
#include <cstring>
#include <new>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
#include "QuestUnitData.h"
#include "TRepository.h"
TL_ORIGINAL(bool,qupOld,(void*,CDataGroup*,CDataGroup*),"_ZN14CQuestUnitData14parseDataGroupEP10CDataGroupS1_")
extern "C" bool qupNew(void*,CDataGroup*,CDataGroup*) __asm__("_ZN14CQuestUnitData14parseDataGroupEP10CDataGroupS1_");
TL_ORIGINAL(void,qupCtor,(void*,void*),"_ZN14CQuestUnitDataC1EP6CQuest")
TL_ORIGINAL(void,qupDtor,(void*),"_ZN14CQuestUnitDataD1Ev")
TL_ORIGINAL(void,qupGroupCtor,(void*,const std::wstring&,CDataGroup*,unsigned,unsigned,TRepository<std::wstring>*),"_ZN10CDataGroupC1ERKSbIwSt11char_traitsIwESaIwEEPS_jjP11TRepositoryIS3_E")
TL_ORIGINAL(void,qupGroupDtor,(void*),"_ZN10CDataGroupD1Ev")
TL_ORIGINAL(void*,qupAddInt,(void*,const std::wstring&,int),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEi")
TL_ORIGINAL(void*,qupAddBool,(void*,const std::wstring&,bool),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEEb")
TL_ORIGINAL(void*,qupAddText,(void*,const std::wstring&,const std::wstring&,bool),"_ZN10CDataGroup12AddDataValueERKSbIwSt11char_traitsIwESaIwEES5_b")
#define QUP_DEP(R,N,A,S) TL_ORIGINAL(R,qupOriginal##N,A,S) TL_FUNCTION(qupBoundary##N,S)
QUP_DEP(bool,Bool,(void*,const std::wstring&,bool),"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEb")
QUP_DEP(int,Int,(void*,const std::wstring&,int),"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEEi")
QUP_DEP(const std::wstring&,Text,(void*,const std::wstring&,const std::wstring&),"_ZN10CDataGroup12GetDataValueERKSbIwSt11char_traitsIwESaIwEES5_")
QUP_DEP(std::wstring,Upper,(const std::wstring&),"_ZN7STRINGS11StringUpperERKSbIwSt11char_traitsIwESaIwEE")
#undef QUP_DEP
namespace qup {
typedef std::wstring Wide;
typedef char ABI[sizeof(Wide)==8&&sizeof(wchar_t)==4&&sizeof(CQuestUnitData)==0xc8&&sizeof(CDataGroup)==0x60?1:-1];
const wchar_t* keys[]={L"REMOVEFROMINVENTORY",L"RELATIVEFLOOR",L"SPECIFICFLOOR",L"SPAWNCLASS",L"@UPPER",L"ITEM",L"MONSTER",L"UNITTYPE",L"NEVERDESTROY",L"SPAWNFROMUNITTYPE",L"UNIQUE_MONSTER_NAME",L"REMOVE_ONLY_QUESTITEMS",L"MINCOUNT",L"MAXCOUNT",L"CREATE",L"MAKECHAMPION"};
const unsigned textOffsets[]={0x78,0x80,0x88,0x90,0x98,0x70};
const unsigned textEvents[]={4,6,7,8,10,11};
const unsigned boolOffsets[]={0x62,0xb8,0x64,0x63,0x61};
const unsigned boolEvents[]={1,9,12,15,16};
struct Case {unsigned shape,seed,mode,fault,repeats,questArg;int lo,hi;bool nullInput,nullQuest;Case():shape(0),seed(0),mode(0),fault(0),repeats(1),questArg(0),lo(2),hi(5),nullInput(false),nullQuest(false){}};
struct Stop {unsigned site;explicit Stop(unsigned n):site(n){}};
template<class T>T& at(void*p,unsigned n){return *reinterpret_cast<T*>(static_cast<char*>(p)+n);}
static const Case* cs;static autotest::Capture* cap;static CQuestUnitData* object;static CDataGroup *group,*quest;
static unsigned errors,firstError,events,faultHits,depth;static bool active;static unsigned char* storage;
static detour::Set *pBool,*pInt,*pText,*pUpper;static Wide sourceText;
static void check(bool ok,unsigned line){if(!ok){if(!errors)firstError=line;++errors;}}
#define NEED(x) check((x),__LINE__)
static void n(unsigned x){cap->add(&x,4);}
static void snapshot(){
 for(unsigned i=0;i<5;++i)n(at<unsigned char>(object,boolOffsets[i]));
 for(unsigned i=0;i<4;++i)n(at<unsigned>(object,0xa0+4*i));
 for(unsigned i=0;i<6;++i)cap->addText(at<Wide>(object,textOffsets[i]));
 n(object->m_pBaseUnitDataGroup==group?1:object->m_pBaseUnitDataGroup==0?0:99);
 n(object->m_pQuestDataGroup==quest?1:object->m_pQuestDataGroup==group?2:object->m_pQuestDataGroup==0?0:99);
}
static void event(const Wide& key,unsigned value){
 if(!active||depth)return;++events;n(0x5000+events);cap->addText(key);n(value);snapshot();
 NEED(events<=16);if(events<=16)NEED(key==keys[events-1]);
 if(cs->fault==events){++faultHits;throw Stop(events);}
}
#define FORWARD(R,N,CALL) p##N->restore();++depth;try{R value=CALL;--depth;TL_REDIRECT(*p##N,qupBoundary##N,&call##N);return value;}catch(...){--depth;TL_REDIRECT(*p##N,qupBoundary##N,&call##N);throw;}
static bool callBool(void*p,const Wide& key,bool fallback){
 event(key,fallback);if(active&&!depth&&cs->mode==1&&key==L"CREATE")object->m_makeChampion=!object->m_makeChampion;
 FORWARD(bool,Bool,qupOriginalBool(p,key,fallback))
}
static int callInt(void*p,const Wide& key,int fallback){
 event(key,static_cast<unsigned>(fallback));if(active&&!depth&&cs->mode==2&&key==L"MAXCOUNT")object->m_minCount=17;
 FORWARD(int,Int,qupOriginalInt(p,key,fallback))
}
static const Wide& callText(void*p,const Wide& key,const Wide& fallback){event(key,0);if(active&&!depth)NEED(fallback.empty());FORWARD(const Wide&,Text,qupOriginalText(p,key,fallback))}
static Wide callUpper(const Wide& input){event(L"@UPPER",0);if(active&&!depth)cap->addText(input);FORWARD(Wide,Upper,qupOriginalUpper(input))}
#undef FORWARD
static CDataGroup* makeGroup(const wchar_t* name){CDataGroup*p=static_cast<CDataGroup*>(autotest::allocate(0x60));qupGroupCtor(p,Wide(name),0,8,8,0);return p;}
static Wide textPayload(unsigned index){
 if(cs->shape==3)return Wide();
 Wide value=L"MiXeD_";value+=wchar_t(L'A'+index);
 if(cs->shape==4)value=Wide(257,wchar_t(L'a'+index));
 if(cs->shape==5){value=L"before";value+=wchar_t(0);value+=L"AFTER";}
 if(cs->shape==6)value=L"\\n\n{}!_123";
 return value;
}
static void setup(){
 errors=firstError=events=faultHits=depth=0;active=false;autotest::g_arenaUsed=0;
 // Minimal child-local original globals; no global constructor sweep.
 ::new(reinterpret_cast<void*>(0x14ff1a8))Wide();
 ::new(reinterpret_cast<void*>(0x14dd9e0))TRepository<Wide>(Wide());
 ::new(reinterpret_cast<void*>(0x14dda88))Wide();
 group=makeGroup(L"UNIT");quest=makeGroup(L"QUEST");
 storage=static_cast<unsigned char*>(autotest::allocate(0xc8+32));std::memset(storage,0x5a,16);std::memset(storage+16+0xc8,0xa6,16);
 object=reinterpret_cast<CQuestUnitData*>(storage+16);qupCtor(object,cs->nullQuest?0:quest);
 object->m_pBaseUnitDataGroup=group;object->m_pQuestDataGroup=group;
 for(unsigned i=0;i<5;++i)at<bool>(object,boolOffsets[i])=bool((cs->seed>>i)&1);
 for(unsigned i=0;i<4;++i)at<int>(object,0xa0+4*i)=-700-int(i);
 for(unsigned i=0;i<6;++i)at<Wide>(object,textOffsets[i])=L"seed_value";
 object->m_displayName=L"untouched_display";object->m_generatedChampionName=L"untouched_generated";
 object->m_baseUnitGuid=0x1234567811223344LL;object->m_requiredUnitCount=19;object->m_currentUnitCount=7;
 if(cs->shape){
  for(unsigned i=0;i<5;++i)qupAddBool(group,Wide(keys[boolEvents[i]-1]),bool((cs->shape+i)&1));
  qupAddInt(group,Wide(L"RELATIVEFLOOR"),-13);qupAddInt(group,Wide(L"SPECIFICFLOOR"),23);
  qupAddInt(group,Wide(L"MINCOUNT"),cs->lo);qupAddInt(group,Wide(L"MAXCOUNT"),cs->hi);
  for(unsigned i=0;i<6;++i)qupAddText(group,Wide(keys[textEvents[i]-1]),textPayload(i),false);
 }
}
static bool written(unsigned offset){
 if(offset>=0x20&&offset<0x30)return true;
 for(unsigned i=0;i<5;++i)if(offset==boolOffsets[i])return true;
 for(unsigned i=0;i<6;++i)if(offset>=textOffsets[i]&&offset<textOffsets[i]+8)return true;
 return offset>=0xa0&&offset<0xb0;
}
static void assertCompleted(bool result,const unsigned char* before){
 NEED(result==!cs->nullInput);
 if(cs->nullInput){NEED(!std::memcmp(before,object,0xc8));NEED(events==0);return;}
 NEED(events==16);NEED(object->m_pBaseUnitDataGroup==0);NEED(object->m_pQuestDataGroup==(cs->questArg==1?0:cs->questArg==2?group:quest));
 for(unsigned i=0;i<5;++i){bool expected=cs->shape?bool((cs->shape+i)&1):i==4?bool((cs->seed>>i)&1):true;if(cs->mode==1&&i==4&&!cs->shape)expected=!bool((cs->seed>>i)&1);NEED(at<bool>(object,boolOffsets[i])==expected);}
 NEED(object->m_relativeFloor==(cs->shape?-13:0));NEED(object->m_specificFloor==(cs->shape?23:-1));
 int lo=cs->shape?cs->lo:0;lo=lo<1?1:lo;int hi=cs->shape?cs->hi:lo;if(cs->mode==2)lo=17;hi=hi<lo?lo:hi;
 NEED(object->m_minCount==lo);NEED(object->m_maxCount==hi);
 for(unsigned i=0;i<6;++i){Wide expected=cs->shape?Wide(textPayload(i).c_str()):Wide();if(i==0)for(unsigned j=0;j<expected.size();++j)if(expected[j]>=L'a'&&expected[j]<=L'z')expected[j]-=L'a'-L'A';NEED(at<Wide>(object,textOffsets[i])==expected);}
 for(unsigned i=0;i<0xc8;++i)if(!written(i))NEED(reinterpret_cast<unsigned char*>(object)[i]==before[i]);
}
static void side(void* context,autotest::Capture& out,bool candidate){
 cs=static_cast<Case*>(context);cap=&out;setup();typedef bool(*Fn)(void*,CDataGroup*,CDataGroup*);Fn invoke=candidate?&qupNew:&qupOld;
 {detour::Set b,i,t,u;pBool=&b;pInt=&i;pText=&t;pUpper=&u;TL_REDIRECT(b,qupBoundaryBool,&callBool);TL_REDIRECT(i,qupBoundaryInt,&callInt);TL_REDIRECT(t,qupBoundaryText,&callText);TL_REDIRECT(u,qupBoundaryUpper,&callUpper);
 if(b.failed()||i.failed()||t.failed()||u.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(!autotest::beginInvocation(out,invoke))return;
 for(unsigned repeat=0;repeat<cs->repeats;++repeat){unsigned char before[0xc8];std::memcpy(before,object,sizeof(before));events=0;unsigned caught=0;bool result=false;active=true;
  try{result=invoke(object,cs->nullInput?0:group,cs->questArg==1?0:cs->questArg==2?group:quest);}catch(const Stop&s){caught=s.site;}catch(...){caught=999;NEED(false);}active=false;
  n(caught);n(result);NEED(caught==cs->fault);if(!caught)assertCompleted(result,before);
  for(unsigned off=0;off<0xc8;++off)if(!written(off))NEED(reinterpret_cast<unsigned char*>(object)[off]==before[off]);
  snapshot();if(caught)break;
 }
 if(!cs->fault)out.callCompleted=1;else NEED(faultHits==1);
 NEED(!b.failed()&&!i.failed()&&!t.failed()&&!u.failed());
 }
 // Original source values remain valid and unchanged even after partial unwind.
 for(unsigned k=0;k<6;++k){Wide fallback;const Wide& value=qupOriginalText(group,Wide(keys[textEvents[k]-1]),fallback);Wide expected=cs->shape?Wide(textPayload(k).c_str()):Wide();NEED(value==expected);cap->addText(value);}
 qupDtor(object);qupGroupDtor(group);qupGroupDtor(quest);
 for(unsigned i=0;i<16;++i){NEED(storage[i]==0x5a);NEED(storage[16+0xc8+i]==0xa6);}
 n(firstError);n(0x51555043);n(errors);
}
static void oldSide(void*c,autotest::Capture&o){side(c,o,false);}static void newSide(void*c,autotest::Capture&o){side(c,o,true);}
static bool oracle(const autotest::Outcome&o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0x51555043&&!tail[1];}
static bool pair(const tlhybrid_host*host,autotest::Coverage&cov,Case&c,unsigned&completed,unsigned&unwinds){autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);bool ok;
 if(c.fault){++unwinds;ok=oracle(a)&&oracle(b)&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==0xd46b70&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);}
 else{++completed;ok=cov.observe(host,a,b)==0&&oracle(a)&&oracle(b);}
 if(!ok){host->log("    unit parser shape=%u seed=%u mode=%u fault=%u bounds=%d/%d status=%d/%d\n",c.shape,c.seed,c.mode,c.fault,c.lo,c.hi,a.childStatus,b.childStatus);cov.report(host);}return ok;}
#undef NEED
}
TL_TEST(quest_unit_parse_closure){using namespace qup;autotest::Coverage coverage("quest_unit_parse_closure",0xd46b70);unsigned completed=0,unwinds=0;
 for(unsigned seed=0;seed<32;++seed){Case c;c.seed=seed;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 for(unsigned shape=1;shape<=6;++shape){Case c;c.shape=shape;c.seed=21;c.repeats=2;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 const int bounds[]={INT_MIN,-1,0,1,2,INT_MAX};for(unsigned i=0;i<6;++i)for(unsigned j=0;j<6;++j){Case c;c.shape=1;c.lo=bounds[i];c.hi=bounds[j];if(!pair(host,coverage,c,completed,unwinds))return 1;}
 for(unsigned input=0;input<2;++input)for(unsigned quest=0;quest<2;++quest){Case c;c.nullInput=input;c.nullQuest=quest;c.seed=21;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 for(unsigned arg=1;arg<=2;++arg){Case c;c.questArg=arg;c.shape=1;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 for(unsigned mode=1;mode<=2;++mode){Case c;c.mode=mode;c.seed=16;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 for(unsigned shape=0;shape<2;++shape)for(unsigned fault=1;fault<=16;++fault){Case c;c.shape=shape;c.seed=21;c.fault=fault;if(!pair(host,coverage,c,completed,unwinds))return 1;}
 coverage.report(host);host->log("    unit parser: %u completed pairs (2 controlled); %u expected unwinds excluded from acceptance\n",completed,unwinds);return completed!=82||unwinds!=32||coverage.completed!=completed||coverage.different||coverage.missing;
}
