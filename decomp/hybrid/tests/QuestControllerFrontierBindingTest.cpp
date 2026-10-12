// Independent four-method frontier: direct init and by-value binding oracles.
// Packet tu-dv6yuftr, original ELF 91b41ae9... . C++98. No acceptance by consumers.
#include <string>
#include <cstring>
#include <new>
#include "AutoTest.h"
#include "Detour.h"
#define QF_PAIR(N,A,S) TL_ORIGINAL(void,qfOld##N,A,S) extern "C" void qfNew##N A __asm__(S);
QF_PAIR(Init,(void*),"_ZN16CQuestController19initQuestControllerEv")
QF_PAIR(Bind,(void*,std::wstring),"_ZN16CQuestController19setUnitInteractWithESbIwSt11char_traitsIwESaIwEE")
QF_PAIR(Ctor,(void*,void*),"_ZN16CQuestControllerC1EP16CResourceManager")
TL_ORIGINAL(void,qfEditorCtor,(void*),"_ZN17CEditorBaseObjectC1Ev")
TL_ORIGINAL(void,qfEditorDtor,(void*),"_ZN17CEditorBaseObjectD1Ev")
TL_ORIGINAL(void,qfDtor,(void*),"_ZN16CQuestControllerD1Ev")
TL_ORIGINAL(void,qfCoreCtor,(void*),"_ZN10CRunicCoreC1Ev")
TL_ORIGINAL(void,qfCoreDtor,(void*),"_ZN10CRunicCoreD1Ev")
TL_ORIGINAL(void,qfQuestCtor,(void*,void*,void*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void,qfQuestDtor,(void*),"_ZN6CQuestD1Ev")
TL_ORIGINAL(void,qfProperty,(void*,const wchar_t*,unsigned),"_ZN26CQuestControllerDescriptor23Set_setUnitInteractWithEP17CEditorBaseObjectP14UNIONDATA16BITj")
TL_ORIGINAL(void,qfScene,(void*,void*),"_ZN26CQuestControllerDescriptor24descriptorSceneActivatedEP12CEditorScene")
TL_FUNCTION(qfInit,"_ZN16CQuestController19initQuestControllerEv")
TL_FUNCTION(qfBind,"_ZN16CQuestController19setUnitInteractWithESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qfManager,"_ZN13CQuestManager12getSingletonEv")
TL_FUNCTION(qfLookup,"_ZN13CQuestManager14getQuestByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qfUnits,"_ZN17CUnitResourceList12getSingletonEv")
TL_FUNCTION(qfGroup,"_ZN17CUnitResourceList24getDataGroupByObjectNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qfAdd,"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(qfRemove,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(qfListener,"_ZN6CQuest27addQuestControllerListernerEP16CQuestController")
TL_FUNCTION(qfUpdate,"_ZN6CLevel15addUpdateObjectEP12iLevelUpdate")
TL_FUNCTION(qfEditor,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(qfUI,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(qfGuid,"_ZN9UTILITIES16createUniqueGuidEv")
namespace qf {
typedef std::wstring Wide;
template<class T>T& at(void*p,unsigned n){return *reinterpret_cast<T*>((char*)p+n);}
struct Case {unsigned kind,mode,text,fault,consumer;};
struct Stop {unsigned site;Stop(unsigned s):site(s){}};
static const Case* c;static autotest::Capture* out;static void* owner;static void* q[3];static void* resource[2];static void* level[2];static void* manager;static void* group;static void* oldGroup;
static detour::Set *adds,*removes,*listeners;static unsigned errors,events[80],count,hits;static bool quiet;static Wide *argument,*witness;static unsigned lookupCalls,listenerCalls;
static void n(unsigned x){out->add(&x,4);}static void need(bool b,unsigned id){if(!b){++errors;n(0xf1000000u+id);}}
static void event(unsigned e){need(count<80,1);if(count<80)events[count++]=e;n(e);if(c->fault==e){++hits;throw Stop(e);}}
static unsigned id(void*p){return p==q[0]?1:p==q[1]?2:p==q[2]?3:p?99:0;}
static unsigned offset(){return c->kind?0x78:0x98;}
static unsigned realAdd(void*p,void*s){return reinterpret_cast<unsigned(*)(void*,void*)>(qfAdd_original)(p,s);}
static void realRemove(void*p,void*s,unsigned i){reinterpret_cast<void(*)(void*,void*,unsigned)>(qfRemove_original)(p,s,i);}
static unsigned add(void*p,void*s){if(!quiet&&s==(char*)owner+offset()){need(!at<void*>(s,0),2);event(40+id(p));}adds->restore();unsigned r=realAdd(p,s);TL_REDIRECT(*adds,qfAdd,&add);return r;}
static void remove(void*p,void*s,unsigned i){if(!quiet&&s==(char*)owner+offset()){need(at<void*>(s,0)==p&&at<unsigned>(s,8)==i,3);event(30+id(p));}removes->restore();realRemove(p,s,i);TL_REDIRECT(*removes,qfRemove,&remove);}
static void assign(void*p){void*s=(char*)owner+offset();quiet=true;if(at<void*>(s,0))remove(at<void*>(s,0),s,at<unsigned>(s,8));at<void*>(s,0)=0;if(p)at<unsigned>(s,8)=add(p,s);at<void*>(s,0)=p;quiet=false;}
static unsigned slots(void*p){void*l=at<void*>(p,8);if(!l)return 0;unsigned result=0;for(unsigned i=0;i<at<unsigned>(l,8);++i)if(at<void**>(l,0)[i]==(char*)owner+offset())++result;return result;}
static void* singleton(){need(at<bool>(owner,0xb0),4);event(10);return manager;}
static void* lookup(void*p,const Wide&s){need(p==manager&&&s==&at<Wide>(owner,0xa8)&&s==L"controller quest",5);event(20);++lookupCalls;
 if(c->mode==5)assign(q[1]);if(c->mode==6)assign(q[2]);return c->mode<2?0:c->mode==2?q[0]:q[1];}
static void listener(void*p,void*s){need(s==owner&&p==(c->mode==2?q[0]:q[1]),6);event(50+id(p));++listenerCalls;
 listeners->restore();reinterpret_cast<void(*)(void*,void*)>(qfListener_original)(p,s);TL_REDIRECT(*listeners,qfListener,&listener);
 if(c->mode==7||c->mode==8){at<bool>(owner,0xb0)=false;at<bool>(owner,0xb1)=c->mode==7;at<void*>(owner,0x68)=resource[1];}
 if(c->mode==10)assign(q[2]);
}
static void update(void*p,void*s){need(s==(char*)owner+0x60&&p==level[c->mode==7?1:0]&&at<bool>(owner,0xb0),7);event(60);}
static void* units(){need(at<Wide>(owner,0x90)==*argument,8);event(11);return manager;}
static void* lookupGroup(void*p,const Wide&s){need(p==manager&&s==*argument&&&s!=&at<Wide>(owner,0x90),9);*witness=s;event(21);++lookupCalls;
 if(c->mode==4||c->mode==5)at<Wide>(owner,0x90)=L"callback changed member";
 if(c->mode==5)assign(q[2]);return c->mode==3?0:group;}
static void* noUI(){return 0;}static unsigned long long guid(){return 0xabc123ULL;}
static bool editor(void*p){need(p==resource[0],10);n(70);return c->consumer==3;}
static Wide value(unsigned t){if(t==0)return Wide();if(t==1)return Wide(L"shared unit");if(t==2){Wide r(4097,L'Z');r[19]=L'\u041a';r[50]=0;return r;}return Wide(L"self derived unit");}
static int refs(const Wide&s){return *reinterpret_cast<const int*>((const char*)s.c_str()-8);}
static void setup(bool candidate){errors=count=hits=lookupCalls=listenerCalls=0;quiet=false;autotest::g_arenaUsed=0;owner=autotest::allocate(0xb8);manager=autotest::allocate(8);group=autotest::allocate(8);oldGroup=autotest::allocate(8);
 new((void*)0x151c128)Wide();new((void*)0x151ab48)Wide();new((void*)0x14f9fe8)Wide();new((void*)0x151d408)Wide();
 for(unsigned i=0;i<2;++i){resource[i]=autotest::allocate(0x70);level[i]=autotest::allocate(0xc0);at<void*>(resource[i],0x18)=level[i];}
 {detour::Set d;TL_REDIRECT(d,qfGuid,&guid);if(candidate)qfNewCtor(owner,resource[0]);else qfOldCtor(owner,resource[0]);}
 at<Wide>(owner,0xa8)=L"controller quest";at<Wide>(owner,0x90)=L"old unit";at<void*>(owner,0x70)=oldGroup;
 for(unsigned i=0;i<3;++i){q[i]=autotest::allocate(0x218);qfQuestCtor(q[i],0,0);for(unsigned j=0;j<=i;++j){void* dummy=autotest::allocate(16);at<void*>(dummy,0)=q[i];at<unsigned>(dummy,8)=realAdd(q[i],dummy);}}
 at<bool>(owner,0xb0)=false;at<bool>(owner,0xb1)=c->text!=0;
 bool initial=c->kind?c->mode!=1:c->mode==1||c->mode==2||c->mode==4||c->mode>=5;
 if(initial){void*s=(char*)owner+offset();at<unsigned>(s,8)=realAdd(q[0],s);at<void*>(s,0)=q[0];if(!c->kind)reinterpret_cast<void(*)(void*,void*)>(qfListener_original)(q[0],owner);}
 if(c->kind&&c->mode==0)at<void*>(owner,0x68)=0;
}
static void expectTrace(){unsigned expected[80],total=0;unsigned m=c->mode;
 if(!c->kind){unsigned repeats=m==9?2:1;for(unsigned r=0;r<repeats;++r){expected[total++]=10;expected[total++]=20;
 if(!r){if(m==1||m==4||m>=7)expected[total++]=31;else if(m==6)expected[total++]=33;if(m>=3&&m!=5)expected[total++]=42;}
 if(m>=2){expected[total++]=m==2?51:52;if(m==7||(c->text&&m!=8))expected[total++]=60;}}}
 else if(m!=0){expected[total++]=11;expected[total++]=21;if(m!=1)expected[total++]=m==5?33:31;}
 unsigned seen=total;if(c->fault){seen=0;while(seen<total&&expected[seen]!=c->fault)++seen;++seen;need(seen<=total,11);}need(count==seen,12);for(unsigned i=0;i<count&&i<seen;++i)need(events[i]==expected[i],100+i);
}
static void observe(){unsigned m=c->mode;expectTrace();need(hits==(c->fault?1u:0u),13);
 n(id(at<void*>(owner,offset())));n(at<unsigned>(owner,offset()+8));n(at<bool>(owner,0xb0));n(at<bool>(owner,0xb1));n(at<void*>(owner,0x68)==resource[1]);n(at<void*>(owner,0x70)==oldGroup?0:at<void*>(owner,0x70)==group?1:2);
 for(unsigned i=0;i<3;++i){n(slots(q[i]));n(at<unsigned>(q[i],0x1b8));}
 out->addText(at<Wide>(owner,0x90));
 if(!c->fault){if(!c->kind){need(at<void*>(owner,0x98)==(m<2?0:m==2?q[0]:m==10?q[2]:q[1]),14);need(at<bool>(owner,0xb0)==(m!=8),15);need(listenerCalls==(m<2?0:m==9?2:1),16);if(m<2)need(!listenerCalls,17);}
 else{need(at<void*>(owner,0x78)==(m==0?q[0]:0),18);need(at<void*>(owner,0x70)==(m==0?oldGroup:m==3?0:group),19);need(at<Wide>(owner,0x90)==(m==0?(c->text==3?*argument:Wide(L"old unit")):m>=4?Wide(L"callback changed member"):*argument),20);}}
 if(c->fault>=30&&c->fault<40)need(id(at<void*>(owner,offset()))==c->fault-30,21);
 if(c->fault>=40&&c->fault<50){need(!at<void*>(owner,offset()),22);need(at<unsigned>(owner,offset()+8)==1,23);}
}
static void side(void*p,autotest::Capture&o,bool candidate){c=(Case*)p;out=&o;setup(candidate);Wide input=value(c->text),kept;argument=&input;witness=&kept;
 if(c->kind&&c->text==3){at<Wide>(owner,0x90)=input;input=at<Wide>(owner,0x90);}Wide sourceWitness(input);const wchar_t* before=input.c_str();
 detour::Set a,r,l,d,route;adds=&a;removes=&r;listeners=&l;TL_REDIRECT(a,qfAdd,&add);TL_REDIRECT(r,qfRemove,&remove);TL_REDIRECT(l,qfListener,&listener);
 TL_REDIRECT(d,qfManager,&singleton);TL_REDIRECT(d,qfLookup,&lookup);TL_REDIRECT(d,qfUpdate,&update);TL_REDIRECT(d,qfUnits,&units);TL_REDIRECT(d,qfGroup,&lookupGroup);TL_REDIRECT(d,qfEditor,&editor);TL_REDIRECT(d,qfGuid,&guid);
 if(a.failed()||r.failed()||l.failed()||d.failed()){o.issue=autotest::Capture::InvalidReport;return;}
 bool caught=false;
 try{if(c->consumer&&c->kind){if(candidate)route.redirect(qfBind_original,qfBind_original,&qfNewBind);if(route.failed()){o.issue=autotest::Capture::InvalidReport;return;}if(!autotest::beginInvocation(o,&qfProperty))return;
   // Property is a NUL-terminated input API, so embedded NUL is not used here.
   qfProperty(c->consumer==4?0:owner,c->consumer==4?0:input.c_str(),~0u);o.callCompleted=1;}
 else if(c->consumer){if(candidate)route.redirect(qfInit_original,qfInit_original,&qfNewInit);if(route.failed()){o.issue=autotest::Capture::InvalidReport;return;}void* wrong=autotest::allocate(0x58);qfEditorCtor(wrong);void*desc=autotest::allocate(0x100);void*scene=autotest::allocate(0x80);void** entries=(void**)autotest::allocate(32);entries[0]=0;entries[1]=owner;entries[2]=wrong;entries[3]=owner;at<void*>(desc,0xe0)=entries;at<unsigned>(desc,0xe8)=at<unsigned>(desc,0xec)=4;at<void*>(scene,0x68)=resource[0];if(!autotest::beginInvocation(o,&qfScene))return;qfScene(desc,scene);qfEditorDtor(wrong);o.callCompleted=1;}
 else if(c->kind){typedef void(*Fn)(void*,Wide);Fn f=candidate?&qfNewBind:&qfOldBind;if(!autotest::beginInvocation(o,f))return;f(owner,input);o.callCompleted=1;}
 else{typedef void(*Fn)(void*);Fn f=candidate?&qfNewInit:&qfOldInit;if(!autotest::beginInvocation(o,f))return;f(owner);if(c->mode==9)f(owner);o.callCompleted=1;}}
 catch(const Stop&s){caught=true;need(s.site==c->fault,24);}need(caught==(c->fault!=0),25);
 route.restore();if(c->consumer==4){need(!count&&!lookupCalls,29);}else if(c->consumer&&!c->kind&&c->consumer==3){need(!count&&!lookupCalls&&!listenerCalls&&!at<bool>(owner,0xb0),26);}else observe();
 need(input==sourceWitness&&input.c_str()==before,27);
 if(c->kind&&!kept.empty()){
  // Count every surviving COW owner explicitly: caller, independent witness,
  // member and lookup witness. The by-value temporary MUST already be gone,
  // both after success and original descriptor EH cleanup.
  int owners=1;if(input.c_str()==kept.c_str())++owners;if(sourceWitness.c_str()==kept.c_str())++owners;if(at<Wide>(owner,0x90).c_str()==kept.c_str())++owners;need(refs(kept)==owners-1,28);n(refs(kept));
 }
 a.restore();r.restore();l.restore();d.restore();
 {detour::Set cleanup;TL_REDIRECT(cleanup,qfUI,&noUI);qfDtor(owner);}for(unsigned i=0;i<3;++i)qfQuestDtor(q[i]);
 n(0x51464942);n(errors);
}
static void oldSide(void*p,autotest::Capture&o){side(p,o,false);}static void newSide(void*p,autotest::Capture&o){side(p,o,true);}
static bool good(const autotest::Outcome&o){unsigned x[2]={0,1};if(o.capture.length>=8)std::memcpy(x,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&x[0]==0x51464942&&!x[1];}
static bool pair(const tlhybrid_host*host,autotest::Coverage&cv,Case&c){autotest::Outcome a,b;autotest::runChild(oldSide,&c,a);autotest::runChild(newSide,&c,b);bool ok=good(a)&&good(b)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
 if(!c.fault&&!c.consumer){if(cv.observe(host,a,b))ok=false;}else{ok=ok&&a.capture.callStarted&&b.capture.callStarted&&a.capture.callCompleted==!c.fault&&b.capture.callCompleted==!c.fault;if(c.consumer)ok=ok&&a.capture.callTarget==(c.kind?0xdbece0:0xdba140)&&a.capture.callTarget==b.capture.callTarget;else ok=ok&&a.capture.callTarget==cv.original&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget);}
 if(!ok){host->log(" init/binding kind=%u mode=%u text=%u fault=%u consumer=%u status=%d/%d good=%u/%u\n",c.kind,c.mode,c.text,c.fault,c.consumer,a.childStatus,b.childStatus,good(a),good(b));for(unsigned s=0;s<2;++s){const autotest::Capture&z=s?b.capture:a.capture;for(size_t i=0;i+4<=z.length;i+=4){unsigned v;std::memcpy(&v,z.data+i,4);if((v&0xffff0000u)==0xf1000000u)host->log(" side %u oracle %u\n",s,v-0xf1000000u);}}}return ok;}
}
TL_TEST(questcontroller_init_frontier){using namespace qf;autotest::Coverage cv("questcontroller_init_frontier",0xdee380);for(unsigned m=0;m<11;++m)for(unsigned t=0;t<2;++t){Case c={0,m,t,0,0};if(!pair(host,cv,c)){cv.report(host);return 1;}}cv.report(host);return cv.different||cv.missing;}
TL_TEST(questcontroller_binding_frontier){using namespace qf;autotest::Coverage cv("questcontroller_binding_frontier",0xdee6b0);for(unsigned m=0;m<6;++m)for(unsigned t=0;t<4;++t){Case c={1,m,t,0,0};if(!pair(host,cv,c)){cv.report(host);return 1;}}cv.report(host);return cv.different||cv.missing;}
TL_TEST(questcontroller_init_binding_unwind){using namespace qf;autotest::Coverage cv("expected unwind, excluded",0xdee380);unsigned faults[]={10,20,31,42,52,60};for(unsigned i=0;i<6;++i){Case c={0,4,1,faults[i],0};if(!pair(host,cv,c))return 1;}cv.original=0xdee6b0;unsigned binding[]={11,21,31};for(unsigned i=0;i<3;++i)for(unsigned t=1;t<4;++t){Case c={1,2,t,binding[i],0};if(!pair(host,cv,c))return 1;}host->log(" init/binding supported expected unwinds; no completed-call credit\n");return 0;}
TL_TEST(questcontroller_property_consumer){using namespace qf;if(!host->comparison_pair(0xdee6b0,(uint64_t)&qfNewBind))return 1;autotest::Coverage cv("property consumer only",0xdee6b0);Case nullCase={1,2,1,0,4};if(!pair(host,cv,nullCase))return 1;for(unsigned m=0;m<6;++m)for(unsigned t=0;t<2;++t){Case c={1,m,t,0,1};if(!pair(host,cv,c))return 1;}unsigned faults[]={11,21,31};for(unsigned i=0;i<3;++i){Case c={1,2,1,faults[i],1};if(!pair(host,cv,c))return 1;}return 0;}
TL_TEST(questcontroller_scene_consumer){using namespace qf;if(!host->comparison_pair(0xdee380,(uint64_t)&qfNewInit))return 1;autotest::Coverage cv("scene consumer only",0xdee380);for(unsigned t=0;t<2;++t){Case c={0,9,t,0,2};if(!pair(host,cv,c))return 1;Case e={0,9,t,0,3};if(!pair(host,cv,e))return 1;}return 0;}
