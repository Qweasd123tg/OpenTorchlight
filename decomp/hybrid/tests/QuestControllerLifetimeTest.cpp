// Independent ELF oracle. C1/C2 def0a0; D1/D2 def220. No constructor or
// destructor under test is replaced by a fake. Expected throws never count as
// completed differential coverage. This file is C++98 and has not been run.
#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <new>
#include <string>
#include "QuestController.h"
#include "TArrayList.h"
#include "AutoTest.h"
#include "Detour.h"
#define QC_PAIR(N,A,S) TL_ORIGINAL(void,qclOld##N,A,S) extern "C" void qclNew##N A __asm__(S);
QC_PAIR(C1,(void*,void*),"_ZN16CQuestControllerC1EP16CResourceManager")
QC_PAIR(C2,(void*,void*),"_ZN16CQuestControllerC2EP16CResourceManager")
QC_PAIR(D1,(void*),"_ZN16CQuestControllerD1Ev")
QC_PAIR(D2,(void*),"_ZN16CQuestControllerD2Ev")
QC_PAIR(D0,(void*),"_ZN16CQuestControllerD0Ev")
QC_PAIR(MD1,(void*),"_ZThn88_N16CQuestControllerD1Ev")
QC_PAIR(MD0,(void*),"_ZThn88_N16CQuestControllerD0Ev")
QC_PAIR(LD1,(void*),"_ZThn96_N16CQuestControllerD1Ev")
QC_PAIR(LD0,(void*),"_ZThn96_N16CQuestControllerD0Ev")
#undef QC_PAIR
TL_ORIGINAL(void,qclInit,(void*),"_ZN16CQuestController19initQuestControllerEv")
TL_ORIGINAL(void,qclQuestCtor,(void*,void*,void*),"_ZN6CQuestC1EP16CResourceManagerP13CQuestManager")
TL_ORIGINAL(void,qclQuestDtor,(void*),"_ZN6CQuestD1Ev")
TL_ORIGINAL(void,qclCoreCtor,(void*),"_ZN10CRunicCoreC1Ev")
TL_ORIGINAL(void,qclCoreDtor,(void*),"_ZN10CRunicCoreD1Ev")
TL_ORIGINAL(unsigned,qclAddSafe,(void*,void*),"_ZN10CRunicCore14addSafePointerEP12TSafePointerIPvE")
TL_ORIGINAL(void,qclAddUI,(void*,unsigned,void*),"_ZN7CGameUI15addMenuListenerE10EMENU_TYPEP13iMenuListener")
TL_ORIGINAL(void,qclMenuAdd,(void*,void*),"_ZN13CDropdownMenu15addMenuListenerEP13iMenuListener")
TL_ORIGINAL(void,qclMenuRemove,(void*,void*),"_ZN13CDropdownMenu18removeMenuListenerEP13iMenuListener")
TL_FUNCTION(qclRemoveSafe,"_ZN10CRunicCore17removeSafePointerEP12TSafePointerIPvEj")
TL_FUNCTION(qclListener,"_ZN6CQuest30removeQuestControllerListernerEP16CQuestController")
TL_FUNCTION(qclBaseDtor,"_ZN17CEditorBaseObjectD1Ev")
TL_FUNCTION(qclUI,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(qclRemoveUI,"_ZN7CGameUI18removeMenuListenerE10EMENU_TYPEP13iMenuListener")
TL_FUNCTION(qclManager,"_ZN13CQuestManager12getSingletonEv")
TL_FUNCTION(qclLookup,"_ZN13CQuestManager14getQuestByNameERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(qclGuid,"_ZN9UTILITIES16createUniqueGuidEv")
extern "C" char qclCopy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEEC1ERKS2_");
extern "C" char qclStringDtor[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEED1Ev");
extern "C" char qclRepDestroy[] __asm__("_ZNSbIwSt11char_traitsIwESaIwEE4_Rep10_M_destroyERKS1_");
extern "C" char qclFree[] __asm__("_ZN4Ogre12NedAllocImpl12deallocBytesEPv");
namespace qcl {
typedef std::wstring Wide;
typedef char OwnerABI[sizeof(CQuestController)==0xb8&&sizeof(Wide)==8?1:-1];
template<class T>T& at(void* p,unsigned o){return *reinterpret_cast<T*>((char*)p+o);}
struct Stop {unsigned site;explicit Stop(unsigned s):site(s){}};
// Faults: constructor 1 category, 2 quest-name. Destructor 1 listener,
// 2 first singleton, 3 second singleton, 4 UI removal, 5 explicit quest
// unregister (one throw, successful cleanup retry), 6 unit member unregister.
struct Case {unsigned ctor,alias,shape,text,fault,negative;};
static const Case* cs;static autotest::Capture* cap;static const tlhybrid_host* context;
static void* owner;static void* quest;static void* unit;static void* ui;static void* dropdown;static uintptr_t menuTable[7];
static unsigned errors,copyCalls,baseCalls,uiCalls,menuCalls,listenerCalls,questUnregister,unitUnregister,faultHits,frees;
static bool active,constructing;static unsigned long long keeperStorage[3];static Wide* keeper[3];static bool retained[3];static bool sourceShared[2],uniqueMember[3];static void* uniqueRep[3];static unsigned repFrees[3],initialQuestIndex;
static detour::Set *copyPatch,*basePatch,*safePatch,*listenerPatch,*freePatch,*repPatch,*menuPatch,*stringPatch;static void* forwardedRep;
static unsigned events[64],eventCount;
static void n(unsigned v){cap->add(&v,4);}
static void need(bool v,unsigned code){if(!v){++errors;n(0xf0000000u+code);}}
static void event(unsigned v){need(eventCount<64,1);if(eventCount<64)events[eventCount++]=v;n(v);}
static int refs(const Wide& s){return *reinterpret_cast<const int*>((const char*)s.c_str()-8);}
static Wide& constant(uintptr_t p){return *reinterpret_cast<Wide*>(p);}
static Wide value(unsigned which){
 if(!cs->text)return Wide();
 if(cs->text==1)return Wide(which==0?L"category shared lifetime":which==1?L"unit shared lifetime":L"quest shared lifetime");
 if(cs->text==2||cs->text==4){const wchar_t p[]={L'\u041a',L'\u4efb',0,L'\u0432',wchar_t(L'0'+which)};return Wide(p,5);}
 Wide r(257+which*37,wchar_t(L'A'+which));r[17]=0;r[31]=L'\u03a9';return r;
}
static void initConstants(){
 // Per-child globals: source variants include shared, Unicode/embedded NUL,
 // long strings and leaked unique source reps requiring a real deep copy.
 Wide category=value(0),name=value(2);new((void*)0x151c128)Wide(category.c_str(),category.size());new((void*)0x151ab48)Wide(name.c_str(),name.size());
 if(cs->text>=4){Wide& s=constant(0x151c128);s[0]=s.c_str()[0];}
 if(cs->text==5){Wide& s=constant(0x151ab48);s[0]=s.c_str()[0];}
 new((void*)0x14f9fe8)Wide();new((void*)0x151d408)Wide();
}
static unsigned long long guid(){return 0x123456789abcdef0ULL;}
static void retain(unsigned i,Wide& s){keeper[i]=new(&keeperStorage[i])Wide(s);retained[i]=true;}
static void copy(Wide* dst,const Wide& src){
 unsigned stage=dst==(Wide*)((char*)owner+0x88)?1:dst==(Wide*)((char*)owner+0xa8)?2:0;
 if(active&&constructing&&stage){++copyCalls;event(10+stage);need(copyCalls==stage,2);need(at<void*>(owner,0x78)==0&&at<unsigned>(owner,0x80)==~0u,3);
  need(at<void*>(owner,0x68)==ui&&at<void*>(owner,0x70)==0,4);
  if(stage==2){need(at<Wide>(owner,0x90).empty(),5);need(!at<void*>(owner,0x98)&&at<unsigned>(owner,0xa0)==~0u,6);}
  if(cs->fault==stage){++faultHits;throw Stop(stage);}
 }
 copyPatch->restore();reinterpret_cast<void(*)(Wide*,const Wide&)>(qclCopy)(dst,src);
 copyPatch->redirect(qclCopy,qclCopy,&copy);need(!copyPatch->failed(),7);
 if(active&&constructing&&stage){copyPatch->restore();retain(stage-1,*dst);sourceShared[stage-1]=dst->c_str()==src.c_str();copyPatch->redirect(qclCopy,qclCopy,&copy);}
}
static void base(void* self){
 if(active&&self==owner){++baseCalls;event(90);
  if(cs->fault!=6||constructing)need(!at<void*>(self,0x78)&&at<unsigned>(self,0x80)==~0u,8);
  if(!constructing||cs->fault!=1)need(!at<void*>(self,0x98)&&at<unsigned>(self,0xa0)==~0u,9);
  need(at<std::ptrdiff_t*>(self,0x58)[-2]==0&&at<std::ptrdiff_t*>(self,0x60)[-2]==0,102);
  // Observe before editor base destruction, never after complete-object free.
  for(unsigned i=0;i<3;++i)if(retained[i]&&!keeper[i]->empty())need(refs(*keeper[i])==(constructing&&i<2&&sourceShared[i]?1:0),20+i);
 }
 basePatch->restore();reinterpret_cast<void(*)(void*)>(qclBaseDtor_original)(self);
 TL_REDIRECT(*basePatch,qclBaseDtor,&base);need(!basePatch->failed(),10);
}
static void* singleton(){if(active&&!constructing){++uiCalls;event(30+uiCalls);unsigned f=uiCalls==1?2:3;if(cs->fault==f){++faultHits;throw Stop(f);}}return cs->shape&4?ui:0;}
static void menu(void* self,unsigned type,void* listener){++menuCalls;event(40);need(self==ui&&type==0&&listener==(char*)owner+0x58,11);if(cs->fault==4){++faultHits;throw Stop(4);}
 menuPatch->restore();reinterpret_cast<void(*)(void*,unsigned,void*)>(qclRemoveUI_original)(self,type,listener);TL_REDIRECT(*menuPatch,qclRemoveUI,&menu);need(!menuPatch->failed(),124);
 need(at<unsigned>(dropdown,0x98)==1&&at<void**>(dropdown,0x90)[0]==listener,125);
 need(at<unsigned>(dropdown,0xb0)==1&&at<void**>(dropdown,0xa8)[0]==listener,126);
}
static void removeListener(void* self,void* controller){
 ++listenerCalls;event(20);need(self==quest&&controller==owner,12);
 if(cs->fault==1){++faultHits;throw Stop(1);}
 listenerPatch->restore();reinterpret_cast<void(*)(void*,void*)>(qclListener_original)(self,controller);
 TL_REDIRECT(*listenerPatch,qclListener,&removeListener);need(!listenerPatch->failed(),13);
 need(at<unsigned>(quest,0x1b8)==0,14);
}
static void removeSafe(void* self,void* pointer,unsigned index){
 bool q=pointer==(char*)owner+0x98,u=pointer==(char*)owner+0x78;
 if(active&&(q||u)){
  event(q?50:60);if(q)++questUnregister;else ++unitUnregister;
  if(q&&!keeper[2]->empty())need(refs(*keeper[2])==(uniqueMember[2]||(cs->fault>=1&&cs->fault<=4)||(cs->fault==5&&questUnregister==2)?0:1),97);
  if(u)for(unsigned i=0;i<3;++i)if(retained[i]&&!keeper[i]->empty())need(refs(*keeper[i])==0,98+i);
  need(self==(q?quest:unit),15);need(at<void*>(pointer,0)==self&&at<unsigned>(pointer,8)==index,16);
  if((q&&cs->fault==5&&questUnregister==1)||(u&&cs->fault==6&&unitUnregister==1)){++faultHits;throw Stop(cs->fault);}
 }
 safePatch->restore();reinterpret_cast<void(*)(void*,void*,unsigned)>(qclRemoveSafe_original)(self,pointer,index);
 TL_REDIRECT(*safePatch,qclRemoveSafe,&removeSafe);need(!safePatch->failed(),17);
}
static void observeRepRelease(void* rep){
 if(active&&!constructing&&!cs->ctor)for(unsigned i=0;i<3;++i)if(uniqueMember[i]&&rep==uniqueRep[i]){
  ++repFrees[i];event(70+i);need(repFrees[i]==1,110+i);
  if(i==2){bool pending=cs->fault>=1&&cs->fault<=5;need(at<void*>(owner,0x98)==((cs->shape&1)&&pending?quest:0),113);need(at<unsigned>(owner,0xa0)==initialQuestIndex,114);}
  else need(!at<void*>(owner,0x98)&&at<unsigned>(owner,0xa0)==~0u,115+i);
 }
}
static void destroyRep(void* rep,const void* allocator){
 bool observe=rep!=forwardedRep;
 repPatch->restore();reinterpret_cast<void(*)(void*,const void*)>(qclRepDestroy)(rep,allocator);
 if(observe)observeRepRelease(rep);
 repPatch->redirect(qclRepDestroy,qclRepDestroy,&destroyRep);need(!repPatch->failed(),117);
}
static void destroyString(Wide* value){
 // EH calls library D1, whose internal _M_destroy PLT bypasses the game's
 // PLT hook. Observe the same unique rep at this real D1 boundary and forward
 // into its actual implementation. Suppress a nested rep observer if binding
 // changes; exactly one successful real destruction remains mandatory.
 void* rep=(void*)((const char*)value->c_str()-24);void* previous=forwardedRep;
 forwardedRep=rep;
 stringPatch->restore();reinterpret_cast<void(*)(Wide*)>(qclStringDtor)(value);
 observeRepRelease(rep);
 stringPatch->redirect(qclStringDtor,qclStringDtor,&destroyString);forwardedRep=previous;need(!stringPatch->failed(),130);
}
static void release(void* p){
 if(p==owner){++frees;event(100);need(baseCalls==1,18);return;} // fixture owns backing arena; do not deallocate it
 freePatch->restore();reinterpret_cast<void(*)(void*)>(qclFree)(p);freePatch->redirect(qclFree,qclFree,&release);need(!freePatch->failed(),19);
}
static void* manager(){return ui;}
static void* lookup(void* self,const Wide& name){need(self==ui&&name==at<Wide>(owner,0xa8),23);return quest;}
static bool mapped(uintptr_t a,uintptr_t b){return a==b||(context&&context->comparison_pair&&context->comparison_pair(a,b));}
static void vtables(bool candidate){
 static const uintptr_t original[]={0xffdd30,0xffdd90,0xffddb8};static const unsigned offsets[]={0,0x58,0x60};
 for(unsigned i=0;i<3;++i){uintptr_t* v=at<uintptr_t*>(owner,offsets[i]);need(v!=0,24+i);if(!v)continue;need(reinterpret_cast<std::ptrdiff_t*>(v)[-2]==-std::ptrdiff_t(offsets[i]),103+i);
  need(reinterpret_cast<void*>(static_cast<iMenuListener*>(reinterpret_cast<CQuestController*>(owner)))==(char*)owner+0x58,28);
  need(reinterpret_cast<void*>(static_cast<iLevelUpdate*>(reinterpret_cast<CQuestController*>(owner)))==(char*)owner+0x60,29);
  // Destructors and method slots belong to the real original/replacement
  // vtable. Never copy original vptrs into the replacement object.
  for(unsigned j=0;j<3;++j){uintptr_t a=reinterpret_cast<uintptr_t*>(original[i])[j];need(candidate?mapped(a,v[j]):a==v[j],35+i*3+j);}
 }
}
static void construct(void* p,autotest::Capture& out,bool candidate){
 cs=(Case*)p;cap=&out;errors=copyCalls=baseCalls=faultHits=eventCount=uiCalls=0;active=false;constructing=true;std::memset(retained,0,sizeof(retained));
 autotest::g_arenaUsed=0;owner=autotest::allocate(0xb8);ui=autotest::allocate(16);std::memset(owner,cs->shape?0xa5:0x5a,0xb8);initConstants();
 detour::Set copies,bases,collaborators;copyPatch=&copies;basePatch=&bases;
 copies.redirect(qclCopy,qclCopy,&copy);TL_REDIRECT(bases,qclBaseDtor,&base);TL_REDIRECT(collaborators,qclGuid,&guid);TL_REDIRECT(collaborators,qclUI,&singleton);
 if(copies.failed()||bases.failed()||collaborators.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 need((uintptr_t)&qclOldC1==(uintptr_t)&qclOldC2,45);
 typedef void(*Fn)(void*,void*);Fn fn=candidate?(cs->alias?&qclNewC2:&qclNewC1):(cs->alias?&qclOldC2:&qclOldC1);
 bool caught=false;active=true;if(!autotest::beginInvocation(out,fn))return;
 try{fn(owner,ui);out.callCompleted=1;}catch(const Stop& s){caught=true;need(s.site==cs->fault,46);}
 need(caught==(cs->fault!=0)&&faultHits==(cs->fault?1u:0u),47);
 if(!caught){need(copyCalls==2,48);vtables(candidate);need(at<void*>(owner,0x68)==ui&&!at<void*>(owner,0x70),49);
  need(!at<void*>(owner,0x78)&&at<unsigned>(owner,0x80)==~0u&&!at<void*>(owner,0x98)&&at<unsigned>(owner,0xa0)==~0u,50);
  need(at<Wide>(owner,0x88)==constant(0x151c128)&&at<Wide>(owner,0x90).empty()&&at<Wide>(owner,0xa8)==constant(0x151ab48),51);
  need(at<bool>(owner,0xb0)&&!at<bool>(owner,0xb1)&&at<bool>(owner,0xb2)&&!at<bool>(owner,0xb3)&&at<unsigned>(owner,0xb4)==5,52);
  out.addText(at<Wide>(owner,0x88));out.addText(at<Wide>(owner,0xa8));
  // Constants remain aliases, so owner+keeper+constant gives refs==2.
  for(unsigned i=0;i<2;++i)if(!keeper[i]->empty())need(refs(*keeper[i])==(sourceShared[i]?2:1),53+i);
  // Drop constants' ownership before cleanup so base's independent keeper
  // witness expects exactly one surviving owner, as in exception paths.
 }
 copies.restore();
 // Constants own an extra reference. Remove it before checking the real D1
 // tail, or after unwind before checking surviving keeper refcounts.
 constant(0x151c128).~Wide();constant(0x151ab48).~Wide();
 if(!caught){constructing=false;qclOldD1(owner);active=false;}
 // On failed construction base observer saw keeper plus source constant.
 // Post-unwind keeper alone must have refs==0, independently of catch result.
 for(unsigned i=0;i<2;++i)if(retained[i]&&!keeper[i]->empty())need(refs(*keeper[i])==0,55+i);
 need(baseCalls==1,57);need(copyCalls==(cs->fault?cs->fault:2),58);
 for(unsigned i=0;i<2;++i)if(retained[i])keeper[i]->~Wide();n(0x51434c46);n(errors);
}
static void ctorOriginal(void* p,autotest::Capture& o){construct(p,o,false);}static void ctorCandidate(void* p,autotest::Capture& o){construct(p,o,true);}
static bool good(const autotest::Outcome& o){unsigned f[2]={0,1};if(o.capture.length>=8)std::memcpy(f,o.capture.data+o.capture.length-8,8);return o.reportValid&&!o.childStatus&&!o.capture.issue&&f[0]==0x51434c46&&!f[1];}
static bool pair(const tlhybrid_host* host,autotest::Coverage& cv,autotest::Body a,autotest::Body b,Case& c){context=host;autotest::Outcome x,y;autotest::runChild(a,&c,x);autotest::runChild(b,&c,y);
 bool ok=good(x)&&good(y)&&x.capture.length==y.capture.length&&!std::memcmp(x.capture.data,y.capture.data,x.capture.length);
 if(!c.fault){if(cv.observe(host,x,y))ok=false;}else ok=ok&&x.capture.callStarted&&y.capture.callStarted&&!x.capture.callCompleted&&!y.capture.callCompleted&&x.capture.callTarget==cv.original&&host->comparison_pair&&host->comparison_pair(x.capture.callTarget,y.capture.callTarget);
 if(!ok){host->log("tlhybrid: QC lifetime ctor=%u alias=%u shape=%u text=%u fault=%u status=%d/%d valid=%u/%u\n",c.ctor,c.alias,c.shape,c.text,c.fault,x.childStatus,y.childStatus,good(x),good(y));
  host->log("tlhybrid: captures length=%lu/%lu report=%u/%u issue=%u/%u started=%u/%u completed=%u/%u target=%llx/%llx expected=%llx\n",(unsigned long)x.capture.length,(unsigned long)y.capture.length,x.reportValid,y.reportValid,x.capture.issue,y.capture.issue,x.capture.callStarted,y.capture.callStarted,x.capture.callCompleted,y.capture.callCompleted,(unsigned long long)x.capture.callTarget,(unsigned long long)y.capture.callTarget,(unsigned long long)cv.original);
  for(unsigned s=0;s<2;++s){const autotest::Capture& z=s?y.capture:x.capture;for(size_t i=0;i+4<=z.length;i+=4){unsigned v;std::memcpy(&v,z.data+i,4);if((v&0xffff0000u)==0xf0000000u)host->log("tlhybrid: side %u oracle %u word=%lu\n",s,v-0xf0000000u,(unsigned long)(i/4));
 if(!c.ctor&&i+256>=z.length)host->log("tlhybrid: side %u tail word %lu = %08x\n",s,(unsigned long)(i/4),v);}}}return ok;
}
}
TL_TEST(questcontroller_constructor_lifetime){using namespace qcl;autotest::Coverage cv("questcontroller_constructor_lifetime",0xdef0a0);for(unsigned a=0;a<2;++a)for(unsigned p=0;p<2;++p)for(unsigned t=0;t<6;++t){Case c={1,a,p,t,0,0};if(!pair(host,cv,ctorOriginal,ctorCandidate,c)){cv.report(host);return 1;}}cv.report(host);return cv.completed!=24||cv.different||cv.missing;}
TL_TEST(questcontroller_constructor_unwind){using namespace qcl;autotest::Coverage cv("constructor unwind excluded",0xdef0a0);for(unsigned a=0;a<2;++a)for(unsigned f=1;f<=2;++f)for(unsigned t=0;t<6;++t){Case c={1,a,1,t,f,0};if(!pair(host,cv,ctorOriginal,ctorCandidate,c))return 1;}host->log("tlhybrid: QC C1/C2: 24 expected copy unwinds, no completed-call credit\n");return 0;}
namespace qcl {
static unsigned safeSlots(void* core,void* target){
 void* list=at<void*>(core,8);if(!list)return 0;void** data=at<void**>(list,0);unsigned count=at<unsigned>(list,8),matches=0;
 for(unsigned i=0;i<count;++i)if(data[i]==target)++matches;return matches;
}
static void destroy(void* p,autotest::Capture& out,bool candidate){
 cs=(Case*)p;cap=&out;errors=copyCalls=baseCalls=uiCalls=menuCalls=listenerCalls=questUnregister=unitUnregister=faultHits=frees=eventCount=0;
 std::memset(retained,0,sizeof(retained));active=false;constructing=false;autotest::g_arenaUsed=0;
 owner=autotest::allocate(0xb8);quest=autotest::allocate(0x218);unit=autotest::allocate(16);ui=autotest::allocate(0x548);dropdown=autotest::allocate(0xc0);std::memset(ui,0,0x548);std::memset(dropdown,0,0xc0);initConstants();
 typedef TArrayList<iMenuListener*> MenuList;
 new((char*)dropdown+0x90)MenuList(2);new((char*)dropdown+0xa8)MenuList(2);
 std::memset(menuTable,0,sizeof(menuTable));menuTable[5]=(uintptr_t)&qclMenuAdd;menuTable[6]=(uintptr_t)&qclMenuRemove;at<void*>(dropdown,0)=menuTable;at<void*>(ui,0x538)=dropdown;
 // These are original constructors, not raw zeroed substitute objects. The
 // unit collaborator is deliberately only a real CRunicCore lifetime: this
 // fixture exercises its inherited safe-pointer API, not BaseUnit behavior.
 detour::Set setup;TL_REDIRECT(setup,qclGuid,&guid);TL_REDIRECT(setup,qclManager,&manager);TL_REDIRECT(setup,qclLookup,&lookup);
 if(setup.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 qclOldC1(owner,ui);if(cs->shape&4){qclAddUI(ui,0,(char*)owner+0x58);need(at<unsigned>(dropdown,0x98)==1&&at<unsigned>(dropdown,0xb0)==0,127);}qclQuestCtor(quest,0,0);qclCoreCtor(unit);
 if(cs->shape&1){qclInit(owner);need(at<void*>(owner,0x98)==quest,61);need(at<unsigned>(quest,0x1b8)==1,62);need(safeSlots(quest,(char*)owner+0x98)==1,63);}
 if(cs->shape&2){at<unsigned>(owner,0x80)=qclAddSafe(unit,(char*)owner+0x78);at<void*>(owner,0x78)=unit;need(safeSlots(unit,(char*)owner+0x78)==1,64);}
 // Do not preserve aliases to source globals here: the three retained strings
 // each have exactly owner+keeper ownership, enabling decrement-order checks.
 const unsigned offs[]={0x88,0x90,0xa8};
 for(unsigned i=0;i<3;++i){Wide& member=at<Wide>(owner,offs[i]);member=value(i);retain(i,member);uniqueMember[i]=cs->text==4||(cs->text==5&&i==2);repFrees[i]=0;uniqueRep[i]=0;
  if(uniqueMember[i]){member[0]=member.c_str()[0];uniqueRep[i]=(void*)((const char*)member.c_str()-24);need(refs(member)==-1&&refs(*keeper[i])==0,118+i);}out.addText(member);
 }
 initialQuestIndex=at<unsigned>(owner,0xa0);
 detour::Set bases,safes,listeners,collaborators,deallocation,representations,menus,strings;stringPatch=&strings;forwardedRep=0;menuPatch=&menus;repPatch=&representations;basePatch=&bases;safePatch=&safes;listenerPatch=&listeners;freePatch=&deallocation;
 TL_REDIRECT(bases,qclBaseDtor,&base);TL_REDIRECT(safes,qclRemoveSafe,&removeSafe);TL_REDIRECT(listeners,qclListener,&removeListener);
 TL_REDIRECT(collaborators,qclUI,&singleton);TL_REDIRECT(menus,qclRemoveUI,&menu);deallocation.redirect(qclFree,qclFree,&release);representations.redirect(qclRepDestroy,qclRepDestroy,&destroyRep);strings.redirect(qclStringDtor,qclStringDtor,&destroyString);
 if(strings.failed()||menus.failed()||representations.failed()||bases.failed()||safes.failed()||listeners.failed()||collaborators.failed()||deallocation.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 typedef void(*Fn)(void*);Fn oldFns[]={qclOldD1,qclOldD2,qclOldD0,qclOldMD1,qclOldMD0,qclOldLD1,qclOldLD0};
 Fn newFns[]={qclNewD1,qclNewD2,qclNewD0,qclNewMD1,qclNewMD0,qclNewLD1,qclNewLD0};Fn fn=candidate?newFns[cs->alias]:oldFns[cs->alias];
 void* argument=(char*)owner+(cs->alias>=5?0x60:cs->alias>=3?0x58:0);bool deleting=cs->alias==2||cs->alias==4||cs->alias==6,caught=false;
 active=true;if(!autotest::beginInvocation(out,fn))return;
 try{fn(argument);out.callCompleted=1;}catch(const Stop& s){caught=true;need(s.site==cs->fault,65);}
 active=false;
 need(caught==(cs->fault!=0)&&faultHits==(cs->fault?1u:0u),66);need(baseCalls==1,67);need(frees==(!caught&&deleting?1u:0u),68);
 need(listenerCalls==((cs->shape&1)?1u:0u),69);
 need(at<unsigned>(dropdown,0x98)==((cs->shape&4)?1u:0u),128);need(at<unsigned>(dropdown,0xb0)==(menuCalls&&cs->fault!=4?1u:0u),129);
 unsigned expectedUI=cs->fault==1?0:cs->fault==2?1:(cs->shape&4)?2:1;
 need(uiCalls==expectedUI,70);need(menuCalls==((cs->shape&4)&&cs->fault!=1&&cs->fault!=2&&cs->fault!=3?1u:0u),71);
 need(questUnregister==((cs->shape&1)?cs->fault==5?2u:1u:0u),72);need(unitUnregister==((cs->shape&2)?1u:0u),73);
 need(safeSlots(quest,(char*)owner+0x98)==0,74);
 need(safeSlots(unit,(char*)owner+0x78)==(cs->fault==6?1u:0u),75);
 // Listener-removal throw leaves the quest-side wrapper registered until the
 // real core destructor invalidates it; successful removal erases the node.
 need(at<unsigned>(quest,0x1b8)==(cs->fault==1?1u:0u),76);
 if(cs->fault==1){void* node=at<void**>(quest,0x1b0)[0];need(node&&at<void*>(node,0)==0&&at<unsigned>(node,8)==~0u,77);}
 for(unsigned i=0;i<3;++i){if(!keeper[i]->empty())need(refs(*keeper[i])==0,78+i);need(repFrees[i]==(uniqueMember[i]?1u:0u),121+i);}
 // Independent sequence oracle; includes only actual parent lifetime events,
 // not nested core unregister calls of quest-side listener wrappers.
 unsigned want[12],count=0;if(cs->shape&1)want[count++]=20;
 if(cs->fault!=1){want[count++]=31;if(cs->fault!=2&&(cs->shape&4)){want[count++]=32;if(cs->fault!=3)want[count++]=40;}}
 bool earlyQuestName=cs->fault>=1&&cs->fault<=4;
 if(earlyQuestName&&uniqueMember[2])want[count++]=72;
 if(cs->shape&1)want[count++]=50;
 if(!earlyQuestName&&uniqueMember[2])want[count++]=72;
 if(cs->fault==5)want[count++]=50;
 if(uniqueMember[1])want[count++]=71;if(uniqueMember[0])want[count++]=70;
 if(cs->shape&2)want[count++]=60;want[count++]=90;if(!caught&&deleting)want[count++]=100;
 need(eventCount==count,81);for(unsigned i=0;i<count&&i<eventCount;++i)need(events[i]==want[i],82+i);
 // A deterministic oracle control proves that omission and reordering cannot
 // satisfy the expected trace. This is not candidate source mutation credit.
 if(cs->negative){unsigned bad[12];std::memcpy(bad,want,count*4);bad[0]^=1;need(std::memcmp(bad,want,count*4)!=0,96);}
 bases.restore();safes.restore();listeners.restore();collaborators.restore();deallocation.restore();representations.restore();menus.restore();strings.restore();
 if(cs->fault==6){ // legitimate throw before unregister effect; no double dtor
  reinterpret_cast<void(*)(void*,void*,unsigned)>(qclRemoveSafe_original)(unit,(char*)owner+0x78,at<unsigned>(owner,0x80));
 }
 at<MenuList>(dropdown,0xa8).~MenuList();at<MenuList>(dropdown,0x90).~MenuList();qclQuestDtor(quest);qclCoreDtor(unit);for(unsigned i=0;i<3;++i)keeper[i]->~Wide();
 n(0x51434c46);n(errors);
}
static void dtorOriginal(void* p,autotest::Capture& o){destroy(p,o,false);}static void dtorCandidate(void* p,autotest::Capture& o){destroy(p,o,true);}
static uintptr_t address(unsigned alias){static const uintptr_t a[]={0xdef220,0xdef220,0xdef510,0xdef4e0,0xdef500,0xdef4d0,0xdef4f0};return a[alias];}
}
TL_TEST(questcontroller_destructor_lifetime){using namespace qcl;for(unsigned a=0;a<7;++a){autotest::Coverage cv("questcontroller_destructor_lifetime",address(a));for(unsigned s=0;s<8;++s)for(unsigned t=0;t<6;++t){Case c={0,a,s,t,0,0};if(!pair(host,cv,dtorOriginal,dtorCandidate,c)){cv.report(host);return 1;}}cv.report(host);if(cv.completed!=48||cv.different||cv.missing)return 1;}return 0;}
TL_TEST(questcontroller_destructor_unwind){using namespace qcl;autotest::Coverage cv("destructor unwind excluded",0xdef220);for(unsigned a=0;a<2;++a)for(unsigned f=1;f<=6;++f)for(unsigned t=1;t<=5;t+=3){Case c={0,a,7,t,f,0};if(!pair(host,cv,dtorOriginal,dtorCandidate,c))return 1;}host->log("tlhybrid: QC D1/D2: 24 exact supported unwinds, real base/string/safe-pointer cleanup; no completed credit\n");return 0;}
TL_TEST(questcontroller_lifetime_oracle_controls){using namespace qcl;autotest::Coverage cv("questcontroller_lifetime_oracle_controls",0xdef220);Case c={0,0,7,1,0,1};if(!pair(host,cv,dtorOriginal,dtorCandidate,c))return 1;host->log("tlhybrid: QC lifetime trace-oracle corruption control, not source-mutant coverage\n");return 0;}
