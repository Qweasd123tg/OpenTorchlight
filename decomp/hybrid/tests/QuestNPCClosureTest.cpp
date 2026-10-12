#include <climits>
#include <cstring>
#include <string>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(long long, oldCalc, (void*,void*), "_ZN13CQuestManager16calculateNPCIconEP10CCharacter")
extern "C" long long newCalc(void*,void*) __asm__("_ZN13CQuestManager16calculateNPCIconEP10CCharacter");
TL_ORIGINAL(bool, oldHas, (void*,void*), "_ZN13CQuestManager17getPlayerHasQuestEP6CQuest")
extern "C" bool newHas(void*,void*) __asm__("_ZN13CQuestManager17getPlayerHasQuestEP6CQuest");
TL_ORIGINAL(int, oldIcon, (void*,void*), "_ZN13CQuestManager10getNPCIconEP10CCharacter")
extern "C" int newIcon(void*,void*) __asm__("_ZN13CQuestManager10getNPCIconEP10CCharacter");
TL_FUNCTION(isaFn,"_ZN9CBaseUnit3ISAEN9UNITTYPES10EUNITTYPESE")
TL_FUNCTION(questFn,"_ZN13CQuestManager14getQuestForNPCEP9CBaseUnit")
TL_FUNCTION(singleFn,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(cinemaFn,"_ZN7CGameUI18getUIIsInCinematicEv")
TL_FUNCTION(dialogFn,"_ZN6CQuest14getQuestDialogEP9CBaseUnit")
TL_FUNCTION(completeFn,"_ZN6CQuest10isCompleteEb")
TL_FUNCTION(addFn,"_ZN9CBaseUnit12addUnitThemeERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(removeFn,"_ZN9CBaseUnit15removeUnitThemeERKSbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case {
 unsigned variant, list, singleton, dirty, count; bool nullNPC,nullPlayer,noQuest,cinematic,enabled,npcFlag,noDialog,icon,custom,passive,complete,nullQuery,isa; int state;
 Case():variant(0),list(2),singleton(1),dirty(0),count(4),nullNPC(false),nullPlayer(false),noQuest(false),cinematic(false),enabled(true),npcFlag(false),noDialog(false),icon(true),custom(false),passive(false),complete(false),nullQuery(false),isa(true),state(1){}
};
struct Event {unsigned code;void* self;void* arg;unsigned value;};
struct Block {unsigned char* p;unsigned n;};
Case const* c; autotest::Capture* cap;void *owner,*npc,*player,*quest,*dialog,*ui[2],*other,*data;void* vt[10];
Block blocks[12];unsigned blockCount,errors,eventCount,singleCalls;Event events[32],expected[32];unsigned expectedCount;unsigned char initial[12][0x800];
template<class T>T& at(void*p,unsigned off){return *reinterpret_cast<T*>(static_cast<char*>(p)+off);}
void* raw(unsigned n){unsigned char*p=(unsigned char*)autotest::allocate(n+32);if(!p)_exit(71);std::memset(p,0xd3,16);std::memset(p+16,0,n);std::memset(p+16+n,0x6c,16);blocks[blockCount].p=p;blocks[blockCount++].n=n;return p+16;}
void emit(unsigned code,void*self,void*arg,unsigned value){if(eventCount>=32){++errors;return;}Event&e=events[eventCount++];e.code=code;e.self=self;e.arg=arg;e.value=value;}
void expect(unsigned code,void*self,void*arg=0,unsigned value=0){Event&e=expected[expectedCount++];e.code=code;e.self=self;e.arg=arg;e.value=value;}
unsigned theme(const std::wstring&s){if(s==L"QUEST COMPLETE")return 1;if(s==L"QUEST INCOMPLETE")return 2;if(s==L"QUEST GIVING")return 3;if(s==L"QUEST PASSIVE")return 4;if(s==L"CUSTOM Ω")return 5;++errors;return 99;}
void add(void*self,const std::wstring&s){emit(20,self,0,theme(s));}
void remove(void*self,const std::wstring&s){emit(21,self,0,theme(s));}
bool isA(void*self,int type){emit(7,self,0,type);return c->isa;}
void* getQuest(void*self,void*arg){emit(1,self,arg,0);return c->noQuest?0:quest;}
void* singleton(){void* result=c->singleton?(singleCalls&&c->singleton==2?ui[1]:ui[0]):0;emit(2,0,result,0);++singleCalls;return result;}
bool enabled(void*self){emit(4,self,0,0);return c->enabled;}
bool wrong(void*self){emit(99,self,0,0);++errors;return false;}
void* getDialog(void*self,void*arg){emit(5,self,arg,0);return c->noDialog?0:dialog;}
}
extern "C" unsigned qmcCinemaRecord(void*self){emit(3,self,0,0);return c->cinematic;}
extern "C" unsigned qmcCompleteRecord(void*self,bool value){emit(6,self,0,value);return c->complete;}
extern "C" unsigned long long qmcDirtyCinema(void*);
extern "C" unsigned long long qmcDirtyComplete(void*,bool);
// Explicit machine-level AL probes: upper bits remain nonzero even for false.
__asm__(".text\n.type qmcDirtyCinema,@function\nqmcDirtyCinema:\nsub $8,%rsp\ncall qmcCinemaRecord\nadd $8,%rsp\nmovabs $0x5a6b7c8d12345600,%rdx\nor %rdx,%rax\nret\n.size qmcDirtyCinema,.-qmcDirtyCinema\n"
".type qmcDirtyComplete,@function\nqmcDirtyComplete:\nsub $8,%rsp\ncall qmcCompleteRecord\nadd $8,%rsp\nmovabs $0x6b7c8d9e23456700,%rdx\nor %rdx,%rax\nret\n.size qmcDirtyComplete,.-qmcDirtyComplete\n");
namespace {
void initialize(){autotest::g_arenaUsed=0;blockCount=errors=eventCount=singleCalls=expectedCount=0;
 owner=raw(0xd0);npc=raw(0x730);player=raw(32);quest=raw(0x220);dialog=raw(0xb0);ui[0]=raw(32);ui[1]=raw(32);other=raw(32);data=raw(8*8);
 for(unsigned i=0;i<10;++i)vt[i]=(void*)&wrong;vt[9]=(void*)&enabled;at<void*>(npc,0)=vt;at<unsigned char>(npc,0x70d)=c->npcFlag;
 at<void*>(owner,0x10)=c->nullPlayer?0:player;at<void*>(owner,0x18)=data;at<unsigned>(owner,0x20)=c->list==0?0:c->count;at<unsigned>(owner,0x24)=c->list==5?1:c->count;
 for(unsigned i=0;i<8;++i)at<void*>(data,i*8)=other;
 if(c->list==2||c->list==6)at<void*>(data,0)=c->nullQuery?0:quest;if(c->list==3)at<void*>(data,8)=c->nullQuery?0:quest;if(c->list==4||c->list==6)at<void*>(data,(c->count-1)*8)=c->nullQuery?0:quest;
 if(c->list==5)at<void*>(data,16)=quest; // Raw find sees it, indexed scan must fall back to slot zero.
 at<int>(dialog,0x70)=c->state;at<unsigned char>(dialog,0x75)=c->icon;at<unsigned char>(dialog,0x76)=c->passive;new(static_cast<char*>(dialog)+0x98)std::wstring(c->custom?L"CUSTOM Ω":L"");
}
bool expectedCalc(){if(c->nullNPC||c->nullPlayer)return false;expect(1,owner,npc);for(unsigned t=1;t<=4;++t)expect(21,npc,0,t);expect(2,0,c->singleton?ui[0]:0);
 if(c->singleton){expect(2,0,c->singleton==2?ui[1]:ui[0]);expect(3,c->singleton==2?ui[1]:ui[0]);if(c->cinematic)return true;}
 if(c->noQuest)return false;expect(4,npc);if(!c->enabled&&c->npcFlag)return false;expect(5,quest,npc);if(c->noDialog)return false;if(!c->icon)return true;
 if(c->custom){expect(20,npc,0,5);return true;}if(c->state==4){expect(c->passive?21:20,npc,0,4);expect(21,npc,0,1);expect(21,npc,0,2);expect(21,npc,0,3);return true;}
 bool member=c->list>=2&&c->list<=4;
 if(member){expect(6,quest,0,0);if(c->complete){expect(20,npc,0,1);expect(21,npc,0,2);expect(21,npc,0,3);expect(21,npc,0,4);}else{expect(21,npc,0,1);expect(21,npc,0,3);expect(21,npc,0,4);expect(20,npc,0,2);}}
 else{expect(20,npc,0,3);expect(21,npc,0,1);expect(21,npc,0,2);expect(21,npc,0,4);}return true;
}
void number(unsigned n){cap->add(&n,sizeof(n));}
void side(void*ctx,autotest::Capture&out,bool candidate){c=(Case*)ctx;cap=&out;initialize();for(unsigned i=0;i<blockCount;++i)std::memcpy(initial[i],blocks[i].p,blocks[i].n+32);detour::Set d;
 TL_REDIRECT(d,isaFn,&isA);TL_REDIRECT(d,questFn,&getQuest);TL_REDIRECT(d,singleFn,&singleton);TL_REDIRECT(d,dialogFn,&getDialog);TL_REDIRECT(d,addFn,&add);TL_REDIRECT(d,removeFn,&remove);
 if(c->dirty&1){TL_REDIRECT(d,cinemaFn,&qmcDirtyCinema);}else{TL_REDIRECT(d,cinemaFn,&qmcCinemaRecord);}
 if(c->dirty&2){TL_REDIRECT(d,completeFn,&qmcDirtyComplete);}else{TL_REDIRECT(d,completeFn,&qmcCompleteRecord);}
 if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c->variant==1){typedef bool(*Fn)(void*,void*);Fn fn=candidate?&newHas:&oldHas;if(!autotest::beginInvocation(out,fn))return;bool result=fn(owner,c->nullQuery?0:quest);out.callCompleted=1;bool wanted=(c->list>=2&&c->list<=4)||c->list==6||(c->list==5&&!c->nullQuery);number(result);if(result!=wanted)++errors;}
 else if(c->variant==2){int wanted=-1;
  if(!c->nullNPC){expect(7,npc,0,0x68);if(c->isa&&!c->nullPlayer){expect(1,owner,npc);if(!c->noQuest){expect(5,quest,npc);if(!c->noDialog&&c->icon){if(c->state==1)wanted=23;else if(c->state==2)wanted=26;else if(c->state==3)wanted=22;}}}}
  typedef int(*Fn)(void*,void*);Fn fn=candidate?&newIcon:&oldIcon;if(!autotest::beginInvocation(out,fn))return;int result=fn(owner,c->nullNPC?0:npc);out.callCompleted=1;number(unsigned(result));if(result!=wanted)++errors;
 }
 else{bool wanted=expectedCalc();typedef long long(*Fn)(void*,void*);Fn fn=candidate?&newCalc:&oldCalc;if(!autotest::beginInvocation(out,fn))return;long long result=fn(owner,c->nullNPC?0:npc);out.callCompleted=1;number(unsigned(result));if(result!=static_cast<long long>(wanted))++errors;}
 if(eventCount!=expectedCount)++errors;for(unsigned i=0;i<eventCount;++i){Event&e=events[i];number(e.code);out.add(&e.self,sizeof(e.self));out.add(&e.arg,sizeof(e.arg));number(e.value);if(i>=expectedCount||e.code!=expected[i].code||e.self!=expected[i].self||e.arg!=expected[i].arg||e.value!=expected[i].value)++errors;}
 for(unsigned i=0;i<blockCount;++i){Block&b=blocks[i];if(std::memcmp(b.p,initial[i],b.n+32))++errors;for(unsigned j=0;j<16;++j)if(b.p[j]!=0xd3||b.p[16+b.n+j]!=0x6c)++errors;if(b.p+16==dialog){out.add(b.p,16+0x98);const std::wstring&s=at<std::wstring>(dialog,0x98);unsigned n=s.size();number(n);out.add(s.data(),n*sizeof(wchar_t));out.add(b.p+16+0xa0,b.n-0xa0+16);}else out.add(b.p,b.n+32);}
 number(0x514e5043);number(errors);
}
void oldSide(void*p,autotest::Capture&o){side(p,o,false);}void newSide(void*p,autotest::Capture&o){side(p,o,true);}
bool oracle(const autotest::Capture&o){unsigned f[2];if(o.length<8)return false;std::memcpy(f,o.data+o.length-8,8);return f[0]==0x514e5043&&f[1]==0;}
bool pair(const tlhybrid_host*h,autotest::Coverage&cov,Case&c,unsigned&count){autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);++count;int diff=cov.observe(h,a,b);if(diff||!oracle(a.capture)||!oracle(b.capture)){h->log("quest npc variant=%u list=%u singleton=%u dirty=%u flags=%u%u%u%u%u%u%u%u%u%u%u%u state=%d\n",c.variant,c.list,c.singleton,c.dirty,c.nullNPC,c.nullPlayer,c.noQuest,c.cinematic,c.enabled,c.npcFlag,c.noDialog,c.icon,c.custom,c.passive,c.complete,c.nullQuery,c.state);cov.report(h);return false;}return true;}
}
TL_TEST(quest_manager_has_quest_closure){autotest::Coverage cov("quest_manager_has_quest_closure",0xd264d0);unsigned n=0;
 const unsigned counts[]={0,1,2,4,6};for(unsigned k=0;k<5;++k)for(unsigned l=1;l<=6;++l)for(unsigned q=0;q<2;++q){
  if((counts[k]==0&&l!=1)||(counts[k]==1&&l!=1&&l!=2)||(counts[k]==2&&(l==3||l==5))||(l==5&&counts[k]<4))continue;
  Case c;c.variant=1;c.list=l;c.count=counts[k];c.nullQuery=q;if(!pair(host,cov,c,n))return 1;
 }cov.report(host);return cov.completed!=n||n<20||cov.different||cov.missing;}
