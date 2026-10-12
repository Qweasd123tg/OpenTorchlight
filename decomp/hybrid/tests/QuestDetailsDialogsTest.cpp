// Independent oracles from original d265f0, d2d8e0 and d31140.
// No target implementation is detoured. Dialog collaborators are scripted.
#include <cstring>
#include <string>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void*,qdOldDetails,(void*,void*,void*),"_ZN13CQuestManager18getDetailsForQuestEP6CQuest")
extern "C" void* qdNewDetails(void*,void*,void*) __asm__("_ZN13CQuestManager18getDetailsForQuestEP6CQuest");
TL_ORIGINAL(bool,qdOldActive,(void*,const std::wstring&),"_ZN13CQuestManager16getQuestIsActiveERKSbIwSt11char_traitsIwESaIwEE")
extern "C" bool qdNewActive(void*,const std::wstring&) __asm__("_ZN13CQuestManager16getQuestIsActiveERKSbIwSt11char_traitsIwESaIwEE");
TL_ORIGINAL(void,qdOldDialogs,(void*,void*,void*,bool),"_ZN13CQuestManager16getDialogsForNPCER10TArrayListIP12CQuestDialogEP9CBaseUnitb")
extern "C" void qdNewDialogs(void*,void*,void*,bool) __asm__("_ZN13CQuestManager16getDialogsForNPCER10TArrayListIP12CQuestDialogEP9CBaseUnitb");
TL_FUNCTION(qdDetails,"_ZN6CQuest15getQuestDetailsEv")
TL_FUNCTION(qdDialog,"_ZN6CQuest14getQuestDialogEP9CBaseUnit")
TL_FUNCTION(qdSelect,"_ZN13CQuestManager14getQuestForNPCEP9CBaseUnit")
extern "C" char qdArrayNew[] __asm__("_Znam");
extern "C" char qdArrayDelete[] __asm__("_ZdaPv");
namespace quest_details_dialogs {
template<class T>T& at(void*p,unsigned n){return *reinterpret_cast<T*>((char*)p+n);}
unsigned errors;autotest::Capture* cap;
void need(bool b){if(!b)++errors;}
void num(unsigned n){cap->add(&n,4);}
void* raw(unsigned n){void*p=autotest::allocate(n);if(!p)_exit(71);std::memset(p,0xa5,n);return p;}
bool equal(const std::wstring&a,const std::wstring&b){if(a.size()!=b.size())return false;for(unsigned i=0;i<a.size();++i)if(a[i]!=b[i])return false;return true;}
std::wstring word(unsigned k){static const wchar_t* t[]={L"",L"a",L"aa",L"quest",L"Quest",L"quest ",L"\u0416\u0443\u043a",L"\u732b\u706b",L"\U0001f680",L"a long quest description whose prefix remains common 001",L"a long quest description whose prefix remains common 002"};if(k<11)return std::wstring(t[k]);const wchar_t e[]={L'a',0,L'b',L'\u03a9'};if(k==11)return std::wstring(e,4);if(k==12)return std::wstring(e,2);return std::wstring(96+k,wchar_t(L'A'+k));}
struct Case{unsigned kind,s,v,fault;};
void finish(){num(0x51445159);num(errors);}
bool good(const autotest::Capture& c){unsigned f[2];if(c.length<8)return false;std::memcpy(f,c.data+c.length-8,8);return f[0]==0x51445159&&!f[1];}
void* detailQuest;void* detailDest;std::wstring* detailText;unsigned detailCalls;bool detailThrow;
void* details(void* dest,void* self){++detailCalls;need(self==detailQuest);need(dest==detailDest);if(detailThrow)throw std::bad_alloc();new(dest)std::wstring(*detailText);return dest;}
void detailSide(const Case& c,autotest::Capture& out,bool candidate){void* owner=raw(0xb0);detailQuest=raw(0x200);unsigned char before[0xb0];std::memcpy(before,owner,sizeof(before));unsigned char* storage=(unsigned char*)raw(40);detailDest=storage+16;std::wstring text=word(c.s),saved=text;detailText=&text;detailCalls=0;detailThrow=c.fault;
 if(c.v==1&&!text.empty())text[0]=text[0]; // Unshareable COW source exercises deep copy.
 detour::Set patch;TL_REDIRECT(patch,qdDetails,&details);if(patch.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void*(*Fn)(void*,void*,void*);Fn f=candidate?&qdNewDetails:&qdOldDetails;bool caught=false;void* result=0;if(!autotest::beginInvocation(out,f))return;
 try{result=f(detailDest,c.v==2?0:owner,c.v==3?0:detailQuest);out.callCompleted=1;}catch(const std::bad_alloc&){caught=true;}
 need(caught==(c.fault!=0));need(detailCalls==(c.v==3?0u:1u));need(!std::memcmp(before,owner,sizeof(before)));need(equal(text,saved));for(unsigned i=0;i<16;++i)need(storage[i]==0xa5&&storage[24+i]==0xa5);
 if(!caught){need(result==detailDest);std::wstring&r=*(std::wstring*)detailDest;need(equal(r,c.v==3?std::wstring():saved));out.addText(r);if(!r.empty()){r[0]=L'!';need(equal(text,saved));}r.~basic_string();}num(detailCalls);num(caught);finish();
}
void activeSide(const Case& c,autotest::Capture& out,bool candidate){void* owner=raw(0xb0);void** list=(void**)raw(6*8);void* quests[6];std::wstring query=word(c.s);unsigned count=c.v/4,capacity=c.v%4;for(unsigned i=0;i<6;++i){quests[i]=raw(0x70);new((char*)quests[i]+0x50)std::wstring(word((c.s+i+1)%16));list[i]=quests[i];}
 // Each shape places an exact candidate at one of six different physical slots.
 unsigned match=c.s%6;at<std::wstring>(quests[match],0x50)=query;
 at<void**>(owner,0x18)=list;at<unsigned>(owner,0x20)=count;at<unsigned>(owner,0x24)=capacity;
 unsigned char before[0xb0];std::memcpy(before,owner,sizeof(before));bool wanted=false;
 // Oracle enumerates the distinct reachable physical slots, not a raw-list find.
 if(count){if(equal(at<std::wstring>(quests[0],0x50),query))wanted=true;unsigned reach=count<capacity?count:capacity;for(unsigned i=1;i<reach;++i)if(equal(at<std::wstring>(quests[i],0x50),query))wanted=true;}
 typedef bool(*Fn)(void*,const std::wstring&);Fn f=candidate?&qdNewActive:&qdOldActive;if(!autotest::beginInvocation(out,f))return;bool actual=f(owner,query);out.callCompleted=1;need(actual==wanted);need(!std::memcmp(before,owner,sizeof(before)));need(equal(query,word(c.s)));num(actual);for(unsigned i=0;i<6;++i){need(list[i]==quests[i]);need(equal(at<std::wstring>(quests[i],0x50),i==match?query:word((c.s+i+1)%16)));at<std::wstring>(quests[i],0x50).~basic_string();}finish();}
struct Event{unsigned type,id;};
struct Plan{unsigned active[8],activeN,selected[2],selectN,reply[12],replyN;bool nullNPC,flag;unsigned pre,capacity,increment,mutate,fail,repetitions;};
Plan plan;void* owner;void* npc;void* quests[5];void* dialogs[6];void** list;void** alternate;void* output;unsigned dialogCalls,selectCalls,eventN,allocN,freeN,allocAttempts;Event events[48];
struct Allocation{unsigned char*p;unsigned n;bool freed;};Allocation allocs[12];
void event(unsigned t,unsigned i){need(eventN<48);if(eventN<48){events[eventN].type=t;events[eventN++].id=i;}num(t);num(i);}
unsigned qid(void*p){for(unsigned i=0;i<5;++i)if(p==quests[i])return i;need(false);return 99;}
void* getDialog(void*self,void*arg){need(arg==npc);unsigned id=qid(self);event(1,id);unsigned call=dialogCalls++;if(plan.repetitions>1&&plan.replyN)call%=plan.replyN;if(plan.mutate==1&&call==0)at<unsigned>(owner,0x20)=1;if(plan.mutate==2&&call==0)at<void**>(owner,0x18)=alternate;if(plan.mutate==3&&call==0)at<unsigned>(owner,0x24)=1;if(plan.mutate==4&&call==0)at<unsigned>(owner,0x20)=3;
 need(call<plan.replyN);unsigned r=call<plan.replyN?plan.reply[call]:0;return r?dialogs[r-1]:0;}
void* selectQuest(void*self,void*arg){need(self==owner&&arg==npc);unsigned call=selectCalls++;if(plan.repetitions>1&&plan.selectN)call%=plan.selectN;event(2,call);need(call<plan.selectN);unsigned r=call<plan.selectN?plan.selected[call]:0;return r?quests[r-1]:0;}
void* allocateArray(size_t n){++allocAttempts;event(3,n);if(plan.fail==allocAttempts)throw std::bad_alloc();need(allocN<12);Allocation&a=allocs[allocN++];a.n=n;a.p=(unsigned char*)raw(n+32);a.freed=false;std::memset(a.p+16,0xcc,n);if(plan.mutate==5&&allocAttempts==1)at<unsigned>(output,8)=0;return a.p+16;}
void deleteArray(void*p){if(!p)return;event(4,0);bool found=false;for(unsigned i=0;i<allocN;++i)if(allocs[i].p+16==p&&!allocs[i].freed){allocs[i].freed=true;found=true;}need(found);++freeN;}
void addReply(unsigned r){plan.reply[plan.replyN++]=r;}
void setupPlan(unsigned s,unsigned v,unsigned fault){std::memset(&plan,0,sizeof(plan));plan.flag=true;plan.increment=v+2;plan.pre=v==2?1:0;plan.capacity=v==0?0:2;plan.fail=fault;plan.repetitions=1;
 switch(s){
 case 0:plan.nullNPC=true;break;
 case 1:plan.selectN=1;break; // null selected quest exits even with fallback flag
 case 2:plan.selectN=1;plan.selected[0]=4;addReply(1);break;
 case 3:plan.flag=false;plan.selectN=1;plan.selected[0]=4;addReply(0);break;
 case 4:plan.selectN=plan.pre?1:2;plan.selected[0]=4;addReply(0);break;
 case 5:case 6:plan.selectN=plan.pre?1:2;plan.selected[0]=4;plan.selected[1]=5;addReply(0);if(!plan.pre)addReply(s==5?0:2);break;
 case 7:plan.activeN=1;plan.active[0]=0;addReply(1);plan.selectN=1;break;
 case 8:plan.activeN=3;plan.active[0]=0;plan.active[1]=1;plan.active[2]=2;addReply(1);addReply(0);addReply(2);plan.selectN=1;break;
 case 24:plan.repetitions=2; // Repeated query appends the same pointers again.
 case 9:plan.activeN=3;plan.active[0]=0;plan.active[1]=1;plan.active[2]=2;addReply(1);addReply(1);addReply(1);plan.selectN=1;plan.selected[0]=1;addReply(1);break;
 case 10:case 11:case 12:plan.activeN=4;plan.active[0]=0;plan.active[1]=s==12?1:0;plan.active[2]=0;plan.active[3]=0;for(unsigned i=0;i<4;++i)addReply(i%2+1);plan.selectN=1;break;
 case 13:plan.mutate=1;plan.activeN=1;plan.active[0]=0;addReply(1);plan.selectN=1;break;
 case 14:plan.mutate=2;plan.activeN=3;plan.active[0]=0;plan.active[1]=3;plan.active[2]=4;addReply(1);addReply(2);addReply(3);plan.selectN=1;break;
 case 15:plan.mutate=3;plan.activeN=3;plan.active[0]=0;plan.active[1]=0;plan.active[2]=0;addReply(1);addReply(2);addReply(3);plan.selectN=1;break;
 case 16:plan.mutate=4;plan.activeN=3;plan.active[0]=0;plan.active[1]=1;plan.active[2]=2;addReply(1);addReply(2);addReply(3);plan.selectN=1;break;
 case 17:plan.activeN=2;plan.active[0]=0;plan.active[1]=1;addReply(0);addReply(0);plan.selectN=plan.pre?1:2;plan.selected[0]=4;plan.selected[1]=5;addReply(0);if(!plan.pre)addReply(2);break;
 case 18:plan.activeN=2;plan.active[0]=0;plan.active[1]=1;addReply(0);addReply(0);plan.selectN=1;break;
 case 19:plan.pre=2;plan.capacity=2;plan.activeN=1;plan.active[0]=0;addReply(1);plan.selectN=1;break;
 case 20:plan.pre=2;plan.capacity=2;plan.selectN=1;plan.selected[0]=4;addReply(1);break;
 case 21:plan.pre=0;plan.capacity=0;plan.selectN=2;plan.selected[0]=4;plan.selected[1]=5;addReply(0);addReply(2);break;
 case 22:plan.pre=2;plan.capacity=2;plan.mutate=5;plan.activeN=1;plan.active[0]=0;addReply(1);plan.selectN=1;break;
 case 23:plan.pre=2;plan.capacity=2;plan.mutate=5;plan.selectN=1;plan.selected[0]=4;addReply(1);break;
 }
}
Event wantedEvents[48];unsigned wantedN,wantedCount,wantedCapacity,wantedSlots[32],wantedAlloc,wantedFree,wantedDialogs,wantedSelect;bool wantedBuffer,wantedUnwind;
void wantEvent(unsigned t,unsigned id){wantedEvents[wantedN].type=t;wantedEvents[wantedN++].id=id;}
bool wantAppend(unsigned r){if(!r)return true;if(wantedCount>=wantedCapacity){unsigned next=wantedBuffer?wantedCapacity+plan.increment:plan.increment;if(!wantedBuffer)wantedCapacity=next;wantEvent(3,next*8);++wantedAlloc;if(plan.fail==wantedAlloc){wantedUnwind=true;return false;}if(plan.mutate==5&&wantedAlloc==1)wantedCount=0;if(wantedBuffer){wantEvent(4,0);++wantedFree;}wantedBuffer=true;wantedCapacity=next;}wantedSlots[wantedCount++]=r;return true;}
void makeOracle(){wantedN=wantedAlloc=wantedFree=wantedDialogs=wantedSelect=0;wantedUnwind=false;wantedCount=plan.pre;wantedCapacity=plan.capacity;wantedBuffer=plan.capacity!=0;for(unsigned i=0;i<32;++i)wantedSlots[i]=0;for(unsigned i=0;i<plan.capacity;++i)wantedSlots[i]=i+4;
 if(plan.nullNPC)return;for(unsigned repetition=0;repetition<plan.repetitions;++repetition){for(unsigned i=0;i<plan.activeN;++i){wantEvent(1,plan.active[i]);unsigned r=plan.reply[wantedDialogs++ % plan.replyN];if(!wantAppend(r))return;}
 for(unsigned i=0;i<plan.selectN;++i){wantEvent(2,i);++wantedSelect;if(!plan.selected[i])return;wantEvent(1,plan.selected[i]-1);unsigned r=plan.reply[wantedDialogs++ % plan.replyN];if(!wantAppend(r))return;}}
}
void dialogSide(const Case& c,autotest::Capture& out,bool candidate){setupPlan(c.s,c.v,c.fault);makeOracle();owner=raw(0xb0);npc=raw(32);for(unsigned i=0;i<5;++i)quests[i]=raw(32);for(unsigned i=0;i<6;++i)dialogs[i]=raw(16);list=(void**)raw(8*8);alternate=(void**)raw(8*8);for(unsigned i=0;i<8;++i){list[i]=quests[i%5];alternate[i]=quests[(i+2)%5];}output=raw(56);void* outputBody=(char*)output+16;void* savedOutput=output;output=outputBody;at<void**>(output,0)=0;at<unsigned>(output,8)=plan.pre;at<unsigned>(output,12)=plan.capacity;at<unsigned>(output,16)=plan.increment;
 dialogCalls=selectCalls=eventN=allocN=freeN=allocAttempts=0;
 if(plan.capacity){Allocation&a=allocs[allocN++];a.n=plan.capacity*8;a.p=(unsigned char*)raw(a.n+32);a.freed=false;at<void**>(output,0)=(void**)(a.p+16);for(unsigned i=0;i<plan.capacity;++i)at<void**>(output,0)[i]=dialogs[i+3];}
 unsigned initialCount=plan.activeN;if(c.s==13)initialCount=3;if(c.s==16)initialCount=1;unsigned capacity=8;if(c.s==10)capacity=0;if(c.s==11)capacity=1;if(c.s==12)capacity=2;
 at<void**>(owner,0x18)=list;at<unsigned>(owner,0x20)=initialCount;at<unsigned>(owner,0x24)=capacity;
 unsigned char ownerBefore[0xb0];std::memcpy(ownerBefore,owner,sizeof(ownerBefore));
 detour::Set patch,arrays;TL_REDIRECT(patch,qdDialog,&getDialog);TL_REDIRECT(patch,qdSelect,&selectQuest);arrays.redirect(qdArrayNew,qdArrayNew,&allocateArray);arrays.redirect(qdArrayDelete,qdArrayDelete,&deleteArray);if(patch.failed()||arrays.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Fn)(void*,void*,void*,bool);Fn f=candidate?&qdNewDialogs:&qdOldDialogs;bool caught=false;if(!autotest::beginInvocation(out,f))return;try{for(unsigned repetition=0;repetition<plan.repetitions;++repetition)f(owner,output,plan.nullNPC?0:npc,plan.flag);out.callCompleted=1;}catch(const std::bad_alloc&){caught=true;}
 need(caught==wantedUnwind);need(eventN==wantedN);for(unsigned i=0;i<eventN&&i<wantedN;++i)need(events[i].type==wantedEvents[i].type&&events[i].id==wantedEvents[i].id);
 need(dialogCalls==wantedDialogs);need(selectCalls==wantedSelect);need(allocAttempts==wantedAlloc);need(freeN==wantedFree);need(at<unsigned>(output,8)==wantedCount);need(at<unsigned>(output,12)==wantedCapacity);need(at<unsigned>(output,16)==plan.increment);need((at<void**>(output,0)!=0)==wantedBuffer);
 if(wantedBuffer){void** p=at<void**>(output,0);for(unsigned i=0;i<wantedCount;++i){need(wantedSlots[i]!=0);need(p[i]==dialogs[wantedSlots[i]-1]);out.addPointer(p[i]);} // Mutating allocation resets count before append; original must retain spare slot one.
  if(plan.mutate==5&&!caught){need(p[1]==dialogs[4]);out.addPointer(p[1]);}}
 for(unsigned i=0;i<allocN;++i){Allocation&a=allocs[i];for(unsigned j=0;j<16;++j)need(a.p[j]==0xa5&&a.p[16+a.n+j]==0xa5);}for(unsigned i=0;i<16;++i)need(((unsigned char*)savedOutput)[i]==0xa5&&((unsigned char*)savedOutput)[40+i]==0xa5);
 if(plan.mutate==1&&dialogCalls)at<unsigned>(ownerBefore,0x20)=1;if(plan.mutate==2&&dialogCalls)at<void**>(ownerBefore,0x18)=alternate;if(plan.mutate==3&&dialogCalls)at<unsigned>(ownerBefore,0x24)=1;if(plan.mutate==4&&dialogCalls)at<unsigned>(ownerBefore,0x20)=3;need(!std::memcmp(ownerBefore,owner,sizeof(ownerBefore)));
 num(dialogCalls);num(selectCalls);num(wantedCount);num(wantedCapacity);num(allocAttempts);num(freeN);num(caught);finish();
}
void side(void*p,autotest::Capture&o,bool candidate){const Case&c=*(Case*)p;cap=&o;errors=0;autotest::g_arenaUsed=0;if(c.kind==0)detailSide(c,o,candidate);else if(c.kind==1)activeSide(c,o,candidate);else dialogSide(c,o,candidate);}
void a(void*p,autotest::Capture&o){side(p,o,false);}void b(void*p,autotest::Capture&o){side(p,o,true);}
bool pair(const tlhybrid_host*h,autotest::Coverage&cov,Case&c,unsigned&n){autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);++n;if(cov.observe(h,x,y)||!good(x.capture)||!good(y.capture)){h->log("query fixture kind=%u scenario=%u variant=%u fault=%u oracle=%u/%u\n",c.kind,c.s,c.v,c.fault,good(x.capture),good(y.capture));cov.report(h);return false;}return true;}
bool faultPair(const tlhybrid_host*h,Case&c,unsigned long address){autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);bool ok=x.reportValid&&y.reportValid&&!x.childStatus&&!y.childStatus&&!x.capture.issue&&!y.capture.issue&&x.capture.callStarted&&y.capture.callStarted&&!x.capture.callCompleted&&!y.capture.callCompleted&&x.capture.callTarget==address&&h->comparison_pair(x.capture.callTarget,y.capture.callTarget)&&good(x.capture)&&good(y.capture)&&x.capture.length==y.capture.length&&!std::memcmp(x.capture.data,y.capture.data,x.capture.length);if(!ok)h->log("query separate unwind kind=%u scenario=%u variant=%u fault=%u oracle=%u/%u\n",c.kind,c.s,c.v,c.fault,good(x.capture),good(y.capture));return ok;}
}
TL_TEST(questmanager_details_query){using namespace quest_details_dialogs;autotest::Coverage cov("questmanager_details_query",0xd265f0);unsigned n=0;for(unsigned s=0;s<16;++s)for(unsigned v=0;v<4;++v){Case c={0,s,v,0};if(!pair(host,cov,c,n))return 1;}cov.report(host);if(cov.completed!=n||n<20||cov.different||cov.missing)return 1;Case c={0,7,0,1};if(!faultPair(host,c,0xd265f0))return 1;host->log("details expected unwinds: 1, separate from completed coverage\n");return 0;}
TL_TEST(questmanager_active_query){using namespace quest_details_dialogs;autotest::Coverage cov("questmanager_active_query",0xd2d8e0);unsigned n=0;for(unsigned s=0;s<16;++s)for(unsigned v=0;v<24;++v){Case c={1,s,v,0};if(!pair(host,cov,c,n))return 1;}cov.report(host);return cov.completed!=n||n<20||cov.different||cov.missing;}
TL_TEST(questmanager_dialogs_query){using namespace quest_details_dialogs;autotest::Coverage cov("questmanager_dialogs_query",0xd31140);unsigned n=0;for(unsigned s=0;s<25;++s)for(unsigned v=0;v<3;++v){Case c={2,s,v,0};if(!pair(host,cov,c,n))return 1;}cov.report(host);if(cov.completed!=n||n<20||cov.different||cov.missing)return 1;
 const Case faults[]={{2,7,0,1},{2,2,0,1},{2,21,0,1},{2,19,0,1},{2,20,0,1},{2,9,0,2}};for(unsigned i=0;i<sizeof(faults)/sizeof(faults[0]);++i){Case c=faults[i];if(!faultPair(host,c,0xd31140))return 1;}host->log("dialogs expected unwinds: 6, separate from completed coverage\n");return 0;}
