// Original ELF 91b41ae9... oracle. C++98; no controller header dependency.
#include <string>
#include <cstring>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#define QC_PAIR(ret,name,args,sym) TL_ORIGINAL(ret,name##Old,args,sym) extern "C" ret name##New args __asm__(sym);
QC_PAIR(void,qcbAccept,(void*,bool),"_ZN16CQuestController16setQuestAcceptedEb")
QC_PAIR(void,qcbComplete,(void*,bool),"_ZN16CQuestController21questHasBeenCompletedEb")
QC_PAIR(void,qcbMenu,(void*,void*,int,int),"_ZN16CQuestController16menuEventOccuredEPv10EMENU_TYPE11EMENU_EVENT")
QC_PAIR(long long,qcbUpdate,(void*,float,void*,const float*),"_ZN16CQuestController17updateLevelObjectEfPN4Ogre6CameraERKNS0_7Vector3E")
TL_FUNCTION(qcbManager,"_ZN13CQuestManager12getSingletonEv")
TL_FUNCTION(qcbGive,"_ZN13CQuestManager9giveQuestEP6CQuestP9CBaseUnitb")
TL_FUNCTION(qcbRemove,"_ZN13CQuestManager11removeQuestEP6CQuestb")
TL_FUNCTION(qcbAddUpdate,"_ZN6CLevel15addUpdateObjectEP12iLevelUpdate")
TL_FUNCTION(qcbActive,"_ZN13CQuestManager16getQuestIsActiveERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qcbDone,"_ZN13CQuestManager16getQuestCompleteERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qcbUI,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(qcbRemoveMenu,"_ZN7CGameUI18removeMenuListenerE10EMENU_TYPEP13iMenuListener")
// Hybrid data symbols intentionally resolve to original storage. Fixture-owned
// secondary tables select actual linked compiler thunks; no emitted candidate
// vtable claim is made. Metadata agrees with original ELF and compiler assembly.
extern "C" void qcbMenuThunk(void*,void*,int,int) __asm__("_ZThn88_N16CQuestController16menuEventOccuredEPv10EMENU_TYPE11EMENU_EVENT");
extern "C" long long qcbUpdateThunk(void*,float,void*,const float*) __asm__("_ZThn96_N16CQuestController17updateLevelObjectEfPN4Ogre6CameraERKNS0_7Vector3E");
extern "C" void qcbMenuD1(void*) __asm__("_ZThn88_N16CQuestControllerD1Ev");
extern "C" void qcbMenuD0(void*) __asm__("_ZThn88_N16CQuestControllerD0Ev");
extern "C" void qcbUpdateD1(void*) __asm__("_ZThn96_N16CQuestControllerD1Ev");
extern "C" void qcbUpdateD0(void*) __asm__("_ZThn96_N16CQuestControllerD0Ev");
static void* qcbFixtureMenuTable[]={(void*)-88,(void*)0xffde00,(void*)&qcbMenuD1,(void*)&qcbMenuD0,(void*)&qcbMenuThunk};
static void* qcbFixtureUpdateTable[]={(void*)-96,(void*)0xffde00,(void*)&qcbUpdateD1,(void*)&qcbUpdateD0,(void*)&qcbUpdateThunk};
static void* qcbMenuAddressPoint(bool candidate){return candidate?(void*)(qcbFixtureMenuTable+2):(void*)0xffdd90;}
static void* qcbUpdateAddressPoint(bool candidate){return candidate?(void*)(qcbFixtureUpdateTable+2):(void*)0xffddb8;}
namespace qcb {
template<class T>T& at(void*p,unsigned o){return *reinterpret_cast<T*>((char*)p+o);}
struct List {void**data;unsigned count,capacity,grow,pad;};
typedef char ABI[(sizeof(std::wstring)==8&&sizeof(List)==24)?1:-1];
struct Case {unsigned kind,mode,variant,input;};
struct Entry {unsigned code,a,b;};
const Case* cs; autotest::Capture* cap; unsigned errors,used,total,managerCalls,nested;
Entry expected[40]; void *owner,*quest[2],*dialog[2],*resource[2],*client[2],*player[2],*level[2],*manager[2],*ui;
void* primary[10];void* alternate[10];void* playerTable[10];
typedef long long(*Update)(void*,float,void*,const float*);Update update;float position[3];
void need(bool b){if(!b)++errors;}
void number(unsigned x){cap->add(&x,4);}
void want(unsigned c,unsigned a=0,unsigned b=0){need(total<40);if(total<40){expected[total].code=c;expected[total].a=a;expected[total++].b=b;}}
void emit(unsigned c,unsigned a=0,unsigned b=0){number(c);number(a);number(b);need(used<total);if(used<total)need(expected[used].code==c&&expected[used].a==a&&expected[used].b==b);++used;}
void* raw(unsigned n){return autotest::allocate(n);}
unsigned incomingEvent(){static const unsigned events[]={3,4,5,7};return events[cs->input%4];}
const wchar_t* initialName(){return cs->input?L"":L"first";}
unsigned initialEvent(){return cs->kind==3&&cs->input?3:5;}
void* getManager(){unsigned i=managerCalls++;emit(1,i);return manager[(cs->kind==3&&cs->mode>=8&&i)?1:0];}
long long give(void*m,void*q,void*u,bool b){need(m==manager[0]&&q==quest[0]&&!u&&b);emit(2);if(cs->mode==5)at<void*>(owner,0x98)=quest[1];return 0;}
long long remove(void*m,void*q,bool b){need(m==manager[0]&&q==quest[0]&&!b);emit(3);at<void*>(owner,0x98)=quest[1];return 0;}
void enabled(void*p,bool b){emit(5,p==player[0]?0:p==player[1]?1:99,b);}
void addUpdate(void*l,void*u){need(l==level[0]&&u==(char*)owner+0x60);need(at<int>(owner,0xb4)==(int)incomingEvent());emit(4);
 if(cs->mode>=5){at<void*>(owner,0x68)=resource[1];at<bool>(owner,0xb2)=true;at<bool>(owner,0xb3)=cs->mode!=6;}}
void* getUI(){emit(8);return ui;}
void removeMenu(void*p,int t,void*l){need(p==ui&&t==0&&l==(char*)owner+0x58);emit(9);}
unsigned long long active(void*m,const std::wstring&s){need(m==manager[0]&&&s==&at<std::wstring>(owner,0xa8)&&s==initialName());need(!at<bool>(owner,0xb0));emit(6);return 0x100ULL|((cs->mode&1)?1:0);}
unsigned long long done(void*m,const std::wstring&s){need(m==manager[cs->mode>=8?1:0]&&&s==&at<std::wstring>(owner,0xa8)&&s==(cs->mode>=8?L"second":initialName()));emit(7);return 0x100ULL|((cs->mode&2)?1:0);}
void broadcastAlt(void*p,int e){need(p==owner);emit(11,e);}
void broadcast(void*p,int e){need(p==owner);emit(10,e);
 if(cs->kind==3&&cs->mode>=8&&cs->mode<=11&&(e==98||e==99)){
  at<std::wstring>(owner,0xa8)=L"second";
  if(cs->mode==10&&!nested){nested=1;need(update(owner,17.0f,0,position)==0);nested=0;}
 }
 if(cs->kind==3&&cs->mode>=16&&e==92){at<int>(owner,0xb4)=cs->mode==16?4:3;at<void*>(owner,0)=alternate;}
}
void setup(){autotest::g_arenaUsed=0;errors=used=total=managerCalls=nested=0;owner=raw(0xb8);ui=raw(8);
 for(unsigned i=0;i<2;++i){quest[i]=raw(0x220);dialog[i]=raw(0x80);resource[i]=raw(0x50);client[i]=raw(0x90);player[i]=raw(0x90);level[i]=raw(8);manager[i]=raw(8);
  List&list=at<List>(quest[i],0x60);list.data=(void**)raw(8);list.data[0]=dialog[i];list.count=list.capacity=1;list.grow=1;
  at<void*>(resource[i],0x18)=level[i];at<void*>(resource[i],0x28)=raw(8);at<void*>(at<void*>(resource[i],0x28),0)=client[i];at<unsigned>(resource[i],0x30)=1;at<void*>(client[i],0x58)=player[i];at<void*>(player[i],0)=playerTable;
 }
 std::memset(primary,0,sizeof(primary));std::memset(alternate,0,sizeof(alternate));std::memset(playerTable,0,sizeof(playerTable));
 primary[6]=(void*)&broadcast;alternate[6]=(void*)&broadcastAlt;playerTable[8]=(void*)&enabled;at<void*>(owner,0)=primary;
 at<void*>(owner,0x68)=resource[0];at<void*>(owner,0x98)=quest[0];at<int>(owner,0xa0)=-1;at<int>(owner,0xb4)=initialEvent();
 new((char*)owner+0xa8)std::wstring(initialName());
}
void plan(){unsigned m=cs->mode;
 if(cs->kind==0){at<unsigned char>(quest[0],0x26)=m==1||m==3; if(m==0)at<void*>(owner,0x98)=0;if(m>=3){want(1);want(m==3?3:2);}return;}
 if(cs->kind==1){want(10,m?100:101);return;}
 if(cs->kind==2){if(m==0){at<void*>(owner,0x68)=0;return;}if(m==1){at<void*>(client[0],0x58)=0;return;}
  at<bool>(owner,0xb3)=m==3||m==4||m==6;at<bool>(owner,0xb2)=m==4;want(4);if(m==3||m==4)want(5,0,m==4);if(m==5)want(5,1,1);return;}
 if(m<12){at<bool>(owner,0xb0)=true;at<bool>(owner,0xb1)=true;want(1,0);want(6);want(10,(m&1)?98:99);
  if(m==10){want(10,92);if(cs->input)want(10,93);want(8);want(9);}want(1,1);want(7);want(10,(m&2)?100:101);return;}
 at<bool>(owner,0xb0)=m==13;at<bool>(owner,0xb1)=m==14;at<int>(owner,0xb4)=m==12?3:m==13?4:m==14?5:m==16?3:27;
 want(10,92);if(m==12||m==13)want(10,m==12?93:94);if(m>=16)want(11,m==16?94:93);want(8);want(9);
}
void side(void*p,autotest::Capture&o,bool candidate){cs=(Case*)p;cap=&o;setup();plan();
 {detour::Set d;TL_REDIRECT(d,qcbManager,&getManager);TL_REDIRECT(d,qcbGive,&give);TL_REDIRECT(d,qcbRemove,&remove);TL_REDIRECT(d,qcbAddUpdate,&addUpdate);TL_REDIRECT(d,qcbActive,&active);TL_REDIRECT(d,qcbDone,&done);TL_REDIRECT(d,qcbUI,&getUI);TL_REDIRECT(d,qcbRemoveMenu,&removeMenu);
  if(d.failed()){o.issue=autotest::Capture::InvalidReport;return;}
  if(cs->kind==0){typedef void(*Fn)(void*,bool);Fn f=candidate?&qcbAcceptNew:&qcbAcceptOld;if(!autotest::beginInvocation(o,f))return;f(owner,cs->mode!=2&&cs->mode!=3);}
  if(cs->kind==1){typedef void(*Fn)(void*,bool);Fn f=candidate?&qcbCompleteNew:&qcbCompleteOld;if(!autotest::beginInvocation(o,f))return;f(owner,cs->mode!=0);}
  if(cs->kind==2){typedef void(*Fn)(void*,void*,int,int);Fn f=candidate?&qcbMenuNew:&qcbMenuOld;void*self=owner;
   if(cs->variant){at<void*>(owner,0x58)=qcbMenuAddressPoint(candidate);self=(char*)owner+0x58;f=reinterpret_cast<Fn>(at<void**>(self,0)[2]);}
   if(!autotest::beginInvocation(o,f))return;f(self,cs->input%2?(void*)0x123:0,cs->mode==0?9:0,incomingEvent());}
  if(cs->kind==3){update=candidate?&qcbUpdateNew:&qcbUpdateOld;Update f=update;void*self=owner;
   if(cs->variant){at<void*>(owner,0x60)=qcbUpdateAddressPoint(candidate);self=(char*)owner+0x60;f=reinterpret_cast<Update>(at<void**>(self,0)[2]);}
   if(!autotest::beginInvocation(o,f))return;position[0]=cs->input?17.0f:0.0f;position[1]=cs->input?-12.0f:0.0f;position[2]=cs->input?0.25f:0.0f;need(f(self,cs->input?-5.25f:3.5f,cs->input?(void*)0x321:0,position)==0);}
  o.callCompleted=1;
 }
 if(cs->kind==0){unsigned m=cs->mode;need(at<unsigned char>(quest[0],0x26)==(m==1||m==3));need(!at<unsigned char>(quest[1],0x26));need(at<unsigned char>(dialog[0],0x76)==(m==4));need(at<unsigned char>(dialog[1],0x76)==(m==5));}
 if(cs->kind==2)need(at<int>(owner,0xb4)==(cs->mode<2?5:(int)incomingEvent()));
 if(cs->kind==3){need(at<bool>(owner,0xb0)==(cs->mode==13));need(at<int>(owner,0xb4)==(cs->mode<12?(int)initialEvent():cs->mode==12?3:cs->mode==13?4:cs->mode==14?5:cs->mode==16?4:cs->mode==17?3:27));}
 need(used==total);number(used);number(0x51434231);number(errors);
 at<std::wstring>(owner,0xa8).~basic_string();
}
void oldSide(void*p,autotest::Capture&o){side(p,o,false);}void newSide(void*p,autotest::Capture&o){side(p,o,true);}
bool good(const autotest::Outcome&o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0x51434231&&!tail[1];}
int run(const tlhybrid_host*host,unsigned kind,unsigned variant,unsigned count,const char*name,unsigned address){autotest::Coverage cov(name,address);
 for(unsigned m=0;m<count;++m)for(unsigned input=0;input<(kind==2?4u:kind==3?2u:1u);++input){if(kind==3&&m>=4&&m<8)continue;Case c={kind,m,variant,input};autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);bool ok=good(a)&&good(b);if(cov.observe(host,a,b))ok=false;
  if(!ok){host->log(" controller behavior kind=%u mode=%u virtual=%u input=%u good=%u/%u status=%d/%d\n",kind,m,variant,input,good(a),good(b),a.childStatus,b.childStatus);cov.report(host);return 1;}}
 cov.report(host);return cov.missing||cov.different;
}
}
TL_TEST(questcontroller_accepted){return qcb::run(host,0,0,6,"questcontroller_accepted",0xde6c00);}
TL_TEST(questcontroller_completed){return qcb::run(host,1,0,2,"questcontroller_completed",0xde6af0);}
TL_TEST(questcontroller_menu){return qcb::run(host,2,0,7,"questcontroller_menu",0xde6cc0);}
TL_TEST(questcontroller_update){return qcb::run(host,3,0,18,"questcontroller_update",0xde6ec0);}
TL_TEST(questcontroller_menu_virtual){return qcb::run(host,2,1,7,"questcontroller_menu_virtual",0xde6cb0);}
TL_TEST(questcontroller_update_virtual){return qcb::run(host,3,1,18,"questcontroller_update_virtual",0xde6eb0);}

