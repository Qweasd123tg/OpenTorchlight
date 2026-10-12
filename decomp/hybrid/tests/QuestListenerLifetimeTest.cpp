// Independent listener oracle, fresh typed packets tu-eonu5gww d14860/d14b30.
// B/C parser/reset/persistence remain original-only, unaccepted boundaries.
// Expected allocation/registration unwinds are not completed-call acceptance.
#include <cstring>
#include <string>
#include <new>
#include "QuestController.h"
#include "SafePointer.h"
#include "TArrayList.h"
#include "AutoTest.h"
#include "Detour.h"
#define QL_PAIR(N,A,S) TL_ORIGINAL(void,qlOld##N,A,S) extern "C" void qlNew##N A __asm__(S);
QL_PAIR(Add,(void*,void*),"_ZN6CQuest27addQuestControllerListernerEP16CQuestController")
QL_PAIR(Remove,(void*,void*),"_ZN6CQuest30removeQuestControllerListernerEP16CQuestController")
QL_PAIR(QuestCtor,(void*,void*,void*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
QL_PAIR(QuestDtor,(void*),"_ZN6CQuestD1Ev")
QL_PAIR(ControllerInit,(void*),"_ZN16CQuestController19initQuestControllerEv")
QL_PAIR(ControllerDtor,(void*),"_ZN16CQuestControllerD1Ev")
#undef QL_PAIR
TL_ORIGINAL(void,qlDialogCtor,(void*,void*),"_ZN12CQuestDialogC1EP6CQuest")
TL_ORIGINAL(void,qlDialogD1,(void*),"_ZN12CQuestDialogD1Ev")
TL_ORIGINAL(void,qlDialogD0,(void*),"_ZN12CQuestDialogD0Ev")
TL_FUNCTION(qlDialogComplete,"_ZN12CQuestDialogD1Ev")
TL_FUNCTION(qlDialogDelete,"_ZN12CQuestDialogD0Ev")
TL_ORIGINAL(void,qlControllerCtor,(void*,void*),"_ZN16CQuestControllerC1EP16CResourceManager")
TL_ORIGINAL(unsigned,qlSafeAdd,(void*,void*),"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_ORIGINAL(void,qlSafeRemove,(void*,void*,unsigned),"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(qlAddRoute,"_ZN6CQuest27addQuestControllerListernerEP16CQuestController")
TL_FUNCTION(qlRemoveRoute,"_ZN6CQuest30removeQuestControllerListernerEP16CQuestController")
TL_FUNCTION(qlRegister,"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_FUNCTION(qlUnregister,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(qlUI,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(qlGuid,"_ZN9UTILITIES16createUniqueGuidEv")
TL_FUNCTION(qlManager,"_ZN13CQuestManager12getSingletonEv")
TL_FUNCTION(qlLookup,"_ZN13CQuestManager14getQuestByNameERKSbIwSt11char_traitsIwESaIwEE")
extern "C" char qlAlloc[] __asm__("_ZN4Ogre12NedAllocImpl10allocBytesEmPKciS2_");
extern "C" char qlFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
extern "C" char qlArrayAlloc[] __asm__("_Znam");
extern "C" char qlArrayFree[] __asm__("_ZdaPv");
namespace ql {
typedef std::wstring Wide;typedef TSafePointer<CQuestController> Weak;
template<class T>T& at(void*p,unsigned n){return *reinterpret_cast<T*>((char*)p+n);}
struct Case {unsigned remove,shape,grow,fault,integration;};
struct Stop {unsigned site;explicit Stop(unsigned s):site(s){}};
static const Case* c;static autotest::Capture* out;static void* quest;static void* controllers[6];static bool alive[6];
static void* nodes[20];static unsigned nodeCount,freed[20],errors,allocations,registrations,unregistrations,arrayAllocations,arrayFrees,hits;
static unsigned seedCount,expected[20],expectedCount,expectedFree[20],initialCapacity,expectedCapacity;
static void* oldArray;static unsigned initialTarget[20];static bool active,inRegistration;static unsigned requested;
static detour::Set *allocPatch,*freePatch,*arrayPatch,*arrayFreePatch,*registerPatch,*unregisterPatch;
static void n(unsigned x){out->add(&x,4);}static void need(bool x,unsigned id){if(!x){++errors;n(0xf1000000u+id);}}
static unsigned nodeId(void*p){for(unsigned i=nodeCount;i>0;--i)if(nodes[i-1]==p)return i;return 0;}
static unsigned targetId(void*p){for(unsigned i=0;i<6;++i)if(controllers[i]==p)return i+1;return p?99:0;}
static void* target(unsigned i){return i?controllers[i-1]:0;}
static unsigned registrySlots(void* core,void* weak){void*l=at<void*>(core,8);unsigned count=0;if(l)for(unsigned i=0;i<at<unsigned>(l,8);++i)if(at<void**>(l,0)[i]==weak)++count;return count;}
static void checkRegistry(void*core){void*l=at<void*>(core,8);if(l)for(unsigned i=0;i<at<unsigned>(l,8);++i){void*w=at<void**>(l,0)[i];need(w&&at<void*>(w,0)==core&&at<unsigned>(w,8)==i,1);}}
static void* noUI(){return 0;}static unsigned long long guid(){return 0x514c123456ULL;}
static void* manager(){return quest;}static void* lookup(void*p,const Wide&){need(p==quest,2);return quest;}
static void* allocate(size_t size,const char*file,int line,const char*function){
 if(active&&inRegistration&&size==24&&c->fault==5){++hits;throw Stop(5);}
 if(active&&!inRegistration&&size==16){++allocations;n(100);if(c->fault==1){++hits;throw Stop(1);}}
 allocPatch->restore();void*p=reinterpret_cast<void*(*)(size_t,const char*,int,const char*)>(qlAlloc)(size,file,line,function);allocPatch->redirect(qlAlloc,qlAlloc,&allocate);
 if(active&&!inRegistration&&size==16){need(nodeCount<20,3);nodes[nodeCount++]=p;}return p;
}
static void release(void*p){unsigned id=nodeId(p);if(active&&id){++freed[id-1];n(200+id);need(freed[id-1]==1,4);
 // Raw-construction failure has never published target/index. Every ordinary
 // wrapper destruction clears both before the allocator sees the allocation.
 need(!at<void*>(p,0)&&at<unsigned>(p,8)==~0u,5);}
 freePatch->restore();reinterpret_cast<void(*)(void*)>(qlFree)(p);freePatch->redirect(qlFree,qlFree,&release);
}
static unsigned registerWeak(void*core,void*w){bool relevant=active&&nodeId(w);if(relevant){++registrations;n(300+targetId(core));need(!at<void*>(w,0)&&at<unsigned>(w,8)==~0u,6);if(c->fault==2){++hits;throw Stop(2);}}
 registerPatch->restore();bool previous=inRegistration;inRegistration=true;unsigned r=qlSafeAdd(core,w);inRegistration=previous;TL_REDIRECT(*registerPatch,qlRegister,&registerWeak);return r;
}
static void unregisterWeak(void*core,void*w,unsigned index){if(active&&nodeId(w)){++unregistrations;n(400+nodeId(w));need(at<void*>(w,0)==core&&at<unsigned>(w,8)==index&&registrySlots(core,w)==1,7);}
 unregisterPatch->restore();qlSafeRemove(core,w,index);TL_REDIRECT(*unregisterPatch,qlUnregister,&unregisterWeak);
}
static void* allocateArray(size_t size){if(active&&inRegistration&&c->fault==6){++hits;throw Stop(6);}
 if(active&&!inRegistration){++arrayAllocations;n(500+unsigned(size));if(c->fault==3||c->fault==4){++hits;throw Stop(c->fault);}}
 arrayPatch->restore();void*p=reinterpret_cast<void*(*)(size_t)>(qlArrayAlloc)(size);arrayPatch->redirect(qlArrayAlloc,qlArrayAlloc,&allocateArray);return p;
}
static void releaseArray(void*p){if(active&&p==oldArray){++arrayFrees;n(600);}arrayFreePatch->restore();reinterpret_cast<void(*)(void*)>(qlArrayFree)(p);arrayFreePatch->redirect(qlArrayFree,qlArrayFree,&releaseArray);}
static void makeNode(unsigned id){void*p=reinterpret_cast<void*(*)(size_t,const char*,int,const char*)>(qlAlloc)(16,0,0,0);new(p)Weak();if(id){at<unsigned>(p,8)=qlSafeAdd(target(id),p);at<void*>(p,0)=target(id);}nodes[nodeCount]=p;initialTarget[nodeCount]=id;++nodeCount;}
static void setup(){errors=nodeCount=allocations=registrations=unregistrations=arrayAllocations=arrayFrees=hits=0;active=inRegistration=false;std::memset(freed,0,sizeof(freed));std::memset(expectedFree,0,sizeof(expectedFree));autotest::g_arenaUsed=0;
 new((void*)0x14f9fe8)Wide();new((void*)0x151c128)Wide();new((void*)0x151ab48)Wide();new((void*)0x151d408)Wide();
 quest=autotest::allocate(0x218);qlOldQuestCtor(quest,0,0);need(at<void*>(quest,0x1e0)!=0,8);
 for(unsigned i=0;i<6;++i){controllers[i]=autotest::allocate(0xb8);qlControllerCtor(controllers[i],0);alive[i]=true;at<bool>(controllers[i],0xb1)=false;}
 // Genuine, nonempty COW members accompany every quest lifetime. Requirements
 // is the real original child. Full owned reward/unit/dialog graph is covered
 // independently in the owned-graph fixture, not inferred from these strings.
 at<Wide>(quest,0x30)=L"listener lifetime quest";at<Wide>(quest,0x50)=Wide(65,L'Q');at<TArrayList<Wide> >(quest,0xc8).add(L"listener detail");at<TArrayList<Wide> >(quest,0xe0).add(L"listener hint");at<TArrayList<Wide> >(quest,0x1f0).add(L"listener objective");
 requested=4;
 switch(c->shape){
 case 0:break; // empty
 case 1:makeNode(1);requested=1;break; // duplicate
 case 2:makeNode(1);makeNode(2);makeNode(3);requested=2;break;
 case 3:makeNode(1);makeNode(2);makeNode(3);break; // absent
 case 4:makeNode(0);makeNode(2);makeNode(4);break; // swapped duplicate is skipped; add duplicates
 case 5:makeNode(0);makeNode(0);makeNode(0);break; // swapped stale is skipped
 case 6:makeNode(1);makeNode(1);makeNode(1);requested=1;break; // real multiple registrations
 case 7:makeNode(1);makeNode(0);makeNode(3);requested=0;break; // equality before stale branch
 case 8:makeNode(1);makeNode(2);makeNode(3);break; // safe capacity-fallback nonmatching remove
 case 9:makeNode(1);makeNode(2);makeNode(3);requested=3;break; // final slot
 case 10:makeNode(1);makeNode(2);makeNode(3);requested=1;break; // first slot
 case 12:requested=0;break; // allocate genuinely null wrapper
 case 13:makeNode(1);makeNode(2);requested=0;break;
 case 14:makeNode(4);makeNode(0);break; // duplicate returns before later stale cleanup
 case 11:makeNode(1);makeNode(2);makeNode(3);qlOldControllerDtor(controllers[0]);alive[0]=false;initialTarget[0]=0;need(!at<void*>(nodes[0],0)&&at<unsigned>(nodes[0],8)==~0u,9);break;
 }
 seedCount=nodeCount;initialCapacity=seedCount?(c->grow==1?seedCount:seedCount+3):0;
 if(seedCount){void** data=new void*[initialCapacity];for(unsigned i=0;i<initialCapacity;++i)data[i]=i<seedCount?nodes[i]:0;at<void*>(quest,0x1b0)=data;}
 at<unsigned>(quest,0x1b8)=seedCount;at<unsigned>(quest,0x1bc)=initialCapacity;at<unsigned>(quest,0x1c0)=c->grow;
 if(c->shape==8)at<unsigned>(quest,0x1bc)=initialCapacity=1;
 oldArray=at<void*>(quest,0x1b0);expectedCount=seedCount;expectedCapacity=initialCapacity;for(unsigned i=0;i<seedCount;++i)expected[i]=i+1;
}
// Independent branch oracle over node identities. No call to candidate helpers.
static bool model(){for(unsigned i=0;i<expectedCount;++i){unsigned slot=i<initialCapacity?i:0,id=expected[slot],t=initialTarget[id-1];
 if(!c->remove&&t==requested)return false;
 if((c->remove&&t==requested)||!t){expectedFree[id-1]=1;expected[slot]=0;--expectedCount;expected[i]=expected[expectedCount];}
 }
 if(!c->remove){if(expectedCount>=expectedCapacity)expectedCapacity=oldArray?expectedCapacity+c->grow:c->grow;expected[expectedCount++]=seedCount+1;return true;}return false;
}
static void cleanup(){active=false;
 // The deliberately inconsistent capacity fallback case never mutates. Restore
 // its physical capacity before the genuine destructor walks all live nodes.
 if(c->shape==8)at<unsigned>(quest,0x1bc)=c->grow==1?seedCount:seedCount+3;
 qlOldQuestDtor(quest);for(unsigned i=0;i<6;++i)if(alive[i])qlOldControllerDtor(controllers[i]);
}
static void side(void*p,autotest::Capture&o,bool candidate){c=(Case*)p;out=&o;detour::Set collaborators;TL_REDIRECT(collaborators,qlUI,&noUI);TL_REDIRECT(collaborators,qlGuid,&guid);if(collaborators.failed()){o.issue=autotest::Capture::InvalidReport;return;}setup();bool append=model();
 detour::Set a,f,aa,af,r,u;allocPatch=&a;freePatch=&f;arrayPatch=&aa;arrayFreePatch=&af;registerPatch=&r;unregisterPatch=&u;
 a.redirect(qlAlloc,qlAlloc,&allocate);f.redirect(qlFree,qlFree,&release);aa.redirect(qlArrayAlloc,qlArrayAlloc,&allocateArray);af.redirect(qlArrayFree,qlArrayFree,&releaseArray);TL_REDIRECT(r,qlRegister,&registerWeak);TL_REDIRECT(u,qlUnregister,&unregisterWeak);
 if(a.failed()||f.failed()||aa.failed()||af.failed()||r.failed()||u.failed()){o.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Fn)(void*,void*);Fn fn=c->remove?(candidate?&qlNewRemove:&qlOldRemove):(candidate?&qlNewAdd:&qlOldAdd);bool caught=false;active=true;if(!autotest::beginInvocation(o,fn))return;
 try{fn(quest,target(requested));o.callCompleted=1;}catch(const Stop&s){caught=true;need(s.site==c->fault,10);}active=false;
 need(caught==(c->fault!=0)&&hits==(c->fault?1u:0u),11);
 unsigned count=at<unsigned>(quest,0x1b8),capacity=at<unsigned>(quest,0x1bc);n(count);n(capacity);n(allocations);n(registrations);n(unregistrations);n(arrayAllocations);n(arrayFrees);
 if(!caught){need(count==expectedCount&&capacity==expectedCapacity,12);for(unsigned i=0;i<count;++i){unsigned id=nodeId(at<void**>(quest,0x1b0)[i]);n(id);need(id==expected[i],13);if(id){void*w=at<void**>(quest,0x1b0)[i];unsigned wanted=id<=seedCount?initialTarget[id-1]:requested;need(targetId(at<void*>(w,0))==wanted,24);n(wanted);n(at<unsigned>(w,8));if(wanted)need(registrySlots(target(wanted),w)==1,25);else need(at<unsigned>(w,8)==~0u,26);}}
  need(allocations==(append?1u:0u),14);need(registrations==(append&&requested?1u:0u),15);unsigned unregistered=0;for(unsigned i=0;i<seedCount;++i){need(freed[i]==expectedFree[i],16);if(expectedFree[i]&&initialTarget[i])++unregistered;}need(unregistrations==unregistered,17);
  unsigned growth=append&&(expectedCount-1>=initialCapacity);need(arrayAllocations==growth&&arrayFrees==(growth&&oldArray?1u:0u),18);
 }else{
  // Original LSDA: d14a24 registration throw frees raw wrapper; append new[]
  // d14a5e/d14af2 has no cleanup and leaks a registered, unlisted wrapper.
  need(count==seedCount&&at<void*>(quest,0x1b0)==oldArray,19);
  need(allocations==1&&nodeCount==seedCount+(c->fault==1?0:1),20);
  if(c->fault==2||c->fault>=5)need(freed[seedCount]==1&&unregistrations==0,21);
  if(c->fault==3||c->fault==4){void*w=nodes[seedCount];need(!freed[seedCount]&&at<void*>(w,0)==target(requested)&&registrySlots(target(requested),w)==1,22);need(capacity==(oldArray?initialCapacity:c->grow),23);
   // Fixture-only recovery AFTER recording the original leak witness.
   qlSafeRemove(target(requested),w,at<unsigned>(w,8));at<void*>(w,0)=0;at<unsigned>(w,8)=~0u;reinterpret_cast<void(*)(void*)>(qlFree)(w);
  }
 }
 for(unsigned i=0;i<6;++i)if(alive[i])checkRegistry(controllers[i]);
 a.restore();f.restore();aa.restore();af.restore();r.restore();u.restore();cleanup();n(0x514c4946);n(errors);
}
static void original(void*p,autotest::Capture&o){side(p,o,false);}static void candidate(void*p,autotest::Capture&o){side(p,o,true);}
static bool good(const autotest::Outcome&o){unsigned tail[2]={0,1};if(o.capture.length>=8)std::memcpy(tail,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&tail[0]==0x514c4946&&!tail[1];}
static bool pair(const tlhybrid_host*host,autotest::Coverage&cv,Case&c){autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);bool ok=good(a)&&good(b)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
 if(!c.fault){if(cv.observe(host,a,b))ok=false;}else ok=ok&&a.capture.callStarted&&b.capture.callStarted&&!a.capture.callCompleted&&!b.capture.callCompleted&&a.capture.callTarget==cv.original&&host->comparison_pair&&host->comparison_pair(a.capture.callTarget,b.capture.callTarget);
 if(!ok){host->log("tlhybrid: listener remove=%u shape=%u grow=%u fault=%u status=%d/%d\n",c.remove,c.shape,c.grow,c.fault,a.childStatus,b.childStatus);for(unsigned s=0;s<2;++s){const autotest::Capture&z=s?b.capture:a.capture;for(size_t i=0;i+4<=z.length;i+=4){unsigned v;std::memcpy(&v,z.data+i,4);if((v&0xffff0000u)==0xf1000000u)host->log("tlhybrid: listener side=%u oracle=%u\n",s,v-0xf1000000u);}}}return ok;
}
}
TL_TEST(quest_listener_add_lifetime){using namespace ql;autotest::Coverage cv("quest_listener_add_lifetime",0xd14860);for(unsigned s=0;s<15;++s)if(s!=8)for(unsigned g=1;g<=4;g+=3){Case c={0,s,g,0,0};if(!pair(host,cv,c)){cv.report(host);return 1;}}cv.report(host);return cv.completed!=28||cv.different||cv.missing;}
TL_TEST(quest_listener_remove_lifetime){using namespace ql;autotest::Coverage cv("quest_listener_remove_lifetime",0xd14b30);for(unsigned s=0;s<15;++s)for(unsigned g=1;g<=4;g+=3){Case c={1,s,g,0,0};if(!pair(host,cv,c)){cv.report(host);return 1;}}cv.report(host);return cv.completed!=30||cv.different||cv.missing;}
TL_TEST(quest_listener_allocation_unwind){using namespace ql;autotest::Coverage cv("listener unwind excluded",0xd14860);for(unsigned f=1;f<=6;++f){Case c={0,f==4?3u:0u,1,f,0};if(!pair(host,cv,c))return 1;}host->log("tlhybrid: listener 6 allocation/registration unwind witnesses; no completed-call credit\n");return 0;}

namespace ql {
static detour::Set *consumerAddPatch,*consumerRemovePatch,*dialogCompletePatch,*dialogDeletePatch;
static bool consumerCandidate;static unsigned consumerAdds,consumerRemoves,dialogDeletes,dialogCompletes;
static void* dialogs[5];static unsigned long long dialogObservers[5][2];
static void addConsumer(void*q,void*controller){++consumerAdds;need(q==quest,30);consumerAddPatch->restore();if(consumerCandidate)qlNewAdd(q,controller);else qlOldAdd(q,controller);TL_REDIRECT(*consumerAddPatch,qlAddRoute,&addConsumer);}
static void removeConsumer(void*q,void*controller){++consumerRemoves;need(q==quest,31);consumerRemovePatch->restore();if(consumerCandidate)qlNewRemove(q,controller);else qlOldRemove(q,controller);TL_REDIRECT(*consumerRemovePatch,qlRemoveRoute,&removeConsumer);}
static void completeDialog(void*p){++dialogCompletes;dialogCompletePatch->restore();qlDialogD1(p);TL_REDIRECT(*dialogCompletePatch,qlDialogComplete,&completeDialog);}
static void deleteDialog(void*p){++dialogDeletes;dialogDeletePatch->restore();qlDialogD0(p);TL_REDIRECT(*dialogDeletePatch,qlDialogDelete,&deleteDialog);}
static void populateDialogs(){new((void*)0x14fb488)Wide();const unsigned lists[]={0x60,0x78,0x90,0xa8};
 for(unsigned i=0;i<5;++i){dialogs[i]=reinterpret_cast<void*(*)(size_t,const char*,int,const char*)>(qlAlloc)(0xa8,0,0,0);qlDialogCtor(dialogs[i],quest);
  at<TArrayList<Wide> >(dialogs[i],0x18).add(L"genuine listener integration dialog");
  if(i<4)at<TArrayList<void*> >(quest,lists[i]).add(dialogs[i]);else at<void*>(quest,0xc0)=dialogs[i];
  void*w=dialogObservers[i];at<void*>(w,0)=0;at<unsigned>(w,8)=qlSafeAdd(dialogs[i],w);at<void*>(w,0)=dialogs[i];need(registrySlots(dialogs[i],w)==1,32);
 }
}
static void integrationSide(void*p,autotest::Capture&o,bool candidate){c=(Case*)p;out=&o;consumerCandidate=candidate;consumerAdds=consumerRemoves=dialogDeletes=dialogCompletes=0;
 detour::Set collaborators;TL_REDIRECT(collaborators,qlUI,&noUI);TL_REDIRECT(collaborators,qlGuid,&guid);TL_REDIRECT(collaborators,qlManager,&manager);TL_REDIRECT(collaborators,qlLookup,&lookup);if(collaborators.failed()){o.issue=autotest::Capture::InvalidReport;return;}
 setup();populateDialogs();
 // Companion A mode replaces a genuinely original, fully destroyed setup
 // quest with candidate construction before reproducing real dialog children.
 if(c->integration&2){qlOldQuestDtor(quest);for(unsigned i=0;i<5;++i)need(!at<void*>(dialogObservers[i],0)&&at<unsigned>(dialogObservers[i],8)==~0u,33);
  if(candidate)qlNewQuestCtor(quest,0,0);else qlOldQuestCtor(quest,0,0);at<Wide>(quest,0x30)=L"candidate construction integration";populateDialogs();}
 detour::Set a,r,dc,dd;consumerAddPatch=&a;consumerRemovePatch=&r;dialogCompletePatch=&dc;dialogDeletePatch=&dd;
 TL_REDIRECT(a,qlAddRoute,&addConsumer);TL_REDIRECT(r,qlRemoveRoute,&removeConsumer);TL_REDIRECT(dc,qlDialogComplete,&completeDialog);TL_REDIRECT(dd,qlDialogDelete,&deleteDialog);
 if(a.failed()||r.failed()||dc.failed()||dd.failed()){o.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Init)(void*);Init init=candidate?&qlNewControllerInit:&qlOldControllerInit;Init destroy=candidate?&qlNewControllerDtor:&qlOldControllerDtor;
 if(!autotest::beginInvocation(o,init))return;init(controllers[0]);o.callCompleted=1;init(controllers[1]);init(controllers[2]);init(controllers[0]);
 need(consumerAdds==4&&at<unsigned>(quest,0x1b8)==3,34);
 for(unsigned i=0;i<3;++i){need(at<void*>(controllers[i],0x98)==quest&&registrySlots(quest,(char*)controllers[i]+0x98)==1,35);checkRegistry(controllers[i]);}
 if(c->integration&1){
  // Quest-first: original/candidate complete destruction owns all wrappers and
  // real dialog children; base invalidation clears three controller observers.
  if(candidate&&(c->integration&2))qlNewQuestDtor(quest);else qlOldQuestDtor(quest);
  for(unsigned i=0;i<3;++i){need(!at<void*>(controllers[i],0x98)&&at<unsigned>(controllers[i],0xa0)==~0u,36);checkRegistry(controllers[i]);destroy(controllers[i]);alive[i]=false;}
  need(consumerRemoves==0,37);
 }else{
  destroy(controllers[1]);alive[1]=false;need(consumerRemoves==1&&at<unsigned>(quest,0x1b8)==2,38);
  void**list=at<void**>(quest,0x1b0);need(at<void*>(list[0],0)==controllers[0]&&at<void*>(list[1],0)==controllers[2],39);
  // Removal and rebind of a surviving observer must create exactly one new
  // registration; repeated init then deduplicates without changing that node.
  removeConsumer(quest,controllers[0]);need(at<unsigned>(quest,0x1b8)==1,40);init(controllers[0]);init(controllers[0]);need(at<unsigned>(quest,0x1b8)==2,41);
  destroy(controllers[2]);alive[2]=false;destroy(controllers[0]);alive[0]=false;need(at<unsigned>(quest,0x1b8)==0&&consumerRemoves==4,42);
  if(candidate&&(c->integration&2))qlNewQuestDtor(quest);else qlOldQuestDtor(quest);
 }
 need(dialogDeletes==5&&dialogCompletes==5,43);for(unsigned i=0;i<5;++i)need(!at<void*>(dialogObservers[i],0)&&at<unsigned>(dialogObservers[i],8)==~0u,44);
 n(consumerAdds);n(consumerRemoves);n(dialogDeletes);n(dialogCompletes);a.restore();r.restore();dc.restore();dd.restore();
 for(unsigned i=0;i<6;++i)if(alive[i])qlOldControllerDtor(controllers[i]);n(0x514c4946);n(errors);
}
static void integrationOriginal(void*p,autotest::Capture&o){integrationSide(p,o,false);}static void integrationCandidate(void*p,autotest::Capture&o){integrationSide(p,o,true);}
}
TL_TEST(quest_listener_controller_cross_invalidation){using namespace ql;autotest::Coverage cv("listener accepted-controller integration (supplemental)",0xdee380);for(unsigned i=0;i<4;++i){Case c={0,0,1,0,i};autotest::Outcome a,b;autotest::runChild(integrationOriginal,&c,a);autotest::runChild(integrationCandidate,&c,b);bool ok=good(a)&&good(b)&&a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);if(cv.observe(host,a,b))ok=false;if(!ok){host->log("tlhybrid: listener cross-invalidation mode=%u status=%d/%d\n",i,a.childStatus,b.childStatus);cv.report(host);return 1;}}cv.report(host);return cv.completed!=4||cv.different||cv.missing;}