TL_TEST(quest_manager_calculate_icon_closure){autotest::Coverage cov("quest_manager_calculate_icon_closure",0xd30900);unsigned n=0;
 for(unsigned l=0;l<6;++l)for(unsigned done=0;done<2;++done)for(unsigned dirty=0;dirty<4;++dirty){Case c;c.list=l;c.complete=done;c.dirty=dirty;if(!pair(host,cov,c,n))return 1;}
 for(unsigned flag=0;flag<13;++flag)for(unsigned dirty=0;dirty<4;++dirty){Case c;c.dirty=dirty;switch(flag){case 0:c.nullNPC=true;break;case 1:c.nullPlayer=true;break;case 2:c.noQuest=true;break;case 3:c.singleton=0;break;case 4:c.singleton=2;break;case 5:c.cinematic=true;break;case 6:c.enabled=false;break;case 7:c.enabled=false;c.npcFlag=true;break;case 8:c.npcFlag=true;break;case 9:c.noDialog=true;break;case 10:c.icon=false;break;case 11:c.custom=true;break;case 12:c.state=4;break;}if(!pair(host,cov,c,n))return 1;}
 for(unsigned p=0;p<2;++p)for(unsigned done=0;done<2;++done)for(unsigned custom=0;custom<2;++custom){Case c;c.state=4;c.passive=p;c.complete=done;c.custom=custom;if(!pair(host,cov,c,n))return 1;}
 cov.report(host);return cov.completed!=n||n<20||cov.different||cov.missing;}

TL_TEST(quest_manager_get_icon_closure){autotest::Coverage cov("quest_manager_get_icon_closure",0xd30830);unsigned n=0;const int states[]={INT_MIN,-1,0,1,2,3,4,5,INT_MAX};
 for(unsigned i=0;i<9;++i)for(unsigned list=0;list<6;++list){Case c;c.variant=2;c.state=states[i];c.list=list;if(!pair(host,cov,c,n))return 1;}
 for(unsigned gate=0;gate<6;++gate)for(unsigned i=0;i<4;++i){Case c;c.variant=2;c.state=i+1;switch(gate){case 0:c.nullNPC=true;break;case 1:c.isa=false;break;case 2:c.nullPlayer=true;break;case 3:c.noQuest=true;break;case 4:c.noDialog=true;break;case 5:c.icon=false;break;}if(!pair(host,cov,c,n))return 1;}
 cov.report(host);return cov.completed!=n||n<20||cov.different||cov.missing;}
