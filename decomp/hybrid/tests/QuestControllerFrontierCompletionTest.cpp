// Original ELF 91b41ae9...; fresh normal packets tu-dv6yuftr, de6b20/de6d40.
// Independent ordered branch oracles. C++98. Expected throws get no completed
// coverage. This fixture is authored only; the integration lead owns execution.
#include <map>
#include <string>
#include <cstring>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#define QCF_PAIR(R,N,A,S) TL_ORIGINAL(R,N##Old,A,S) extern "C" R N##New A __asm__(S);
QCF_PAIR(void,qcfComplete,(void*,bool),"_ZN16CQuestController16setQuestCompleteEb")
QCF_PAIR(void,qcfInteract,(void*),"_ZN16CQuestController16interactWithUnitEv")
TL_ORIGINAL(void,qcfDescriptor,(void*,void*,unsigned,void*),"_ZN26CQuestControllerDescriptor15InputLogicEventEP17CEditorBaseObjectjS1_")
TL_FUNCTION(qcfManager,"_ZN13CQuestManager12getSingletonEv")
TL_FUNCTION(qcfQuery,"_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qcfGive,"_ZN13CQuestManager9giveQuestEP6CQuestP9CBaseUnitb")
TL_FUNCTION(qcfSet,"_ZN6CQuest13setIsCompleteEb")
TL_FUNCTION(qcfFinish,"_ZN13CQuestManager13completeQuestEP6CQuest")
TL_FUNCTION(qcfReset,"_ZN13CQuestManager10resetQuestEP6CQuest")
TL_FUNCTION(qcfLookup,"_ZN6CLevel22getBaseUnitByDataGroupEP10CDataGroup")
TL_FUNCTION(qcfAddSafe,"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(qcfRemoveSafe,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(qcfUI,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(qcfRemoveMenu,"_ZN7CGameUI18removeMenuListenerE10EMENU_TYPEP13iMenuListener")
TL_FUNCTION(qcfAddMenu,"_ZN7CGameUI15addMenuListenerE10EMENU_TYPEP13iMenuListener")
TL_FUNCTION(qcfClose,"_ZN7CGameUI8closeAllEv")
TL_FUNCTION(qcfForce,"_ZN7CGameUI22forceInteractiveDialogEP7CPlayerP9CBaseUnitP6CQuest")
TL_FUNCTION(qcfAddUpdate,"_ZN6CLevel15addUpdateObjectEP12iLevelUpdate")
TL_ORIGINAL(void,qcfCoreCtor,(void*),"_ZN10CRunicCoreC1Ev")
TL_ORIGINAL(void,qcfCoreDtor,(void*),"_ZN10CRunicCoreD1Ev")
TL_ORIGINAL(void,qcfOldUIAdd,(void*,int,void*),"_ZN7CGameUI15addMenuListenerE10EMENU_TYPEP13iMenuListener")
TL_ORIGINAL(void,qcfOldUIRemove,(void*,int,void*),"_ZN7CGameUI18removeMenuListenerE10EMENU_TYPEP13iMenuListener")
TL_ORIGINAL(void,qcfOldLevelAdd,(void*,void*),"_ZN6CLevel15addUpdateObjectEP12iLevelUpdate")
TL_ORIGINAL(void,qcfMenuBroadcast,(void*,int,int),"_ZN13CDropdownMenu14broadcastEventE10EMENU_TYPE11EMENU_EVENT")
TL_ORIGINAL(void,qcfLevelTick,(void*,void*,const float*,float),"_ZN6CLevel24updateLevelUpdateObjectsEPN4Ogre6CameraERKNS0_7Vector3Ef")
extern "C" void qcfMenuThunk(void*,void*,int,int) __asm__("_ZThn88_N16CQuestController16menuEventOccuredEPv10EMENU_TYPE11EMENU_EVENT");
extern "C" long long qcfUpdateThunk(void*,float,void*,const float*) __asm__("_ZThn96_N16CQuestController17updateLevelObjectEfPN4Ogre6CameraERKNS0_7Vector3E");
extern "C" void qcfMenuD1(void*) __asm__("_ZThn88_N16CQuestControllerD1Ev");
extern "C" void qcfMenuD0(void*) __asm__("_ZThn88_N16CQuestControllerD0Ev");
extern "C" void qcfUpdateD1(void*) __asm__("_ZThn96_N16CQuestControllerD1Ev");
extern "C" void qcfUpdateD0(void*) __asm__("_ZThn96_N16CQuestControllerD0Ev");
namespace qcf {
template<class T>T& at(void* p,unsigned o){return *reinterpret_cast<T*>((char*)p+o);}
struct List {void** data;unsigned count,capacity,grow,pad;};
typedef char ABI[sizeof(std::wstring)==8&&sizeof(List)==24?1:-1];
struct Case {unsigned mode,input,fault,consumer;};
struct Stop {};
struct Entry {unsigned code,a,b,c;};
static const Case* cs;static autotest::Capture* cap;static unsigned errors,used,total;
static Entry expected[64];
void n(unsigned v){cap->add(&v,4);}
void need(bool b){if(!b)++errors;}
void* raw(unsigned s){return autotest::allocate(s);}
unsigned id(void* p,void** values,unsigned count){if(!p)return 99;for(unsigned i=0;i<count;++i)if(p==values[i])return i;return 98;}
void want(unsigned c,unsigned a=0,unsigned b=0,unsigned d=0){need(total<64);if(total<64){Entry& e=expected[total++];e.code=c;e.a=a;e.b=b;e.c=d;}}
void emit(unsigned c,unsigned a=0,unsigned b=0,unsigned d=0){n(c);n(a);n(b);n(d);need(used<total);if(used<total){Entry& e=expected[used];need(e.code==c&&e.a==a&&e.b==b&&e.c==d);}++used;if(cs->fault==used)throw Stop();}
void start(void* p,autotest::Capture& o){cs=(Case*)p;cap=&o;errors=used=total=0;autotest::g_arenaUsed=0;}
void tail(bool caught){need(caught==(cs->fault!=0));need(used==(cs->fault?cs->fault:total));n(caught);n(used);n(0x51434649);n(errors);}
bool good(const autotest::Outcome& o){unsigned v[2]={0,1};if(o.capture.length>=8)std::memcpy(v,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&v[0]==0x51434649&&!v[1];}
bool pair(const tlhybrid_host* host,autotest::Coverage& cv,autotest::Body a,autotest::Body b,Case c){autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);
 bool ok=good(x)&&good(y)&&x.capture.length==y.capture.length&&!std::memcmp(x.capture.data,y.capture.data,x.capture.length);
 if(c.consumer==1)ok=ok&&x.capture.callStarted&&y.capture.callStarted&&x.capture.callCompleted&&y.capture.callCompleted&&x.capture.callTarget==0xdba0b0&&y.capture.callTarget==0xdba0b0;
 else if(c.fault)ok=ok&&x.capture.callStarted&&y.capture.callStarted&&!x.capture.callCompleted&&!y.capture.callCompleted&&x.capture.callTarget==cv.original&&host->comparison_pair(x.capture.callTarget,y.capture.callTarget);
 else if(cv.observe(host,x,y))ok=false;
 if(!ok){unsigned xe=~0u,ye=~0u;if(x.capture.length>=4)std::memcpy(&xe,x.capture.data+x.capture.length-4,4);if(y.capture.length>=4)std::memcpy(&ye,y.capture.data+y.capture.length-4,4);host->log(" frontier %s mode=%u input=%u fault=%u consumer=%u good=%u/%u errors=%u/%u status=%d/%d lengths=%lu/%lu\n",cv.name,c.mode,c.input,c.fault,c.consumer,good(x),good(y),xe,ye,x.childStatus,y.childStatus,(unsigned long)x.capture.length,(unsigned long)y.capture.length);}
 return ok;
}
static void* menuTable[]={(void*)-88,(void*)0xffde00,(void*)&qcfMenuD1,(void*)&qcfMenuD0,(void*)&qcfMenuThunk};
static void* updateTable[]={(void*)-96,(void*)0xffde00,(void*)&qcfUpdateD1,(void*)&qcfUpdateD0,(void*)&qcfUpdateThunk};
}
namespace qcc {
using namespace qcf;
static void *owner,*quest[3],*manager[5];static void* primary[12];
static unsigned managerCalls,nested,setCalls[3],completeCalls[3],resetCalls[3],giveCalls[3];
typedef void(*Fn)(void*,bool);static Fn invoked;
unsigned qid(void* p){return id(p,quest,3);}
bool value(){return cs->mode!=1&&cs->mode!=10&&cs->mode!=11&&cs->mode!=12;}
unsigned response(){return cs->mode==2?1:cs->mode==14?0x101:0x100;}
void* singleton(){unsigned call=managerCalls;emit(1,call);++managerCalls;if(cs->mode==7&&call==0)at<void*>(owner,0x98)=quest[1];if(cs->mode==8&&call==1)at<void*>(owner,0x98)=quest[2];return manager[call?1:0];}
unsigned long long query(void* m,const std::wstring& s){need(m==manager[0]&&&s==&at<std::wstring>(quest[0],0x50)&&s==L"quest A"&&s!=at<std::wstring>(owner,0xa8));emit(2,0,response());
 if(cs->mode==5||cs->mode==6||cs->mode==8)at<void*>(owner,0x98)=quest[1];
 if(cs->mode==16&&!nested){nested=1;invoked(owner,false);nested=0;}
 return 0x7263000000000000ULL|response();
}
long long give(void* m,void* q,void* unit,bool announce){need(m==manager[1]&&!unit&&!announce);unsigned i=qid(q);emit(3,i,1);if(i<3)++giveCalls[i];if(cs->mode==6)at<void*>(owner,0x98)=quest[2];if(cs->mode==17&&!nested){nested=1;invoked(owner,false);nested=0;}return 0;}
void set(void* q,bool v){unsigned i=qid(q);emit(4,i,v);if(i<3)++setCalls[i];at<unsigned char>(q,0x24)=v;if(cs->mode==6)at<void*>(owner,0x98)=quest[0];if(cs->mode==9||cs->mode==12)at<void*>(owner,0x98)=quest[1];}
long long finish(void* m,void* q){unsigned i=qid(q);need(i<3&&m==manager[i+2]);emit(5,i,i+2);if(i<3)++completeCalls[i];return 1;}
void reset(void* m,void* q){unsigned i=qid(q);need(i<3&&m==manager[i+2]);emit(6,i,i+2);if(i<3)++resetCalls[i];}
void setup(){owner=raw(0xb8);std::memset(primary,0,sizeof(primary));primary[1]=(void*)0xffde00;at<void*>(owner,0)=primary+2;new((char*)owner+0xa8)std::wstring(L"different controller name");managerCalls=nested=0;
 std::memset(setCalls,0,sizeof(setCalls));std::memset(completeCalls,0,sizeof(completeCalls));std::memset(resetCalls,0,sizeof(resetCalls));std::memset(giveCalls,0,sizeof(giveCalls));
 for(unsigned i=0;i<5;++i)manager[i]=raw(16);
 for(unsigned i=0;i<3;++i){quest[i]=raw(0x220);new((char*)quest[i]+0x50)std::wstring(i==0?L"quest A":i==1?L"quest B":L"quest C");at<void*>(quest[i],0x1d0)=manager[i+2];at<unsigned char>(quest[i],0x26)=1;}
 at<void*>(owner,0x98)=cs->mode<2?0:quest[0];at<unsigned char>(quest[0],0x24)=cs->mode==11;
 if(cs->mode==4||cs->mode==6||cs->mode==8||cs->mode==17)at<unsigned char>(quest[0],0x26)=0;
 if(cs->mode==6||cs->mode==8)at<unsigned char>(quest[1],0x26)=0;
}
void plan(){unsigned m=cs->mode;if(m<2)return;if(!value()){want(4,0,0);want(6,m==12?1:0,m==12?3:2);return;}
 want(1,0);want(2,0,response());if(response()&255)return;
 if(m==16){want(4,0,0);want(6,0,2);}
 unsigned q=(m==5||m==6||m==7||m==8)?1:0;
 if(m==4||m==6||m==8||m==17){want(1,1);want(3,q,1);if(m==6||m==8)q=2;if(m==17){want(4,0,0);want(6,0,2);}}
 want(4,q,1);if(m==6)q=0;if(m==9)q=1;want(5,q,q+2);
}
void side(void* p,autotest::Capture& out,bool candidate){start(p,out);setup();plan();invoked=candidate?&qcfCompleteNew:&qcfCompleteOld;bool caught=false;
 {detour::Set d,route;TL_REDIRECT(d,qcfManager,&singleton);TL_REDIRECT(d,qcfQuery,&query);TL_REDIRECT(d,qcfGive,&give);TL_REDIRECT(d,qcfSet,&set);TL_REDIRECT(d,qcfFinish,&finish);TL_REDIRECT(d,qcfReset,&reset);
  if(cs->consumer&&candidate)route.redirect(reinterpret_cast<char*>(&qcfCompleteOld),reinterpret_cast<char*>(&qcfCompleteOld),&qcfCompleteNew);
  if(d.failed()||route.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  if(cs->consumer){if(!autotest::beginInvocation(out,&qcfDescriptor))return;try{qcfDescriptor(0,owner,value()?0x37:0x38,0);out.callCompleted=1;}catch(const Stop&){caught=true;}}
  else{if(!autotest::beginInvocation(out,invoked))return;try{invoked(owner,value());out.callCompleted=1;}catch(const Stop&){caught=true;}}
 }
 n(qid(at<void*>(owner,0x98)));n(managerCalls);for(unsigned i=0;i<3;++i){n(at<unsigned char>(quest[i],0x24));n(at<unsigned char>(quest[i],0x26));n(setCalls[i]);n(completeCalls[i]);n(resetCalls[i]);n(giveCalls[i]);at<std::wstring>(quest[i],0x50).~basic_string();}
 at<std::wstring>(owner,0xa8).~basic_string();tail(caught);
}
void oldSide(void* p,autotest::Capture& o){side(p,o,false);}void newSide(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(questcontroller_set_complete){using namespace qcf;autotest::Coverage cv("questcontroller_set_complete",0xde6b20);for(unsigned m=0;m<18;++m){Case c={m,0,0,0};if(!pair(host,cv,qcc::oldSide,qcc::newSide,c)){cv.report(host);return 1;}}cv.report(host);return cv.completed!=18||cv.different||cv.missing;}
TL_TEST(questcontroller_set_complete_unwind){using namespace qcf;autotest::Coverage cv("set complete unwind excluded",0xde6b20);const unsigned modes[]={6,12,16,17};const unsigned counts[]={6,2,6,8};for(unsigned i=0;i<4;++i)for(unsigned f=1;f<=counts[i];++f){Case c={modes[i],0,f,0};if(!pair(host,cv,qcc::oldSide,qcc::newSide,c))return 1;}host->log(" controller set complete: 22 exact partial-state throws; no completed-call credit\n");return 0;}
TL_TEST(questcontroller_completion_descriptor_consumer){using namespace qcf;if(!host->comparison_pair(0xde6b20,(uint64_t)&qcfCompleteNew))return 1;autotest::Coverage cv("completion descriptor consumer",0xde6b20);for(unsigned m=0;m<18;++m){Case c={m,0,0,1};if(!pair(host,cv,qcc::oldSide,qcc::newSide,c))return 1;}host->log(" original descriptor: 18 completion dispatch comparisons; consumer-only\n");return 0;}

namespace qci {
using namespace qcf;
static void *owner,*unit[2],*quest[2],*resources[2],*clients[2],*players[2],*levels[2],*ui[4],*dataGroup,*menu;
static void *primary[12],*alternate[12],*playerTable[10],*playerAlternate[10];
static unsigned uiCalls,removed,added,closed,forced,broadcasts,sets,gets,lookups,safeRemoves,safeAdds;
static detour::Set *addPatch,*removePatch,*menuAddPatch,*menuRemovePatch;
static bool playerEnabled[2];
unsigned uid(void* p){return id(p,unit,2);}unsigned qid(void* p){return id(p,quest,2);}unsigned pid(void* p){return id(p,players,2);}
unsigned slots(void* core){void* l=at<void*>(core,8);if(!l)return 0;List& a=at<List>(l,0);unsigned n=0;for(unsigned i=0;i<a.count;++i)if(a.data[i]==(char*)owner+0x78)++n;return n;}
unsigned originalAdd(void* p,void* cell){return reinterpret_cast<unsigned(*)(void*,void*)>(qcfAddSafe_original)(p,cell);}
void originalRemove(void* p,void* cell,unsigned index){reinterpret_cast<void(*)(void*,void*,unsigned)>(qcfRemoveSafe_original)(p,cell,index);}
void bind(void* target){
 // Reentrant collaborator work uses real core operations, not the method's
 // observed boundary hooks. Each side therefore has genuine memberships.
 addPatch->restore();removePatch->restore();void* old=at<void*>(owner,0x78);
 if(old!=target){if(old)originalRemove(old,(char*)owner+0x78,at<unsigned>(owner,0x80));at<void*>(owner,0x78)=0;if(target)at<unsigned>(owner,0x80)=originalAdd(target,(char*)owner+0x78);at<void*>(owner,0x78)=target;}
}
void installSafes();
unsigned addSafe(void* p,void* cell){need(cell==(char*)owner+0x78&&at<void*>(cell,0)==0);emit(22,uid(p),at<unsigned>(cell,8));++safeAdds;addPatch->restore();unsigned index=originalAdd(p,cell);TL_REDIRECT(*addPatch,qcfAddSafe,&addSafe);need(!addPatch->failed());need(slots(p)==1);return index;}
void removeSafe(void* p,void* cell,unsigned index){need(cell==(char*)owner+0x78&&at<void*>(cell,0)==p&&at<unsigned>(cell,8)==index&&slots(p)==1);emit(21,uid(p),index);++safeRemoves;removePatch->restore();originalRemove(p,cell,index);TL_REDIRECT(*removePatch,qcfRemoveSafe,&removeSafe);need(!removePatch->failed());need(!slots(p));}
void installSafes(){TL_REDIRECT(*addPatch,qcfAddSafe,&addSafe);TL_REDIRECT(*removePatch,qcfRemoveSafe,&removeSafe);need(!addPatch->failed()&&!removePatch->failed());}
void replaceUnit(unsigned i){bind(unit[i]);installSafes();}
void* lookup(void* p,void* data){need(p==levels[0]&&data==dataGroup);emit(20);++lookups;
 if(cs->mode==4||cs->mode==6)replaceUnit(1);if(cs->mode==5)replaceUnit(0);
 return cs->mode==1||cs->mode==6?0:unit[0];
}
void* singleton(){unsigned c=uiCalls,which=cs->consumer==2?0:c;need(c<5);if(which>=4)which=0;emit(23,c,which);++uiCalls;
 if(cs->mode==12&&c==3){replaceUnit(1);at<void*>(owner,0x98)=quest[1];}
 return ui[which];
}
void removeMenu(void* p,int type,void* listener){need(type==0&&listener==(char*)owner+0x58);emit(24,id(p,ui,4));++removed;
 if(cs->consumer==2){menuRemovePatch->restore();qcfOldUIRemove(p,type,listener);TL_REDIRECT(*menuRemovePatch,qcfRemoveMenu,&removeMenu);need(!menuRemovePatch->failed());}
 if(cs->mode==7)at<void*>(owner,0x68)=resources[1];
}
void addMenu(void* p,int type,void* listener){need(type==0&&listener==(char*)owner+0x58);emit(25,id(p,ui,4));++added;
 if(cs->consumer==2){menuAddPatch->restore();qcfOldUIAdd(p,type,listener);TL_REDIRECT(*menuAddPatch,qcfAddMenu,&addMenu);need(!menuAddPatch->failed());}
 if(cs->mode==8)at<void*>(owner,0x68)=resources[1];
}
void close(void* p){emit(26,id(p,ui,4));++closed;if(cs->mode==9)at<void*>(owner,0x68)=resources[1];}
unsigned long long enabled(void* p){unsigned i=pid(p);need(i<2);emit(27,i,cs->input&1);++gets;
 if(cs->mode==10){at<void*>(owner,0x68)=resources[1];at<bool>(owner,0xb3)=!(cs->input&2);}
 if(cs->mode==14)at<void*>(p,0)=playerAlternate;
 return 0x5200000000000100ULL|(cs->input&1);
}
void setEnabledCommon(void* p,bool value,unsigned alternative){unsigned i=pid(p);need(i<2);emit(28,i,value,alternative);++sets;if(i<2)playerEnabled[i]=value;
 if(cs->mode==11){replaceUnit(1);at<void*>(owner,0x98)=quest[1];at<void*>(owner,0x68)=resources[1];}
}
void setEnabled(void* p,bool value){setEnabledCommon(p,value,0);}void setEnabledAlt(void* p,bool value){setEnabledCommon(p,value,1);}
void force(void* p,void* player,void* target,void* q){need(p==ui[cs->consumer==2?0:3]);emit(29,pid(player),uid(target),qid(q));++forced;if(cs->mode==13)at<void*>(owner,0)=alternate+2;}
void broadcast(void* p,unsigned e){need(p==owner);emit(30,e,0);++broadcasts;}void broadcastAlt(void* p,unsigned e){need(p==owner);emit(30,e,1);++broadcasts;}
void setup(bool candidate){owner=raw(0xb8);dataGroup=raw(8);menu=0;uiCalls=removed=added=closed=forced=broadcasts=sets=gets=lookups=safeRemoves=safeAdds=0;
 std::memset(primary,0,sizeof(primary));std::memset(alternate,0,sizeof(alternate));std::memset(playerTable,0,sizeof(playerTable));std::memset(playerAlternate,0,sizeof(playerAlternate));
 primary[1]=alternate[1]=(void*)0xffde00;primary[8]=(void*)&broadcast;alternate[8]=(void*)&broadcastAlt;playerTable[8]=(void*)&setEnabled;playerAlternate[8]=(void*)&setEnabledAlt;playerTable[9]=playerAlternate[9]=(void*)&enabled;
 at<void*>(owner,0)=primary+2;at<unsigned>(owner,0x80)=0x777;new((char*)owner+0xa8)std::wstring(L"frontier interact");at<bool>(owner,0xb2)=!(cs->input&1);at<bool>(owner,0xb3)=cs->input&2;at<int>(owner,0xb4)=5;
 for(unsigned i=0;i<2;++i){unit[i]=raw(16);qcfCoreCtor(unit[i]);for(unsigned j=0;j<=i;++j){void* cell=raw(16);at<void*>(cell,0)=unit[i];at<unsigned>(cell,8)=originalAdd(unit[i],cell);}
  quest[i]=raw(16);resources[i]=raw(0x50);clients[i]=raw(0x90);players[i]=raw(0x90);levels[i]=raw(0xc0);playerEnabled[i]=cs->input&1;
  at<void*>(resources[i],0x18)=levels[i];at<void*>(resources[i],0x28)=raw(8);at<void*>(at<void*>(resources[i],0x28),0)=clients[i];at<unsigned>(resources[i],0x30)=1;at<void*>(clients[i],0x58)=players[i];at<void*>(players[i],0)=playerTable;
 }
 for(unsigned i=0;i<4;++i)ui[i]=raw(cs->consumer==2?0x548:8);
 at<void*>(owner,0x68)=resources[0];at<void*>(owner,0x70)=cs->mode?dataGroup:0;at<void*>(owner,0x98)=quest[0];
 if(cs->mode>=3&&cs->mode!=4&&cs->mode!=5&&cs->mode!=6){at<unsigned>(owner,0x80)=originalAdd(unit[0],(char*)owner+0x78);at<void*>(owner,0x78)=unit[0];}
 if(cs->consumer==2){menu=raw(0xc0);at<void*>(ui[0],0x538)=menu;at<void*>(menu,0)=(void*)0xff0ad0;
  List& listeners=at<List>(menu,0x90);listeners.data=new void*[4];std::memset(listeners.data,0,32);listeners.capacity=listeners.grow=4;at<List>(menu,0xa8).grow=4;
  List& updates=at<List>(levels[0],0xa8);updates.data=(void**)raw(32);updates.capacity=updates.grow=4;
  at<void*>(owner,0x58)=candidate?(void*)(menuTable+2):(void*)0xffdd90;at<void*>(owner,0x60)=candidate?(void*)(updateTable+2):(void*)0xffddb8;
 }
}
void plan(){unsigned m=cs->mode;if(!m)return;
 if(m<=6&&m!=3){want(20);if(m==1)return;if(m==4||m==6)want(21,1,2);if(m==6)return;if(m!=5)want(22,0,m==4?2:0x777);}
 unsigned same=cs->consumer==2;want(23,0,0);want(24,0);want(23,1,same?0:1);want(25,same?0:1);want(23,2,same?0:2);want(26,same?0:2);
 unsigned player=m>=7&&m<=9?1:0;want(27,player,cs->input&1);bool disable=m==10?!(cs->input&2):(cs->input&2)!=0;
 if(disable)want(28,player,0,m==14?1:0);want(23,3,same?0:3);unsigned target=m==11&&disable?1:0;want(29,player,target,target);want(30,0x5b,m==13?1:0);
 if(cs->consumer==2){unsigned event=cs->mode==3?3:cs->mode==15?4:7;if(disable)want(28,0,cs->input&1);want(30,0x5c);if(event==3||event==4)want(30,event==3?0x5d:0x5e);want(23,4,0);want(24,0);}
}
void snapshot(){n(uid(at<void*>(owner,0x78)));n(qid(at<void*>(owner,0x98)));n(at<unsigned>(owner,0x80));n(at<bool>(owner,0xb2));n(at<bool>(owner,0xb3));n(id(at<void*>(owner,0x68),resources,2));n(at<void*>(owner,0)==alternate+2);n(at<int>(owner,0xb4));
 for(unsigned i=0;i<2;++i){n(slots(unit[i]));n(playerEnabled[i]);n(at<void*>(players[i],0)==playerAlternate);}n(uiCalls);n(removed);n(added);n(closed);n(forced);n(broadcasts);n(sets);n(gets);n(lookups);n(safeRemoves);n(safeAdds);
}
void cleanup(){for(unsigned i=0;i<2;++i)qcfCoreDtor(unit[i]);at<std::wstring>(owner,0xa8).~basic_string();if(menu){delete[] at<List>(menu,0x90).data;delete[] at<List>(menu,0xa8).data;}}
void side(void* p,autotest::Capture& out,bool candidate){start(p,out);setup(candidate);plan();bool caught=false;
 {detour::Set callbacks,adds,removes,menuAdds,menuRemoves,route,levelRoute;addPatch=&adds;removePatch=&removes;menuAddPatch=&menuAdds;menuRemovePatch=&menuRemoves;installSafes();
  TL_REDIRECT(callbacks,qcfLookup,&lookup);TL_REDIRECT(callbacks,qcfUI,&singleton);TL_REDIRECT(menuRemoves,qcfRemoveMenu,&removeMenu);TL_REDIRECT(menuAdds,qcfAddMenu,&addMenu);TL_REDIRECT(callbacks,qcfClose,&close);TL_REDIRECT(callbacks,qcfForce,&force);
  if(cs->consumer==1&&candidate)route.redirect(reinterpret_cast<char*>(&qcfInteractOld),reinterpret_cast<char*>(&qcfInteractOld),&qcfInteractNew);
  if(cs->consumer==2&&qcfAddUpdate_linked!=qcfAddUpdate_original)levelRoute.redirect(qcfAddUpdate_linked,qcfAddUpdate_linked,&qcfOldLevelAdd);
  if(callbacks.failed()||adds.failed()||removes.failed()||menuAdds.failed()||menuRemoves.failed()||route.failed()||levelRoute.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef void(*Fn)(void*);Fn fn=candidate?&qcfInteractNew:&qcfInteractOld;
  if(cs->consumer==1){if(!autotest::beginInvocation(out,&qcfDescriptor))return;try{qcfDescriptor(0,owner,0x30,0);out.callCompleted=1;}catch(const Stop&){caught=true;}}
  else{if(!autotest::beginInvocation(out,fn))return;try{fn(owner);out.callCompleted=1;}catch(const Stop&){caught=true;}}
  if(cs->consumer==2&&!caught){List& listeners=at<List>(menu,0x90);List& pending=at<List>(menu,0xa8);List& updates=at<List>(levels[0],0xa8);
   need(listeners.count==1&&listeners.data[0]==(char*)owner+0x58&&!pending.count);unsigned event=cs->mode==3?3:cs->mode==15?4:7;qcfMenuBroadcast(menu,0,event);
   need(updates.count==1&&updates.data[0]==(char*)owner+0x60);need(at<int>(owner,0xb4)==(int)event);float pos[3]={0,1,2};qcfLevelTick(levels[0],0,pos,0.5f);
   need(!updates.count&&listeners.count==1&&pending.count==1&&pending.data[0]==(char*)owner+0x58);qcfMenuBroadcast(menu,0,7);need(!listeners.count&&!pending.count&&!pending.capacity&&!pending.data&&!updates.count);need(playerEnabled[0]==bool(cs->input&1));
  }
 }
 snapshot();if(!caught){if(cs->mode==0||cs->mode==1||cs->mode==6){need(!at<void*>(owner,0x78));need(at<bool>(owner,0xb2)==!(cs->input&1));}else{need(at<bool>(owner,0xb2)==bool(cs->input&1));need(forced==1);}}
 cleanup();tail(caught);
}
void oldSide(void* p,autotest::Capture& o){side(p,o,false);}void newSide(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(questcontroller_interact){using namespace qcf;autotest::Coverage cv("questcontroller_interact",0xde6d40);for(unsigned m=0;m<15;++m)for(unsigned input=0;input<4;++input){Case c={m,input,0,0};if(!pair(host,cv,qci::oldSide,qci::newSide,c)){cv.report(host);return 1;}}cv.report(host);return cv.completed!=60||cv.different||cv.missing;}
TL_TEST(questcontroller_interact_unwind){using namespace qcf;autotest::Coverage cv("interact unwind excluded",0xde6d40);const unsigned modes[]={4,11,12,13,14};const unsigned counts[]={14,11,11,11,11};for(unsigned i=0;i<5;++i)for(unsigned f=1;f<=counts[i];++f){Case c={modes[i],3,f,0};if(!pair(host,cv,qci::oldSide,qci::newSide,c))return 1;}host->log(" controller interact: 58 supported boundary throws, exact partial safe/listener/player state; no completed-call credit\n");return 0;}
TL_TEST(questcontroller_interact_descriptor_consumer){using namespace qcf;if(!host->comparison_pair(0xde6d40,(uint64_t)&qcfInteractNew))return 1;autotest::Coverage cv("interact descriptor consumer",0xde6d40);for(unsigned m=0;m<15;++m){Case c={m,3,0,1};if(!pair(host,cv,qci::oldSide,qci::newSide,c))return 1;}host->log(" original descriptor: 15 interact dispatch comparisons; consumer-only\n");return 0;}
TL_TEST(questcontroller_interact_real_menu_level){using namespace qcf;if(!host->comparison_pair(0xde6cb0,(uint64_t)&qcfMenuThunk)||!host->comparison_pair(0xde6eb0,(uint64_t)&qcfUpdateThunk))return 1;autotest::Coverage cv("questcontroller_interact_real_menu_level",0xde6d40);const unsigned modes[]={3,15,16};for(unsigned m=0;m<3;++m)for(unsigned input=0;input<4;++input){Case c={modes[m],input,0,2};if(!pair(host,cv,qci::oldSide,qci::newSide,c)){cv.report(host);return 1;}}cv.report(host);return cv.completed!=12||cv.different||cv.missing;}

// Real accepted manager closure: give/complete/reset, quest acceptance setter,
// completion setter and controller callbacks. Only translation and NPC setup
// remain external stubs. Manager player is legitimately null; no UI/audio or
// reward effects are synthesized. Genuine maps and active-list storage survive
// a full complete -> reset transition in the same invocation.
TL_FUNCTION(qcfTranslateSingleton,"_ZN16CStringTranslate11getSingltonEv")
TL_FUNCTION(qcfTranslate,"_ZN16CStringTranslate18getTranslateStringEPKw")
TL_FUNCTION(qcfInitialize,"_ZN6CQuest22initializeQuestWithNPCEP9CBaseUnit")
namespace qcr {
using namespace qcf;
typedef std::map<std::wstring,bool> Map;
static void *owner,*manager,*quest,*resource,*dialog,*translator;static void* primary[12];static Map* completed;static List* active;static bool candidate;
static detour::Set *givePatch,*finishPatch,*resetPatch,*setPatch;
void* singleton(){emit(40);return manager;}
void* translatorSingleton(){emit(41);return translator;}
std::wstring translate(void* p,const wchar_t* text){need(p==translator&&std::wstring(text)==L"New Quest");emit(42);return L"fixture new quest";}
void initialize(void* p,void* npc){need(p==quest&&!npc);emit(43);at<void*>(quest,0x30)=0;}
void broadcast(void* p,unsigned event){need(p==owner);emit(44,event);}
long long give(void* m,void* q,void* u,bool announce){need(m==manager&&q==quest&&!u&&!announce);emit(45);givePatch->restore();typedef long long(*Fn)(void*,void*,void*,bool);Fn fn=reinterpret_cast<Fn>(candidate?qcfGive_linked:qcfGive_original);long long r=fn(m,q,u,announce);TL_REDIRECT(*givePatch,qcfGive,&give);need(!givePatch->failed()&&r==1&&active->count==1&&active->data[0]==quest&&at<unsigned char>(quest,0x26));return r;}
long long finish(void* m,void* q){need(m==manager&&q==quest&&at<unsigned char>(quest,0x24));emit(46);finishPatch->restore();typedef long long(*Fn)(void*,void*);long long r=reinterpret_cast<Fn>(candidate?qcfFinish_linked:qcfFinish_original)(m,q);TL_REDIRECT(*finishPatch,qcfFinish,&finish);need(!finishPatch->failed()&&r==1);return r;}
void reset(void* m,void* q){need(m==manager&&q==quest&&!at<unsigned char>(quest,0x24));emit(47);resetPatch->restore();typedef void(*Fn)(void*,void*);reinterpret_cast<Fn>(candidate?qcfReset_linked:qcfReset_original)(m,q);TL_REDIRECT(*resetPatch,qcfReset,&reset);need(!resetPatch->failed());}
void set(void* q,bool value){need(q==quest);emit(48,value);setPatch->restore();typedef void(*Fn)(void*,bool);reinterpret_cast<Fn>(candidate?qcfSet_linked:qcfSet_original)(q,value);TL_REDIRECT(*setPatch,qcfSet,&set);need(!setPatch->failed()&&at<unsigned char>(quest,0x24)==value);}
void setup(){owner=raw(0xb8);manager=raw(0xd0);quest=raw(0x220);resource=raw(0x50);dialog=raw(0x80);translator=raw(8);std::memset(primary,0,sizeof(primary));primary[1]=(void*)0xffde00;primary[8]=(void*)&broadcast;at<void*>(owner,0)=primary+2;
 new((char*)owner+0xa8)std::wstring(L"frontier real quest");new((char*)quest+0x50)std::wstring(L"frontier real quest");at<void*>(owner,0x98)=quest;at<void*>(quest,0x1d0)=manager;at<void*>(manager,0x38)=resource;
 active=&at<List>(manager,0x18);active->data=(void**)raw(32);active->capacity=active->grow=4;active->count=cs->mode==1||cs->mode==2||cs->mode==3?1:0;if(active->count)active->data[0]=quest;
 completed=new((char*)manager+0x70)Map;completed->insert(Map::value_type(L"frontier real quest",cs->mode==2||cs->mode==5));completed->insert(Map::value_type(L"unrelated",true));
 at<unsigned char>(quest,0x26)=cs->mode==1||cs->mode==2||cs->mode==3;at<unsigned char>(quest,0x24)=cs->mode==2;at<unsigned char>(quest,0x20b)=cs->mode==4;
 List& dialogs=at<List>(quest,0x60);dialogs.data=(void**)raw(8);dialogs.data[0]=dialog;dialogs.count=dialogs.capacity=dialogs.grow=1;at<unsigned char>(dialog,0x76)=1;
 List& listeners=at<List>(quest,0x1b0);listeners.data=(void**)raw(8);void* cell=raw(16);at<void*>(cell,0)=owner;listeners.data[0]=cell;listeners.count=listeners.capacity=listeners.grow=1;
}
void plan(){if(cs->mode==2||cs->mode==3){want(48,0);want(47);want(44,0x65);return;}
 want(40);if(cs->mode==5)return;
 if(cs->mode!=1){want(40);want(45);want(41);want(42);want(44,0x62);}
 want(48,1);want(46);want(43);want(48,cs->mode!=4);want(44,0x64);
 // Complete and then reset through the SAME direct controller entry.
 want(48,0);want(47);want(44,0x65);
}
void side(void* p,autotest::Capture& out,bool replacement){start(p,out);candidate=replacement;setup();plan();
 {detour::Set callbacks,gives,finishes,resets,sets;givePatch=&gives;finishPatch=&finishes;resetPatch=&resets;setPatch=&sets;
  TL_REDIRECT(callbacks,qcfManager,&singleton);TL_REDIRECT(callbacks,qcfTranslateSingleton,&translatorSingleton);TL_REDIRECT(callbacks,qcfTranslate,&translate);TL_REDIRECT(callbacks,qcfInitialize,&initialize);TL_REDIRECT(gives,qcfGive,&give);TL_REDIRECT(finishes,qcfFinish,&finish);TL_REDIRECT(resets,qcfReset,&reset);TL_REDIRECT(sets,qcfSet,&set);
  if(callbacks.failed()||gives.failed()||finishes.failed()||resets.failed()||sets.failed()){out.issue=autotest::Capture::InvalidReport;return;}
  typedef void(*Fn)(void*,bool);Fn fn=candidate?&qcfCompleteNew:&qcfCompleteOld;if(!autotest::beginInvocation(out,fn))return;
  fn(owner,cs->mode!=2&&cs->mode!=3);
  if(cs->mode<2||cs->mode==4){need(!active->count&&!at<unsigned char>(quest,0x26));need(at<unsigned char>(quest,0x24)==(cs->mode!=4));need(completed->find(L"frontier real quest")->second==(cs->mode!=4));need(!at<unsigned char>(dialog,0x76));fn(owner,false);}
  out.callCompleted=1;
 }
 need(!active->count);need(completed->size()==2&&completed->find(L"unrelated")->second);need(completed->find(L"frontier real quest")->second==(cs->mode==5));need(!at<unsigned char>(quest,0x24));need(at<unsigned char>(quest,0x26)==(cs->mode==2||cs->mode==3));
 n(active->count);n(at<unsigned char>(quest,0x24));n(at<unsigned char>(quest,0x26));n(at<unsigned char>(dialog,0x76));for(Map::iterator i=completed->begin();i!=completed->end();++i){out.addText(i->first);n(i->second);}completed->~Map();at<std::wstring>(owner,0xa8).~basic_string();at<std::wstring>(quest,0x50).~basic_string();tail(false);
}
void oldSide(void* p,autotest::Capture& o){side(p,o,false);}void newSide(void* p,autotest::Capture& o){side(p,o,true);}
}
TL_TEST(questcontroller_complete_real_manager_chain){using namespace qcf;autotest::Coverage cv("questcontroller_complete_real_manager_chain",0xde6b20);for(unsigned m=0;m<6;++m){Case c={m,0,0,0};if(!pair(host,cv,qcr::oldSide,qcr::newSide,c)){cv.report(host);return 1;}}cv.report(host);return cv.completed!=6||cv.different||cv.missing;}

namespace qcf {
void descriptorNoop(void* p,autotest::Capture& out){start(p,out);void* owner=raw(0xb8);void* table[12];std::memset(table,0,sizeof(table));
 // Authentic source RTTI for a plain CEditorBaseObject is a non-target type.
 table[1]=(void*)(cs->mode==1?0xfc4610:0xffde00);at<void*>(owner,0)=table+2;
 if(!autotest::beginInvocation(out,&qcfDescriptor))return;qcfDescriptor(0,cs->mode==0?0:owner,cs->mode<2?0x30:cs->mode==2?0x2f:0x39,0);out.callCompleted=1;tail(false);
}
}
TL_TEST(questcontroller_descriptor_noncontroller_inputs){using namespace qcf;autotest::Coverage cv("descriptor no-op consumers",0xdba0b0);for(unsigned m=0;m<4;++m){Case c={m,0,0,1};if(!pair(host,cv,descriptorNoop,descriptorNoop,c))return 1;}host->log(" original descriptor: null, wrong RTTI and outside-range no-op controls\n");return 0;}