// Real registration, dispatch and deferred removal across original consumers.
TL_ORIGINAL(void,qcbOldUIAdd,(void*,int,void*),"_ZN7CGameUI15addMenuListenerE10EMENU_TYPEP13iMenuListener")
TL_ORIGINAL(void,qcbOldUIRemove,(void*,int,void*),"_ZN7CGameUI18removeMenuListenerE10EMENU_TYPEP13iMenuListener")
TL_ORIGINAL(void,qcbOldLevelAdd,(void*,void*),"_ZN6CLevel15addUpdateObjectEP12iLevelUpdate")
TL_ORIGINAL(void,qcbOldMenuBroadcast,(void*,int,int),"_ZN13CDropdownMenu14broadcastEventE10EMENU_TYPE11EMENU_EVENT")
TL_ORIGINAL(void,qcbOldLevelTick,(void*,void*,const float*,float),"_ZN6CLevel24updateLevelUpdateObjectsEPN4Ogre6CameraERKNS0_7Vector3Ef")
// Original CQuestDialogMenu primary address point, ELF vtable ff0ac0+10.
namespace qcb {
void consumerSide(void*p,autotest::Capture&o,bool candidate){cs=(Case*)p;cap=&o;setup();
 ui=raw(0x548);level[0]=raw(0xc0);at<void*>(resource[0],0x18)=level[0];void*menu=raw(0xc0);at<void*>(ui,0x538)=menu;at<void*>(menu,0)=(void*)0xff0ad0;
 List&listeners=at<List>(menu,0x90);listeners.data=new void*[4];std::memset(listeners.data,0,32);listeners.capacity=4;listeners.grow=4;
 List&pending=at<List>(menu,0xa8);pending.grow=4;
 List&updates=at<List>(level[0],0xa8);updates.data=(void**)raw(32);updates.capacity=updates.grow=4;
 at<void*>(owner,0x58)=qcbMenuAddressPoint(candidate);at<void*>(owner,0x60)=qcbUpdateAddressPoint(candidate);
 at<bool>(owner,0xb3)=cs->mode!=0;at<bool>(owner,0xb2)=cs->mode==2;
 if(cs->mode)want(5,0,cs->mode==2);want(10,92);if(incomingEvent()==3||incomingEvent()==4)want(10,incomingEvent()==3?93:94);want(8);
 {detour::Set d;TL_REDIRECT(d,qcbUI,&getUI);
  // Keep these consumer boundaries original on both sides. Do not patch an
  // original entry to itself: only a distinct linked body needs redirection.
  if(qcbAddUpdate_linked!=qcbAddUpdate_original)d.redirect(qcbAddUpdate_linked,qcbAddUpdate_linked,&qcbOldLevelAdd);
  if(qcbRemoveMenu_linked!=qcbRemoveMenu_original)d.redirect(qcbRemoveMenu_linked,qcbRemoveMenu_linked,&qcbOldUIRemove);
  if(d.failed()){o.issue=autotest::Capture::InvalidReport;delete[] listeners.data;return;}
  qcbOldUIAdd(ui,0,(char*)owner+0x58);qcbOldUIAdd(ui,0,(char*)owner+0x58);
  need(listeners.count==1&&listeners.data[0]==(char*)owner+0x58);
  if(!autotest::beginInvocation(o,&qcbOldMenuBroadcast)){delete[] listeners.data;return;}
  qcbOldMenuBroadcast(menu,0,incomingEvent());
  need(at<int>(owner,0xb4)==(int)incomingEvent());need(updates.count==1&&updates.data[0]==(char*)owner+0x60);
  qcbOldLevelTick(level[0],0,position,0.5f);
  // A zero result removes the update entry; menu removal is deferred until
  // the NEXT real dropdown broadcast, which must not call the listener again.
  need(updates.count==0);need(listeners.count==1);need(pending.count==1&&pending.data[0]==(char*)owner+0x58);
  qcbOldMenuBroadcast(menu,0,7);need(!listeners.count&&!pending.count&&!pending.capacity&&!pending.data);need(!updates.count);
  o.callCompleted=1;
 }
 need(used==total);number(used);number(0x51434231);number(errors);delete[] listeners.data;at<std::wstring>(owner,0xa8).~basic_string();
}
void consumerOld(void*p,autotest::Capture&o){consumerSide(p,o,false);}void consumerNew(void*p,autotest::Capture&o){consumerSide(p,o,true);}
}
TL_TEST(questcontroller_real_menu_level_consumer){using namespace qcb;
 // Both sides enter original consumer code; acceptance comes from direct
 // controller tests above. Verify the consumer reaches replacement thunks.
 if(!host->comparison_pair(0xde6cb0,(uint64_t)at<void*>(qcbMenuAddressPoint(true),0x10))||!host->comparison_pair(0xde6eb0,(uint64_t)at<void*>(qcbUpdateAddressPoint(true),0x10)))return 1;
 for(unsigned mode=0;mode<3;++mode)for(unsigned input=0;input<4;++input){Case c={4,mode,0,input};autotest::Outcome a,b;autotest::runChild(consumerOld,&c,a);autotest::runChild(consumerNew,&c,b);
  bool ok=good(a)&&good(b)&&a.capture.callStarted&&b.capture.callStarted&&a.capture.callCompleted&&b.capture.callCompleted&&a.capture.callTarget==0xb102d0&&b.capture.callTarget==0xb102d0&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
  if(!ok){host->log(" controller real menu/level consumer mode=%u input=%u good=%u/%u status=%d/%d\n",mode,input,good(a),good(b),a.childStatus,b.childStatus);return 1;}}
 host->log(" controller real menu/level consumer: 12 registration/dispatch/deferred-removal comparisons; not counted as direct method coverage\n");return 0;
}
